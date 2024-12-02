# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 22:48:14 2023

@author: cgomezco
"""
import numpy as np
import shutil
import os
import neat
import os.path
import time
import lxml.etree as etxml
import pandas as pd
import subprocess
import matplotlib.pyplot as plt 
import psutil

#west file
folder = "/path/to/model"
scenarios = folder+"/scenarios/"
filename = 'BSM1_OL_ASM1.Dynamic.ObjEval.Exp.xml'
generation = 200
#Real data
real = pd.read_csv(folder+"/path/to/RealData.csv")
#Param
param_eind = pd.read_csv(folder+"/Path/to/patameters.csv", header=None)

# Relevant inputs for the model
inputs = [0.96835528545816, 0.142986647789243, 0, 0.534423211974549, 0.768241598357242, 1, 0.431242981325574, 0.000764284049311295, 0.960183985023809, 0.342508146329742, 0.00324987920021324, 0.806062112627477, 1.25786423845298, 0.147764900619868]

#Objective function
def objective_func(ts1, ts2, w1 = 0.1, w2 = 1.0):
    # Ensure both time series have the same length
    if len(ts1) != len(ts2):
        raise ValueError("Time series must have the same length")
    # 1. Distance Component (Mean Squared Error)
    distance = np.mean((ts1 - ts2) ** 2)
    # 3. Average Value Alignment Component
    avg_alignment = abs(np.mean(ts1) - np.mean(ts2))
    # Final reward function (negative of the loss)
    return -(w1 * distance + w2 * avg_alignment)

# Individual tested for each parameter set
def eval_genome(genome, config):
    net = neat.nn.FeedForwardNetwork.create(genome, config)
    output = net.activate(inputs)
    #Load parameters
    var_list = []
    m = 0
    for index, row in param_eind.iterrows():
        var_list.append([row[0],round(row[1]+(int((output[m]+1)/2 * int(round((row[2] - row[1]) / row[3],0)))*row[3]),row[4])])
        m += 1
    
    #Check individual file☺
    if not os.path.exists(scenarios+"scen"+str(genome.key)):
        shutil.copytree(scenarios+"scen", scenarios+"scen"+str(genome.key)) 
    
    current_folder = scenarios+"scen"+str(genome.key)
    current_file = scenarios+"scen"+str(genome.key)+"/"+filename
    #Rewrite xml
    tree = etxml.parse(current_file)
    root = tree.getroot()
    Tag=root[0][1][0][0][1][0][0]
    for name in var_list:
        for q in Tag.iter('Quantity'): # check every element if it has the same name as the parameter name
            parnameinfile=q.get('Name') 
            if parnameinfile.endswith(name[0]):
                q.set('Value',str(name[1])) # in the xml the values need to be put as string

    tree.write(current_file)#, encoding='UTF-8', xml_declaration=True)
    
    #Rewrite run file
    with open(current_folder+"/run.bat", "rt") as bat_file:
        text = bat_file.readlines()

    new_text = []
    for line in text:
        if filename in line:
            new_text.append('texec "'+current_folder+'/BSM1_OL_ASM1.Dynamic.ObjEval.Exp.xml"\n')
        elif "TITLE" in line:
            new_text.append('TITLE window'+str(genome.key)+'\n')
        else:
            new_text.append(line)
            
    with open(current_folder+"/run.bat", "wt") as bat_file:
        for line in new_text:
            bat_file.write(line)
    
    #Execute run file
    # , creationflags=subprocess.CREATE_NEW_CONSOLE
    t = time.time()
    shell_process = subprocess.Popen(current_folder+"/run.bat")

    while (shell_process.poll() is None) and ((time.time() - t) < 330):
        time.sleep(1)
    
    try:
        if shell_process.poll() is None:
            parent = psutil.Process(shell_process.pid)
            for child in parent.children(recursive=True):
                child.kill()
            parent.kill()
    except:
        time.sleep(0.1)
        if shell_process.poll() is None:
            parent = psutil.Process(shell_process.pid)
            for child in parent.children(recursive=True):
                child.kill()
            parent.kill()
    
    if os.path.isfile(current_folder+"/Output_Mod.txt"):
        sim = pd.read_csv(current_folder+"/Output_Mod.txt", sep="\t")
        sim.drop(0, inplace=True, axis=0)
        sim.drop('#.t', inplace=True, axis=1)
        sim = sim.astype(float)
        print(len(sim))
        # Create a common time grid based on the minimum and maximum of all time series
        common_time = np.linspace(start=max(real.index.min(), sim.index.min()),
                                  stop=min(real.index.max(), sim.index.max()), num=1000)
        
        # Interpolating the data for each file using numpy.interp
        signal1 = pd.DataFrame(index=common_time)
        signal2 = pd.DataFrame(index=common_time)

        for col in real.columns:
            signal1[col] = np.interp(common_time, real.index, real[col])
            signal2[col] = np.interp(common_time, sim.index, sim[col])
        
        fitness = []
        for i, column in enumerate(signal1.columns):
            fitness.append(objective_func(signal1[col], signal2[col]))
            
        return_val = sum(fitness)

    else:
        return_val =  -99999
    
    try:
        time.sleep(0.1)
        shutil.rmtree(current_folder)
    except:
        time.sleep(0.2)
        shutil.rmtree(current_folder)
    return return_val

#ESNEAT run Function
def run(config_file):
    config = neat.Config(neat.DefaultGenome, neat.DefaultReproduction,
                         neat.DefaultSpeciesSet, neat.DefaultStagnation,
                         config_file)
    #Restore checkpoint
    #p = neat.Checkpointer.restore_checkpoint('neat-checkpoint-57')
    #Excecute
    p = neat.Population(config)
    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)
    p.add_reporter(neat.Checkpointer(1))

    pe = neat.ParallelEvaluator(10, eval_genome)
    winner = p.run(pe.evaluate, generation)

    winner_net = neat.nn.FeedForwardNetwork.create(winner, config)
    output = winner_net.activate(inputs)

    var_list = []
    m = 0
    for index, row in param_eind.iterrows():
        var_list.append([row[0],round(row[1]+(int((output[m]+1)/2 * int(round((row[2] - row[1]) / row[3],0)))*row[3]),row[4])])
        m += 1
    
    #Check individual file
    if not os.path.exists(scenarios+"scen"+"Final"):
        shutil.copytree(scenarios+"scen", scenarios+"scen"+"Final") 
    
    current_folder = scenarios+"scen"+"Final"
    current_file = scenarios+"scen"+"Final"+"/"+filename
    
    with open(current_folder+"/paramFinal.txt", 'w') as f:
        for line in var_list:
            f.write(f"{line}\n")
    
    tree = etxml.parse(current_file)
    root = tree.getroot()
    Tag=root[0][1][0][0][1][0][0]
    for name in var_list:
        for q in Tag.iter('Quantity'): # check every element if it has the same name as the parameter name
            parnameinfile=q.get('Name') 
            if parnameinfile.endswith(name[0]):
                q.set('Value',str(name[1])) # in the xml the values need to be put as string
                
    tree.write(current_file)#, encoding='UTF-8', xml_declaration=True)
    
    #Rewrite run file
    with open(current_folder+"/run.bat", "rt") as bat_file:
        text = bat_file.readlines()

    new_text = []
    for line in text:
        if filename in line:
            new_text.append('texec "'+current_folder+'/BSM1_OL_ASM1.Dynamic.ObjEval.Exp.xml"\n')
        elif "TITLE" in line:
            new_text.append('TITLE window'+"Final"+'\n')
        else:
            new_text.append(line)
            
    with open(current_folder+"/run.bat", "wt") as bat_file:
        for line in new_text:
            bat_file.write(line)
    
    #Execute run file
    t = time.time()
    shell_process = subprocess.Popen(current_folder+"/run.bat")

    while (shell_process.poll() is None) and ((time.time() - t) < 330):
        time.sleep(1)

    #Close window if still running
    try:
        if shell_process.poll() is None:
            parent = psutil.Process(shell_process.pid)
            for child in parent.children(recursive=True):
                child.kill()
            parent.kill()
    except:
        time.sleep(0.1)
        if shell_process.poll() is None:
            parent = psutil.Process(shell_process.pid)
            for child in parent.children(recursive=True):
                child.kill()
            parent.kill() 
     
    if os.path.isfile(current_folder+"/Output_Mod.txt"):
        sim = pd.read_csv(current_folder+"/Output_Mod.txt", sep="\t")
        sim.drop(0, inplace=True, axis=0)
        sim.drop('#.t', inplace=True, axis=1)
        sim = sim.astype(float)
        #Delete first 2 days during dynamic adjust
        
        # Create a common time grid based on the minimum and maximum of all time series
        common_time = np.linspace(start=max(real.index.min(), sim.index.min()),
                                  stop=min(real.index.max(), sim.index.max()), num=1000)
        
        # Interpolating the data for each file using numpy.interp
        signal1 = pd.DataFrame(index=common_time)
        signal2 = pd.DataFrame(index=common_time)

        for col in real.columns:
            signal1[col] = np.interp(common_time, real.index, real[col])
            signal2[col] = np.interp(common_time, sim.index, sim[col])
        
        fitness = []
        for i, column in enumerate(signal1.columns):
            fitness.append(objective_func(signal1[col], signal2[col]))
            
        return_val = sum(fitness)
        print(f"Reward (R): {return_val}")
        for i, column in enumerate(real.columns):

            plt.figure(figsize=(10, 6))

            # Calculate the RMSE
            rmse1 = round(np.sqrt(np.mean((signal1[column] - signal2[column]) ** 2)),2)
            
            plt.plot(signal2.index, signal2[column], label=f'Real - {column}', linestyle='-', color='blue')
            plt.plot(signal1.index, signal1[column], label=f'Manual - {column} - RMSE:{rmse1}', linestyle='--', color='orange')
            
            plt.title(f'Comparison of {column}')
            plt.xlabel('Index')
            plt.ylabel(f'{column}')
            plt.legend(loc='best')
            plt.grid(True)
            plt.savefig(current_folder+'/RealVsSim_'+column+'.png')
            plt.show()
    else:
        raise ValueError("%s isn't a file!" % current_folder+"/Output_Mod.txt")
    
if __name__ == '__main__':
    config_path =folder+'/config-feedforward.txt'
    run(config_path)
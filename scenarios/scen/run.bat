TITLE ventana
SET INCLUDE=%INCLUDE%;C:\Program Files (x86)\DHI\WEST\2023\include
SET LIB=%LIB%;C:\Program Files (x86)\DHI\WEST\2023\lib\win32-msvc
SET PATH=C:\Program Files (x86)\DHI\WEST\2023\bin\x64;C:\Program Files (x86)\DHI\WEST\2023\bin;%PATH%
SET TORNADO_CC_PLATFORM=win32-msvc
SET TORNADO_CC_PATH=
SET TORNADO_DATA_PATH=C:\Users\Public\Documents\DHI\WEST\2023
SET TORNADO_ROOT_PATH=C:\Program Files (x86)\DHI\WEST\2023
SET OPENMODELICAHOME=C:\Program Files (x86)\DHI\WEST\2023\third_party\omc
texec -l /min "log.log" "Eindhoven.Dynamic.ObjEval.Exp.xml"
  break>"blank.txt"
EXIT
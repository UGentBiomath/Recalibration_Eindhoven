#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <float.h>

#include "Tornado/Common/Util/DLL.h"
#include "Tornado/Common/MSLE/MSLE.h"

#include "Tornado/ME/MSLU/MSLU.h"




#define f_S_A pModel->Params[0]
#define f_S_F pModel->Params[1]
#define F_VSS_TSS pModel->Params[2]
#define f_X_S pModel->Params[3]
#define S_ALK_In pModel->Params[4]
#define S_Al_In pModel->Params[5]
#define S_N2_In pModel->Params[6]
#define S_NO_In pModel->Params[7]
#define S_O_In pModel->Params[8]
#define X_AUT_In pModel->Params[9]
#define X_H_In pModel->Params[10]
#define X_MEOH_In pModel->Params[11]
#define X_MEP_In pModel->Params[12]
#define X_PAO_In pModel->Params[13]
#define X_PHA_In pModel->Params[14]
#define X_PP_In pModel->Params[15]
#define _1_ pModel->Params[16]
#define WWTPSpecificVolume_1_1_1_ pModel->Params[17]
#define WWTPSpecificVolume_2_1_1_ pModel->Params[18]
#define WWTPSpecificVolume_3_1_1_ pModel->Params[19]
#define WWTPSpecificVolume_4_1_1_ pModel->Params[20]
#define WWTPSpecificVolume_5_1_1_ pModel->Params[21]
#define WWTPSpecificVolume_6_1_1_ pModel->Params[22]
#define WWTPSpecificVolume_7_1_1_ pModel->Params[23]
#define WWTPSpecificVolume_8_1_1_ pModel->Params[24]
#define WWTPSpecificVolume_9_1_1_ pModel->Params[25]
#define WWTPSpecificVolume_10_1_1_ pModel->Params[26]
#define WWTPSpecificVolume_11_1_1_ pModel->Params[27]
#define WWTPSpecificVolume_12_1_1_ pModel->Params[28]
#define WWTPSpecificVolume_13_1_1_ pModel->Params[29]
#define WWTPSpecificVolume_14_1_1_ pModel->Params[30]
#define WWTPSpecificVolume_15_1_1_ pModel->Params[31]
#define WWTPSpecificVolume_16_1_1_ pModel->Params[32]
#define WWTPSpecificVolume_17_1_1_ pModel->Params[33]
#define WWTPSpecificVolume_18_1_1_ pModel->Params[34]
#define WWTPSpecificVolume_19_1_1_ pModel->Params[35]
#define WWTPSpecificVolume_20_1_1_ pModel->Params[36]
#define WWTPSpecificVolume_21_1_1_ pModel->Params[37]
#define WWTPSpecificVolume_22_1_1_ pModel->Params[38]

#define t pModel->IndepVars[0]

#define Water pModel->InputVars[0]
#define Influent_Load_1_1_1_ pModel->OutputVars[0]
#define Influent_Load_2_1_1_ pModel->OutputVars[1]
#define Influent_Load_3_1_1_ pModel->OutputVars[2]
#define Influent_Load_4_1_1_ pModel->OutputVars[3]
#define Influent_Load_5_1_1_ pModel->OutputVars[4]
#define Influent_Load_6_1_1_ pModel->OutputVars[5]
#define Influent_Load_7_1_1_ pModel->OutputVars[6]
#define Influent_Load_8_1_1_ pModel->OutputVars[7]
#define Influent_Load_9_1_1_ pModel->OutputVars[8]
#define Influent_Load_10_1_1_ pModel->OutputVars[9]
#define Influent_Load_11_1_1_ pModel->OutputVars[10]
#define Influent_Load_12_1_1_ pModel->OutputVars[11]
#define Influent_Load_13_1_1_ pModel->OutputVars[12]
#define Influent_Load_14_1_1_ pModel->OutputVars[13]
#define Influent_Load_15_1_1_ pModel->OutputVars[14]
#define Influent_Load_16_1_1_ pModel->OutputVars[15]
#define Influent_Load_17_1_1_ pModel->OutputVars[16]
#define Influent_Load_18_1_1_ pModel->OutputVars[17]
#define Influent_Load_19_1_1_ pModel->OutputVars[18]
#define Influent_Load_20_1_1_ pModel->OutputVars[19]
#define Influent_Load_21_1_1_ pModel->OutputVars[20]
#define Influent_Load_22_1_1_ pModel->OutputVars[21]
#define CODs pModel->InputVars[1]
#define PO pModel->InputVars[2]
#define NH pModel->InputVars[3]
#define CODt pModel->InputVars[4]
#define TSS pModel->InputVars[5]

#define Inflow_1_1_1_ pModel->AlgVars[0]
#define Inflow_2_1_1_ pModel->AlgVars[1]
#define Inflow_3_1_1_ pModel->AlgVars[2]
#define Inflow_4_1_1_ pModel->AlgVars[3]
#define Inflow_5_1_1_ pModel->AlgVars[4]
#define Inflow_6_1_1_ pModel->AlgVars[5]
#define Inflow_7_1_1_ pModel->AlgVars[6]
#define Inflow_8_1_1_ pModel->AlgVars[7]
#define Inflow_9_1_1_ pModel->AlgVars[8]
#define Inflow_10_1_1_ pModel->AlgVars[9]
#define Inflow_11_1_1_ pModel->AlgVars[10]
#define Inflow_12_1_1_ pModel->AlgVars[11]
#define Inflow_13_1_1_ pModel->AlgVars[12]
#define Inflow_14_1_1_ pModel->AlgVars[13]
#define Inflow_15_1_1_ pModel->AlgVars[14]
#define Inflow_16_1_1_ pModel->AlgVars[15]
#define Inflow_17_1_1_ pModel->AlgVars[16]
#define Inflow_18_1_1_ pModel->AlgVars[17]
#define Inflow_19_1_1_ pModel->AlgVars[18]
#define Inflow_20_1_1_ pModel->AlgVars[19]
#define Inflow_21_1_1_ pModel->AlgVars[20]
#define Inflow_22_1_1_ pModel->AlgVars[21]
#define S_COD pModel->AlgVars[22]
#define X_COD pModel->AlgVars[23]
#define X_I_Help pModel->AlgVars[24]



#ifdef _WIN32
#ifndef _WIN32
#undef _SVID_SOURCE
#define _SVID_SOURCE

extern _LIB_VERSION_TYPE _LIB_VERSION;
#endif

int
#ifdef _WIN32
_matherr(struct _exception* except)
#else
matherr(struct exception* except)
#endif
{
  static char Buffer[1024];

  switch (except->type)
  {
#ifdef _MSC_VER
    case _DOMAIN:
#else
    case DOMAIN:
#endif
      sprintf(Buffer, "Argument domain error: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

#ifdef _MSC_VER
    case _SING:
#else
    case SING:
#endif
      sprintf(Buffer, "Argument singularity: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

#ifdef _MSC_VER
    case _OVERFLOW:
#else
    case OVERFLOW:
#endif
      sprintf(Buffer, "Overflow range error: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

#ifdef _MSC_VER
    case _PLOSS:
#else
    case PLOSS:
#endif
      sprintf(Buffer, "Partial loss of significance: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

#ifdef _MSC_VER
    case _TLOSS:
#else
    case TLOSS:
#endif
      sprintf(Buffer, "Total loss of significance: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

#ifdef _MSC_VER
    case _UNDERFLOW:
#else
    case UNDERFLOW:
#endif
      sprintf(Buffer, "The result is too small to be represented: %s(%g, %g)", except->name, except->arg1, except->arg2);
      break;

    default:
      sprintf(Buffer, "Unknown error type: %s(%g, %g)", except->name, except->arg1, except->arg2);
  }

  MSLUMessage(MSLU_ERROR, Buffer);

  return 1;
}
#endif


double
MSLUMessage2(struct TModel* pModel,
             size_t Type,
             const char* pMessage)
{
  MSLUMessage(Type, pMessage);
  if (Type == MSLU_ERROR)
    longjmp(pModel->JumpBuffer, 1);

  return 0;
}

#define MSLUMessage(Type, pMessage) MSLUMessage2(pModel, Type, pMessage)


char*
SetPath(const char* pPath)
{
  return MSLUSetPath(pPath);
}





int
ComputeInitial(struct TModel* pModel)
{
  MSLUConfigure(NULL, pModel->pCaller, pModel->pCallbackMessage, pModel->pCallbackTerminate, pModel->pCallbackGetStartTime, pModel->pCallbackGetStopTime, pModel->pCallbackSetGlobalValue, pModel->pCallbackGetGlobalValue, pModel->pCallbackSetGlobalVector, pModel->pCallbackGetGlobalVector);

  WWTPSpecificVolume_1_1_1_ = 1e-06;

  return 0;
}


int
ComputeState(struct TModel* pModel)
{
  Inflow_1_1_1_ = Water * (1);

  Influent_Load_1_1_1_ = - Inflow_1_1_1_ / WWTPSpecificVolume_1_1_1_;

  S_COD = CODs * (1);

  Inflow_2_1_1_ = S_COD * (1 - f_S_A - f_S_F);

  Influent_Load_2_1_1_ = - Inflow_2_1_1_ * Inflow_1_1_1_;

  Inflow_3_1_1_ = S_O_In * (1);

  Influent_Load_3_1_1_ = - Inflow_3_1_1_ * Inflow_1_1_1_;

  Inflow_4_1_1_ = S_N2_In * (1);

  Influent_Load_4_1_1_ = - Inflow_4_1_1_ * Inflow_1_1_1_;

  Inflow_5_1_1_ = S_COD * (f_S_F);

  Influent_Load_5_1_1_ = - Inflow_5_1_1_ * Inflow_1_1_1_;

  Inflow_6_1_1_ = S_COD * (f_S_A);

  Influent_Load_6_1_1_ = - Inflow_6_1_1_ * Inflow_1_1_1_;

  Inflow_7_1_1_ = S_Al_In * (1);

  Influent_Load_7_1_1_ = - Inflow_7_1_1_ * Inflow_1_1_1_;

  Inflow_8_1_1_ = S_NO_In * (1);

  Influent_Load_8_1_1_ = - Inflow_8_1_1_ * Inflow_1_1_1_;

  Inflow_9_1_1_ = PO * (1);

  Influent_Load_9_1_1_ = - Inflow_9_1_1_ * Inflow_1_1_1_;

  Inflow_10_1_1_ = NH * (1);

  Influent_Load_10_1_1_ = - Inflow_10_1_1_ * Inflow_1_1_1_;

  Inflow_11_1_1_ = S_ALK_In * (1);

  Influent_Load_11_1_1_ = - Inflow_11_1_1_ * Inflow_1_1_1_;

  Inflow_18_1_1_ = X_AUT_In * (1);

  Inflow_14_1_1_ = X_H_In * (1);

  Inflow_15_1_1_ = X_PAO_In * (1);

  Inflow_17_1_1_ = X_PHA_In * (1);

  X_COD = CODs * (- 1) + CODt * (1);

  Inflow_13_1_1_ = X_COD * (f_X_S);

  X_I_Help = Inflow_18_1_1_ * (- 1) + Inflow_14_1_1_ * (- 1) + Inflow_15_1_1_ * (- 1) + Inflow_17_1_1_ * (- 1) + Inflow_13_1_1_ * (- 1) + X_COD * (1);

  Inflow_12_1_1_ = X_I_Help * (( (X_I_Help <= 0) ? (0) : (1) ));

  Influent_Load_12_1_1_ = - Inflow_12_1_1_ * Inflow_1_1_1_;

  Influent_Load_13_1_1_ = - Inflow_13_1_1_ * Inflow_1_1_1_;

  Influent_Load_14_1_1_ = - Inflow_14_1_1_ * Inflow_1_1_1_;

  Influent_Load_15_1_1_ = - Inflow_15_1_1_ * Inflow_1_1_1_;

  Inflow_16_1_1_ = X_PP_In * (1);

  Influent_Load_16_1_1_ = - Inflow_16_1_1_ * Inflow_1_1_1_;

  Influent_Load_17_1_1_ = - Inflow_17_1_1_ * Inflow_1_1_1_;

  Influent_Load_18_1_1_ = - Inflow_18_1_1_ * Inflow_1_1_1_;

  Inflow_19_1_1_ = TSS * (1);

  Influent_Load_19_1_1_ = - Inflow_19_1_1_ * Inflow_1_1_1_;

  Inflow_20_1_1_ = X_MEOH_In * (1);

  Influent_Load_20_1_1_ = - Inflow_20_1_1_ * Inflow_1_1_1_;

  Inflow_21_1_1_ = X_MEP_In * (1);

  Influent_Load_21_1_1_ = - Inflow_21_1_1_ * Inflow_1_1_1_;

  Inflow_22_1_1_ = TSS * (1 - F_VSS_TSS);

  Influent_Load_22_1_1_ = - Inflow_22_1_1_ * Inflow_1_1_1_;


  return 0;
}


int
ComputeOutput(struct TModel* pModel)
{
  return 0;
}


int
ComputeFinal(struct TModel* pModel)
{
  return 0;
}


void*
GetID()
{
  return (void*)L"Tornado.MSLE.Model._Influent_in_";
}


void*
Create()
{
  struct TModel* pModel;

#ifndef _WIN32
  _LIB_VERSION = _SVID_;
#endif
  pModel = (struct TModel*)malloc(sizeof(struct TModel));
  memset(pModel, 0x0, sizeof(struct TModel));

  pModel->pVersion = wcsdup(L"2023 ");
  pModel->pType = wcsdup(L"ODE");

  pModel->NoParams = 39;
  pModel->NoIndepVars = 1;
  pModel->NoInputVars = 6;
  pModel->NoOutputVars = 22;
  pModel->NoAlgVars = 25;
  pModel->NoDerVars = 0;
  pModel->NoDerivatives = 0;
  pModel->NoPrevious = 0;
  pModel->NoResidues = 0;
  pModel->NoSolveSets = 0;
  pModel->NoEvents = 0;

  pModel->Params = (double*)malloc(sizeof(double) * pModel->NoParams);
  pModel->IndepVars = (double*)malloc(sizeof(double) * pModel->NoIndepVars);
  pModel->InputVars = (double*)malloc(sizeof(double) * pModel->NoInputVars);
  pModel->OutputVars = (double*)malloc(sizeof(double) * pModel->NoOutputVars);
  pModel->AlgVars = (double*)malloc(sizeof(double) * pModel->NoAlgVars);
  pModel->DerVars = (double*)malloc(sizeof(double) * pModel->NoDerVars);
  pModel->Derivatives = (double*)malloc(sizeof(double) * pModel->NoDerivatives);
  pModel->Previous = (double*)malloc(sizeof(double) * pModel->NoPrevious);
  pModel->Residues = (double*)malloc(sizeof(double) * pModel->NoResidues);
  pModel->SolveSets = (TSolveSetP)malloc(sizeof(struct TSolveSet) * pModel->NoSolveSets);
  pModel->Events = (TEventP)malloc(sizeof(struct TEvent) * pModel->NoEvents);

  pModel->ComputeInitial = ComputeInitial;
  pModel->ComputeState = ComputeState;
  pModel->ComputeOutput = ComputeOutput;
  pModel->ComputeFinal = ComputeFinal;

  return (void*)pModel;
}


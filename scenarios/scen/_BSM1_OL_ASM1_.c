#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <float.h>

#include "Tornado/Common/Util/DLL.h"
#include "Tornado/Common/MSLE/MSLE.h"

#include "Tornado/ME/MSLU/MSLU.h"





#define t pModel->IndepVars[0]





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


  return 0;
}


int
ComputeState(struct TModel* pModel)
{

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
  MSLUBufferRemoveAll();
  MSLUMarkovRemoveAll();
  MSLUMatrixRemoveAll();
  MSLUPhreeqcRemoveAll();
  MSLURandRemoveAll();
  MSLUTimerRemoveAll();
  return 0;
}


void*
GetID()
{
  return (void*)L"Tornado.MSLE.Model._BSM1_OL_ASM1_";
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

  pModel->NoParams = 0;
  pModel->NoIndepVars = 1;
  pModel->NoInputVars = 0;
  pModel->NoOutputVars = 0;
  pModel->NoAlgVars = 0;
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


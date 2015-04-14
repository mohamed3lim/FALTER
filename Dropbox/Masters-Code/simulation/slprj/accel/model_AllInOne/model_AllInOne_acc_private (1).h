#include "__cf_model_AllInOne.h"
#ifndef RTW_HEADER_model_AllInOne_acc_private_h_
#define RTW_HEADER_model_AllInOne_acc_private_h_
#include "rtwtypes.h"
#ifndef RTW_COMMON_DEFINES_
#define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else
#ifndef RTWTYPES_ID_C08S16I32L64N64F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
extern real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern real_T
rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern void
rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( const real_T u0 [ 3 ] , const real_T u1
[ 9 ] , real_T y [ 3 ] ) ; boolean_T
model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T *
tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * *
tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf ,
boolean_T istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
model_AllInOne_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart
, real_T * tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T
oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; void
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Enable ( SimStruct *
const S ) ; void
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Disable ( SimStruct *
const S ) ; void model_AllInOne_Forwallsthataretofartake0asdistancevalue (
const real_T rtu_0 [ 9 ] ,
B_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T * localB ) ; void
model_AllInOne_nobox_Enable ( SimStruct * const S ) ; void
model_AllInOne_nobox_Disable ( SimStruct * const S ) ; void
model_AllInOne_nobox ( const real_T rtu_0 [ 54 ] , real_T rty_no_box [ 54 ] )
; void model_AllInOne_NoBO_Enable ( SimStruct * const S ) ; void
model_AllInOne_NoBO_Disable ( SimStruct * const S ) ; void
model_AllInOne_NoBO ( real_T rtu_0 , real_T * rty_bo ) ; void
model_AllInOne_BO_Enable ( SimStruct * const S ) ; void
model_AllInOne_BO_Disable ( SimStruct * const S ) ; void
model_AllInOne_BO_Update ( SimStruct * const S , B_BO_model_AllInOne_T *
localB , DW_BO_model_AllInOne_T * localDW , P_BO_model_AllInOne_T * localP )
; void model_AllInOne_BO ( SimStruct * const S , real_T * rty_bo ,
B_BO_model_AllInOne_T * localB , DW_BO_model_AllInOne_T * localDW ,
P_BO_model_AllInOne_T * localP ) ;
#endif

#ifndef FALTER_SHAREDMEMORY_SFUNCTION_H
#define FALTER_SHAREDMEMORY_SFUNCTION_H

#include <uav_environment.h>
#include <position_motion.h>
#include <pmd_data.h>
#include <ctrl_ref.h>

#ifdef SHAREDMEMORY_SFUNCTION

    #define NUM_OUTPUT              6

    #define OUTPUT_FLAGS            0
    #define OUTPUT_POSITIONDATA     1
    #define OUTPUT_UAVENV           2
    #define OUTPUT_ERRORS           3
    #define OUTPUT_PMD              4
	#define OUTPUT_CTRLREF			5

#endif
        
#ifdef S_FUNCTION_NAME
    #define FALTER_SHAREDMEMORY_SFUNCTION_EXTERN 
        
    #define SHAREDMEMORY() const uint32_T* p;\
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_FLAGS);\
    flags =  (int *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_POSITION);\
    sharedData =  (struct MotionAndAlignment *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_UAVENV);\
    uavEnv =  (struct UavEnv *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_ERRORS);\
    errors =  (unsigned long *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_CTRL_REF);\
    sharedCtrlRef =  (struct CtrlRef *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);

    #define SHAREDMEMORY_PERCEPTION() const uint32_T* p;\
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_FLAGS);\
    flags =  (int *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_POSITION);\
    sharedData =  (struct MotionAndAlignment *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_UAVENV);\
    uavEnv =  (struct UavEnv *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);\
    \
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_ERRORS);\
    errors =  (unsigned long *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);

    #define SHAREDMEMORY_PARTICLE() const uint32_T* p;\
    p = (const uint32_T*)ssGetInputPortSignal(S,INPUT_PMD_DATA);\
    pmdData =  (struct PmdData *)(((unsigned long)p[1])*0xFFFFFFFF + p[0]);
    
    #define SHAREDMEMORY_PMD()  SHAREDMEMORY_PARTICLE()

#else
    #define FALTER_SHAREDMEMORY_SFUNCTION_EXTERN extern
#endif

/** 
 * SHARED MEMORY
 **/
        
/**
 * sharedFlags is used in org.fortiss.falter.datacom/obstacles_notification.c
 */
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN int* flags;

/**
 * sharedPositionData is used in org.fortiss.falter.datacom/position.c
 **/
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN struct MotionAndAlignment* sharedData;

/**
 * sharedUavEnv is used in org.fortiss.falter.datacom/uav_environment.c
 **/
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN struct UavEnv* uavEnv;

/**
 * Used in org.fortiss.falter.datacom/error_notification.c
 **/
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN unsigned long* errors;

/**
 * Used in org.fortiss.falter.datacom/pmd_data.c
 **/
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN struct PmdData* pmdData;

/**
 * Used in org.fortiss.falter.datacom/ctrl_ref.c
 **/
FALTER_SHAREDMEMORY_SFUNCTION_EXTERN struct CtrlRef* sharedCtrlRef;

#endif /* FALTER_SHAREDMEMORY_SFUNCTION_H */

/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 *  -------------------------------------------------------------------------
 *  | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  -------------------------------------------------------------------------
 *
 * Copyright 1990-2002 The MathWorks, Inc.
 * $Revision: 1.27.4.1 $
 */

/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  falter_sharedMemory_sfunction
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "falter_sharedMemory_sfunction.h"
#include <math.h>

/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 * See matlabroot/simulink/src/sfuntmpl_doc.c for more details.
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* See sfuntmpl_doc.c for more details on the macros below */

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 0)) return;
    
    /* OUTPUT ports */
    
    if (!ssSetNumOutputPorts(S, NUM_OUTPUT)) return;

    /**
     * All output ports are pointers. They can be 64bit pointers so we need
     * 64bit (2 * 32bit) wide output signals.
     **/
    int i;
    for( i=0; i < NUM_OUTPUT; i++) {
        ssSetOutputPortWidth(S, i, 2);
        ssSetOutputPortDataType(S, i, SS_UINT32);
    }
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, 0);
    
    ssSetNumDWork(S,NUM_OUTPUT);
    
    /* set all dwork vectors to length 1. They are all pointer and no arrays */
    for( i=0; i < NUM_OUTPUT; i++) {
        ssSetDWorkWidth(S,i,1);
    }
    
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    //TODO move to header file
    ssSetSampleTime(S, 0, 0.05);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {  
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
    int **flagsPointer = (int **)ssGetDWork(S,OUTPUT_FLAGS);
    *flagsPointer = (int *)malloc(sizeof(int));
    
    struct MotionAndAlignment **positionDataPointer = (struct MotionAndAlignment **)ssGetDWork(S,OUTPUT_POSITIONDATA);
    *positionDataPointer = (struct MotionAndAlignment *)malloc(sizeof(struct MotionAndAlignment));
    (*positionDataPointer)->angleYaw = 0.0;
    (*positionDataPointer)->recalibratedAltitude = 120;
    (*positionDataPointer)->recalibratedSpeedZ = 0;
    (*positionDataPointer)->speedX = 0;
    (*positionDataPointer)->speedY = 0;
    (*positionDataPointer)->speedZ = 0;

    //position in mm; lookout: different starting positions for simulation and global convention
    (*positionDataPointer)->altitude = 120;
    (*positionDataPointer)->positionX = -23000;
    (*positionDataPointer)->positionY = 4000;


    
    struct UavEnv **uavEnvPointer = (struct UavEnv **)ssGetDWork(S,OUTPUT_UAVENV);
    *uavEnvPointer = (struct UavEnv *)malloc(sizeof(struct UavEnv));

    unsigned long **errorsPointer = (unsigned long **)ssGetDWork(S,OUTPUT_ERRORS);
    *errorsPointer = (unsigned long *) malloc(sizeof(unsigned long));
    
    struct PmdData **pmdPointer = (struct PmdData **)ssGetDWork(S,OUTPUT_PMD);
    *pmdPointer = (struct PmdData *) malloc(sizeof(struct PmdData));
    
    struct CtrlRef **ctrlRefPointer = (struct CtrlRef **)ssGetDWork(S,OUTPUT_CTRLREF);
	*ctrlRefPointer = (struct CtrlRef *) malloc(sizeof(struct CtrlRef));
	(*ctrlRefPointer)->flightMode = CTRLREF_STARTING;
	(*ctrlRefPointer)->altitude = 0;
	(*ctrlRefPointer)->motorStatus = CTRLREF_MOTORS_OFF;
	(*ctrlRefPointer)->fmInitialized = FLIGHT_MANAGER_NOT_INITIALIZED;

  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{   
    uint32_T p1;
    uint32_T p2;
    /**
     * we don't know the size of the pointer (hopefully it's 32bit or 64bit)
     * so we split it into two ints with a size of 32bit. There is no 64bit
     * data type in Matlab
     **/
    int **flagsPointer = (int **)ssGetDWork(S,OUTPUT_FLAGS);
    flags = *flagsPointer;
    p1 = ((unsigned long)flags % 0xFFFFFFFF);
    p2 = ((unsigned long)flags / 0xFFFFFFFF);
        
    /* Pass pointer as output */
    uint32_T *output_flags = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_FLAGS);
    output_flags[0] = p1;
    output_flags[1] = p2;
    
    struct MotionAndAlignment **positionDataPointer = (struct MotionAndAlignment **)ssGetDWork(S,OUTPUT_POSITIONDATA);
    sharedData = *positionDataPointer;
    p1 = ((unsigned long)sharedData % 0xFFFFFFFF);
    p2 = ((unsigned long)sharedData / 0xFFFFFFFF);
        
    /* Pass pointer as output */
    uint32_T *output_positionData = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_POSITIONDATA);
    output_positionData[0] = p1;
    output_positionData[1] = p2;
    
    
    struct UavEnv **uavEnvPointer = (struct UavEnv **)ssGetDWork(S,OUTPUT_UAVENV);
    uavEnv = *uavEnvPointer;
    p1 = ((unsigned long)uavEnv % 0xFFFFFFFF);
    p2 = ((unsigned long)uavEnv / 0xFFFFFFFF);
        
    /* Pass pointer as output */
    uint32_T *output_uavEnv = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_UAVENV);
    output_uavEnv[0] = p1;
    output_uavEnv[1] = p2;
    
    unsigned long **errorsPointer = (unsigned long **)ssGetDWork(S,OUTPUT_ERRORS);
    errors = *errorsPointer;
    p1 = ((unsigned long)errors % 0xFFFFFFFF);
    p2 = ((unsigned long)errors / 0xFFFFFFFF);
        
    /* Pass pointer as output */
    uint32_T *output_errors = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_ERRORS);
    output_errors[0] = p1;
    output_errors[1] = p2;
    
    struct PmdData **pmdPointer = (struct PmdData **)ssGetDWork(S,OUTPUT_PMD);
    pmdData = *pmdPointer;
    p1 = ((unsigned long)pmdData % 0xFFFFFFFF);
    p2 = ((unsigned long)pmdData / 0xFFFFFFFF);
        
    /* Pass pointer as output */
    uint32_T *output_pmd = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_PMD);
    output_pmd[0] = p1;
    output_pmd[1] = p2;
    
    struct CtrlRef **ctrlRefPointer = (struct CtrlRef **)ssGetDWork(S,OUTPUT_CTRLREF);
    sharedCtrlRef = *ctrlRefPointer;
	p1 = ((unsigned long)sharedCtrlRef % 0xFFFFFFFF);
	p2 = ((unsigned long)sharedCtrlRef / 0xFFFFFFFF);

	/* Pass pointer as output */
	uint32_T *output_ctrRef = (uint32_T *)ssGetOutputPortSignal(S,OUTPUT_CTRLREF);
	output_ctrRef[0] = p1;
	output_ctrRef[1] = p2;

}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}

/*======================================================*
 * See sfuntmpl_doc.c for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

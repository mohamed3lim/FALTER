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

#define S_FUNCTION_NAME  falter_perception_sfunction
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "variables_perception.h"
#include "falter_sharedMemory_sfunction.h"

extern int perception_init();
extern void perceptionStep();

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

    if (!ssSetNumInputPorts(S, NUM_INPUT)) return;
    
    /* counter for all input ports */
    int i = 0;
    
    /* SRF08 input ports setup */
    for ( i = INPUT_SRF_GND; i < INPUT_SRF_GND + INPUT_SRF_NUM; i++ ) {
        /* set width of input vector */
        ssSetInputPortWidth(S, i, INPUT_SRF_WIDTH);
        
        /* set datatype to double */
        ssSetInputPortDataType(S, i, SS_DOUBLE);
    }
    
    /* ADC */
    ssSetInputPortWidth(S, INPUT_ADC, INPUT_ADC_WIDTH);
    ssSetInputPortDataType(S, INPUT_ADC, SS_UINT32);
    
    /* SHARED MEMORY */
    /* obstacle flags */
    ssSetInputPortWidth(S, INPUT_FLAGS, 2);
    ssSetInputPortDataType(S, INPUT_FLAGS, SS_UINT32);
    /* obstacle flags */
    ssSetInputPortWidth(S, INPUT_POSITION, 2);
    ssSetInputPortDataType(S, INPUT_POSITION, SS_UINT32);
    /* uav env */
    ssSetInputPortWidth(S, INPUT_UAVENV, 2);
    ssSetInputPortDataType(S, INPUT_UAVENV, SS_UINT32);
    /* errors */
    ssSetInputPortWidth(S, INPUT_ERRORS, 2);
    ssSetInputPortDataType(S, INPUT_ERRORS, SS_UINT32);
    
    /* general settings for input ports */
    for ( i=0; i < NUM_INPUT; i++) {
        /*direct input signal access*/
        ssSetInputPortRequiredContiguous(S, i, true);
        /*
        * Set direct feedthrough flag (1=yes, 0=no).
        * A port has direct feedthrough if the input is used in either
        * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
        * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
        */
        ssSetInputPortDirectFeedThrough(S, i, 1);
    }
    
    
    
    if (!ssSetNumOutputPorts(S, NUM_OUTPUT)) return;
    
    ssSetOutputPortMatrixDimensions(S, OUTPUT_UAVENV, OUTPUT_UAVENV_HEIGHT, OUTPUT_UAVENV_WIDTH);
    // The data type of an output port is double(real_t) by default - and thats perfectly fine here.
    

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, 0);
    
    ssSetNumDWork(S,1);
    ssSetDWorkWidth(S,0,1);
    
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.005);
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
    perception_init();
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{   
    input_srf_gnd = (const double *)ssGetInputPortSignal(S,INPUT_SRF_GND);
    input_srf_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_LHS);
    input_srf_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_RHS);
    input_srf_front_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_RHS);
    input_srf_front_ctr = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_CTR);
    input_srf_front_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_LHS);
    input_srf_rear = (const double *)ssGetInputPortSignal(S,INPUT_SRF_REAR);
    input_srf_ceiling = (const double *)ssGetInputPortSignal(S,INPUT_SRF_CEILING);
    
    input_ad = (const int *)ssGetInputPortSignal(S,INPUT_ADC);
    
    output_uavenv = (double*)ssGetOutputPortSignal(S,OUTPUT_UAVENV);
    
	if(ssIsSampleHit(S,0,tid)) { 
        sim_time = ssGetT(S);
    }
    
	SHAREDMEMORY_PERCEPTION();
    
    perceptionStep();
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

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

#define S_FUNCTION_NAME  control
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "variables_control.h"
//#include "variables_perception.h"

//#include "falter_sharedMemory_sfunction.h"

extern int ctrl_init();
extern void ctrl_step();

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

    /* ACC and GYRO input port setup */
    ssSetInputPortWidth(S, INPUT_ACC, INPUT_ACC_WIDTH);
    ssSetInputPortWidth(S, INPUT_GYRO, INPUT_GYRO_WIDTH);
    ssSetInputPortWidth(S, INPUT_GYRO_RATES, INPUT_GYRO_RATES_WIDTH);
    
    /* ADC */
    //TODO: exists in perception as well!
    /*Ground Sensor */
    ssSetInputPortWidth(S, INPUT_ADC, INPUT_ADC_WIDTH);
    ssSetInputPortDataType(S, INPUT_ADC, SS_UINT32);
    
    ssSetInputPortWidth(S, INPUT_Z_PID, 1);
    ssSetInputPortDataType(S, INPUT_Z_PID, SS_DOUBLE);
    
    /* set datatype to double (this is default) */
    //ssSetInputPortDataType(S, INPUT_ACC, SS_DOUBLE);
    //ssSetInputPortDataType(S, INPUT_GYRO, SS_DOUBLE);
    
    int i;
    
    /* SRF08 input ports setup */
    for ( i = INPUT_SRF_GND; i < INPUT_SRF_GND + INPUT_SRF_NUM; i++ ) {
        /* set width of input vector */
        ssSetInputPortWidth(S, i, INPUT_SRF_WIDTH);
        
        /* set datatype to double */
        ssSetInputPortDataType(S, i, SS_DOUBLE);
    }
    
//     ssSetInputPortWidth(S, INPUT_SRF_GND, INPUT_SRF_WIDTH);
//     ssSetInputPortDataType(S, INPUT_SRF_GND, SS_DOUBLE);
    
    /* shared memory */
    /* obstacle flags */
    ssSetInputPortWidth(S, INPUT_YAW_PID, 1);
    ssSetInputPortDataType(S, INPUT_YAW_PID, SS_DOUBLE);
    
    ssSetInputPortWidth(S, INPUT_X_PID, 1);
    ssSetInputPortDataType(S, INPUT_X_PID, SS_DOUBLE);

    ssSetInputPortWidth(S, INPUT_Y_PID, 1);
    ssSetInputPortDataType(S, INPUT_Y_PID, SS_DOUBLE);
    
    /* obstacle flags */
//     ssSetInputPortWidth(S, INPUT_POSITION, 2);
//     ssSetInputPortDataType(S, INPUT_POSITION, SS_UINT32);
//     /* uav env */
//     ssSetInputPortWidth(S, INPUT_UAVENV, 2);
//     ssSetInputPortDataType(S, INPUT_UAVENV, SS_UINT32);
//     /* errors */
    ssSetInputPortWidth(S, INPUT_X_POSITION, 1);
    ssSetInputPortDataType(S, INPUT_X_POSITION, SS_DOUBLE);

    ssSetInputPortWidth(S, INPUT_Y_POSITION, 1);
    ssSetInputPortDataType(S, INPUT_Y_POSITION, SS_DOUBLE);
    
    ssSetInputPortWidth(S, INPUT_PMD, INPUT_PMD_WIDTH);
    ssSetInputPortDataType(S, INPUT_PMD, SS_SINGLE);
    
    /* MAGIC VELOCITY */
    ssSetInputPortWidth(S, INPUT_MAGIC_VELOCITY, INPUT_MAGIC_VELOCITY_WIDTH);
    
    /* QUATERNIONS */
    ssSetInputPortWidth(S, INPUT_QUATERNIONS, INPUT_QUATERNIONS_WIDTH);
    
    /* general settings for input ports */
    //int i;
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
    
    /* OUTPUT ports */
    
    if (!ssSetNumOutputPorts(S, NUM_OUTPUT)) return;
    
    ssSetOutputPortWidth(S, OUTPUT_LED, OUTPUT_LED_WIDTH);
    
    ssSetOutputPortWidth(S, OUTPUT_GAS, 1);
    ssSetOutputPortWidth(S, OUTPUT_YAW, 1);
    ssSetOutputPortWidth(S, OUTPUT_NICK, 1);
    ssSetOutputPortWidth(S, OUTPUT_ROLL, 1);
    
    ssSetOutputPortWidth(S, OUTPUT_INTERNAL_DATA, OUTPUT_INTERNAL_DATA_WIDTH);
    
    ssSetOutputPortWidth(S, OUTPUT_ROLL, 1);
    ssSetOutputPortWidth(S, OUTPUT_ELEVATION, 1);
    ssSetOutputPortWidth(S, OUTPUT_X, 1);
    ssSetOutputPortWidth(S, OUTPUT_Y, 1);
    ssSetOutputPortWidth(S, OUTPUT_DESIRED_YAW, 1);
    

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
    /* sample time in seconds */
    ssSetSampleTime(S, 0, 0.01);
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
	sim_time = 0;
    
    input_acc = (const double *)ssGetInputPortSignal(S,INPUT_ACC);
    input_gyro = (const double *)ssGetInputPortSignal(S,INPUT_GYRO);
    
    input_x_position = (const double *)ssGetInputPortSignal(S,INPUT_X_POSITION);
    input_y_position = (const double *)ssGetInputPortSignal(S,INPUT_Y_POSITION);
    
    input_magic_velocity = (const double *)ssGetInputPortSignal(S,INPUT_MAGIC_VELOCITY);
    
    input_quaternions = (const double *)ssGetInputPortSignal(S,INPUT_QUATERNIONS);
    
    input_gyro_rates = (const double *)ssGetInputPortSignal(S,INPUT_GYRO_RATES);
    
    input_ad = (const int *)ssGetInputPortSignal(S,INPUT_ADC);
    
    srf_gnd = (const double *)ssGetInputPortSignal(S,INPUT_SRF_GND);
    srf_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_LHS);
    srf_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_RHS);
    srf_front_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_RHS);
    srf_front_ctr = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_CTR);
    srf_front_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_LHS);
    srf_rear = (const double *)ssGetInputPortSignal(S,INPUT_SRF_REAR);
    srf_ceiling = (const double *)ssGetInputPortSignal(S,INPUT_SRF_CEILING);
    
    input_z_pid = (const double *)ssGetInputPortSignal(S,INPUT_Z_PID);
    input_yaw_pid = (const double *)ssGetInputPortSignal(S,INPUT_YAW_PID);
    
    input_x_pid = (const double *)ssGetInputPortSignal(S,INPUT_X_PID);
    input_y_pid = (const double *)ssGetInputPortSignal(S,INPUT_Y_PID);
    
    input_pmd = (const float *)ssGetInputPortSignal(S,INPUT_PMD);
    
// 	if(ssIsSampleHit(S,0,tid)) { 
//         sim_time = ssGetT(S);
//     }
    
    output_led = (double *)ssGetOutputPortSignal(S,OUTPUT_LED);
    output_gas = (double *)ssGetOutputPortSignal(S,OUTPUT_GAS);
    output_yaw = (double *)ssGetOutputPortSignal(S,OUTPUT_YAW);
    output_nick = (double *)ssGetOutputPortSignal(S,OUTPUT_NICK);
    output_roll = (double *)ssGetOutputPortSignal(S,OUTPUT_ROLL);
    
    output_elevation = (double *)ssGetOutputPortSignal(S,OUTPUT_ELEVATION);
    output_desired_yaw = (double *)ssGetOutputPortSignal(S,OUTPUT_DESIRED_YAW);
    
    output_x = (double *)ssGetOutputPortSignal(S,OUTPUT_X);
    output_y = (double *)ssGetOutputPortSignal(S,OUTPUT_Y);
    ctrl_init();
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
//     input_acc = (const double *)ssGetInputPortSignal(S,INPUT_ACC);
//     input_gyro = (const double *)ssGetInputPortSignal(S,INPUT_GYRO);
//     
//     input_magic_velocity = (const double *)ssGetInputPortSignal(S,INPUT_MAGIC_VELOCITY);
//     
//     input_quaternions = (const double *)ssGetInputPortSignal(S,INPUT_QUATERNIONS);
//     
//     input_gyro_rates = (const double *)ssGetInputPortSignal(S,INPUT_GYRO_RATES);
//     
//     input_ad = (const int *)ssGetInputPortSignal(S,INPUT_ADC);
//     
//     srf_gnd = (const double *)ssGetInputPortSignal(S,INPUT_SRF_GND);
//     srf_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_LHS);
//     srf_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_RHS);
//     srf_front_rhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_RHS);
//     srf_front_ctr = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_CTR);
//     srf_front_lhs = (const double *)ssGetInputPortSignal(S,INPUT_SRF_FRONT_LHS);
//     srf_rear = (const double *)ssGetInputPortSignal(S,INPUT_SRF_REAR);
//     srf_ceiling = (const double *)ssGetInputPortSignal(S,INPUT_SRF_CEILING);
//     
//     input_z_pid = (const double *)ssGetInputPortSignal(S,INPUT_Z_PID);
//     input_yaw_pid = (const double *)ssGetInputPortSignal(S,INPUT_YAW_PID);
//     
//     input_x_pid = (const double *)ssGetInputPortSignal(S,INPUT_X_PID);
//     input_y_pid = (const double *)ssGetInputPortSignal(S,INPUT_Y_PID);
//     
// 	if(ssIsSampleHit(S,0,tid)) { 
//         sim_time = ssGetT(S);
//     }
//     
//     output_led = (double *)ssGetOutputPortSignal(S,OUTPUT_LED);
//     output_gas = (double *)ssGetOutputPortSignal(S,OUTPUT_GAS);
//     output_yaw = (double *)ssGetOutputPortSignal(S,OUTPUT_YAW);
//     output_nick = (double *)ssGetOutputPortSignal(S,OUTPUT_NICK);
//     output_roll = (double *)ssGetOutputPortSignal(S,OUTPUT_ROLL);
//     
//     output_elevation = (double *)ssGetOutputPortSignal(S,OUTPUT_ELEVATION);
//     output_desired_yaw = (double *)ssGetOutputPortSignal(S,OUTPUT_DESIRED_YAW);
//     
//     output_x = (double *)ssGetOutputPortSignal(S,OUTPUT_X);
//     output_y = (double *)ssGetOutputPortSignal(S,OUTPUT_Y);
    
    //output_internalData = (double *)ssGetOutputPortSignal(S,OUTPUT_INTERNAL_DATA);
    

    
    /*const uint32_T* flagsPointer = (const uint32_T*)ssGetInputPortSignal(S,INPUT_FLAGS);
    flags =  (int *)(((unsigned long)flagsPointer[0])*0xFFFFFFFF + flagsPointer[1]);
    
    const uint32_T* positionPointer = (const uint32_T*)ssGetInputPortSignal(S,INPUT_POSITION);
    sharedPositionData =  (double *)(((unsigned long)positionPointer[0])*0xFFFFFFFF + positionPointer[1]);*/
    
    ctrl_step();
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

/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 *  -------------------------------------------------------------------------
 *  | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  -------------------------------------------------------------------------
 *
 * Copyright 1990-2002 The MathWorks, Inc.
 * $Revision: 1.27.4.2 $
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  minSensorResults
#define S_FUNCTION_LEVEL 2

#define SENSOR_WIDTH 17
#define SENSOR_MIN_DIFF 0.05

// Number of parameters
#define NUM_PARAMETERS  1

// Number of NUM_SENSORS parameter
#define PARAM_NUM_SENSORS 0


/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"


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
    
    /* Parameter  Ports */
    ssSetNumSFcnParams(S, NUM_PARAMETERS);/* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }
    
    double *num_sensors = mxGetPr(ssGetSFcnParam(S,PARAM_NUM_SENSORS));    

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortMatrixDimensions(S, 0, DYNAMICALLY_SIZED, DYNAMICALLY_SIZED);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, (*num_sensors) * SENSOR_WIDTH);
    
//    mexPrintf("NUM SENSORS: %f\n", (*num_sensors));

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S,
                 SS_OPTION_WORKS_WITH_CODE_REUSE);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);

}


#define MDL_SET_INPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_INPUT_PORT_DIMENSION_INFO)
  static void mdlSetInputPortDimensionInfo(SimStruct *S, int_T port, const DimsInfo_T *dimsInfo)
  {
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
  }
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
  static void mdlSetOutputPortDimensionInfo(SimStruct *S, int_T port, const DimsInfo_T *dimsInfo)
  {
    if(!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
  }
#endif /* MDL_SET_OUTPUT_PORT_DIMENSION_INFO */
          

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO)
void mdlSetDefaultPortDimensionInfo(SimStruct *S) {
        if(ssGetInputPortWidth(S, 0) == DYNAMICALLY_SIZED ) {
            double *num_sensors = mxGetPr(ssGetSFcnParam(S,PARAM_NUM_SENSORS));  
            ssSetInputPortMatrixDimensions(S, 0, 1, (*num_sensors) * SENSOR_WIDTH);
        }
    }
#endif /* MDL_SET_DEFAULT_PORT_DIMENSION_INFO */

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS)
  static void mdlSetWorkWidths(SimStruct *S)
  {
     ssSupportsMultipleExecInstances(S, 1);
  }
#endif /* MDL_SET_WORK_WIDTHS */

#undef MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
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



#undef MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */


int compare_real_T(const void *a, const void *b) {
    const real_T *da = (const real_T *) a;
    const real_T *db = (const real_T *) b;
    
    if( *da != *db ) {
        if( *da == 0 ) return 1;
        if( *db == 0 ) return -1;
    }
     
    return (*da > *db) - (*da < *db);
}



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    /* Parameters */
    int num_sensors = (int)(*((double*)mxGetPr(ssGetSFcnParam(S,PARAM_NUM_SENSORS))));    
    
    
    const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
    real_T       *y = ssGetOutputPortSignal(S,0);
    
    int_T uWidth = ssGetInputPortWidth(S,0);
    int_T yWidth = ssGetOutputPortWidth(S,0);
    
    //counter for distances
    int i;
    //number of walls
    int count = (uWidth/(num_sensors))/SENSOR_WIDTH;
    //counter for sensors
    int k;
    //counter for distances within a sensor result
    int d;
    //dist of last iteration
    double ld;
    //dist of current iteration
    double cd;
    
    //mexPrintf("walls: %d, num Sensors: %d\n", count, num_sensors);
    
    for (k = 0; k < num_sensors; k++){
        ld = 0;
        cd = 0;
        d = 0;
        int offsetU = k*SENSOR_WIDTH;
        //here one result set has the same amount of distances as there are measurement beams.
        int offsetY = k*SENSOR_WIDTH;
                
        qsort ((void*)(u + offsetU), SENSOR_WIDTH, sizeof(real_T), compare_real_T);
        for (i = 0; i < SENSOR_WIDTH; i++){
            cd = u[offsetU + i];
            if(cd - ld > SENSOR_MIN_DIFF){
                y[offsetY + d] = cd;
                //mexPrintf("y: %d\t", cd);
                d++;
            }
            
            ld = cd;
        }
        //mexPrintf("\n");
        
        for(; d < SENSOR_WIDTH; d++){
            y[offsetY + d] = 0;
        }
    }
}



#undef MDL_UPDATE  /* Change to #undef to remove function */
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



#undef MDL_DERIVATIVES  /* Change to #undef to remove function */
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

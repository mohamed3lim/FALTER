/* variables for falter_perception_sfunction */

#ifndef VARIABLES_PERCEPTION_H
#define VARIABLES_PERCEPTION_H

#include "simstruc.h"
#include <uav_environment.h>

/* Number of output ports */
#define NUM_OUTPUT              1

#define OUTPUT_UAVENV           0
#define OUTPUT_UAVENV_WIDTH     (2*UAV_ENV_RANGE_LONGIT+1)
#define OUTPUT_UAVENV_HEIGHT    (2*UAV_ENV_RANGE_LATERAL+1)


/** Number of input ports 
 *  0 - 7: SRF08
 **/

/* shared memory inputs */
#define INPUT_FLAGS             0
#define INPUT_POSITION          1
#define INPUT_UAVENV            2
#define INPUT_ERRORS            3


/* input port number and width of a SRF08 */
#define INPUT_SRF_NUM           8
#define INPUT_SRF_WIDTH        17

#define INPUT_SRF_GND           4
#define INPUT_SRF_LHS           5
#define INPUT_SRF_RHS           6
#define INPUT_SRF_FRONT_RHS     7
#define INPUT_SRF_FRONT_CTR     8
#define INPUT_SRF_FRONT_LHS     9
#define INPUT_SRF_REAR          10
#define INPUT_SRF_CEILING       11

#define INPUT_ADC               12
#define INPUT_ADC_WIDTH         8

// #ifdef LASER
// #define INPUT_LASER            13
// #define INPUT_LASER_WIDTH      683
// #endif

/* IPC, SRF08 input and FcData */
// #ifdef LASER
//     #define NUM_INPUT              14
// #else
#define NUM_INPUT              13
//#endif


#ifdef S_FUNCTION_NAME
    #define VARIABLES_PERCEPTION_EXTERN 
#else
    #define VARIABLES_PERCEPTION_EXTERN extern
#endif

/* SRF08 */
VARIABLES_PERCEPTION_EXTERN const double* input_srf_gnd;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_lhs;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_rhs;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_front_rhs;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_front_ctr;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_front_lhs;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_rear;
VARIABLES_PERCEPTION_EXTERN const double* input_srf_ceiling;

/* ADC */
VARIABLES_PERCEPTION_EXTERN const int* input_ad;

// /* LASER */
// #ifdef LASER
// VARIABLES_PERCEPTION_EXTERN const double* input_laser;
// #endif

/* Simulation time */
VARIABLES_PERCEPTION_EXTERN double sim_time;

/* UAV Environment output */
VARIABLES_PERCEPTION_EXTERN double* output_uavenv;

#endif /* VARIABLES_PERCEPTION_H */

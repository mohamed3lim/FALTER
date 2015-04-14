/* variables for falter_control_sfunction */

#ifndef VARIABLES_CONTROL_H
#define VARIABLES_CONTROL_H

#include "simstruc.h"
#warning stop


/* output port number and width of the LED */
#define OUTPUT_LED              0
#define OUTPUT_LED_WIDTH        1

#define OUTPUT_GAS              1

#define OUTPUT_YAW              2

#define OUTPUT_NICK             3

#define OUTPUT_ROLL             4

#define OUTPUT_INTERNAL_DATA    5

#define OUTPUT_ELEVATION        6
#define OUTPUT_DESIRED_YAW      7
#define OUTPUT_X                8
#define OUTPUT_Y                9

#define OUTPUT_INTERNAL_DATA_WIDTH	20

/* Number of output ports */
#define NUM_OUTPUT              10


/** Number of input ports 
 *  0 - 7: SRF08
 **/

/* IPC inputs */
// #define INPUT_FLAGS             0
// 
// 
// #define INPUT_POSITION          1
// #define INPUT_UAVENV            2

#define INPUT_YAW_PID           0
#define INPUT_X_PID             1
#define INPUT_Y_PID             2

#define INPUT_X_POSITION        3
#define INPUT_Y_POSITION        4

#define INPUT_ACC               5
#define INPUT_ACC_WIDTH         3

#define INPUT_GYRO              6   
#define INPUT_GYRO_WIDTH        1

#define INPUT_GYRO_RATES        7
#define INPUT_GYRO_RATES_WIDTH  3

#define INPUT_MAGIC_VELOCITY             8
#define INPUT_MAGIC_VELOCITY_WIDTH       3

#define INPUT_QUATERNIONS             9
#define INPUT_QUATERNIONS_WIDTH       4

#define INPUT_ADC                    10
#define INPUT_ADC_WIDTH              8


/* IPC, SRF08 input and FcData */
#define NUM_INPUT               21

#define INPUT_SRF_GND           11
#define INPUT_SRF_LHS           12
#define INPUT_SRF_RHS           13
#define INPUT_SRF_FRONT_RHS     14
#define INPUT_SRF_FRONT_CTR     15
#define INPUT_SRF_FRONT_LHS     16
#define INPUT_SRF_REAR          17
#define INPUT_SRF_CEILING       18  
#define INPUT_Z_PID             19

#define INPUT_SRF_WIDTH        17
#define INPUT_SRF_NUM           8

#define INPUT_PMD                 20
// #define PMD_RES_WIDTH             3  
// #define PMD_RES_HEIGHT            4 
#define PMD_RES_HEIGHT            32
#define PMD_RES_WIDTH             24    
#define INPUT_PMD_WIDTH           (PMD_RES_WIDTH * PMD_RES_HEIGHT)
// #define INPUT_PMD_WIDTH           (48 * 64) //// check this one!

#ifdef S_FUNCTION_NAME
    #define SFUNCTION_EXTERN 
#else
    #define SFUNCTION_EXTERN extern
#endif

/* INPUT */
/* IPC */
SFUNCTION_EXTERN const unsigned long* input_errors;

/* FCSERIAL DATA */
SFUNCTION_EXTERN const double* input_acc;
SFUNCTION_EXTERN const double* input_gyro;
SFUNCTION_EXTERN const double* input_gyro_rates;

/* Laser */
SFUNCTION_EXTERN const double* input_laser;

/* MAGIC SPEED */
SFUNCTION_EXTERN const double* input_magic_velocity;

/* MAGIC SPEED */
SFUNCTION_EXTERN const double* input_quaternions;

//TODO:
//probably won't work because of int pointer!
//actully input_ad exist in perception as well! confusionß
SFUNCTION_EXTERN const int* input_ad;

SFUNCTION_EXTERN const double* srf_gnd;
SFUNCTION_EXTERN const double* srf_rhs;
SFUNCTION_EXTERN const double* srf_lhs;
SFUNCTION_EXTERN const double* srf_front_rhs;
SFUNCTION_EXTERN const double* srf_front_ctr;
SFUNCTION_EXTERN const double* srf_front_lhs;
SFUNCTION_EXTERN const double* srf_rear;
SFUNCTION_EXTERN const double* srf_ceiling;

SFUNCTION_EXTERN const double* input_z_pid;
SFUNCTION_EXTERN const double* input_yaw_pid;
SFUNCTION_EXTERN const double* input_x_pid;
SFUNCTION_EXTERN const double* input_y_pid;

SFUNCTION_EXTERN const double* input_x_position;
SFUNCTION_EXTERN const double* input_y_position;

/* OUTPUT */
/* LED */
SFUNCTION_EXTERN double* output_led;
SFUNCTION_EXTERN double* output_gas;
SFUNCTION_EXTERN double* output_yaw;
SFUNCTION_EXTERN double* output_nick;
SFUNCTION_EXTERN double* output_roll;

SFUNCTION_EXTERN double* output_elevation;
SFUNCTION_EXTERN double* output_desired_yaw;
SFUNCTION_EXTERN double* output_x;
SFUNCTION_EXTERN double* output_y;

SFUNCTION_EXTERN double* output_internalData;
SFUNCTION_EXTERN const float* input_pmd;

/* Simulation time */
SFUNCTION_EXTERN double sim_time;

#endif /* VARIABLES_CONTROL_H */

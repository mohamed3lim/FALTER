/* variables for falter_particle_sfunction */

#ifndef VARIABLES_PARTICLE_H
#define VARIABLES_PARTICLE_H

#include "simstruc.h"
#include <pmd_data.h>

/* Sample Time for the particle filter task. */
#define PARTICLE_SAMPLE_TIME      (0.5)

/* Number of output ports */
#define NUM_OUTPUT                0

/* shared memory inputs */
#define INPUT_PMD_DATA            0

/* INPUT */
#define INPUT_POSITION            1

/* INPUT */
#define INPUT_DCM                 2

/* INPUT */
#define INPUT_WALLS               3

/* INPUT */
#define INPUT_MEASURED_VELOCITY   4

/* Number of input ports */
#define NUM_INPUT                 5


#ifdef S_FUNCTION_NAME
    #define VARIABLES_PARTICLE_EXTERN 
#else
    #define VARIABLES_PARTICLE_EXTERN extern
#endif
        
VARIABLES_PARTICLE_EXTERN const double* input_position;

/* Simulation time */
VARIABLES_PARTICLE_EXTERN double sim_time;

VARIABLES_PARTICLE_EXTERN const double *input_dcm;
        
VARIABLES_PARTICLE_EXTERN const double *input_walls;

VARIABLES_PARTICLE_EXTERN const double *input_measured_velocity;



#endif /* VARIABLES_PARTICLE_H */

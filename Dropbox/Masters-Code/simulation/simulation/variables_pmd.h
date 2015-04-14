/* 
 * Variables for falter_pmd_sfunction 
 *
 * @author: bayha
 * @author: singh
 */

#ifndef VARIABLES_PMD_H
#define VARIABLES_PMD_H

#include "simstruc.h"
// #include <pmd_data.h>

/* Sample Time for the pmd task. */
#define PMD_SAMPLE_TIME           (0.05)

/* Number of output ports */
#define NUM_OUTPUT                0

/* shared memory inputs */
// #define INPUT_PMD_DATA            0

/* PMD sensor input */
#define INPUT_PMD                 1
// #define INPUT_PMD_WIDTH           (PMD_RES_WIDTH * PMD_RES_HIGHT)
#define INPUT_PMD_WIDTH           (48 * 64) //// check this one!
/* Number of input ports */
// #define NUM_INPUT                 2
#define NUM_INPUT                 1


#ifdef S_FUNCTION_NAME
    #define VARIABLES_PMD_EXTERN 
#else
    #define VARIABLES_PMD_EXTERN extern
#endif

/* PMD Distance Data */
VARIABLES_PMD_EXTERN const float* input_pmd;

/* Simulation time */
VARIABLES_PMD_EXTERN double sim_time;

#endif /* VARIABLES_PMD_H */

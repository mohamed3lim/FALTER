/* variables for all s-functions */

#ifndef VARIABLES_H
#define VARIABLES_H

#ifdef S_FUNCTION_NAME
    #define VARIABLES_EXTERN 
#else
    #define VARIABLES_EXTERN extern
#endif

/** 
 * SHARED MEMORY 
 * This variables are read only. They are used in the s-functions that do
 * not initialize the shared memory.
 **/
        
/**
 * sharedFlags is used in org.fortiss.falter.datacom/obstacles_notification.c
 * It is initialized in falter_perception_sfunction.c
 */

#endif /* VARIABLES_H */

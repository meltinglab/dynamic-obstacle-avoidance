/* Copyright 2018 The MathWorks, Inc. */

/* CA_CHECK_FLOATING_POINT_ENABLED controls whether floating point 
 * checks are executed. */
#ifndef CA_CHECK_FLOATING_POINT_ENABLED
   #error "CA_CHECK_FLOATING_POINT_ENABLED should always be defined!"
#endif

#if CA_CHECK_FLOATING_POINT_ENABLED == 1

    /* CA_CHECK_DAZ_ENABLED controls whether floating point DAZ checks are executed. */
    #ifndef CA_CHECK_DAZ_ENABLED
       #error "CA_CHECK_DAZ_ENABLED should always be defined!"
    #endif

    #include <float.h>
    volatile double realmin = DBL_MIN;
    
    #if CA_CHECK_DAZ_ENABLED == 1
        /* Initialize the DAZ test variable to ~DBL_MIN/2 (64bit) */
        volatile double denormalAsZero = 1.11e-308;
    #else
        /* Initialize the DAZ test variable to 0 because the compiler does 
         * not support out of range values.
         * This forces act->denormalAsZero to 1*/
        volatile double denormalAsZero = 0;
    #endif
#else
    typedef int xil_no_empty_unit;
#endif

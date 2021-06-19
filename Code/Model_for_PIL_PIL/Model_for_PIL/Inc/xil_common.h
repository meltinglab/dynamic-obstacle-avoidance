/* Copyright 2011-2013 The MathWorks, Inc. */

/*
 * File: xil_common.h
 *
 * SIL/PIL common definitions
 */

#ifndef __XIL_COMMON_H__
#define __XIL_COMMON_H__

#include "rtwtypes.h"
#include <string.h> /* include definition of size_t */

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

/* MIN is typically used in data stream implementations */
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#endif

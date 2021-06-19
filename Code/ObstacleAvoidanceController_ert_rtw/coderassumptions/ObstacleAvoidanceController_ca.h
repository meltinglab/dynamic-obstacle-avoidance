/*
 * File: ObstacleAvoidanceController_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef OBSTACLEAVOIDANCECONTROLLER_CA_H
#define OBSTACLEAVOIDANCECONTROLLER_CA_H

/* preprocessor validation checks */
#include "ObstacleAvoidanceController_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_HWImpl_TestResults CA_ObstacleAvoidanceController_HWRes;
extern CA_PWS_TestResults CA_ObstacleAvoidanceController_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_HWImpl CA_ObstacleAvoidanceController_ExpHW;
extern CA_HWImpl CA_ObstacleAvoidanceController_ActHW;

/* entry point function to run tests */
void ObstacleAvoidanceController_caRunTests(void);

#endif                                 /* OBSTACLEAVOIDANCECONTROLLER_CA_H */

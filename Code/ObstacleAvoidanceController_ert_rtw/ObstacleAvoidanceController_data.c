/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ObstacleAvoidanceController_data.c
 *
 * Code generated for Simulink model 'ObstacleAvoidanceController'.
 *
 * Model version                  : 5.1
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Jun 16 16:17:03 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Passed (12), Warning (1), Error (0)
 */

#include "ObstacleAvoidanceController.h"
#include "ObstacleAvoidanceController_private.h"

/* Invariant block signals (default storage) */
const ConstB_ObstacleAvoidanceController ObstacleAvoidanceController_ConstB = {
  { 30.0, 30.0, 8.0, 30.0 },           /* '<S8>/Math Function' */

  { 0.0, 0.0 },                        /* '<S8>/Math Function1' */

  { 0.0, 0.0 }                         /* '<S8>/Math Function2' */
};

/* Constant parameters (default storage) */
const ConstP_ObstacleAvoidanceController ObstacleAvoidanceController_ConstP = {
  /* Expression: lastPcov
   * Referenced by: '<S8>/LastPcov'
   */
  { 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1000.0 },

  /* Expression: lastx+xoff
   * Referenced by: '<S8>/last_x'
   */
  { 0.0, 0.0, -1.5483180211105141, 27.777777777777779, 0.0, 0.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_for_PIL.h
 *
 * Code generated for Simulink model :Model_for_PIL.
 *
 * Model version      : 1.18
 * Simulink Coder version    : 9.1 (R2019a) 23-Nov-2018
 * TLC version       : 9.1 (Sep  3 2020)
 * C/C++ source code generated on  : Sat Jun 19 17:49:38 2021
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STM32CortexM
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Passed (11), Warnings (2), Error (0)
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#ifndef RTW_HEADER_Model_for_PIL_h_
#define RTW_HEADER_Model_for_PIL_h_
#include <math.h>
#include <string.h>
#ifndef Model_for_PIL_COMMON_INCLUDES_
# define Model_for_PIL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Model_for_PIL_COMMON_INCLUDES_ */

#include "Model_for_PIL_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Real-time Model Data Structure */
struct tag_RTM_Model_for_PIL {
  const char_T **errorStatus;
};

typedef struct {
  RT_MODEL_Model_for_PIL rtm;
} MdlrefDW_Model_for_PIL;

/* Model reference registration function */
extern void Model_for_PIL_initialize(const char_T **rt_errorStatus,
  RT_MODEL_Model_for_PIL *const Model_for_PIL_M);
extern void Model_for_PIL(const real_T *rtu_SafeX, const real_T *rtu_SafeY,
  const real_T *rtu_EndX, const real_T *rtu_EndY, const real_T rtu_EntryPoint[4],
  const real_T rtu_DetPoint[4], const real_T *rtu_detection, const real_T
  *rtu_Zone, const real_T *rtu_Lw, const real_T rtu_Reference[4], const real_T
  *rtu_Curvature, real_T rty_E[4], real_T rty_F[8], real_T rty_G[2]);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model_for_PIL'
 * '<S1>'   : 'Model_for_PIL/Obs'
 * '<S2>'   : 'Model_for_PIL/Obs/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_Model_for_PIL_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Model_for_PIL.h
 */

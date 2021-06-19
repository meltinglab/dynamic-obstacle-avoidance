/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_for_PIL.c
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

#include "Model_for_PIL.h"
#include "Model_for_PIL_private.h"

/* Output and update for referenced model: 'Model_for_PIL' */
void Model_for_PIL(const real_T *rtu_SafeX, const real_T *rtu_SafeY, const
                   real_T *rtu_EndX, const real_T *rtu_EndY, const real_T
                   rtu_EntryPoint[4], const real_T rtu_DetPoint[4], const real_T
                   *rtu_detection, const real_T *rtu_Zone, const real_T *rtu_Lw,
                   const real_T rtu_Reference[4], const real_T *rtu_Curvature,
                   real_T rty_E[4], real_T rty_F[8], real_T rty_G[2])
{
  real_T Theta_ref;
  real_T q2;
  real_T slope;
  real_T constraintIntercept;
  boolean_T rEQ0;
  real_T q;
  if (rtIsNaN(rtu_Reference[2] + 3.1415926535897931)) {
    Theta_ref = (rtNaN);
  } else if (rtIsInf(rtu_Reference[2] + 3.1415926535897931)) {
    Theta_ref = (rtNaN);
  } else if (rtu_Reference[2] + 3.1415926535897931 == 0.0) {
    Theta_ref = 0.0;
  } else {
    Theta_ref = fmod(rtu_Reference[2] + 3.1415926535897931, 6.2831853071795862);
    rEQ0 = (Theta_ref == 0.0);
    if (!rEQ0) {
      q = fabs((rtu_Reference[2] + 3.1415926535897931) / 6.2831853071795862);
      rEQ0 = !(fabs(q - floor(q + 0.5)) > 2.2204460492503131E-16 * q);
    }

    if (rEQ0) {
      Theta_ref = 0.0;
    } else {
      if (rtu_Reference[2] + 3.1415926535897931 < 0.0) {
        Theta_ref += 6.2831853071795862;
      }
    }
  }

  Theta_ref -= 3.1415926535897931;
  q = tan(Theta_ref);
  if (fabs(q) > 1.0) {
    q = 1.0 / q;
    if (*rtu_detection != 0.0) {
      q2 = sin(Theta_ref);
      constraintIntercept = q * rtu_Reference[1];
      q2 = ((rtu_Reference[0] - 0.5 * *rtu_Lw / q2) - constraintIntercept) -
        *rtu_Lw / q2;
      if (*rtu_Zone == 2.0) {
        slope = (*rtu_SafeX - rtu_DetPoint[0]) / (*rtu_SafeY - rtu_DetPoint[1]);
        constraintIntercept = *rtu_SafeX - slope * *rtu_SafeY;
      } else if (*rtu_Zone == 3.0) {
        slope = q - 416.0 / rtu_Reference[3] * fabs(*rtu_Curvature);
        constraintIntercept = (rtu_Reference[0] - *rtu_Lw / sin(Theta_ref)) -
          slope * rtu_Reference[1];
      } else if (*rtu_Zone == 4.0) {
        slope = (rtu_EntryPoint[0] - *rtu_EndX) / (rtu_EntryPoint[1] - *rtu_EndY);
        constraintIntercept = rtu_EntryPoint[0] - slope * rtu_EntryPoint[1];
      } else {
        slope = q;
        constraintIntercept = (0.5 * *rtu_Lw / sin(Theta_ref) + rtu_Reference[0])
          - constraintIntercept;
      }

      if ((Theta_ref > 0.0) && (slope <= 0.0)) {
        rty_F[0] = 1.0;
        rty_F[2] = -slope;
        rty_F[4] = 0.0;
        rty_F[6] = 0.0;
        rty_F[1] = -1.0;
        rty_F[3] = q;
        rty_F[5] = 0.0;
        rty_F[7] = 0.0;
        rty_G[0] = constraintIntercept;
        rty_G[1] = -q2;
      } else if ((Theta_ref < 0.0) && (slope > 0.0)) {
        rty_F[0] = -1.0;
        rty_F[2] = slope;
        rty_F[4] = 0.0;
        rty_F[6] = 0.0;
        rty_F[1] = 1.0;
        rty_F[3] = -q;
        rty_F[5] = 0.0;
        rty_F[7] = 0.0;
        rty_G[0] = -constraintIntercept;
        rty_G[1] = q2;
      } else if ((Theta_ref > 0.0) && (slope > 0.0)) {
        rty_F[0] = 1.0;
        rty_F[2] = -slope;
        rty_F[4] = 0.0;
        rty_F[6] = 0.0;
        rty_F[1] = -1.0;
        rty_F[3] = q;
        rty_F[5] = 0.0;
        rty_F[7] = 0.0;
        rty_G[0] = constraintIntercept;
        rty_G[1] = -q2;
      } else {
        rty_F[0] = -1.0;
        rty_F[2] = slope;
        rty_F[4] = 0.0;
        rty_F[6] = 0.0;
        rty_F[1] = 1.0;
        rty_F[3] = -q;
        rty_F[5] = 0.0;
        rty_F[7] = 0.0;
        rty_G[0] = -constraintIntercept;
        rty_G[1] = q2;
      }
    } else {
      memset(&rty_F[0], 0, sizeof(real_T) << 3U);
      rty_G[0] = 0.0;
      rty_G[1] = 0.0;
    }
  } else if (*rtu_detection != 0.0) {
    q2 = cos(Theta_ref);
    constraintIntercept = q * rtu_Reference[0];
    q2 = ((0.5 * *rtu_Lw / q2 + rtu_Reference[1]) - constraintIntercept) +
      *rtu_Lw / q2;
    if (*rtu_Zone == 2.0) {
      slope = (*rtu_SafeY - rtu_DetPoint[1]) / (*rtu_SafeX - rtu_DetPoint[0]);
      constraintIntercept = *rtu_SafeY - slope * *rtu_SafeX;
    } else if (*rtu_Zone == 3.0) {
      slope = 416.0 / rtu_Reference[3] * fabs(*rtu_Curvature) + q;
      constraintIntercept = (*rtu_Lw / cos(Theta_ref) + rtu_Reference[1]) -
        slope * rtu_Reference[0];
    } else if (*rtu_Zone == 4.0) {
      slope = (rtu_EntryPoint[1] - *rtu_EndY) / (rtu_EntryPoint[0] - *rtu_EndX);
      constraintIntercept = rtu_EntryPoint[1] - slope * rtu_EntryPoint[0];
    } else {
      slope = q;
      constraintIntercept = (rtu_Reference[1] - 0.5 * *rtu_Lw / cos(Theta_ref))
        - constraintIntercept;
    }

    Theta_ref = fabs(Theta_ref);
    if ((Theta_ref <= 1.5707963267948966) && (slope >= 0.0)) {
      rty_F[0] = slope;
      rty_F[2] = -1.0;
      rty_F[4] = 0.0;
      rty_F[6] = 0.0;
      rty_F[1] = -q;
      rty_F[3] = 1.0;
      rty_F[5] = 0.0;
      rty_F[7] = 0.0;
      rty_G[0] = -constraintIntercept;
      rty_G[1] = q2;
    } else if ((Theta_ref > 1.5707963267948966) && (slope < 0.0)) {
      rty_F[0] = -slope;
      rty_F[2] = 1.0;
      rty_F[4] = 0.0;
      rty_F[6] = 0.0;
      rty_F[1] = q;
      rty_F[3] = -1.0;
      rty_F[5] = 0.0;
      rty_F[7] = 0.0;
      rty_G[0] = constraintIntercept;
      rty_G[1] = -q2;
    } else if ((Theta_ref <= 1.5707963267948966) && (slope < 0.0)) {
      rty_F[0] = slope;
      rty_F[2] = -1.0;
      rty_F[4] = 0.0;
      rty_F[6] = 0.0;
      rty_F[1] = -q;
      rty_F[3] = 1.0;
      rty_F[5] = 0.0;
      rty_F[7] = 0.0;
      rty_G[0] = -constraintIntercept;
      rty_G[1] = q2;
    } else {
      rty_F[0] = -slope;
      rty_F[2] = 1.0;
      rty_F[4] = 0.0;
      rty_F[6] = 0.0;
      rty_F[1] = q;
      rty_F[3] = -1.0;
      rty_F[5] = 0.0;
      rty_F[7] = 0.0;
      rty_G[0] = constraintIntercept;
      rty_G[1] = -q2;
    }
  } else {
    memset(&rty_F[0], 0, sizeof(real_T) << 3U);
    rty_G[0] = 0.0;
    rty_G[1] = 0.0;
  }

  rty_E[0] = 0.0;
  rty_E[1] = 0.0;
  rty_E[2] = 0.0;
  rty_E[3] = 0.0;
}

/* Model initialize function */
void Model_for_PIL_initialize(const char_T **rt_errorStatus,
  RT_MODEL_Model_for_PIL *const Model_for_PIL_M)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(Model_for_PIL_M, rt_errorStatus);
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] Model_for_PIL.c
 */

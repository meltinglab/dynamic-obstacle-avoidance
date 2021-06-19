/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ObstacleAvoidanceController.c
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
#include "DropConstraint_pw8y7UcF.h"
#include "Unconstrained_XbGnMUND.h"
#include "WtMult_9ptEzcS9.h"
#include "abs_dPqD3gJW.h"
#include "abs_eSIKPPwm.h"
#include "maximum2_o0q4L4FQ.h"
#include "maximum_WbjyebyW.h"
#include "minimum_t5zjUC2Z.h"
#include "mtimes_ZHySypuw.h"
#include "norm_U2d2wUAJ.h"
#include "rt_hypotd_snf.h"
#include "rt_powd_snf.h"
#include "rt_roundd_snf.h"
#include "trisolve_eOpSOCVD.h"
#include "xpotrf_wTXxIm7P.h"

/* Named constants for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
#define ObstacleAvoidanceController_nu (2.0)
#define ObstacleAvoidanceController_ny (4.0)

/* Named constants for MATLAB Function: '<S3>/Plant Model Generator' */
#define ObstacleAvoidanceController_Ts (0.01)

/* Block signals (default storage) */
B_ObstacleAvoidanceController ObstacleAvoidanceController_B;

/* Block states (default storage) */
DW_ObstacleAvoidanceController ObstacleAvoidanceController_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ObstacleAvoidanceController ObstacleAvoidanceController_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ObstacleAvoidanceController ObstacleAvoidanceController_Y;

/* Real-time model */
static RT_MODEL_ObstacleAvoidanceController ObstacleAvoidanceController_M_;
RT_MODEL_ObstacleAvoidanceController *const ObstacleAvoidanceController_M =
  &ObstacleAvoidanceController_M_;

/* Forward declaration for local functions */
static void ObstacleAvoidanceController_lusolve_PSVNo910(const real_T A[36],
  const real_T B[36], real_T X[36]);
static void ObstacleAvoidanceController_PadeApproximantOfDegree_quffSMBJ(const
  real_T A[36], uint8_T m, real_T F[36]);
static void ObstacleAvoidanceController_mpc_plantupdate_ktgMNkJb(const real_T a
  [16], real_T b[8], const real_T c[16], real_T b_A[36], real_T b_B[54], real_T
  b_C[24], const real_T b_D[36], const real_T b_mvindex[2], const real_T
  b_myindex[4], const real_T b_Uscale[2], const real_T b_Yscale[4], real_T Bu[12],
  real_T Bv[6], real_T Cm[24], real_T Dv[4], real_T Dvm[4], real_T QQ[36],
  real_T RR[16], real_T NN[24]);
static real_T ObstacleAvoidanceController_mod_b(real_T x);
static real_T ObstacleAvoidanceController_mod(real_T x);
static void ObstacleAvoidanceController_mpc_updateFromNominal(real_T b_Mlim[87],
  const real_T b_Mrows[55], const real_T U0[2], const real_T b_Uscale[2], const
  real_T old_mvoff[2], const real_T b_mvindex[2], real_T b_utarget[30], const
  real_T Y0[4], const real_T b_Yscale[4], const real_T old_yoff[4], const real_T
  b_myindex[4], const real_T X0[4], real_T b_xoff[6], const real_T DX0[4],
  real_T Bv[96], real_T new_mvoff[2], real_T new_yoff[4], real_T new_myoff[4]);
static void ObstacleAvoidanceController_mrdiv_BGzNp2vj(const real_T b_A[16],
  const real_T b_B[16], real_T Y[16]);
static void ObstacleAvoidanceController_mpc_constraintcoef_HBE9OVn8(const real_T
  b_A[36], const real_T Bu[12], const real_T Bv[6], const real_T b_C[24], const
  real_T Dv[4], const real_T b_Jm[300], real_T b_SuJm[600], real_T b_Sx[360],
  real_T b_Su1[120], real_T b_Hv[960]);
static void ObstacleAvoidanceController_kron_h2HmpwPU(const real_T b_A[256],
  const real_T b_B[4], real_T K[1024]);
static void ObstacleAvoidanceController_mpc_customconstraintcoef_X8ClKd4y(const
  real_T b_SuJm[600], const real_T b_Sx[360], const real_T b_Su1[120], const
  real_T b_Hv[960], const real_T b_C[24], const real_T Dv[64], const real_T
  b_Jm[300], const real_T E[4], const real_T F[8], const real_T G[2], const
  real_T mvoff[2], const real_T b_yoff[4], real_T Mu[320], real_T b_Mv[512],
  real_T b_Mu1[64], real_T b_Mx[192], real_T b_Mlim[32]);
static void ObstacleAvoidanceController_mpc_calculatehessian_l89OAA4T(const
  real_T b_Wy[4], const real_T b_Wu[2], const real_T b_Wdu[2], const real_T
  b_SuJm[600], const real_T I2Jm[300], const real_T b_Jm[300], const real_T
  b_I1[60], const real_T b_Su1[120], const real_T b_Sx[360], const real_T b_Hv
  [960], real_T nmv, real_T b_ny, real_T b_H[100], real_T b_Ku1[20], real_T
  b_Kut[300], real_T b_Kx[60], real_T b_Kv[160], real_T b_Kr[600]);
static void ObstacleAvoidanceController_mpc_checkhessian_zJaLOdRx(real_T b_H[121],
  real_T L[121], real_T *BadH);
static real_T ObstacleAvoidanceController_xnrm2_GjDYLhOh(int32_T n, const real_T
  x[121], int32_T ix0);
static void ObstacleAvoidanceController_xgemv_2GgNT4xY(int32_T b_m, int32_T n,
  const real_T b_A[121], int32_T ia0, const real_T x[121], int32_T ix0, real_T
  y[11]);
static void ObstacleAvoidanceController_xgerc_UQHWFbLL(int32_T b_m, int32_T n,
  real_T alpha1, int32_T ix0, const real_T y[11], real_T b_A[121], int32_T ia0);
static void ObstacleAvoidanceController_qrf_Bv1QUViS(real_T b_A[121], int32_T
  ia0, int32_T b_m, int32_T n, int32_T nfxd, real_T tau[11]);
static void ObstacleAvoidanceController_xgeqrf_iz011iUO(real_T b_A[121], real_T
  tau[11]);
static void ObstacleAvoidanceController_xorgqr_BxYGaI4b(int32_T b_m, int32_T n,
  int32_T k, real_T b_A[121], int32_T ia0, const real_T tau[11], int32_T itau0);
static void ObstacleAvoidanceController_qr_m3UlPv27(const real_T b_A[121],
  real_T Q[121], real_T R[121]);
static real_T ObstacleAvoidanceController_KWIKfactor_lFdJjicy(const real_T b_Ac
  [957], const int16_T iC[87], int16_T nA, const real_T b_Linv[121], real_T
  RLinv[121], real_T b_D[121], real_T b_H[121], int16_T n);
static void ObstacleAvoidanceController_qpkwik_XjF1fpUJ(const real_T b_Linv[121],
  const real_T b_Hinv[121], const real_T f[11], const real_T b_Ac[957], const
  real_T b[87], int16_T iA[87], int16_T maxiter, real_T FeasTol, real_T x[11],
  real_T lambda[87], real_T *status);
static void ObstacleAvoidanceController_mpc_solveQP_qQaaXkaK(const real_T xQP[6],
  const real_T b_Kx[60], const real_T b_Kr[600], const real_T rseq[60], const
  real_T b_Ku1[20], const real_T old_u[2], const real_T b_Kv[160], const real_T
  vseq[16], const real_T b_Kut[300], const real_T b_utarget[30], const real_T
  b_Linv[121], const real_T b_Hinv[121], const real_T b_Ac[957], const real_T
  Bc[87], boolean_T iA[87], real_T zopt[11], real_T f[11], real_T *status);
static void ObstacleAvoidanceController_mpcblock_optimizer(const real_T rseq[60],
  const real_T vseq[16], const real_T x[6], const real_T old_u[2], const
  boolean_T iA[87], real_T b_Mlim[87], real_T b_Mx[522], real_T b_Mu1[174],
  real_T b_Mv[1392], const real_T b_utarget[30], const real_T b_uoff[2], const
  real_T b_yoff[4], real_T b_H[121], real_T b_Ac[957], const real_T ywt[4],
  const real_T uwt[2], const real_T duwt[2], const real_T b_Jm[300], const
  real_T b_I1[60], const real_T b_A[36], const real_T Bu[192], const real_T Bv
  [96], const real_T b_C[24], const real_T Dv[64], const real_T b_Mrows[55],
  const real_T b_Ecc[4], const real_T b_Fcc[8], const real_T b_Gcc[2], real_T u
  [2], real_T useq[32], real_T *status, boolean_T iAout[87]);

/* Function for MATLAB Function: '<S3>/Plant Model Generator' */
static void ObstacleAvoidanceController_lusolve_PSVNo910(const real_T A[36],
  const real_T B[36], real_T X[36])
{
  real_T y;
  int32_T b_j;
  int32_T c;
  int32_T c_ix;
  int32_T c_k;
  int32_T d;
  int32_T ijA;
  int32_T ix;
  int32_T jA;
  int8_T ipiv[6];
  int8_T ipiv_0;
  (void)memcpy(&ObstacleAvoidanceController_B.b_A[0], &A[0], 36U * (sizeof
    (real_T)));
  for (c = 0; c < 6; c++) {
    ipiv[c] = (int8_T)(c + 1);
  }

  for (b_j = 0; b_j < 5; b_j++) {
    c = b_j * 7;
    jA = 0;
    ix = c;
    ObstacleAvoidanceController_B.smax = fabs
      (ObstacleAvoidanceController_B.b_A[c]);
    for (c_k = 2; c_k <= (6 - b_j); c_k++) {
      ix++;
      y = fabs(ObstacleAvoidanceController_B.b_A[ix]);
      if (y > ObstacleAvoidanceController_B.smax) {
        jA = c_k - 1;
        ObstacleAvoidanceController_B.smax = y;
      }
    }

    if (ObstacleAvoidanceController_B.b_A[c + jA] != 0.0) {
      if (jA != 0) {
        jA += b_j;
        ipiv[b_j] = (int8_T)(jA + 1);
        for (ix = 0; ix < 6; ix++) {
          c_k = (ix * 6) + b_j;
          ObstacleAvoidanceController_B.smax =
            ObstacleAvoidanceController_B.b_A[c_k];
          c_ix = (ix * 6) + jA;
          ObstacleAvoidanceController_B.b_A[c_k] =
            ObstacleAvoidanceController_B.b_A[c_ix];
          ObstacleAvoidanceController_B.b_A[c_ix] =
            ObstacleAvoidanceController_B.smax;
        }
      }

      jA = (c - b_j) + 6;
      for (ix = c + 1; ix < jA; ix++) {
        ObstacleAvoidanceController_B.b_A[ix] /=
          ObstacleAvoidanceController_B.b_A[c];
      }
    }

    jA = c;
    ix = c + 6;
    for (c_k = 0; c_k <= (4 - b_j); c_k++) {
      if (ObstacleAvoidanceController_B.b_A[ix] != 0.0) {
        ObstacleAvoidanceController_B.smax =
          -ObstacleAvoidanceController_B.b_A[ix];
        c_ix = c + 1;
        d = (jA - b_j) + 12;
        for (ijA = jA + 7; ijA < d; ijA++) {
          ObstacleAvoidanceController_B.b_A[ijA] +=
            ObstacleAvoidanceController_B.b_A[c_ix] *
            ObstacleAvoidanceController_B.smax;
          c_ix++;
        }
      }

      ix += 6;
      jA += 6;
    }
  }

  (void)memcpy(&X[0], &B[0], 36U * (sizeof(real_T)));
  for (c = 0; c < 5; c++) {
    ipiv_0 = ipiv[c];
    if ((c + 1) != ((int32_T)ipiv_0)) {
      for (jA = 0; jA < 6; jA++) {
        ix = (6 * jA) + c;
        ObstacleAvoidanceController_B.smax = X[ix];
        b_j = (((int32_T)ipiv_0) + (6 * jA)) - 1;
        X[ix] = X[b_j];
        X[b_j] = ObstacleAvoidanceController_B.smax;
      }
    }
  }

  for (jA = 0; jA < 6; jA++) {
    ix = 6 * jA;
    for (c_k = 0; c_k < 6; c_k++) {
      c_ix = 6 * c_k;
      c = c_k + ix;
      if (X[c] != 0.0) {
        for (d = c_k + 2; d < 7; d++) {
          b_j = (d + ix) - 1;
          X[b_j] -= ObstacleAvoidanceController_B.b_A[(d + c_ix) - 1] * X[c];
        }
      }
    }
  }

  for (jA = 0; jA < 6; jA++) {
    ix = 6 * jA;
    for (c_k = 5; c_k >= 0; c_k--) {
      c_ix = 6 * c_k;
      c = c_k + ix;
      ObstacleAvoidanceController_B.smax = X[c];
      if (ObstacleAvoidanceController_B.smax != 0.0) {
        X[c] = ObstacleAvoidanceController_B.smax /
          ObstacleAvoidanceController_B.b_A[c_k + c_ix];
        for (d = 0; d < c_k; d++) {
          b_j = d + ix;
          X[b_j] -= X[c] * ObstacleAvoidanceController_B.b_A[d + c_ix];
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S3>/Plant Model Generator' */
static void ObstacleAvoidanceController_PadeApproximantOfDegree_quffSMBJ(const
  real_T A[36], uint8_T m, real_T F[36])
{
  int32_T A2_tmp;
  int32_T c_k;
  int32_T e_k;
  int32_T i;
  for (e_k = 0; e_k < 6; e_k++) {
    for (c_k = 0; c_k < 6; c_k++) {
      ObstacleAvoidanceController_B.A2[c_k + (6 * e_k)] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      for (c_k = 0; c_k < 6; c_k++) {
        A2_tmp = (6 * e_k) + c_k;
        ObstacleAvoidanceController_B.A2[A2_tmp] += A[(6 * i) + c_k] * A[(6 *
          e_k) + i];
      }
    }
  }

  if (((int32_T)m) == 3) {
    (void)memcpy(&ObstacleAvoidanceController_B.U_p[0],
                 &ObstacleAvoidanceController_B.A2[0], 36U * (sizeof(real_T)));
    for (c_k = 0; c_k < 6; c_k++) {
      for (e_k = 0; e_k < 6; e_k++) {
        ObstacleAvoidanceController_B.A4_l[e_k + (6 * c_k)] = 0.0;
      }

      A2_tmp = (6 * c_k) + c_k;
      ObstacleAvoidanceController_B.U_p[A2_tmp] += 60.0;
    }

    for (c_k = 0; c_k < 6; c_k++) {
      for (i = 0; i < 6; i++) {
        for (e_k = 0; e_k < 6; e_k++) {
          A2_tmp = (6 * c_k) + e_k;
          ObstacleAvoidanceController_B.A4_l[A2_tmp] += A[(6 * i) + e_k] *
            ObstacleAvoidanceController_B.U_p[(6 * c_k) + i];
        }
      }
    }

    for (e_k = 0; e_k < 36; e_k++) {
      ObstacleAvoidanceController_B.U_p[e_k] =
        ObstacleAvoidanceController_B.A4_l[e_k];
      ObstacleAvoidanceController_B.V[e_k] = 12.0 *
        ObstacleAvoidanceController_B.A2[e_k];
    }

    ObstacleAvoidanceController_B.d_n = 120.0;
  } else {
    for (e_k = 0; e_k < 6; e_k++) {
      for (c_k = 0; c_k < 6; c_k++) {
        ObstacleAvoidanceController_B.A3[c_k + (6 * e_k)] = 0.0;
      }

      for (i = 0; i < 6; i++) {
        for (c_k = 0; c_k < 6; c_k++) {
          A2_tmp = (6 * e_k) + c_k;
          ObstacleAvoidanceController_B.A3[A2_tmp] +=
            ObstacleAvoidanceController_B.A2[(6 * i) + c_k] *
            ObstacleAvoidanceController_B.A2[(6 * e_k) + i];
        }
      }
    }

    if (((int32_T)m) == 5) {
      for (e_k = 0; e_k < 36; e_k++) {
        ObstacleAvoidanceController_B.U_p[e_k] = (420.0 *
          ObstacleAvoidanceController_B.A2[e_k]) +
          ObstacleAvoidanceController_B.A3[e_k];
      }

      for (c_k = 0; c_k < 6; c_k++) {
        for (e_k = 0; e_k < 6; e_k++) {
          ObstacleAvoidanceController_B.A4_l[e_k + (6 * c_k)] = 0.0;
        }

        A2_tmp = (6 * c_k) + c_k;
        ObstacleAvoidanceController_B.U_p[A2_tmp] += 15120.0;
      }

      for (c_k = 0; c_k < 6; c_k++) {
        for (i = 0; i < 6; i++) {
          for (e_k = 0; e_k < 6; e_k++) {
            A2_tmp = (6 * c_k) + e_k;
            ObstacleAvoidanceController_B.A4_l[A2_tmp] += A[(6 * i) + e_k] *
              ObstacleAvoidanceController_B.U_p[(6 * c_k) + i];
          }
        }
      }

      for (e_k = 0; e_k < 36; e_k++) {
        ObstacleAvoidanceController_B.U_p[e_k] =
          ObstacleAvoidanceController_B.A4_l[e_k];
        ObstacleAvoidanceController_B.V[e_k] = (30.0 *
          ObstacleAvoidanceController_B.A3[e_k]) + (3360.0 *
          ObstacleAvoidanceController_B.A2[e_k]);
      }

      ObstacleAvoidanceController_B.d_n = 30240.0;
    } else {
      for (e_k = 0; e_k < 6; e_k++) {
        for (c_k = 0; c_k < 6; c_k++) {
          ObstacleAvoidanceController_B.A4[c_k + (6 * e_k)] = 0.0;
        }

        for (i = 0; i < 6; i++) {
          for (c_k = 0; c_k < 6; c_k++) {
            A2_tmp = (6 * e_k) + c_k;
            ObstacleAvoidanceController_B.A4[A2_tmp] +=
              ObstacleAvoidanceController_B.A3[(6 * i) + c_k] *
              ObstacleAvoidanceController_B.A2[(6 * e_k) + i];
          }
        }
      }

      switch (m) {
       case 7:
        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.U_p[e_k] = ((1512.0 *
            ObstacleAvoidanceController_B.A3[e_k]) +
            ObstacleAvoidanceController_B.A4[e_k]) + (277200.0 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        for (c_k = 0; c_k < 6; c_k++) {
          for (e_k = 0; e_k < 6; e_k++) {
            ObstacleAvoidanceController_B.A4_l[e_k + (6 * c_k)] = 0.0;
          }

          A2_tmp = (6 * c_k) + c_k;
          ObstacleAvoidanceController_B.U_p[A2_tmp] += 8.64864E+6;
        }

        for (c_k = 0; c_k < 6; c_k++) {
          for (i = 0; i < 6; i++) {
            for (e_k = 0; e_k < 6; e_k++) {
              A2_tmp = (6 * c_k) + e_k;
              ObstacleAvoidanceController_B.A4_l[A2_tmp] += A[(6 * i) + e_k] *
                ObstacleAvoidanceController_B.U_p[(6 * c_k) + i];
            }
          }
        }

        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.U_p[e_k] =
            ObstacleAvoidanceController_B.A4_l[e_k];
          ObstacleAvoidanceController_B.V[e_k] = ((56.0 *
            ObstacleAvoidanceController_B.A4[e_k]) + (25200.0 *
            ObstacleAvoidanceController_B.A3[e_k])) + (1.99584E+6 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        ObstacleAvoidanceController_B.d_n = 1.729728E+7;
        break;

       case 9:
        for (e_k = 0; e_k < 6; e_k++) {
          for (c_k = 0; c_k < 6; c_k++) {
            ObstacleAvoidanceController_B.V[c_k + (6 * e_k)] = 0.0;
          }

          for (i = 0; i < 6; i++) {
            for (c_k = 0; c_k < 6; c_k++) {
              A2_tmp = (6 * e_k) + c_k;
              ObstacleAvoidanceController_B.V[A2_tmp] +=
                ObstacleAvoidanceController_B.A4[(6 * i) + c_k] *
                ObstacleAvoidanceController_B.A2[(6 * e_k) + i];
            }
          }
        }

        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.U_p[e_k] = (((3960.0 *
            ObstacleAvoidanceController_B.A4[e_k]) +
            ObstacleAvoidanceController_B.V[e_k]) + (2.16216E+6 *
            ObstacleAvoidanceController_B.A3[e_k])) + (3.027024E+8 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        for (c_k = 0; c_k < 6; c_k++) {
          for (e_k = 0; e_k < 6; e_k++) {
            ObstacleAvoidanceController_B.A4_l[e_k + (6 * c_k)] = 0.0;
          }

          A2_tmp = (6 * c_k) + c_k;
          ObstacleAvoidanceController_B.U_p[A2_tmp] += 8.8216128E+9;
        }

        for (c_k = 0; c_k < 6; c_k++) {
          for (i = 0; i < 6; i++) {
            for (e_k = 0; e_k < 6; e_k++) {
              A2_tmp = (6 * c_k) + e_k;
              ObstacleAvoidanceController_B.A4_l[A2_tmp] += A[(6 * i) + e_k] *
                ObstacleAvoidanceController_B.U_p[(6 * c_k) + i];
            }
          }
        }

        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.U_p[e_k] =
            ObstacleAvoidanceController_B.A4_l[e_k];
          ObstacleAvoidanceController_B.V[e_k] = (((90.0 *
            ObstacleAvoidanceController_B.V[e_k]) + (110880.0 *
            ObstacleAvoidanceController_B.A4[e_k])) + (3.027024E+7 *
            ObstacleAvoidanceController_B.A3[e_k])) + (2.0756736E+9 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        ObstacleAvoidanceController_B.d_n = 1.76432256E+10;
        break;

       default:
        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.U_p[e_k] = ((3.352212864E+10 *
            ObstacleAvoidanceController_B.A4[e_k]) + (1.05594705216E+13 *
            ObstacleAvoidanceController_B.A3[e_k])) + (1.1873537964288E+15 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        for (e_k = 0; e_k < 6; e_k++) {
          A2_tmp = (6 * e_k) + e_k;
          ObstacleAvoidanceController_B.U_p[A2_tmp] += 3.238237626624E+16;
        }

        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.V[e_k] = ((16380.0 *
            ObstacleAvoidanceController_B.A3[e_k]) +
            ObstacleAvoidanceController_B.A4[e_k]) + (4.08408E+7 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        for (e_k = 0; e_k < 6; e_k++) {
          for (c_k = 0; c_k < 6; c_k++) {
            ObstacleAvoidanceController_B.d_n = 0.0;
            for (i = 0; i < 6; i++) {
              ObstacleAvoidanceController_B.d_n +=
                ObstacleAvoidanceController_B.A4[(6 * i) + e_k] *
                ObstacleAvoidanceController_B.V[(6 * c_k) + i];
            }

            A2_tmp = (6 * c_k) + e_k;
            ObstacleAvoidanceController_B.A4_l[A2_tmp] =
              ObstacleAvoidanceController_B.U_p[A2_tmp] +
              ObstacleAvoidanceController_B.d_n;
          }
        }

        for (e_k = 0; e_k < 6; e_k++) {
          for (c_k = 0; c_k < 6; c_k++) {
            ObstacleAvoidanceController_B.U_p[c_k + (6 * e_k)] = 0.0;
          }

          for (i = 0; i < 6; i++) {
            for (c_k = 0; c_k < 6; c_k++) {
              A2_tmp = (6 * e_k) + c_k;
              ObstacleAvoidanceController_B.U_p[A2_tmp] += A[(6 * i) + c_k] *
                ObstacleAvoidanceController_B.A4_l[(6 * e_k) + i];
            }
          }
        }

        for (e_k = 0; e_k < 36; e_k++) {
          ObstacleAvoidanceController_B.A4_l[e_k] = ((182.0 *
            ObstacleAvoidanceController_B.A4[e_k]) + (960960.0 *
            ObstacleAvoidanceController_B.A3[e_k])) + (1.32324192E+9 *
            ObstacleAvoidanceController_B.A2[e_k]);
        }

        for (e_k = 0; e_k < 6; e_k++) {
          for (c_k = 0; c_k < 6; c_k++) {
            ObstacleAvoidanceController_B.d_n = 0.0;
            for (i = 0; i < 6; i++) {
              ObstacleAvoidanceController_B.d_n +=
                ObstacleAvoidanceController_B.A4[(6 * i) + e_k] *
                ObstacleAvoidanceController_B.A4_l[(6 * c_k) + i];
            }

            A2_tmp = (6 * c_k) + e_k;
            ObstacleAvoidanceController_B.V[A2_tmp] =
              (((ObstacleAvoidanceController_B.A4[A2_tmp] * 6.704425728E+11) +
                ObstacleAvoidanceController_B.d_n) +
               (ObstacleAvoidanceController_B.A3[A2_tmp] * 1.29060195264E+14)) +
              (ObstacleAvoidanceController_B.A2[A2_tmp] * 7.7717703038976E+15);
          }
        }

        ObstacleAvoidanceController_B.d_n = 6.476475253248E+16;
        break;
      }
    }
  }

  for (e_k = 0; e_k < 6; e_k++) {
    A2_tmp = (6 * e_k) + e_k;
    ObstacleAvoidanceController_B.V[A2_tmp] += ObstacleAvoidanceController_B.d_n;
  }

  for (e_k = 0; e_k < 36; e_k++) {
    ObstacleAvoidanceController_B.d_n = ObstacleAvoidanceController_B.U_p[e_k];
    ObstacleAvoidanceController_B.V[e_k] -= ObstacleAvoidanceController_B.d_n;
    ObstacleAvoidanceController_B.U_p[e_k] = 2.0 *
      ObstacleAvoidanceController_B.d_n;
  }

  ObstacleAvoidanceController_lusolve_PSVNo910(ObstacleAvoidanceController_B.V,
    ObstacleAvoidanceController_B.U_p, F);
  for (e_k = 0; e_k < 6; e_k++) {
    c_k = (6 * e_k) + e_k;
    F[c_k]++;
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_plantupdate_ktgMNkJb(const real_T a
  [16], real_T b[8], const real_T c[16], real_T b_A[36], real_T b_B[54], real_T
  b_C[24], const real_T b_D[36], const real_T b_mvindex[2], const real_T
  b_myindex[4], const real_T b_Uscale[2], const real_T b_Yscale[4], real_T Bu[12],
  real_T Bv[6], real_T Cm[24], real_T Dv[4], real_T Dvm[4], real_T QQ[36],
  real_T RR[16], real_T NN[24])
{
  real_T b_Uscale_0;
  int32_T CovMat_tmp;
  int32_T RR_tmp;
  int32_T b_tmp;
  int32_T i;
  int8_T UnknownIn[8];
  for (i = 0; i < 2; i++) {
    b_Uscale_0 = b_Uscale[i];
    b_tmp = i * 4;
    b[b_tmp] *= b_Uscale_0;
    b[b_tmp + 1] *= b_Uscale_0;
    b[b_tmp + 2] *= b_Uscale_0;
    b[b_tmp + 3] *= b_Uscale_0;
  }

  for (i = 0; i < 4; i++) {
    b_tmp = i * 4;
    b_C[b_tmp] = c[b_tmp] / b_Yscale[0];
    b_A[6 * i] = a[b_tmp];
    b_C[b_tmp + 1] = c[b_tmp + 1] / b_Yscale[1];
    b_A[(6 * i) + 1] = a[b_tmp + 1];
    b_C[b_tmp + 2] = c[b_tmp + 2] / b_Yscale[2];
    b_A[(6 * i) + 2] = a[b_tmp + 2];
    b_C[b_tmp + 3] = c[b_tmp + 3] / b_Yscale[3];
    b_A[(6 * i) + 3] = a[b_tmp + 3];
  }

  for (i = 0; i < 2; i++) {
    b_tmp = (((int32_T)b_mvindex[i]) - 1) * 4;
    b_B[6 * i] = b[b_tmp];
    b_B[(6 * i) + 1] = b[b_tmp + 1];
    b_B[(6 * i) + 2] = b[b_tmp + 2];
    b_B[(6 * i) + 3] = b[b_tmp + 3];
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      Bu[b_tmp + (6 * i)] = b_B[(6 * i) + b_tmp];
    }
  }

  for (i = 0; i < 6; i++) {
    Bv[i] = b_B[i + 12];
    b_tmp = i * 4;
    Cm[b_tmp] = b_C[(b_tmp + ((int32_T)b_myindex[0])) - 1];
    Cm[b_tmp + 1] = b_C[(b_tmp + ((int32_T)b_myindex[1])) - 1];
    Cm[b_tmp + 2] = b_C[(b_tmp + ((int32_T)b_myindex[2])) - 1];
    Cm[b_tmp + 3] = b_C[(b_tmp + ((int32_T)b_myindex[3])) - 1];
  }

  Dv[0] = b_D[8];
  Dvm[0] = b_D[((int32_T)b_myindex[0]) + 7];
  Dv[1] = b_D[9];
  Dvm[1] = b_D[((int32_T)b_myindex[1]) + 7];
  Dv[2] = b_D[10];
  Dvm[2] = b_D[((int32_T)b_myindex[2]) + 7];
  Dv[3] = b_D[11];
  Dvm[3] = b_D[((int32_T)b_myindex[3]) + 7];
  for (i = 0; i < 8; i++) {
    UnknownIn[i] = 0;
  }

  UnknownIn[0] = 1;
  UnknownIn[1] = 2;
  for (i = 0; i < 6; i++) {
    UnknownIn[i + 2] = (int8_T)(i + 4);
  }

  for (i = 0; i < 8; i++) {
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      ObstacleAvoidanceController_B.b_B[b_tmp + (10 * i)] = b_B[((((int32_T)
        UnknownIn[i]) - 1) * 6) + b_tmp];
    }

    b_tmp = (((int32_T)UnknownIn[i]) - 1) * 4;
    ObstacleAvoidanceController_B.b_B[(10 * i) + 6] = b_D[(b_tmp + ((int32_T)
      b_myindex[0])) - 1];
    ObstacleAvoidanceController_B.b_B[(10 * i) + 7] = b_D[(b_tmp + ((int32_T)
      b_myindex[1])) - 1];
    ObstacleAvoidanceController_B.b_B[(10 * i) + 8] = b_D[(b_tmp + ((int32_T)
      b_myindex[2])) - 1];
    ObstacleAvoidanceController_B.b_B[(10 * i) + 9] = b_D[(b_tmp + ((int32_T)
      b_myindex[3])) - 1];
  }

  for (i = 0; i < 6; i++) {
    for (b_tmp = 0; b_tmp < 8; b_tmp++) {
      ObstacleAvoidanceController_B.b_B_c[b_tmp + (i * 8)] = b_B[((((int32_T)
        UnknownIn[b_tmp]) - 1) * 6) + i];
    }
  }

  for (i = 0; i < 4; i++) {
    for (b_tmp = 0; b_tmp < 8; b_tmp++) {
      ObstacleAvoidanceController_B.b_B_c[b_tmp + ((i + 6) * 8)] = b_D
        [(((((int32_T)UnknownIn[b_tmp]) - 1) * 4) + ((int32_T)b_myindex[i])) - 1];
    }
  }

  for (i = 0; i < 10; i++) {
    (void)memset(&ObstacleAvoidanceController_B.CovMat[i * 10], 0, 10U * (sizeof
      (real_T)));
    for (RR_tmp = 0; RR_tmp < 8; RR_tmp++) {
      for (b_tmp = 0; b_tmp < 10; b_tmp++) {
        CovMat_tmp = (10 * i) + b_tmp;
        ObstacleAvoidanceController_B.CovMat[CovMat_tmp] +=
          ObstacleAvoidanceController_B.b_B[(10 * RR_tmp) + b_tmp] *
          ObstacleAvoidanceController_B.b_B_c[(i * 8) + RR_tmp];
      }
    }
  }

  for (i = 0; i < 6; i++) {
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      QQ[b_tmp + (6 * i)] = ObstacleAvoidanceController_B.CovMat[(10 * i) +
        b_tmp];
    }
  }

  for (i = 0; i < 4; i++) {
    RR_tmp = (i + 6) * 10;
    b_tmp = i * 4;
    RR[b_tmp] = ObstacleAvoidanceController_B.CovMat[RR_tmp + 6];
    RR[b_tmp + 1] = ObstacleAvoidanceController_B.CovMat[RR_tmp + 7];
    RR[b_tmp + 2] = ObstacleAvoidanceController_B.CovMat[RR_tmp + 8];
    RR[b_tmp + 3] = ObstacleAvoidanceController_B.CovMat[RR_tmp + 9];
    for (b_tmp = 0; b_tmp < 6; b_tmp++) {
      NN[b_tmp + (6 * i)] = ObstacleAvoidanceController_B.CovMat[RR_tmp + b_tmp];
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static real_T ObstacleAvoidanceController_mod_b(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, ObstacleAvoidanceController_nu);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += ObstacleAvoidanceController_nu;
    } else {
      /* no actions */
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static real_T ObstacleAvoidanceController_mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, ObstacleAvoidanceController_ny);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += ObstacleAvoidanceController_ny;
    } else {
      /* no actions */
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_updateFromNominal(real_T b_Mlim[87],
  const real_T b_Mrows[55], const real_T U0[2], const real_T b_Uscale[2], const
  real_T old_mvoff[2], const real_T b_mvindex[2], real_T b_utarget[30], const
  real_T Y0[4], const real_T b_Yscale[4], const real_T old_yoff[4], const real_T
  b_myindex[4], const real_T X0[4], real_T b_xoff[6], const real_T DX0[4],
  real_T Bv[96], real_T new_mvoff[2], real_T new_yoff[4], real_T new_myoff[4])
{
  real_T U[2];
  real_T U_0;
  real_T k;
  int32_T b_ct;
  int32_T b_utarget_tmp;
  int32_T i;
  U[0] = U0[0] / b_Uscale[0];
  U[1] = U0[1] / b_Uscale[1];
  new_yoff[0] = Y0[0] / b_Yscale[0];
  new_yoff[1] = Y0[1] / b_Yscale[1];
  new_yoff[2] = Y0[2] / b_Yscale[2];
  new_yoff[3] = Y0[3] / b_Yscale[3];
  new_mvoff[0] = U0[((int32_T)b_mvindex[0]) - 1] / b_Uscale[((int32_T)b_mvindex
    [0]) - 1];
  new_mvoff[1] = U0[((int32_T)b_mvindex[1]) - 1] / b_Uscale[((int32_T)b_mvindex
    [1]) - 1];
  new_myoff[0] = new_yoff[((int32_T)b_myindex[0]) - 1];
  new_myoff[1] = new_yoff[((int32_T)b_myindex[1]) - 1];
  new_myoff[2] = new_yoff[((int32_T)b_myindex[2]) - 1];
  new_myoff[3] = new_yoff[((int32_T)b_myindex[3]) - 1];
  for (b_ct = 0; b_ct < 55; b_ct++) {
    k = b_Mrows[b_ct];
    if (k <= 60.0) {
      k = ObstacleAvoidanceController_mod(k - 1.0) + 1.0;
      b_Mlim[b_ct] += old_yoff[((int32_T)k) - 1] - new_yoff[((int32_T)k) - 1];
    } else if (k <= 120.0) {
      k = ObstacleAvoidanceController_mod((k - 60.0) - 1.0) + 1.0;
      b_Mlim[b_ct] -= old_yoff[((int32_T)k) - 1] - new_yoff[((int32_T)k) - 1];
    } else if (k <= 150.0) {
      k = ObstacleAvoidanceController_mod_b((k - 120.0) - 1.0) + 1.0;
      b_Mlim[b_ct] += old_mvoff[((int32_T)k) - 1] - U[((int32_T)b_mvindex
        [((int32_T)k) - 1]) - 1];
    } else if (k <= 180.0) {
      k = ObstacleAvoidanceController_mod_b(((k - 120.0) - 30.0) - 1.0) + 1.0;
      b_Mlim[b_ct] -= old_mvoff[((int32_T)k) - 1] - U[((int32_T)b_mvindex
        [((int32_T)k) - 1]) - 1];
    } else {
      /* no actions */
    }
  }

  for (b_ct = 0; b_ct < 2; b_ct++) {
    k = old_mvoff[b_ct];
    U_0 = U[((int32_T)b_mvindex[b_ct]) - 1];
    for (i = 0; i < 15; i++) {
      b_utarget_tmp = (2 * i) + b_ct;
      b_utarget[b_utarget_tmp] = (b_utarget[b_utarget_tmp] + k) - U_0;
    }
  }

  b_xoff[0] = X0[0];
  Bv[0] = DX0[0];
  b_xoff[1] = X0[1];
  Bv[1] = DX0[1];
  b_xoff[2] = X0[2];
  Bv[2] = DX0[2];
  b_xoff[3] = X0[3];
  Bv[3] = DX0[3];
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mrdiv_BGzNp2vj(const real_T b_A[16],
  const real_T b_B[16], real_T Y[16])
{
  real_T smax;
  real_T y;
  int32_T c;
  int32_T c_ix;
  int32_T c_k;
  int32_T d;
  int32_T d_j;
  int32_T ijA;
  int32_T ix;
  int32_T jA;
  int8_T ipiv[4];
  int8_T ipiv_0;
  (void)memcpy(&ObstacleAvoidanceController_B.c_A_l[0], &b_B[0], (sizeof(real_T))
               << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (d_j = 0; d_j < 3; d_j++) {
    c = d_j * 5;
    jA = 0;
    ix = c;
    smax = fabs(ObstacleAvoidanceController_B.c_A_l[c]);
    for (c_k = 2; c_k <= (4 - d_j); c_k++) {
      ix++;
      y = fabs(ObstacleAvoidanceController_B.c_A_l[ix]);
      if (y > smax) {
        jA = c_k - 1;
        smax = y;
      }
    }

    if (ObstacleAvoidanceController_B.c_A_l[c + jA] != 0.0) {
      if (jA != 0) {
        jA += d_j;
        ipiv[d_j] = (int8_T)(jA + 1);
        smax = ObstacleAvoidanceController_B.c_A_l[d_j];
        ObstacleAvoidanceController_B.c_A_l[d_j] =
          ObstacleAvoidanceController_B.c_A_l[jA];
        ObstacleAvoidanceController_B.c_A_l[jA] = smax;
        smax = ObstacleAvoidanceController_B.c_A_l[d_j + 4];
        ObstacleAvoidanceController_B.c_A_l[d_j + 4] =
          ObstacleAvoidanceController_B.c_A_l[jA + 4];
        ObstacleAvoidanceController_B.c_A_l[jA + 4] = smax;
        smax = ObstacleAvoidanceController_B.c_A_l[d_j + 8];
        ObstacleAvoidanceController_B.c_A_l[d_j + 8] =
          ObstacleAvoidanceController_B.c_A_l[jA + 8];
        ObstacleAvoidanceController_B.c_A_l[jA + 8] = smax;
        smax = ObstacleAvoidanceController_B.c_A_l[d_j + 12];
        ObstacleAvoidanceController_B.c_A_l[d_j + 12] =
          ObstacleAvoidanceController_B.c_A_l[jA + 12];
        ObstacleAvoidanceController_B.c_A_l[jA + 12] = smax;
      }

      jA = (c - d_j) + 4;
      for (ix = c + 1; ix < jA; ix++) {
        ObstacleAvoidanceController_B.c_A_l[ix] /=
          ObstacleAvoidanceController_B.c_A_l[c];
      }
    }

    jA = c;
    ix = c + 4;
    for (c_k = 0; c_k <= (2 - d_j); c_k++) {
      if (ObstacleAvoidanceController_B.c_A_l[ix] != 0.0) {
        smax = -ObstacleAvoidanceController_B.c_A_l[ix];
        c_ix = c + 1;
        d = (jA - d_j) + 8;
        for (ijA = jA + 5; ijA < d; ijA++) {
          ObstacleAvoidanceController_B.c_A_l[ijA] +=
            ObstacleAvoidanceController_B.c_A_l[c_ix] * smax;
          c_ix++;
        }
      }

      ix += 4;
      jA += 4;
    }
  }

  (void)memcpy(&Y[0], &b_A[0], (sizeof(real_T)) << 4U);
  for (d_j = 0; d_j < 4; d_j++) {
    c = d_j * 4;
    for (jA = 0; jA < d_j; jA++) {
      ix = jA * 4;
      smax = ObstacleAvoidanceController_B.c_A_l[jA + c];
      if (smax != 0.0) {
        Y[c] -= smax * Y[ix];
        Y[c + 1] -= smax * Y[ix + 1];
        Y[c + 2] -= smax * Y[ix + 2];
        Y[c + 3] -= smax * Y[ix + 3];
      }
    }

    smax = 1.0 / ObstacleAvoidanceController_B.c_A_l[d_j + c];
    Y[c] *= smax;
    Y[c + 1] *= smax;
    Y[c + 2] *= smax;
    Y[c + 3] *= smax;
  }

  for (d_j = 3; d_j >= 0; d_j--) {
    c = d_j * 4;
    for (jA = d_j + 2; jA < 5; jA++) {
      ix = (jA - 1) * 4;
      smax = ObstacleAvoidanceController_B.c_A_l[(jA + c) - 1];
      if (smax != 0.0) {
        Y[c] -= smax * Y[ix];
        Y[c + 1] -= smax * Y[ix + 1];
        Y[c + 2] -= smax * Y[ix + 2];
        Y[c + 3] -= smax * Y[ix + 3];
      }
    }
  }

  for (d_j = 2; d_j >= 0; d_j--) {
    ipiv_0 = ipiv[d_j];
    if ((d_j + 1) != ((int32_T)ipiv_0)) {
      c = d_j * 4;
      smax = Y[c];
      jA = (((int32_T)ipiv_0) - 1) * 4;
      Y[c] = Y[jA];
      Y[jA] = smax;
      smax = Y[c + 1];
      Y[c + 1] = Y[jA + 1];
      Y[jA + 1] = smax;
      smax = Y[c + 2];
      Y[c + 2] = Y[jA + 2];
      Y[jA + 2] = smax;
      smax = Y[c + 3];
      Y[c + 3] = Y[jA + 3];
      Y[jA + 3] = smax;
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_constraintcoef_HBE9OVn8(const real_T
  b_A[36], const real_T Bu[12], const real_T Bv[6], const real_T b_C[24], const
  real_T Dv[4], const real_T b_Jm[300], real_T b_SuJm[600], real_T b_Sx[360],
  real_T b_Su1[120], real_T b_Hv[960])
{
  real_T b_Su1_tmp_0;
  real_T b_Su1_tmp_1;
  real_T b_Su1_tmp_3;
  real_T b_Su1_tmp_4;
  int32_T CA_tmp;
  int32_T b_Hv_tmp;
  int32_T b_Su1_tmp;
  int32_T b_Su1_tmp_2;
  int32_T i_0;
  int8_T rows[4];
  int8_T i;
  for (i_0 = 0; i_0 < 4; i_0++) {
    for (b_Hv_tmp = 0; b_Hv_tmp < 6; b_Hv_tmp++) {
      CA_tmp = i_0 + (b_Hv_tmp * 4);
      ObstacleAvoidanceController_B.CA_g[CA_tmp] = 0.0;
      for (b_Su1_tmp_2 = 0; b_Su1_tmp_2 < 6; b_Su1_tmp_2++) {
        ObstacleAvoidanceController_B.CA_g[CA_tmp] += b_C[(b_Su1_tmp_2 * 4) +
          i_0] * b_A[(6 * b_Hv_tmp) + b_Su1_tmp_2];
      }
    }

    for (b_Hv_tmp = 0; b_Hv_tmp < 2; b_Hv_tmp++) {
      CA_tmp = i_0 + (b_Hv_tmp * 4);
      ObstacleAvoidanceController_B.Sum_h[CA_tmp] = 0.0;
      for (b_Su1_tmp_2 = 0; b_Su1_tmp_2 < 6; b_Su1_tmp_2++) {
        ObstacleAvoidanceController_B.Sum_h[CA_tmp] += b_C[(b_Su1_tmp_2 * 4) +
          i_0] * Bu[(6 * b_Hv_tmp) + b_Su1_tmp_2];
      }
    }

    ObstacleAvoidanceController_B.b_C_ju[i_0] = 0.0;
    for (b_Hv_tmp = 0; b_Hv_tmp < 6; b_Hv_tmp++) {
      ObstacleAvoidanceController_B.b_C_ju[i_0] += b_C[(b_Hv_tmp * 4) + i_0] *
        Bv[b_Hv_tmp];
    }

    b_Hv[i_0] = ObstacleAvoidanceController_B.b_C_ju[i_0];
    b_Hv[i_0 + 60] = Dv[i_0];
  }

  for (i_0 = 0; i_0 < 14; i_0++) {
    b_Hv_tmp = 60 * (i_0 + 2);
    b_Hv[b_Hv_tmp] = 0.0;
    b_Hv[b_Hv_tmp + 1] = 0.0;
    b_Hv[b_Hv_tmp + 2] = 0.0;
    b_Hv[b_Hv_tmp + 3] = 0.0;
  }

  for (i_0 = 0; i_0 < 16; i_0++) {
    (void)memset(&b_Hv[(i_0 * 60) + 4], 0, 56U * (sizeof(real_T)));
  }

  for (i_0 = 0; i_0 < 6; i_0++) {
    b_Hv_tmp = i_0 * 4;
    b_Sx[60 * i_0] = ObstacleAvoidanceController_B.CA_g[b_Hv_tmp];
    b_Sx[(60 * i_0) + 1] = ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 1];
    b_Sx[(60 * i_0) + 2] = ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 2];
    b_Sx[(60 * i_0) + 3] = ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 3];
    (void)memset(&b_Sx[(i_0 * 60) + 4], 0, 56U * (sizeof(real_T)));
  }

  for (i_0 = 0; i_0 < 2; i_0++) {
    b_Su1_tmp = i_0 * 4;
    b_Su1_tmp_0 = ObstacleAvoidanceController_B.Sum_h[b_Su1_tmp];
    b_Su1[60 * i_0] = b_Su1_tmp_0;
    b_Su1_tmp_1 = ObstacleAvoidanceController_B.Sum_h[b_Su1_tmp + 1];
    b_Su1_tmp_2 = (60 * i_0) + 1;
    b_Su1[b_Su1_tmp_2] = b_Su1_tmp_1;
    b_Su1_tmp_3 = ObstacleAvoidanceController_B.Sum_h[b_Su1_tmp + 2];
    CA_tmp = (60 * i_0) + 2;
    b_Su1[CA_tmp] = b_Su1_tmp_3;
    b_Su1_tmp_4 = ObstacleAvoidanceController_B.Sum_h[b_Su1_tmp + 3];
    b_Su1_tmp = (60 * i_0) + 3;
    b_Su1[b_Su1_tmp] = b_Su1_tmp_4;
    (void)memset(&b_Su1[(i_0 * 60) + 4], 0, 56U * (sizeof(real_T)));
    ObstacleAvoidanceController_B.Su[60 * i_0] = b_Su1_tmp_0;
    ObstacleAvoidanceController_B.Su[b_Su1_tmp_2] = b_Su1_tmp_1;
    ObstacleAvoidanceController_B.Su[CA_tmp] = b_Su1_tmp_3;
    ObstacleAvoidanceController_B.Su[b_Su1_tmp] = b_Su1_tmp_4;
  }

  for (i_0 = 0; i_0 < 28; i_0++) {
    b_Hv_tmp = 60 * (i_0 + 2);
    ObstacleAvoidanceController_B.Su[b_Hv_tmp] = 0.0;
    ObstacleAvoidanceController_B.Su[b_Hv_tmp + 1] = 0.0;
    ObstacleAvoidanceController_B.Su[b_Hv_tmp + 2] = 0.0;
    ObstacleAvoidanceController_B.Su[b_Hv_tmp + 3] = 0.0;
  }

  for (i_0 = 0; i_0 < 30; i_0++) {
    (void)memset(&ObstacleAvoidanceController_B.Su[(i_0 * 60) + 4], 0, 56U *
                 (sizeof(real_T)));
  }

  for (b_Su1_tmp = 0; b_Su1_tmp < 14; b_Su1_tmp++) {
    i = (int8_T)(((b_Su1_tmp + 1) * 4) + 1);
    for (i_0 = 0; i_0 < 4; i_0++) {
      rows[i_0] = (int8_T)(i_0 + ((int32_T)i));
      for (b_Hv_tmp = 0; b_Hv_tmp < 2; b_Hv_tmp++) {
        b_Su1_tmp_0 = 0.0;
        for (b_Su1_tmp_2 = 0; b_Su1_tmp_2 < 6; b_Su1_tmp_2++) {
          b_Su1_tmp_0 += ObstacleAvoidanceController_B.CA_g[(b_Su1_tmp_2 * 4) +
            i_0] * Bu[(6 * b_Hv_tmp) + b_Su1_tmp_2];
        }

        CA_tmp = (b_Hv_tmp * 4) + i_0;
        ObstacleAvoidanceController_B.Sum_h[CA_tmp] += b_Su1_tmp_0;
      }
    }

    for (i_0 = 0; i_0 < 2; i_0++) {
      CA_tmp = i_0 * 4;
      b_Su1_tmp_0 = ObstacleAvoidanceController_B.Sum_h[CA_tmp];
      b_Su1[(((int32_T)rows[0]) + (60 * i_0)) - 1] = b_Su1_tmp_0;
      ObstacleAvoidanceController_B.Sum[CA_tmp] = b_Su1_tmp_0;
      b_Su1_tmp_0 = ObstacleAvoidanceController_B.Sum_h[CA_tmp + 1];
      b_Su1[(((int32_T)rows[1]) + (60 * i_0)) - 1] = b_Su1_tmp_0;
      ObstacleAvoidanceController_B.Sum[CA_tmp + 1] = b_Su1_tmp_0;
      b_Su1_tmp_0 = ObstacleAvoidanceController_B.Sum_h[CA_tmp + 2];
      b_Su1[(((int32_T)rows[2]) + (60 * i_0)) - 1] = b_Su1_tmp_0;
      ObstacleAvoidanceController_B.Sum[CA_tmp + 2] = b_Su1_tmp_0;
      b_Su1_tmp_0 = ObstacleAvoidanceController_B.Sum_h[CA_tmp + 3];
      b_Su1[(((int32_T)rows[3]) + (60 * i_0)) - 1] = b_Su1_tmp_0;
      ObstacleAvoidanceController_B.Sum[CA_tmp + 3] = b_Su1_tmp_0;
    }

    for (i_0 = 0; i_0 < 28; i_0++) {
      CA_tmp = (i_0 + 2) * 4;
      ObstacleAvoidanceController_B.Sum[CA_tmp] =
        ObstacleAvoidanceController_B.Su[((60 * i_0) + ((int32_T)rows[0])) - 5];
      ObstacleAvoidanceController_B.Sum[CA_tmp + 1] =
        ObstacleAvoidanceController_B.Su[((60 * i_0) + ((int32_T)rows[1])) - 5];
      ObstacleAvoidanceController_B.Sum[CA_tmp + 2] =
        ObstacleAvoidanceController_B.Su[((60 * i_0) + ((int32_T)rows[2])) - 5];
      ObstacleAvoidanceController_B.Sum[CA_tmp + 3] =
        ObstacleAvoidanceController_B.Su[((60 * i_0) + ((int32_T)rows[3])) - 5];
    }

    for (i_0 = 0; i_0 < 30; i_0++) {
      b_Hv_tmp = i_0 * 4;
      ObstacleAvoidanceController_B.Su[(((int32_T)rows[0]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.Sum[b_Hv_tmp];
      ObstacleAvoidanceController_B.Su[(((int32_T)rows[1]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.Sum[b_Hv_tmp + 1];
      ObstacleAvoidanceController_B.Su[(((int32_T)rows[2]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.Sum[b_Hv_tmp + 2];
      ObstacleAvoidanceController_B.Su[(((int32_T)rows[3]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.Sum[b_Hv_tmp + 3];
    }

    for (i_0 = 0; i_0 < 4; i_0++) {
      ObstacleAvoidanceController_B.b_C_ju[i_0] = 0.0;
      for (b_Hv_tmp = 0; b_Hv_tmp < 6; b_Hv_tmp++) {
        ObstacleAvoidanceController_B.b_C_ju[i_0] +=
          ObstacleAvoidanceController_B.CA_g[(b_Hv_tmp * 4) + i_0] * Bv[b_Hv_tmp];
      }

      ObstacleAvoidanceController_B.CA[i_0] =
        ObstacleAvoidanceController_B.b_C_ju[i_0];
    }

    for (i_0 = 0; i_0 < 15; i_0++) {
      CA_tmp = (i_0 + 1) * 4;
      ObstacleAvoidanceController_B.CA[CA_tmp] = b_Hv[((60 * i_0) + ((int32_T)
        rows[0])) - 5];
      ObstacleAvoidanceController_B.CA[CA_tmp + 1] = b_Hv[((60 * i_0) +
        ((int32_T)rows[1])) - 5];
      ObstacleAvoidanceController_B.CA[CA_tmp + 2] = b_Hv[((60 * i_0) +
        ((int32_T)rows[2])) - 5];
      ObstacleAvoidanceController_B.CA[CA_tmp + 3] = b_Hv[((60 * i_0) +
        ((int32_T)rows[3])) - 5];
    }

    for (i_0 = 0; i_0 < 16; i_0++) {
      b_Hv_tmp = i_0 * 4;
      b_Hv[(((int32_T)rows[0]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA[b_Hv_tmp];
      b_Hv[(((int32_T)rows[1]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA[b_Hv_tmp + 1];
      b_Hv[(((int32_T)rows[2]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA[b_Hv_tmp + 2];
      b_Hv[(((int32_T)rows[3]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA[b_Hv_tmp + 3];
    }

    for (i_0 = 0; i_0 < 4; i_0++) {
      for (b_Hv_tmp = 0; b_Hv_tmp < 6; b_Hv_tmp++) {
        CA_tmp = i_0 + (b_Hv_tmp * 4);
        ObstacleAvoidanceController_B.CA_l[CA_tmp] = 0.0;
        for (b_Su1_tmp_2 = 0; b_Su1_tmp_2 < 6; b_Su1_tmp_2++) {
          ObstacleAvoidanceController_B.CA_l[CA_tmp] +=
            ObstacleAvoidanceController_B.CA_g[(b_Su1_tmp_2 * 4) + i_0] * b_A[(6
            * b_Hv_tmp) + b_Su1_tmp_2];
        }
      }
    }

    (void)memcpy(&ObstacleAvoidanceController_B.CA_g[0],
                 &ObstacleAvoidanceController_B.CA_l[0], 24U * (sizeof(real_T)));
    for (i_0 = 0; i_0 < 6; i_0++) {
      b_Hv_tmp = i_0 * 4;
      b_Sx[(((int32_T)rows[0]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA_g[b_Hv_tmp];
      b_Sx[(((int32_T)rows[1]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 1];
      b_Sx[(((int32_T)rows[2]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 2];
      b_Sx[(((int32_T)rows[3]) + (60 * i_0)) - 1] =
        ObstacleAvoidanceController_B.CA_g[b_Hv_tmp + 3];
    }
  }

  for (i_0 = 0; i_0 < 10; i_0++) {
    (void)memset(&b_SuJm[i_0 * 60], 0, 60U * (sizeof(real_T)));
    for (b_Su1_tmp_2 = 0; b_Su1_tmp_2 < 30; b_Su1_tmp_2++) {
      for (b_Hv_tmp = 0; b_Hv_tmp < 60; b_Hv_tmp++) {
        b_Su1_tmp = (60 * i_0) + b_Hv_tmp;
        b_SuJm[b_Su1_tmp] += ObstacleAvoidanceController_B.Su[(60 * b_Su1_tmp_2)
          + b_Hv_tmp] * b_Jm[(30 * i_0) + b_Su1_tmp_2];
      }
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_kron_h2HmpwPU(const real_T b_A[256],
  const real_T b_B[4], real_T K[1024])
{
  int32_T K_tmp;
  int32_T b_j1;
  int32_T i1;
  int32_T j2;
  int32_T kidx;
  kidx = -1;
  for (b_j1 = 0; b_j1 < 16; b_j1++) {
    for (j2 = 0; j2 < 2; j2++) {
      for (i1 = 0; i1 < 16; i1++) {
        K_tmp = j2 * 2;
        ObstacleAvoidanceController_B.K_tmp = b_A[(b_j1 * 16) + i1];
        K[kidx + 1] = ObstacleAvoidanceController_B.K_tmp * b_B[K_tmp];
        K[kidx + 2] = ObstacleAvoidanceController_B.K_tmp * b_B[K_tmp + 1];
        kidx += 2;
      }
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_customconstraintcoef_X8ClKd4y(const
  real_T b_SuJm[600], const real_T b_Sx[360], const real_T b_Su1[120], const
  real_T b_Hv[960], const real_T b_C[24], const real_T Dv[64], const real_T
  b_Jm[300], const real_T E[4], const real_T F[8], const real_T G[2], const
  real_T mvoff[2], const real_T b_yoff[4], real_T Mu[320], real_T b_Mv[512],
  real_T b_Mu1[64], real_T b_Mx[192], real_T b_Mlim[32])
{
  int32_T b_I1_tmp;
  int32_T b_i1;
  int32_T i1;
  int32_T j2;
  int32_T kidx;
  static const real_T b[256] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  ObstacleAvoidanceController_B.b_I[1] = 0.0;
  ObstacleAvoidanceController_B.b_I[2] = 0.0;
  ObstacleAvoidanceController_B.b_I[0] = 1.0;
  ObstacleAvoidanceController_B.b_I[3] = 1.0;
  kidx = -1;
  for (j2 = 0; j2 < 2; j2++) {
    for (i1 = 0; i1 < 16; i1++) {
      b_I1_tmp = j2 * 2;
      ObstacleAvoidanceController_B.b_I1_b[kidx + 1] = (int8_T)
        ObstacleAvoidanceController_B.b_I[b_I1_tmp];
      ObstacleAvoidanceController_B.b_I1_b[kidx + 2] = (int8_T)
        ObstacleAvoidanceController_B.b_I[b_I1_tmp + 1];
      kidx += 2;
    }
  }

  ObstacleAvoidanceController_B.b_I[1] = 0.0;
  ObstacleAvoidanceController_B.b_I[2] = 0.0;
  ObstacleAvoidanceController_B.b_I[0] = 1.0;
  ObstacleAvoidanceController_B.b_I[3] = 1.0;
  (void)memset(&ObstacleAvoidanceController_B.c_I[0], 0, (sizeof(real_T)) << 8U);
  for (kidx = 0; kidx < 16; kidx++) {
    ObstacleAvoidanceController_B.c_I[kidx + (kidx * 16)] = 1.0;
  }

  ObstacleAvoidanceController_kron_h2HmpwPU(ObstacleAvoidanceController_B.c_I, E,
    ObstacleAvoidanceController_B.Ep1);
  (void)memset(&ObstacleAvoidanceController_B.c_I[0], 0, (sizeof(real_T)) << 8U);
  for (kidx = 0; kidx < 16; kidx++) {
    ObstacleAvoidanceController_B.c_I[kidx + (kidx * 16)] = 1.0;
  }

  kidx = -1;
  for (j2 = 0; j2 < 16; j2++) {
    for (i1 = 0; i1 < 4; i1++) {
      for (b_i1 = 0; b_i1 < 16; b_i1++) {
        b_I1_tmp = i1 * 2;
        ObstacleAvoidanceController_B.Fp1_tmp =
          ObstacleAvoidanceController_B.c_I[(j2 * 16) + b_i1];
        ObstacleAvoidanceController_B.Fp1[kidx + 1] =
          ObstacleAvoidanceController_B.Fp1_tmp * F[b_I1_tmp];
        ObstacleAvoidanceController_B.Fp1[kidx + 2] =
          ObstacleAvoidanceController_B.Fp1_tmp * F[b_I1_tmp + 1];
        kidx += 2;
      }
    }
  }

  ObstacleAvoidanceController_kron_h2HmpwPU(b, ObstacleAvoidanceController_B.b_I,
    ObstacleAvoidanceController_B.Dv);
  for (kidx = 0; kidx < 10; kidx++) {
    (void)memcpy(&ObstacleAvoidanceController_B.b_Jm[kidx * 32], &b_Jm[kidx * 30],
                 30U * (sizeof(real_T)));
    b_I1_tmp = kidx * 32;
    ObstacleAvoidanceController_B.b_Jm[b_I1_tmp + 30] = 0.0;
    ObstacleAvoidanceController_B.b_Jm[b_I1_tmp + 31] = 0.0;
    (void)memset(&ObstacleAvoidanceController_B.dv2[b_I1_tmp], 0, (sizeof(real_T))
                 << 5U);
    for (i1 = 0; i1 < 32; i1++) {
      for (j2 = 0; j2 < 32; j2++) {
        b_i1 = (kidx * 32) + j2;
        ObstacleAvoidanceController_B.dv2[b_i1] +=
          ObstacleAvoidanceController_B.Dv[(i1 * 32) + j2] *
          ObstacleAvoidanceController_B.b_Jm[b_I1_tmp + i1];
      }
    }

    j2 = kidx * 64;
    ObstacleAvoidanceController_B.dv1[j2] = 0.0;
    ObstacleAvoidanceController_B.dv1[j2 + 1] = 0.0;
    ObstacleAvoidanceController_B.dv1[j2 + 2] = 0.0;
    ObstacleAvoidanceController_B.dv1[j2 + 3] = 0.0;
    (void)memcpy(&ObstacleAvoidanceController_B.dv1[j2 + 4], &b_SuJm[kidx * 60],
                 60U * (sizeof(real_T)));
  }

  for (kidx = 0; kidx < 10; kidx++) {
    (void)memset(&ObstacleAvoidanceController_B.b_Jm[kidx * 32], 0, (sizeof
      (real_T)) << 5U);
    for (i1 = 0; i1 < 32; i1++) {
      for (j2 = 0; j2 < 32; j2++) {
        b_I1_tmp = (kidx * 32) + j2;
        ObstacleAvoidanceController_B.b_Jm[b_I1_tmp] +=
          ObstacleAvoidanceController_B.Ep1[(i1 * 32) + j2] *
          ObstacleAvoidanceController_B.dv2[(kidx * 32) + i1];
      }
    }

    (void)memset(&ObstacleAvoidanceController_B.Fp1_c[kidx * 32], 0, (sizeof
      (real_T)) << 5U);
    for (i1 = 0; i1 < 64; i1++) {
      for (j2 = 0; j2 < 32; j2++) {
        b_I1_tmp = (kidx * 32) + j2;
        ObstacleAvoidanceController_B.Fp1_c[b_I1_tmp] +=
          ObstacleAvoidanceController_B.Fp1[(i1 * 32) + j2] *
          ObstacleAvoidanceController_B.dv1[(kidx * 64) + i1];
      }
    }
  }

  for (kidx = 0; kidx < 320; kidx++) {
    Mu[kidx] = ObstacleAvoidanceController_B.b_Jm[kidx] +
      ObstacleAvoidanceController_B.Fp1_c[kidx];
  }

  for (kidx = 0; kidx < 2048; kidx++) {
    ObstacleAvoidanceController_B.Fp1_m[kidx] =
      -ObstacleAvoidanceController_B.Fp1[kidx];
  }

  ObstacleAvoidanceController_B.Dv[0] = Dv[0];
  ObstacleAvoidanceController_B.Dv[1] = Dv[1];
  ObstacleAvoidanceController_B.Dv[2] = Dv[2];
  ObstacleAvoidanceController_B.Dv[3] = Dv[3];
  for (kidx = 0; kidx < 15; kidx++) {
    j2 = (kidx + 1) * 64;
    ObstacleAvoidanceController_B.Dv[j2] = 0.0;
    ObstacleAvoidanceController_B.Dv[j2 + 1] = 0.0;
    ObstacleAvoidanceController_B.Dv[j2 + 2] = 0.0;
    ObstacleAvoidanceController_B.Dv[j2 + 3] = 0.0;
  }

  for (kidx = 0; kidx < 16; kidx++) {
    (void)memcpy(&ObstacleAvoidanceController_B.Dv[(kidx * 64) + 4], &b_Hv[kidx *
                 60], 60U * (sizeof(real_T)));
  }

  for (kidx = 0; kidx < 32; kidx++) {
    for (j2 = 0; j2 < 16; j2++) {
      ObstacleAvoidanceController_B.Fp1_tmp = 0.0;
      for (i1 = 0; i1 < 64; i1++) {
        ObstacleAvoidanceController_B.Fp1_tmp +=
          ObstacleAvoidanceController_B.Fp1_m[(i1 * 32) + kidx] *
          ObstacleAvoidanceController_B.Dv[(j2 * 64) + i1];
      }

      b_Mv[kidx + (j2 * 32)] = ObstacleAvoidanceController_B.Fp1_tmp;
    }
  }

  for (kidx = 0; kidx < 2048; kidx++) {
    ObstacleAvoidanceController_B.Fp1_m[kidx] =
      -ObstacleAvoidanceController_B.Fp1[kidx];
  }

  for (kidx = 0; kidx < 6; kidx++) {
    j2 = kidx * 4;
    b_I1_tmp = kidx * 64;
    ObstacleAvoidanceController_B.b_C[b_I1_tmp] = b_C[j2];
    ObstacleAvoidanceController_B.b_C[b_I1_tmp + 1] = b_C[j2 + 1];
    ObstacleAvoidanceController_B.b_C[b_I1_tmp + 2] = b_C[j2 + 2];
    ObstacleAvoidanceController_B.b_C[b_I1_tmp + 3] = b_C[j2 + 3];
    (void)memcpy(&ObstacleAvoidanceController_B.b_C[b_I1_tmp + 4], &b_Sx[kidx *
                 60], 60U * (sizeof(real_T)));
    (void)memset(&b_Mx[kidx * 32], 0, (sizeof(real_T)) << 5U);
    for (i1 = 0; i1 < 64; i1++) {
      for (j2 = 0; j2 < 32; j2++) {
        b_i1 = (kidx * 32) + j2;
        b_Mx[b_i1] += ObstacleAvoidanceController_B.Fp1_m[(i1 * 32) + j2] *
          ObstacleAvoidanceController_B.b_C[b_I1_tmp + i1];
      }
    }
  }

  for (kidx = 0; kidx < 1024; kidx++) {
    ObstacleAvoidanceController_B.Dv[kidx] =
      -ObstacleAvoidanceController_B.Ep1[kidx];
  }

  for (kidx = 0; kidx < 2; kidx++) {
    j2 = kidx * 64;
    ObstacleAvoidanceController_B.dv4[j2] = 0.0;
    ObstacleAvoidanceController_B.dv4[j2 + 1] = 0.0;
    ObstacleAvoidanceController_B.dv4[j2 + 2] = 0.0;
    ObstacleAvoidanceController_B.dv4[j2 + 3] = 0.0;
    (void)memcpy(&ObstacleAvoidanceController_B.dv4[j2 + 4], &b_Su1[kidx * 60],
                 60U * (sizeof(real_T)));
  }

  for (kidx = 0; kidx < 2; kidx++) {
    for (j2 = 0; j2 < 32; j2++) {
      b_i1 = kidx * 32;
      b_I1_tmp = j2 + b_i1;
      ObstacleAvoidanceController_B.Ep1_g[b_I1_tmp] = 0.0;
      for (i1 = 0; i1 < 32; i1++) {
        ObstacleAvoidanceController_B.Ep1_g[b_I1_tmp] +=
          ObstacleAvoidanceController_B.Dv[(i1 * 32) + j2] * ((real_T)
          ObstacleAvoidanceController_B.b_I1_b[b_i1 + i1]);
      }

      ObstacleAvoidanceController_B.Fp1_g[b_I1_tmp] = 0.0;
      for (i1 = 0; i1 < 64; i1++) {
        ObstacleAvoidanceController_B.Fp1_g[b_I1_tmp] +=
          ObstacleAvoidanceController_B.Fp1[(i1 * 32) + j2] *
          ObstacleAvoidanceController_B.dv4[(kidx * 64) + i1];
      }
    }
  }

  for (kidx = 0; kidx < 64; kidx++) {
    b_Mu1[kidx] = ObstacleAvoidanceController_B.Ep1_g[kidx] -
      ObstacleAvoidanceController_B.Fp1_g[kidx];
  }

  for (kidx = 0; kidx < 2; kidx++) {
    ObstacleAvoidanceController_B.E_j[kidx] = (E[kidx + 2] * mvoff[1]) + (E[kidx]
      * mvoff[0]);
    ObstacleAvoidanceController_B.F_o[kidx] = (F[kidx + 6] * b_yoff[3]) +
      ((F[kidx + 4] * b_yoff[2]) + ((F[kidx + 2] * b_yoff[1]) + (F[kidx] *
         b_yoff[0])));
  }

  for (kidx = 0; kidx < 16; kidx++) {
    j2 = kidx * 2;
    ObstacleAvoidanceController_B.E[j2] = (ObstacleAvoidanceController_B.E_j[0]
      + ObstacleAvoidanceController_B.F_o[0]) - G[0];
    ObstacleAvoidanceController_B.E[j2 + 1] =
      (ObstacleAvoidanceController_B.E_j[1] + ObstacleAvoidanceController_B.F_o
       [1]) - G[1];
  }

  for (kidx = 0; kidx < 32; kidx++) {
    b_Mlim[kidx] = -ObstacleAvoidanceController_B.E[kidx];
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_calculatehessian_l89OAA4T(const
  real_T b_Wy[4], const real_T b_Wu[2], const real_T b_Wdu[2], const real_T
  b_SuJm[600], const real_T I2Jm[300], const real_T b_Jm[300], const real_T
  b_I1[60], const real_T b_Su1[120], const real_T b_Sx[360], const real_T b_Hv
  [960], real_T nmv, real_T b_ny, real_T b_H[100], real_T b_Ku1[20], real_T
  b_Kut[300], real_T b_Kx[60], real_T b_Kv[160], real_T b_Kr[600])
{
  real_T b_Wy_0;
  int32_T b_Kr_tmp;
  int32_T b_SuJm_tmp;
  int32_T i;
  int32_T i_0;
  int16_T ixw;
  ixw = 1;
  for (i = 0; i < 60; i++) {
    b_Wy_0 = b_Wy[ixw - 1];
    for (i_0 = 0; i_0 < 10; i_0++) {
      b_Kr_tmp = (60 * i_0) + i;
      b_Kr[b_Kr_tmp] = b_SuJm[b_Kr_tmp] * b_Wy_0;
    }

    i_0 = ((int32_T)ixw) + 1;
    if ((ixw + 1) > 32767) {
      i_0 = 32767;
    }

    ixw = (int16_T)i_0;
    if (((int16_T)i_0) > 4) {
      b_Wy_0 = rt_roundd_snf(4.0 - b_ny);
      if (b_Wy_0 < 32768.0) {
        if (b_Wy_0 >= -32768.0) {
          ixw = (int16_T)b_Wy_0;
        } else {
          ixw = MIN_int16_T;
        }
      } else {
        ixw = MAX_int16_T;
      }

      i_0 = ((int32_T)ixw) + 1;
      if (b_Wy_0 < 32768.0) {
        if (b_Wy_0 >= -32768.0) {
          ixw = (int16_T)b_Wy_0;
        } else {
          ixw = MIN_int16_T;
        }
      } else {
        ixw = MAX_int16_T;
      }

      if ((ixw + 1) > 32767) {
        i_0 = 32767;
      }

      ixw = (int16_T)i_0;
    }
  }

  WtMult_9ptEzcS9(b_Wu, I2Jm, nmv, b_Kut);
  WtMult_9ptEzcS9(b_Wdu, b_Jm, nmv, ObstacleAvoidanceController_B.dv3);
  for (i_0 = 0; i_0 < 10; i_0++) {
    for (i = 0; i < 10; i++) {
      b_SuJm_tmp = i + (10 * i_0);
      ObstacleAvoidanceController_B.b_SuJm[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 60; b_Kr_tmp++) {
        ObstacleAvoidanceController_B.b_SuJm[b_SuJm_tmp] += b_SuJm[(60 * i) +
          b_Kr_tmp] * b_Kr[(60 * i_0) + b_Kr_tmp];
      }

      ObstacleAvoidanceController_B.b_Jm_c[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 30; b_Kr_tmp++) {
        ObstacleAvoidanceController_B.b_Jm_c[b_SuJm_tmp] += b_Jm[(30 * i) +
          b_Kr_tmp] * ObstacleAvoidanceController_B.dv3[(30 * i_0) + b_Kr_tmp];
      }
    }
  }

  for (i_0 = 0; i_0 < 10; i_0++) {
    for (i = 0; i < 10; i++) {
      b_Wy_0 = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 30; b_Kr_tmp++) {
        b_Wy_0 += I2Jm[(30 * i_0) + b_Kr_tmp] * b_Kut[(30 * i) + b_Kr_tmp];
      }

      b_Kr_tmp = (10 * i) + i_0;
      b_H[b_Kr_tmp] = (ObstacleAvoidanceController_B.b_SuJm[b_Kr_tmp] +
                       ObstacleAvoidanceController_B.b_Jm_c[b_Kr_tmp]) + b_Wy_0;
    }
  }

  for (i_0 = 0; i_0 < 2; i_0++) {
    for (i = 0; i < 10; i++) {
      b_SuJm_tmp = i_0 + (i * 2);
      ObstacleAvoidanceController_B.b_Su1[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 60; b_Kr_tmp++) {
        ObstacleAvoidanceController_B.b_Su1[b_SuJm_tmp] += b_Su1[(60 * i_0) +
          b_Kr_tmp] * b_Kr[(60 * i) + b_Kr_tmp];
      }

      ObstacleAvoidanceController_B.b_I1[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 30; b_Kr_tmp++) {
        ObstacleAvoidanceController_B.b_I1[b_SuJm_tmp] += b_I1[(30 * i_0) +
          b_Kr_tmp] * b_Kut[(30 * i) + b_Kr_tmp];
      }
    }
  }

  for (i_0 = 0; i_0 < 20; i_0++) {
    b_Ku1[i_0] = ObstacleAvoidanceController_B.b_Su1[i_0] +
      ObstacleAvoidanceController_B.b_I1[i_0];
  }

  for (i_0 = 0; i_0 < 300; i_0++) {
    b_Kut[i_0] = -b_Kut[i_0];
  }

  for (i_0 = 0; i_0 < 10; i_0++) {
    for (i = 0; i < 6; i++) {
      b_SuJm_tmp = i + (6 * i_0);
      b_Kx[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 60; b_Kr_tmp++) {
        b_Kx[b_SuJm_tmp] += b_Sx[(60 * i) + b_Kr_tmp] * b_Kr[(60 * i_0) +
          b_Kr_tmp];
      }
    }

    for (i = 0; i < 16; i++) {
      b_SuJm_tmp = i + (i_0 * 16);
      b_Kv[b_SuJm_tmp] = 0.0;
      for (b_Kr_tmp = 0; b_Kr_tmp < 60; b_Kr_tmp++) {
        b_Kv[b_SuJm_tmp] += b_Hv[(60 * i) + b_Kr_tmp] * b_Kr[(60 * i_0) +
          b_Kr_tmp];
      }
    }
  }

  for (i_0 = 0; i_0 < 600; i_0++) {
    b_Kr[i_0] = -b_Kr[i_0];
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_checkhessian_zJaLOdRx(real_T b_H[121],
  real_T L[121], real_T *BadH)
{
  int32_T Tries;
  int32_T j;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *BadH = 0.0;
  (void)memcpy(&L[0], &b_H[0], 121U * (sizeof(real_T)));
  Tries = xpotrf_wTXxIm7P(L);
  guard1 = false;
  if (Tries == 0) {
    for (Tries = 0; Tries < 11; Tries++) {
      ObstacleAvoidanceController_B.varargin_1[Tries] = L[(11 * Tries) + Tries];
    }

    if (minimum_t5zjUC2Z(ObstacleAvoidanceController_B.varargin_1) >
        1.4901161193847656E-7) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    ObstacleAvoidanceController_B.normH = 0.0;
    Tries = 0;
    exitg2 = false;
    while ((!exitg2) && (Tries < 11)) {
      ObstacleAvoidanceController_B.s = 0.0;
      for (j = 0; j < 11; j++) {
        ObstacleAvoidanceController_B.s += fabs(b_H[(11 * j) + Tries]);
      }

      if (rtIsNaN(ObstacleAvoidanceController_B.s)) {
        ObstacleAvoidanceController_B.normH = (rtNaN);
        exitg2 = true;
      } else {
        if (ObstacleAvoidanceController_B.s >
            ObstacleAvoidanceController_B.normH) {
          ObstacleAvoidanceController_B.normH = ObstacleAvoidanceController_B.s;
        }

        Tries++;
      }
    }

    if (ObstacleAvoidanceController_B.normH >= 1.0E+10) {
      *BadH = 2.0;
    } else {
      Tries = 0;
      exitg1 = false;
      while ((!exitg1) && (Tries <= 4)) {
        ObstacleAvoidanceController_B.normH = rt_powd_snf(10.0, (real_T)Tries) *
          1.4901161193847656E-7;
        (void)memset(&ObstacleAvoidanceController_B.b_b[0], 0, 121U * (sizeof
          (int8_T)));
        for (j = 0; j < 11; j++) {
          ObstacleAvoidanceController_B.b_b[j + (11 * j)] = 1;
        }

        for (j = 0; j < 121; j++) {
          ObstacleAvoidanceController_B.s = (ObstacleAvoidanceController_B.normH
            * ((real_T)ObstacleAvoidanceController_B.b_b[j])) + b_H[j];
          L[j] = ObstacleAvoidanceController_B.s;
          b_H[j] = ObstacleAvoidanceController_B.s;
        }

        j = xpotrf_wTXxIm7P(L);
        guard2 = false;
        if (j == 0) {
          for (j = 0; j < 11; j++) {
            ObstacleAvoidanceController_B.varargin_1[j] = L[(11 * j) + j];
          }

          if (minimum_t5zjUC2Z(ObstacleAvoidanceController_B.varargin_1) >
              1.4901161193847656E-7) {
            *BadH = 1.0;
            exitg1 = true;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          *BadH = 3.0;
          Tries++;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static real_T ObstacleAvoidanceController_xnrm2_GjDYLhOh(int32_T n, const real_T
  x[121], int32_T ix0)
{
  real_T absxk;
  real_T t;
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      ObstacleAvoidanceController_B.scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > ObstacleAvoidanceController_B.scale) {
          t = ObstacleAvoidanceController_B.scale / absxk;
          y = ((y * t) * t) + 1.0;
          ObstacleAvoidanceController_B.scale = absxk;
        } else {
          t = absxk / ObstacleAvoidanceController_B.scale;
          y += t * t;
        }
      }

      y = ObstacleAvoidanceController_B.scale * sqrt(y);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_xgemv_2GgNT4xY(int32_T b_m, int32_T n,
  const real_T b_A[121], int32_T ia0, const real_T x[121], int32_T ix0, real_T
  y[11])
{
  int32_T b;
  int32_T b_iy;
  int32_T d;
  int32_T ia;
  int32_T iac;
  int32_T ix;
  if ((b_m != 0) && (n != 0)) {
    for (b_iy = 0; b_iy < n; b_iy++) {
      y[b_iy] = 0.0;
    }

    b_iy = 0;
    b = ((n - 1) * 11) + ia0;
    for (iac = ia0; iac <= b; iac += 11) {
      ix = ix0;
      ObstacleAvoidanceController_B.c = 0.0;
      d = (iac + b_m) - 1;
      for (ia = iac; ia <= d; ia++) {
        ObstacleAvoidanceController_B.c += b_A[ia - 1] * x[ix - 1];
        ix++;
      }

      y[b_iy] += ObstacleAvoidanceController_B.c;
      b_iy++;
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_xgerc_UQHWFbLL(int32_T b_m, int32_T n,
  real_T alpha1, int32_T ix0, const real_T y[11], real_T b_A[121], int32_T ia0)
{
  int32_T b;
  int32_T ijA;
  int32_T ix;
  int32_T j;
  int32_T jA;
  int32_T jy;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 0; j < n; j++) {
      if (y[jy] != 0.0) {
        ObstacleAvoidanceController_B.temp = y[jy] * alpha1;
        ix = ix0;
        b = b_m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          b_A[ijA] += b_A[ix - 1] * ObstacleAvoidanceController_B.temp;
          ix++;
        }
      }

      jy++;
      jA += 11;
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_qrf_Bv1QUViS(real_T b_A[121], int32_T
  ia0, int32_T b_m, int32_T n, int32_T nfxd, real_T tau[11])
{
  int32_T b_k;
  int32_T coltop;
  int32_T exitg1;
  int32_T i;
  int32_T lastv;
  boolean_T exitg2;
  (void)memset(&ObstacleAvoidanceController_B.work[0], 0, 11U * (sizeof(real_T)));
  for (i = 0; i < nfxd; i++) {
    ObstacleAvoidanceController_B.ii = (((i * 11) + ia0) + i) - 1;
    lastv = b_m - i;
    if ((i + 1) < b_m) {
      ObstacleAvoidanceController_B.b_atmp =
        b_A[ObstacleAvoidanceController_B.ii];
      tau[i] = 0.0;
      if (lastv > 0) {
        ObstacleAvoidanceController_B.beta1 =
          ObstacleAvoidanceController_xnrm2_GjDYLhOh(lastv - 1, b_A,
          ObstacleAvoidanceController_B.ii + 2);
        if (ObstacleAvoidanceController_B.beta1 != 0.0) {
          ObstacleAvoidanceController_B.beta1 = rt_hypotd_snf
            (b_A[ObstacleAvoidanceController_B.ii],
             ObstacleAvoidanceController_B.beta1);
          if (b_A[ObstacleAvoidanceController_B.ii] >= 0.0) {
            ObstacleAvoidanceController_B.beta1 =
              -ObstacleAvoidanceController_B.beta1;
          }

          if (fabs(ObstacleAvoidanceController_B.beta1) <
              1.0020841800044864E-292) {
            ObstacleAvoidanceController_B.knt = -1;
            coltop = ObstacleAvoidanceController_B.ii + lastv;
            do {
              ObstacleAvoidanceController_B.knt++;
              for (b_k = ObstacleAvoidanceController_B.ii + 1; b_k < coltop; b_k
                   ++) {
                b_A[b_k] *= 9.9792015476736E+291;
              }

              ObstacleAvoidanceController_B.beta1 *= 9.9792015476736E+291;
              ObstacleAvoidanceController_B.b_atmp *= 9.9792015476736E+291;
            } while (!(fabs(ObstacleAvoidanceController_B.beta1) >=
                       1.0020841800044864E-292));

            ObstacleAvoidanceController_B.beta1 = rt_hypotd_snf
              (ObstacleAvoidanceController_B.b_atmp,
               ObstacleAvoidanceController_xnrm2_GjDYLhOh(lastv - 1, b_A,
                ObstacleAvoidanceController_B.ii + 2));
            if (ObstacleAvoidanceController_B.b_atmp >= 0.0) {
              ObstacleAvoidanceController_B.beta1 =
                -ObstacleAvoidanceController_B.beta1;
            }

            tau[i] = (ObstacleAvoidanceController_B.beta1 -
                      ObstacleAvoidanceController_B.b_atmp) /
              ObstacleAvoidanceController_B.beta1;
            ObstacleAvoidanceController_B.b_atmp = 1.0 /
              (ObstacleAvoidanceController_B.b_atmp -
               ObstacleAvoidanceController_B.beta1);
            for (b_k = ObstacleAvoidanceController_B.ii + 1; b_k < coltop; b_k++)
            {
              b_A[b_k] *= ObstacleAvoidanceController_B.b_atmp;
            }

            for (coltop = 0; coltop <= ObstacleAvoidanceController_B.knt; coltop
                 ++) {
              ObstacleAvoidanceController_B.beta1 *= 1.0020841800044864E-292;
            }

            ObstacleAvoidanceController_B.b_atmp =
              ObstacleAvoidanceController_B.beta1;
          } else {
            tau[i] = (ObstacleAvoidanceController_B.beta1 -
                      b_A[ObstacleAvoidanceController_B.ii]) /
              ObstacleAvoidanceController_B.beta1;
            ObstacleAvoidanceController_B.b_atmp = 1.0 /
              (b_A[ObstacleAvoidanceController_B.ii] -
               ObstacleAvoidanceController_B.beta1);
            ObstacleAvoidanceController_B.knt = ObstacleAvoidanceController_B.ii
              + lastv;
            for (coltop = ObstacleAvoidanceController_B.ii + 1; coltop <
                 ObstacleAvoidanceController_B.knt; coltop++) {
              b_A[coltop] *= ObstacleAvoidanceController_B.b_atmp;
            }

            ObstacleAvoidanceController_B.b_atmp =
              ObstacleAvoidanceController_B.beta1;
          }
        }
      }

      b_A[ObstacleAvoidanceController_B.ii] =
        ObstacleAvoidanceController_B.b_atmp;
    } else {
      tau[i] = 0.0;
    }

    if ((i + 1) < n) {
      ObstacleAvoidanceController_B.b_atmp =
        b_A[ObstacleAvoidanceController_B.ii];
      b_A[ObstacleAvoidanceController_B.ii] = 1.0;
      if (tau[i] != 0.0) {
        ObstacleAvoidanceController_B.knt = (ObstacleAvoidanceController_B.ii +
          lastv) - 1;
        while ((lastv > 0) && (b_A[ObstacleAvoidanceController_B.knt] == 0.0)) {
          lastv--;
          ObstacleAvoidanceController_B.knt--;
        }

        ObstacleAvoidanceController_B.knt = (n - i) - 1;
        exitg2 = false;
        while ((!exitg2) && (ObstacleAvoidanceController_B.knt > 0)) {
          coltop = (((ObstacleAvoidanceController_B.knt - 1) * 11) +
                    ObstacleAvoidanceController_B.ii) + 11;
          b_k = coltop;
          do {
            exitg1 = 0;
            if ((b_k + 1) <= (coltop + lastv)) {
              if (b_A[b_k] != 0.0) {
                exitg1 = 1;
              } else {
                b_k++;
              }
            } else {
              ObstacleAvoidanceController_B.knt--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        ObstacleAvoidanceController_B.knt = 0;
      }

      if (lastv > 0) {
        ObstacleAvoidanceController_xgemv_2GgNT4xY(lastv,
          ObstacleAvoidanceController_B.knt, b_A,
          ObstacleAvoidanceController_B.ii + 12, b_A,
          ObstacleAvoidanceController_B.ii + 1,
          ObstacleAvoidanceController_B.work);
        ObstacleAvoidanceController_xgerc_UQHWFbLL(lastv,
          ObstacleAvoidanceController_B.knt, -tau[i],
          ObstacleAvoidanceController_B.ii + 1,
          ObstacleAvoidanceController_B.work, b_A,
          ObstacleAvoidanceController_B.ii + 12);
      }

      b_A[ObstacleAvoidanceController_B.ii] =
        ObstacleAvoidanceController_B.b_atmp;
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_xgeqrf_iz011iUO(real_T b_A[121], real_T
  tau[11])
{
  (void)memset(&tau[0], 0, 11U * (sizeof(real_T)));
  ObstacleAvoidanceController_qrf_Bv1QUViS(b_A, 1, 11, 11, 11, tau);
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_xorgqr_BxYGaI4b(int32_T b_m, int32_T n,
  int32_T k, real_T b_A[121], int32_T ia0, const real_T tau[11], int32_T itau0)
{
  int32_T b_ia;
  int32_T coltop;
  int32_T exitg1;
  int32_T i;
  int32_T lastc;
  boolean_T exitg2;
  if (n >= 1) {
    for (i = k; i < n; i++) {
      ObstacleAvoidanceController_B.itau = ((i * 11) + ia0) - 1;
      ObstacleAvoidanceController_B.iaii = 0;
      while (ObstacleAvoidanceController_B.iaii <= (b_m - 1)) {
        b_A[ObstacleAvoidanceController_B.itau +
          ObstacleAvoidanceController_B.iaii] = 0.0;
        ObstacleAvoidanceController_B.iaii++;
      }

      b_A[ObstacleAvoidanceController_B.itau + i] = 1.0;
    }

    ObstacleAvoidanceController_B.itau = (itau0 + k) - 2;
    (void)memset(&ObstacleAvoidanceController_B.work_n[0], 0, 11U * (sizeof
      (real_T)));
    for (i = k; i >= 1; i--) {
      ObstacleAvoidanceController_B.iaii = ((((i - 1) * 11) + ia0) + i) - 1;
      if (i < n) {
        b_A[ObstacleAvoidanceController_B.iaii - 1] = 1.0;
        lastc = (b_m - i) - 1;
        if (tau[ObstacleAvoidanceController_B.itau] != 0.0) {
          ObstacleAvoidanceController_B.lastv = lastc + 2;
          lastc += ObstacleAvoidanceController_B.iaii;
          while ((ObstacleAvoidanceController_B.lastv > 0) && (b_A[lastc] == 0.0))
          {
            ObstacleAvoidanceController_B.lastv--;
            lastc--;
          }

          lastc = n - i;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            coltop = (((lastc - 1) * 11) + ObstacleAvoidanceController_B.iaii) +
              10;
            b_ia = coltop;
            do {
              exitg1 = 0;
              if ((b_ia + 1) <= (coltop + ObstacleAvoidanceController_B.lastv))
              {
                if (b_A[b_ia] != 0.0) {
                  exitg1 = 1;
                } else {
                  b_ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          ObstacleAvoidanceController_B.lastv = 0;
          lastc = 0;
        }

        if (ObstacleAvoidanceController_B.lastv > 0) {
          ObstacleAvoidanceController_xgemv_2GgNT4xY
            (ObstacleAvoidanceController_B.lastv, lastc, b_A,
             ObstacleAvoidanceController_B.iaii + 11, b_A,
             ObstacleAvoidanceController_B.iaii,
             ObstacleAvoidanceController_B.work_n);
          ObstacleAvoidanceController_xgerc_UQHWFbLL
            (ObstacleAvoidanceController_B.lastv, lastc,
             -tau[ObstacleAvoidanceController_B.itau],
             ObstacleAvoidanceController_B.iaii,
             ObstacleAvoidanceController_B.work_n, b_A,
             ObstacleAvoidanceController_B.iaii + 11);
        }
      }

      if (i < b_m) {
        ObstacleAvoidanceController_B.lastv =
          (ObstacleAvoidanceController_B.iaii + b_m) - i;
        for (lastc = ObstacleAvoidanceController_B.iaii; lastc <
             ObstacleAvoidanceController_B.lastv; lastc++) {
          b_A[lastc] *= -tau[ObstacleAvoidanceController_B.itau];
        }
      }

      b_A[ObstacleAvoidanceController_B.iaii - 1] = 1.0 -
        tau[ObstacleAvoidanceController_B.itau];
      ObstacleAvoidanceController_B.lastv = 0;
      while (ObstacleAvoidanceController_B.lastv <= (i - 2)) {
        b_A[(ObstacleAvoidanceController_B.iaii -
             ObstacleAvoidanceController_B.lastv) - 2] = 0.0;
        ObstacleAvoidanceController_B.lastv++;
      }

      ObstacleAvoidanceController_B.itau--;
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_qr_m3UlPv27(const real_T b_A[121],
  real_T Q[121], real_T R[121])
{
  (void)memcpy(&ObstacleAvoidanceController_B.c_A[0], &b_A[0], 121U * (sizeof
    (real_T)));
  ObstacleAvoidanceController_xgeqrf_iz011iUO(ObstacleAvoidanceController_B.c_A,
    ObstacleAvoidanceController_B.tau);
  for (ObstacleAvoidanceController_B.j_j = 0; ObstacleAvoidanceController_B.j_j <
       11; ObstacleAvoidanceController_B.j_j++) {
    ObstacleAvoidanceController_B.i_h = 0;
    while (ObstacleAvoidanceController_B.i_h <=
           ObstacleAvoidanceController_B.j_j) {
      R[ObstacleAvoidanceController_B.i_h + (11 *
        ObstacleAvoidanceController_B.j_j)] = ObstacleAvoidanceController_B.c_A
        [(11 * ObstacleAvoidanceController_B.j_j) +
        ObstacleAvoidanceController_B.i_h];
      ObstacleAvoidanceController_B.i_h++;
    }

    ObstacleAvoidanceController_B.i_h = ObstacleAvoidanceController_B.j_j + 1;
    while ((ObstacleAvoidanceController_B.i_h + 1) < 12) {
      R[ObstacleAvoidanceController_B.i_h + (11 *
        ObstacleAvoidanceController_B.j_j)] = 0.0;
      ObstacleAvoidanceController_B.i_h++;
    }
  }

  ObstacleAvoidanceController_xorgqr_BxYGaI4b(11, 11, 11,
    ObstacleAvoidanceController_B.c_A, 1, ObstacleAvoidanceController_B.tau, 1);
  for (ObstacleAvoidanceController_B.j_j = 0; ObstacleAvoidanceController_B.j_j <
       11; ObstacleAvoidanceController_B.j_j++) {
    (void)memcpy(&Q[ObstacleAvoidanceController_B.j_j * 11],
                 &ObstacleAvoidanceController_B.c_A[ObstacleAvoidanceController_B.j_j
                 * 11], 11U * (sizeof(real_T)));
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static real_T ObstacleAvoidanceController_KWIKfactor_lFdJjicy(const real_T b_Ac
  [957], const int16_T iC[87], int16_T nA, const real_T b_Linv[121], real_T
  RLinv[121], real_T b_D[121], real_T b_H[121], int16_T n)
{
  real_T Status;
  int32_T exitg1;
  int16_T b_j;
  int16_T c_k;
  Status = 1.0;
  (void)memset(&RLinv[0], 0, 121U * (sizeof(real_T)));
  ObstacleAvoidanceController_B.i_c = 1;
  while ((ObstacleAvoidanceController_B.i_c - 1) <= (((int32_T)nA) - 1)) {
    ObstacleAvoidanceController_B.iC_m = (int32_T)iC[((int16_T)
      ObstacleAvoidanceController_B.i_c) - 1];
    for (ObstacleAvoidanceController_B.b_i_m = 0;
         ObstacleAvoidanceController_B.b_i_m < 11;
         ObstacleAvoidanceController_B.b_i_m++) {
      ObstacleAvoidanceController_B.c_i = ObstacleAvoidanceController_B.b_i_m +
        (11 * (((int32_T)((int16_T)ObstacleAvoidanceController_B.i_c)) - 1));
      RLinv[ObstacleAvoidanceController_B.c_i] = 0.0;
      for (ObstacleAvoidanceController_B.e_i = 0;
           ObstacleAvoidanceController_B.e_i < 11;
           ObstacleAvoidanceController_B.e_i++) {
        RLinv[ObstacleAvoidanceController_B.c_i] += b_Ac[((87 *
          ObstacleAvoidanceController_B.e_i) +
          ObstacleAvoidanceController_B.iC_m) - 1] * b_Linv[(11 *
          ObstacleAvoidanceController_B.e_i) +
          ObstacleAvoidanceController_B.b_i_m];
      }
    }

    ObstacleAvoidanceController_B.i_c++;
  }

  ObstacleAvoidanceController_qr_m3UlPv27(RLinv,
    ObstacleAvoidanceController_B.QQ, ObstacleAvoidanceController_B.RR);
  ObstacleAvoidanceController_B.b_i_m = 1;
  do {
    exitg1 = 0;
    if ((ObstacleAvoidanceController_B.b_i_m - 1) <= (((int32_T)nA) - 1)) {
      if (fabs(ObstacleAvoidanceController_B.RR[(((((int16_T)
               ObstacleAvoidanceController_B.b_i_m) - 1) * 11) + ((int16_T)
             ObstacleAvoidanceController_B.b_i_m)) - 1]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        ObstacleAvoidanceController_B.b_i_m++;
      }
    } else {
      ObstacleAvoidanceController_B.c_i = 1;
      while ((ObstacleAvoidanceController_B.c_i - 1) <= (((int32_T)n) - 1)) {
        ObstacleAvoidanceController_B.e_i = 1;
        while ((ObstacleAvoidanceController_B.e_i - 1) <= (((int32_T)n) - 1)) {
          ObstacleAvoidanceController_B.b_Linv = 0.0;
          for (ObstacleAvoidanceController_B.b_i_m = 0;
               ObstacleAvoidanceController_B.b_i_m < 11;
               ObstacleAvoidanceController_B.b_i_m++) {
            ObstacleAvoidanceController_B.b_Linv += b_Linv[((((int32_T)((int16_T)
              ObstacleAvoidanceController_B.c_i)) - 1) * 11) +
              ObstacleAvoidanceController_B.b_i_m] *
              ObstacleAvoidanceController_B.QQ[((((int32_T)((int16_T)
              ObstacleAvoidanceController_B.e_i)) - 1) * 11) +
              ObstacleAvoidanceController_B.b_i_m];
          }

          ObstacleAvoidanceController_B.TL[(((int16_T)
            ObstacleAvoidanceController_B.c_i) + (11 * (((int16_T)
            ObstacleAvoidanceController_B.e_i) - 1))) - 1] =
            ObstacleAvoidanceController_B.b_Linv;
          ObstacleAvoidanceController_B.e_i++;
        }

        ObstacleAvoidanceController_B.c_i++;
      }

      (void)memset(&RLinv[0], 0, 121U * (sizeof(real_T)));
      for (b_j = nA; b_j > 0; b_j--) {
        ObstacleAvoidanceController_B.b_i_m = 11 * (((int32_T)b_j) - 1);
        ObstacleAvoidanceController_B.c_i = (((int32_T)b_j) +
          ObstacleAvoidanceController_B.b_i_m) - 1;
        RLinv[ObstacleAvoidanceController_B.c_i] = 1.0;
        for (c_k = b_j; c_k <= nA; c_k++) {
          ObstacleAvoidanceController_B.e_i = (((((int32_T)c_k) - 1) * 11) +
            ((int32_T)b_j)) - 1;
          RLinv[ObstacleAvoidanceController_B.e_i] /=
            ObstacleAvoidanceController_B.RR[ObstacleAvoidanceController_B.c_i];
        }

        if (b_j > 1) {
          ObstacleAvoidanceController_B.i_c = 1;
          while ((ObstacleAvoidanceController_B.i_c - 1) <= (((int32_T)b_j) - 2))
          {
            for (c_k = b_j; c_k <= nA; c_k++) {
              ObstacleAvoidanceController_B.c_i = (((int32_T)c_k) - 1) * 11;
              ObstacleAvoidanceController_B.e_i =
                (ObstacleAvoidanceController_B.c_i + ((int32_T)((int16_T)
                   ObstacleAvoidanceController_B.i_c))) - 1;
              RLinv[ObstacleAvoidanceController_B.e_i] -=
                ObstacleAvoidanceController_B.RR
                [(ObstacleAvoidanceController_B.b_i_m + ((int32_T)((int16_T)
                    ObstacleAvoidanceController_B.i_c))) - 1] * RLinv
                [(ObstacleAvoidanceController_B.c_i + ((int32_T)b_j)) - 1];
            }

            ObstacleAvoidanceController_B.i_c++;
          }
        }
      }

      ObstacleAvoidanceController_B.e_i = 1;
      while ((ObstacleAvoidanceController_B.e_i - 1) <= (((int32_T)n) - 1)) {
        for (b_j = (int16_T)ObstacleAvoidanceController_B.e_i; b_j <= n; b_j++)
        {
          ObstacleAvoidanceController_B.b_i_m = (((int32_T)((int16_T)
            ObstacleAvoidanceController_B.e_i)) + (11 * (((int32_T)b_j) - 1))) -
            1;
          b_H[ObstacleAvoidanceController_B.b_i_m] = 0.0;
          ObstacleAvoidanceController_B.c_i = ((int32_T)nA) + 1;
          if ((nA + 1) > 32767) {
            ObstacleAvoidanceController_B.c_i = 32767;
          }

          for (c_k = (int16_T)ObstacleAvoidanceController_B.c_i; c_k <= n; c_k++)
          {
            ObstacleAvoidanceController_B.c_i = (((int32_T)c_k) - 1) * 11;
            b_H[ObstacleAvoidanceController_B.b_i_m] -=
              ObstacleAvoidanceController_B.TL
              [(ObstacleAvoidanceController_B.c_i + ((int32_T)((int16_T)
                  ObstacleAvoidanceController_B.e_i))) - 1] *
              ObstacleAvoidanceController_B.TL
              [(ObstacleAvoidanceController_B.c_i + ((int32_T)b_j)) - 1];
          }

          b_H[(b_j + (11 * (((int16_T)ObstacleAvoidanceController_B.e_i) - 1)))
            - 1] = b_H[ObstacleAvoidanceController_B.b_i_m];
        }

        ObstacleAvoidanceController_B.e_i++;
      }

      ObstacleAvoidanceController_B.e_i = 1;
      while ((ObstacleAvoidanceController_B.e_i - 1) <= (((int32_T)nA) - 1)) {
        ObstacleAvoidanceController_B.i_c = 1;
        while ((ObstacleAvoidanceController_B.i_c - 1) <= (((int32_T)n) - 1)) {
          ObstacleAvoidanceController_B.b_i_m = (((int32_T)((int16_T)
            ObstacleAvoidanceController_B.i_c)) + (11 * (((int32_T)((int16_T)
            ObstacleAvoidanceController_B.e_i)) - 1))) - 1;
          b_D[ObstacleAvoidanceController_B.b_i_m] = 0.0;
          for (b_j = (int16_T)ObstacleAvoidanceController_B.e_i; b_j <= nA; b_j
               ++) {
            ObstacleAvoidanceController_B.c_i = (((int32_T)b_j) - 1) * 11;
            b_D[ObstacleAvoidanceController_B.b_i_m] +=
              ObstacleAvoidanceController_B.TL
              [(ObstacleAvoidanceController_B.c_i + ((int32_T)((int16_T)
                  ObstacleAvoidanceController_B.i_c))) - 1] * RLinv
              [(ObstacleAvoidanceController_B.c_i + ((int32_T)((int16_T)
                  ObstacleAvoidanceController_B.e_i))) - 1];
          }

          ObstacleAvoidanceController_B.i_c++;
        }

        ObstacleAvoidanceController_B.e_i++;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_qpkwik_XjF1fpUJ(const real_T b_Linv[121],
  const real_T b_Hinv[121], const real_T f[11], const real_T b_Ac[957], const
  real_T b[87], int16_T iA[87], int16_T maxiter, real_T FeasTol, real_T x[11],
  real_T lambda[87], real_T *status)
{
  int32_T exitg1;
  int32_T exitg3;
  int16_T kDrop;
  int16_T kNext;
  int16_T nA;
  int16_T tmp;
  int16_T tmp_0;
  uint16_T b_x;
  uint16_T q;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  *status = 1.0;
  (void)memset(&lambda[0], 0, 87U * (sizeof(real_T)));
  (void)memset(&x[0], 0, 11U * (sizeof(real_T)));
  (void)memset(&ObstacleAvoidanceController_B.r[0], 0, 11U * (sizeof(real_T)));
  ObstacleAvoidanceController_B.rMin = 0.0;
  cTolComputed = false;
  for (ObstacleAvoidanceController_B.i_n = 0; ObstacleAvoidanceController_B.i_n <
       87; ObstacleAvoidanceController_B.i_n++) {
    ObstacleAvoidanceController_B.cTol[ObstacleAvoidanceController_B.i_n] = 1.0;
    ObstacleAvoidanceController_B.iC[ObstacleAvoidanceController_B.i_n] = 0;
  }

  nA = 0;
  for (ObstacleAvoidanceController_B.i_n = 0; ObstacleAvoidanceController_B.i_n <
       87; ObstacleAvoidanceController_B.i_n++) {
    if (iA[ObstacleAvoidanceController_B.i_n] == 1) {
      ObstacleAvoidanceController_B.ct = ((int32_T)nA) + 1;
      if ((nA + 1) > 32767) {
        ObstacleAvoidanceController_B.ct = 32767;
      }

      nA = (int16_T)ObstacleAvoidanceController_B.ct;
      ObstacleAvoidanceController_B.iC[((int16_T)
        ObstacleAvoidanceController_B.ct) - 1] = (int16_T)
        (ObstacleAvoidanceController_B.i_n + 1);
    }
  }

  guard1 = false;
  if (nA > 0) {
    (void)memset(&ObstacleAvoidanceController_B.Opt[0], 0, 22U * (sizeof(real_T)));
    for (ObstacleAvoidanceController_B.i_n = 0;
         ObstacleAvoidanceController_B.i_n < 11;
         ObstacleAvoidanceController_B.i_n++) {
      ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.i_n] =
        f[ObstacleAvoidanceController_B.i_n];
      ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.i_n + 11] =
        0.0;
    }

    DualFeasible = false;
    ObstacleAvoidanceController_B.ct = 3 * ((int32_T)nA);
    if (ObstacleAvoidanceController_B.ct > 32767) {
      ObstacleAvoidanceController_B.ct = 32767;
    }

    if (((int16_T)ObstacleAvoidanceController_B.ct) > 50) {
      kNext = (int16_T)ObstacleAvoidanceController_B.ct;
    } else {
      kNext = 50;
    }

    q = (uint16_T)(((uint32_T)kNext) / 10U);
    b_x = (uint16_T)(((uint32_T)kNext) - ((uint32_T)((int32_T)(((int32_T)q) * 10))));
    if ((((int32_T)b_x) > 0) && (((int32_T)b_x) >= 5)) {
      q = (uint16_T)((int32_T)(((int32_T)q) + 1));
    }

    ColdReset = false;
    do {
      exitg3 = 0;
      if (((!DualFeasible) && (nA > 0)) && (((int32_T)(*status)) <= ((int32_T)
            maxiter))) {
        ObstacleAvoidanceController_B.Xnorm0 =
          ObstacleAvoidanceController_KWIKfactor_lFdJjicy(b_Ac,
          ObstacleAvoidanceController_B.iC, nA, b_Linv,
          ObstacleAvoidanceController_B.RLinv, ObstacleAvoidanceController_B.b_D,
          ObstacleAvoidanceController_B.b_H, 11);
        if (ObstacleAvoidanceController_B.Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2.0;
            exitg3 = 2;
          } else {
            nA = 0;
            (void)memset(&iA[0], 0, 87U * (sizeof(int16_T)));
            (void)memset(&ObstacleAvoidanceController_B.iC[0], 0, 87U * (sizeof
              (int16_T)));
            ColdReset = true;
          }
        } else {
          ObstacleAvoidanceController_B.i_n = 1;
          while ((ObstacleAvoidanceController_B.i_n - 1) <= (((int32_T)nA) - 1))
          {
            ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
              ObstacleAvoidanceController_B.i_n)) + 11;
            if ((((int16_T)ObstacleAvoidanceController_B.i_n) + 11) > 32767) {
              ObstacleAvoidanceController_B.ct = 32767;
            }

            ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.ct -
              1] = b[ObstacleAvoidanceController_B.iC[((int16_T)
              ObstacleAvoidanceController_B.i_n) - 1] - 1];
            for (kNext = (int16_T)ObstacleAvoidanceController_B.i_n; kNext <= nA;
                 kNext++) {
              ObstacleAvoidanceController_B.ct = (((int32_T)kNext) + (11 *
                (((int32_T)((int16_T)ObstacleAvoidanceController_B.i_n)) - 1)))
                - 1;
              ObstacleAvoidanceController_B.U[ObstacleAvoidanceController_B.ct] =
                0.0;
              ObstacleAvoidanceController_B.b_k = 1;
              while ((ObstacleAvoidanceController_B.b_k - 1) <= (((int32_T)nA) -
                      1)) {
                ObstacleAvoidanceController_B.c_k = (((int32_T)((int16_T)
                  ObstacleAvoidanceController_B.b_k)) - 1) * 11;
                ObstacleAvoidanceController_B.U[ObstacleAvoidanceController_B.ct]
                  += ObstacleAvoidanceController_B.RLinv
                  [(ObstacleAvoidanceController_B.c_k + ((int32_T)kNext)) - 1] *
                  ObstacleAvoidanceController_B.RLinv
                  [(ObstacleAvoidanceController_B.c_k + ((int32_T)((int16_T)
                      ObstacleAvoidanceController_B.i_n))) - 1];
                ObstacleAvoidanceController_B.b_k++;
              }

              ObstacleAvoidanceController_B.U[(((int16_T)
                ObstacleAvoidanceController_B.i_n) + (11 * (kNext - 1))) - 1] =
                ObstacleAvoidanceController_B.U[ObstacleAvoidanceController_B.ct];
            }

            ObstacleAvoidanceController_B.i_n++;
          }

          for (ObstacleAvoidanceController_B.i_n = 0;
               ObstacleAvoidanceController_B.i_n < 11;
               ObstacleAvoidanceController_B.i_n++) {
            ObstacleAvoidanceController_B.Xnorm0 = 0.0;
            for (ObstacleAvoidanceController_B.ct = 0;
                 ObstacleAvoidanceController_B.ct < 11;
                 ObstacleAvoidanceController_B.ct++) {
              ObstacleAvoidanceController_B.Xnorm0 +=
                ObstacleAvoidanceController_B.b_H[ObstacleAvoidanceController_B.i_n
                + (11 * ObstacleAvoidanceController_B.ct)] *
                ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.ct];
            }

            ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.i_n]
              = ObstacleAvoidanceController_B.Xnorm0;
            ObstacleAvoidanceController_B.b_k = 1;
            while ((ObstacleAvoidanceController_B.b_k - 1) <= (((int32_T)nA) - 1))
            {
              ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
                ObstacleAvoidanceController_B.b_k)) + 11;
              if ((((int16_T)ObstacleAvoidanceController_B.b_k) + 11) > 32767) {
                ObstacleAvoidanceController_B.ct = 32767;
              }

              ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.i_n]
                += ObstacleAvoidanceController_B.b_D[((((int32_T)((int16_T)
                ObstacleAvoidanceController_B.b_k)) - 1) * 11) +
                ObstacleAvoidanceController_B.i_n] *
                ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.ct
                - 1];
              ObstacleAvoidanceController_B.b_k++;
            }
          }

          ObstacleAvoidanceController_B.b_k = 1;
          while ((ObstacleAvoidanceController_B.b_k - 1) <= (((int32_T)nA) - 1))
          {
            ObstacleAvoidanceController_B.Xnorm0 = 0.0;
            for (ObstacleAvoidanceController_B.ct = 0;
                 ObstacleAvoidanceController_B.ct < 11;
                 ObstacleAvoidanceController_B.ct++) {
              ObstacleAvoidanceController_B.Xnorm0 +=
                ObstacleAvoidanceController_B.b_D[((((int32_T)((int16_T)
                ObstacleAvoidanceController_B.b_k)) - 1) * 11) +
                ObstacleAvoidanceController_B.ct] *
                ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.ct];
            }

            ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
              ObstacleAvoidanceController_B.b_k)) + 11;
            if ((((int16_T)ObstacleAvoidanceController_B.b_k) + 11) > 32767) {
              ObstacleAvoidanceController_B.ct = 32767;
            }

            ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.ct -
              1] = ObstacleAvoidanceController_B.Xnorm0;
            ObstacleAvoidanceController_B.c_k = 1;
            while ((ObstacleAvoidanceController_B.c_k - 1) <= (((int32_T)nA) - 1))
            {
              ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
                ObstacleAvoidanceController_B.b_k)) + 11;
              if ((((int16_T)ObstacleAvoidanceController_B.b_k) + 11) > 32767) {
                ObstacleAvoidanceController_B.ct = 32767;
              }

              ObstacleAvoidanceController_B.i_n = ((int32_T)((int16_T)
                ObstacleAvoidanceController_B.b_k)) + 11;
              if ((((int16_T)ObstacleAvoidanceController_B.b_k) + 11) > 32767) {
                ObstacleAvoidanceController_B.i_n = 32767;
              }

              ObstacleAvoidanceController_B.i_m = ((int32_T)((int16_T)
                ObstacleAvoidanceController_B.c_k)) + 11;
              if ((((int16_T)ObstacleAvoidanceController_B.c_k) + 11) > 32767) {
                ObstacleAvoidanceController_B.i_m = 32767;
              }

              ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.ct
                - 1] = (ObstacleAvoidanceController_B.U[(((((int16_T)
                ObstacleAvoidanceController_B.c_k) - 1) * 11) + ((int16_T)
                          ObstacleAvoidanceController_B.b_k)) - 1] *
                        ObstacleAvoidanceController_B.Rhs[ObstacleAvoidanceController_B.i_m
                        - 1]) +
                ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.i_n
                - 1];
              ObstacleAvoidanceController_B.c_k++;
            }

            ObstacleAvoidanceController_B.b_k++;
          }

          ObstacleAvoidanceController_B.Xnorm0 = -1.0E-12;
          kDrop = 0;
          ObstacleAvoidanceController_B.i_n = 1;
          while ((ObstacleAvoidanceController_B.i_n - 1) <= (((int32_T)nA) - 1))
          {
            ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
              ObstacleAvoidanceController_B.i_n)) + 11;
            if ((((int16_T)ObstacleAvoidanceController_B.i_n) + 11) > 32767) {
              ObstacleAvoidanceController_B.ct = 32767;
            }

            lambda[ObstacleAvoidanceController_B.iC[((int16_T)
              ObstacleAvoidanceController_B.i_n) - 1] - 1] =
              ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.ct
              - 1];
            ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
              ObstacleAvoidanceController_B.i_n)) + 11;
            if ((((int16_T)ObstacleAvoidanceController_B.i_n) + 11) > 32767) {
              ObstacleAvoidanceController_B.ct = 32767;
            }

            if ((ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.ct
                 - 1] < ObstacleAvoidanceController_B.Xnorm0) && (((int16_T)
                  ObstacleAvoidanceController_B.i_n) <= nA)) {
              kDrop = (int16_T)ObstacleAvoidanceController_B.i_n;
              ObstacleAvoidanceController_B.ct = ((int32_T)((int16_T)
                ObstacleAvoidanceController_B.i_n)) + 11;
              if ((((int16_T)ObstacleAvoidanceController_B.i_n) + 11) > 32767) {
                ObstacleAvoidanceController_B.ct = 32767;
              }

              ObstacleAvoidanceController_B.Xnorm0 =
                ObstacleAvoidanceController_B.Opt[ObstacleAvoidanceController_B.ct
                - 1];
            }

            ObstacleAvoidanceController_B.i_n++;
          }

          if (kDrop <= 0) {
            DualFeasible = true;
            (void)memcpy(&x[0], &ObstacleAvoidanceController_B.Opt[0], 11U *
                         (sizeof(real_T)));
          } else {
            (*status)++;
            if (((int32_T)(*status)) > ((int32_T)q)) {
              nA = 0;
              (void)memset(&iA[0], 0, 87U * (sizeof(int16_T)));
              (void)memset(&ObstacleAvoidanceController_B.iC[0], 0, 87U *
                           (sizeof(int16_T)));
              ColdReset = true;
            } else {
              lambda[ObstacleAvoidanceController_B.iC[kDrop - 1] - 1] = 0.0;
              DropConstraint_pw8y7UcF(kDrop, iA, &nA,
                ObstacleAvoidanceController_B.iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          (void)memset(&lambda[0], 0, 87U * (sizeof(real_T)));
          Unconstrained_XbGnMUND(b_Hinv, f, x, 11);
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Unconstrained_XbGnMUND(b_Hinv, f, x, 11);
    guard1 = true;
  }

  if (guard1) {
    ObstacleAvoidanceController_B.Xnorm0 = norm_U2d2wUAJ(x);
    exitg2 = false;
    while ((!exitg2) && (((int32_T)(*status)) <= ((int32_T)maxiter))) {
      ObstacleAvoidanceController_B.cMin = -FeasTol;
      kNext = 0;
      for (ObstacleAvoidanceController_B.i_n = 0;
           ObstacleAvoidanceController_B.i_n < 87;
           ObstacleAvoidanceController_B.i_n++) {
        ObstacleAvoidanceController_B.zTa =
          ObstacleAvoidanceController_B.cTol[ObstacleAvoidanceController_B.i_n];
        if (!cTolComputed) {
          for (ObstacleAvoidanceController_B.ct = 0;
               ObstacleAvoidanceController_B.ct < 11;
               ObstacleAvoidanceController_B.ct++) {
            ObstacleAvoidanceController_B.b_Ac[ObstacleAvoidanceController_B.ct]
              = b_Ac[ObstacleAvoidanceController_B.i_n + (87 *
              ObstacleAvoidanceController_B.ct)] *
              x[ObstacleAvoidanceController_B.ct];
          }

          abs_eSIKPPwm(ObstacleAvoidanceController_B.b_Ac,
                       ObstacleAvoidanceController_B.z);
          ObstacleAvoidanceController_B.zTa = fmax
            (ObstacleAvoidanceController_B.zTa, maximum_WbjyebyW
             (ObstacleAvoidanceController_B.z));
        }

        if (iA[ObstacleAvoidanceController_B.i_n] == 0) {
          ObstacleAvoidanceController_B.cVal = 0.0;
          for (ObstacleAvoidanceController_B.ct = 0;
               ObstacleAvoidanceController_B.ct < 11;
               ObstacleAvoidanceController_B.ct++) {
            ObstacleAvoidanceController_B.cVal +=
              b_Ac[ObstacleAvoidanceController_B.i_n + (87 *
              ObstacleAvoidanceController_B.ct)] *
              x[ObstacleAvoidanceController_B.ct];
          }

          ObstacleAvoidanceController_B.cVal =
            (ObstacleAvoidanceController_B.cVal -
             b[ObstacleAvoidanceController_B.i_n]) /
            ObstacleAvoidanceController_B.zTa;
          if (ObstacleAvoidanceController_B.cVal <
              ObstacleAvoidanceController_B.cMin) {
            ObstacleAvoidanceController_B.cMin =
              ObstacleAvoidanceController_B.cVal;
            kNext = (int16_T)(ObstacleAvoidanceController_B.i_n + 1);
          }
        }

        ObstacleAvoidanceController_B.cTol[ObstacleAvoidanceController_B.i_n] =
          ObstacleAvoidanceController_B.zTa;
      }

      cTolComputed = true;
      if (kNext <= 0) {
        exitg2 = true;
      } else if (((int32_T)(*status)) == ((int32_T)maxiter)) {
        *status = 0.0;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((kNext > 0) && (((int32_T)(*status)) <= ((int32_T)maxiter))) {
            guard2 = false;
            if (nA == 0) {
              for (ObstacleAvoidanceController_B.ct = 0;
                   ObstacleAvoidanceController_B.ct < 11;
                   ObstacleAvoidanceController_B.ct++) {
                ObstacleAvoidanceController_B.z[ObstacleAvoidanceController_B.ct]
                  = 0.0;
                for (ObstacleAvoidanceController_B.i_n = 0;
                     ObstacleAvoidanceController_B.i_n < 11;
                     ObstacleAvoidanceController_B.i_n++) {
                  ObstacleAvoidanceController_B.z[ObstacleAvoidanceController_B.ct]
                    += b_Ac[((87 * ObstacleAvoidanceController_B.i_n) +
                             ((int32_T)kNext)) - 1] * b_Hinv[(11 *
                    ObstacleAvoidanceController_B.i_n) +
                    ObstacleAvoidanceController_B.ct];
                }
              }

              guard2 = true;
            } else {
              ObstacleAvoidanceController_B.cMin =
                ObstacleAvoidanceController_KWIKfactor_lFdJjicy(b_Ac,
                ObstacleAvoidanceController_B.iC, nA, b_Linv,
                ObstacleAvoidanceController_B.RLinv,
                ObstacleAvoidanceController_B.b_D,
                ObstacleAvoidanceController_B.b_H, 11);
              if (ObstacleAvoidanceController_B.cMin <= 0.0) {
                *status = -2.0;
                exitg1 = 1;
              } else {
                for (ObstacleAvoidanceController_B.ct = 0;
                     ObstacleAvoidanceController_B.ct < 121;
                     ObstacleAvoidanceController_B.ct++) {
                  ObstacleAvoidanceController_B.U[ObstacleAvoidanceController_B.ct]
                    =
                    -ObstacleAvoidanceController_B.b_H[ObstacleAvoidanceController_B.ct];
                }

                for (ObstacleAvoidanceController_B.ct = 0;
                     ObstacleAvoidanceController_B.ct < 11;
                     ObstacleAvoidanceController_B.ct++) {
                  ObstacleAvoidanceController_B.z[ObstacleAvoidanceController_B.ct]
                    = 0.0;
                  for (ObstacleAvoidanceController_B.i_n = 0;
                       ObstacleAvoidanceController_B.i_n < 11;
                       ObstacleAvoidanceController_B.i_n++) {
                    ObstacleAvoidanceController_B.z[ObstacleAvoidanceController_B.ct]
                      += b_Ac[((87 * ObstacleAvoidanceController_B.i_n) +
                               ((int32_T)kNext)) - 1] *
                      ObstacleAvoidanceController_B.U[(11 *
                      ObstacleAvoidanceController_B.i_n) +
                      ObstacleAvoidanceController_B.ct];
                  }
                }

                ObstacleAvoidanceController_B.i_n = 1;
                while ((ObstacleAvoidanceController_B.i_n - 1) <= (((int32_T)nA)
                        - 1)) {
                  ObstacleAvoidanceController_B.cVal = 0.0;
                  for (ObstacleAvoidanceController_B.ct = 0;
                       ObstacleAvoidanceController_B.ct < 11;
                       ObstacleAvoidanceController_B.ct++) {
                    ObstacleAvoidanceController_B.cVal += b_Ac[((87 *
                      ObstacleAvoidanceController_B.ct) + ((int32_T)kNext)) - 1]
                      * ObstacleAvoidanceController_B.b_D[((((int32_T)((int16_T)
                      ObstacleAvoidanceController_B.i_n)) - 1) * 11) +
                      ObstacleAvoidanceController_B.ct];
                  }

                  ObstacleAvoidanceController_B.r[((int16_T)
                    ObstacleAvoidanceController_B.i_n) - 1] =
                    ObstacleAvoidanceController_B.cVal;
                  ObstacleAvoidanceController_B.i_n++;
                }

                guard2 = true;
              }
            }

            if (guard2) {
              kDrop = 0;
              ObstacleAvoidanceController_B.cMin = 0.0;
              DualFeasible = true;
              ColdReset = true;
              if (nA > 0) {
                ObstacleAvoidanceController_B.ct = 0;
                exitg4 = false;
                while ((!exitg4) && (ObstacleAvoidanceController_B.ct <=
                                     (((int32_T)nA) - 1))) {
                  if (ObstacleAvoidanceController_B.r[ObstacleAvoidanceController_B.ct]
                      >= 1.0E-12) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    ObstacleAvoidanceController_B.ct++;
                  }
                }
              }

              if ((nA != 0) && (!ColdReset)) {
                ObstacleAvoidanceController_B.ct = 1;
                while ((ObstacleAvoidanceController_B.ct - 1) <= (((int32_T)nA)
                        - 1)) {
                  ObstacleAvoidanceController_B.cVal =
                    ObstacleAvoidanceController_B.r[((int16_T)
                    ObstacleAvoidanceController_B.ct) - 1];
                  if (ObstacleAvoidanceController_B.cVal > 1.0E-12) {
                    ObstacleAvoidanceController_B.cVal =
                      lambda[ObstacleAvoidanceController_B.iC[((int16_T)
                      ObstacleAvoidanceController_B.ct) - 1] - 1] /
                      ObstacleAvoidanceController_B.cVal;
                    if ((kDrop == 0) || (ObstacleAvoidanceController_B.cVal <
                                         ObstacleAvoidanceController_B.rMin)) {
                      ObstacleAvoidanceController_B.rMin =
                        ObstacleAvoidanceController_B.cVal;
                      kDrop = (int16_T)ObstacleAvoidanceController_B.ct;
                    }
                  }

                  ObstacleAvoidanceController_B.ct++;
                }

                if (kDrop > 0) {
                  ObstacleAvoidanceController_B.cMin =
                    ObstacleAvoidanceController_B.rMin;
                  DualFeasible = false;
                }
              }

              for (ObstacleAvoidanceController_B.ct = 0;
                   ObstacleAvoidanceController_B.ct < 11;
                   ObstacleAvoidanceController_B.ct++) {
                ObstacleAvoidanceController_B.b_Ac[ObstacleAvoidanceController_B.ct]
                  = b_Ac[((87 * ObstacleAvoidanceController_B.ct) + ((int32_T)
                           kNext)) - 1];
              }

              ObstacleAvoidanceController_B.zTa = mtimes_ZHySypuw
                (ObstacleAvoidanceController_B.z,
                 ObstacleAvoidanceController_B.b_Ac);
              if (ObstacleAvoidanceController_B.zTa <= 0.0) {
                ObstacleAvoidanceController_B.cVal = 0.0;
                ColdReset = true;
              } else {
                ObstacleAvoidanceController_B.cVal = 0.0;
                for (ObstacleAvoidanceController_B.ct = 0;
                     ObstacleAvoidanceController_B.ct < 11;
                     ObstacleAvoidanceController_B.ct++) {
                  ObstacleAvoidanceController_B.cVal += b_Ac[((87 *
                    ObstacleAvoidanceController_B.ct) + ((int32_T)kNext)) - 1] *
                    x[ObstacleAvoidanceController_B.ct];
                }

                ObstacleAvoidanceController_B.cVal = (b[kNext - 1] -
                  ObstacleAvoidanceController_B.cVal) /
                  ObstacleAvoidanceController_B.zTa;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1.0;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  ObstacleAvoidanceController_B.zTa =
                    ObstacleAvoidanceController_B.cMin;
                } else if (DualFeasible) {
                  ObstacleAvoidanceController_B.zTa =
                    ObstacleAvoidanceController_B.cVal;
                } else {
                  ObstacleAvoidanceController_B.zTa = fmin
                    (ObstacleAvoidanceController_B.cMin,
                     ObstacleAvoidanceController_B.cVal);
                }

                ObstacleAvoidanceController_B.ct = 1;
                while ((ObstacleAvoidanceController_B.ct - 1) <= (((int32_T)nA)
                        - 1)) {
                  ObstacleAvoidanceController_B.i_n = (int32_T)
                    ObstacleAvoidanceController_B.iC[((int16_T)
                    ObstacleAvoidanceController_B.ct) - 1];
                  lambda[ObstacleAvoidanceController_B.i_n - 1] -=
                    ObstacleAvoidanceController_B.r[((int16_T)
                    ObstacleAvoidanceController_B.ct) - 1] *
                    ObstacleAvoidanceController_B.zTa;
                  if ((ObstacleAvoidanceController_B.i_n <= 87) &&
                      (lambda[ObstacleAvoidanceController_B.i_n - 1] < 0.0)) {
                    lambda[ObstacleAvoidanceController_B.i_n - 1] = 0.0;
                  }

                  ObstacleAvoidanceController_B.ct++;
                }

                lambda[kNext - 1] += ObstacleAvoidanceController_B.zTa;
                if (ObstacleAvoidanceController_B.zTa ==
                    ObstacleAvoidanceController_B.cMin) {
                  DropConstraint_pw8y7UcF(kDrop, iA, &nA,
                    ObstacleAvoidanceController_B.iC);
                }

                if (!ColdReset) {
                  for (ObstacleAvoidanceController_B.ct = 0;
                       ObstacleAvoidanceController_B.ct < 11;
                       ObstacleAvoidanceController_B.ct++) {
                    x[ObstacleAvoidanceController_B.ct] +=
                      ObstacleAvoidanceController_B.zTa *
                      ObstacleAvoidanceController_B.z[ObstacleAvoidanceController_B.ct];
                  }

                  if (ObstacleAvoidanceController_B.zTa ==
                      ObstacleAvoidanceController_B.cVal) {
                    if (nA == 11) {
                      *status = -1.0;
                      exitg1 = 1;
                    } else {
                      ObstacleAvoidanceController_B.ct = ((int32_T)nA) + 1;
                      if ((nA + 1) > 32767) {
                        ObstacleAvoidanceController_B.ct = 32767;
                      }

                      nA = (int16_T)ObstacleAvoidanceController_B.ct;
                      ObstacleAvoidanceController_B.iC[((int16_T)
                        ObstacleAvoidanceController_B.ct) - 1] = kNext;
                      kDrop = (int16_T)ObstacleAvoidanceController_B.ct;
                      exitg4 = false;
                      while ((!exitg4) && (kDrop > 1)) {
                        tmp = ObstacleAvoidanceController_B.iC[kDrop - 1];
                        tmp_0 = ObstacleAvoidanceController_B.iC[kDrop - 2];
                        if (tmp > tmp_0) {
                          exitg4 = true;
                        } else {
                          ObstacleAvoidanceController_B.iC[kDrop - 1] = tmp_0;
                          ObstacleAvoidanceController_B.iC[kDrop - 2] = tmp;
                          kDrop--;
                        }
                      }

                      iA[kNext - 1] = 1;
                      kNext = 0;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            ObstacleAvoidanceController_B.cMin = norm_U2d2wUAJ(x);
            if (fabs(ObstacleAvoidanceController_B.cMin -
                     ObstacleAvoidanceController_B.Xnorm0) > 0.001) {
              ObstacleAvoidanceController_B.Xnorm0 =
                ObstacleAvoidanceController_B.cMin;
              abs_dPqD3gJW(b, ObstacleAvoidanceController_B.dv5);
              maximum2_o0q4L4FQ(ObstacleAvoidanceController_B.dv5, 1.0,
                                ObstacleAvoidanceController_B.cTol);
              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpc_solveQP_qQaaXkaK(const real_T xQP[6],
  const real_T b_Kx[60], const real_T b_Kr[600], const real_T rseq[60], const
  real_T b_Ku1[20], const real_T old_u[2], const real_T b_Kv[160], const real_T
  vseq[16], const real_T b_Kut[300], const real_T b_utarget[30], const real_T
  b_Linv[121], const real_T b_Hinv[121], const real_T b_Ac[957], const real_T
  Bc[87], boolean_T iA[87], real_T zopt[11], real_T f[11], real_T *status)
{
  (void)memset(&f[0], 0, 11U * (sizeof(real_T)));
  for (ObstacleAvoidanceController_B.i_o = 0; ObstacleAvoidanceController_B.i_o <
       10; ObstacleAvoidanceController_B.i_o++) {
    ObstacleAvoidanceController_B.b_Kx = 0.0;
    for (ObstacleAvoidanceController_B.f_tmp = 0;
         ObstacleAvoidanceController_B.f_tmp < 6;
         ObstacleAvoidanceController_B.f_tmp++) {
      ObstacleAvoidanceController_B.b_Kx += b_Kx[(6 *
        ObstacleAvoidanceController_B.i_o) + ObstacleAvoidanceController_B.f_tmp]
        * xQP[ObstacleAvoidanceController_B.f_tmp];
    }

    ObstacleAvoidanceController_B.b_Kr = 0.0;
    for (ObstacleAvoidanceController_B.f_tmp = 0;
         ObstacleAvoidanceController_B.f_tmp < 60;
         ObstacleAvoidanceController_B.f_tmp++) {
      ObstacleAvoidanceController_B.b_Kr += b_Kr[(60 *
        ObstacleAvoidanceController_B.i_o) + ObstacleAvoidanceController_B.f_tmp]
        * rseq[ObstacleAvoidanceController_B.f_tmp];
    }

    ObstacleAvoidanceController_B.b_Kv = 0.0;
    for (ObstacleAvoidanceController_B.f_tmp = 0;
         ObstacleAvoidanceController_B.f_tmp < 16;
         ObstacleAvoidanceController_B.f_tmp++) {
      ObstacleAvoidanceController_B.b_Kv += b_Kv
        [(ObstacleAvoidanceController_B.i_o * 16) +
        ObstacleAvoidanceController_B.f_tmp] *
        vseq[ObstacleAvoidanceController_B.f_tmp];
    }

    ObstacleAvoidanceController_B.b_Kut = 0.0;
    for (ObstacleAvoidanceController_B.f_tmp = 0;
         ObstacleAvoidanceController_B.f_tmp < 30;
         ObstacleAvoidanceController_B.f_tmp++) {
      ObstacleAvoidanceController_B.b_Kut += b_Kut[(30 *
        ObstacleAvoidanceController_B.i_o) + ObstacleAvoidanceController_B.f_tmp]
        * b_utarget[ObstacleAvoidanceController_B.f_tmp];
    }

    ObstacleAvoidanceController_B.f_tmp = ObstacleAvoidanceController_B.i_o * 2;
    f[ObstacleAvoidanceController_B.i_o] =
      ((((b_Ku1[ObstacleAvoidanceController_B.f_tmp + 1] * old_u[1]) +
         (b_Ku1[ObstacleAvoidanceController_B.f_tmp] * old_u[0])) +
        (ObstacleAvoidanceController_B.b_Kx + ObstacleAvoidanceController_B.b_Kr))
       + ObstacleAvoidanceController_B.b_Kv) +
      ObstacleAvoidanceController_B.b_Kut;
  }

  for (ObstacleAvoidanceController_B.i_o = 0; ObstacleAvoidanceController_B.i_o <
       87; ObstacleAvoidanceController_B.i_o++) {
    ObstacleAvoidanceController_B.iAnew[ObstacleAvoidanceController_B.i_o] =
      iA[ObstacleAvoidanceController_B.i_o] ? ((int16_T)1) : ((int16_T)0);
  }

  ObstacleAvoidanceController_qpkwik_XjF1fpUJ(b_Linv, b_Hinv, f, b_Ac, Bc,
    ObstacleAvoidanceController_B.iAnew, 392, 1.0E-6, zopt,
    ObstacleAvoidanceController_B.a__1, status);
  for (ObstacleAvoidanceController_B.i_o = 0; ObstacleAvoidanceController_B.i_o <
       87; ObstacleAvoidanceController_B.i_o++) {
    iA[ObstacleAvoidanceController_B.i_o] =
      (ObstacleAvoidanceController_B.iAnew[ObstacleAvoidanceController_B.i_o] !=
       0);
  }

  if (((*status) < 0.0) || ((*status) == 0.0)) {
    (void)memset(&zopt[0], 0, 11U * (sizeof(real_T)));
  }
}

/* Function for MATLAB Function: '<S36>/FixedHorizonOptimizer' */
static void ObstacleAvoidanceController_mpcblock_optimizer(const real_T rseq[60],
  const real_T vseq[16], const real_T x[6], const real_T old_u[2], const
  boolean_T iA[87], real_T b_Mlim[87], real_T b_Mx[522], real_T b_Mu1[174],
  real_T b_Mv[1392], const real_T b_utarget[30], const real_T b_uoff[2], const
  real_T b_yoff[4], real_T b_H[121], real_T b_Ac[957], const real_T ywt[4],
  const real_T uwt[2], const real_T duwt[2], const real_T b_Jm[300], const
  real_T b_I1[60], const real_T b_A[36], const real_T Bu[192], const real_T Bv
  [96], const real_T b_C[24], const real_T Dv[64], const real_T b_Mrows[55],
  const real_T b_Ecc[4], const real_T b_Fcc[8], const real_T b_Gcc[2], real_T u
  [2], real_T useq[32], real_T *status, boolean_T iAout[87])
{
  static const int8_T c_A[225] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1 };

  boolean_T exitg1;
  (void)memset(&useq[0], 0, (sizeof(real_T)) << 5U);
  (void)memset(&iAout[0], 0, 87U * (sizeof(boolean_T)));
  ObstacleAvoidanceController_mpc_constraintcoef_HBE9OVn8(b_A, &Bu[0], &Bv[0],
    b_C, &Dv[0], b_Jm, ObstacleAvoidanceController_B.c_SuJm,
    ObstacleAvoidanceController_B.c_Sx, ObstacleAvoidanceController_B.c_Su1,
    ObstacleAvoidanceController_B.c_Hv);
  if (b_Mrows[0] > 0.0) {
    ObstacleAvoidanceController_B.i = 0;
    exitg1 = false;
    while ((!exitg1) && (ObstacleAvoidanceController_B.i < 55)) {
      if (b_Mrows[ObstacleAvoidanceController_B.i] <= 60.0) {
        ObstacleAvoidanceController_B.b_j1 = (int32_T)
          b_Mrows[ObstacleAvoidanceController_B.i];
        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 10;
             ObstacleAvoidanceController_B.kidx++) {
          b_Ac[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            -ObstacleAvoidanceController_B.c_SuJm[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 6;
             ObstacleAvoidanceController_B.kidx++) {
          b_Mx[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            -ObstacleAvoidanceController_B.c_Sx[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        b_Mu1[ObstacleAvoidanceController_B.i] =
          -ObstacleAvoidanceController_B.c_Su1[ObstacleAvoidanceController_B.b_j1
          - 1];
        b_Mu1[ObstacleAvoidanceController_B.i + 87] =
          -ObstacleAvoidanceController_B.c_Su1[ObstacleAvoidanceController_B.b_j1
          + 59];
        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 16;
             ObstacleAvoidanceController_B.kidx++) {
          b_Mv[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            -ObstacleAvoidanceController_B.c_Hv[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        ObstacleAvoidanceController_B.i++;
      } else if (b_Mrows[ObstacleAvoidanceController_B.i] <= 120.0) {
        ObstacleAvoidanceController_B.b_j1 = (int32_T)((real_T)
          (b_Mrows[ObstacleAvoidanceController_B.i] - 60.0));
        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 10;
             ObstacleAvoidanceController_B.kidx++) {
          b_Ac[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            ObstacleAvoidanceController_B.c_SuJm[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 6;
             ObstacleAvoidanceController_B.kidx++) {
          b_Mx[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            ObstacleAvoidanceController_B.c_Sx[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        b_Mu1[ObstacleAvoidanceController_B.i] =
          ObstacleAvoidanceController_B.c_Su1[ObstacleAvoidanceController_B.b_j1
          - 1];
        b_Mu1[ObstacleAvoidanceController_B.i + 87] =
          ObstacleAvoidanceController_B.c_Su1[ObstacleAvoidanceController_B.b_j1
          + 59];
        for (ObstacleAvoidanceController_B.kidx = 0;
             ObstacleAvoidanceController_B.kidx < 16;
             ObstacleAvoidanceController_B.kidx++) {
          b_Mv[ObstacleAvoidanceController_B.i + (87 *
            ObstacleAvoidanceController_B.kidx)] =
            ObstacleAvoidanceController_B.c_Hv[((60 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.b_j1) - 1];
        }

        ObstacleAvoidanceController_B.i++;
      } else {
        exitg1 = true;
      }
    }
  }

  ObstacleAvoidanceController_mpc_customconstraintcoef_X8ClKd4y
    (ObstacleAvoidanceController_B.c_SuJm, ObstacleAvoidanceController_B.c_Sx,
     ObstacleAvoidanceController_B.c_Su1, ObstacleAvoidanceController_B.c_Hv,
     b_C, Dv, b_Jm, b_Ecc, b_Fcc, b_Gcc, b_uoff, b_yoff,
     ObstacleAvoidanceController_B.MuCC, ObstacleAvoidanceController_B.MvCC,
     ObstacleAvoidanceController_B.Mu1CC, ObstacleAvoidanceController_B.MxCC,
     &b_Mlim[55]);
  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 10;
       ObstacleAvoidanceController_B.kidx++) {
    for (ObstacleAvoidanceController_B.b_j1 = 0;
         ObstacleAvoidanceController_B.b_j1 < 32;
         ObstacleAvoidanceController_B.b_j1++) {
      b_Ac[(ObstacleAvoidanceController_B.b_j1 + (87 *
             ObstacleAvoidanceController_B.kidx)) + 55] =
        -ObstacleAvoidanceController_B.MuCC[(ObstacleAvoidanceController_B.kidx *
        32) + ObstacleAvoidanceController_B.b_j1];
    }
  }

  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 6;
       ObstacleAvoidanceController_B.kidx++) {
    (void)memcpy(&b_Mx[(ObstacleAvoidanceController_B.kidx * 87) + 55],
                 &ObstacleAvoidanceController_B.MxCC[ObstacleAvoidanceController_B.kidx
                 * 32], (sizeof(real_T)) << 5U);
  }

  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 2;
       ObstacleAvoidanceController_B.kidx++) {
    (void)memcpy(&b_Mu1[(ObstacleAvoidanceController_B.kidx * 87) + 55],
                 &ObstacleAvoidanceController_B.Mu1CC[ObstacleAvoidanceController_B.kidx
                 * 32], (sizeof(real_T)) << 5U);
  }

  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 16;
       ObstacleAvoidanceController_B.kidx++) {
    (void)memcpy(&b_Mv[(ObstacleAvoidanceController_B.kidx * 87) + 55],
                 &ObstacleAvoidanceController_B.MvCC[ObstacleAvoidanceController_B.kidx
                 * 32], (sizeof(real_T)) << 5U);
  }

  if (ywt[0] < 0.0) {
    ObstacleAvoidanceController_B.c_Wy[0] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wy[0] = ywt[0] * ywt[0];
  }

  if (ywt[1] < 0.0) {
    ObstacleAvoidanceController_B.c_Wy[1] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wy[1] = ywt[1] * ywt[1];
  }

  if (ywt[2] < 0.0) {
    ObstacleAvoidanceController_B.c_Wy[2] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wy[2] = ywt[2] * ywt[2];
  }

  if (ywt[3] < 0.0) {
    ObstacleAvoidanceController_B.c_Wy[3] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wy[3] = ywt[3] * ywt[3];
  }

  if (uwt[0] < 0.0) {
    ObstacleAvoidanceController_B.c_Wu[0] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wu[0] = uwt[0] * uwt[0];
  }

  if (duwt[0] < 0.0) {
    ObstacleAvoidanceController_B.c_Wdu[0] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wdu[0] = duwt[0] * duwt[0];
  }

  if (uwt[1] < 0.0) {
    ObstacleAvoidanceController_B.c_Wu[1] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wu[1] = uwt[1] * uwt[1];
  }

  if (duwt[1] < 0.0) {
    ObstacleAvoidanceController_B.c_Wdu[1] = 0.0;
  } else {
    ObstacleAvoidanceController_B.c_Wdu[1] = duwt[1] * duwt[1];
  }

  ObstacleAvoidanceController_B.b_I_i[1] = 0;
  ObstacleAvoidanceController_B.b_I_i[2] = 0;
  ObstacleAvoidanceController_B.b_I_i[0] = 1;
  ObstacleAvoidanceController_B.b_I_i[3] = 1;
  ObstacleAvoidanceController_B.kidx = -1;
  for (ObstacleAvoidanceController_B.b_j1 = 0;
       ObstacleAvoidanceController_B.b_j1 < 15;
       ObstacleAvoidanceController_B.b_j1++) {
    for (ObstacleAvoidanceController_B.j2 = 0; ObstacleAvoidanceController_B.j2 <
         2; ObstacleAvoidanceController_B.j2++) {
      for (ObstacleAvoidanceController_B.i1 = 0;
           ObstacleAvoidanceController_B.i1 < 15;
           ObstacleAvoidanceController_B.i1++) {
        ObstacleAvoidanceController_B.i = ObstacleAvoidanceController_B.j2 * 2;
        ObstacleAvoidanceController_B.a_tmp = (int32_T)c_A[(15 *
          ObstacleAvoidanceController_B.b_j1) + ObstacleAvoidanceController_B.i1];
        ObstacleAvoidanceController_B.a_k[ObstacleAvoidanceController_B.kidx + 1]
          = (int8_T)(ObstacleAvoidanceController_B.a_tmp * ((int32_T)
          ObstacleAvoidanceController_B.b_I_i[ObstacleAvoidanceController_B.i]));
        ObstacleAvoidanceController_B.a_k[ObstacleAvoidanceController_B.kidx + 2]
          = (int8_T)(ObstacleAvoidanceController_B.a_tmp * ((int32_T)
          ObstacleAvoidanceController_B.b_I_i[ObstacleAvoidanceController_B.i +
          1]));
        ObstacleAvoidanceController_B.kidx += 2;
      }
    }
  }

  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 10;
       ObstacleAvoidanceController_B.kidx++) {
    (void)memset
      (&ObstacleAvoidanceController_B.a[ObstacleAvoidanceController_B.kidx * 30],
       0, 30U * (sizeof(real_T)));
    for (ObstacleAvoidanceController_B.j2 = 0; ObstacleAvoidanceController_B.j2 <
         30; ObstacleAvoidanceController_B.j2++) {
      for (ObstacleAvoidanceController_B.b_j1 = 0;
           ObstacleAvoidanceController_B.b_j1 < 30;
           ObstacleAvoidanceController_B.b_j1++) {
        ObstacleAvoidanceController_B.i = (30 *
          ObstacleAvoidanceController_B.kidx) +
          ObstacleAvoidanceController_B.b_j1;
        ObstacleAvoidanceController_B.a[ObstacleAvoidanceController_B.i] +=
          ((real_T)ObstacleAvoidanceController_B.a_k[(30 *
            ObstacleAvoidanceController_B.j2) +
           ObstacleAvoidanceController_B.b_j1]) * b_Jm[(30 *
          ObstacleAvoidanceController_B.kidx) + ObstacleAvoidanceController_B.j2];
      }
    }
  }

  ObstacleAvoidanceController_mpc_calculatehessian_l89OAA4T
    (ObstacleAvoidanceController_B.c_Wy, ObstacleAvoidanceController_B.c_Wu,
     ObstacleAvoidanceController_B.c_Wdu, ObstacleAvoidanceController_B.c_SuJm,
     ObstacleAvoidanceController_B.a, b_Jm, b_I1,
     ObstacleAvoidanceController_B.c_Su1, ObstacleAvoidanceController_B.c_Sx,
     ObstacleAvoidanceController_B.c_Hv, ObstacleAvoidanceController_nu,
     ObstacleAvoidanceController_ny, ObstacleAvoidanceController_B.b,
     ObstacleAvoidanceController_B.c_Ku1, ObstacleAvoidanceController_B.c_Kut,
     ObstacleAvoidanceController_B.c_Kx, ObstacleAvoidanceController_B.c_Kv,
     ObstacleAvoidanceController_B.c_Kr);
  for (ObstacleAvoidanceController_B.kidx = 0;
       ObstacleAvoidanceController_B.kidx < 10;
       ObstacleAvoidanceController_B.kidx++) {
    (void)memcpy(&b_H[ObstacleAvoidanceController_B.kidx * 11],
                 &ObstacleAvoidanceController_B.b[ObstacleAvoidanceController_B.kidx
                 * 10], 10U * (sizeof(real_T)));
  }

  (void)memcpy(&ObstacleAvoidanceController_B.c_Linv[0], &b_H[0], 121U * (sizeof
    (real_T)));
  ObstacleAvoidanceController_mpc_checkhessian_zJaLOdRx
    (ObstacleAvoidanceController_B.c_Linv, ObstacleAvoidanceController_B.d_Linv,
     &ObstacleAvoidanceController_B.BadH);
  if (ObstacleAvoidanceController_B.BadH > 1.0) {
    for (ObstacleAvoidanceController_B.i = 0; ObstacleAvoidanceController_B.i <
         2; ObstacleAvoidanceController_B.i++) {
      u[ObstacleAvoidanceController_B.i] = old_u[ObstacleAvoidanceController_B.i]
        + b_uoff[ObstacleAvoidanceController_B.i];
      for (ObstacleAvoidanceController_B.kidx = 0;
           ObstacleAvoidanceController_B.kidx < 16;
           ObstacleAvoidanceController_B.kidx++) {
        useq[ObstacleAvoidanceController_B.kidx +
          (ObstacleAvoidanceController_B.i * 16)] =
          u[ObstacleAvoidanceController_B.i];
      }
    }

    *status = -2.0;
  } else {
    (void)memset(&ObstacleAvoidanceController_B.c_I_o[0], 0, 121U * (sizeof
      (int8_T)));
    for (ObstacleAvoidanceController_B.i = 0; ObstacleAvoidanceController_B.i <
         11; ObstacleAvoidanceController_B.i++) {
      ObstacleAvoidanceController_B.c_I_o[ObstacleAvoidanceController_B.i + (11 *
        ObstacleAvoidanceController_B.i)] = 1;
    }

    for (ObstacleAvoidanceController_B.kidx = 0;
         ObstacleAvoidanceController_B.kidx < 11;
         ObstacleAvoidanceController_B.kidx++) {
      for (ObstacleAvoidanceController_B.b_j1 = 0;
           ObstacleAvoidanceController_B.b_j1 < 11;
           ObstacleAvoidanceController_B.b_j1++) {
        ObstacleAvoidanceController_B.i = (11 *
          ObstacleAvoidanceController_B.kidx) +
          ObstacleAvoidanceController_B.b_j1;
        ObstacleAvoidanceController_B.c_Linv[ObstacleAvoidanceController_B.i] =
          (real_T)
          ObstacleAvoidanceController_B.c_I_o[ObstacleAvoidanceController_B.i];
      }
    }

    trisolve_eOpSOCVD(ObstacleAvoidanceController_B.d_Linv,
                      ObstacleAvoidanceController_B.c_Linv);
    for (ObstacleAvoidanceController_B.i = 0; ObstacleAvoidanceController_B.i <
         87; ObstacleAvoidanceController_B.i++) {
      iAout[ObstacleAvoidanceController_B.i] =
        iA[ObstacleAvoidanceController_B.i];
      ObstacleAvoidanceController_B.BadH = 0.0;
      for (ObstacleAvoidanceController_B.kidx = 0;
           ObstacleAvoidanceController_B.kidx < 6;
           ObstacleAvoidanceController_B.kidx++) {
        ObstacleAvoidanceController_B.BadH += b_Mx[(87 *
          ObstacleAvoidanceController_B.kidx) + ObstacleAvoidanceController_B.i]
          * x[ObstacleAvoidanceController_B.kidx];
      }

      ObstacleAvoidanceController_B.b_Mlim_b[ObstacleAvoidanceController_B.i] =
        b_Mlim[ObstacleAvoidanceController_B.i] +
        ObstacleAvoidanceController_B.BadH;
      ObstacleAvoidanceController_B.b_Mu1[ObstacleAvoidanceController_B.i] =
        (b_Mu1[ObstacleAvoidanceController_B.i + 87] * old_u[1]) +
        (b_Mu1[ObstacleAvoidanceController_B.i] * old_u[0]);
    }

    for (ObstacleAvoidanceController_B.kidx = 0;
         ObstacleAvoidanceController_B.kidx < 11;
         ObstacleAvoidanceController_B.kidx++) {
      for (ObstacleAvoidanceController_B.b_j1 = 0;
           ObstacleAvoidanceController_B.b_j1 < 11;
           ObstacleAvoidanceController_B.b_j1++) {
        ObstacleAvoidanceController_B.i = ObstacleAvoidanceController_B.b_j1 +
          (11 * ObstacleAvoidanceController_B.kidx);
        ObstacleAvoidanceController_B.d_Linv[ObstacleAvoidanceController_B.i] =
          0.0;
        for (ObstacleAvoidanceController_B.j2 = 0;
             ObstacleAvoidanceController_B.j2 < 11;
             ObstacleAvoidanceController_B.j2++) {
          ObstacleAvoidanceController_B.d_Linv[ObstacleAvoidanceController_B.i] +=
            ObstacleAvoidanceController_B.c_Linv[(11 *
            ObstacleAvoidanceController_B.b_j1) +
            ObstacleAvoidanceController_B.j2] *
            ObstacleAvoidanceController_B.c_Linv[(11 *
            ObstacleAvoidanceController_B.kidx) +
            ObstacleAvoidanceController_B.j2];
        }
      }
    }

    for (ObstacleAvoidanceController_B.kidx = 0;
         ObstacleAvoidanceController_B.kidx < 87;
         ObstacleAvoidanceController_B.kidx++) {
      ObstacleAvoidanceController_B.BadH = 0.0;
      for (ObstacleAvoidanceController_B.b_j1 = 0;
           ObstacleAvoidanceController_B.b_j1 < 16;
           ObstacleAvoidanceController_B.b_j1++) {
        ObstacleAvoidanceController_B.BadH += b_Mv[(87 *
          ObstacleAvoidanceController_B.b_j1) +
          ObstacleAvoidanceController_B.kidx] *
          vseq[ObstacleAvoidanceController_B.b_j1];
      }

      ObstacleAvoidanceController_B.b_Mlim_p[ObstacleAvoidanceController_B.kidx]
        =
        -((ObstacleAvoidanceController_B.b_Mlim_b[ObstacleAvoidanceController_B.kidx]
           + ObstacleAvoidanceController_B.b_Mu1[ObstacleAvoidanceController_B.kidx])
          + ObstacleAvoidanceController_B.BadH);
    }

    ObstacleAvoidanceController_mpc_solveQP_qQaaXkaK(x,
      ObstacleAvoidanceController_B.c_Kx, ObstacleAvoidanceController_B.c_Kr,
      rseq, ObstacleAvoidanceController_B.c_Ku1, old_u,
      ObstacleAvoidanceController_B.c_Kv, vseq,
      ObstacleAvoidanceController_B.c_Kut, b_utarget,
      ObstacleAvoidanceController_B.c_Linv, ObstacleAvoidanceController_B.d_Linv,
      b_Ac, ObstacleAvoidanceController_B.b_Mlim_p, iAout,
      ObstacleAvoidanceController_B.zopt, ObstacleAvoidanceController_B.f,
      status);
    u[0] = (old_u[0] + ObstacleAvoidanceController_B.zopt[0]) + b_uoff[0];
    u[1] = (old_u[1] + ObstacleAvoidanceController_B.zopt[1]) + b_uoff[1];
  }
}

/* Model step function */
void ObstacleAvoidanceController_step(void)
{
  boolean_T rEQ0;
  static const int8_T tmp[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  static const real_T theta[5] = { 0.01495585217958292, 0.253939833006323,
    0.95041789961629319, 2.097847961257068, 5.3719203511481517 };

  static const uint8_T b[5] = { 3U, 5U, 7U, 9U, 13U };

  static const real_T c[36] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.27770760375671827, 0.0062434479946626509, 1.0, 0.0, 0.0, 0.0,
    0.00022476412780785541, -0.0099974737352418585, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  static const int8_T e[24] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 0, 0, 1, 0 };

  static const real_T d[54] = { 1.1238206390392769E-6, -4.99873686762093E-5, 0.0,
    0.01, 0.0, 0.0, 0.013566830996048695, 0.0003050107473845435,
    0.097705866260210286, 0.0, 0.0, 0.0, -0.42373623950128214,
    -0.28737444680072083, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T f[36] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  static const real_T g[87] = { 26.777777777777779, 26.777777777777779,
    26.777777777777779, 26.777777777777779, 26.777777777777779,
    26.777777777777779, 26.777777777777779, 26.777777777777779,
    26.777777777777779, 26.777777777777779, 26.777777777777779,
    26.777777777777779, 26.777777777777779, 26.777777777777779,
    26.777777777777779, 4.0, 0.62831853071795862, 4.0, 0.62831853071795862, 4.0,
    0.62831853071795862, 4.0, 0.62831853071795862, 4.0, 0.62831853071795862,
    7.85, 0.62831853071795862, 7.85, 0.62831853071795862, 7.85,
    0.62831853071795862, 7.85, 0.62831853071795862, 7.85, 0.62831853071795862,
    0.08, 0.010471975511965976, 0.08, 0.010471975511965976, 0.08,
    0.010471975511965976, 0.08, 0.010471975511965976, 0.08, 0.010471975511965976,
    0.2, 0.010471975511965976, 0.2, 0.010471975511965976, 0.2,
    0.010471975511965976, 0.2, 0.010471975511965976, 0.2, 0.010471975511965976,
    72.222222222222229, 127.77777777777777, 72.222222222222229,
    127.77777777777777, 72.222222222222229, 127.77777777777777,
    72.222222222222229, 127.77777777777777, 72.222222222222229,
    127.77777777777777, 72.222222222222229, 127.77777777777777,
    72.222222222222229, 127.77777777777777, 72.222222222222229,
    127.77777777777777, 72.222222222222229, 127.77777777777777,
    72.222222222222229, 127.77777777777777, 72.222222222222229,
    127.77777777777777, 72.222222222222229, 127.77777777777777,
    72.222222222222229, 127.77777777777777, 72.222222222222229,
    127.77777777777777, 72.222222222222229, 127.77777777777777,
    72.222222222222229, 127.77777777777777 };

  static const real_T n[6] = { 0.0, 0.0, -1.5483180211105141, 27.777777777777779,
    0.0, 0.0 };

  static const real_T h[55] = { 64.0, 68.0, 72.0, 76.0, 80.0, 84.0, 88.0, 92.0,
    96.0, 100.0, 104.0, 108.0, 112.0, 116.0, 120.0, 121.0, 122.0, 123.0, 124.0,
    125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 151.0, 152.0, 153.0, 154.0, 155.0,
    156.0, 157.0, 158.0, 159.0, 160.0, 181.0, 182.0, 183.0, 184.0, 185.0, 186.0,
    187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0, 194.0, 195.0, 196.0, 197.0,
    198.0, 199.0, 200.0 };

  static const real_T l[4] = { 0.0, 0.0, -1.5483180211105141, 27.777777777777779
  };

  static const real_T u[522] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0,
    1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0,
    1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0,
    1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0,
    1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T v[174] = { 0.01, 0.02, 0.03, 0.04, 0.05,
    0.060000000000000005, 0.07, 0.08, 0.09, 0.099999999999999992,
    0.10999999999999999, 0.11999999999999998, 0.12999999999999998,
    0.13999999999999999, 0.15, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.01, 0.01, -0.02, 0.02, -0.03, 0.03, -0.04, 0.04,
    -0.05, 0.05, -0.060000000000000005, 0.060000000000000005, -0.07, 0.07, -0.08,
    0.08, -0.09, 0.09, -0.099999999999999992, 0.099999999999999992,
    -0.10999999999999999, 0.10999999999999999, -0.11999999999999998,
    0.11999999999999998, -0.12999999999999998, 0.12999999999999998,
    -0.13999999999999999, 0.13999999999999999, -0.15, 0.15, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T w[121] = { 112.001202, -4.9960323180242991E-16,
    101.13919199999997, -4.1825196177450492E-16, 90.372759749999986,
    -4.0017082905982611E-16, 79.791894, -2.6409897902048623E-16, 69.4865655,
    -2.2204460492503131E-16, 0.0, -4.6364007944017831E-16, 30310.455008185338,
    -4.4808597043378079E-16, 25669.433785831363, -4.3133144262983905E-16,
    21439.884917202955, -3.0623186198593022E-16, 17621.590690516678,
    -4.4408920985006262E-16, 14213.007500058324, 0.0, 101.13919199999997,
    -5.078315837329413E-16, 91.63729575, -4.3475475180215372E-16,
    82.13996699999997, -3.3765621987612876E-16, 72.737203499999993,
    -2.6637270718904097E-16, 63.518994, -2.2204460492503131E-16, 0.0,
    -4.552653023372123E-16, 25669.433785831363, -3.4368539750097366E-16,
    21782.56379468727, -3.5959624894439515E-16, 18232.139388480093,
    -2.4312952176341504E-16, 15018.605802391778, -3.3306690738754696E-16,
    12141.745324638896, 0.0, 90.372759749999986, -5.4078959090968149E-16,
    82.13996699999997, -3.7954386007660869E-16, 73.91085975,
    -3.20539272921288E-16, 65.685437999999976, -2.5550772124516754E-16,
    57.553699499999993, -2.2204460492503131E-16, 0.0, -2.8789807088186303E-16,
    21439.884917202955, -3.2597013040381669E-16, 18232.139388480093,
    -2.7842893214504342E-16, 15295.870642085634, -2.3133040467411917E-16,
    12631.078678019578, -3.3306690738754696E-16, 10238.208731463883, 0.0,
    79.791894, -4.1561707790024882E-16, 72.737203499999993,
    -3.1537236092400905E-16, 65.685437999999976, -2.1147167864829996E-16,
    58.6365975, -1.6998466014338661E-16, 51.590681999999987,
    -1.1102230246251565E-16, 0.0, -2.9460529246167746E-16, 17621.590690516678,
    -2.8391786667979427E-16, 15018.605802391778, -2.9885179469429957E-16,
    12631.078678019578, -2.153233594867848E-16, 10459.009317400078,
    -1.1102230246251565E-16, 8502.3977205332758, 0.0, 69.486565499999983,
    -2.4877858774670163E-16, 63.518994, -2.9533743121065206E-16,
    57.553699499999993, -2.2276966059993935E-16, 51.590681999999987,
    -1.3208042148949737E-16, 45.629941500000008, -1.1102230246251565E-16, 0.0,
    -2.5334236215162429E-16, 14213.007500058326, -2.1752860632890646E-16,
    12141.745324638898, -2.5433138289839E-16, 10238.208731463881,
    -1.9510838620141191E-16, 8502.3977205332758, -2.2204460492503131E-16,
    6934.3122918470781, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    100000.0 };

  static const real_T y[957] = { 0.01, 0.02, 0.03, 0.04, 0.05,
    0.060000000000000005, 0.07, 0.08, 0.09, 0.099999999999999992,
    0.10999999999999999, 0.11999999999999998, 0.12999999999999998,
    0.13999999999999999, 0.15, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.01, 0.01, -0.02, 0.02, -0.03, 0.03, -0.04,
    0.04, -0.05, 0.05, -0.060000000000000005, 0.060000000000000005, -0.07, 0.07,
    -0.08, 0.08, -0.09, 0.09, -0.099999999999999992, 0.099999999999999992,
    -0.10999999999999999, 0.10999999999999999, -0.11999999999999998,
    0.11999999999999998, -0.12999999999999998, 0.12999999999999998,
    -0.13999999999999999, 0.13999999999999999, -0.15, 0.15, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.060000000000000005, 0.07,
    0.08, 0.09, 0.099999999999999992, 0.10999999999999999, 0.11999999999999998,
    0.12999999999999998, 0.13999999999999999, -0.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, -1.0, -0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.01, 0.01,
    -0.02, 0.02, -0.03, 0.03, -0.04, 0.04, -0.05, 0.05, -0.060000000000000005,
    0.060000000000000005, -0.07, 0.07, -0.08, 0.08, -0.09, 0.09,
    -0.099999999999999992, 0.099999999999999992, -0.10999999999999999,
    0.10999999999999999, -0.11999999999999998, 0.11999999999999998,
    -0.12999999999999998, 0.12999999999999998, -0.13999999999999999,
    0.13999999999999999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.01, 0.02,
    0.03, 0.04, 0.05, 0.060000000000000005, 0.07, 0.08, 0.09,
    0.099999999999999992, 0.10999999999999999, 0.11999999999999998,
    0.12999999999999998, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.01, 0.01, -0.02, 0.02,
    -0.03, 0.03, -0.04, 0.04, -0.05, 0.05, -0.060000000000000005,
    0.060000000000000005, -0.07, 0.07, -0.08, 0.08, -0.09, 0.09,
    -0.099999999999999992, 0.099999999999999992, -0.10999999999999999,
    0.10999999999999999, -0.11999999999999998, 0.11999999999999998,
    -0.12999999999999998, 0.12999999999999998, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -1.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0,
    0.0, 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.060000000000000005, 0.07, 0.08,
    0.09, 0.099999999999999992, 0.10999999999999999, 0.11999999999999998, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -1.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.01, 0.01, -0.02, 0.02, -0.03, 0.03,
    -0.04, 0.04, -0.05, 0.05, -0.060000000000000005, 0.060000000000000005, -0.07,
    0.07, -0.08, 0.08, -0.09, 0.09, -0.099999999999999992, 0.099999999999999992,
    -0.10999999999999999, 0.10999999999999999, -0.11999999999999998,
    0.11999999999999998, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.01, 0.02, 0.03, 0.04, 0.05, 0.060000000000000005, 0.07, 0.08, 0.09,
    0.099999999999999992, 0.10999999999999999, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.01, 0.01, -0.02, 0.02, -0.03, 0.03, -0.04, 0.04,
    -0.05, 0.05, -0.060000000000000005, 0.060000000000000005, -0.07, 0.07, -0.08,
    0.08, -0.09, 0.09, -0.099999999999999992, 0.099999999999999992,
    -0.10999999999999999, 0.10999999999999999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0,
    0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3,
    1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0, 0.3, 1.0 };

  static const real_T bb[300] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T gb[60] = { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0 };

  boolean_T exitg1;

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   *  Inport: '<Root>/param'
   *  Inport: '<Root>/u'
   */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       16; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i] = (real_T)
      tmp[ObstacleAvoidanceController_B.b_i];
  }

  /*  The model has four states: */
  /*  */
  /*  * |xPos| - Global horizontal position of the car center */
  /*  * |yPos| - Global vertical position of the car center */
  /*  * |theta| - Heading angle of the car (0 when facing east, counterclockwise positive) */
  /*  * |V| - Speed of the car (positve) */
  /*  There are two manipulated variables: */
  /*  * |throttle| - Throttle (positive when accelerating, negative when braking) */
  /*  * |delta| - Steering angle change (counterclockwise positive) */
  /*  There are two parameters: */
  /*  * |l_r| - Distance from CoG to rear axle */
  /*  * |l_f| - Distance from CoG to front axle */
  ObstacleAvoidanceController_B.carLength = ObstacleAvoidanceController_U.param
    [0] + ObstacleAvoidanceController_U.param[1];
  ObstacleAvoidanceController_B.b_s = tan(ObstacleAvoidanceController_U.u[1]);

  /*  Generate discrete-time model using ZOH. */
  ObstacleAvoidanceController_B.q2 = cos(ObstacleAvoidanceController_U.State[2]);
  ObstacleAvoidanceController_B.Curvature = sin
    (ObstacleAvoidanceController_U.State[2]);
  ObstacleAvoidanceController_B.A[0] = 0.0;
  ObstacleAvoidanceController_B.A[6] = 0.0;
  ObstacleAvoidanceController_B.A[12] = ((-ObstacleAvoidanceController_U.State[3])
    * ObstacleAvoidanceController_B.Curvature) * ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[18] = ObstacleAvoidanceController_B.q2 *
    ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[1] = 0.0;
  ObstacleAvoidanceController_B.A[7] = 0.0;
  ObstacleAvoidanceController_B.A[13] = (ObstacleAvoidanceController_U.State[3] *
    ObstacleAvoidanceController_B.q2) * ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[19] = ObstacleAvoidanceController_B.Curvature *
    ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[2] = 0.0;
  ObstacleAvoidanceController_B.A[8] = 0.0;
  ObstacleAvoidanceController_B.A[14] = 0.0;
  ObstacleAvoidanceController_B.A[20] = (ObstacleAvoidanceController_B.b_s /
    ObstacleAvoidanceController_B.carLength) * ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[3] = 0.0;
  ObstacleAvoidanceController_B.A[9] = 0.0;
  ObstacleAvoidanceController_B.A[15] = 0.0;
  ObstacleAvoidanceController_B.A[21] = 0.0;
  ObstacleAvoidanceController_B.A[26] = 0.0;
  ObstacleAvoidanceController_B.A[32] = ((((ObstacleAvoidanceController_B.b_s *
    ObstacleAvoidanceController_B.b_s) + 1.0) *
    ObstacleAvoidanceController_U.State[3]) /
    ObstacleAvoidanceController_B.carLength) * ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[24] = 0.0;
  ObstacleAvoidanceController_B.A[25] = 0.0;
  ObstacleAvoidanceController_B.A[27] = ObstacleAvoidanceController_Ts;
  ObstacleAvoidanceController_B.A[30] = 0.0;
  ObstacleAvoidanceController_B.A[31] = 0.0;
  ObstacleAvoidanceController_B.A[33] = 0.0;
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.A[(6 * ObstacleAvoidanceController_B.b_i) + 4]
      = 0.0;
    ObstacleAvoidanceController_B.A[(6 * ObstacleAvoidanceController_B.b_i) + 5]
      = 0.0;
  }

  ObstacleAvoidanceController_B.carLength = 0.0;
  ObstacleAvoidanceController_B.b_j = 0;
  exitg1 = false;
  while ((!exitg1) && (ObstacleAvoidanceController_B.b_j < 6)) {
    ObstacleAvoidanceController_B.b_s = 0.0;
    for (ObstacleAvoidanceController_B.b_i = 0;
         ObstacleAvoidanceController_B.b_i < 6;
         ObstacleAvoidanceController_B.b_i++) {
      ObstacleAvoidanceController_B.b_s += fabs(ObstacleAvoidanceController_B.A
        [(6 * ObstacleAvoidanceController_B.b_j) +
        ObstacleAvoidanceController_B.b_i]);
    }

    if (rtIsNaN(ObstacleAvoidanceController_B.b_s)) {
      ObstacleAvoidanceController_B.carLength = (rtNaN);
      exitg1 = true;
    } else {
      if (ObstacleAvoidanceController_B.b_s >
          ObstacleAvoidanceController_B.carLength) {
        ObstacleAvoidanceController_B.carLength =
          ObstacleAvoidanceController_B.b_s;
      }

      ObstacleAvoidanceController_B.b_j++;
    }
  }

  if (ObstacleAvoidanceController_B.carLength <= 5.3719203511481517) {
    ObstacleAvoidanceController_B.b_i = 0;
    exitg1 = false;
    while ((!exitg1) && (ObstacleAvoidanceController_B.b_i < 5)) {
      if (ObstacleAvoidanceController_B.carLength <=
          theta[ObstacleAvoidanceController_B.b_i]) {
        ObstacleAvoidanceController_PadeApproximantOfDegree_quffSMBJ
          (ObstacleAvoidanceController_B.A, b[ObstacleAvoidanceController_B.b_i],
           ObstacleAvoidanceController_B.M);
        exitg1 = true;
      } else {
        ObstacleAvoidanceController_B.b_i++;
      }
    }
  } else {
    ObstacleAvoidanceController_B.b_s = ObstacleAvoidanceController_B.carLength /
      5.3719203511481517;
    if ((!rtIsInf(ObstacleAvoidanceController_B.b_s)) && (!rtIsNaN
         (ObstacleAvoidanceController_B.b_s))) {
      ObstacleAvoidanceController_B.b_s = frexp
        (ObstacleAvoidanceController_B.b_s, &ObstacleAvoidanceController_B.e);
    } else {
      ObstacleAvoidanceController_B.e = 0;
    }

    ObstacleAvoidanceController_B.carLength = (real_T)
      ObstacleAvoidanceController_B.e;
    if (ObstacleAvoidanceController_B.b_s == 0.5) {
      ObstacleAvoidanceController_B.carLength = ((real_T)
        ObstacleAvoidanceController_B.e) - 1.0;
    }

    ObstacleAvoidanceController_B.b_s = rt_powd_snf(2.0,
      ObstacleAvoidanceController_B.carLength);
    for (ObstacleAvoidanceController_B.b_i = 0;
         ObstacleAvoidanceController_B.b_i < 36;
         ObstacleAvoidanceController_B.b_i++) {
      ObstacleAvoidanceController_B.A_m[ObstacleAvoidanceController_B.b_i] =
        ObstacleAvoidanceController_B.A[ObstacleAvoidanceController_B.b_i] /
        ObstacleAvoidanceController_B.b_s;
    }

    ObstacleAvoidanceController_PadeApproximantOfDegree_quffSMBJ
      (ObstacleAvoidanceController_B.A_m, 13, ObstacleAvoidanceController_B.M);
    ObstacleAvoidanceController_B.j = 0;
    while (ObstacleAvoidanceController_B.j <= (((int32_T)
             ObstacleAvoidanceController_B.carLength) - 1)) {
      for (ObstacleAvoidanceController_B.b_i = 0;
           ObstacleAvoidanceController_B.b_i < 6;
           ObstacleAvoidanceController_B.b_i++) {
        for (ObstacleAvoidanceController_B.e = 0;
             ObstacleAvoidanceController_B.e < 6;
             ObstacleAvoidanceController_B.e++) {
          ObstacleAvoidanceController_B.M_tmp =
            ObstacleAvoidanceController_B.b_i + (6 *
            ObstacleAvoidanceController_B.e);
          ObstacleAvoidanceController_B.A[ObstacleAvoidanceController_B.M_tmp] =
            0.0;
          for (ObstacleAvoidanceController_B.b_j = 0;
               ObstacleAvoidanceController_B.b_j < 6;
               ObstacleAvoidanceController_B.b_j++) {
            ObstacleAvoidanceController_B.A[ObstacleAvoidanceController_B.M_tmp]
              += ObstacleAvoidanceController_B.M[(6 *
              ObstacleAvoidanceController_B.b_j) +
              ObstacleAvoidanceController_B.b_i] *
              ObstacleAvoidanceController_B.M[(6 *
              ObstacleAvoidanceController_B.e) +
              ObstacleAvoidanceController_B.b_j];
          }
        }
      }

      (void)memcpy(&ObstacleAvoidanceController_B.M[0],
                   &ObstacleAvoidanceController_B.A[0], 36U * (sizeof(real_T)));
      ObstacleAvoidanceController_B.j++;
    }
  }

  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       4; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.e = ObstacleAvoidanceController_B.b_i * 4;
    ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.e] =
      ObstacleAvoidanceController_B.M[6 * ObstacleAvoidanceController_B.b_i];
    ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.e + 1] =
      ObstacleAvoidanceController_B.M[(6 * ObstacleAvoidanceController_B.b_i) +
      1];
    ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.e + 2] =
      ObstacleAvoidanceController_B.M[(6 * ObstacleAvoidanceController_B.b_i) +
      2];
    ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.e + 3] =
      ObstacleAvoidanceController_B.M[(6 * ObstacleAvoidanceController_B.b_i) +
      3];
  }

  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       2; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.e = (ObstacleAvoidanceController_B.b_i + 4) *
      6;
    ObstacleAvoidanceController_B.b_j = ObstacleAvoidanceController_B.b_i * 4;
    ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_j] =
      ObstacleAvoidanceController_B.M[ObstacleAvoidanceController_B.e];
    ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_j + 1] =
      ObstacleAvoidanceController_B.M[ObstacleAvoidanceController_B.e + 1];
    ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_j + 2] =
      ObstacleAvoidanceController_B.M[ObstacleAvoidanceController_B.e + 2];
    ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_j + 3] =
      ObstacleAvoidanceController_B.M[ObstacleAvoidanceController_B.e + 3];
  }

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Ref_pSteps'
   */
  /*  Nominal conditions for discrete-time plant */
  /*  curvatureEstimator try to estimate the curvature of the road in the next */
  /*  small portion, by making the average of the values in the reference angle */
  /*  of the road for the prediction horizon */
  ObstacleAvoidanceController_B.carLength =
    ObstacleAvoidanceController_U.Ref_pSteps[30];
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       15; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.x[ObstacleAvoidanceController_B.b_i] =
      ObstacleAvoidanceController_U.Ref_pSteps[ObstacleAvoidanceController_B.b_i
      + 30] - ObstacleAvoidanceController_B.carLength;
  }

  ObstacleAvoidanceController_B.b_s = ObstacleAvoidanceController_B.x[0];
  for (ObstacleAvoidanceController_B.j = 0; ObstacleAvoidanceController_B.j < 14;
       ObstacleAvoidanceController_B.j++) {
    ObstacleAvoidanceController_B.b_s +=
      ObstacleAvoidanceController_B.x[ObstacleAvoidanceController_B.j + 1];
  }

  ObstacleAvoidanceController_B.Curvature = ObstacleAvoidanceController_B.b_s /
    15.0;

  /* End of MATLAB Function: '<S4>/MATLAB Function' */

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Inport: '<Root>/DetPoint'
   *  Inport: '<Root>/EndX'
   *  Inport: '<Root>/EndY'
   *  Inport: '<Root>/EntryPoint'
   *  Inport: '<Root>/Lw'
   *  Inport: '<Root>/Reference'
   *  Inport: '<Root>/SafeX'
   *  Inport: '<Root>/SafeY'
   *  Inport: '<Root>/Zone'
   *  Inport: '<Root>/detection'
   */
  /*  LaneKeepConstraint function generates the matrices E F G to give to the */
  /*  controller in order to define linear constraint. */
  /*  */
  /*  Controller needs to satisfy the following equation: */
  /*            E*u(k+j)+F*y(k+j)<=G */
  /*  LaneKeepConstraint take as input: */
  /*  - Reference -         Actual reference point for the controller */
  /*  - Lw -                [m] Lane Width */
  /*  - detection -     flag that is 1 when obstacle is detected, 0 otherwise */
  /*  - SafeX,SafeY -   Point where starts the Safe Zone, as lower bound of the */
  /*                    overtaking (left) lane */
  /*  - EndX,EndY -     Point where ends the Safe Zone, as lower bound of the */
  /*  - EntryPoint -    Point in the reference map, after the obstacle, where */
  /*                    the vehicle should return after the overtaking maneuver */
  /*  - Zone -          flag that tell where the vehicle is with respect to the */
  /*                    obstacle. Outcomes are: */
  /*                        - 0 - No obstacle */
  /*                        - 1 - Well before the obstacle */
  /*                        - 2 - Before the obstacle, leave the lane */
  /*                        - 3 - In the Safe Zone, stay in the left lane */
  /*                        - 4 - After the Safe Zone, come back in your lane */
  /*                        - 5 - Obstacle passed  */
  /*  - DetectionPoint -    Point where to start leave the lane to go in the */
  /*                        Safe Zone */
  /*  Acquire the Reference point */
  /*  Normalize Theta_ref to -pi:pi */
  if (rtIsNaN(ObstacleAvoidanceController_U.Reference[2] + 3.1415926535897931))
  {
    ObstacleAvoidanceController_B.carLength = (rtNaN);
  } else if (rtIsInf(ObstacleAvoidanceController_U.Reference[2] +
                     3.1415926535897931)) {
    ObstacleAvoidanceController_B.carLength = (rtNaN);
  } else if ((ObstacleAvoidanceController_U.Reference[2] + 3.1415926535897931) ==
             0.0) {
    ObstacleAvoidanceController_B.carLength = 0.0;
  } else {
    ObstacleAvoidanceController_B.carLength = fmod
      (ObstacleAvoidanceController_U.Reference[2] + 3.1415926535897931,
       6.2831853071795862);
    rEQ0 = (ObstacleAvoidanceController_B.carLength == 0.0);
    if (!rEQ0) {
      ObstacleAvoidanceController_B.b_s = fabs
        ((ObstacleAvoidanceController_U.Reference[2] + 3.1415926535897931) /
         6.2831853071795862);
      rEQ0 = !(fabs(ObstacleAvoidanceController_B.b_s - floor
                    (ObstacleAvoidanceController_B.b_s + 0.5)) >
               (2.2204460492503131E-16 * ObstacleAvoidanceController_B.b_s));
    }

    if (rEQ0) {
      ObstacleAvoidanceController_B.carLength = 0.0;
    } else if ((ObstacleAvoidanceController_U.Reference[2] + 3.1415926535897931)
               < 0.0) {
      ObstacleAvoidanceController_B.carLength += 6.2831853071795862;
    } else {
      /* no actions */
    }
  }

  ObstacleAvoidanceController_B.carLength -= 3.1415926535897931;

  /*  Set 0 constraints on input */
  /*  Point where to reenter in the lane when obstacle is passed */
  /*  Point where to leave tha lane when obstacle is detected */
  /*  Road orientation */
  ObstacleAvoidanceController_B.b_s = tan
    (ObstacleAvoidanceController_B.carLength);
  if (fabs(ObstacleAvoidanceController_B.b_s) > 1.0) {
    /*  Close to vertical */
    ObstacleAvoidanceController_B.b_s = 1.0 / tan
      (ObstacleAvoidanceController_B.carLength);

    /*  Inverse angular coefficient */
    /*  Lane boundaries */
    if (ObstacleAvoidanceController_U.detection != 0.0) {
      ObstacleAvoidanceController_B.q2 = sin
        (ObstacleAvoidanceController_B.carLength);
      ObstacleAvoidanceController_B.constraintIntercept =
        ObstacleAvoidanceController_B.b_s *
        ObstacleAvoidanceController_U.Reference[1];
      ObstacleAvoidanceController_B.q2 =
        ((ObstacleAvoidanceController_U.Reference[0] - ((0.5 *
            ObstacleAvoidanceController_U.Lw) / ObstacleAvoidanceController_B.q2))
         - ObstacleAvoidanceController_B.constraintIntercept) -
        (ObstacleAvoidanceController_U.Lw / ObstacleAvoidanceController_B.q2);

      /*  Bound of the overtaking lane */
      if (ObstacleAvoidanceController_U.Zone == 2.0) {
        /*  Before the Safe, change line */
        ObstacleAvoidanceController_B.Curvature =
          (ObstacleAvoidanceController_U.SafeX -
           ObstacleAvoidanceController_U.DetPoint[0]) /
          (ObstacleAvoidanceController_U.SafeY -
           ObstacleAvoidanceController_U.DetPoint[1]);
        ObstacleAvoidanceController_B.constraintIntercept =
          ObstacleAvoidanceController_U.SafeX -
          (ObstacleAvoidanceController_B.Curvature *
           ObstacleAvoidanceController_U.SafeY);
      } else if (ObstacleAvoidanceController_U.Zone == 3.0) {
        /*  In the Safe Zone */
        ObstacleAvoidanceController_B.Curvature =
          ObstacleAvoidanceController_B.b_s - ((416.0 /
          ObstacleAvoidanceController_U.Reference[3]) * fabs
          (ObstacleAvoidanceController_B.Curvature));
        ObstacleAvoidanceController_B.constraintIntercept =
          (ObstacleAvoidanceController_U.Reference[0] -
           (ObstacleAvoidanceController_U.Lw / sin
            (ObstacleAvoidanceController_B.carLength))) -
          (ObstacleAvoidanceController_B.Curvature *
           ObstacleAvoidanceController_U.Reference[1]);
      } else if (ObstacleAvoidanceController_U.Zone == 4.0) {
        /*  After the Safe */
        ObstacleAvoidanceController_B.Curvature =
          (ObstacleAvoidanceController_U.EntryPoint[0] -
           ObstacleAvoidanceController_U.EndX) /
          (ObstacleAvoidanceController_U.EntryPoint[1] -
           ObstacleAvoidanceController_U.EndY);
        ObstacleAvoidanceController_B.constraintIntercept =
          ObstacleAvoidanceController_U.EntryPoint[0] -
          (ObstacleAvoidanceController_B.Curvature *
           ObstacleAvoidanceController_U.EntryPoint[1]);
      } else {
        /* Far from the obstacle */
        ObstacleAvoidanceController_B.Curvature =
          ObstacleAvoidanceController_B.b_s;
        ObstacleAvoidanceController_B.constraintIntercept = (((0.5 *
          ObstacleAvoidanceController_U.Lw) / sin
          (ObstacleAvoidanceController_B.carLength)) +
          ObstacleAvoidanceController_U.Reference[0]) -
          ObstacleAvoidanceController_B.constraintIntercept;
      }

      if ((ObstacleAvoidanceController_B.carLength > 0.0) &&
          (ObstacleAvoidanceController_B.Curvature <= 0.0)) {
        /*  x < constraintIntercept + constraintSlope*Y */
        /*  x > q2 + m*Y */
        ObstacleAvoidanceController_B.F[0] = 1.0;
        ObstacleAvoidanceController_B.F[2] =
          -ObstacleAvoidanceController_B.Curvature;
        ObstacleAvoidanceController_B.F[4] = 0.0;
        ObstacleAvoidanceController_B.F[6] = 0.0;
        ObstacleAvoidanceController_B.F[1] = -1.0;
        ObstacleAvoidanceController_B.F[3] = ObstacleAvoidanceController_B.b_s;
        ObstacleAvoidanceController_B.F[5] = 0.0;
        ObstacleAvoidanceController_B.F[7] = 0.0;
        ObstacleAvoidanceController_B.G[0] =
          ObstacleAvoidanceController_B.constraintIntercept;
        ObstacleAvoidanceController_B.G[1] = -ObstacleAvoidanceController_B.q2;
      } else if ((ObstacleAvoidanceController_B.carLength < 0.0) &&
                 (ObstacleAvoidanceController_B.Curvature > 0.0)) {
        /*  x > constraintIntercept + constraintSlope*Y */
        /*  x < q2 + m*Y */
        ObstacleAvoidanceController_B.F[0] = -1.0;
        ObstacleAvoidanceController_B.F[2] =
          ObstacleAvoidanceController_B.Curvature;
        ObstacleAvoidanceController_B.F[4] = 0.0;
        ObstacleAvoidanceController_B.F[6] = 0.0;
        ObstacleAvoidanceController_B.F[1] = 1.0;
        ObstacleAvoidanceController_B.F[3] = -ObstacleAvoidanceController_B.b_s;
        ObstacleAvoidanceController_B.F[5] = 0.0;
        ObstacleAvoidanceController_B.F[7] = 0.0;
        ObstacleAvoidanceController_B.G[0] =
          -ObstacleAvoidanceController_B.constraintIntercept;
        ObstacleAvoidanceController_B.G[1] = ObstacleAvoidanceController_B.q2;
      } else if ((ObstacleAvoidanceController_B.carLength > 0.0) &&
                 (ObstacleAvoidanceController_B.Curvature > 0.0)) {
        /*  x < constraintIntercept + constraintSlope*Y */
        /*  x > q2 + m*Y */
        ObstacleAvoidanceController_B.F[0] = 1.0;
        ObstacleAvoidanceController_B.F[2] =
          -ObstacleAvoidanceController_B.Curvature;
        ObstacleAvoidanceController_B.F[4] = 0.0;
        ObstacleAvoidanceController_B.F[6] = 0.0;
        ObstacleAvoidanceController_B.F[1] = -1.0;
        ObstacleAvoidanceController_B.F[3] = ObstacleAvoidanceController_B.b_s;
        ObstacleAvoidanceController_B.F[5] = 0.0;
        ObstacleAvoidanceController_B.F[7] = 0.0;
        ObstacleAvoidanceController_B.G[0] =
          ObstacleAvoidanceController_B.constraintIntercept;
        ObstacleAvoidanceController_B.G[1] = -ObstacleAvoidanceController_B.q2;
      } else {
        /*  x > constraintIntercept + constraintSlope*Y */
        /*  x < q2 + m*Y */
        ObstacleAvoidanceController_B.F[0] = -1.0;
        ObstacleAvoidanceController_B.F[2] =
          ObstacleAvoidanceController_B.Curvature;
        ObstacleAvoidanceController_B.F[4] = 0.0;
        ObstacleAvoidanceController_B.F[6] = 0.0;
        ObstacleAvoidanceController_B.F[1] = 1.0;
        ObstacleAvoidanceController_B.F[3] = -ObstacleAvoidanceController_B.b_s;
        ObstacleAvoidanceController_B.F[5] = 0.0;
        ObstacleAvoidanceController_B.F[7] = 0.0;
        ObstacleAvoidanceController_B.G[0] =
          -ObstacleAvoidanceController_B.constraintIntercept;
        ObstacleAvoidanceController_B.G[1] = ObstacleAvoidanceController_B.q2;
      }
    } else {
      /*  No obstacle */
      /*              if Theta_ref < 0 */
      /*                  F = [-1 m 0 0 */
      /*                      1 -m 0 0]; */
      /*                  G = [-q1; q2]; */
      /*              else */
      /*                  F = [1 -m 0 0 */
      /*                      -1 m 0 0]; */
      /*                  G = [q1; -q2]; */
      /*              end */
      (void)memset(&ObstacleAvoidanceController_B.F[0], 0, (sizeof(real_T)) <<
                   3U);
      ObstacleAvoidanceController_B.G[0] = 0.0;
      ObstacleAvoidanceController_B.G[1] = 0.0;
    }

    /*  close to horizontal */
  } else if (ObstacleAvoidanceController_U.detection != 0.0) {
    ObstacleAvoidanceController_B.q2 = cos
      (ObstacleAvoidanceController_B.carLength);
    ObstacleAvoidanceController_B.constraintIntercept =
      ObstacleAvoidanceController_B.b_s *
      ObstacleAvoidanceController_U.Reference[0];
    ObstacleAvoidanceController_B.q2 = ((((0.5 *
      ObstacleAvoidanceController_U.Lw) / ObstacleAvoidanceController_B.q2) +
      ObstacleAvoidanceController_U.Reference[1]) -
      ObstacleAvoidanceController_B.constraintIntercept) +
      (ObstacleAvoidanceController_U.Lw / ObstacleAvoidanceController_B.q2);
    if (ObstacleAvoidanceController_U.Zone == 2.0) {
      /*  Before the Safe */
      ObstacleAvoidanceController_B.Curvature =
        (ObstacleAvoidanceController_U.SafeY -
         ObstacleAvoidanceController_U.DetPoint[1]) /
        (ObstacleAvoidanceController_U.SafeX -
         ObstacleAvoidanceController_U.DetPoint[0]);
      ObstacleAvoidanceController_B.constraintIntercept =
        ObstacleAvoidanceController_U.SafeY -
        (ObstacleAvoidanceController_B.Curvature *
         ObstacleAvoidanceController_U.SafeX);
    } else if (ObstacleAvoidanceController_U.Zone == 3.0) {
      /*  In the Safe Zone */
      /*                  slope = ( (EndY - SafeY)/(EndX - SafeX) ); */
      /*                  constraintSlope = slope; */
      /*                  constraintIntercept = EndY - constraintSlope*EndX; */
      ObstacleAvoidanceController_B.Curvature = ((416.0 /
        ObstacleAvoidanceController_U.Reference[3]) * fabs
        (ObstacleAvoidanceController_B.Curvature)) +
        ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.constraintIntercept =
        ((ObstacleAvoidanceController_U.Lw / cos
          (ObstacleAvoidanceController_B.carLength)) +
         ObstacleAvoidanceController_U.Reference[1]) -
        (ObstacleAvoidanceController_B.Curvature *
         ObstacleAvoidanceController_U.Reference[0]);
    } else if (ObstacleAvoidanceController_U.Zone == 4.0) {
      /*  After the Safe */
      ObstacleAvoidanceController_B.Curvature =
        (ObstacleAvoidanceController_U.EntryPoint[1] -
         ObstacleAvoidanceController_U.EndY) /
        (ObstacleAvoidanceController_U.EntryPoint[0] -
         ObstacleAvoidanceController_U.EndX);
      ObstacleAvoidanceController_B.constraintIntercept =
        ObstacleAvoidanceController_U.EntryPoint[1] -
        (ObstacleAvoidanceController_B.Curvature *
         ObstacleAvoidanceController_U.EntryPoint[0]);
    } else {
      ObstacleAvoidanceController_B.Curvature =
        ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.constraintIntercept =
        (ObstacleAvoidanceController_U.Reference[1] - ((0.5 *
           ObstacleAvoidanceController_U.Lw) / cos
          (ObstacleAvoidanceController_B.carLength))) -
        ObstacleAvoidanceController_B.constraintIntercept;
    }

    ObstacleAvoidanceController_B.carLength = fabs
      (ObstacleAvoidanceController_B.carLength);
    if ((ObstacleAvoidanceController_B.carLength <= 1.5707963267948966) &&
        (ObstacleAvoidanceController_B.Curvature >= 0.0)) {
      /*  y > constraintIntercept + constraintSlope*X */
      /*  y < q2 + m*X */
      ObstacleAvoidanceController_B.F[0] =
        ObstacleAvoidanceController_B.Curvature;
      ObstacleAvoidanceController_B.F[2] = -1.0;
      ObstacleAvoidanceController_B.F[4] = 0.0;
      ObstacleAvoidanceController_B.F[6] = 0.0;
      ObstacleAvoidanceController_B.F[1] = -ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.F[3] = 1.0;
      ObstacleAvoidanceController_B.F[5] = 0.0;
      ObstacleAvoidanceController_B.F[7] = 0.0;
      ObstacleAvoidanceController_B.G[0] =
        -ObstacleAvoidanceController_B.constraintIntercept;
      ObstacleAvoidanceController_B.G[1] = ObstacleAvoidanceController_B.q2;
    } else if ((ObstacleAvoidanceController_B.carLength > 1.5707963267948966) &&
               (ObstacleAvoidanceController_B.Curvature < 0.0)) {
      /*  y < constraintIntercept + constraintSlope*X */
      /*  y > q2 + m*X */
      ObstacleAvoidanceController_B.F[0] =
        -ObstacleAvoidanceController_B.Curvature;
      ObstacleAvoidanceController_B.F[2] = 1.0;
      ObstacleAvoidanceController_B.F[4] = 0.0;
      ObstacleAvoidanceController_B.F[6] = 0.0;
      ObstacleAvoidanceController_B.F[1] = ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.F[3] = -1.0;
      ObstacleAvoidanceController_B.F[5] = 0.0;
      ObstacleAvoidanceController_B.F[7] = 0.0;
      ObstacleAvoidanceController_B.G[0] =
        ObstacleAvoidanceController_B.constraintIntercept;
      ObstacleAvoidanceController_B.G[1] = -ObstacleAvoidanceController_B.q2;
    } else if ((ObstacleAvoidanceController_B.carLength <= 1.5707963267948966) &&
               (ObstacleAvoidanceController_B.Curvature < 0.0)) {
      /*  y > constraintIntercept + constraintSlope*X */
      /*  y < q2 + m*X */
      ObstacleAvoidanceController_B.F[0] =
        ObstacleAvoidanceController_B.Curvature;
      ObstacleAvoidanceController_B.F[2] = -1.0;
      ObstacleAvoidanceController_B.F[4] = 0.0;
      ObstacleAvoidanceController_B.F[6] = 0.0;
      ObstacleAvoidanceController_B.F[1] = -ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.F[3] = 1.0;
      ObstacleAvoidanceController_B.F[5] = 0.0;
      ObstacleAvoidanceController_B.F[7] = 0.0;
      ObstacleAvoidanceController_B.G[0] =
        -ObstacleAvoidanceController_B.constraintIntercept;
      ObstacleAvoidanceController_B.G[1] = ObstacleAvoidanceController_B.q2;
    } else {
      ObstacleAvoidanceController_B.F[0] =
        -ObstacleAvoidanceController_B.Curvature;
      ObstacleAvoidanceController_B.F[2] = 1.0;
      ObstacleAvoidanceController_B.F[4] = 0.0;
      ObstacleAvoidanceController_B.F[6] = 0.0;
      ObstacleAvoidanceController_B.F[1] = ObstacleAvoidanceController_B.b_s;
      ObstacleAvoidanceController_B.F[3] = -1.0;
      ObstacleAvoidanceController_B.F[5] = 0.0;
      ObstacleAvoidanceController_B.F[7] = 0.0;
      ObstacleAvoidanceController_B.G[0] =
        ObstacleAvoidanceController_B.constraintIntercept;
      ObstacleAvoidanceController_B.G[1] = -ObstacleAvoidanceController_B.q2;
    }
  } else {
    /*              if abs(Theta_ref) < pi/2 */
    /*                  F = [-m 1 0 0 */
    /*                      m -1 0 0]; */
    /*                  G = [-q1; q2]; */
    /*              else */
    /*                  F = [m -1 0 0 */
    /*                      -m 1 0 0]; */
    /*                  G = [q1; -q2]; */
    /*              end */
    (void)memset(&ObstacleAvoidanceController_B.F[0], 0, (sizeof(real_T)) << 3U);
    ObstacleAvoidanceController_B.G[0] = 0.0;
    ObstacleAvoidanceController_B.G[1] = 0.0;
  }

  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  /*  Constants */
  /*  isLTV=true forces isAdaptive=false */
  /*  Pre-allocate all the MEX block outputs for the simulation mode */
  /*  Model update */
  /*  Allocate matrices. Must allocate 3D matrix also in Adaptive case, */
  /*  otherwise EML code does not compile. */
  (void)memset(&ObstacleAvoidanceController_B.Bu[0], 0, 192U * (sizeof(real_T)));
  (void)memset(&ObstacleAvoidanceController_B.Bv[0], 0, 96U * (sizeof(real_T)));
  (void)memset(&ObstacleAvoidanceController_B.Dv_f[0], 0, (sizeof(real_T)) << 6U);
  (void)memset(&ObstacleAvoidanceController_B.Dvm[0], 0, (sizeof(real_T)) << 6U);
  (void)memset(&ObstacleAvoidanceController_B.Cm[0], 0, 384U * (sizeof(real_T)));

  /*  Adaptive */
  (void)memcpy(&ObstacleAvoidanceController_B.A[0], &c[0], 36U * (sizeof(real_T)));
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       24; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.b_C_j[ObstacleAvoidanceController_B.b_i] =
      (real_T)e[ObstacleAvoidanceController_B.b_i];
  }

  ObstacleAvoidanceController_B.dv8[0] = 1.0;
  ObstacleAvoidanceController_B.dv8[1] = 2.0;
  ObstacleAvoidanceController_B.b_myoff[0] = 1.0;
  ObstacleAvoidanceController_B.b_myoff[1] = 2.0;
  ObstacleAvoidanceController_B.b_myoff[2] = 3.0;
  ObstacleAvoidanceController_B.b_myoff[3] = 4.0;
  ObstacleAvoidanceController_B.dv9[0] = 1.0;
  ObstacleAvoidanceController_B.dv9[1] = 1.0;
  ObstacleAvoidanceController_B.y_innov[0] = 1.0;
  ObstacleAvoidanceController_B.y_innov[1] = 1.0;
  ObstacleAvoidanceController_B.y_innov[2] = 1.0;
  ObstacleAvoidanceController_B.y_innov[3] = 1.0;
  (void)memcpy(&ObstacleAvoidanceController_B.rtb_B_l[0],
               &ObstacleAvoidanceController_B.B[0], 8U * (sizeof(real_T)));
  (void)memcpy(&ObstacleAvoidanceController_B.d[0], &d[0], 54U * (sizeof(real_T)));
  ObstacleAvoidanceController_mpc_plantupdate_ktgMNkJb
    (ObstacleAvoidanceController_B.A_d, ObstacleAvoidanceController_B.rtb_B_l,
     ObstacleAvoidanceController_B.C, ObstacleAvoidanceController_B.A,
     ObstacleAvoidanceController_B.d, ObstacleAvoidanceController_B.b_C_j, f,
     ObstacleAvoidanceController_B.dv8, ObstacleAvoidanceController_B.b_myoff,
     ObstacleAvoidanceController_B.dv9, ObstacleAvoidanceController_B.y_innov,
     &ObstacleAvoidanceController_B.Bu[0], &ObstacleAvoidanceController_B.Bv[0],
     ObstacleAvoidanceController_B.L, &ObstacleAvoidanceController_B.Dv_f[0],
     &ObstacleAvoidanceController_B.Dvm[0], ObstacleAvoidanceController_B.M,
     ObstacleAvoidanceController_B.Kinv, ObstacleAvoidanceController_B.Nk);
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.b_j = ObstacleAvoidanceController_B.b_i * 4;
    ObstacleAvoidanceController_B.Cm[ObstacleAvoidanceController_B.b_j] =
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j];
    ObstacleAvoidanceController_B.Cm[ObstacleAvoidanceController_B.b_j + 1] =
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j + 1];
    ObstacleAvoidanceController_B.Cm[ObstacleAvoidanceController_B.b_j + 2] =
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j + 2];
    ObstacleAvoidanceController_B.Cm[ObstacleAvoidanceController_B.b_j + 3] =
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j + 3];
  }

  /*  Offset update together with Mlim, utarget, Bv and Dv values */
  (void)memcpy(&ObstacleAvoidanceController_B.b_Mlim[0], &g[0], 87U * (sizeof
    (real_T)));
  (void)memset(&ObstacleAvoidanceController_B.b_utarget[0], 0, 30U * (sizeof
    (real_T)));
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.b_xoff[ObstacleAvoidanceController_B.b_i] =
      n[ObstacleAvoidanceController_B.b_i];
  }

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   *  Inport: '<Root>/u'
   */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       4; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.rtb_C_e[ObstacleAvoidanceController_B.b_i] =
      (ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i + 12] *
       ObstacleAvoidanceController_U.State[3]) +
      ((ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i + 8] *
        ObstacleAvoidanceController_U.State[2]) +
       ((ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i + 4] *
         ObstacleAvoidanceController_U.State[1]) +
        (ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i] *
         ObstacleAvoidanceController_U.State[0])));
    ObstacleAvoidanceController_B.b_myoff[ObstacleAvoidanceController_B.b_i] =
      (0.0 * ObstacleAvoidanceController_U.u[1]) + (0.0 *
      ObstacleAvoidanceController_U.u[0]);
    ObstacleAvoidanceController_B.rtb_A_b[ObstacleAvoidanceController_B.b_i] =
      (ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.b_i + 12]
       * ObstacleAvoidanceController_U.State[3]) +
      ((ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.b_i + 8]
        * ObstacleAvoidanceController_U.State[2]) +
       ((ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.b_i + 4]
         * ObstacleAvoidanceController_U.State[1]) +
        (ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.b_i] *
         ObstacleAvoidanceController_U.State[0])));
    ObstacleAvoidanceController_B.rtb_B_j[ObstacleAvoidanceController_B.b_i] =
      (ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_i + 4] *
       ObstacleAvoidanceController_U.u[1]) +
      (ObstacleAvoidanceController_B.B[ObstacleAvoidanceController_B.b_i] *
       ObstacleAvoidanceController_U.u[0]);
  }

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  ObstacleAvoidanceController_B.dv8[0] = 1.0;
  ObstacleAvoidanceController_B.dv9[0] = 0.0;
  ObstacleAvoidanceController_B.dv10[0] = 1.0;
  ObstacleAvoidanceController_B.dv8[1] = 1.0;
  ObstacleAvoidanceController_B.dv9[1] = 0.0;
  ObstacleAvoidanceController_B.dv10[1] = 2.0;

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' */
  ObstacleAvoidanceController_B.rtb_C_f[0] =
    ObstacleAvoidanceController_B.rtb_C_e[0] +
    ObstacleAvoidanceController_B.b_myoff[0];

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  ObstacleAvoidanceController_B.y_innov[0] = 1.0;
  ObstacleAvoidanceController_B.dv7[0] = 1.0;

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   */
  ObstacleAvoidanceController_B.rtb_A_a[0] =
    (ObstacleAvoidanceController_B.rtb_A_b[0] +
     ObstacleAvoidanceController_B.rtb_B_j[0]) -
    ObstacleAvoidanceController_U.State[0];
  ObstacleAvoidanceController_B.rtb_C_f[1] =
    ObstacleAvoidanceController_B.rtb_C_e[1] +
    ObstacleAvoidanceController_B.b_myoff[1];

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  ObstacleAvoidanceController_B.y_innov[1] = 1.0;
  ObstacleAvoidanceController_B.dv7[1] = 2.0;

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   */
  ObstacleAvoidanceController_B.rtb_A_a[1] =
    (ObstacleAvoidanceController_B.rtb_A_b[1] +
     ObstacleAvoidanceController_B.rtb_B_j[1]) -
    ObstacleAvoidanceController_U.State[1];
  ObstacleAvoidanceController_B.rtb_C_f[2] =
    ObstacleAvoidanceController_B.rtb_C_e[2] +
    ObstacleAvoidanceController_B.b_myoff[2];

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  ObstacleAvoidanceController_B.y_innov[2] = 1.0;
  ObstacleAvoidanceController_B.dv7[2] = 3.0;

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   */
  ObstacleAvoidanceController_B.rtb_A_a[2] =
    (ObstacleAvoidanceController_B.rtb_A_b[2] +
     ObstacleAvoidanceController_B.rtb_B_j[2]) -
    ObstacleAvoidanceController_U.State[2];
  ObstacleAvoidanceController_B.rtb_C_f[3] =
    ObstacleAvoidanceController_B.rtb_C_e[3] +
    ObstacleAvoidanceController_B.b_myoff[3];

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  ObstacleAvoidanceController_B.y_innov[3] = 1.0;
  ObstacleAvoidanceController_B.dv7[3] = 4.0;

  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */

  /* MATLAB Function: '<S3>/Plant Model Generator' incorporates:
   *  Inport: '<Root>/State '
   */
  ObstacleAvoidanceController_B.rtb_A_a[3] =
    (ObstacleAvoidanceController_B.rtb_A_b[3] +
     ObstacleAvoidanceController_B.rtb_B_j[3]) -
    ObstacleAvoidanceController_U.State[3];

  /* Outputs for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/Ref_pSteps'
   *  Inport: '<Root>/State '
   *  Inport: '<Root>/u'
   *  Memory: '<S8>/LastPcov'
   *  Memory: '<S8>/last_x'
   *  UnitDelay: '<S8>/last_mv'
   */
  ObstacleAvoidanceController_mpc_updateFromNominal
    (ObstacleAvoidanceController_B.b_Mlim, h, ObstacleAvoidanceController_U.u,
     ObstacleAvoidanceController_B.dv8, ObstacleAvoidanceController_B.dv9,
     ObstacleAvoidanceController_B.dv10, ObstacleAvoidanceController_B.b_utarget,
     ObstacleAvoidanceController_B.rtb_C_f,
     ObstacleAvoidanceController_B.y_innov, l, ObstacleAvoidanceController_B.dv7,
     ObstacleAvoidanceController_U.State, ObstacleAvoidanceController_B.b_xoff,
     ObstacleAvoidanceController_B.rtb_A_a, ObstacleAvoidanceController_B.Bv,
     ObstacleAvoidanceController_B.b_uoff, ObstacleAvoidanceController_B.rtb_C_e,
     ObstacleAvoidanceController_B.b_myoff);

  /*  Remove last u offset */
  /*  Get reference and MD signals -- accounting for previewing */
  /*  When doing code generation, use M code directly */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       16; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.C[ObstacleAvoidanceController_B.b_i] = 1.0;
  }

  (void)memset(&ObstacleAvoidanceController_B.rseq[0], 0, 60U * (sizeof(real_T)));
  for (ObstacleAvoidanceController_B.j = 0; ObstacleAvoidanceController_B.j < 4;
       ObstacleAvoidanceController_B.j++) {
    for (ObstacleAvoidanceController_B.b_i = 0;
         ObstacleAvoidanceController_B.b_i < 15;
         ObstacleAvoidanceController_B.b_i++) {
      ObstacleAvoidanceController_B.rseq[ObstacleAvoidanceController_B.j +
        (ObstacleAvoidanceController_B.b_i * 4)] =
        ObstacleAvoidanceController_U.Ref_pSteps[(15 *
        ObstacleAvoidanceController_B.j) + ObstacleAvoidanceController_B.b_i] -
        ObstacleAvoidanceController_B.rtb_C_e[ObstacleAvoidanceController_B.j];
    }
  }

  /*  External MV override.   */
  /*  NOTE: old_u and ext_mv input signals are dimensionless and offset-free. */
  /*  no external mv: old_u is the optimal u[k-1] from last_mv */
  /*  Obtain x[k|k] */
  /*  Remove offset */
  /*  Calculate gain matrices, and perform measurement update. */
  (void)memset(&ObstacleAvoidanceController_B.A_d[0], 0, (sizeof(real_T)) << 4U);
  for (ObstacleAvoidanceController_B.j = 0; ObstacleAvoidanceController_B.j < 4;
       ObstacleAvoidanceController_B.j++) {
    ObstacleAvoidanceController_B.A_d[ObstacleAvoidanceController_B.j +
      (ObstacleAvoidanceController_B.j * 4)] = 1.0;
    for (ObstacleAvoidanceController_B.b_i = 0;
         ObstacleAvoidanceController_B.b_i < 6;
         ObstacleAvoidanceController_B.b_i++) {
      ObstacleAvoidanceController_B.b_j = (ObstacleAvoidanceController_B.b_i * 4)
        + ObstacleAvoidanceController_B.j;
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i + (6 *
        ObstacleAvoidanceController_B.j)] =
        ObstacleAvoidanceController_B.Cm[ObstacleAvoidanceController_B.b_j];
      ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j] =
        0.0;
      for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
           6; ObstacleAvoidanceController_B.e++) {
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j] +=
          ObstacleAvoidanceController_B.Cm[(ObstacleAvoidanceController_B.e * 4)
          + ObstacleAvoidanceController_B.j] *
          ObstacleAvoidanceController_DW.LastPcov_PreviousInput[(6 *
          ObstacleAvoidanceController_B.b_i) + ObstacleAvoidanceController_B.e];
      }
    }
  }

  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       4; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         4; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.carLength = 0.0;
      for (ObstacleAvoidanceController_B.b_j = 0;
           ObstacleAvoidanceController_B.b_j < 6;
           ObstacleAvoidanceController_B.b_j++) {
        ObstacleAvoidanceController_B.carLength +=
          ObstacleAvoidanceController_B.Cm_d[(ObstacleAvoidanceController_B.b_j *
          4) + ObstacleAvoidanceController_B.b_i] *
          ObstacleAvoidanceController_B.L[(6 * ObstacleAvoidanceController_B.e)
          + ObstacleAvoidanceController_B.b_j];
      }

      ObstacleAvoidanceController_B.b_j = (ObstacleAvoidanceController_B.e * 4)
        + ObstacleAvoidanceController_B.b_i;
      ObstacleAvoidanceController_B.Cm_dy[ObstacleAvoidanceController_B.b_j] =
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.b_j] +
        ObstacleAvoidanceController_B.carLength;
    }
  }

  ObstacleAvoidanceController_mrdiv_BGzNp2vj(ObstacleAvoidanceController_B.A_d,
    ObstacleAvoidanceController_B.Cm_dy, ObstacleAvoidanceController_B.Kinv);
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         6; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.A_m[ObstacleAvoidanceController_B.e + (6 *
        ObstacleAvoidanceController_B.b_i)] = 0.0;
    }

    for (ObstacleAvoidanceController_B.b_j = 0;
         ObstacleAvoidanceController_B.b_j < 6;
         ObstacleAvoidanceController_B.b_j++) {
      for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
           6; ObstacleAvoidanceController_B.e++) {
        ObstacleAvoidanceController_B.j = (6 * ObstacleAvoidanceController_B.b_i)
          + ObstacleAvoidanceController_B.e;
        ObstacleAvoidanceController_B.A_m[ObstacleAvoidanceController_B.j] +=
          ObstacleAvoidanceController_B.A[(6 * ObstacleAvoidanceController_B.b_j)
          + ObstacleAvoidanceController_B.e] *
          ObstacleAvoidanceController_DW.LastPcov_PreviousInput[(6 *
          ObstacleAvoidanceController_B.b_i) + ObstacleAvoidanceController_B.b_j];
      }
    }
  }

  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         4; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.carLength = 0.0;
      for (ObstacleAvoidanceController_B.b_j = 0;
           ObstacleAvoidanceController_B.b_j < 6;
           ObstacleAvoidanceController_B.b_j++) {
        ObstacleAvoidanceController_B.carLength +=
          ObstacleAvoidanceController_B.A_m[(6 *
          ObstacleAvoidanceController_B.b_j) + ObstacleAvoidanceController_B.b_i]
          * ObstacleAvoidanceController_B.L[(6 * ObstacleAvoidanceController_B.e)
          + ObstacleAvoidanceController_B.b_j];
      }

      ObstacleAvoidanceController_B.j = (6 * ObstacleAvoidanceController_B.e) +
        ObstacleAvoidanceController_B.b_i;
      ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.j] =
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.j] +
        ObstacleAvoidanceController_B.carLength;
    }
  }

  /*  LTVKF state estimation. */
  /*  Scale measured output and remove offset. */
  /*  Correct x(k|k-1) for possible external mv override. */
  /*  NOTE:  Offset was removed from x[k|k-1] at k=0. */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         4; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.b_j = ObstacleAvoidanceController_B.b_i + (6
        * ObstacleAvoidanceController_B.e);
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j] = 0.0;
      ObstacleAvoidanceController_B.j = ObstacleAvoidanceController_B.e * 4;
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j] *
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_i];
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 1] *
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_i + 6];
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 2] *
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_i +
        12];
      ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 3] *
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_i +
        18];
    }

    ObstacleAvoidanceController_B.xk[ObstacleAvoidanceController_B.b_i] =
      ((ObstacleAvoidanceController_B.Bu[ObstacleAvoidanceController_B.b_i + 6] *
        0.0) +
       (ObstacleAvoidanceController_B.Bu[ObstacleAvoidanceController_B.b_i] *
        0.0)) +
      (ObstacleAvoidanceController_DW.last_x_PreviousInput[ObstacleAvoidanceController_B.b_i]
       - ObstacleAvoidanceController_B.b_xoff[ObstacleAvoidanceController_B.b_i]);
  }

  /*  Measurement upate to x(k|k) */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       4; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.carLength = 0.0;
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         6; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.carLength +=
        ObstacleAvoidanceController_B.Cm[(ObstacleAvoidanceController_B.e * 4) +
        ObstacleAvoidanceController_B.b_i] *
        ObstacleAvoidanceController_B.xk[ObstacleAvoidanceController_B.e];
    }

    ObstacleAvoidanceController_B.y_innov[ObstacleAvoidanceController_B.b_i] =
      (ObstacleAvoidanceController_U.State[ObstacleAvoidanceController_B.b_i] -
       ObstacleAvoidanceController_B.b_myoff[ObstacleAvoidanceController_B.b_i])
      - (ObstacleAvoidanceController_B.carLength +
         ObstacleAvoidanceController_B.Dvm[ObstacleAvoidanceController_B.b_i]);
  }

  /*  Real-time MV target override */
  /*  Note: utargetValue is a vector length p*nu.   */
  /*  no external utarget */
  /*  Real-time custom constraint override (scaled E/F/S) */
  /*  When doing code generation, use M code directly */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         4; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.b_j = ObstacleAvoidanceController_B.b_i + (6
        * ObstacleAvoidanceController_B.e);
      ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_j] = 0.0;
      for (ObstacleAvoidanceController_B.j = 0; ObstacleAvoidanceController_B.j <
           6; ObstacleAvoidanceController_B.j++) {
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_j] +=
          ObstacleAvoidanceController_DW.LastPcov_PreviousInput[(6 *
          ObstacleAvoidanceController_B.j) + ObstacleAvoidanceController_B.b_i] *
          ObstacleAvoidanceController_B.Cm[(ObstacleAvoidanceController_B.j * 4)
          + ObstacleAvoidanceController_B.e];
      }
    }

    ObstacleAvoidanceController_B.carLength = 0.0;
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         4; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.b_j = ObstacleAvoidanceController_B.b_i + (6
        * ObstacleAvoidanceController_B.e);
      ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] = 0.0;
      ObstacleAvoidanceController_B.j = ObstacleAvoidanceController_B.e * 4;
      ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j] *
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_i];
      ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 1] *
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_i + 6];
      ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 2] *
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_i + 12];
      ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] +=
        ObstacleAvoidanceController_B.Kinv[ObstacleAvoidanceController_B.j + 3] *
        ObstacleAvoidanceController_B.Nk[ObstacleAvoidanceController_B.b_i + 18];
      ObstacleAvoidanceController_B.carLength +=
        ObstacleAvoidanceController_B.dv6[ObstacleAvoidanceController_B.b_j] *
        ObstacleAvoidanceController_B.y_innov[ObstacleAvoidanceController_B.e];
    }

    ObstacleAvoidanceController_B.xk_b[ObstacleAvoidanceController_B.b_i] =
      ObstacleAvoidanceController_B.xk[ObstacleAvoidanceController_B.b_i] +
      ObstacleAvoidanceController_B.carLength;
  }

  ObstacleAvoidanceController_B.dv8[0] =
    ObstacleAvoidanceController_Y.ThrottleAndDelta[0] -
    ObstacleAvoidanceController_B.b_uoff[0];
  ObstacleAvoidanceController_B.dv8[1] =
    ObstacleAvoidanceController_Y.ThrottleAndDelta[1] -
    ObstacleAvoidanceController_B.b_uoff[1];
  (void)memset(&ObstacleAvoidanceController_B.dv[0], 0, 1392U * (sizeof(real_T)));

  /* MATLAB Function: '<S2>/MATLAB Function' */
  ObstacleAvoidanceController_B.b_myoff[0] = 0.0;
  ObstacleAvoidanceController_B.b_myoff[1] = 0.0;
  ObstacleAvoidanceController_B.b_myoff[2] = 0.0;
  ObstacleAvoidanceController_B.b_myoff[3] = 0.0;

  /* Memory: '<S8>/Memory' */
  (void)memcpy(&ObstacleAvoidanceController_B.bv[0],
               &ObstacleAvoidanceController_DW.Memory_PreviousInput[0], 87U *
               (sizeof(boolean_T)));

  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  (void)memcpy(&ObstacleAvoidanceController_B.u[0], &u[0], 522U * (sizeof(real_T)));
  (void)memcpy(&ObstacleAvoidanceController_B.v[0], &v[0], 174U * (sizeof(real_T)));
  (void)memcpy(&ObstacleAvoidanceController_B.w[0], &w[0], 121U * (sizeof(real_T)));
  (void)memcpy(&ObstacleAvoidanceController_B.y[0], &y[0], 957U * (sizeof(real_T)));

  /* Update for Memory: '<S8>/Memory' incorporates:
   *  MATLAB Function: '<S36>/FixedHorizonOptimizer'
   *  Math: '<S8>/Math Function'
   *  Math: '<S8>/Math Function1'
   *  Math: '<S8>/Math Function2'
   */
  ObstacleAvoidanceController_mpcblock_optimizer
    (ObstacleAvoidanceController_B.rseq, ObstacleAvoidanceController_B.C,
     ObstacleAvoidanceController_B.xk_b, ObstacleAvoidanceController_B.dv8,
     ObstacleAvoidanceController_B.bv, ObstacleAvoidanceController_B.b_Mlim,
     ObstacleAvoidanceController_B.u, ObstacleAvoidanceController_B.v,
     ObstacleAvoidanceController_B.dv, ObstacleAvoidanceController_B.b_utarget,
     ObstacleAvoidanceController_B.b_uoff, ObstacleAvoidanceController_B.rtb_C_e,
     ObstacleAvoidanceController_B.w, ObstacleAvoidanceController_B.y,
     ObstacleAvoidanceController_ConstB.MathFunction,
     ObstacleAvoidanceController_ConstB.MathFunction1,
     ObstacleAvoidanceController_ConstB.MathFunction2, bb, gb,
     ObstacleAvoidanceController_B.A, ObstacleAvoidanceController_B.Bu,
     ObstacleAvoidanceController_B.Bv, ObstacleAvoidanceController_B.b_C_j,
     ObstacleAvoidanceController_B.Dv_f, h,
     ObstacleAvoidanceController_B.b_myoff, ObstacleAvoidanceController_B.F,
     ObstacleAvoidanceController_B.G,
     ObstacleAvoidanceController_Y.ThrottleAndDelta,
     ObstacleAvoidanceController_B.useq,
     &ObstacleAvoidanceController_B.carLength,
     ObstacleAvoidanceController_DW.Memory_PreviousInput);

  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  /*  LTVKF state and covariance update */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         6; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.L_tmp[ObstacleAvoidanceController_B.e + (6 *
        ObstacleAvoidanceController_B.b_i)] = 0.0;
    }
  }

  for (ObstacleAvoidanceController_B.b_j = 0; ObstacleAvoidanceController_B.b_j <
       6; ObstacleAvoidanceController_B.b_j++) {
    for (ObstacleAvoidanceController_B.b_i = 0;
         ObstacleAvoidanceController_B.b_i < 6;
         ObstacleAvoidanceController_B.b_i++) {
      for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
           6; ObstacleAvoidanceController_B.e++) {
        ObstacleAvoidanceController_B.j = (6 * ObstacleAvoidanceController_B.b_i)
          + ObstacleAvoidanceController_B.e;
        ObstacleAvoidanceController_B.L_tmp[ObstacleAvoidanceController_B.j] +=
          ObstacleAvoidanceController_B.A_m[(6 *
          ObstacleAvoidanceController_B.b_j) + ObstacleAvoidanceController_B.e] *
          ObstacleAvoidanceController_B.A[(6 * ObstacleAvoidanceController_B.b_j)
          + ObstacleAvoidanceController_B.b_i];
      }

      ObstacleAvoidanceController_B.j = ObstacleAvoidanceController_B.b_j + (6 *
        ObstacleAvoidanceController_B.b_i);
      ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.j] =
        0.0;
      ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.j] +=
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j] *
        ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i];
      ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.j] +=
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j + 6]
        * ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i + 6];
      ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.j] +=
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j +
        12] * ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i
        + 12];
      ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.j] +=
        ObstacleAvoidanceController_B.Cm_d[ObstacleAvoidanceController_B.b_j +
        18] * ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i
        + 18];
    }
  }

  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       36; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_B.A_m[ObstacleAvoidanceController_B.b_i] =
      (ObstacleAvoidanceController_B.L_tmp[ObstacleAvoidanceController_B.b_i] -
       ObstacleAvoidanceController_B.L_tmp_n[ObstacleAvoidanceController_B.b_i])
      + ObstacleAvoidanceController_B.M[ObstacleAvoidanceController_B.b_i];
  }

  /*  guarantee symmetric for numerical stability */
  /*  Updated state must include offset */
  /*  return xest in original value */
  ObstacleAvoidanceController_B.carLength =
    ObstacleAvoidanceController_Y.ThrottleAndDelta[0] -
    ObstacleAvoidanceController_B.b_uoff[0];
  ObstacleAvoidanceController_B.b_s =
    ObstacleAvoidanceController_Y.ThrottleAndDelta[1] -
    ObstacleAvoidanceController_B.b_uoff[1];
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    /* Update for Memory: '<S8>/LastPcov' incorporates:
     *  MATLAB Function: '<S36>/FixedHorizonOptimizer'
     */
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         6; ObstacleAvoidanceController_B.e++) {
      /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
      ObstacleAvoidanceController_B.b_j = (6 * ObstacleAvoidanceController_B.b_i)
        + ObstacleAvoidanceController_B.e;
      ObstacleAvoidanceController_DW.LastPcov_PreviousInput[ObstacleAvoidanceController_B.b_j]
        = (ObstacleAvoidanceController_B.A_m[ObstacleAvoidanceController_B.b_j]
           + ObstacleAvoidanceController_B.A_m[(6 *
            ObstacleAvoidanceController_B.e) + ObstacleAvoidanceController_B.b_i])
        * 0.5;
    }

    /* End of Update for Memory: '<S8>/LastPcov' */

    /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
    ObstacleAvoidanceController_B.xk_b[ObstacleAvoidanceController_B.b_i] = 0.0;
  }

  /* MATLAB Function: '<S36>/FixedHorizonOptimizer' */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    for (ObstacleAvoidanceController_B.e = 0; ObstacleAvoidanceController_B.e <
         6; ObstacleAvoidanceController_B.e++) {
      ObstacleAvoidanceController_B.xk_b[ObstacleAvoidanceController_B.e] +=
        ObstacleAvoidanceController_B.A[(6 * ObstacleAvoidanceController_B.b_i)
        + ObstacleAvoidanceController_B.e] *
        ObstacleAvoidanceController_B.xk[ObstacleAvoidanceController_B.b_i];
    }

    ObstacleAvoidanceController_B.Bu_d[ObstacleAvoidanceController_B.b_i] = 0.0;
    ObstacleAvoidanceController_B.Bu_d[ObstacleAvoidanceController_B.b_i] +=
      ObstacleAvoidanceController_B.Bu[ObstacleAvoidanceController_B.b_i] *
      ObstacleAvoidanceController_B.carLength;
    ObstacleAvoidanceController_B.Bu_d[ObstacleAvoidanceController_B.b_i] +=
      ObstacleAvoidanceController_B.Bu[ObstacleAvoidanceController_B.b_i + 6] *
      ObstacleAvoidanceController_B.b_s;
  }

  /* Update for Memory: '<S8>/last_x' incorporates:
   *  MATLAB Function: '<S36>/FixedHorizonOptimizer'
   */
  for (ObstacleAvoidanceController_B.b_i = 0; ObstacleAvoidanceController_B.b_i <
       6; ObstacleAvoidanceController_B.b_i++) {
    ObstacleAvoidanceController_DW.last_x_PreviousInput[ObstacleAvoidanceController_B.b_i]
      = (((((ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i +
             6] * ObstacleAvoidanceController_B.y_innov[1]) +
            (ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i] *
             ObstacleAvoidanceController_B.y_innov[0])) +
           (ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i +
            12] * ObstacleAvoidanceController_B.y_innov[2])) +
          (ObstacleAvoidanceController_B.L[ObstacleAvoidanceController_B.b_i +
           18] * ObstacleAvoidanceController_B.y_innov[3])) +
         ((ObstacleAvoidanceController_B.xk_b[ObstacleAvoidanceController_B.b_i]
           + ObstacleAvoidanceController_B.Bu_d[ObstacleAvoidanceController_B.b_i])
          + ObstacleAvoidanceController_B.Bv[ObstacleAvoidanceController_B.b_i]))
      + ObstacleAvoidanceController_B.b_xoff[ObstacleAvoidanceController_B.b_i];
  }

  /* End of Update for Memory: '<S8>/last_x' */
  /* End of Outputs for SubSystem: '<S1>/Obstacle avoidance controller' */
}

/* Model initialize function */
void ObstacleAvoidanceController_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;

    /* SystemInitialize for Atomic SubSystem: '<S1>/Obstacle avoidance controller' */
    /* InitializeConditions for Memory: '<S8>/LastPcov' */
    (void)memcpy(&ObstacleAvoidanceController_DW.LastPcov_PreviousInput[0],
                 &ObstacleAvoidanceController_ConstP.LastPcov_InitialCondition[0],
                 36U * (sizeof(real_T)));

    /* InitializeConditions for Memory: '<S8>/last_x' */
    for (i = 0; i < 6; i++) {
      ObstacleAvoidanceController_DW.last_x_PreviousInput[i] =
        ObstacleAvoidanceController_ConstP.last_x_InitialCondition[i];
    }

    /* End of InitializeConditions for Memory: '<S8>/last_x' */
    /* End of SystemInitialize for SubSystem: '<S1>/Obstacle avoidance controller' */
  }
}

/* Model terminate function */
void ObstacleAvoidanceController_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

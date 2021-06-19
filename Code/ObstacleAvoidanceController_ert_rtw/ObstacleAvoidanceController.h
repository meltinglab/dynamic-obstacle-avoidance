/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ObstacleAvoidanceController.h
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

#ifndef RTW_HEADER_ObstacleAvoidanceController_h_
#define RTW_HEADER_ObstacleAvoidanceController_h_
#include <math.h>
#include <string.h>
#ifndef ObstacleAvoidanceController_COMMON_INCLUDES_
#define ObstacleAvoidanceController_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                        /* ObstacleAvoidanceController_COMMON_INCLUDES_ */

#include "ObstacleAvoidanceController_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Fp1[2048];
  real_T Fp1_m[2048];
  real_T Su[1800];
  real_T dv[1392];
  real_T Ep1[1024];
  real_T Dv[1024];
  real_T c_Hv[960];
  real_T y[957];
  real_T dv1[640];
  real_T c_SuJm[600];
  real_T c_Kr[600];
  real_T u[522];
  real_T MvCC[512];
  real_T Cm[384];
  real_T b_C[384];
  real_T c_Sx[360];
  real_T MuCC[320];
  real_T b_Jm[320];
  real_T dv2[320];
  real_T Fp1_c[320];
  real_T c_Kut[300];
  real_T a[300];
  real_T dv3[300];
  real_T c_I[256];
  real_T Bu[192];
  real_T MxCC[192];
  real_T v[174];
  real_T c_Kv[160];
  real_T dv4[128];
  real_T w[121];
  real_T c_Linv[121];
  real_T d_Linv[121];
  real_T RLinv[121];
  real_T b_D[121];
  real_T b_H[121];
  real_T U[121];
  real_T TL[121];
  real_T QQ[121];
  real_T RR[121];
  real_T c_A[121];
  real_T c_Su1[120];
  real_T Sum[120];
  int8_T a_k[900];
  real_T b[100];
  real_T b_SuJm[100];
  real_T b_Jm_c[100];
  real_T CovMat[100];
  real_T Bv[96];
  real_T b_Mlim[87];
  real_T b_Mlim_b[87];
  real_T b_Mu1[87];
  real_T b_Mlim_p[87];
  real_T a__1[87];
  real_T cTol[87];
  real_T dv5[87];
  real_T b_B[80];
  real_T b_B_c[80];
  real_T Dv_f[64];
  real_T Dvm[64];
  real_T Mu1CC[64];
  real_T Ep1_g[64];
  real_T Fp1_g[64];
  real_T CA[64];
  real_T rseq[60];
  real_T c_Kx[60];
  real_T d[54];
  real_T M[36];
  real_T A[36];
  real_T A_m[36];
  real_T L_tmp[36];
  real_T L_tmp_n[36];
  real_T A2[36];
  real_T U_p[36];
  real_T V[36];
  real_T A3[36];
  real_T A4[36];
  real_T A4_l[36];
  real_T b_A[36];
  real_T useq[32];                     /* '<S36>/FixedHorizonOptimizer' */
  real_T E[32];
  real_T b_utarget[30];
  real_T L[24];
  real_T b_C_j[24];
  real_T Nk[24];
  real_T Cm_d[24];
  real_T dv6[24];
  real_T CA_g[24];
  real_T CA_l[24];
  real_T Opt[22];
  real_T Rhs[22];
  int16_T iAnew[87];
  int16_T iC[87];
  real_T c_Ku1[20];
  real_T b_Su1[20];
  real_T b_I1[20];
  real_T Kinv[16];
  real_T C[16];                        /* '<S3>/Plant Model Generator' */
  real_T A_d[16];                      /* '<S3>/Plant Model Generator' */
  real_T Cm_dy[16];
  real_T c_A_l[16];
  int8_T c_I_o[121];
  int8_T b_b[121];
  real_T x[15];
  real_T zopt[11];
  real_T f[11];
  real_T r[11];
  real_T z[11];
  real_T b_Ac[11];
  real_T tau[11];
  real_T work[11];
  real_T varargin_1[11];
  real_T work_n[11];
  boolean_T bv[87];
  int8_T b_I1_b[64];
  real_T B[8];                         /* '<S3>/Plant Model Generator' */
  real_T F[8];                         /* '<S2>/MATLAB Function' */
  real_T rtb_B_l[8];
  real_T Sum_h[8];
  real_T xk[6];
  real_T b_xoff[6];
  real_T xk_b[6];
  real_T Bu_d[6];
  real_T y_innov[4];
  real_T b_myoff[4];
  real_T rtb_C_e[4];
  real_T rtb_A_b[4];
  real_T rtb_B_j[4];
  real_T rtb_C_f[4];
  real_T dv7[4];
  real_T rtb_A_a[4];
  real_T c_Wy[4];
  real_T b_I[4];
  real_T b_C_ju[4];
  real_T b_uoff[2];
  real_T G[2];                         /* '<S2>/MATLAB Function' */
  real_T dv8[2];
  real_T dv9[2];
  real_T dv10[2];
  real_T c_Wu[2];
  real_T c_Wdu[2];
  real_T E_j[2];
  real_T F_o[2];
  real_T carLength;
  real_T b_s;
  real_T q2;
  real_T constraintIntercept;
  real_T Curvature;                    /* '<S4>/MATLAB Function' */
  real_T BadH;
  real_T Fp1_tmp;
  real_T K_tmp;
  real_T b_Kx;
  real_T b_Kr;
  real_T b_Kv;
  real_T b_Kut;
  real_T rMin;
  real_T Xnorm0;
  real_T cMin;
  real_T cVal;
  real_T zTa;
  real_T b_Linv;
  real_T b_atmp;
  real_T beta1;
  real_T temp;
  real_T d_n;
  real_T smax;
  real_T normH;
  real_T s;
  real_T c;
  real_T scale;
  int8_T b_I_i[4];
  int32_T j;
  int32_T b_j;
  int32_T b_i;
  int32_T e;
  int32_T M_tmp;
  int32_T kidx;
  int32_T b_j1;
  int32_T j2;
  int32_T i1;
  int32_T i;
  int32_T a_tmp;
  int32_T i_o;
  int32_T f_tmp;
  int32_T b_k;
  int32_T c_k;
  int32_T ct;
  int32_T i_n;
  int32_T i_m;
  int32_T i_c;
  int32_T b_i_m;
  int32_T c_i;
  int32_T e_i;
  int32_T iC_m;
  int32_T j_j;
  int32_T i_h;
  int32_T ii;
  int32_T knt;
  int32_T itau;
  int32_T iaii;
  int32_T lastv;
} B_ObstacleAvoidanceController;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T LastPcov_PreviousInput[36];   /* '<S8>/LastPcov' */
  real_T last_x_PreviousInput[6];      /* '<S8>/last_x' */
  boolean_T Memory_PreviousInput[87];  /* '<S8>/Memory' */
} DW_ObstacleAvoidanceController;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T MathFunction[4];        /* '<S8>/Math Function' */
  const real_T MathFunction1[2];       /* '<S8>/Math Function1' */
  const real_T MathFunction2[2];       /* '<S8>/Math Function2' */
} ConstB_ObstacleAvoidanceController;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: lastPcov
   * Referenced by: '<S8>/LastPcov'
   */
  real_T LastPcov_InitialCondition[36];

  /* Expression: lastx+xoff
   * Referenced by: '<S8>/last_x'
   */
  real_T last_x_InitialCondition[6];
} ConstP_ObstacleAvoidanceController;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Ref_pSteps[60];               /* '<Root>/Ref_pSteps' */
  real_T SafeX;                        /* '<Root>/SafeX' */
  real_T SafeY;                        /* '<Root>/SafeY' */
  real_T EndX;                         /* '<Root>/EndX' */
  real_T EndY;                         /* '<Root>/EndY' */
  real_T EntryPoint[4];                /* '<Root>/EntryPoint' */
  real_T DetPoint[4];                  /* '<Root>/DetPoint' */
  real_T detection;                    /* '<Root>/detection' */
  real_T Zone;                         /* '<Root>/Zone' */
  real_T Lw;                           /* '<Root>/Lw' */
  real_T Reference[4];                 /* '<Root>/Reference' */
  real_T State[4];                     /* '<Root>/State ' */
  real_T u[2];                         /* '<Root>/u' */
  real_T param[2];                     /* '<Root>/param' */
} ExtU_ObstacleAvoidanceController;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T ThrottleAndDelta[2];          /* '<Root>/ThrottleAndDelta' */
} ExtY_ObstacleAvoidanceController;

/* Real-time Model Data Structure */
struct tag_RTM_ObstacleAvoidanceController {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_ObstacleAvoidanceController ObstacleAvoidanceController_B;

/* Block states (default storage) */
extern DW_ObstacleAvoidanceController ObstacleAvoidanceController_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_ObstacleAvoidanceController ObstacleAvoidanceController_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_ObstacleAvoidanceController ObstacleAvoidanceController_Y;
extern const ConstB_ObstacleAvoidanceController
  ObstacleAvoidanceController_ConstB;  /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_ObstacleAvoidanceController
  ObstacleAvoidanceController_ConstP;

/* Model entry point functions */
extern void ObstacleAvoidanceController_initialize(void);
extern void ObstacleAvoidanceController_step(void);
extern void ObstacleAvoidanceController_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ObstacleAvoidanceController *const ObstacleAvoidanceController_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/Data Type Conversion22' : Unused code path elimination
 * Block '<S8>/Data Type Conversion23' : Unused code path elimination
 * Block '<S8>/Floor' : Unused code path elimination
 * Block '<S8>/Floor1' : Unused code path elimination
 * Block '<S9>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S10>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S11>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S12>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S13>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S14>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S15>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S16>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S17>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S18>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S19>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S20>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S21>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S22>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S23>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S24>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S25>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S26>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S27>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S28>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S29>/Vector Dimension Check' : Unused code path elimination
 * Block '<S30>/Vector Dimension Check' : Unused code path elimination
 * Block '<S31>/Vector Dimension Check' : Unused code path elimination
 * Block '<S32>/Vector Dimension Check' : Unused code path elimination
 * Block '<S33>/Vector Dimension Check' : Unused code path elimination
 * Block '<S34>/Vector Dimension Check' : Unused code path elimination
 * Block '<S35>/Vector Dimension Check' : Unused code path elimination
 * Block '<S8>/useq_scale' : Unused code path elimination
 * Block '<S8>/useq_scale1' : Unused code path elimination
 * Block '<S8>/ym_zero' : Unused code path elimination
 * Block '<S6>/m_zero' : Unused code path elimination
 * Block '<S6>/p_zero' : Unused code path elimination
 * Block '<S8>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion11' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion14' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion15' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion16' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion17' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion18' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion19' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion20' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion21' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S8>/E Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/F Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/G Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/Reshape' : Reshape block reduction
 * Block '<S8>/Reshape1' : Reshape block reduction
 * Block '<S8>/Reshape2' : Reshape block reduction
 * Block '<S8>/Reshape3' : Reshape block reduction
 * Block '<S8>/Reshape4' : Reshape block reduction
 * Block '<S8>/Reshape5' : Reshape block reduction
 * Block '<S8>/S Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/ext.mv_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/mo or x Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/u_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/umin_scale4' : Eliminated nontunable gain of 1
 * Block '<S8>/uref_scale' : Eliminated nontunable gain of 1
 * Block '<S8>/ymin_scale1' : Eliminated nontunable gain of 1
 * Block '<S8>/ymin_scale2' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Model_code/ObstacleAvoidanceController')    - opens subsystem Model_code/ObstacleAvoidanceController
 * hilite_system('Model_code/ObstacleAvoidanceController/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model_code'
 * '<S1>'   : 'Model_code/ObstacleAvoidanceController'
 * '<S2>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller'
 * '<S3>'   : 'Model_code/ObstacleAvoidanceController/Plant generator'
 * '<S4>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller'
 * '<S5>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/MATLAB Function'
 * '<S6>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller'
 * '<S7>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/MATLAB Function'
 * '<S8>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC'
 * '<S9>'   : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check'
 * '<S10>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check A'
 * '<S11>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check B'
 * '<S12>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check C'
 * '<S13>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check D'
 * '<S14>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check DX'
 * '<S15>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check U'
 * '<S16>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check X'
 * '<S17>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check Y'
 * '<S18>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check1'
 * '<S19>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Matrix Signal Check2'
 * '<S20>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check'
 * '<S21>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S22>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check2'
 * '<S23>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check3'
 * '<S24>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check4'
 * '<S25>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check5'
 * '<S26>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check6'
 * '<S27>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check7'
 * '<S28>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Preview Signal Check8'
 * '<S29>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S30>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S31>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Scalar Signal Check2'
 * '<S32>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Vector Signal Check'
 * '<S33>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Vector Signal Check1'
 * '<S34>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Vector Signal Check11'
 * '<S35>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S36>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/optimizer'
 * '<S37>'  : 'Model_code/ObstacleAvoidanceController/Obstacle avoidance controller/Adaptive MPC Controller/Adaptive MPC Controller/MPC/optimizer/FixedHorizonOptimizer'
 * '<S38>'  : 'Model_code/ObstacleAvoidanceController/Plant generator/Plant Model Generator'
 */
#endif                           /* RTW_HEADER_ObstacleAvoidanceController_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/* Copyright 2006-2016 The MathWorks, Inc. */

/* 
 * File: xil_interface.h
 *
 * SIL/PIL interface functions
 */

#ifndef __XIL_INTERFACE_H__
#define __XIL_INTERFACE_H__

/* include rtwtypes.h & XILIOData */
#include "xil_interface_common.h"

/* Generated xil_interface.c may use xilCommandDispatchAndResponse for client/server */
#include "xil_interface_lib.h"

/* xil_interface.c|cpp always presents a C 
 * function-call interface for xil_interface_lib.c */
#ifdef __cplusplus
extern "C" {
#endif

/* Get data type information - called from mdlStart */
extern XIL_INTERFACE_ERROR_CODE xilGetDataTypeInfo(void);

/* Process Parameters - called from mdlProcessParameters / mdlStart */
extern XIL_INTERFACE_ERROR_CODE xilProcessParams(uint32_T);

/* Initialize - called from mdlStart */
extern XIL_INTERFACE_ERROR_CODE xilInitialize(uint32_T);

/* System Initialize - called from mdlSystemInitialize (or mdlInitializeConditions) */
extern XIL_INTERFACE_ERROR_CODE xilSystemInitialize(uint32_T);

/* System Reset - called from mdlSystemReset */
extern XIL_INTERFACE_ERROR_CODE xilSystemReset(uint32_T);

/* Initialize input XILIOData pointer */
extern XIL_INTERFACE_ERROR_CODE xilGetHostToTargetData(uint32_T, XIL_COMMAND_TYPE_ENUM, uint32_T, XILIOData **);

/* Output - called from mdlOutputs */
extern XIL_INTERFACE_ERROR_CODE xilOutput(uint32_T, uint32_T);

/* Update - called from mdlOutputs (not mdlUpdate) */
extern XIL_INTERFACE_ERROR_CODE xilUpdate(uint32_T, uint32_T);

/* Initialize output XILIOData pointer */
extern XIL_INTERFACE_ERROR_CODE xilGetTargetToHostData(uint32_T, XIL_COMMAND_TYPE_ENUM, uint32_T, XILIOData **);

/* Terminate - called from mdlTerminate */
extern XIL_INTERFACE_ERROR_CODE xilTerminate(uint32_T);

/* Enable - called from mdlEnable */
extern XIL_INTERFACE_ERROR_CODE xilEnable(uint32_T, uint32_T);

/* Disable - called from mdlDisable */
extern XIL_INTERFACE_ERROR_CODE xilDisable(uint32_T, uint32_T);

/* Pause - called from mdlSimStatusChange */
extern XIL_INTERFACE_ERROR_CODE xilPause(uint32_T);

#ifdef __cplusplus
}
#endif

#endif

/* Copyright 2006-2018 The MathWorks, Inc. */

/* 
 * File: xil_interface_lib.h
 *
 * SIL/PIL support library
 */

#ifndef __XIL_INTERFACE_LIB_H__
#define __XIL_INTERFACE_LIB_H__

#include "xil_error_codes.h"
#include "xil_common.h"
#include "xil_interface_common.h" 

/* always present a C function-call interface for xil_interface_lib.c */
#ifdef __cplusplus
extern "C" {
#endif

/* xil interface functions to be called from main */
extern XIL_INTERFACE_LIB_ERROR_CODE xilInit(const int argc, 
                                            void *argv[]);
extern XIL_INTERFACE_LIB_ERROR_CODE xilRun(void);

/* terminate XIL communications */
extern XIL_INTERFACE_LIB_ERROR_CODE xilTerminateComms(void);

/* Dispatch and receive client/server commands within a step */
extern void xilCommandDispatchAndResponse(XIL_COMMAND_TYPE_ENUM xilCommandType, 
                                          uint32_T xilCommandIdx, uint32_T xilFcnId,
                                          uint32_T serverFcnId, MemUnit_T xilResponseId,
                                          XIL_PROCESS_MSG_CONTEXT_SWITCH callerCtx);

/* return the current context (cc) */
extern XIL_PROCESS_MSG_CONTEXT_SWITCH xilGetCurrentProcessMsgContext(void);
#ifdef __cplusplus
}
#endif

#endif

/* Copyright 2006-2017 The MathWorks, Inc. */

/* 
 * File: xil_interface_lib_private.h
 *
 * SIL/PIL support library
 */

#ifndef __XIL_INTERFACE_LIB_PRIVATE_H__
#define __XIL_INTERFACE_LIB_PRIVATE_H__

#include "xil_interface_common.h"

/* Enumeration to denote UDATA or YDATA processing */
typedef enum {XIL_UDATA_IO = 0, XIL_YDATA_IO} XIL_IO_TYPE;

/* define some error codes */
typedef enum {XIL_PROCESSDATA_SUCCESS=0, 
              XIL_PROCESSDATA_DATA_STREAM_ERROR, 
              XIL_PROCESSDATA_IO_TYPE_ERROR} XIL_PROCESSDATA_ERROR_CODE;

/* define error response error ids */
typedef enum {XIL_RESPONSE_ERROR_SUCCESS=0,
              XIL_RESPONSE_ERROR_PROCESS_UDATA,
              XIL_RESPONSE_ERROR_PROCESS_YDATA, 
              XIL_RESPONSE_ERROR_PROCESS_PARAMS, 
              XIL_RESPONSE_ERROR_INITIALIZE,
              XIL_RESPONSE_ERROR_SYSTEM_INITIALIZE, 
              XIL_RESPONSE_ERROR_OUTPUT, 
              XIL_RESPONSE_ERROR_UPDATE,
              XIL_RESPONSE_ERROR_TERMINATE,
              XIL_RESPONSE_ERROR_ENABLE, 
              XIL_RESPONSE_ERROR_DISABLE, 
              XIL_RESPONSE_ERROR_SYSTEM_RESET} XIL_RESPONSE_ERROR_ID;

/* static functions */
static void getNextXILIOData(void);
  
static XIL_HANDLE_RECV_STATE computeNextState(
        XIL_HANDLE_RECV_STATE currentState,
        XIL_COMMAND_TYPE_ENUM command);


#endif

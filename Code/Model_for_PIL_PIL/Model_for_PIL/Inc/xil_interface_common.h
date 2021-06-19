/* Copyright 2006-2016 The MathWorks, Inc. */

/*
 * File: xil_interface_common.h
 *
 * SIL/PIL common definitions
 */

#ifndef __XIL_INTERFACE_COMMON_H__
#define __XIL_INTERFACE_COMMON_H__

#include "xil_common.h"

/* define some error codes */
typedef enum {XIL_INTERFACE_SUCCESS=0, 
              XIL_INTERFACE_UNKNOWN_TID,
              XIL_INTERFACE_UNKNOWN_FCNID,
              XIL_INTERFACE_COMMS_FAILURE,
              XIL_INTERFACE_MEMORY_ALLOCATION_ERROR,
              XIL_INTERFACE_OFFLOADED_PROCESSING} XIL_INTERFACE_ERROR_CODE;

typedef enum {XIL_INIT_COMMAND = 0, 
              XIL_INITIALIZE_COMMAND,
              XIL_SYSTEM_INITIALIZE_COMMAND,
              XIL_OUTPUT_COMMAND, 
              XIL_TERMINATE_COMMAND, 
              XIL_ENABLE_COMMAND,
              XIL_DISABLE_COMMAND, 
              XIL_CONST_OUTPUT_COMMAND, 
              XIL_PROCESS_PARAMS_COMMAND,
              XIL_CLIENT_SERVER_COMMAND,
              XIL_SHUTDOWN_COMMAND,
              XIL_UPDATE_COMMAND,
              XIL_SYSTEM_RESET_COMMAND,
              XIL_PAUSE_COMMAND} XIL_COMMAND_TYPE_ENUM;

/* define response ids */
typedef enum {XIL_RESPONSE_ERROR=0, 
              XIL_RESPONSE_OUTPUT_DATA,              
              XIL_RESPONSE_PRINTF,
              XIL_RESPONSE_FOPEN,
              XIL_RESPONSE_FPRINTF,
              XIL_RESPONSE_SIGNAL_RAISED,
              XIL_RESPONSE_TYPE_SIZE,
              XIL_RESPONSE_CS_REQUEST_SERVICE              
              } XIL_RESPONSE_ID;

/* define receive states */
typedef enum {XIL_INVALID_STATE=-1,
              XIL_READ_COMMAND_CODE,
              XIL_READ_FCNID,
              XIL_READ_XILTID,
              XIL_PROCESS_HOST_TO_TARGET_DATA,
              XIL_CALL_XILINTERFACE,
              XIL_PROCESS_TARGET_TO_HOST_DATA,
              XIL_COMPLETE} XIL_HANDLE_RECV_STATE;

/* Defines what states we need to save to make xilProcessMsg re-entrant. 
 * This is used by client/server commands which could happen in the middle 
 * of a step */
typedef struct xilProcessMsgContextSwitch {
	XIL_HANDLE_RECV_STATE state;
	XIL_COMMAND_TYPE_ENUM command;
	uint32_T commandIdx;
	uint32_T fcnId;
} XIL_PROCESS_MSG_CONTEXT_SWITCH;

/* XILIOData is defined as a start address
 * and length in MemUnits */
typedef struct xilIOData {
   uint32_T memUnitLength;
   MemUnit_T * address;
} XILIOData;

#endif

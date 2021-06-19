/* Copyright 2006-2017 The MathWorks, Inc. */

/* 
 * File: xil_interface_lib.c
 *
 * SIL/PIL support library
 *
 */

#include "xil_interface_lib.h"
#include "xil_interface_lib_private.h"
#include "xil_data_stream.h"
#include "codeinstr_data_stream.h"
#include "xil_interface.h"
#include "coder_assumptions_app.h"
#include "XILTgtAppSvc_CInterface.h"

#ifdef LDRA_ENABLED
#include "code_coverage_utils.h"
#endif /* LDRA_ENABLED */

#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
    void swapBytes(MemUnit_T * const buffer, uint32_T size);
    static XIL_DATA_STREAM_ERROR_CODE xilReadDataAndSwapBytes(MemUnit_T * dst, uint32_T size);
#endif /* HOST_BIG_ENDIAN_PROTOCOL_TESTING */

/* Internal state variable holding information about the
 * XILIOData currently being processed. 
 *
 * Note: this variable is shared by UDATA processing code
 * and YDATA processing code and used for all IO.
 *
 */
static XILIOData * xilIODataPtr;
static int isShutdownCommand = 0;
static int processMsgSuccess = 1;
static uint32_T serverFcnId;

/* xilProcessMsg current context (cc)*/
static XIL_PROCESS_MSG_CONTEXT_SWITCH cc = {XIL_READ_COMMAND_CODE, XIL_INIT_COMMAND, 0, 0};

/* static functions */
static void restoreProcessMsgContext(XIL_PROCESS_MSG_CONTEXT_SWITCH cachedCtx) {
    cc.state      = cachedCtx.state;
    cc.command    = cachedCtx.command;
    cc.commandIdx = cachedCtx.commandIdx;
    cc.fcnId      = cachedCtx.fcnId;
}

static void getNextXILIOData(void) {
   /* increment xilIOData ptr if we have not reached the end */
   if (xilIODataPtr->memUnitLength!=0) {
      xilIODataPtr++;
   }
}

static XIL_PROCESSDATA_ERROR_CODE processHostToTargetData(uint32_T fcnId,
        XIL_COMMAND_TYPE_ENUM command,
        uint32_T commandIdx)  {
    
    /* this function receives some arbitrary data size that needs to be 
     * into the appropriate memory addresses. Since it is not guaranteed 
     * that we will copy all the required data in one go, we need to keep 
     * track of which address (and size) in xilIODataPtr we last copied 
     * to so we can continue copying the remaining data the next time we 
     * receive them.
     */
    static MemUnit_T * uDataAddress = NULL;
    static uint32_T uDataLength = 0;
    int processingComplete = 0;
        
	/* initialize uDataAddress and uDataLength if necessary*/
    if (uDataAddress == NULL) {
		/* initialise xilIODataPtr before beginning to process data */
		if (xilGetHostToTargetData(fcnId, command, commandIdx, &xilIODataPtr)) {
			/* no udata processing to be done - we're complete */
			processingComplete = 1;			
			return XIL_PROCESSDATA_SUCCESS;
		}

        uDataAddress = xilIODataPtr->address;
        uDataLength = xilIODataPtr->memUnitLength;
    }
    
    while(!(processingComplete)) {
        xilReadData(uDataAddress, uDataLength);
        getNextXILIOData();
            
        if (xilIODataPtr->memUnitLength == 0) {
            /* done processing all xilIOData */                
            processingComplete = 1;
            uDataAddress = NULL;
        } else {
            /* reset our pointer to next xilIOData */
            uDataAddress = xilIODataPtr->address;
            uDataLength = xilIODataPtr->memUnitLength;
        }
    }

    return XIL_PROCESSDATA_SUCCESS;
}

static XIL_PROCESSDATA_ERROR_CODE processTargetToHostData(uint32_T fcnId,
        MemUnit_T responseId,
        XIL_COMMAND_TYPE_ENUM command,
        uint32_T commandIdx)  {
        
    int moreXILData = 1;
    
    /* initialise before beginning to process data */    
    if (xilGetTargetToHostData(fcnId, command, commandIdx, &xilIODataPtr)) {
        /* no ydata processing to be done - we're complete */        
        return XIL_PROCESSDATA_SUCCESS;
    }
    /* send response id */
    if (xilWriteData(&responseId, sizeof(responseId)) != XIL_DATA_STREAM_SUCCESS) {        
        return XIL_PROCESSDATA_DATA_STREAM_ERROR;
    }
    
    /* send server function id if this is a caller function */
    if (responseId == XIL_RESPONSE_CS_REQUEST_SERVICE) {
        if (xilWriteData((MemUnit_T *) &serverFcnId, sizeof(serverFcnId)) != XIL_DATA_STREAM_SUCCESS) {
            return XIL_PROCESSDATA_DATA_STREAM_ERROR;
        }
    }
    
    while(moreXILData) {
        if (xilWriteData(xilIODataPtr->address, xilIODataPtr->memUnitLength) != XIL_DATA_STREAM_SUCCESS) {            
            return XIL_PROCESSDATA_DATA_STREAM_ERROR;
        }
        /* get next xilIOData */
        getNextXILIOData();
        if (xilIODataPtr->memUnitLength == 0) {
            moreXILData = 0;
        }
    }
    return XIL_PROCESSDATA_SUCCESS;
}

static XIL_INTERFACE_LIB_ERROR_CODE finalizeCommandResponse(XIL_RESPONSE_ERROR_ID errorId, MemUnit_T isEndOfXILStep)  {

#ifdef CODE_INSTRUMENTATION_ENABLED
    /* flush the output stream
     * before beginning next command */
    if (codeInstrDataFlush() != XIL_DATA_STREAM_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
#endif

   /* only send the error id if necessary */
   if (errorId != XIL_RESPONSE_ERROR_SUCCESS) {
      /* send response id code */
      MemUnit_T memUnitData = XIL_RESPONSE_ERROR;
      if (xilWriteData(&memUnitData, sizeof(memUnitData)) != XIL_DATA_STREAM_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;      
      }
      /* send error id */
	  memUnitData = (MemUnit_T) errorId;
      if (xilWriteData(&memUnitData, sizeof(memUnitData)) != XIL_DATA_STREAM_SUCCESS) {
         return XIL_INTERFACE_LIB_ERROR;      
      }	  
   }
   /* flush the output stream 
    * before beginning next command */
   if (xilDataFlush(isEndOfXILStep) != XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_LIB_ERROR;      
   }   
   return XIL_INTERFACE_LIB_SUCCESS;
}

/* Given current state and command, compute the next state for handleReceive */
static XIL_HANDLE_RECV_STATE computeNextState(XIL_HANDLE_RECV_STATE state, XIL_COMMAND_TYPE_ENUM command) {
    
    XIL_HANDLE_RECV_STATE nextState;
    
    switch(state) {
        case XIL_READ_COMMAND_CODE:
            switch(command) {
                case XIL_INIT_COMMAND:                    
                case XIL_CONST_OUTPUT_COMMAND:
                case XIL_INITIALIZE_COMMAND:
                case XIL_SYSTEM_INITIALIZE_COMMAND:
                case XIL_TERMINATE_COMMAND:
                case XIL_PROCESS_PARAMS_COMMAND:
                case XIL_ENABLE_COMMAND:
                case XIL_DISABLE_COMMAND:
                case XIL_CLIENT_SERVER_COMMAND:
                case XIL_UPDATE_COMMAND:
                case XIL_OUTPUT_COMMAND:
                case XIL_SYSTEM_RESET_COMMAND:
                case XIL_PAUSE_COMMAND:
                    nextState = XIL_READ_FCNID;
                    break;
                case XIL_SHUTDOWN_COMMAND:
                    nextState = XIL_READ_FCNID;
                    break;
                default:
                    nextState = XIL_INVALID_STATE;
                    break;
            }
            break;
        case XIL_READ_FCNID:
            switch(command) {
                case XIL_INIT_COMMAND:
                case XIL_PAUSE_COMMAND:
                    nextState = XIL_CALL_XILINTERFACE;
                    break;
                case XIL_CONST_OUTPUT_COMMAND:
                    nextState = XIL_PROCESS_TARGET_TO_HOST_DATA;
                    break;
                case XIL_INITIALIZE_COMMAND:
                case XIL_SYSTEM_INITIALIZE_COMMAND:
                case XIL_TERMINATE_COMMAND:
                case XIL_PROCESS_PARAMS_COMMAND:
                case XIL_SYSTEM_RESET_COMMAND:
                    nextState = XIL_PROCESS_HOST_TO_TARGET_DATA;
                    break;
                case XIL_ENABLE_COMMAND:
                case XIL_DISABLE_COMMAND:
                case XIL_CLIENT_SERVER_COMMAND:  
                case XIL_UPDATE_COMMAND:
                case XIL_OUTPUT_COMMAND:
                    nextState = XIL_READ_XILTID;
                    break;
                default:
                    nextState = XIL_INVALID_STATE;
                    break;
            }
            break;            
        case XIL_READ_XILTID:
            switch(command) {
                case XIL_ENABLE_COMMAND:
                case XIL_DISABLE_COMMAND:
                case XIL_CLIENT_SERVER_COMMAND:
                case XIL_OUTPUT_COMMAND:
                case XIL_UPDATE_COMMAND:
                    nextState = XIL_PROCESS_HOST_TO_TARGET_DATA;
                    break;
                default:
                    nextState = XIL_INVALID_STATE;
                    break;
            }
            break;
        case XIL_PROCESS_HOST_TO_TARGET_DATA:
            switch(command) {
                case XIL_INITIALIZE_COMMAND:
                case XIL_SYSTEM_INITIALIZE_COMMAND:                
                case XIL_ENABLE_COMMAND:
                case XIL_DISABLE_COMMAND:
                case XIL_TERMINATE_COMMAND:
                case XIL_PROCESS_PARAMS_COMMAND:
                case XIL_OUTPUT_COMMAND:
                case XIL_UPDATE_COMMAND:
                case XIL_SYSTEM_RESET_COMMAND:
                case XIL_PAUSE_COMMAND:
                    nextState = XIL_CALL_XILINTERFACE;
                    break;
                case XIL_CLIENT_SERVER_COMMAND:
                    nextState = XIL_COMPLETE;
                    break;
                default:
                    nextState = XIL_INVALID_STATE;
                    break;
            }
            break;
        case XIL_CALL_XILINTERFACE:
            switch(command) {
                case XIL_UPDATE_COMMAND:
                case XIL_INIT_COMMAND:
                case XIL_PROCESS_PARAMS_COMMAND:
                    nextState = XIL_COMPLETE;
                    break;
                case XIL_INITIALIZE_COMMAND:
                case XIL_SYSTEM_INITIALIZE_COMMAND:
                case XIL_CONST_OUTPUT_COMMAND:
                case XIL_ENABLE_COMMAND:
                case XIL_DISABLE_COMMAND:                
                case XIL_OUTPUT_COMMAND:
                case XIL_SYSTEM_RESET_COMMAND:
                case XIL_PAUSE_COMMAND:
                case XIL_TERMINATE_COMMAND:   
                    nextState = XIL_PROCESS_TARGET_TO_HOST_DATA;
                    break;
                default:
                    nextState = XIL_INVALID_STATE;
                    break;
            }
            break;
        case XIL_PROCESS_TARGET_TO_HOST_DATA:
            /* done */
            nextState = XIL_COMPLETE;
            break;
        default:
            nextState = XIL_INVALID_STATE;
            break;
    }
    return nextState;
}

#define XIL_COMMAND_TYPE_SIZE sizeof(MemUnit_T)
#define XIL_COMMAND_CODE_IDX 0
#define XIL_COMMAND_FCNID_IDX (XIL_COMMAND_CODE_IDX + XIL_COMMAND_TYPE_SIZE)
#define XIL_COMMAND_FCNID_SIZE sizeof(uint32_T)
#define XIL_COMMAND_XILTID_IDX (XIL_COMMAND_FCNID_IDX + XIL_COMMAND_FCNID_SIZE)
#define XIL_COMMAND_XILTID_SIZE sizeof(uint32_T)
#define XIL_COMMAND_ERROR_STATUS_SIZE sizeof(MemUnit_T)

#define XIL_RUN_EXIT_ERROR processMsgSuccess = 0;      \
                           return
#define XIL_RUN_EXIT return

#define XIL_EXIT_ERROR_IF_INVALID_STATE if (cc.state == XIL_INVALID_STATE) {      \
                                         XIL_RUN_EXIT_ERROR;                   \
                                      }                                                                                           

static void xilReadCommandCode(void) {
    MemUnit_T commandCode;    
    if (cc.state==XIL_READ_COMMAND_CODE) {
        /* read commandCode */

        xilReadData(&(commandCode), XIL_COMMAND_TYPE_SIZE);

        /* cast from the MemUnit commandCode to the enumeration commandCode */
        cc.command = (XIL_COMMAND_TYPE_ENUM) commandCode;
            
        if (cc.command == XIL_SHUTDOWN_COMMAND) {
			/* Terminate this process when XIL simulation is complete */
            isShutdownCommand = 1;             
            if (finalizeCommandResponse(XIL_RESPONSE_ERROR_TERMINATE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                XIL_RUN_EXIT_ERROR;
            }
            else {
                XIL_RUN_EXIT;
            }
        } else {
            /* compute next state */
            cc.state = computeNextState(cc.state, cc.command);
            XIL_EXIT_ERROR_IF_INVALID_STATE;
        }
    }
}
                           
void xilProcessMsg(void) { 
    /* read commandCode */
    xilReadCommandCode();
    
    if (cc.state==XIL_READ_FCNID) {
        /* read fcnId */
#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
        xilReadDataAndSwapBytes(((MemUnit_T*)&(cc.fcnId)), XIL_COMMAND_FCNID_SIZE);
#else
        xilReadData(((MemUnit_T*)&(cc.fcnId)), XIL_COMMAND_FCNID_SIZE);
#endif /*HOST_BIG_ENDIAN_PROTOCOL_TESTING*/
        

            
        /* compute next state */
        cc.state = computeNextState(cc.state, cc.command);
        XIL_EXIT_ERROR_IF_INVALID_STATE;
    }
        
        
    if (cc.state==XIL_READ_XILTID) {
        /* read commandIdx */
        
#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
        xilReadDataAndSwapBytes(((MemUnit_T*)&(cc.commandIdx)), XIL_COMMAND_XILTID_SIZE);
#else
        xilReadData(((MemUnit_T*)&(cc.commandIdx)), XIL_COMMAND_XILTID_SIZE);
#endif /*HOST_BIG_ENDIAN_PROTOCOL_TESTING*/

        /* compute next state */
        cc.state = computeNextState(cc.state, cc.command);
            XIL_EXIT_ERROR_IF_INVALID_STATE;
    }
        
    if (cc.state == XIL_PROCESS_HOST_TO_TARGET_DATA) {
        /* process inputs if required by command */
        XIL_PROCESSDATA_ERROR_CODE processDataError;
        /* process data from host */
        processDataError = processHostToTargetData(cc.fcnId, cc.command, cc.commandIdx);
        if (processDataError == XIL_PROCESSDATA_DATA_STREAM_ERROR) {
            XIL_RUN_EXIT_ERROR;
        } else if (processDataError != XIL_PROCESSDATA_SUCCESS) {
            if (finalizeCommandResponse(XIL_RESPONSE_ERROR_PROCESS_UDATA, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                XIL_RUN_EXIT_ERROR;
            }
            else {
                XIL_RUN_EXIT;
            }
        }
            
        /* compute next state */
        cc.state = computeNextState(cc.state, cc.command);
            XIL_EXIT_ERROR_IF_INVALID_STATE
    }
        
    if (cc.state == XIL_CALL_XILINTERFACE) {
        /* call xilInterface function */
        switch(cc.command) {
#ifndef OUT_OF_PROCESS_EXEC
            case XIL_INIT_COMMAND:
            {
#if CODER_ASSUMPTIONS_ENABLED == 1
                /* run validation of coder assumptions */
                if (coderAssumptionsRun() != XIL_INTERFACE_LIB_SUCCESS) {
                    XIL_RUN_EXIT_ERROR;
                } 
#endif
                if (xilGetDataTypeInfo() != XIL_INTERFACE_SUCCESS) {
                    XIL_RUN_EXIT_ERROR;
                }
                break;
            }
            case XIL_CONST_OUTPUT_COMMAND:
                /* no function */
                break;
            case XIL_PROCESS_PARAMS_COMMAND:
                if (xilProcessParams(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_PROCESS_PARAMS, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_INITIALIZE_COMMAND:
                if (xilInitialize(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_INITIALIZE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_PAUSE_COMMAND:
                if (xilPause(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_INITIALIZE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_SYSTEM_INITIALIZE_COMMAND:
                if (xilSystemInitialize(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_SYSTEM_INITIALIZE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_TERMINATE_COMMAND:
                if (xilTerminate(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_TERMINATE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_ENABLE_COMMAND:
                if (xilEnable(cc.fcnId, cc.commandIdx) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_ENABLE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_DISABLE_COMMAND:
                if (xilDisable(cc.fcnId, cc.commandIdx) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_DISABLE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
            case XIL_UPDATE_COMMAND:
                if (xilUpdate(cc.fcnId, cc.commandIdx) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_UPDATE, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    } else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
#endif
            case XIL_OUTPUT_COMMAND:
                if (xilOutput(cc.fcnId, cc.commandIdx) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_OUTPUT, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }
                break;
#ifndef OUT_OF_PROCESS_EXEC
            case XIL_SYSTEM_RESET_COMMAND:
                if (xilSystemReset(cc.fcnId) != XIL_INTERFACE_SUCCESS) {
                    if (finalizeCommandResponse(XIL_RESPONSE_ERROR_SYSTEM_RESET, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                        XIL_RUN_EXIT_ERROR;
                    }
                    else {
                        XIL_RUN_EXIT;
                    }
                }                     
                break;
#endif
            default:
                XIL_RUN_EXIT_ERROR;
        }
        /* compute next state */
        cc.state = computeNextState(cc.state, cc.command);
        XIL_EXIT_ERROR_IF_INVALID_STATE;
    }
    if (cc.state == XIL_PROCESS_TARGET_TO_HOST_DATA) {
        XIL_PROCESSDATA_ERROR_CODE processDataError;
        /* process data from target */
        processDataError = processTargetToHostData(cc.fcnId, XIL_RESPONSE_OUTPUT_DATA, cc.command, cc.commandIdx);
        if (processDataError == XIL_PROCESSDATA_DATA_STREAM_ERROR) {
            XIL_RUN_EXIT_ERROR;
        } else if (processDataError != XIL_PROCESSDATA_SUCCESS) {
            if (finalizeCommandResponse(XIL_RESPONSE_ERROR_PROCESS_YDATA, 1) != XIL_INTERFACE_LIB_SUCCESS) {
                XIL_RUN_EXIT_ERROR;
            }
            else {
                XIL_RUN_EXIT;
            }
        }
        /* compute next state */
        cc.state = computeNextState(cc.state, cc.command);
        XIL_EXIT_ERROR_IF_INVALID_STATE;
        /*break;*/
    }
        

#ifdef LDRA_ENABLED
    /* upload code coverage execution history from target*/
    if (cc.command == XIL_TERMINATE_COMMAND) {
        callTargetUploadFcns();
    }
#endif /* LDRA_ENABLED */
                
    /* client/server commands could be executed in the middle of a step */
    if ((cc.state == XIL_COMPLETE) && (cc.command != XIL_CLIENT_SERVER_COMMAND)) { 
        /* finalize the response */
        MemUnit_T isEndOfXILStep = 1;
        if (finalizeCommandResponse(XIL_RESPONSE_ERROR_SUCCESS, isEndOfXILStep) != XIL_INTERFACE_LIB_SUCCESS) {
            XIL_RUN_EXIT_ERROR;
        }
        
        /* reset state */
        cc.state = XIL_READ_COMMAND_CODE;
    }

    XIL_RUN_EXIT;
    
}

/* Call xilProcessMsg to process host to target data */
uint8_T commsRun(void)
{            
    const uint8_T success = 1;

    xilProcessMsg();
    return success;
}

XIL_INTERFACE_LIB_ERROR_CODE xilRun(void) {
    XIL_INTERFACE_LIB_ERROR_CODE errorCode = XIL_INTERFACE_LIB_SUCCESS;
    int success;             

    /* read one msg and pass to owning application */
    success = commsRun();
    
    success = success && processMsgSuccess;
    if (success) {        
        if (isShutdownCommand) {
            errorCode = XIL_INTERFACE_LIB_TERMINATE;
        } else {
            errorCode = XIL_INTERFACE_LIB_SUCCESS;
        }
        
    } else {
        errorCode = XIL_INTERFACE_LIB_ERROR;
    }
    return errorCode;
}

/* Dispatch and receive client/server commands within a step */
void xilCommandDispatchAndResponse(XIL_COMMAND_TYPE_ENUM xilCommandType, 
                                   uint32_T xilCommandIdx, uint32_T xilFcnId, 
                                   uint32_T svrFcnId, MemUnit_T xilResponseId,
                                   XIL_PROCESS_MSG_CONTEXT_SWITCH callerCtx) {

    /* define a binary flag, each CS command needs to process a response */
    int needToProcessCSResponse = 1;
    
    /* update server function id */
    serverFcnId = svrFcnId;        

    /* send input data to the host */
    if (processTargetToHostData(xilFcnId, xilResponseId, xilCommandType, 
            xilCommandIdx) == XIL_PROCESSDATA_DATA_STREAM_ERROR) {
        restoreProcessMsgContext(callerCtx);
        XIL_RUN_EXIT_ERROR;
    }
    
    /* finalize the response */
    {
        MemUnit_T isEndOfXILStep = 0;
        if (finalizeCommandResponse(XIL_RESPONSE_ERROR_SUCCESS, isEndOfXILStep) !=
                XIL_INTERFACE_LIB_SUCCESS) {
            restoreProcessMsgContext(callerCtx);
            XIL_RUN_EXIT_ERROR;
        }
    }
    
    /* reset state for new context, recursive calls are safe because all
     * the caller contexts (callerCtx) are cached in the stack */
    cc.state = XIL_READ_COMMAND_CODE;
    
    while(needToProcessCSResponse) {
        /* read next command requested by the host */
        xilReadCommandCode();
        if (cc.command == XIL_CLIENT_SERVER_COMMAND) {
            /* if the host sent a response to the server call, process it
             * and then exit the loop. Otherwise, process the current 
             * command and read the next one */
            needToProcessCSResponse = 0;
        }
        /* process response data sent by host */
        if (xilRun() != XIL_INTERFACE_LIB_SUCCESS) {
            restoreProcessMsgContext(callerCtx);
            XIL_RUN_EXIT_ERROR;
        }
    }
    
    restoreProcessMsgContext(callerCtx);
    
}

XIL_PROCESS_MSG_CONTEXT_SWITCH xilGetCurrentProcessMsgContext(void) {
    /* return the current context (cc) */
    return cc;
}


#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING

void swapBytes(MemUnit_T * const buffer, uint32_T size) {
    MemUnit_T tmp;
    MemUnit_T *headPtr;
    MemUnit_T *tailPtr;
    uint32_T idx;

    for(idx = 0; idx < size/2; idx ++) {
        headPtr = buffer + idx; 
        tailPtr = buffer + size -1 - idx;
        tmp = *headPtr;
        *headPtr = *tailPtr;
        *tailPtr = tmp;
    }
}

static XIL_DATA_STREAM_ERROR_CODE xilReadDataAndSwapBytes(MemUnit_T * dst, uint32_T size) {
    XIL_DATA_STREAM_ERROR_CODE readDataVal = xilReadData(dst, size);

    if (readDataVal == XIL_DATA_STREAM_SUCCESS) {
        swapBytes(dst, size);
    }
    return readDataVal;
}

#endif /*HOST_BIG_ENDIAN_PROTOCOL_TESTING*/

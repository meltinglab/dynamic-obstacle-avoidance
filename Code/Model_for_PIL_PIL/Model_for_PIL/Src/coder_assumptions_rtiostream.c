/* Copyright 2013-2015 The MathWorks, Inc. */

#include "rx_tx_buffer_sizes.h"
#include "xil_common.h"
#include "CoderAssumpTgtAppSvc_CInterface.h"

/* coder assumptions buffer is statically allocated for rtiostream-based implementation */
static IOUnit_T coderAssumpWriteBuffer[CA_TX_BUFFER_MEMUNIT_SIZE];

extern uint8_T coderAssumpTgtAppSvcCreate(void) {
    return CODERASSUMPTGTAPPSVC_SUCCESS;
}

extern void coderAssumpTgtAppSvcDestroy(void) {
}

/* Allocation method simply returns the statically allocated buffer */
extern uint8_T coderAssumpTgtAppSvcAllocBuffer(
        void** ppBuf,
        const uint16_T dataSize) {
    
    /* buffer is already statically allocated */
    *ppBuf = &coderAssumpWriteBuffer[APPLICATION_ID_IDX];
    
    UNUSED_PARAMETER(dataSize);
    
    /* nothing to do as buffer is already statically allocated */
    return CODERASSUMPTGTAPPSVC_SUCCESS;
}

/* return pointer to the coder assumptions buffer data */
extern IOUnit_T * coderAssumpTgtAppSvcGetBufferDataPtr(
        void* const pBuf) {
    
    /* buffer is already statically allocated */
    UNUSED_PARAMETER(pBuf);
       
    return &coderAssumpWriteBuffer[PAYLOAD_IDX];
}

/* send data over rtiostream */
extern uint8_T coderAssumpTgtAppSvcSend(
        void* const pBuf,        
        const uint16_T dataSize) {
    
    return (uint8_T)commsEnqueueBuffer(pBuf, CODERASSUMP_RTIOSTREAM_BASED_SERVICE_ID, dataSize);
}


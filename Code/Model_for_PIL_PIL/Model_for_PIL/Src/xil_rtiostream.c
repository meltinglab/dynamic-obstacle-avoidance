/* Copyright 2013-2015 The MathWorks, Inc. */

#include "rx_tx_buffer_sizes.h"
#include "xil_common.h"
#include "XILTgtAppSvc_CInterface.h"

/* XIL buffer is statically allocated for rtiostream-based implementation */
static IOUnit_T xilWriteBuffer[XIL_TX_BUFFER_MEMUNIT_SIZE];

extern uint8_T xilTgtAppSvcCreate(void) {
    return XILTGTAPPSVC_SUCCESS;
}

extern void xilTgtAppSvcDestroy(void) {
}

/* Allocation method simply returns the statically allocated buffer */
extern uint8_T xilTgtAppSvcAllocBuffer(
        void** ppBuf,
        const uint16_T dataSize) {
    
    /* buffer is already statically allocated */
    *ppBuf = &xilWriteBuffer[APPLICATION_ID_IDX];
    
    UNUSED_PARAMETER(dataSize);
    
    /* nothing to do as buffer is already statically allocated */
    return XILTGTAPPSVC_SUCCESS;
}

/* return pointer to XIL buffer data */
extern IOUnit_T * xilTgtAppSvcGetBufferDataPtr(
        void* const pBuf) {
    
    /* buffer is already statically allocated */
    UNUSED_PARAMETER(pBuf);
       
    return &xilWriteBuffer[PAYLOAD_IDX];
}

/* send data over rtiostream */
extern uint8_T xilTgtAppSvcSend(
        void* const pBuf,        
        const uint16_T dataSize) {
    
    return (uint8_T)commsEnqueueBuffer(pBuf, XIL_RTIOSTREAM_BASED_SERVICE_ID, dataSize);
}


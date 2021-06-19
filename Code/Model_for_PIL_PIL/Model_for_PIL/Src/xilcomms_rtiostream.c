/* Copyright 2013-2017 The MathWorks, Inc. */
#include "xilcomms_rtiostream.h"
#include "comms_interface.h"
#include "rtiostream.h"
#include "rtiostream_utils.h"
#include "rx_tx_buffer_sizes.h"
#include "xil_common.h"
#include "XILTgtAppSvc.h"
#ifdef HOST_WORD_ADDRESSABLE_TESTING
    #include <stdio.h>
    #include <stdlib.h>
    #include "xil_data_stream.h"
#endif
#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
    extern void swapBytes(MemUnit_T * const buffer, uint32_T size);
#endif /* HOST_BIG_ENDIAN_PROTOCOL_TESTING */

/* call xilProcessMsg */
extern void xilProcessMsg(void);

/* store stream handle */
static int streamID;

/* allocate the buffers */
static IOUnit_T xilCommsBuffer[RTIOSTREAM_RX_BUFFER_SIZE];


/* open rtiostream */
int commsInit(const int argc, void * argv[]){
    
    streamID = rtIOStreamOpen(argc, argv);
    if (streamID == RTIOSTREAM_ERROR) {
        return COMMS_ERROR;
    }
    return COMMS_SUCCESS;
}

/* close rtiostream */
int commsTerminate(void) {    
    if (rtIOStreamClose(streamID) == RTIOSTREAM_NO_ERROR) {
        return COMMS_SUCCESS;
    } else {
        return COMMS_ERROR;
    }
}

/* call rtIOStreamBlockingSend to send data*/
int commsEnqueueBuffer(        
        void* const pBuf,
        const uint8_T appId,
        const uint16_T dataSize) {
    
    int rtIOStreamErrorStatus;
    IOUnit_T* appBuffer;
    MemUnit_T appIdMemUnit = (MemUnit_T)appId;
    uint32_T writeDataAvail = (uint32_T)dataSize;   
    uint32_T transferSize = writeDataAvail + BUFFER_HEADER_SIZE;           

    /* write size and application id before sending the buffer */
#ifdef HOST_WORD_ADDRESSABLE_TESTING
    /* writeDataAvail is in terms of IOUnit_T (uint8_T) - convert to MemUnit_T's
     * abort if writeDataAvail does not divide exactly */
    uint32_T writeDataAvailMemUnits = writeDataAvail / MEM_UNIT_BYTES;
    uint32_T memUnitsRemainder = writeDataAvail % MEM_UNIT_BYTES;
    if (memUnitsRemainder != 0) {
        fprintf(stderr,"Target application aborted: the number of available Bytes in the " \
            "TargetToHost TX Buffer (%d B) does not divide exactly by the number of " \
            "Bytes per MemUnit (%d B).\n", writeDataAvail, MEM_UNIT_BYTES);
        /* this condition can happen only when the buffer is full with the first
         * chunk of outgoing data, at this point the host will not be midway through
         * receiving a response. Therefore, it is ok to drop the pending data. */
        resetXILWriteBuffer();
        /* send the abort message */
        abort();
    }
    
#else
    uint32_T writeDataAvailMemUnits = writeDataAvail;
#endif
    
    /* get the pointer for the application buffer of the given app id */
    appBuffer = (IOUnit_T*) pBuf;
	if (appBuffer == NULL) {
		/* early return */
		return COMMS_ERROR;
	}
        
    UNUSED_PARAMETER(pBuf);
    
    memcpy((void *) &appBuffer[APPLICATION_ID_IDX], &appIdMemUnit, sizeof(appIdMemUnit));        

#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
    /* swap the bytes of the playload size that will be sent to the host */
    swapBytes((MemUnit_T*)(&writeDataAvailMemUnits), sizeof(writeDataAvailMemUnits));
#endif /*HOST_BIG_ENDIAN_PROTOCOL_TESTING*/

    memcpy((void *) &appBuffer[PAYLOAD_SIZE_IDX], &writeDataAvailMemUnits, sizeof(writeDataAvailMemUnits));    
    
   /* Blocks until all requested outgoing data is sent */
   rtIOStreamErrorStatus = rtIOStreamBlockingSend(streamID,
                                                 (const void *) appBuffer,
                                                 transferSize);
                                                      
   if (rtIOStreamErrorStatus == RTIOSTREAM_ERROR)
         return COMMS_ERROR;
   
   return COMMS_SUCCESS;
}

int rtiostreamReadMessage(IOUnit_T ** currentBufferPosition, uint16_T *currentBufSize) {
    
    int rtIOStreamErrorStatus;
    uint32_T dataSize = 0;
    MemUnit_T appId;


    rtIOStreamErrorStatus = rtIOStreamBlockingRecv(streamID,
        (void *) &appId,
        sizeof(appId));

    if (rtIOStreamErrorStatus == RTIOSTREAM_ERROR)
	    return COMMS_ERROR;

    
    /* receive size of data contained in the buffer */
    rtIOStreamErrorStatus = rtIOStreamBlockingRecv(streamID,
        (void *) &dataSize,
        sizeof(dataSize));

#ifdef HOST_BIG_ENDIAN_PROTOCOL_TESTING
    /* swap the bytes of the dataSize sent from the host */
    swapBytes((MemUnit_T*)(&dataSize), sizeof(dataSize));
#endif /*HOST_BIG_ENDIAN_PROTOCOL_TESTING*/

    if (rtIOStreamErrorStatus == RTIOSTREAM_ERROR)
		return COMMS_ERROR;

    
#ifdef HOST_WORD_ADDRESSABLE_TESTING
	/* dataSize is in terms of MemUnit_T - convert to IOUnit_T (uint8_T). Note
     * that dataSize will not overflow since the host already divided dataSize 
	 * by memUnit_T before transmission, so this multiplication should be safe
     * and won't overflow.
	 */
    dataSize *= MEM_UNIT_BYTES;
#endif

    /* receive the data */
    rtIOStreamErrorStatus = rtIOStreamBlockingRecv(streamID,
        (void *) &(xilCommsBuffer[0]),
        dataSize);

    *currentBufferPosition = &(xilCommsBuffer[0]);
    *currentBufSize = (uint16_T)dataSize;

    return COMMS_SUCCESS;
}


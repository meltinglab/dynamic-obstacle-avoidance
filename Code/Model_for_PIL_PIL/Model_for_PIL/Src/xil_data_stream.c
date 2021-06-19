/* Copyright 2007-2016 The MathWorks, Inc. */
#include "comms_interface.h"
#ifndef USING_CS_API    
#include "rtiostream.h"
#include "rtiostream_utils.h"
#endif
#include "xil_data_stream.h"
#include "xil_interface_lib.h"
#include "XILTgtAppSvc_CInterface.h"

#ifdef USING_CS_API
    #define XIL_TX_BUFFER_MEMUNIT_SIZE xilTgtAppSvcGetMaxPayloadCapacity()
    #define BUFFER_HEADER_SIZE 0
#else
    #include "rx_tx_buffer_sizes.h"
#endif

#define COMMAND_COMPLETE_SIZE (sizeof(MemUnit_T))
#define COMMAND_COMPLETE_IDX 0
#define WRITE_DATA_BUFFER_IDX (COMMAND_COMPLETE_IDX + COMMAND_COMPLETE_SIZE)
#define USED_WRITE_BUFFER_SIZE (COMMAND_COMPLETE_SIZE + xilWriteDataAvail)
#define WRITE_BUFFER_SIZE (XIL_TX_BUFFER_MEMUNIT_SIZE - COMMAND_COMPLETE_SIZE - BUFFER_HEADER_SIZE)


static void* pBuffer;
static IOUnit_T* xilWriteBuffer;
static IOUnit_T* xilWriteDataPtr;
static uint16_T xilWriteDataAvail;
static MemUnit_T* commandResponseType;

/* reset the write buffer */
XIL_INTERFACE_LIB_ERROR_CODE resetXILWriteBuffer(void) {
    
    /* Ask the CS to allocate a buffer that the XIL app service will use for
     * transmission
     */
    if (!xilTgtAppSvcAllocBuffer(&pBuffer, XIL_TX_BUFFER_MEMUNIT_SIZE)) {
        return XIL_INTERFACE_LIB_ERROR;
    }
    xilWriteBuffer = xilTgtAppSvcGetBufferDataPtr(pBuffer);
    
    /* set commandResponseType and xilWriteDataPtr pointer */
    commandResponseType = (MemUnit_T *) &xilWriteBuffer[COMMAND_COMPLETE_IDX];
    xilWriteDataPtr = &xilWriteBuffer[WRITE_DATA_BUFFER_IDX];
    
    /* ready for next command */
    xilWriteDataAvail = 0;
    *commandResponseType = XIL_COMMAND_NOT_COMPLETE;
    
    return XIL_INTERFACE_LIB_SUCCESS;
}

XIL_INTERFACE_LIB_ERROR_CODE silpilInit(void) {
    
    /* Create XIL service */
    if (xilTgtAppSvcCreate() != XILTGTAPPSVC_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
    
    /* Reset write buffer */
    return resetXILWriteBuffer();
}

/* send pending writes */
static XIL_DATA_STREAM_ERROR_CODE sendWriteBuffer(void) {
       
    if (xilTgtAppSvcSend(pBuffer, USED_WRITE_BUFFER_SIZE) == XILTGTAPPSVC_ERROR) {
        return XIL_DATA_FLUSH_ERROR;
    }
    
   /* reset */
   if (resetXILWriteBuffer()!= XIL_INTERFACE_LIB_SUCCESS) {
	   return XIL_DATA_FLUSH_ERROR;
   }
   
   return XIL_DATA_STREAM_SUCCESS;
}

XIL_DATA_STREAM_ERROR_CODE xilWriteData(const MemUnit_T * src, uint32_T size) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
   const IOUnit_T * srcPtr = (const IOUnit_T *) src;   
   size_t transferAmount;
   uint16_T bufferAvail;
  
   /* block until all data is processed */
   while (size > 0) {      
      /* send if we have a full message worth of data */   
      if (xilWriteDataAvail == WRITE_BUFFER_SIZE) {
         errorCode = sendWriteBuffer();
         if (errorCode != XIL_DATA_STREAM_SUCCESS) {
            return errorCode;
         }
      }
      bufferAvail = WRITE_BUFFER_SIZE - xilWriteDataAvail;
      transferAmount = (uint16_T) MIN(bufferAvail, size);
      /* copy data into write buffer */
      memcpy((void *) xilWriteDataPtr, srcPtr, transferAmount);
      size -= (uint32_T) transferAmount;
      xilWriteDataAvail += (uint16_T) transferAmount;
      srcPtr += transferAmount;
      xilWriteDataPtr += transferAmount;
   }
   return errorCode;
}

XIL_DATA_STREAM_ERROR_CODE xilReadData(MemUnit_T * dst, uint32_T size) {

    XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
     
    static IOUnit_T* currentBufferPosition = NULL;
    static uint16_T currentBufSize = 0;
    uint16_T readAmount;
    int32_T index = 0;
    int rtIOStreamErrorStatus;
    IOUnit_T * dstPtr = (IOUnit_T *) dst;

    while (size > 0)
    {
        if (currentBufSize > 0) {

            readAmount = (uint16_T) MIN(currentBufSize, size);
            memcpy(dstPtr+index, currentBufferPosition, (size_t)readAmount);

            currentBufSize -= readAmount;
            currentBufferPosition +=readAmount;
            size -= (uint32_T)readAmount;

            if (size == 0) {
                /* If we've satisfied the data request we're done, return */
                return errorCode;
            }

            /*Buffer empty and more data needed get new data*/
            index += (int32_T)readAmount;
        }

        /* Get NEW DATA */
#ifdef USING_CS_API
        {
            uint16_T tmpSize = 0;
            static uint8_T * tmpData;
            static boolean_T firstTime = true;

            /*If we've previously read a message free it before getting the next*/
            if (!firstTime)
            {
                xilTgtAppSvcFreeLastReceivedData();
            }
            
            /*Block until a message has been received*/
            while (tmpSize == 0)
            {
                tmpData = xilTgtAppSvcGetReceivedData(&tmpSize);
            }

            /*Update first time flag*/
            firstTime = false;

            /*Setup buffer position and size from message data*/
            currentBufSize = tmpSize;
            currentBufferPosition = (IOUnit_T *)tmpData;
        }
#else
        rtIOStreamErrorStatus = rtiostreamReadMessage(&currentBufferPosition, &currentBufSize);

        if (rtIOStreamErrorStatus == RTIOSTREAM_ERROR)
	    	return XIL_READ_DATA_ERROR;

    
#endif
    }

    return errorCode;
}



XIL_DATA_STREAM_ERROR_CODE xilDataFlush(MemUnit_T isEndOfXILStep) {
    
    /* final part of command */
    if (isEndOfXILStep) {
        *commandResponseType = XIL_STEP_COMPLETE;
    } else {
        *commandResponseType = XIL_COMMAND_COMPLETE;
    }

    /* send the write buffer */
    if (sendWriteBuffer() == XIL_DATA_FLUSH_ERROR){
        return XIL_DATA_FLUSH_ERROR;
    }
    
    return XIL_DATA_STREAM_SUCCESS;

}

void silpilTerminate(void) {
    xilTgtAppSvcDestroy();
}



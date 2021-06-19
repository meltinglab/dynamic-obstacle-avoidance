/* Copyright 2015-2017 The MathWorks, Inc. */

#include "coder_assumptions_data_stream.h"
#include "xil_interface_lib.h"
#include "CoderAssumpTgtAppSvc_CInterface.h"

#ifdef USING_CS_API    
   #define CA_TX_BUFFER_MEMUNIT_SIZE coderAssumpTgtAppSvcGetMaxPayloadCapacity()
   #define BUFFER_HEADER_SIZE 0    
#else
   #include "rx_tx_buffer_sizes.h"    
#endif

static void* pBuffer;
static IOUnit_T* coderAssumptionsWriteDataPtr;
static uint16_T coderAssumptionsWriteDataAvail;

XIL_DATA_STREAM_ERROR_CODE coderAssumptionsWriteData(const void * src, const size_t size) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;

   const size_t WRITE_BUFFER_SIZE = CA_TX_BUFFER_MEMUNIT_SIZE - BUFFER_HEADER_SIZE;
   size_t sizeToTransfer = size;

   /* check to see if buffer will overflow */
   if ((coderAssumptionsWriteDataAvail + sizeToTransfer) > WRITE_BUFFER_SIZE) {
      errorCode = XIL_WRITE_DATA_ERROR;
      return errorCode;
   }

   /* copy data into write buffer */
   memcpy((void *) coderAssumptionsWriteDataPtr, src, sizeToTransfer);
   coderAssumptionsWriteDataAvail += (uint16_T) sizeToTransfer;
   coderAssumptionsWriteDataPtr += sizeToTransfer;

   return errorCode;
}


/* reset the write buffer */
XIL_INTERFACE_LIB_ERROR_CODE resetCoderAssumptionsWriteBuffer(void) {
    
    /* Ask the CS to allocate a buffer that the app will 
     * use for transmission
     */
    if (!coderAssumpTgtAppSvcAllocBuffer(&pBuffer, CA_TX_BUFFER_MEMUNIT_SIZE)) {
        return XIL_INTERFACE_LIB_ERROR;
    }
    
    /* set coderAssumptionsWriteDataPtr pointer */
    coderAssumptionsWriteDataPtr = coderAssumpTgtAppSvcGetBufferDataPtr(pBuffer); 
    
    /* ready for next command */
    coderAssumptionsWriteDataAvail = 0;
    
    return XIL_INTERFACE_LIB_SUCCESS;
}

/* send pending writes */
XIL_DATA_STREAM_ERROR_CODE coderAssumptionsSendWriteBuffer(void) {
   /* send */
   if (coderAssumpTgtAppSvcSend(pBuffer, coderAssumptionsWriteDataAvail) == CODERASSUMPTGTAPPSVC_ERROR) {             
      return XIL_WRITE_DATA_ERROR;
   }   
   
   /* reset */
   if (resetCoderAssumptionsWriteBuffer()!= XIL_INTERFACE_LIB_SUCCESS) {
	   return XIL_WRITE_DATA_ERROR;
   }
   
   return XIL_DATA_STREAM_SUCCESS;
}

XIL_INTERFACE_LIB_ERROR_CODE coderAssumptionsInit(void) {    
    /* Create coder assumptions app service */
    if (coderAssumpTgtAppSvcCreate() != CODERASSUMPTGTAPPSVC_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }

   /* Reset write buffer */
   return resetCoderAssumptionsWriteBuffer();
}

void coderAssumptionsTerminate(void) {      
   coderAssumpTgtAppSvcDestroy();
}

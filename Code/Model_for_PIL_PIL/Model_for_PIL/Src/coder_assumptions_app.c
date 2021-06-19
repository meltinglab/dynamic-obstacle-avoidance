/* Copyright 2015-2017 The MathWorks, Inc. */

#include "coder_assumptions_app.h"
#include "coder_assumptions_data_stream.h"
#include "xil_interface_lib.h"

/*
 * Include coder_assumptions.h for Hardware Implementation setting
 * preprocessor validation checks.
 * These checks verify fundamental data types that the comms 
 * stack relies on, e.g. uint8_T, uint16_T, uint32_T.
 *
 * Also access the global results variables and the entry point
 * function for running coder assumptions tests.
 */
#include "coder_assumptions.h" 

/* combine arguments (after expanding arguments) */
#define CA_EXP_CONCAT(a,b) CA_CONCAT(a,b)
#define CA_CONCAT(a,b) a ## b

/* Compile time static assert for checking fundamental assumptions such 
 * as sizeof values for specific data types. */
#define CA_STATIC_ASSERT(expr, msg) typedef char CA_EXP_CONCAT(assert_failed__, msg) [(expr) ? (+1) : (-1)]

#include "coder_assumptions_hwimpl.h"

#ifdef HOST_WORD_ADDRESSABLE_TESTING
   /* MemUnit_T can be any of uint8_T, uint16_T, uint32_T
    * Just check it is consistent with MEM_UNIT_BYTES */
   CA_STATIC_ASSERT(sizeof(MemUnit_T) == MEM_UNIT_BYTES, INVALID_MEMUNIT_T);
#else
   /* Verify MemUnit_T: sizeof must be 1 */
   CA_STATIC_ASSERT(sizeof(MemUnit_T) == 1, MEMUNIT_T_NOT_SIZEOF_1);
   /* Verify MEM_UNIT_BYTES: must match the size of the largest integer that has sizeof == 1 
    * Only word addressable targets up to 32-bits are supported. */
   CA_STATIC_ASSERT((sizeof(uint32_T) == 1) ? MEM_UNIT_BYTES == 4 : 
                 (sizeof(uint16_T) == 1) ? MEM_UNIT_BYTES == 2 :
                 (sizeof(uint8_T) == 1) ? MEM_UNIT_BYTES == 1 : 0, INVALID_MEM_UNIT_BYTES);
#endif
                 
#include "coder_assumptions_shared_enums.h"

static MemUnit_T pwsEnabled;


static XIL_DATA_STREAM_ERROR_CODE sendResult(const CA_TestResult result, 
                                             const MemUnit_T resultType, 
                                             const MemUnit_T actual, 
                                             const MemUnit_T assumed) {
   XIL_DATA_STREAM_ERROR_CODE errorCode;
   MemUnit_T tmp;
   /* send result type */
   errorCode = coderAssumptionsWriteData(&resultType, sizeof(MemUnit_T));   
   if (errorCode) return errorCode;
   
   /* send result status */
   tmp = (MemUnit_T) result.status;
   errorCode = coderAssumptionsWriteData(&tmp, sizeof(MemUnit_T));   
   if (errorCode) return errorCode;

   /* send result msg id */
   tmp = (MemUnit_T) result.msg;
   errorCode = coderAssumptionsWriteData(&tmp, sizeof(MemUnit_T));   
   if (errorCode) return errorCode;
   
   /* send actual */
   errorCode = coderAssumptionsWriteData(&actual, sizeof(MemUnit_T));   
   if (errorCode) return errorCode;
   
   /* send assumed */
   errorCode = coderAssumptionsWriteData(&assumed, sizeof(MemUnit_T));
   if (errorCode) return errorCode;
   
   /* final return */
   return errorCode;
}

static XIL_DATA_STREAM_ERROR_CODE transmitMemUnitBytes(void) {
   XIL_DATA_STREAM_ERROR_CODE errorCode; 
   const MemUnit_T memUnitBytes = MEM_UNIT_BYTES;

   /* send memUnitBytes */
   errorCode = coderAssumptionsWriteData(&memUnitBytes, sizeof(MemUnit_T));
   if (errorCode) return errorCode;
    
   errorCode = coderAssumptionsSendWriteBuffer();  
   if (errorCode) return errorCode;
   
   return errorCode;
}

/* portable word sizes specified checks */
static XIL_DATA_STREAM_ERROR_CODE sendPWS(void) {
    XIL_DATA_STREAM_ERROR_CODE errorCode; 
    MemUnit_T commandId;  
   
    /* send CA_PWS */
    commandId = CA_PWS;
    errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
    if (errorCode) return errorCode;

    /* PWS enabled in build */
    commandId = CA_PWS_ENABLED;
    errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
    if (errorCode) return errorCode;

    pwsEnabled = (MemUnit_T) CA_Actual_HWImpl.portableWordSizes;
    errorCode = coderAssumptionsWriteData(&pwsEnabled, sizeof(MemUnit_T));
    if (errorCode) return errorCode;

    /* extended PWS checks */
    if (pwsEnabled) {
       /* config setting mismatch */
       errorCode = sendResult(CA_PortableWordSizes_Results.configSetting, 
                                    (MemUnit_T) CA_PWS_CONFIG_SETTING,  
                                    (MemUnit_T) CA_Actual_HWImpl.portableWordSizes, 
                                    (MemUnit_T) CA_Expected_HWImpl.portableWordSizes);
       if (errorCode) return errorCode; 
    }


    errorCode = coderAssumptionsSendWriteBuffer();  
    if (errorCode) return errorCode;

    return errorCode;
}

/* hardware implementation checks message 1 */
static XIL_DATA_STREAM_ERROR_CODE sendHWImpl1(void) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;    
   MemUnit_T commandId;

   /* send CA_HW_IMPL_SIZES_1 */    
   commandId = CA_HW_IMPL_SIZES_1;
   errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
   if (errorCode) return errorCode;

   /* bit per char */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerChar, 
         (MemUnit_T) CA_HW_IMPL_BIT_CHAR,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerChar, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerChar);
   if (errorCode) return errorCode;

   /* bit per short */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerShort, 
         (MemUnit_T) CA_HW_IMPL_BIT_SHORT,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerShort, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerShort);
   if (errorCode) return errorCode;

   /* bit per int */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerInt, 
         (MemUnit_T) CA_HW_IMPL_BIT_INT,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerInt, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerInt);
   if (errorCode) return errorCode;

   /* bit per long */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerLong, 
         (MemUnit_T) CA_HW_IMPL_BIT_LONG,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerLong, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerLong);
   if (errorCode) return errorCode;

   /* transmit message */
   errorCode = coderAssumptionsSendWriteBuffer();
   if (errorCode) return errorCode;

   return errorCode;
}

/* hardware implementation checks message 2 */
static XIL_DATA_STREAM_ERROR_CODE sendHWImpl2(void) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
   MemUnit_T commandId;
   
   /* send CA_HW_IMPL_SIZES_2 */    
   commandId = CA_HW_IMPL_SIZES_2;
   errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
   if (errorCode) return errorCode;

   /* support long long */
   errorCode = sendResult(CA_HWImpl_Results.supportLongLong, 
         (MemUnit_T) CA_HW_IMPL_SUPPORT_LONGLONG,  
         (MemUnit_T) CA_Actual_HWImpl.supportLongLong, 
         (MemUnit_T) CA_Expected_HWImpl.supportLongLong);
   if (errorCode) return errorCode;

   /* bit per long long */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerLongLong, 
         (MemUnit_T) CA_HW_IMPL_BIT_LONGLONG,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerLongLong, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerLongLong);
   if (errorCode) return errorCode;

   /* bit per float */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerFloat, 
         (MemUnit_T) CA_HW_IMPL_BIT_FLOAT,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerFloat, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerFloat);
   if (errorCode) return errorCode;

   /* bit per double */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerDouble, 
         (MemUnit_T) CA_HW_IMPL_BIT_DOUBLE,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerDouble, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerDouble);
   if (errorCode) return errorCode;

   /* transmit message */
   errorCode = coderAssumptionsSendWriteBuffer();
   if (errorCode) return errorCode;

   return errorCode;
}

/* hardware implementation checks message 3 */
static XIL_DATA_STREAM_ERROR_CODE sendHWImpl3(void) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
   MemUnit_T commandId;

   /* send CA_HW_IMPL_SIZES_3 */    
   commandId = CA_HW_IMPL_SIZES_3;
   errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
   if (errorCode) return errorCode;

   /* bit per pointer */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerPointer, 
         (MemUnit_T) CA_HW_IMPL_BIT_POINTER,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerPointer, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerPointer);
   if (errorCode) return errorCode;

   /* bit per size_t */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerSizeT, 
         (MemUnit_T) CA_HW_IMPL_BIT_SIZE_T,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerSizeT, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerSizeT);
   if (errorCode) return errorCode;

   /* bit per ptrdiff_t */
   errorCode = sendResult(CA_HWImpl_Results.bitsPerPtrDiffT, 
         (MemUnit_T) CA_HW_IMPL_BIT_PTRDIFF_T,  
         (MemUnit_T) CA_Actual_HWImpl.bitsPerPtrDiffT, 
         (MemUnit_T) CA_Expected_HWImpl.bitsPerPtrDiffT);
   if (errorCode) return errorCode;

   /* transmit message */
   errorCode = coderAssumptionsSendWriteBuffer();
   if (errorCode) return errorCode;

   return errorCode;
}


/* hardware implementation checks message 4 */
static XIL_DATA_STREAM_ERROR_CODE sendHWImpl4(void) {
   XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
   MemUnit_T commandId;

   /* send CA_HW_IMPL_SIZES_4 */
   commandId = CA_HW_IMPL_SIZES_4;
   errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
   if (errorCode) return errorCode;

   /* byte order */
   errorCode = sendResult(CA_HWImpl_Results.byteOrder, 
         (MemUnit_T) CA_HW_IMPL_BYTE_ORDER,  
         (MemUnit_T) CA_Actual_HWImpl.byteOrder, 
         (MemUnit_T) CA_Expected_HWImpl.byteOrder);
   if (errorCode) return errorCode;

   /* integer division rounding */
   errorCode = sendResult(CA_HWImpl_Results.intDivRoundTo, 
         (MemUnit_T) CA_HW_IMPL_INT_DIV_ROUND,  
         (MemUnit_T) CA_Actual_HWImpl.intDivRoundTo, 
         (MemUnit_T) CA_Expected_HWImpl.intDivRoundTo);
   if (errorCode) return errorCode;

   /* shift right on a signed integer */
   errorCode = sendResult(CA_HWImpl_Results.shiftRightBehavior, 
         (MemUnit_T) CA_HW_IMPL_SHIFT_RIGHT,  
         (MemUnit_T) CA_Actual_HWImpl.shiftRightBehavior, 
         (MemUnit_T) CA_Expected_HWImpl.shiftRightBehavior);
   if (errorCode) return errorCode;

   /* transmit message */
   errorCode = coderAssumptionsSendWriteBuffer();
   if (errorCode) return errorCode;

   return errorCode;
}

/* hardware implementation, checks unrelated to sizes */
static XIL_DATA_STREAM_ERROR_CODE sendHardwareChecks(void){
    XIL_DATA_STREAM_ERROR_CODE errorCode = XIL_DATA_STREAM_SUCCESS;
    MemUnit_T commandId;

    commandId = CA_CHECKS_1;
    errorCode = coderAssumptionsWriteData(&commandId, sizeof(MemUnit_T));
    if (errorCode) return errorCode;

   /* memory at startup */
   errorCode = sendResult(CA_HWImpl_Results.memoryAtStartup,
         (MemUnit_T) CA_HW_IMPL_MEMORY_STARTUP,
         (MemUnit_T) CA_Actual_HWImpl.memoryAtStartup,
         (MemUnit_T) CA_Expected_HWImpl.memoryAtStartup);
   if(errorCode) return errorCode;
   
   /* denormal flush to zero */
   errorCode = sendResult(CA_HWImpl_Results.denormalFlushToZero,
         (MemUnit_T) CA_HW_IMPL_DENORMAL_FTZ,
         (MemUnit_T) CA_Actual_HWImpl.denormalFlushToZero,
         (MemUnit_T) CA_Expected_HWImpl.denormalFlushToZero);
   if(errorCode) return errorCode;
   
   /* denormal as zero */
   errorCode = sendResult(CA_HWImpl_Results.denormalAsZero,
         (MemUnit_T) CA_HW_IMPL_DENORMAL_DAZ,
         (MemUnit_T) CA_Actual_HWImpl.denormalAsZero,
         (MemUnit_T) CA_Expected_HWImpl.denormalAsZero);
   if(errorCode) return errorCode;
   /* transmit message */
   errorCode = coderAssumptionsSendWriteBuffer();
   if (errorCode) return errorCode;

   return errorCode;
}

static XIL_DATA_STREAM_ERROR_CODE runChecks(void) {
    XIL_DATA_STREAM_ERROR_CODE errorCode;
    MemUnit_T endTransmission = CA_END_TRANSMIT;

     /* first, run the coder assumptions checks */
    CA_Run_Tests();

    /* now send the results to the host */
    errorCode = transmitMemUnitBytes();
    if (errorCode) return errorCode;

    errorCode = sendPWS();
    if (errorCode) return errorCode;

    errorCode = sendHWImpl1();
    if (errorCode) return errorCode;
    errorCode = sendHWImpl2();
    if (errorCode) return errorCode;
    errorCode = sendHWImpl3();
    if (errorCode) return errorCode;
    errorCode = sendHWImpl4();
    if (errorCode) return errorCode;

    /* send results of miscellaneous checks */
    errorCode = sendHardwareChecks();
    if (errorCode) return errorCode;

    /* let host know all tests have completed */
    errorCode = coderAssumptionsWriteData(&endTransmission, sizeof(MemUnit_T));
    if (errorCode) return errorCode;
    errorCode = coderAssumptionsSendWriteBuffer();
    
    /* final return */
    return errorCode;
}


/* 
 * XIL interface entry points 
 *
 */
XIL_INTERFACE_LIB_ERROR_CODE coderAssumptionsRun(void) {
   if (runChecks() != XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_LIB_ERROR;
   }
   else {
      return XIL_INTERFACE_LIB_SUCCESS;
   }
}

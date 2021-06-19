/* Copyright 2015-2018 The MathWorks, Inc. */

#ifdef XIL_SIGNAL_HANDLER
#include <signal.h>
#include <stdio.h>
#if defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
        #include <execinfo.h>
        #define MAX_STACKTRACE 12
    #endif
#endif

#ifdef SIL_DISABLE_SUBNORMAL_SUPPORT
    #if SIL_DISABLE_SUBNORMAL_SUPPORT >= 1 
#include <immintrin.h>
    #endif
#endif

#include "xil_error_codes.h"
#include "xil_interface_lib.h"
#include "xil_data_stream.h"
#include "comms_interface.h"

#ifdef CODE_INSTRUMENTATION_ENABLED
#include "codeinstr_data_stream.h"
#endif

#ifndef CODER_ASSUMPTIONS_ENABLED
   #error "CODER_ASSUMPTIONS_ENABLED should always be defined!"
#endif

#if CODER_ASSUMPTIONS_ENABLED == 1
#include "coder_assumptions_data_stream.h"
#endif

#ifdef XIL_SIGNAL_HANDLER
/* define signal handler codes */
typedef enum {XIL_SIGNAL_SIGFPE=0, 
              XIL_SIGNAL_SIGILL, 
              XIL_SIGNAL_ABRT,
              XIL_SIGNAL_SEGV,
              XIL_SIGNAL_UNKNOWN} XIL_SIGNAL_RAISED;

static void XILSigHandler(int32_T sigNo)
{
  MemUnit_T memUnitData = XIL_RESPONSE_SIGNAL_RAISED;

  fflush(stderr);
  
  xilWriteData(&memUnitData, sizeof(memUnitData));
  switch (sigNo)
  {
    case SIGFPE:
    {
        /* Erroneous arithmetic operation, such as division by zero */
        memUnitData = XIL_SIGNAL_SIGFPE;
        break;
    }
    case SIGILL:
    {
        /* Illegal, malformed, unknown or privileged instruction */
        memUnitData = XIL_SIGNAL_SIGILL;
        break;
    }
    case SIGABRT:
    {
        /* Signal abort */
        memUnitData = XIL_SIGNAL_ABRT;
        break;
    }
    case SIGSEGV:
    {
        /* Segmentation violation */
        #if defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
            void *array[MAX_STACKTRACE];
            int bt_size = 0;
        #endif
            
        memUnitData = XIL_SIGNAL_SEGV;
            
        #if defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
            bt_size = backtrace(array, MAX_STACKTRACE);
            backtrace_symbols_fd(array, bt_size, 2);
        #endif
        break;
    }
    default:
    {
        memUnitData = XIL_SIGNAL_UNKNOWN;
        break;
    }
  }
  xilWriteData(&memUnitData, sizeof(memUnitData));
  
  xilDataFlush((MemUnit_T)1);
  xilTerminateComms();
}
#endif

/* Entry point (called from sil_main.c & pil_main.c) to initialize services */
XIL_INTERFACE_LIB_ERROR_CODE xilInit(const int argc, void *argv[]) {
    
    if (commsInit(argc, argv) != COMMS_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
    
    if (silpilInit()!=XIL_INTERFACE_LIB_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
    
#ifdef CODE_INSTRUMENTATION_ENABLED
    if (codeInstrInit()!=XIL_INTERFACE_LIB_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
#endif
    
#if CODER_ASSUMPTIONS_ENABLED == 1
    if (coderAssumptionsInit()!=XIL_INTERFACE_LIB_SUCCESS) {
        return XIL_INTERFACE_LIB_ERROR;
    }
#endif

#ifdef XIL_SIGNAL_HANDLER
    /* register signals to catch */
    signal(SIGFPE, XILSigHandler);  /* Erroneous arithmetic operation */
    signal(SIGILL, XILSigHandler);  /* Illegal operation */
    signal(SIGABRT, XILSigHandler); /* Abort signal */
    signal(SIGSEGV, XILSigHandler); /* Segmentation violation */
#endif

#ifdef SIL_DISABLE_SUBNORMAL_SUPPORT
    #if SIL_DISABLE_SUBNORMAL_SUPPORT == 1
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    #elif SIL_DISABLE_SUBNORMAL_SUPPORT == 2
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
    #endif
#endif
    return XIL_INTERFACE_LIB_SUCCESS;
}

/* Entry point (called from sil_main.c & pil_main.c) to terminate services */
XIL_INTERFACE_LIB_ERROR_CODE xilTerminateComms(void) {
    
    silpilTerminate();
    
#ifdef CODE_INSTRUMENTATION_ENABLED
    codeInstrTerminate();
#endif
    
#if CODER_ASSUMPTIONS_ENABLED == 1
    coderAssumptionsTerminate();
#endif
    
    commsTerminate();
    
    return XIL_INTERFACE_LIB_SUCCESS;
}


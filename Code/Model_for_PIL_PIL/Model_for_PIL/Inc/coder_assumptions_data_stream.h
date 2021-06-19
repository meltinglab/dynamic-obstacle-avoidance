/* Copyright 2015-2017 The MathWorks, Inc. */

/* 
 * File: coder_assumptions_data_stream.h
 *
 */					 

#include "xil_error_codes.h"
#include <stddef.h>

extern XIL_DATA_STREAM_ERROR_CODE coderAssumptionsWriteData(const void * src, const size_t size);
extern XIL_DATA_STREAM_ERROR_CODE coderAssumptionsSendWriteBuffer(void);
extern XIL_INTERFACE_LIB_ERROR_CODE resetCoderAssumptionsWriteBuffer(void);
extern XIL_INTERFACE_LIB_ERROR_CODE coderAssumptionsInit(void);
extern void coderAssumptionsTerminate(void);

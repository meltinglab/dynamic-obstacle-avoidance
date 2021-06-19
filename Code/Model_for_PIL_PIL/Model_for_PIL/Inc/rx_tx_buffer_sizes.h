/* Copyright 2013-2016 The MathWorks, Inc. */

/* 
 * File: rx_tx_buffer_sizes.h
 *
 * Defines the buffer sizes for the various XIL services.
 * Make sure we are backwards compatible with PIL implementations that 
 * define RTIOSTREAM_TX_BUFFER_BYTE_SIZE and RTIOSTREAM_RX_BUFFER_BYTE_SIZE
 * in their connectivity config. We will use these preprocessor defines to
 * derive both the RX and TX buffer sizes for the various XIL services and
 * make sure we don't incur more memory requirements.
 */		

#ifndef __RX_TX_BUFFER_SIZES_H__
#define __RX_TX_BUFFER_SIZES_H__

#include "rtwtypes.h"

/* transmit buffer size in mem units - no need to worry about fractions 
 * as division in C always floors the result. 
 */
#define RTIOSTREAM_TX_BUFFER_MEMUNIT_SIZE (RTIOSTREAM_TX_BUFFER_BYTE_SIZE / MEM_UNIT_BYTES)

/* Receive buffer size */
#ifdef HOST_WORD_ADDRESSABLE_TESTING
#define RTIOSTREAM_RX_BUFFER_SIZE (RTIOSTREAM_RX_BUFFER_BYTE_SIZE)
#else
#define RTIOSTREAM_RX_BUFFER_SIZE (RTIOSTREAM_RX_BUFFER_BYTE_SIZE / MEM_UNIT_BYTES)
#endif

/* # app services sharing the TX buffer allocation */
#ifdef CODE_INSTRUMENTATION_ENABLED
   #define NUM_APPS_SHARING_TX 2
#else
   /* XIL */
   #define NUM_APPS_SHARING_TX 1
#endif

/* send buffer sizes for applications */
#ifdef HOST_WORD_ADDRESSABLE_TESTING
   /* buffer is actually defined in terms of "byte" IOUnits 
    * so use BYTE_SIZE to make sure we have the same effective 
    * buffer size during PWS */
   #define XIL_TX_BUFFER_MEMUNIT_SIZE (RTIOSTREAM_TX_BUFFER_BYTE_SIZE / NUM_APPS_SHARING_TX)
#else
   #define XIL_TX_BUFFER_MEMUNIT_SIZE (RTIOSTREAM_TX_BUFFER_MEMUNIT_SIZE / NUM_APPS_SHARING_TX)
#endif

#if CODE_INSTRUMENTATION_ENABLED
   #define CODE_INSTR_TX_BUFFER_MEMUNIT_SIZE XIL_TX_BUFFER_MEMUNIT_SIZE
#endif

#if CODER_ASSUMPTIONS_ENABLED == 1
/* buffer includes space for BUFFER_HEADER_SIZE */
#ifdef HOST_WORD_ADDRESSABLE_TESTING
   /* buffer is actually defined in terms of "byte" IOUnits 
    * so multiply up to make sure we have the same effective 
    * buffer size during PWS */
   #define CA_TX_BUFFER_MEMUNIT_SIZE (32 * MEM_UNIT_BYTES)
   #if CA_TX_BUFFER_MEMUNIT_SIZE > RTIOSTREAM_TX_BUFFER_BYTE_SIZE
     #error "Coder assumptions transmit buffer size must be less than or equal to the overall rtiostream transmit buffer size.   Increase RTIOSTREAM_TX_BUFFER_BYTE_SIZE accordingly."
   #endif
#else
   /* simply reserve a 32 memunit buffer */
   #define CA_TX_BUFFER_MEMUNIT_SIZE 32
   #if CA_TX_BUFFER_MEMUNIT_SIZE > RTIOSTREAM_TX_BUFFER_MEMUNIT_SIZE
     #error "Coder assumptions transmit buffer size must be less than or equal to the overall rtiostream transmit buffer size.   Increase RTIOSTREAM_TX_BUFFER_BYTE_SIZE accordingly."
   #endif
#endif

#endif

#define APPLICATION_ID_SIZE (sizeof(MemUnit_T))
#define WRITE_DATA_AVAIL_SIZE (sizeof(uint32_T))
#define BUFFER_HEADER_SIZE  (APPLICATION_ID_SIZE + WRITE_DATA_AVAIL_SIZE)
#define APPLICATION_ID_IDX 0
#define PAYLOAD_SIZE_IDX (APPLICATION_ID_IDX + APPLICATION_ID_SIZE)
#define PAYLOAD_IDX (PAYLOAD_SIZE_IDX + WRITE_DATA_AVAIL_SIZE)

#endif /*__RX_TX_BUFFER_SIZES_H__ */


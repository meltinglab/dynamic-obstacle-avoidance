/* Copyright 2015-2017 The MathWorks, Inc. */
#ifndef __CODER_ASSUMPTIONS_HWIMPL_H__
#define __CODER_ASSUMPTIONS_HWIMPL_H__

#include "coder_assumptions_shared_enums.h"

typedef struct {
   CA_TestResultStatus status;
   CA_TestResultMsgId msg;
} CA_TestResult;

typedef unsigned int CA_BitsPerXValue;

typedef unsigned int CA_OnOffValue;

typedef struct {
   CA_BitsPerXValue bitsPerChar;
   CA_BitsPerXValue bitsPerShort;
   CA_BitsPerXValue bitsPerInt;
   CA_BitsPerXValue bitsPerLong;
   CA_BitsPerXValue bitsPerLongLong;
   CA_BitsPerXValue bitsPerFloat;
   CA_BitsPerXValue bitsPerDouble;
   CA_BitsPerXValue bitsPerPointer;
   CA_BitsPerXValue bitsPerSizeT;
   CA_BitsPerXValue bitsPerPtrDiffT;
   CA_EndianessValue byteOrder;
   CA_IntDivRoundToValue intDivRoundTo;
   CA_OnOffValue shiftRightBehavior;
   CA_OnOffValue supportLongLong;
   CA_OnOffValue portableWordSizes;
   const char * hwDeviceType;
   CA_OnOffValue memoryAtStartup;
   CA_OnOffValue denormalFlushToZero;
   CA_OnOffValue denormalAsZero;
} CA_HWImpl;

typedef struct {
   CA_TestResult bitsPerChar;
   CA_TestResult bitsPerShort;
   CA_TestResult bitsPerInt;
   CA_TestResult bitsPerLong;
   CA_TestResult bitsPerLongLong;
   CA_TestResult bitsPerFloat;
   CA_TestResult bitsPerDouble;
   CA_TestResult bitsPerPointer;
   CA_TestResult bitsPerSizeT;
   CA_TestResult bitsPerPtrDiffT;
   CA_TestResult byteOrder;
   CA_TestResult intDivRoundTo;
   CA_TestResult shiftRightBehavior;
   CA_TestResult supportLongLong;
   CA_TestResult memoryAtStartup;
   CA_TestResult denormalFlushToZero;
   CA_TestResult denormalAsZero;
} CA_HWImpl_TestResults;

typedef struct {
   CA_TestResult configSetting;
} CA_PWS_TestResults;

extern void caVerifyHWImpl(CA_HWImpl *, const CA_HWImpl *, CA_HWImpl_TestResults *);
extern void caVerifyPortableWordSizes(CA_HWImpl *, const CA_HWImpl *, CA_PWS_TestResults *);


#endif

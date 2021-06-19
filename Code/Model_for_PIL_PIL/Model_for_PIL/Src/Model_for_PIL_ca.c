/*
 * File: Model_for_PIL_ca.c
 *
 * Abstract: Tests assumptions in the generated code.
 */

#include "Model_for_PIL_ca.h"

CA_HWImpl_TestResults CA_Model_for_PIL_HWRes;
CA_PWS_TestResults CA_Model_for_PIL_PWSRes;
const CA_HWImpl CA_Model_for_PIL_ExpHW = {
  8,                                   /* BitPerChar */
  16,                                  /* BitPerShort */
  32,                                  /* BitPerInt */
  32,                                  /* BitPerLong */
  64,                                  /* BitPerLongLong */
  32,                                  /* BitPerFloat */
  64,                                  /* BitPerDouble */
  32,                                  /* BitPerPointer */
  32,                                  /* BitPerSizeT */
  32,                                  /* BitPerPtrDiffT */
  CA_LITTLE_ENDIAN,                    /* Endianess */
  CA_ZERO,                             /* IntDivRoundTo */
  1,                                   /* ShiftRightIntArith */
  0,                                   /* LongLongMode */
  0,                                   /* PortableWordSizes */
  "STM32CortexM",                      /* HWDeviceType */
  0,                                   /* MemoryAtStartup */
  0,                                   /* DenormalFlushToZero */
  0                                    /* DenormalAsZero */
};

CA_HWImpl CA_Model_for_PIL_ActHW;
void Model_for_PIL_caRunTests(void)
{
  /* verify hardware implementation */
  caVerifyPortableWordSizes(&CA_Model_for_PIL_ActHW, &CA_Model_for_PIL_ExpHW,
    &CA_Model_for_PIL_PWSRes);
  caVerifyHWImpl(&CA_Model_for_PIL_ActHW, &CA_Model_for_PIL_ExpHW,
                 &CA_Model_for_PIL_HWRes);
}

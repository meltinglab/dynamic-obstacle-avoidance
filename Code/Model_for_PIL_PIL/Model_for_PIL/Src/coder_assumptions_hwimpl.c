/* Copyright 2015-2018 The MathWorks, Inc. */

#include "coder_assumptions_hwimpl.h"

#include <stddef.h>
#include <limits.h>

/* CA_CHECK_FLOATING_POINT_ENABLED controls whether floating point 
 * checks are executed. */
#ifndef CA_CHECK_FLOATING_POINT_ENABLED
   #error "CA_CHECK_FLOATING_POINT_ENABLED should always be defined!"
#endif

/* CA_CHECK_LONG_LONG_ENABLED controls whether long long checks 
 * are executed. */
#ifndef CA_CHECK_LONG_LONG_ENABLED
   #error "CA_CHECK_LONG_LONG_ENABLED should always be defined!"
#endif

#if CA_CHECK_LONG_LONG_ENABLED == 1
    /* we would expect "long long" compilation failure to 
    * have occurred if long long is not available. */
    typedef unsigned long long ca_numBits_t;
#else
    typedef unsigned long ca_numBits_t;
#endif

#if CA_CHECK_FLOATING_POINT_ENABLED == 1
#include <float.h>
#endif

/* For testing memory at startup - are globals default-initialized to 0? */
CA_OnOffValue aGlobalInt;

#if CA_CHECK_FLOATING_POINT_ENABLED == 1
    static volatile double realmin = DBL_MIN;
    extern volatile double denormalAsZero;
#endif

/* return the minimum number of bits needed to 
 * represent the input value */
static unsigned int numBits(ca_numBits_t value) {
   /* note: returns 1 for zero as well as 1 */
   unsigned int num = 1;

   while (value >>= 1) {
      num++;
   }
   return num;
}

static unsigned int getBitsPerMemUnit(CA_HWImpl * act){
   /* sizeof returns a size in memory units (bytes for byte addressable machines
    * and words for word addressable machines). Determine the number of 
    * bits each sizeof memory unit represents. */
   CA_BitsPerXValue bitsPerMemUnit=0;
   
   #ifndef CA_BITS_PER_MEM_UNITS
   /* Find the largest data type (up to at least 32-bits wide, i.e. long) 
    * with sizeof equal to 1 and assume its number of bits fully fills the underlying 
    * memory unit */
   #if defined(_WIN32) && defined(_MSC_VER)
      /*temporarily disable warning C4127 caused by using sizeof in boolean equation*/
      #pragma warning(push)
      #pragma warning(disable: 4127)
   #endif
   if (sizeof(long) == 1) {
      bitsPerMemUnit = act->bitsPerLong;
   }
   else if (sizeof(int) == 1) {
      bitsPerMemUnit = act->bitsPerInt;
   }
   else if (sizeof(short) == 1) {
      bitsPerMemUnit = act->bitsPerShort;
   }
   else if (sizeof(char) == 1) {
      bitsPerMemUnit = act->bitsPerChar;
   }
   #if defined(_WIN32) && defined(_MSC_VER)
      /*re-enable the warning C4127*/
      #pragma warning(pop)
   #endif

   #else
      /* allow override via preprocessor define, e.g. in case of 
       * a 64-bit word addressable architecture with 
       * 32-bit long data type stored in a 64-bit container. */
      bitsPerMemUnit = CA_BITS_PER_MEM_UNITS;
  #endif
    return bitsPerMemUnit;
}

/* get CPU characteristics */
static void getCPUInfo(CA_HWImpl * act,  CA_BitsPerXValue * bitsPerMemUnit) {
   int i1, i2, i3, i4, i5, i6, i7, i8, i9, r1, r2;
   
   /*-----------------------------------------------------------------------
    * shifts right on signed integers
    */
   i1 = -28;
   i2 = ( i1 >> 2 );

   act->shiftRightBehavior = ( i2 == ( i1 /  4) );

   /*-----------------------------------------------------------------------
    * negative operand integer division rounding
    */

   {
      /* num and denom must be declared volatile to force the divisions to
       * happen on the target, instead of being optimized away by the compiler.
       */
      volatile int num, denom;

      denom = 4;
      num = -7;
      i1 = num / denom;   /* -7/4 */
      num = -6;
      i2 = num / denom;   /* -6/4 */
      num = -5;
      i3 = num / denom;   /* -5/4 */
      denom = -4;
      num = 7;
      i4 = num / denom;   /* 7/-4 */
      num = 6;
      i5 = num / denom;   /* 6/-4 */
      num = 5;
      i6 = num / denom;   /* 5/-4 */
      num = -7;
      i7 = num / denom;   /* -7/-4 */
      num = -6;
      i8 = num / denom;   /* -6/-4 */
      num = -5;
      i9 = num / denom;   /* -5/-4 */
   }

   /* round toward floor test */
   r1 = ((i1 == -2) && (i2 == -2) && (i3 == -2) &&
         (i4 == -2) && (i5 == -2) && (i6 == -2) &&
         (i7 ==  1) && (i8 ==  1) && (i9 ==  1));

   /* round toward zero test */
   r2 = ((i1 == -1) && (i2 == -1) && (i3 == -1) &&
         (i4 == -1) && (i5 == -1) && (i6 == -1) &&
         (i7 ==  1) && (i8 ==  1) && (i9 ==  1));

   /* set rounding behaviour*/
   if (r1 && !r2) {
      /* Rounds to floor */
      act->intDivRoundTo = CA_FLOOR;
   }
   else if (!r1 && r2) {
      /* rounds to zero */
      act->intDivRoundTo = CA_ZERO;
   }
   else {
      /* undefined */
      act->intDivRoundTo = CA_UNDEFINED;
   }

   {
      /*-----------------------------------------------------------------------
       * Byte order test
       */
       
       /* Avoid compiler warning about constant expression */
       volatile int isSameSize = (sizeof(long) == sizeof(char));
       if (isSameSize) {
           /* This Byte order test assumes that the size of char is 
            * less than the size of long. If this is not the case (for 
            * example TigerSharc integer data type sizes are all 32-bit), 
            * then this test will always return that the target is little 
            * endian. For such targets, the byte order becomes irrelevant 
            * and is safe to skip.
            */
           act->byteOrder = CA_UNABLE_TO_DETERMINE_ON_TARGET;
       } else {
           long s1 = 1;
           act->byteOrder =  (*((char *) &s1) == 1) ? CA_LITTLE_ENDIAN : CA_BIG_ENDIAN;
       }
   }
   
   /*-----------------------------------------------------------------------
    * bits per char, short, int, long
    *
    * limits.h based check supports the case where a smaller data
    * type is implemented in a larger container, e.g. an 8-bit integer
    * implemented in a 16-bit container on some word addressable systems, 
    * e.g. DSP563xx 16-bit mode - sizeof(char) would be one 16-bit word whereas
    * UCHAR_MAX would be limited to 255.
    */
   act->bitsPerChar = numBits(UCHAR_MAX);
   act->bitsPerShort = numBits(USHRT_MAX);
   act->bitsPerInt = numBits(UINT_MAX);
   act->bitsPerLong = numBits(ULONG_MAX);
   *bitsPerMemUnit=getBitsPerMemUnit(act);
#if CA_CHECK_LONG_LONG_ENABLED == 1
   {
    /* expect "long long" compilation failure to have occurred 
     * during production code compilation, e.g. rtwtypes.h */
    act->supportLongLong = 1;
      
    /* report bits per long long based on type bits rather than 
     * ULLONG_MAX which may not exist pre-C99 */
    act->bitsPerLongLong = numBits(~(unsigned long long)0);
   }
#else   
   /* set default values, but they won't be checked against */
   act->supportLongLong = 0;
   act->bitsPerLongLong = 0;
#endif

   return;
}

static CA_TestResult testPass(const CA_TestResultMsgId msg) {
   CA_TestResult result;
   result.status = CA_PASS;
   result.msg = msg;
   return result;
}

static CA_TestResult testFail(const CA_TestResultMsgId msg) {
   CA_TestResult result;
   result.status = CA_FAIL;
   result.msg = msg;
   return result;
}

static CA_TestResult testWarn(const CA_TestResultMsgId msg) {
   CA_TestResult result;
   result.status = CA_WARN;
   result.msg = msg;
   return result;
}

static CA_TestResult testSkip(const CA_TestResultMsgId msg) {
   CA_TestResult result;
   result.status = CA_SKIP;
   result.msg = msg;
   return result;
}

/* the testReview function is currently used only if floating points are 
 * enabled. when this function will be used elsewhere, the guard below  
 * must be removed. */
#if CA_CHECK_FLOATING_POINT_ENABLED == 1
static CA_TestResult testReview(const CA_TestResultMsgId msg) {
   CA_TestResult result;
   result.status = CA_INFO;
   result.msg = msg;
   return result;
}
#endif

static CA_TestResult runTest(const unsigned int actual, const unsigned int config) {
   CA_TestResult result;
   if (actual == config) {
      result = testPass(CA_NO_MSG);
   }
   else {
      result = testFail(CA_NO_MSG);
   }
   return result;
}

/* portable word sizes specified checks */
void caVerifyPortableWordSizes(CA_HWImpl * act, const CA_HWImpl * exp, CA_PWS_TestResults * res) {
   /* see if code is being compiled with portable word sizes 
    * switched on: note that even if the PortableWordSizes
    * configuration setting is on, the code may be compiled
    * without the PORTABLE_WORDSIZES define for on-target 
    * use. */
#ifdef PORTABLE_WORDSIZES
   act->portableWordSizes = 1;
#else
   act->portableWordSizes = 0;
#endif

   if (act->portableWordSizes) {
      /* check config setting is consistent with preprocessor define */
      if (exp->portableWordSizes) {
         res->configSetting = testPass(CA_NO_MSG);
      }
      else {
         res->configSetting = testFail(CA_ERROR_PWS_CONFIG_SETTING);   
      }
   }
}

/* Hardware implementation checks */
void caVerifyHWImpl(CA_HWImpl * act, const CA_HWImpl * exp, CA_HWImpl_TestResults * res) {
   CA_BitsPerXValue bitsPerMemUnit;
   /* 
    * Get the actual CPU info 
    */
   getCPUInfo(act, &bitsPerMemUnit);
   
   /* 
    * Run tests against expected CPU info 
    */
   if ((act->intDivRoundTo == CA_UNDEFINED) && 
        (exp->intDivRoundTo != CA_UNDEFINED)) {
      /* actual behavior undefined => config must 
       * choose undefined too */
      res->intDivRoundTo = testFail(CA_NO_MSG);
   }
   else {
      if (exp->intDivRoundTo == CA_UNDEFINED) {
         /* Undefined is sub-optimal */
         res->intDivRoundTo = testWarn(CA_WARN_INT_DIV_UNDEFINED);
      }
      else {
         if (act->intDivRoundTo == exp->intDivRoundTo) {
               res->intDivRoundTo = testPass(CA_NO_MSG);
         }
         else {
            res->intDivRoundTo = testFail(CA_NO_MSG);
         }
      }
   }

   if (exp->byteOrder == CA_UNSPECIFIED) {
      /* Undefined is sub-optimal */
      res->byteOrder = testWarn(CA_WARN_BYTE_ORDER_UNSPECIFIED);      
   } else if (act->byteOrder == CA_UNABLE_TO_DETERMINE_ON_TARGET) {
       /* skip byte order test for targets that has all of its integer 
        * types size set to 32-bit */
       res->byteOrder = testPass(CA_NO_MSG);
   } else {
      if (act->byteOrder == exp->byteOrder) {
         res->byteOrder = testPass(CA_NO_MSG);
      }
      else {
         res->byteOrder = testFail(CA_NO_MSG);
      }
   }

   /* shiftRightBehavior
    *
    * note that shift right behavior has no impact on portable 
    * word sizes behavior because even when this option is off, 
    * portable code is generated */
   res->shiftRightBehavior = runTest(act->shiftRightBehavior, 
         exp->shiftRightBehavior);

   /* bitsPerChar */
   res->bitsPerChar = runTest(act->bitsPerChar, 
         exp->bitsPerChar);

   /* bitsPerShort */
   res->bitsPerShort = runTest(act->bitsPerShort, 
         exp->bitsPerShort);

   /* bitsPerInt */
   res->bitsPerInt = runTest(act->bitsPerInt, 
         exp->bitsPerInt);

   /* bitsPerLong */
   res->bitsPerLong = runTest(act->bitsPerLong, 
         exp->bitsPerLong);

   /* user has to opt in to support long long */
   if (exp->supportLongLong) {
      /* check actual support */
      res->supportLongLong = runTest(act->supportLongLong, 
            exp->supportLongLong);   

      /* check bits per long long */
      res->bitsPerLongLong = runTest(act->bitsPerLongLong, 
            exp->bitsPerLongLong);
   }
   else {
      /* ok */
      res->supportLongLong = testSkip(CA_NO_MSG);
      /* ok */
      res->bitsPerLongLong = testSkip(CA_NO_MSG);
   }

#if CA_CHECK_FLOATING_POINT_ENABLED == 1
   act->bitsPerFloat = sizeof(float) * bitsPerMemUnit;
   act->bitsPerDouble = sizeof(double) * bitsPerMemUnit;
   
   /* float is not configurable in the config so just warn */
   if (act->bitsPerFloat == exp->bitsPerFloat) {
      res->bitsPerFloat = testPass(CA_NO_MSG);
   }
   else {
      res->bitsPerFloat = testWarn(CA_NO_MSG);
   }

   /* double is not configurable in the config so just warn
    *
    * Allow either 32 or 64 bits without warning.
    * Note that PIL has an additional run time check for 
    * non-64-bit double and will error in this case if 
    * double data types are used at the component boundary.*/
   switch (act->bitsPerDouble) {
      case 32: /* drop through */
      case 64:
         res->bitsPerDouble = testPass(CA_NO_MSG);
         break;
      default:
         res->bitsPerDouble = testWarn(CA_NO_MSG);
         break;
   }
#else
   res->bitsPerFloat = testSkip(CA_NO_MSG);
   res->bitsPerDouble = testSkip(CA_NO_MSG);   
#endif

   /* pointer is fully configurable => error on failure */
   act->bitsPerPointer = sizeof(void *) * bitsPerMemUnit;
   res->bitsPerPointer = runTest(act->bitsPerPointer, 
         exp->bitsPerPointer);

   /* size_t and ptrdiff_t defined in stddef.h */
   act->bitsPerSizeT = sizeof(size_t) * bitsPerMemUnit;
   res->bitsPerSizeT = runTest(act->bitsPerSizeT, exp->bitsPerSizeT);

   act->bitsPerPtrDiffT = sizeof(ptrdiff_t) * bitsPerMemUnit;
   res->bitsPerPtrDiffT = runTest(act->bitsPerPtrDiffT, exp->bitsPerPtrDiffT);

   /*-----------------------------------------------------------------------
    * Memory at startup test.
    *
    * According to the C standard, the value of uninitialized globals is set to
    * 0 by the compiler. This verifies that the value of the global int defined
    * at the top of the file is actually 0 as expected.
    */
   act->memoryAtStartup = aGlobalInt;
   if (act->memoryAtStartup != exp->memoryAtStartup){
       /* Warn if globals are not default initialized to 0. */
       res->memoryAtStartup = testWarn(CA_NO_MSG);
   }
   else {
       res->memoryAtStartup = testPass(CA_NO_MSG);
   }
   
#if CA_CHECK_FLOATING_POINT_ENABLED == 1
   /*-----------------------------------------------------------------------
    * Denormal floating points support tests.
    *
    */
   act->denormalFlushToZero = (realmin/2.0) == 0 ? (CA_OnOffValue)1 : (CA_OnOffValue)0;
   if (act->denormalFlushToZero != exp->denormalFlushToZero){
       /* review if denormal results are flushed to zero */
       res->denormalFlushToZero = testReview(CA_NO_MSG);
   }
   else {
       res->denormalFlushToZero = testPass(CA_NO_MSG);
   }
   
   act->denormalAsZero = denormalAsZero == 0 ? (CA_OnOffValue)1 : (CA_OnOffValue)0;
   if (act->denormalAsZero != exp->denormalAsZero) {
       /* review if denormal inputs are defaulted to zero */
       res->denormalAsZero = testReview(CA_NO_MSG);
   }
   else {
       res->denormalAsZero = testPass(CA_NO_MSG);
   }
#else
   res->denormalFlushToZero = testSkip(CA_NO_MSG);
   res->denormalAsZero = testSkip(CA_NO_MSG);
#endif
}


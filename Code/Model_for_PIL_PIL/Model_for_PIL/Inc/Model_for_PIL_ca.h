/*
 * File: Model_for_PIL_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef MODEL_FOR_PIL_CA_H
#define MODEL_FOR_PIL_CA_H

/* preprocessor validation checks */
#include "Model_for_PIL_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_HWImpl_TestResults CA_Model_for_PIL_HWRes;
extern CA_PWS_TestResults CA_Model_for_PIL_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_HWImpl CA_Model_for_PIL_ExpHW;
extern CA_HWImpl CA_Model_for_PIL_ActHW;

/* entry point function to run tests */
void Model_for_PIL_caRunTests(void);

#endif                                 /* MODEL_FOR_PIL_CA_H */

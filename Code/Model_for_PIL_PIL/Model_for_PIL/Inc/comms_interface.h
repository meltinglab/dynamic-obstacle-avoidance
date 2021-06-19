/* Copyright 2015 The MathWorks, Inc. */
#ifndef comms_interface_h
#define comms_interface_h

/* error codes */
static const int COMMS_ERROR = 0;
static const int COMMS_SUCCESS = 1;

/* initialize comm service */
extern int commsInit(const int argc, void * argv[]);

/* terminate comm service */
extern int commsTerminate(void);

#endif

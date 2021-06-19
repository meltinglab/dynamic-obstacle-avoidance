/* STM32SerialRtiostream-ProfilerTimer.c
 *
 * Specifies profile timer access functions
 *
 * Copyright 2011 The MathWorks, Inc.
 */

#include "STM32SerialRtiostream-ProfilerTimer.h"
#include "STM32SerialRtiostream_Config.h"


void profileTimerInit(void)
{
    /* SysTick called every time currentVal 1 to 0. Then reloaded with reload val. */
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL  = 0x00000000;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}


unsigned int profileTimerRead(unsigned int initTimer)
{
    static unsigned char initTimerDone = 0;
    unsigned int timerVal;

    if (initTimer == 0)
    {
        /* When initTimer is null, it is xilProfilingSectionStart */
        SysTick->VAL = 0x00FFFFFF;
        timerVal = 0x00FFFFFF;
        initTimerDone = 1;
    }
    else
    {
        /*When initTimer is NOT null, it is xilProfilingSectionEnd if init has been done initTimerDone == 1 */
        if (initTimerDone == 1)
        {
            timerVal = SysTick->VAL;
            initTimerDone = 0;
        }
        else
        {
            initTimerDone = 1;
            SysTick->VAL = 0x00FFFFFF;
            timerVal = 0x00FFFFFF;
        }
    }

    return timerVal;
}

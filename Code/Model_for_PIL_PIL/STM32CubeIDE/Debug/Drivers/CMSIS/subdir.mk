################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/djtn/Documents/GitHub/dynamic-obstacle-avoidance/Code/Model_for_PIL_PIL/Src/system_stm32l4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32l4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32l4xx.o: C:/Users/djtn/Documents/GitHub/dynamic-obstacle-avoidance/Code/Model_for_PIL_PIL/Src/system_stm32l4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-DMemUnit_T=uint8_T' '-DMEM_UNIT_BYTES=1' '-DRTIOSTREAM_TX_BUFFER_BYTE_SIZE=128' '-DRTIOSTREAM_RX_BUFFER_BYTE_SIZE=128' '-DCODER_ASSUMPTIONS_ENABLED=1' -DCA_CHECK_FLOATING_POINT_ENABLED -DCA_CHECK_LONG_LONG_ENABLED -DCA_CHECK_DAZ_ENABLED -DSTM32L433xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Model_for_PIL/Inc -I../../../../../../../../../MATLAB/STM32-MAT/STM32/pil/stm32SerialRtiostream -I"../../../../../../../../../Program Files/MATLAB/R2019a/extern/include" -I"../../../../../../../../../Program Files/MATLAB/R2019a/extern/include/coder/connectivity/CoderAssumpTgtAppSvc" -I"../../../../../../../../../Program Files/MATLAB/R2019a/extern/include/coder/connectivity/XILTgtAppSvc" -I"../../../../../../../../../Program Files/MATLAB/R2019a/rtw/c/ert" -I"../../../../../../../../../Program Files/MATLAB/R2019a/rtw/c/src" -I"../../../../../../../../../Program Files/MATLAB/R2019a/rtw/c/src/ext_mode/common" -I"../../../../../../../../../Program Files/MATLAB/R2019a/simulink/include" -I"../../../../../../../../../Program Files/MATLAB/R2019a/toolbox/coder/rtiostream/src" -I"../../../../../../../../../Program Files/MATLAB/R2019a/toolbox/coder/rtiostream/src/utils" -I"../../../../../../../../../Program Files/MATLAB/R2019a/toolbox/rtw/targets/pil/c" -I../../../slprj/stm32/Model_for_PIL -I../../../slprj/stm32/Model_for_PIL/coderassumptions -I../../../slprj/stm32/Model_for_PIL/pil -I../../../slprj/stm32/_sharedutils -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


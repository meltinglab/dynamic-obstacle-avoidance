################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MATLAB/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/subdir.mk
-include Application/Startup/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Model_for_PIL.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Model_for_PIL.list \

OBJCOPY_BIN += \
Model_for_PIL.bin \


# All Target
all: Model_for_PIL.elf secondary-outputs

# Tool invocations
Model_for_PIL.elf: $(OBJS) $(USER_OBJS) C:\Users\djtn\Documents\GitHub\dynamic-obstacle-avoidance\Code\Model_for_PIL_PIL\STM32CubeIDE\STM32L433RCTXP_FLASH.ld
	arm-none-eabi-gcc -o "Model_for_PIL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\djtn\Documents\GitHub\dynamic-obstacle-avoidance\Code\Model_for_PIL_PIL\STM32CubeIDE\STM32L433RCTXP_FLASH.ld" --specs=nosys.specs -Wl,-Map="Model_for_PIL.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Model_for_PIL.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Model_for_PIL.list"
	@echo 'Finished building: $@'
	@echo ' '

Model_for_PIL.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Model_for_PIL.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

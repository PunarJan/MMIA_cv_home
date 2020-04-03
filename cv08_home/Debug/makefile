################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cv08_home.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
cv08_home.list \

OBJCOPY_BIN += \
cv08_home.bin \


# All Target
all: cv08_home.elf secondary-outputs

# Tool invocations
cv08_home.elf: $(OBJS) $(USER_OBJS) C:\Users\Punar\Desktop\MMIA_cv_home\cv08_home\STM32F429ZITX_FLASH.ld
	arm-none-eabi-gcc -o "cv08_home.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Punar\Desktop\MMIA_cv_home\cv08_home\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="cv08_home.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

cv08_home.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "cv08_home.list"
	@echo 'Finished building: $@'
	@echo ' '

cv08_home.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "cv08_home.bin"
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

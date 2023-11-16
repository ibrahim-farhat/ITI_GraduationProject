################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TestApp/subdir.mk
-include SERL/ICU/Source/subdir.mk
-include SERL/FIR/Source/subdir.mk
-include MCAL/TIMERS/Source/subdir.mk
-include MCAL/SPI/Source/subdir.mk
-include MCAL/PORT/Source/subdir.mk
-include MCAL/GIE/Source/subdir.mk
-include MCAL/DIO/Source/subdir.mk
-include MCAL/ADC/Source/subdir.mk
-include HAL/ULTSONIC/Source/subdir.mk
-include HAL/MOTOR/Source/subdir.mk
-include HAL/MCP/Source/subdir.mk
-include HAL/LM35/Source/subdir.mk
-include HAL/LDR/Source/subdir.mk
-include HAL/CLCD/Source/subdir.mk
-include Data_Structures/Stack/subdir.mk
-include Data_Structures/Queue/subdir.mk
-include Common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
ITI_GP.lss \

FLASH_IMAGE += \
ITI_GP.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ITI_GP.elf secondary-outputs

# Tool invocations
ITI_GP.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ITI_GP.map -mmcu=atmega32 -o "ITI_GP.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ITI_GP.lss: ITI_GP.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ITI_GP.elf  >"ITI_GP.lss"
	@echo 'Finished building: $@'
	@echo ' '

ITI_GP.hex: ITI_GP.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ITI_GP.elf  "ITI_GP.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ITI_GP.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ITI_GP.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ITI_GP.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

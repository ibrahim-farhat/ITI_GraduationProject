################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TestApp/subdir.mk
-include MCAL/USART/Source/subdir.mk
-include MCAL/TIMERS/Source/subdir.mk
-include MCAL/SPI/Source/subdir.mk
-include MCAL/PORT/Source/subdir.mk
-include MCAL/GIE/Source/subdir.mk
-include MCAL/DIO/Source/subdir.mk
-include HAL/ULTSONIC/Source/subdir.mk
-include HAL/MOTOR/Source/subdir.mk
-include HAL/MCP/Source/subdir.mk
-include HAL/CLCD/Source/subdir.mk
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
ITI_GP_Motors.lss \

FLASH_IMAGE += \
ITI_GP_Motors.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ITI_GP_Motors.elf secondary-outputs

# Tool invocations
ITI_GP_Motors.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ITI_GP_Motors.map -mmcu=atmega32 -o "ITI_GP_Motors.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ITI_GP_Motors.lss: ITI_GP_Motors.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ITI_GP_Motors.elf  >"ITI_GP_Motors.lss"
	@echo 'Finished building: $@'
	@echo ' '

ITI_GP_Motors.hex: ITI_GP_Motors.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ITI_GP_Motors.elf  "ITI_GP_Motors.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ITI_GP_Motors.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ITI_GP_Motors.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ITI_GP_Motors.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

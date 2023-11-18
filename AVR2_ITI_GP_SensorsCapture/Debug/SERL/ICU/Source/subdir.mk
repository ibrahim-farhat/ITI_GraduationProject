################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERL/ICU/Source/ICU_program.c 

OBJS += \
./SERL/ICU/Source/ICU_program.o 

C_DEPS += \
./SERL/ICU/Source/ICU_program.d 


# Each subdirectory must supply rules for building sources it contributes
SERL/ICU/Source/%.o: ../SERL/ICU/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



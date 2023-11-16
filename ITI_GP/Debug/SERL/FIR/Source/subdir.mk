################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERL/FIR/Source/FIR_program.c 

OBJS += \
./SERL/FIR/Source/FIR_program.o 

C_DEPS += \
./SERL/FIR/Source/FIR_program.d 


# Each subdirectory must supply rules for building sources it contributes
SERL/FIR/Source/%.o: ../SERL/FIR/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



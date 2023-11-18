################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FIR_program.c \
../Src/GPIO_program.c \
../Src/MCP2515_program.c \
../Src/RCC_program.c \
../Src/SPI_Program.c \
../Src/SYSTICK_program.c \
../Src/main.c \
../Src/queue.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/FIR_program.o \
./Src/GPIO_program.o \
./Src/MCP2515_program.o \
./Src/RCC_program.o \
./Src/SPI_Program.o \
./Src/SYSTICK_program.o \
./Src/main.o \
./Src/queue.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/FIR_program.d \
./Src/GPIO_program.d \
./Src/MCP2515_program.d \
./Src/RCC_program.d \
./Src/SPI_Program.d \
./Src/SYSTICK_program.d \
./Src/main.d \
./Src/queue.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/FIR_program.cyclo ./Src/FIR_program.d ./Src/FIR_program.o ./Src/FIR_program.su ./Src/GPIO_program.cyclo ./Src/GPIO_program.d ./Src/GPIO_program.o ./Src/GPIO_program.su ./Src/MCP2515_program.cyclo ./Src/MCP2515_program.d ./Src/MCP2515_program.o ./Src/MCP2515_program.su ./Src/RCC_program.cyclo ./Src/RCC_program.d ./Src/RCC_program.o ./Src/RCC_program.su ./Src/SPI_Program.cyclo ./Src/SPI_Program.d ./Src/SPI_Program.o ./Src/SPI_Program.su ./Src/SYSTICK_program.cyclo ./Src/SYSTICK_program.d ./Src/SYSTICK_program.o ./Src/SYSTICK_program.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/queue.cyclo ./Src/queue.d ./Src/queue.o ./Src/queue.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src


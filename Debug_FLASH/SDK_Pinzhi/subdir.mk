################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK_Pinzhi/delay.c \
../SDK_Pinzhi/key.c \
../SDK_Pinzhi/rtos.c \
../SDK_Pinzhi/uart.c 

OBJS += \
./SDK_Pinzhi/delay.o \
./SDK_Pinzhi/key.o \
./SDK_Pinzhi/rtos.o \
./SDK_Pinzhi/uart.o 

C_DEPS += \
./SDK_Pinzhi/delay.d \
./SDK_Pinzhi/key.d \
./SDK_Pinzhi/rtos.d \
./SDK_Pinzhi/uart.d 


# Each subdirectory must supply rules for building sources it contributes
SDK_Pinzhi/%.o: ../SDK_Pinzhi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK_Pinzhi/delay.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



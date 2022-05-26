################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../COTS/HAL/HLCD/HLCD_progr.c 

OBJS += \
./COTS/HAL/HLCD/HLCD_progr.o 

C_DEPS += \
./COTS/HAL/HLCD/HLCD_progr.d 


# Each subdirectory must supply rules for building sources it contributes
COTS/HAL/HLCD/%.o: ../COTS/HAL/HLCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



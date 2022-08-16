################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include COTS/MCAL/MWatchDogTimer/subdir.mk
-include COTS/MCAL/MUART/subdir.mk
-include COTS/MCAL/MTimers/subdir.mk
-include COTS/MCAL/MSPI/subdir.mk
-include COTS/MCAL/MI2C/subdir.mk
-include COTS/MCAL/MGIE/subdir.mk
-include COTS/MCAL/MEXTI/subdir.mk
-include COTS/MCAL/MDIO/subdir.mk
-include COTS/MCAL/MADC/subdir.mk
-include COTS/HAL/HSSD/subdir.mk
-include COTS/HAL/HLM35/subdir.mk
-include COTS/HAL/HLDR/subdir.mk
-include COTS/HAL/HLCD/subdir.mk
-include COTS/HAL/HKEYPAD/subdir.mk
-include COTS/HAL/HEEPROM/subdir.mk
-include COTS/HAL/HDCM/subdir.mk
-include COTS/APP/subdir.mk
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
PE_Drivers.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: PE_Drivers.elf secondary-outputs

# Tool invocations
PE_Drivers.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PE_Drivers.map -mmcu=atmega32 -o "PE_Drivers.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PE_Drivers.lss: PE_Drivers.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PE_Drivers.elf  >"PE_Drivers.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PE_Drivers.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PE_Drivers.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PE_Drivers.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

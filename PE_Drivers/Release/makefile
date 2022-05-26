################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include COTS/MCAL/MDIO/subdir.mk
-include COTS/HAL/HSSD/subdir.mk
-include COTS/HAL/HLCD/subdir.mk
-include COTS/HAL/HKEYPAD/subdir.mk
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

FLASH_IMAGE += \
PE_Drivers.hex \

EEPROM_IMAGE += \
PE_Drivers.eep \

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

PE_Drivers.hex: PE_Drivers.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex PE_Drivers.elf  "PE_Drivers.hex"
	@echo 'Finished building: $@'
	@echo ' '

PE_Drivers.eep: PE_Drivers.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex PE_Drivers.elf  "PE_Drivers.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PE_Drivers.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PE_Drivers.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PE_Drivers.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

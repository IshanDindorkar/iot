################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/ESP8266WiFi/src/subdir.mk
-include libraries/ESP8266HTTPClient/src/subdir.mk
-include libraries/DHT-sensor-library/subdir.mk
-include core/core/umm_malloc/subdir.mk
-include core/core/spiffs/subdir.mk
-include core/core/libb64/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/arduino.ar \

ELF += \
nodemcu_gateway.elf \

HEX += \
nodemcu_gateway.hex \


# All Target
all: nodemcu_gateway

# Tool invocations
nodemcu_gateway: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/opt/eclipse//arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-size" -A "/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/nodemcu_gateway.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/opt/eclipse//arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-ar" cru     /home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

nodemcu_gateway.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	${A.RECIPE.HOOKS.LINKING.PRELINK.1.PATTERN}
	"/opt/eclipse//arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-gcc" -fexceptions -Wl,-Map "-Wl,/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/nodemcu_gateway.map" -g -Wall -Wextra -Os -nostdlib -Wl,--no-check-sections -u app_entry -u _printf_float -u _scanf_float -Wl,-static "-L/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/lib" "-L/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/lib/NONOSDK22x_190703" "-L/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/ld" "-L/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/libc/xtensa-lx106-elf/lib" "-Teagle.flash.4m3m.ld" -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,spi_flash_read  -o "/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/nodemcu_gateway.elf" -Wl,--start-group   $(LINK_OBJ)   /home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release/arduino.ar  -lhal -lphy -lpp -lnet80211 -llwip2-536-feat -lwpa -lcrypto -lmain -lwps -lbearssl -laxtls -lespnow -lsmartconfig -lairkiss -lwpa2 -lstdc++-exc -lm -lc -lgcc -Wl,--end-group  "-L/home/ishan/eclipse-arduino-workspace/nodemcu_gateway/Release"
	@echo 'Finished building: $@'
	@echo ' '

nodemcu_gateway.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${A.RECIPE.OBJCOPY.HEX.1.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.2.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.3.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets

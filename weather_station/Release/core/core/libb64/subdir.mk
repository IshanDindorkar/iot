################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266/libb64/cdecode.cpp \
/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266/libb64/cencode.cpp 

AR_OBJ += \
./core/core/libb64/cdecode.cpp.o \
./core/core/libb64/cencode.cpp.o 

CPP_DEPS += \
./core/core/libb64/cdecode.cpp.d \
./core/core/libb64/cencode.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
core/core/libb64/cdecode.cpp.o: /opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266/libb64/cdecode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/eclipse//arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/include" "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/lwip2/include" "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/ishan/eclipse-arduino-workspace/weather_station/Release/core" -c -Wall -Wextra -Os -g -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++11 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_NODEMCU -DARDUINO_ARCH_ESP8266 '-DARDUINO_BOARD="ESP8266_NODEMCU"' -DLED_BUILTIN=16 -DFLASHMODE_DIO  -DESP8266   -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/variants/nodemcu" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266HTTPClient/src" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266WiFi/src" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/SPI" -I"/home/ishan/Arduino/libraries/DHT-sensor-library" -I"/home/ishan/Arduino/libraries/Adafruit_Sensor" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

core/core/libb64/cencode.cpp.o: /opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266/libb64/cencode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/eclipse//arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/2.5.0-4-b40a506/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/include" "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/lwip2/include" "-I/opt/eclipse//arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/ishan/eclipse-arduino-workspace/weather_station/Release/core" -c -Wall -Wextra -Os -g -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++11 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_NODEMCU -DARDUINO_ARCH_ESP8266 '-DARDUINO_BOARD="ESP8266_NODEMCU"' -DLED_BUILTIN=16 -DFLASHMODE_DIO  -DESP8266   -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/variants/nodemcu" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266HTTPClient/src" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266WiFi/src" -I"/opt/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.7.4/libraries/SPI" -I"/home/ishan/Arduino/libraries/DHT-sensor-library" -I"/home/ishan/Arduino/libraries/Adafruit_Sensor" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/Core/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/Core/Src/system_stm32f4xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/USB_DEVICE" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/STM32F4_study/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/CMSIS/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32f4xx.cyclo ./Drivers/CMSIS/system_stm32f4xx.d ./Drivers/CMSIS/system_stm32f4xx.o ./Drivers/CMSIS/system_stm32f4xx.su

.PHONY: clean-Drivers-2f-CMSIS

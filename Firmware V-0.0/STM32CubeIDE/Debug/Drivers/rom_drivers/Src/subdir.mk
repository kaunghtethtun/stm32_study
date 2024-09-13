################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.c 

OBJS += \
./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.o 

C_DEPS += \
./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/rom_drivers/Src/%.o Drivers/rom_drivers/Src/%.su Drivers/rom_drivers/Src/%.cyclo: ../Drivers/rom_drivers/Src/%.c Drivers/rom_drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/USB_DEVICE" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/STM32F4_study/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-rom_drivers-2f-Src

clean-Drivers-2f-rom_drivers-2f-Src:
	-$(RM) ./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.cyclo ./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.d ./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.o ./Drivers/rom_drivers/Src/ROM_LSDB4830_CAFC.su

.PHONY: clean-Drivers-2f-rom_drivers-2f-Src


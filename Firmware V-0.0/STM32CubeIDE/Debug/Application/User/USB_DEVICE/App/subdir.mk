################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usb_device.c \
C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usbd_cdc_if.c \
C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usbd_desc.c 

OBJS += \
./Application/User/USB_DEVICE/App/usb_device.o \
./Application/User/USB_DEVICE/App/usbd_cdc_if.o \
./Application/User/USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./Application/User/USB_DEVICE/App/usb_device.d \
./Application/User/USB_DEVICE/App/usbd_cdc_if.d \
./Application/User/USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USB_DEVICE/App/usb_device.o: C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usb_device.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/USB_DEVICE" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/STM32F4_study/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/USB_DEVICE/App/usb_device.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/USB_DEVICE/App/usbd_cdc_if.o: C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usbd_cdc_if.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/USB_DEVICE" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/STM32F4_study/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/USB_DEVICE/App/usbd_cdc_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/USB_DEVICE/App/usbd_desc.o: C:/Users/Kaung\ Htet\ Htun/OneDrive/Desktop/STM32F4_study/Firmware\ V-0.0/USB_DEVICE/App/usbd_desc.c Application/User/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../../Core/Inc -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/USB_DEVICE" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/Desktop/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/HAL/Firmware V-0.0/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Kaung Htet Htun/OneDrive/Desktop/STM32F4_study/Firmware V-0.0/STM32CubeIDE/Drivers/rom_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/USB_DEVICE/App/usbd_desc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USB_DEVICE-2f-App

clean-Application-2f-User-2f-USB_DEVICE-2f-App:
	-$(RM) ./Application/User/USB_DEVICE/App/usb_device.cyclo ./Application/User/USB_DEVICE/App/usb_device.d ./Application/User/USB_DEVICE/App/usb_device.o ./Application/User/USB_DEVICE/App/usb_device.su ./Application/User/USB_DEVICE/App/usbd_cdc_if.cyclo ./Application/User/USB_DEVICE/App/usbd_cdc_if.d ./Application/User/USB_DEVICE/App/usbd_cdc_if.o ./Application/User/USB_DEVICE/App/usbd_cdc_if.su ./Application/User/USB_DEVICE/App/usbd_desc.cyclo ./Application/User/USB_DEVICE/App/usbd_desc.d ./Application/User/USB_DEVICE/App/usbd_desc.o ./Application/User/USB_DEVICE/App/usbd_desc.su

.PHONY: clean-Application-2f-User-2f-USB_DEVICE-2f-App


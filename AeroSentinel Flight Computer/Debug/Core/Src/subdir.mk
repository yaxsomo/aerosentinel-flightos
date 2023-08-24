################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BlackBox.c \
../Core/Src/Compass.c \
../Core/Src/Control_Center.c \
../Core/Src/IMU.c \
../Core/Src/KalmanQuaternions.c \
../Core/Src/Pressure.c \
../Core/Src/Pyro.c \
../Core/Src/RCFilter.c \
../Core/Src/Temperature.c \
../Core/Src/e220.c \
../Core/Src/fatfs_sd.c \
../Core/Src/lsm6ds3tr-c_reg.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/BlackBox.o \
./Core/Src/Compass.o \
./Core/Src/Control_Center.o \
./Core/Src/IMU.o \
./Core/Src/KalmanQuaternions.o \
./Core/Src/Pressure.o \
./Core/Src/Pyro.o \
./Core/Src/RCFilter.o \
./Core/Src/Temperature.o \
./Core/Src/e220.o \
./Core/Src/fatfs_sd.o \
./Core/Src/lsm6ds3tr-c_reg.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/BlackBox.d \
./Core/Src/Compass.d \
./Core/Src/Control_Center.d \
./Core/Src/IMU.d \
./Core/Src/KalmanQuaternions.d \
./Core/Src/Pressure.d \
./Core/Src/Pyro.d \
./Core/Src/RCFilter.d \
./Core/Src/Temperature.d \
./Core/Src/e220.d \
./Core/Src/fatfs_sd.d \
./Core/Src/lsm6ds3tr-c_reg.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/DSP/Include -I../Middlewares/ST/STM32_MotionFX_Library/Inc -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BlackBox.cyclo ./Core/Src/BlackBox.d ./Core/Src/BlackBox.o ./Core/Src/BlackBox.su ./Core/Src/Compass.cyclo ./Core/Src/Compass.d ./Core/Src/Compass.o ./Core/Src/Compass.su ./Core/Src/Control_Center.cyclo ./Core/Src/Control_Center.d ./Core/Src/Control_Center.o ./Core/Src/Control_Center.su ./Core/Src/IMU.cyclo ./Core/Src/IMU.d ./Core/Src/IMU.o ./Core/Src/IMU.su ./Core/Src/KalmanQuaternions.cyclo ./Core/Src/KalmanQuaternions.d ./Core/Src/KalmanQuaternions.o ./Core/Src/KalmanQuaternions.su ./Core/Src/Pressure.cyclo ./Core/Src/Pressure.d ./Core/Src/Pressure.o ./Core/Src/Pressure.su ./Core/Src/Pyro.cyclo ./Core/Src/Pyro.d ./Core/Src/Pyro.o ./Core/Src/Pyro.su ./Core/Src/RCFilter.cyclo ./Core/Src/RCFilter.d ./Core/Src/RCFilter.o ./Core/Src/RCFilter.su ./Core/Src/Temperature.cyclo ./Core/Src/Temperature.d ./Core/Src/Temperature.o ./Core/Src/Temperature.su ./Core/Src/e220.cyclo ./Core/Src/e220.d ./Core/Src/e220.o ./Core/Src/e220.su ./Core/Src/fatfs_sd.cyclo ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/lsm6ds3tr-c_reg.cyclo ./Core/Src/lsm6ds3tr-c_reg.d ./Core/Src/lsm6ds3tr-c_reg.o ./Core/Src/lsm6ds3tr-c_reg.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src


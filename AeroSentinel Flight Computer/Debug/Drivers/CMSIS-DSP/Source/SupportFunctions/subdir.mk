################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.c \
../Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.c 

OBJS += \
./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.o \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.o 

C_DEPS += \
./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.d \
./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-DSP/Source/SupportFunctions/%.o Drivers/CMSIS-DSP/Source/SupportFunctions/%.su Drivers/CMSIS-DSP/Source/SupportFunctions/%.cyclo: ../Drivers/CMSIS-DSP/Source/SupportFunctions/%.c Drivers/CMSIS-DSP/Source/SupportFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS-DSP -I../Drivers/CMSIS-DSP/Include -I../Drivers/CMSIS-DSP/Include/dsp -I../Drivers/CMSIS-DSP/PrivateInclude -I../Drivers/CMSIS-DSP/Source -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2d-DSP-2f-Source-2f-SupportFunctions

clean-Drivers-2f-CMSIS-2d-DSP-2f-Source-2f-SupportFunctions:
	-$(RM) ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctions.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/SupportFunctionsF16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_barycenter_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bitonic_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_bubble_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_copy_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_float.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f16_to_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_float.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_f64_to_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.o
	-$(RM) ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_fill_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_float_to_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_heap_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_insertion_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_merge_sort_init_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_float.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q15_to_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_float.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q31_to_q7.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_f64.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_float.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q15.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.cyclo
	-$(RM) ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_q7_to_q31.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_quick_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_selection_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_sort_init_f32.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f16.su ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.cyclo ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.d ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.o ./Drivers/CMSIS-DSP/Source/SupportFunctions/arm_weighted_sum_f32.su

.PHONY: clean-Drivers-2f-CMSIS-2d-DSP-2f-Source-2f-SupportFunctions


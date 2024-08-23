################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/hal/src/hal.c 

C_DEPS += \
./source/hal/src/hal.d 

OBJS += \
./source/hal/src/hal.o 


# Each subdirectory must supply rules for building sources it contributes
source/hal/src/%.o: ../source/hal/src/%.c source/hal/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\source" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\source\app" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\source\driver" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\source\hal" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\device" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\CMSIS_Ass2\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-hal-2f-src

clean-source-2f-hal-2f-src:
	-$(RM) ./source/hal/src/hal.d ./source/hal/src/hal.o

.PHONY: clean-source-2f-hal-2f-src


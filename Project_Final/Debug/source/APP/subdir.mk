################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/APP/MAIN_APP.c 

C_DEPS += \
./source/APP/MAIN_APP.d 

OBJS += \
./source/APP/MAIN_APP.o 


# Each subdirectory must supply rules for building sources it contributes
source/APP/%.o: ../source/APP/%.c source/APP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\APP" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\DRIVER" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\HAL" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\device" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-APP

clean-source-2f-APP:
	-$(RM) ./source/APP/MAIN_APP.d ./source/APP/MAIN_APP.o

.PHONY: clean-source-2f-APP


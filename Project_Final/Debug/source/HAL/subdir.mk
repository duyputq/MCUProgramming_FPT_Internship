################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/HAL/HAL_FLASH.c \
../source/HAL/HAL_QUEUE.c \
../source/HAL/HAL_SREC.c \
../source/HAL/HAL_UART.c 

C_DEPS += \
./source/HAL/HAL_FLASH.d \
./source/HAL/HAL_QUEUE.d \
./source/HAL/HAL_SREC.d \
./source/HAL/HAL_UART.d 

OBJS += \
./source/HAL/HAL_FLASH.o \
./source/HAL/HAL_QUEUE.o \
./source/HAL/HAL_SREC.o \
./source/HAL/HAL_UART.o 


# Each subdirectory must supply rules for building sources it contributes
source/HAL/%.o: ../source/HAL/%.c source/HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\APP" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\DRIVER" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\source\HAL" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\device" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Project_Final\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-HAL

clean-source-2f-HAL:
	-$(RM) ./source/HAL/HAL_FLASH.d ./source/HAL/HAL_FLASH.o ./source/HAL/HAL_QUEUE.d ./source/HAL/HAL_QUEUE.o ./source/HAL/HAL_SREC.d ./source/HAL/HAL_SREC.o ./source/HAL/HAL_UART.d ./source/HAL/HAL_UART.o

.PHONY: clean-source-2f-HAL


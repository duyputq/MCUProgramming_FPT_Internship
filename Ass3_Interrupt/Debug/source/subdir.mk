################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Ass3_Interrupt.c \
../source/func.c \
../source/main.c \
../source/mtb.c 

C_DEPS += \
./source/Ass3_Interrupt.d \
./source/func.d \
./source/main.d \
./source/mtb.d 

OBJS += \
./source/Ass3_Interrupt.o \
./source/func.o \
./source/main.o \
./source/mtb.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Ass3_Interrupt\source" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Ass3_Interrupt\device" -I"C:\Users\Duy\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Ass3_Interrupt\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Ass3_Interrupt.d ./source/Ass3_Interrupt.o ./source/func.d ./source/func.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o

.PHONY: clean-source


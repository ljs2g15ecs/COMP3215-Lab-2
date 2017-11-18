################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SLIP.c \
../source/mtb.c 

OBJS += \
./source/SLIP.o \
./source/mtb.o 

C_DEPS += \
./source/SLIP.d \
./source/mtb.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCPU_MKW41Z512VHT4 -DCPU_MKW41Z512VHT4_cm0plus -D__REDLIB__ -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\source" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\utilities" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\drivers" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\startup" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\frdmkw41z" -I"C:\Users\lewis\Documents\Part III\COMP3215\COMP3215-Lab-2\SLIP\CMSIS" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Data_Manipulation.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.c 

OBJS += \
./Stm32_F103C6_Drivers/Data_Manipulation.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Data_Manipulation.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/%.o Stm32_F103C6_Drivers/%.su Stm32_F103C6_Drivers/%.cyclo: ../Stm32_F103C6_Drivers/%.c Stm32_F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"E:/Courses_Trainings/Embedded_Diploma/Assingments/Unit_6_Microcontroller_Architectures/lesson 3/Drivers/HAL/inc" -I"E:/Courses_Trainings/Embedded_Diploma/Assingments/Unit_6_Microcontroller_Architectures/lesson 3/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers

clean-Stm32_F103C6_Drivers:
	-$(RM) ./Stm32_F103C6_Drivers/Data_Manipulation.cyclo ./Stm32_F103C6_Drivers/Data_Manipulation.d ./Stm32_F103C6_Drivers/Data_Manipulation.o ./Stm32_F103C6_Drivers/Data_Manipulation.su ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.cyclo ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.d ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.o ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_Driver.su ./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.cyclo ./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.d ./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.o ./Stm32_F103C6_Drivers/Stm32_F103C6_GPIO_Driver.su

.PHONY: clean-Stm32_F103C6_Drivers


/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
void clock_init()
{
	RCC_GPIOA_CLK_EN();
}
void GPIO_Init(){
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, PinConfig);
}
int main(void)
{
	clock_init();
	GPIO_Init();
    /* Loop forever */
	while(1){
	MCAL_GPIO_Write_PIN(GPIOA, GPIO_PIN_0, GPIO_PIN_LOW);
	for(int i=0;i<0xFFFF;i++);
	MCAL_GPIO_Write_PIN(GPIOA, GPIO_PIN_0, GPIO_PIN_HIGH);
	for(int i=0;i<0xFFFF;i++);
	}
}
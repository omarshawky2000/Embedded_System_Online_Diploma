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
#include "Stm32_F103C6_EXTI_Driver.h"
#include "lcd.h"
#include "keypad.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

 uint32_t IRQ_Flag = 0 ;
 void ISR_CALLBACK(void);

 void wait_ms(uint32_t time)
 {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++)
			;
 }
 int main(void)
 {
	//Enable Clock();
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	LCD_INIT();
	LCD_clear_screen();

	EXTI_Config_t EXTI_CFG ;
	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Trigger_Case = EXTI_Trigger_RisingEdge ;
	EXTI_CFG.P_IRQ_CALLBACK = ISR_CALLBACK ;
	EXTI_CFG.IRQ_EN = EXTI_ENABLE ;

	MCAL_EXTI_GPIO_Init(&EXTI_CFG);

	/*Loop Forever*/
	while (1)
		{
			if(IRQ_Flag)
			{
				LCD_clear_screen();
				IRQ_Flag = 0 ;
			}
		}

 }
 void ISR_CALLBACK(void)
 {
	 IRQ_Flag = 1 ;
	 LCD_WRITE_STRING("IRQ EXTI9 has happened _|-");
	 wait_ms(1000);
 }

/*
 * stm32f103x8.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include "stdlib.h"
#include "stdint.h"
#include "Data_Manipulation.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_BASE 									0x08000000UL
#define SYSTEM_Memory_BASE 									0x1FFFF000UL
#define SRAM_Memory_BASE 									0x20000000UL

#define Peripherals_BASE 									0x40000000UL

#define CORTEX_M3_Internal_Peripherals_BASE 				0xE0000000UL

//-----------------------------
//Base addresses for AHB CORTEX_M3_Internal_Peripherals_BASE
//-----------------------------
//*****NVIC Peripheral*****
//----------------------------
#define NVIC_BASE 											(CORTEX_M3_Internal_Peripherals_BASE+ 0x0000E100UL)
#define NVIC_ISER0 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000000UL)
#define NVIC_ISER1 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000004UL)
#define NVIC_ISER2 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000008UL)
#define NVIC_ICER0 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000080UL)
#define NVIC_ICER1 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000084UL)
#define NVIC_ICER2 										   *(volatile uint32_t*)(NVIC_BASE+ 0x00000088UL)


//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

//*****RCC Peripheral*****
//----------------------------
#define RCC_BASE 											(Peripherals_BASE+ 0x00021000UL)

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//*****GPIO Peripheral*****
//----------------------------
//A,B are fully included in the LQFP48 Package
#define GPIOA_BASE 											(Peripherals_BASE+ 0x00010800UL)
#define GPIOB_BASE 											(Peripherals_BASE+ 0x00010C00UL)

//C,D are partially included in the LQFP48 Package
#define GPIOC_BASE 											(Peripherals_BASE+ 0x00011000UL)
#define GPIOD_BASE 											(Peripherals_BASE+ 0x00011400UL)

////E is not included in the LQFP48 Package
#define GPIOE_BASE 											(Peripherals_BASE+ 0x00011800UL)

//*****EXTI Peripheral*****
//----------------------------
#define EXTI_BASE 											(Peripherals_BASE+ 0x00010400UL)

//*****AFIO Peripheral*****
//----------------------------
#define AFIO_BASE 											(Peripherals_BASE+ 0x00010000UL)

//*****USART Peripheral*****
//----------------------------
#define USART1_BASE 										(Peripherals_BASE+ 0x00013800UL)


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

//*****USART Peripheral*****
//----------------------------
#define USART2_BASE 										(Peripherals_BASE+ 0x00004400UL)

#define USART3_BASE 										(Peripherals_BASE+ 0x00004800UL)

//=============================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref:Peripheral register:GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref:Peripheral register:RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref:Peripheral register:EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*


typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref:Peripheral register:AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	 uint32_t RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref:Peripheral register:USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}USART_TypeDef;

//=============================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//@ref:Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#define GPIOA													((GPIO_TypeDef*)	GPIOA_BASE)
#define GPIOB													((GPIO_TypeDef*)	GPIOB_BASE)
#define GPIOC													((GPIO_TypeDef*)	GPIOC_BASE)
#define GPIOD													((GPIO_TypeDef*)	GPIOD_BASE)
#define GPIOE													((GPIO_TypeDef*)	GPIOE_BASE)

#define RCC														((RCC_TypeDef*)		RCC_BASE)

#define EXTI													((EXTI_TypeDef*)	EXTI_BASE)

#define AFIO													((AFIO_TypeDef*)	AFIO_BASE)

#define USART1													((USART_TypeDef*)	USART1_BASE)
#define USART2													((USART_TypeDef*)	USART2_BASE)
#define USART3													((USART_TypeDef*)	USART3_BASE)

//=============================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//@ref:RCC clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#define RCC_GPIOA_CLK_EN()										(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()										(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()										(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()										(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()										(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()										(RCC->APB2ENR |= 1<<0)

#define RCC_USART1_CLK_EN()										(RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN()										(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN()										(RCC->APB1ENR |= 1<<18)

//ECC Reset mechanism
#define RCC_USART1_CLK_DIS()									(RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_CLK_DIS()									(RCC->APB1RSTR |= 1<<17)
#define RCC_USART3_CLK_DIS()									(RCC->APB1RSTR |= 1<<18)

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//@ref:NVIC clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#define NVIC_IRQ6_EXTI0_EN()									(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_EN()									(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_EN()									(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_EN()									(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_EN()									(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_EN()									(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ37_USART1_EN()									(NVIC_ISER1 |= 1<<5)  //37-32
#define NVIC_IRQ38_USART2_EN()									(NVIC_ISER1 |= 1<<6)  //38-32
#define NVIC_IRQ39_USART3_EN()									(NVIC_ISER1 |= 1<<7)  //39-32
#define NVIC_IRQ40_EXTI10_15_EN()								(NVIC_ISER1 |= 1<<8)  //40-32

#define NVIC_IRQ6_EXTI0_DIS()									(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_DIS()									(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_DIS()									(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_DIS()									(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_DIS()									(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DIS()								(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ37_USART1_DIS()									(NVIC_ICER1 |= 1<<5)  //37-32
#define NVIC_IRQ38_USART2_DIS()									(NVIC_ICER1 |= 1<<6)  //38-32
#define NVIC_IRQ39_USART3_DIS()									(NVIC_ICER1 |= 1<<7)  //39-32
#define NVIC_IRQ40_EXTI10_15_DIS()								(NVIC_ICER1 |= 1<<8)  //40-32

//=============================================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103X6_H_ */

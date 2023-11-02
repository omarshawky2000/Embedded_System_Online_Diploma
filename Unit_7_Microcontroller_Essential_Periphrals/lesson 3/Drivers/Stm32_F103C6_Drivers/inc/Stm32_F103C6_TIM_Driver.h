/*
 * Stm32_F103C6_EXTI_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32_F103C6_EXTI_DRIVER_H_
#define INC_STM32_F103C6_EXTI_DRIVER_H_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"

//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------


// TIMER Configuration structure
typedef struct
{
	uint8_t					BASIC_MODE;				// Specifies the timer Mode
													// @ref: BASIC_TIM_MODE_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					GP_MODE;				// Specifies the timer Mode
													// @ref: GP_TIM_MODE_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					GP_CLK;					// Specifies the selected clock for the timer
													// @ref: GP_CLK_define found in "Stm32_F103C6_TIM_Driver.h"

	uint16_t 				RELOAD_VAL;				// Specifies the reload value of the timer

	uint16_t 				PRESCALAR;				// Specifies the prescalar

	uint8_t 				INT_MODE;				// Specifies if the interrupt should be enabled or disabled.
													// Will the mask in EXTI and NVIC
													// @ref: TIM_INT_MODE_define found in "Stm32_F103C6_TIM_Driver.h"

	void			(*P_TIMx_INT_CALLBACK)(void);	// Set the C Functions that will be called in the ISR

}TIM_Config_t;


// TIMER initialization status structure
typedef struct
{
	uint8_t					TIM1_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM2_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM3_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM4_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM5_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM6_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM7_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

	uint8_t					TIM8_INIT_STATUS;		// Specifies if the TIMx is initialized by it corresponding function
													// @ref: TIM_INIT_STATUS_define found in "Stm32_F103C6_TIM_Driver.h"

}TIM_INIT_STATUS_t;


//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------

//@ref BASIC_TIM_MODE_define
#define BASIC_TIM_MODE_AUTORELOAD		0U						//The timer autoreload the value at overflow
#define BASIC_TIM_MODE_ONEPULSE			1U						//The timer is set to one pulse mode

//ref GP_TIM_MODE_define

//@ref: GP_CLK_define
#define GP_TIM_CLK_INT					0U						//The internal clock is selected
#define GP_TIM_CLK_EXCLK1				1U						//The External clock mode 1: external input pin (TIx) is selected
#define GP_TIM_CLK_EXCLK2				2U						//The External clock mode 2: external trigger input (ETR) is selected
#define GP_TIM_CLK_INTTRG_INP			3U						//The Internal Trigger input (ITRx) using one timer as a prescaler for another.


//@ref TIM_IRQ_define
#define TIM1_BRK_IRQ					24U						//TIM1 Break interrupt
#define TIM1_UP_IRQ						25U						//TIM1 Update interrupt
#define TIM1_TRG_COM_IRQ				26U						//TIM1 Trigger and Commutation interrupt
#define TIM1_CC_IRQ						27U						//TIM1 Capture Compare interrupt
#define TIM2_IRQ						28U						//TIM2 global interrupt
#define TIM3_IRQ						29U						//TIM3 global interrupt
#define TIM4_IRQ						30U						//TIM4 global interrupt
#define TIM5_IRQ						50U						//TIM5 global interrupt
#define TIM6_IRQ						54U						//TIM6 global interrupt
#define TIM7_IRQ						55U						//TIM7 global interrupt
#define TIM8_BRK_IRQ					43U						//TIM8 Break interrupt
#define TIM8_UP_IRQ						44U						//TIM8 Update interrupt
#define TIM8_TRG_COM_IRQ				45U						//TIM8 Trigger and Commutation interrupt
#define TIM8_CC_IRQ						46U						//TIM8 Capture Compare interrupt



// @ref: TIM_INT_MODE_define
#define TIM_INT_DISABLE					0U				//Disable the TIM IRQ
#define TIM_INT_ENABLE					1U				//Enable the TIM IRQ

//@ref: TIM_INIT_STATUS_define
#define TIM_NOT_INITIALIZED				0U				//TIMx is not initialized yet
#define TIM_INITIALIZED					1U				//TIMx has been initialized

/*=
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void MCAL_BASIC_TIMx_Init(BASIC_TIM6_TIM7_TypeDef* TIMx ,TIM_Config_t* TIMConfig );

void MCAL_GP_TIMx_Init(GP_TIM2_5_TypeDef* TIMx ,TIM_Config_t* TIMConfig );


void MCAL_BASIC_TIMx_Deinit(BASIC_TIM6_TIM7_TypeDef* TIMx);

void MCAL_GP_TIMx_Deinit(GP_TIM2_5_TypeDef* TIMx);


void MCAL_BASIC_TIMx_Start(BASIC_TIM6_TIM7_TypeDef* TIMx);

void MCAL_GP_TIMx_Start(GP_TIM2_5_TypeDef* TIMx);


void MCAL_BASIC_TIMx_Stop(BASIC_TIM6_TIM7_TypeDef* TIMx);

void MCAL_GP_TIMx_Stop(GP_TIM2_5_TypeDef* TIMx);


void MCAL_BASIC_TIMER_Delay_ms(BASIC_TIM6_TIM7_TypeDef* TIMx , uint16_t Delay_ms);

void MCAL_GP_TIMER_Delay_ms(GP_TIM2_5_TypeDef* TIMx ,uint16_t Delay_ms);

void MCAL_GP_TIMER_Delay_us(GP_TIM2_5_TypeDef* TIMx ,uint16_t Delay_us);




#endif /* INC_STM32_F103C6_EXTI_DRIVER_H_ */

/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_TIM_Driver.h"

 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================
 void _ISR_FLAG_TOGGLE 	(void);

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 void			(*GPfn_TIMx_INT_CALLBACK[15])(void);
 TIM_INIT_STATUS_t 		_TIMERS_STATUS;
 uint8_t		 		_FLAG = 1;
 //========================================================================
 //								PRIVATE MACROS
 //========================================================================
 #define Enable_RCC_TIMx(x)	(		((uint32_t)x==(uint32_t)TIM1)	?RCC_TIM1_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM2)	?RCC_TIM2_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM3)	?RCC_TIM3_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM4)	?RCC_TIM4_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM5)	?RCC_TIM5_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM6)	?RCC_TIM6_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM7)	?RCC_TIM7_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM8)	?RCC_TIM8_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM9)	?RCC_TIM9_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM10)	?RCC_TIM10_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM11)	?RCC_TIM11_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM12)	?RCC_TIM12_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM13)	?RCC_TIM13_CLK_EN():\
									((uint32_t)x==(uint32_t)TIM14)	?RCC_TIM14_CLK_EN():0	 )


 #define GET_BASIC_TIMx_IDX(x)	(	((uint32_t)x==(uint32_t)TIM6)	?5:\
									((uint32_t)x==(uint32_t)TIM7)	?6:16	 )

 #define GET_GP_TIMx_IDX(x)		(	((uint32_t)x==(uint32_t)TIM2)	?1:\
									((uint32_t)x==(uint32_t)TIM3)	?2:\
									((uint32_t)x==(uint32_t)TIM4)	?3:\
									((uint32_t)x==(uint32_t)TIM5)	?4:16	 )


 //========================================================================
 //								       APIs
 //========================================================================

/* ================================================================
 * @Fn				-MCAL_BASIC_TIMx_Init
 *
 * @brief 			-Initializes the TIM(x) where x is the number of TIM
 *
 * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_BASIC_TIMx_Init(BASIC_TIM6_TIM7_TypeDef* TIMx ,TIM_Config_t* TIMConfig )
 {
	 //Note the RCC is configured on 8 MHz by default unless PLL is used
	 //The following implementation depend on default 8 MHz frequency using PLL should change the calculations
	 if((uint32_t)TIMx==(uint32_t)TIM6||(uint32_t)TIMx==(uint32_t)TIM7)
	 {
	 Enable_RCC_TIMx(TIMx);
	 //Get the Index to correctly set the IRQ Handler to the CallBack function set by the use
	 uint8_t BASIC_TIMx_IDX = GET_BASIC_TIMx_IDX(TIMx);

	 //Check if the mode is One pulse or Auto reload
	 switch(TIMConfig->BASIC_MODE)
	 {
	 	 case BASIC_TIM_MODE_AUTORELOAD:
	 		 SetBit(TIMx->CR1,7);
	 		 break;

	 	 case BASIC_TIM_MODE_ONEPULSE:
	 		 ClearBit(TIMx->CR1,7);
	 		 break;
	 	 default:
	 		 break;
	 }

	 //Set the Prescaler
	 TIMx->PSC = TIMConfig->PRESCALAR;

	 //Set the AutoReload
	 TIMx->ARR = TIMConfig->RELOAD_VAL;

	 //Enable or disable the interrupt of the Timer from NVIC and TIMx
	 switch(TIMConfig->INT_MODE)
	 {
	 	 case TIM_INT_DISABLE:
	 		 if((uint32_t)TIMx==(uint32_t)TIM6) NVIC_IRQ54_TIM6_DIS();
	 		 else NVIC_IRQ55_TIM7_DIS();
	 		 ClearBit(TIMx->DIER,0);
	 		 break;

	 	 case TIM_INT_ENABLE:
	 		 if((uint32_t)TIMx==(uint32_t)TIM6) NVIC_IRQ54_TIM6_EN();
	 		 else NVIC_IRQ55_TIM7_EN();
	 		 SetBit(TIMx->DIER,0);
	 		 break;

	 	 default:
	 		 break;
	 }

	 //Set the Callback to the handler
	 GPfn_TIMx_INT_CALLBACK[BASIC_TIMx_IDX] = TIMConfig->P_TIMx_INT_CALLBACK;

	 //Set the Init status of TIMx as initialized
	 if(TIMx==TIM6)_TIMERS_STATUS.TIM6_INIT_STATUS = TIM_INITIALIZED;
	 else _TIMERS_STATUS.TIM7_INIT_STATUS = TIM_INITIALIZED;

	 //Note this Function doesn't start the Timer it only initialize it
	 //To start the timer use MCAL_BASIC_TIMx_Start

	 }

 }

/* ================================================================
 * @Fn				-MCAL_BASIC_TIMx_Deinit
 *
  * @brief 			-Deinitializes the TIM(x) where x is the number of TIM
  *
  * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
  * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
  *
  * @retval 		-NONE
  *
  * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_BASIC_TIMx_Deinit(BASIC_TIM6_TIM7_TypeDef* TIMx)
 {
	 if(((uint32_t)TIMx==(uint32_t)TIM6)||(uint32_t)TIMx==(uint32_t)TIM7)
	 {
	 TIMx->CR1 	= 0x0000;
	 TIMx->CR2 	= 0x0000;
	 TIMx->DIER = 0x0000;
	 TIMx->SR 	= 0x0000;
	 TIMx->EGR 	= 0x0000;
	 TIMx->CNT 	= 0x0000;
	 TIMx->PSC 	= 0x0000;
	 TIMx->ARR 	= 0xFFFF;

	 //Set the Init status of TIMx as not initialized
	 if(TIMx==TIM6)_TIMERS_STATUS.TIM6_INIT_STATUS = TIM_NOT_INITIALIZED;
	 else _TIMERS_STATUS.TIM7_INIT_STATUS = TIM_NOT_INITIALIZED;
	 }
 }

/* ================================================================
 * @Fn				-MCAL_BASIC_TIMx_Start
 *
 * @brief 			-Starts the timer
 *
 * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_BASIC_TIMx_Start(BASIC_TIM6_TIM7_TypeDef* TIMx)
  {
	  if((uint32_t)TIMx==(uint32_t)TIM6)
	  {
		  if(_TIMERS_STATUS.TIM6_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM7)
	  {
		  if(_TIMERS_STATUS.TIM7_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else;
  }

/* ================================================================
 * @Fn				-MCAL_BASIC_TIMx_Start
 *
 * @brief 			-Stops the timer
 *
 * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_BASIC_TIMx_Stop(BASIC_TIM6_TIM7_TypeDef* TIMx)
  {
 	 if((uint32_t)TIMx==(uint32_t)TIM6)
 	 {
 		 if(_TIMERS_STATUS.TIM6_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
 		 else;
 	 }
 	 else if((uint32_t)TIMx==(uint32_t)TIM7)
 	 {
 		 if(_TIMERS_STATUS.TIM7_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
 		 else;
 	 }
 	 else;
  }

/* =================================================================
 * @FN			- _Update_EXTI
 *
 * @Brief		- Helper Function to update the EXTI
 *
 * @param [in] 	-EXTI_Config : Pointer to structure of the configuration for the EXTI
 * 				 @ref EXTI Configuration structure found in "Stm32_F103C6_EXTI_Driver.h"
 *
 * @retval		- NONE
 *
 * Note-		- NONE
 * =================================================================
 */
 void MCAL_BASIC_TIMER_Delay_ms(BASIC_TIM6_TIM7_TypeDef* TIMx ,uint16_t Delay_ms)
 {
	 TIM_Config_t TIMConfig;
	 TIMConfig.INT_MODE 		= 	TIM_INT_ENABLE;
	 TIMConfig.BASIC_MODE     = 	BASIC_TIM_MODE_ONEPULSE;
	 //Set the prescaler to 8000 so the output timer will tick up 1000 time per second
	 TIMConfig.PRESCALAR 		= 	1000;
	 TIMConfig.RELOAD_VAL 	= 	Delay_ms;
	 TIMConfig.P_TIMx_INT_CALLBACK = _ISR_FLAG_TOGGLE;
	 MCAL_BASIC_TIMx_Init(TIMx, &TIMConfig);
	 MCAL_BASIC_TIMx_Start(TIMx);
	 while(_FLAG);
	 _FLAG	=	1;
	 MCAL_BASIC_TIMx_Deinit(TIMx);
 }

/* ================================================================
 * @Fn				-MCAL_GP_TIMx_Init
 *
 * @brief 			-Initializes the TIM(x) where x is the number of TIM
 *
 * @param [in] 	-TIMx :  where x can be (2 , 3 , 4 , 5 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_GP_TIMx_Init(GP_TIM2_5_TypeDef* TIMx ,TIM_Config_t* TIMConfig )
 {
	 //Note the RCC is configured on 8 MHz by default unless PLL is used
	 //The following implementation depend on default 8 MHz frequency using PLL should change the calculations

	 //Get the Index to correctly set the IRQ Handler to the CallBack function set by the use
	 uint8_t GPTIM_IDX = GET_GP_TIMx_IDX(TIMx);

	 if(GPTIM_IDX > 0 && GPTIM_IDX < 5)
	 {
	 Enable_RCC_TIMx(TIMx);

	 //Check if the mode is One pulse or Auto reload
	 switch(TIMConfig->BASIC_MODE)
	 {
	 	 case BASIC_TIM_MODE_AUTORELOAD:
	 		 SetBit(TIMx->CR1,7);
	 		 break;

	 	 case BASIC_TIM_MODE_ONEPULSE:
	 		 ClearBit(TIMx->CR1,7);
	 		 break;
	 	 default:
	 		 break;
	 }

	 //Set the Prescaler
	 TIMx->PSC = TIMConfig->PRESCALAR;

	 //Set the AutoReload
	 TIMx->ARR = TIMConfig->RELOAD_VAL;

	 //Enable or disable the interrupt of the Timer from NVIC and TIMx
	 switch(TIMConfig->INT_MODE)
	 {
	 	 case TIM_INT_DISABLE:
	 		 if((uint32_t)TIMx==(uint32_t)TIM2)		 NVIC_IRQ28_TIM2_DIS();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM3) NVIC_IRQ29_TIM3_DIS();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM4) NVIC_IRQ30_TIM4_DIS();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM5) NVIC_IRQ50_TIM5_DIS();
	 		 else;
	 		 ClearBit(TIMx->DIER,0);
	 		 break;

	 	 case TIM_INT_ENABLE:
	 		 if((uint32_t)TIMx==(uint32_t)TIM2)		 NVIC_IRQ28_TIM2_EN();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM3) NVIC_IRQ29_TIM3_EN();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM4) NVIC_IRQ30_TIM4_EN();
	 		 else if((uint32_t)TIMx==(uint32_t)TIM5) NVIC_IRQ50_TIM5_EN();
	 		 else;
	 		 SetBit(TIMx->DIER,0);
	 		 break;

	 	 default:
	 		 break;
	 }

	 //Set the Callback to the handler
	 GPfn_TIMx_INT_CALLBACK[GPTIM_IDX] = TIMConfig->P_TIMx_INT_CALLBACK;

	 //Set the Init status of TIMx as initialized
	if		((uint32_t)TIMx==(uint32_t)TIM2)_TIMERS_STATUS.TIM2_INIT_STATUS = TIM_INITIALIZED;
	else if((uint32_t)TIMx==(uint32_t)TIM3) _TIMERS_STATUS.TIM3_INIT_STATUS = TIM_INITIALIZED;
	else if((uint32_t)TIMx==(uint32_t)TIM4) _TIMERS_STATUS.TIM4_INIT_STATUS = TIM_INITIALIZED;
	else if((uint32_t)TIMx==(uint32_t)TIM5) _TIMERS_STATUS.TIM5_INIT_STATUS = TIM_INITIALIZED;
	else;

	 //Note this Function doesn't start the Timer it only initialize it
	 //To start the timer use MCAL_BASIC_TIMx_Start

	 }

 }

/* ================================================================
 * @Fn				-MCAL_GP_TIMx_Deinit
 *
 * @brief 		-Deinitializes the TIM(x) where x is the number of TIM
 *
 * @param [in] 	-TIMx :  where x can be (2 , 3 , 4 , 5 depending on device used) to select the TIM peripheral
 * 				 @ref TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_GP_TIMx_Deinit(GP_TIM2_5_TypeDef* TIMx)
  {
	 //Get the Index to correctly set the IRQ Handler to the CallBack function set by the use
	 uint8_t GPTIM_IDX = GET_GP_TIMx_IDX(TIMx);

	 if(GPTIM_IDX > 0 && GPTIM_IDX < 5)
	 {
 	 TIMx->CR1 	= 0x0000;
 	 TIMx->CR2 	= 0x0000;
 	 TIMx->DIER = 0x0000;
 	 TIMx->SR 	= 0x0000;
 	 TIMx->EGR 	= 0x0000;
 	 TIMx->CNT 	= 0x0000;
 	 TIMx->PSC 	= 0x0000;
 	 TIMx->ARR 	= 0xFFFF;

	 //Set the Init status of TIMx as not initialized
 	 if		((uint32_t)TIMx==(uint32_t)TIM2)_TIMERS_STATUS.TIM2_INIT_STATUS  = TIM_NOT_INITIALIZED;
 	 else if((uint32_t)TIMx==(uint32_t)TIM3) _TIMERS_STATUS.TIM3_INIT_STATUS = TIM_NOT_INITIALIZED;
 	 else if((uint32_t)TIMx==(uint32_t)TIM4) _TIMERS_STATUS.TIM4_INIT_STATUS = TIM_NOT_INITIALIZED;
 	 else if((uint32_t)TIMx==(uint32_t)TIM5) _TIMERS_STATUS.TIM5_INIT_STATUS = TIM_NOT_INITIALIZED;
 	 else;
 	 }
  }

/* ================================================================
 * @Fn				-MCAL_GP_TIMx_Start
 *
 * @brief 			-Starts the timer
 *
 * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_GP_TIMx_Start(GP_TIM2_5_TypeDef* TIMx)
  {
	  if((uint32_t)TIMx==(uint32_t)TIM2)
	  {
		  if(_TIMERS_STATUS.TIM2_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM3)
	  {
		  if(_TIMERS_STATUS.TIM3_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM4)
	  {
		  if(_TIMERS_STATUS.TIM4_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM5)
	  {
		  if(_TIMERS_STATUS.TIM5_INIT_STATUS == TIM_INITIALIZED)SetBit(TIMx->CR1,0); //Set the Enable Bit
		  else;
	  }
	  else;
  }

/* ================================================================
 * @Fn			-MCAL_GP_TIMx_Stop
 *
 * @brief 		-Stops the timer
 *
 * @param [in] 	-TIMx :  where x can be (6 or 7 depending on device used) to select the TIM peripheral
 * 				 @ref BASIC TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @retval 		-NONE
 *
 * Note			-STM32F103C6 MCU only has TIM 1,2,3,4,5,6,7,8 Modules
 * =================================================================
 */
 void MCAL_GP_TIMx_Stop(GP_TIM2_5_TypeDef* TIMx)
  {
	  if((uint32_t)TIMx==(uint32_t)TIM2)
	  {
		  if(_TIMERS_STATUS.TIM2_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM3)
	  {
		  if(_TIMERS_STATUS.TIM3_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM4)
	  {
		  if(_TIMERS_STATUS.TIM4_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
		  else;
	  }
	  else if((uint32_t)TIMx==(uint32_t)TIM5)
	  {
		   if(_TIMERS_STATUS.TIM5_INIT_STATUS == TIM_INITIALIZED)ClearBit(TIMx->CR1,0); //Clear the Enable Bit
		   else;
	  }
	  else;
  }

/* =================================================================
 * @FN			- MCAL_GP_TIMER_Delay_ms
 *
 * @Brief		- Delay the program for x milliseconds
 *
 * @param [in] -TIMx :  where x can be (2 through 5) to select the TIM peripheral
 * 			 @ref GP TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @param [in] -Delay_ms :  time to be waited in ms max value is 65535 ms
 *
 * @retval		- NONE
 *
 * Note-		- NONE
 * =================================================================
 */
 void MCAL_GP_TIMER_Delay_ms(GP_TIM2_5_TypeDef* TIMx ,uint16_t Delay_ms)
  {
 	 TIM_Config_t TIMConfig;
 	 TIMConfig.INT_MODE 		= 	TIM_INT_ENABLE;
 	 TIMConfig.BASIC_MODE     = 	BASIC_TIM_MODE_ONEPULSE;
 	 //Set the prescaler to 8000 so the output timer will tick up 1000 time per second
 	 TIMConfig.PRESCALAR 		= 	7999;
 	 TIMConfig.RELOAD_VAL 	    = 	Delay_ms;
 	 TIMConfig.P_TIMx_INT_CALLBACK = _ISR_FLAG_TOGGLE;
 	 MCAL_GP_TIMx_Init(TIMx, &TIMConfig);
 	 MCAL_GP_TIMx_Start(TIMx);
 	 while(_FLAG);
 	 _FLAG	=	1;
 	 MCAL_GP_TIMx_Deinit(TIMx);
  }

/* =================================================================
 * @FN		- MCAL_GP_TIMER_Delay_us
 *
 * @Brief		- Delay the program for x microseconds
 *
 * @param [in] -TIMx :  where x can be (2 through 5) to select the TIM peripheral
 * 			 @ref GP TIMER Configuration structure found in "Stm32_F103C6_TIM_Driver.h"
 *
 * @param [in] -Delay_us :  time to be waited in us max value is 65535 us
 *
 * @retval	- NONE
 *
 * Note-		- NONE
 * =================================================================
 */
 void MCAL_GP_TIMER_Delay_us(GP_TIM2_5_TypeDef* TIMx ,uint16_t Delay_us)
  {
  	TIM_Config_t TIMConfig;
  	TIMConfig.INT_MODE 		= 	TIM_INT_ENABLE;
  	TIMConfig.BASIC_MODE     = 	BASIC_TIM_MODE_ONEPULSE;
  	//Set the prescaler to 8 so the output timer will tick up 1,000,0000 time per second
  	TIMConfig.PRESCALAR 		= 	7;
  	TIMConfig.RELOAD_VAL 	    = 	Delay_us;
  	TIMConfig.P_TIMx_INT_CALLBACK = _ISR_FLAG_TOGGLE;
  	MCAL_GP_TIMx_Init(TIMx, &TIMConfig);
  	MCAL_GP_TIMx_Start(TIMx);
  	while(_FLAG);
  	_FLAG	=	1;
  	MCAL_GP_TIMx_Deinit(TIMx);
  }

/* =================================================================
 * @FN			- _ISR_FLAG_TOGGLE
 *
 * @Brief		- Helper Function to change the flag to zero at interrupt
 *
 * @param [in] - NONE
 *
 * @retval		- NONE
 *
 * Note-		- NONE
 * =================================================================
 */
 void _ISR_FLAG_TOGGLE(void)
  {
	  _FLAG = 0;
  }

 //========================================================================
 //								ISR Functions
 //========================================================================
 void TIM2_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM2->SR,0);
	 GPfn_TIMx_INT_CALLBACK[1]();
 }

 void TIM3_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM3->SR,0);
	 GPfn_TIMx_INT_CALLBACK[2]();

 }

 void TIM4_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM4->SR,0);
	 GPfn_TIMx_INT_CALLBACK[3]();
 }

 void TIM5_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM5->SR,0);
	 GPfn_TIMx_INT_CALLBACK[4]();

 }

 void TIM6_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM6->SR,0);
	 GPfn_TIMx_INT_CALLBACK[5]();

 }

 void TIM7_IRQHandler (void)
 {
	 //Clear the update flag
	 ClearBit(TIM7->SR,0);
	 GPfn_TIMx_INT_CALLBACK[6]();

 }



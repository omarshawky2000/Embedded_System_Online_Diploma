/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_GPIO_Driver.h"
 #include "Stm32_F103C6_EXTI_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 void			(*GP_IRQ_CALLBACK[15])(void);

 //========================================================================
 //								PRIVATE MACROS
 //========================================================================
 #define AFIO_GPIO_EXTI_Mapping(x)	(	(x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:0	 )

 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================
 void _Update_EXTI	(EXTI_Config_t* EXTI_Config);
 void _Enable_NVIC	(uint16_t IRQ);
 void _Disable_NVIC	(uint16_t IRQ);

 //========================================================================
 //								       APIs
 //========================================================================
 /* ================================================================
  * @Fn				-MCAL_EXTI_GPIO_Init
  *
  * @brief 			-Initializes the EXTI(N) where N is the number of EXTI
  *
  * @param [in] 	-EXTI_Config : Pointer to structure of the configuration for the EXTI
  * 				 @ref EXTI Configuration structure found in "Stm32_F103C6_EXTI_Driver.h"
  *
  * @retval 		-NONE
  *
  * Note			-STM32F103C6 MCU has GPIO A , B , C , D , E Modules
  * 				but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
  * 				-Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
  * =================================================================
  */
 void MCAL_EXTI_GPIO_Init(EXTI_Config_t* EXTI_Config)
 {
	_Update_EXTI(EXTI_Config);
 }

/* ================================================================
 * @Fn				-MCAL_EXTI_GPIO_Denit
 *
 * @brief 			-Deinitialize the EXTI Peripheral
 *
 * @param [in] 		-NONE
 *
 * @retval 			-NONE
 *
 * Note				-NONE
 * =================================================================
 */
 void MCAL_EXTI_GPIO_Deinit(void)
 {
	EXTI->IMR    = 0x00000000;
	EXTI->EMR    = 0x00000000;
	EXTI->RTSR   = 0x00000000;
	EXTI->FTSR   = 0x00000000;
	EXTI->SWIER  = 0x00000000;
	//Write ones to clear all the pending interrupts
	EXTI->PR	 = 0xFFFFFFFF;
	//Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_DIS();
	NVIC_IRQ7_EXTI1_DIS();
	NVIC_IRQ8_EXTI2_DIS();
	NVIC_IRQ9_EXTI3_DIS();
	NVIC_IRQ10_EXTI4_DIS();
	NVIC_IRQ23_EXTI5_9_DIS();
	NVIC_IRQ40_EXTI10_15_DIS();
 }

/* =================================================================
 * @FN			- MCAL_GPIO_Read_PIN
 * @Brief		- Read GPIOx Pin y and return the value
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 * @param(in)	- PinNumber: the number of pin to read @ref GPIO_PINS_define
 * @retval		- The value of the pin "two values based on @ref GPIO_PIN_state"
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
 void MCAL_EXTI_GPIO_Update(EXTI_Config_t* EXTI_Config)
 {
	_Update_EXTI(EXTI_Config);
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
 void _Update_EXTI(EXTI_Config_t* EXTI_Config)
 {
	//1 - Configure GPIO to be AF Input -> Floating Input
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	PinConfig.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, PinConfig);
	//==============================================================
	//2- UPDATE AFIO to Route between EXTI Line with PORT A,B,C,D
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4 ;

	uint8_t AFIO_EXTICR_Position = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4) ;

	//clear the 4 bits
	ClearHalfByte( AFIO->EXTICR[AFIO_EXTICR_index] , AFIO_EXTICR_Position );
	//Set the Bits corresponding to chosen GPIO port
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)&0xF)\
										                        <<AFIO_EXTICR_Position*4);
	//==============================================================
	//3- Update the Rising/Falling Edge
	//Clear the rising and falling bits
	ClearBit(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	ClearBit(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	switch(EXTI_Config->Trigger_Case)
	{
		case EXTI_Trigger_FallingEdge:
			SetBit(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_RisingEdge:
			SetBit(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_RisingAndFallingEdge:
			SetBit(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			SetBit(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		default:
			break;
	}
	//==============================================================
	//4- Update the function CALLBACK to the ISR
	GP_IRQ_CALLBACK[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CALLBACK;
	//==============================================================
	//5- Enable/Disable the IRQ EXTI & NVIC
	if (EXTI_Config->IRQ_EN == EXTI_ENABLE)
	{
		SetBit(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		_Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else
	{
		ClearBit(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		_Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}


 }

 /* =================================================================
  * @FN			- _Enable_NVIC
  *
  * @Brief		- Helper Function to Enable the NVIC for a certain IRQ
  *
  * @param[in] 	- IRQ : EXTI_IRQ_Number from 0 -> 15
  *
  * @retval		- NONE
  *
  * Note-		- NONE
  * =================================================================
  */
 void _Enable_NVIC	(uint16_t IRQ)
 {
	 switch(IRQ)
	 {
	 	 case 0 :
	 		 NVIC_IRQ6_EXTI0_EN();
	 		 break;

	 	 case 1 :
	 		 NVIC_IRQ7_EXTI1_EN();
	 		 break;

	 	 case 2 :
	 		 NVIC_IRQ8_EXTI2_EN();
	 		 break;

	 	 case 3 :
	 		 NVIC_IRQ9_EXTI3_EN();
	 		 break;

	 	 case 4 :
	 		 NVIC_IRQ10_EXTI4_EN();
	 		 break;

	 	 case 5 :
	 	 case 6 :
	 	 case 7 :
	 	 case 8 :
	 	 case 9 :
	 		 NVIC_IRQ23_EXTI5_9_EN();
	 		 break;

	 	 case 10 :
	 	 case 11 :
	 	 case 12 :
	 	 case 13 :
	 	 case 14 :
	 		 NVIC_IRQ40_EXTI10_15_EN();
	 		 break;

	 	 default:
	 		 break;

	 }
 }

 /* =================================================================
  * @FN			- _Disable_NVIC
  *
  * @Brief		- Helper Function to Enable the NVIC for a certain IRQ
  *
  * @param[in] 	- IRQ : EXTI_IRQ_Number from 0 -> 15
  *
  * @retval		- NONE
  *
  * Note-		- NONE
  * =================================================================
  */
 void _Disable_NVIC	(uint16_t IRQ)
 {
	 switch(IRQ)
	 {
	 	 case 0 :
	 		 NVIC_IRQ6_EXTI0_DIS();
	 		 break;

	 	 case 1 :
	 		 NVIC_IRQ7_EXTI1_DIS();
	 		 break;

	 	 case 2 :
	 		 NVIC_IRQ8_EXTI2_DIS();
	 		 break;

	 	 case 3 :
	 		 NVIC_IRQ9_EXTI3_DIS();
	 		 break;

	 	 case 4 :
	 		 NVIC_IRQ10_EXTI4_DIS();
	 		 break;

	 	 case 5 :
	 	 case 6 :
	 	 case 7 :
	 	 case 8 :
	 	 case 9 :
	 		 NVIC_IRQ23_EXTI5_9_DIS();
	 		 break;

	 	 case 10 :
	 	 case 11 :
	 	 case 12 :
	 	 case 13 :
	 	 case 14 :
	 		 NVIC_IRQ40_EXTI10_15_DIS();
	 		 break;

	 	 default:
	 		 break;

	 }
 }
/* ================================================================= */

 //========================================================================
 //								ISR Functions
 //========================================================================
 void EXTI0_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 SetBit(EXTI->PR,0);
	 GP_IRQ_CALLBACK[0]();

 }

 void EXTI1_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 SetBit(EXTI->PR,1);
	 GP_IRQ_CALLBACK[1]();

 }

 void EXTI2_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 SetBit(EXTI->PR,2);
	 GP_IRQ_CALLBACK[2]();

 }

 void EXTI3_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 SetBit(EXTI->PR,3);
	 GP_IRQ_CALLBACK[3]();

 }

 void EXTI4_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 SetBit(EXTI->PR,4);
	 GP_IRQ_CALLBACK[4]();

 }


 void EXTI9_5_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 if( ReadBit(EXTI->PR,5) )	 	{ SetBit(EXTI->PR,5); GP_IRQ_CALLBACK[5]();}
	 else if( ReadBit(EXTI->PR,6) ) { SetBit(EXTI->PR,6); GP_IRQ_CALLBACK[6]();}
	 else if( ReadBit(EXTI->PR,7) ) { SetBit(EXTI->PR,7); GP_IRQ_CALLBACK[7]();}
	 else if( ReadBit(EXTI->PR,8) ) { SetBit(EXTI->PR,8); GP_IRQ_CALLBACK[8]();}
	 else if( ReadBit(EXTI->PR,9) ) { SetBit(EXTI->PR,9); GP_IRQ_CALLBACK[9]();}

 }

 void EXTI15_10_IRQHandler (void)
 {
	 //Clear Interrupt flag by writing 1
	 if( ReadBit(EXTI->PR,10) )	 	{ SetBit(EXTI->PR,10); GP_IRQ_CALLBACK[10]();}
	 else if( ReadBit(EXTI->PR,11) ) { SetBit(EXTI->PR,11); GP_IRQ_CALLBACK[11]();}
	 else if( ReadBit(EXTI->PR,12) ) { SetBit(EXTI->PR,12); GP_IRQ_CALLBACK[12]();}
	 else if( ReadBit(EXTI->PR,13) ) { SetBit(EXTI->PR,13); GP_IRQ_CALLBACK[13]();}
	 else if( ReadBit(EXTI->PR,14) ) { SetBit(EXTI->PR,14); GP_IRQ_CALLBACK[14]();}

 }


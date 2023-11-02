/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_GPIO_Driver.h"

 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================
 uint8_t _FindPinNum (uint16_t PinNumber);


 /*================================================================
  * @Fn				-MCAL_GPIO_Init
  *
  * @brief 			-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
  *
  * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
  * 				 @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
  *
  * @param [in] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
  *         		 the configuration information for the specified GPIO PIN.
  * 				 @ref GPIO_PinConfig_t define found in "Stm32_F103C6_GPIO_Driver.h"
  *
  * @retval 		-none
  *
  * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
  * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 * =================================================================
 */
 void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx , GPIO_PinConfig_t PinConfig)
 {
 	//Enable the RCC on the GPIO port

 	//Initialize the pin mode
 	uint8_t PINNUM = _FindPinNum(PinConfig.GPIO_PinNumber);
 	//Port Configuration register low GPIOx_CRL -> Configure pin 0 to pin 7
 	if(PinConfig.GPIO_PinNumber< GPIO_PIN_8)
 	{
 		switch(PinConfig.GPIO_MODE)
 		{
 			case GPIO_MODE_ANALOG:
 				(GPIOx->CRL) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRL) &= ~(0XC<<4*PINNUM);   //reset two bits in CNF
 				break;

 			case GPIO_MODE_INPUT_FLO:
 				(GPIOx->CRL) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRL) &= ~(0X8<<4*PINNUM);   //reset 2nd bit in CNF
 				(GPIOx->CRL) |=  (0X4<<4*PINNUM);   //set 1st bit in CNF
 				break;

 			case GPIO_MODE_INPUT_PU:
 				(GPIOx->CRL) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRL) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRL) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				(GPIOx->ODR) |=  PinConfig.GPIO_PinNumber;
 				break;

 			case GPIO_MODE_INPUT_PD:
 				(GPIOx->CRL) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRL) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRL) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				(GPIOx->ODR) &= ~PinConfig.GPIO_PinNumber;
 				break;

 			case GPIO_MODE_OUTPUT_PP:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 				{
 					case GPIO_SPEED_10M:
 						(GPIOx->CRL) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 						(GPIOx->CRL) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 						break;
 					case GPIO_SPEED_2M:
 						(GPIOx->CRL) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 						(GPIOx->CRL) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 						break;
 					case GPIO_SPEED_50M:
 						(GPIOx->CRL) |=  (3<<4*PINNUM);	//set the two bits in MODE
 						break;
 				}
 				(GPIOx->CRL) &= ~(0XC<<4*PINNUM);   //reset two bits in CNF
 				break;

 			case GPIO_MODE_OUTPUT_OD:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 				{
 					case GPIO_SPEED_10M:
 						(GPIOx->CRL) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 						(GPIOx->CRL) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 						break;
 					case GPIO_SPEED_2M:
 						(GPIOx->CRL) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 						(GPIOx->CRL) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 						break;
 					case GPIO_SPEED_50M:
 						(GPIOx->CRL) |=  (3<<4*PINNUM);	//set the two bits in MODE
 						break;
 				}
 				(GPIOx->CRL) &= ~(0X8<<4*PINNUM);   //reset 2nd bits in CNF
 				(GPIOx->CRL) |=  (0X4<<4*PINNUM);   //set 1st bits in CNF
 				break;

 			case GPIO_MODE_OUTPUT_AF_PP:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 					{
 						case GPIO_SPEED_10M:
 							(GPIOx->CRL) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 							(GPIOx->CRL) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 							break;
 						case GPIO_SPEED_2M:
 							(GPIOx->CRL) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 							(GPIOx->CRL) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 							break;
 						case GPIO_SPEED_50M:
 							(GPIOx->CRL) |=  (3<<4*PINNUM);	//set the two bits in MODE
 							break;
 					}
 				(GPIOx->CRL) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRL) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				break;

 			case GPIO_MODE_OUTPUT_AF_OD:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 					{
 						case GPIO_SPEED_10M:
 							(GPIOx->CRL) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 							(GPIOx->CRL) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 							break;
 						case GPIO_SPEED_2M:
 							(GPIOx->CRL) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 							(GPIOx->CRL) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 							break;
 						case GPIO_SPEED_50M:
 							(GPIOx->CRL) |=  (3<<4*PINNUM);	//set the two bits in MODE
 							break;
 					}
 				(GPIOx->CRL) |= (0Xc<<4*PINNUM);   //set two bits in CNF
 				break;

 			case GPIO_MODE_INPUT_AF:
 				(GPIOx->CRL) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRL) &= ~(0X8<<4*PINNUM);   //reset 2nd bit in CNF
 				(GPIOx->CRL) |=  (0X4<<4*PINNUM);   //set 1st bit in CNF
 				break;
 		}
 	}



 	//Port Configuration register high GPIOx_CRH -> Configure pin 8 to pin 15
 	else{
 		PINNUM = PINNUM - 8;
 		switch(PinConfig.GPIO_MODE)
 		{
 			case GPIO_MODE_ANALOG:
 				(GPIOx->CRH) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRH) &= ~(0XC<<4*PINNUM);   //reset two bits in CNF
 				break;

 			case GPIO_MODE_INPUT_FLO:
 				(GPIOx->CRH) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRH) &= ~(0X8<<4*PINNUM);   //reset 2nd bit in CNF
 				(GPIOx->CRH) |=  (0X4<<4*PINNUM);   //set 1st bit in CNF
 				break;

 			case GPIO_MODE_INPUT_PU:
 				(GPIOx->CRH) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRH) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRH) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				(GPIOx->ODR) |=  PinConfig.GPIO_PinNumber;
 				break;

 			case GPIO_MODE_INPUT_PD:
 				(GPIOx->CRH) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRH) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRH) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				(GPIOx->ODR) &= ~PinConfig.GPIO_PinNumber;
 				break;

 			case GPIO_MODE_OUTPUT_PP:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 				{
 					case GPIO_SPEED_10M:
 						(GPIOx->CRH) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 						(GPIOx->CRH) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 						break;
 					case GPIO_SPEED_2M:
 						(GPIOx->CRH) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 						(GPIOx->CRH) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 						break;
 					case GPIO_SPEED_50M:
 						(GPIOx->CRH) |=  (3<<4*PINNUM);	//set the two bits in MODE
 						break;
 				}
 				(GPIOx->CRH) &= ~(0XC<<4*PINNUM);   //reset two bits in CNF
 				break;

 			case GPIO_MODE_OUTPUT_OD:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 				{
 					case GPIO_SPEED_10M:
 						(GPIOx->CRH) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 						(GPIOx->CRH) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 						break;
 					case GPIO_SPEED_2M:
 						(GPIOx->CRH) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 						(GPIOx->CRH) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 						break;
 					case GPIO_SPEED_50M:
 						(GPIOx->CRH) |=  (3<<4*PINNUM);	//set the two bits in MODE
 						break;
 				}
 				(GPIOx->CRH) &= ~(0X8<<4*PINNUM);   //reset 2nd bits in CNF
 				(GPIOx->CRH) |=  (0X4<<4*PINNUM);   //set 1st bits in CNF
 				break;

 			case GPIO_MODE_OUTPUT_AF_PP:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 					{
 						case GPIO_SPEED_10M:
 							(GPIOx->CRH) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 							(GPIOx->CRH) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 							break;
 						case GPIO_SPEED_2M:
 							(GPIOx->CRH) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 							(GPIOx->CRH) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 							break;
 						case GPIO_SPEED_50M:
 							(GPIOx->CRH) |=  (3<<4*PINNUM);	//set the two bits in MODE
 							break;
 					}
 				(GPIOx->CRH) &= ~(0X4<<4*PINNUM);   //reset 1st bit in CNF
 				(GPIOx->CRH) |=  (0X8<<4*PINNUM);   //set 2nd bit in CNF
 				break;

 			case GPIO_MODE_OUTPUT_AF_OD:
 				switch(PinConfig.GPIO_OUTPUT_SPEED)
 					{
 						case GPIO_SPEED_10M:
 							(GPIOx->CRH) &= ~(2<<4*PINNUM);	//reset 2nd bit in MODE
 							(GPIOx->CRH) |=  (1<<4*PINNUM);	//set 1st bit in MODE
 							break;
 						case GPIO_SPEED_2M:
 							(GPIOx->CRH) &= ~(1<<4*PINNUM);	//set 2nd bit in MODE
 							(GPIOx->CRH) |=  (2<<4*PINNUM);	//reset 1st bit in MODE
 							break;
 						case GPIO_SPEED_50M:
 							(GPIOx->CRH) |=  (3<<4*PINNUM);	//set the two bits in MODE
 							break;
 					}
 				(GPIOx->CRH) |= (0Xc<<4*PINNUM);   //set two bits in CNF
 				break;

 			case GPIO_MODE_INPUT_AF:
 				(GPIOx->CRH) &= ~(0X3<<4*PINNUM);	//reset two bits in MODE
 				(GPIOx->CRH) &= ~(0X8<<4*PINNUM);   //reset 2nd bit in CNF
 				(GPIOx->CRH) |=  (0X4<<4*PINNUM);   //set 1st bit in CNF
 				break;
 		}
 	}
 }

/* =================================================================
 * @FN			- MCAL_GPIO_DeInit
 *
 * @Brief		- DeInitialize a GPIOx Whole peripheral
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 * 				  @ref:Peripheral Instants found in "stm32f103x6.h"
 *
 * @retval		- NONE
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
	//Write the reset values for GPIOx
	GPIOx->CRL =  0x44444444;
	GPIOx->CRH =  0x44444444;
	GPIOx->ODR =  0x00;
	GPIOx->IDR =  0x00;
	GPIOx->BSRR = 0x00;
	GPIOx->BRR =  0x00;
	GPIOx->LCKR = 0x00;
}

/* =================================================================
 * @FN			- MCAL_GPIO_Read_PIN
 *
 * @Brief		- Read GPIOx Pin y and return the value.
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 *
 *
 * @param(in)	- PinNumber: the number of pin to read.
 * 				  @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @retval		- The value of the pin "two values".
 * 				  @ref GPIO_PIN_state found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
uint8_t MCAL_GPIO_Read_PIN(GPIO_TypeDef* GPIOx ,uint16_t PinNumber)
{
	//Read a specific pin value
	uint8_t PINNUM = _FindPinNum(PinNumber);
	return ((GPIOx->IDR)&PinNumber)>>PINNUM;
}

/* =================================================================
 * @FN			- MCAL_GPIO_Read_PORT
 *
 * @Brief		- Read GPIOx and return the value
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 * 				  @ref Peripheral Instants found in "stm32f103x6.h"
 *
 * @retval		- The value of the Port
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
uint16_t MCAL_GPIO_Read_PORT(GPIO_TypeDef* GPIOx)
{
	//Read the whole port at once
	return (GPIOx->IDR)&0xFFFF;
}

/* =================================================================
 * @FN			- MCAL_GPIO_write_PIN
 *
 * @Brief		- Write a certain value to GPIOx Pin y.
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral.
 * 				  @ref:Peripheral Instants found in "stm32f103x6.h"
 *
 * @param(in)	- PinNumber: the number of pin to read.
 * 				  @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @param(in)	- Value: The value of the pin "two values".
 * 				  @ref GPIO_PIN_state found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @retval		- NONE
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
void MCAL_GPIO_Write_PIN(GPIO_TypeDef* GPIOx ,uint16_t PinNumber,uint8_t Value)
{
	switch (Value)
	{
		//If Value to be written is low
		case GPIO_PIN_LOW:
			//Reset the pin
			(GPIOx->ODR) &= ~PinNumber;
			break;
		//If Value to be written is high
		case GPIO_PIN_HIGH:
			//Set the pin
			(GPIOx->ODR) |= PinNumber;
			break;
		default:
			break;
	}

}

/* =================================================================
 * @FN			- MCAL_GPIO_write_PORT
 *
 * @Brief		- Write a certain value to GPIOx Whole PORT
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 *  			  @ref:Peripheral Instants found in "stm32f103x6.h"
 *
 * @param(in)	- Value: The value of be written on the port (varies from 0x0000 to 0xFFFF)
 *
 * @retval		- NONE
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
void MCAL_GPIO_Write_PORT(GPIO_TypeDef* GPIOx ,uint16_t Value)
{
	//Write the value on the whole port
	(GPIOx->ODR) = (Value & 0xFFFF);
}

/* =================================================================
 * @FN			- MCAL_GPIO_Toggle_PIN
 *
 * @Brief		- Toggle a certain GPIOx Pin y.
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 *  			  @ref:Peripheral Instants found in "stm32f103x6.h"
 *
 * @param(in)	- PinNumber: the number of pin to read.
 * 				  @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @retval		- NONE
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
void MCAL_GPIO_Toggle_PIN(GPIO_TypeDef* GPIOx ,uint16_t PinNumber)
{
	//Toggle the Pin using the given pin number
	(GPIOx->ODR) ^= PinNumber;
}

/* =================================================================
 * @FN			- MCAL_GPIO_Lock_PIN
 *
 * @Brief		- Lock a certain GPIOx pin y and freeze the IO mechanism
 *
 * @param(in)	- GPIOx: where x can be (A,B...E depending on device used) to select the GPIO peripheral
 *  			  @ref:Peripheral Instants found in "stm32f103x6.h"
 *
 * @param(in)	- PinNumber: the number of pin to read.
 * 				  @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @retval		- Return Values OK or Error for the Pin locking procedure.
 * 				  @ref: GPIO_PIN_LOCKING_STATUS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
uint8_t MCAL_GPIO_Lock_PIN(GPIO_TypeDef* GPIOx ,uint16_t PinNumber)
{
	//Write 1
	(GPIOx->LCKR) |= PinNumber;
	//Write 0
	(GPIOx->LCKR) &= ~PinNumber;
	//Write 1
	(GPIOx->LCKR) |= PinNumber;
	//Read 0
	if((GPIOx->LCKR) & PinNumber);
	//Read 1
	if((GPIOx->LCKR) & PinNumber) return GPIO_PIN_LOCK_OK;
	else return GPIO_PIN_LOCK_ERROR;
}

/* =================================================================
 * @FN			- _FindPinNum
 *
 * @Brief		- Helper Function to return the pin number of the defines
 *
 * @param(in)	- PinNumber: the number of pin to read.
 * 				  @ref GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"
 *
 * @retval		- Return the number of the pin (0,1,2,3,4)
 *
 * Note-		- STM32F103C6 MCU has GPIO A , B , C , D , E Modules
 * 				  but in LQFP48 Package has GPIO A , B , part of C and D exported to the external pins
 * =================================================================
 */
uint8_t _FindPinNum (uint16_t PinNumber)
{
	int counter=0;
	while(PinNumber){
		counter ++;
		PinNumber = (PinNumber>>1);
	}
	return counter-1;
}

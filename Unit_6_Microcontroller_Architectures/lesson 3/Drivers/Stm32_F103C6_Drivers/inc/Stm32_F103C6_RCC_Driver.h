/*
 * Stm32_F103C6_RCC_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"


//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------
#define HSI_RC_CLK			8000000

#define HSE_Clock			16000000

/*
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
uint32_t MCAL_RCC_GetSYS_CLKFreq(void);

uint32_t MCAL_RCC_GetHCLKFreq(void);

uint32_t MCAL_RCC_GetPCLK1Freq(void);

uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32_F103C6_EXTI_DRIVER_H_ */

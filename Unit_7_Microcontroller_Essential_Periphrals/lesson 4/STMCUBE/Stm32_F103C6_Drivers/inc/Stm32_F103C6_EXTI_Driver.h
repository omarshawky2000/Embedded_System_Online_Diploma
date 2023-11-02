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
#include "Stm32_F103C6_GPIO_Driver.h"

//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
//EXTI Mapping with GPIO structure
typedef struct
{
	uint16_t 			EXTI_InputLineNumber;	// Specifies the Input line number to the EXTI
												// @ref: EXTI_define found in "Stm32_F103C6_EXTI_Driver.h"

	GPIO_TypeDef	 * 	GPIO_Port;				// Specifies the GPIO Port to be configured with EXTI
												// @ref: Peripheral Instants found in "stm32f103x6.h"

	uint16_t 			GPIO_PIN;				// Specifies the GPIO Pin to be configured with EXTI
												// @ref: GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"

	uint16_t 			IVT_IRQ_Number;			// Specifies the Input line number to the EXTI
												// @ref: EXTI_IRQ_define found in "Stm32_F103C6_EXTI_Driver.h"

}EXTI_GPIO_Mapping_t;

//EXTI Configuration structure
typedef struct
{
	EXTI_GPIO_Mapping_t		EXTI_PIN;			// Structure to the EXTI to GPIO Mapping Configuration
												// @ref: EXTI_Mapping_define found in "Stm32_F103C6_EXTI_Driver.h"

	uint8_t 				Trigger_Case;		// Specifies the case that trigger the interrupt
												// @ref: EXTI_Trigger_define found in "Stm32_F103C6_EXTI_Driver.h"

	uint8_t 				IRQ_EN;				// Specifies if the interrupt is enabled or disabled
												// Will the mask in EXTI and NVIC
												// @ref: EXTI_IRQ_EN_define found in "Stm32_F103C6_EXTI_Driver.h"

	void			(*P_IRQ_CALLBACK)(void);	// Set the C Functions that will be called in the ISR

}EXTI_Config_t;

//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------

//@ref EXTI_define
#define EXTI0						0U
#define EXTI1						1U
#define EXTI2						2U
#define EXTI3						3U
#define EXTI4						4U
#define EXTI5						5U
#define EXTI6						6U
#define EXTI7						7U
#define EXTI8						8U
#define EXTI9						9U
#define EXTI10						10U
#define EXTI11						11U
#define EXTI12						12U
#define EXTI13						13U
#define EXTI14						14U
#define EXTI15						15U

//@ref EXTI_IRQ_define
#define EXTI0_IRQ					6U
#define EXTI1_IRQ					7U
#define EXTI2_IRQ					8U
#define EXTI3_IRQ					9U
#define EXTI4_IRQ					10U
#define EXTI5_IRQ					23U
#define EXTI6_IRQ					23U
#define EXTI7_IRQ					23U
#define EXTI8_IRQ					23U
#define EXTI9_IRQ					23U
#define EXTI10_IRQ					40U
#define EXTI11_IRQ					40U
#define EXTI12_IRQ					40U
#define EXTI13_IRQ					40U
#define EXTI14_IRQ					40U
#define EXTI15_IRQ					40U

//@ref EXTI_Mapping_define
//EXTI0
#define EXTI0PA0		(EXTI_GPIO_Mapping_t){ EXTI0 , GPIOA , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PB0		(EXTI_GPIO_Mapping_t){ EXTI0 , GPIOB , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PC0		(EXTI_GPIO_Mapping_t){ EXTI0 , GPIOC , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PD0		(EXTI_GPIO_Mapping_t){ EXTI0 , GPIOD , GPIO_PIN_0 , EXTI0_IRQ }

//EXTI1
#define EXTI1PA1		(EXTI_GPIO_Mapping_t){ EXTI1 , GPIOA , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PB1		(EXTI_GPIO_Mapping_t){ EXTI1 , GPIOB , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PC1		(EXTI_GPIO_Mapping_t){ EXTI1 , GPIOC , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PD1		(EXTI_GPIO_Mapping_t){ EXTI1 , GPIOD , GPIO_PIN_1 , EXTI1_IRQ }

//EXTI2
#define EXTI2PA2		(EXTI_GPIO_Mapping_t){ EXTI2 , GPIOA , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PB2		(EXTI_GPIO_Mapping_t){ EXTI2 , GPIOB , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PC2		(EXTI_GPIO_Mapping_t){ EXTI2 , GPIOC , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PD2		(EXTI_GPIO_Mapping_t){ EXTI2 , GPIOD , GPIO_PIN_2 , EXTI2_IRQ }

//EXTI3
#define EXTI3PA3		(EXTI_GPIO_Mapping_t){ EXTI3 , GPIOA , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PB3		(EXTI_GPIO_Mapping_t){ EXTI3 , GPIOB , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PC3		(EXTI_GPIO_Mapping_t){ EXTI3 , GPIOC , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PD3		(EXTI_GPIO_Mapping_t){ EXTI3 , GPIOD , GPIO_PIN_3 , EXTI3_IRQ }

//EXTI4
#define EXTI4PA4		(EXTI_GPIO_Mapping_t){ EXTI4 , GPIOA , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PB4		(EXTI_GPIO_Mapping_t){ EXTI4 , GPIOB , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PC4		(EXTI_GPIO_Mapping_t){ EXTI4 , GPIOC , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PD4		(EXTI_GPIO_Mapping_t){ EXTI4 , GPIOD , GPIO_PIN_4 , EXTI4_IRQ }

//EXTI5
#define EXTI5PA5		(EXTI_GPIO_Mapping_t){ EXTI5 , GPIOA , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PB5		(EXTI_GPIO_Mapping_t){ EXTI5 , GPIOB , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PC5		(EXTI_GPIO_Mapping_t){ EXTI5 , GPIOC , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PD5		(EXTI_GPIO_Mapping_t){ EXTI5 , GPIOD , GPIO_PIN_5 , EXTI5_IRQ }

//EXTI6
#define EXTI6PA6		(EXTI_GPIO_Mapping_t){ EXTI6 , GPIOA , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PB6		(EXTI_GPIO_Mapping_t){ EXTI6 , GPIOB , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PC6		(EXTI_GPIO_Mapping_t){ EXTI6 , GPIOC , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PD6		(EXTI_GPIO_Mapping_t){ EXTI6 , GPIOD , GPIO_PIN_6 , EXTI6_IRQ }

//EXTI7
#define EXTI7PA7		(EXTI_GPIO_Mapping_t){ EXTI7 , GPIOA , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PB7		(EXTI_GPIO_Mapping_t){ EXTI7 , GPIOB , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PC7		(EXTI_GPIO_Mapping_t){ EXTI7 , GPIOC , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PD7		(EXTI_GPIO_Mapping_t){ EXTI7 , GPIOD , GPIO_PIN_7 , EXTI7_IRQ }


//EXTI8
#define EXTI8PA8		(EXTI_GPIO_Mapping_t){ EXTI8 , GPIOA , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PB8		(EXTI_GPIO_Mapping_t){ EXTI8 , GPIOB , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PC8		(EXTI_GPIO_Mapping_t){ EXTI8 , GPIOC , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PD8		(EXTI_GPIO_Mapping_t){ EXTI8 , GPIOD , GPIO_PIN_8 , EXTI8_IRQ }


//EXTI9
#define EXTI9PA9		(EXTI_GPIO_Mapping_t){ EXTI9 , GPIOA , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PB9		(EXTI_GPIO_Mapping_t){ EXTI9 , GPIOB , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PC9		(EXTI_GPIO_Mapping_t){ EXTI9 , GPIOC , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PD9		(EXTI_GPIO_Mapping_t){ EXTI9 , GPIOD , GPIO_PIN_9 , EXTI9_IRQ }


//EXTI10
#define EXTI10PA10		(EXTI_GPIO_Mapping_t){ EXTI10 , GPIOA , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PB10		(EXTI_GPIO_Mapping_t){ EXTI10 , GPIOB , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PC10		(EXTI_GPIO_Mapping_t){ EXTI10 , GPIOC , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PD10		(EXTI_GPIO_Mapping_t){ EXTI10 , GPIOD , GPIO_PIN_10 , EXTI10_IRQ }


//EXTI11
#define EXTI11PA11		(EXTI_GPIO_Mapping_t){ EXTI11 , GPIOA , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PB11		(EXTI_GPIO_Mapping_t){ EXTI11 , GPIOB , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PC11		(EXTI_GPIO_Mapping_t){ EXTI11 , GPIOC , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PD11		(EXTI_GPIO_Mapping_t){ EXTI11 , GPIOD , GPIO_PIN_11 , EXTI11_IRQ }


//EXTI12
#define EXTI12PA12		(EXTI_GPIO_Mapping_t){ EXTI12 , GPIOA , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PB12		(EXTI_GPIO_Mapping_t){ EXTI12 , GPIOB , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PC12		(EXTI_GPIO_Mapping_t){ EXTI12 , GPIOC , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PD12		(EXTI_GPIO_Mapping_t){ EXTI12 , GPIOD , GPIO_PIN_12 , EXTI12_IRQ }


//EXTI13
#define EXTI13PA13		(EXTI_GPIO_Mapping_t){ EXTI13 , GPIOA , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PB13		(EXTI_GPIO_Mapping_t){ EXTI13 , GPIOB , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PC13		(EXTI_GPIO_Mapping_t){ EXTI13 , GPIOC , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PD13		(EXTI_GPIO_Mapping_t){ EXTI13 , GPIOD , GPIO_PIN_13 , EXTI13_IRQ }

//EXTI14
#define EXTI14PA14		(EXTI_GPIO_Mapping_t){ EXTI14 , GPIOA , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PB14		(EXTI_GPIO_Mapping_t){ EXTI14 , GPIOB , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PC14		(EXTI_GPIO_Mapping_t){ EXTI14 , GPIOC , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PD14		(EXTI_GPIO_Mapping_t){ EXTI14 , GPIOD , GPIO_PIN_14 , EXTI14_IRQ }

//EXTI15
#define EXTI15PA15		(EXTI_GPIO_Mapping_t){ EXTI15 , GPIOA , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PB15		(EXTI_GPIO_Mapping_t){ EXTI15 , GPIOB , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PC15		(EXTI_GPIO_Mapping_t){ EXTI15 , GPIOC , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PD15		(EXTI_GPIO_Mapping_t){ EXTI15 , GPIOD , GPIO_PIN_15 , EXTI15_IRQ }


//@ref EXTI_Trigger_define
#define EXTI_Trigger_RisingEdge							0U				//Rising Edge Detection
#define EXTI_Trigger_FallingEdge						1U				//Falling Edge Detection
#define EXTI_Trigger_RisingAndFallingEdge				2U				//Both Rising and Falling Edge Detection

//@ref EXTI_IRQ_EN_define
#define EXTI_DISABLE					0U				//Disable the EXTI IRQ
#define EXTI_ENABLE						1U				//Enable the EXTI IRQ


/*=
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void MCAL_EXTI_GPIO_Init(EXTI_Config_t* EXTI_Config);

void MCAL_EXTI_GPIO_Deinit(void);

void MCAL_EXTI_GPIO_Update(EXTI_Config_t* EXTI_Config);

#endif /* INC_STM32_F103C6_EXTI_DRIVER_H_ */

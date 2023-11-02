/*
 * Stm32_F103C6_EXTI_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_HAL_BLDC_DRIVER_H_
#define INC_HAL_BLDC_DRIVER_H_
//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"
//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
typedef uint8_t Half_Bridge_STATE;
typedef uint8_t BLDC_Driver_Vector;

//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
//BLDC Mapping with GPIO structure
typedef struct
{

	GPIO_TypeDef	 * 	GPIO_Port;				// Specifies the GPIO Port to be configured with EXTI
												// @ref: Peripheral Instants found in "stm32f103x6.h"

	uint16_t 			GPIO_PIN;				// Specifies the GPIO Pin to be configured with EXTI
												// @ref: GPIO_PINS_define found in "Stm32_F103C6_GPIO_Driver.h"

}BLDC_GPIO_Mapping_t;


//BLDC State Configuration structure
typedef struct
{
	BLDC_GPIO_Mapping_t		HB1_HIGH_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"

	BLDC_GPIO_Mapping_t		HB1_LOW_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"

	BLDC_GPIO_Mapping_t		HB2_HIGH_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"

	BLDC_GPIO_Mapping_t		HB2_LOW_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"

	BLDC_GPIO_Mapping_t		HB3_HIGH_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"

	BLDC_GPIO_Mapping_t		HB3_LOW_SIDE;		// Structure to the BLDC Drivers to GPIO Mapping Configuration
												// @ref: BLDC_Mapping_define found in "BLDC_driver.h"


}BLDC_Config_t;

//Half Bridge state structure
typedef struct
{
	Half_Bridge_STATE		HB1_HIGH_STATE;		// State of the half brige high side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

	Half_Bridge_STATE		HB1_LOW_STATE;		// State of the half brige low side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

	Half_Bridge_STATE		HB2_HIGH_STATE;		// State of the half brige high side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

	Half_Bridge_STATE		HB2_LOW_STATE;		// State of the half brige low side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

	Half_Bridge_STATE		HB3_HIGH_STATE;		// State of the half brige high side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

	Half_Bridge_STATE		HB3_LOW_STATE;		// State of the half brige low side MOSFET
												// @ref: HB_STATE_define found in "BLDC_driver.h"

}Bridge_States_t;


//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------
// @ref: BLDC_Mapping_define

#define A0  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_0}
#define A1  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_1}
#define A2  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_2}
#define A3  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_3}
#define A4  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_4}
#define A5  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_5}
#define A6  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_6}
#define A7  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_7}
#define A8  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_8}
#define A9  (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_9}
#define A10 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_10}
#define A11 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_11}
#define A12 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_12}
#define A13 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_13}
#define A14 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_14}
#define A15 (BLDC_GPIO_Mapping_t){GPIOA,GPIO_PIN_15}

#define B0  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_0}
#define B1  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_1}
#define B2  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_2}
#define B3  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_3}
#define B4  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_4}
#define B5  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_5}
#define B6  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_6}
#define B7  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_7}
#define B8  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_8}
#define B9  (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_9}
#define B10 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_10}
#define B11 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_11}
#define B12 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_12}
#define B13 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_13}
#define B14 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_14}
#define B15 (BLDC_GPIO_Mapping_t){GPIOB,GPIO_PIN_15}

// @ref: HB_STATE_define
#define HB_OFF							((Half_Bridge_STATE)0x0000U)
#define HB_ON							((Half_Bridge_STATE)0x0001U)


// @ref: BLDC_DRIVER_VECTOR_define
#define VECTOR_0						(Bridge_States_t){ HB_OFF , HB_ON  , HB_OFF , HB_ON  , HB_OFF , HB_ON  }
#define VECTOR_1						(Bridge_States_t){ HB_ON  , HB_OFF , HB_OFF , HB_OFF , HB_OFF , HB_ON  }
#define VECTOR_2						(Bridge_States_t){ HB_OFF , HB_OFF , HB_ON  , HB_OFF , HB_OFF , HB_ON  }
#define VECTOR_3						(Bridge_States_t){ HB_OFF , HB_ON  , HB_ON  , HB_OFF , HB_OFF , HB_OFF }
#define VECTOR_4						(Bridge_States_t){ HB_OFF , HB_ON  , HB_OFF , HB_OFF , HB_ON  , HB_OFF }
#define VECTOR_5						(Bridge_States_t){ HB_OFF , HB_OFF , HB_OFF , HB_ON  , HB_ON  , HB_OFF }
#define VECTOR_6						(Bridge_States_t){ HB_ON  , HB_OFF , HB_OFF , HB_ON  , HB_OFF , HB_OFF }
#define VECTOR_7						(Bridge_States_t){ HB_ON  , HB_OFF , HB_ON  , HB_OFF , HB_ON  , HB_OFF }

//----------------------------------------------------------
//Default Configuration
//----------------------------------------------------------
//BLDC_DEFAULT0
#define BLDC_DEFAULT0		(BLDC_Config_t){ A3 , A4 , A5 , A6 , A7 , A8 }

/*
* ===============================================
* APIs Supported by "HAL_BLDC_DRIVER"
* ===============================================
*/
void HAL_BLDC_Init(BLDC_Config_t* BLDC_Config);

void HAL_BLDC_Write_HB_States(Bridge_States_t* Bridges_States);

void HAL_BLDC_Write_Vector(Bridge_States_t VECTOR);

void HAL_BLDC_Deinit(void);


#endif /* INC_HAL_BLDC_DRIVER_H_ */

/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "HAL_BLDC_driver.h"
 #include "Stm32_F103C6_EXTI_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 BLDC_Config_t _BLDC_Config;			  //Save Current BLDC Configuration
 Bridge_States_t _VECTOR;			      //Save Current BLDC Vector State

 //========================================================================
 //								PRIVATE MACROS
 //========================================================================



 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================



 //========================================================================
 //								       APIs
 //========================================================================
 /* ================================================================
  * @Fn				-HAL_BLDC_Init
  *
  * @brief 			-Initializes the BLDC Half bridge drivers with the configured GPIO Pins
  *
  * @param [in] 	-BLDC_Config : Pointer to structure of the configuration for the BLDC
  * 				 @ref BLDC Configuration structure found in "HAL_BLDC_driver.h"
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void HAL_BLDC_Init(BLDC_Config_t* BLDC_Config)
 {
	//Save the given parameters inside a private structure
	_BLDC_Config.HB1_HIGH_SIDE.GPIO_Port = BLDC_Config->HB1_HIGH_SIDE.GPIO_Port;
	_BLDC_Config.HB1_HIGH_SIDE.GPIO_PIN = BLDC_Config->HB1_HIGH_SIDE.GPIO_PIN;

	_BLDC_Config.HB1_LOW_SIDE.GPIO_Port = BLDC_Config->HB1_LOW_SIDE.GPIO_Port;
	_BLDC_Config.HB1_LOW_SIDE.GPIO_PIN = BLDC_Config->HB1_LOW_SIDE.GPIO_PIN;

	_BLDC_Config.HB2_HIGH_SIDE.GPIO_Port = BLDC_Config->HB2_HIGH_SIDE.GPIO_Port;
	_BLDC_Config.HB2_HIGH_SIDE.GPIO_PIN = BLDC_Config->HB2_HIGH_SIDE.GPIO_PIN;

	_BLDC_Config.HB2_LOW_SIDE.GPIO_Port = BLDC_Config->HB2_LOW_SIDE.GPIO_Port;
	_BLDC_Config.HB2_LOW_SIDE.GPIO_PIN = BLDC_Config->HB2_LOW_SIDE.GPIO_PIN;

	_BLDC_Config.HB3_HIGH_SIDE.GPIO_Port = BLDC_Config->HB3_HIGH_SIDE.GPIO_Port;
	_BLDC_Config.HB3_HIGH_SIDE.GPIO_PIN = BLDC_Config->HB3_HIGH_SIDE.GPIO_PIN;

	_BLDC_Config.HB3_LOW_SIDE.GPIO_Port = BLDC_Config->HB3_LOW_SIDE.GPIO_Port;
	_BLDC_Config.HB3_LOW_SIDE.GPIO_PIN = BLDC_Config->HB3_LOW_SIDE.GPIO_PIN;

	GPIO_PinConfig_t PinConfig;
	//Note all pins will be configured as open drain
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;

	//Configuring Half bridge 1 High side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB1_HIGH_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB1_HIGH_SIDE.GPIO_Port, PinConfig);

	//Configuring Half bridge 1 Low side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB1_LOW_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB1_LOW_SIDE.GPIO_Port, PinConfig);

	//Configuring Half bridge 2 High side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB2_HIGH_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB2_LOW_SIDE.GPIO_Port, PinConfig);

	//Configuring Half bridge 2 Low side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB2_LOW_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB2_LOW_SIDE.GPIO_Port, PinConfig);

	//Configuring Half bridge 3 High side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB3_HIGH_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB3_HIGH_SIDE.GPIO_Port, PinConfig);

	//Configuring Half bridge 3 Low side MOSFET
	PinConfig.GPIO_PinNumber = _BLDC_Config.HB3_LOW_SIDE.GPIO_PIN;
	MCAL_GPIO_Init(_BLDC_Config.HB3_LOW_SIDE.GPIO_Port, PinConfig);

 }

/* ================================================================= */

 /* ================================================================
  * @Fn				-HAL_BLDC_Write_HB_States
  *
  * @brief 			-Writes the state of each half bridge high and low side
  *
  * @param [in] 	-Bridges_States : Pointer to structure of the states for all the half bridges
  * 				 @ref Half Bridge state structure found in "HAL_BLDC_driver.h"
  *
  * @retval 		-NONE
  *
  * Note			-HAL_BLDC_Init Must be called first
  * =================================================================
  */
 void HAL_BLDC_Write_HB_States(Bridge_States_t* Bridges_States)
 {
	/**********************HB1******************************/
	/*###################HIGH SIDE###################*/
	//Changing HB1 High side state
	if( Bridges_States->HB1_HIGH_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB1_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB1_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB1_HIGH_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB1_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB1_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given

	/*###################LOW SIDE###################*/
	//Changing HB1 Low side state
	if( Bridges_States->HB1_LOW_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB1_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB1_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB1_LOW_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB1_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB1_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given


	/**********************HB2******************************/
	/*###################HIGH SIDE###################*/
	//Changing HB2 High side state
	if( Bridges_States->HB2_HIGH_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB2_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB2_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB2_HIGH_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB2_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB2_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given

	/*###################LOW SIDE###################*/
	//Changing HB2 Low side state
	if( Bridges_States->HB2_LOW_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB2_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB2_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB2_LOW_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB2_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB2_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given

	/**********************HB3******************************/
	/*###################HIGH SIDE###################*/
	if( Bridges_States->HB3_HIGH_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB3_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB3_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB3_HIGH_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB3_HIGH_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB3_HIGH_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given

	/*###################LOW SIDE###################*/
	//Changing HB2 Low side state
	if( Bridges_States->HB3_LOW_STATE == HB_ON)
	{	//Write High to the PIN if state is given as ON
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB3_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB3_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_HIGH);
	}
	else if( Bridges_States->HB2_LOW_STATE == HB_OFF)
	{	//Write LOW to the PIN if state is given as OFF
		MCAL_GPIO_Write_PIN(_BLDC_Config.HB3_LOW_SIDE.GPIO_Port\
						   ,_BLDC_Config.HB3_LOW_SIDE.GPIO_PIN\
						   ,GPIO_PIN_LOW);
	}
	else;	//Don't Change PIN state if wrong entry is given

 }

 /* ================================================================= */
 /* ================================================================
  * @Fn				-HAL_BLDC_Write_HB_States
  *
  * @brief 			-Writes the state of each half bridge high and low side
  *
  * @param [in] 	-VECTOR : Write a predefined vector all at once
  * 				 @ref BLDC_DRIVER_VECTOR_define found in "HAL_BLDC_driver.h"
  *
  * @retval 		-NONE
  *
  * Note			-HAL_BLDC_Init Must be called first
  * =================================================================
  */
 void HAL_BLDC_Write_Vector(Bridge_States_t VECTOR)
 {
	 //Saving the given vector to the private variable
	 _VECTOR.HB1_HIGH_STATE = VECTOR.HB1_HIGH_STATE;
	 _VECTOR.HB1_LOW_STATE  = VECTOR.HB1_LOW_STATE;

	 _VECTOR.HB2_HIGH_STATE = VECTOR.HB2_HIGH_STATE;
	 _VECTOR.HB2_LOW_STATE  = VECTOR.HB2_LOW_STATE;

	 _VECTOR.HB3_HIGH_STATE = VECTOR.HB3_HIGH_STATE;
	 _VECTOR.HB3_LOW_STATE  = VECTOR.HB3_LOW_STATE;

	 //Write the vector states to the BLDC Half bridges
	 HAL_BLDC_Write_HB_States(& _VECTOR);

 }

 /* ================================================================= */


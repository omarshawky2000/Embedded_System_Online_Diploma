/*
 * Stm32_F103C6_I2C_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"


#define I2C_EVENT_MASTER_BYTE_TRANSMITTING				((uint32_t) 0x00070080)  /*  TRA , BUSY , MSL , TXE Flags */
//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
//ACKN Direction ENUM
typedef enum
{
	ACK_DIS= 0,
	ACK_EN

}ACKN_STATE;
//I2C Direction ENUM
typedef enum
{
	I2C_DIRECTION_TRANSMIT= 0,
	I2C_DIRECTION_RECIEVE

}I2C_DIR;

//FUNCTIONAL STATE ENUM
typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5,
	EV6,
	EV7,
	EV8,
	EV8_1,
	MASTER_BYTE_TRANSMITTING = ((uint32_t) 0x00070080)

}STATUS;


//FUNCTIONAL STATE ENUM
typedef enum
{
	FLAG_LOW,
	FLAG_HIGH

}FLAGSTATUS;

//FUNCTIONAL STATE ENUM
typedef enum
{
	FS_ENABLE,
	FS_DISABLE

}FUNCTIONAL_STATE;

//REPEATED START ENUM
typedef enum
{
	REPEATED_START,
	NO_REPEATED_START

}RP_START;

//STOP CONDITION ENUM
typedef enum
{
	With_STOP,
	Without_STOP

}STOP_CONDITION;

//Slave State ENUM
typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_MATCHED,
	I2C_EV_DATA_REQ,				//The APP layer should send the data (I2C_SlaveSendData) in the ISR
	I2C_EV_DATA_REV				    //The APP layer should read the data (I2C_SlaveReadData) in the ISR

}SLAVE_STATTE;
//I2C Slave Address structure
typedef struct
{
	uint8_t 	EN_Dual_ADD;							//1- Enable , 2- Disable
	uint8_t 	I2C_ADDRESSING_MODE;					//@ref: I2C_ADDRESSING_MODE_define: found in "Stm32_F103C6_I2C_Driver.h"
	uint16_t 	PRIMARY_SLAVE_ADDRESS;
	uint16_t 	SECONDARY_SLAVE_ADDRESS;
}S_I2C_SLAVE_DEVICE_ADDRESS;
//I2C Interrupt source structure
struct S_IRQ_SRC
{
	uint8_t 	TXE:1;			//TX buffer empty interrupt
	uint8_t 	RXNE:1;			//RX buffer not empty interrupt
	uint8_t 	ERRI:1;			//Error interrupt
	uint8_t 	Reserved:5;
};

//I2C Configuration structure
typedef struct
{
	uint16_t 							I2C_CLOCK_SPEED;		// Specifies the Clock Frequency
																// @ref: I2C_CLOCK_SPEED_define found in "Stm32_F103C6_I2C_Driver.h"

	uint16_t 							I2C_MODE;				// Specifies I2C or SMB mode
																// @ref: I2C_MODE_define found in "Stm32_F103C6_I2CDriver.h"

	uint16_t 							I2C_STRETCH_MODE;		// Specifies whether the stretching mode is enabled / disabled
																// @ref: I2C_STRETCH_MODE_define found in "Stm32_F103C6_I2C_Driver.h"

	S_I2C_SLAVE_DEVICE_ADDRESS			I2C_SLAVE_ADDRESS;		// Specifies the slave address


	uint16_t 							I2C_ACK_CONTROL;		// Enable or Disable the Acknowledgment
																// @ref: I2C_ACK_CONTROL_define found in "Stm32_F103C6_I2C_Driver.h"

	uint16_t 							I2C_GENERALCALL_EN;		// Specifies to enable or disable the general call feature
																// @ref: I2C_GENERALCALL_EN_define found in "Stm32_F103C6_I2C_Driver.h"

	uint16_t 							I2C_IRQ_ENABLE;			// Enable or Disable I2C Interrupts
																// @ref: I2C_IRQ_ENABLE_define found in "Stm32_F103C6_I2C_Driver.h"

	void			(*P_SLAVE_EV_IRQ_CALLBACK)(SLAVE_STATTE STATE);		// Set the C Functions that will be called in the ISR

}I2C_Config_t;

//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------
// @ref: I2C_CLOCK_SPEED_define:
// - Standard Speed (Up to 100KHz)
// - Fast speed (Up to 400KHz)
// - to configure Clock before enabling the register
// ---I2C_CR2.FREQ[5:0}: Peripheral clock frequency
// . Configure the clock conrol registers
//		Thigh =  CCR * TPCLK1
//			SM or FM
// . Configure the rise time register I2C_TRISE
// ---

#define  I2C_SCLK_SM_50K						(50000UL)
#define  I2C_SCLK_SM_100K						(100000UL)


// @ref:I2C_STERTCH_MODE_define:

#define  I2C_STRETCH_MODE_EN					(0x00000000UL)
#define  I2C_STRETCH_MODE_DIS					I2C_CR1_NOSTRETCH

// @ref: I2C_MODE_define
#define  I2C_MODE_I2C							(0x00000000UL)
#define  I2C_MODE_BUS							I2C_CR1_SMBUS
//@ref: I2C_ADDRESSING_MODE_define:
#define  I2C_ADDRESSING_MODE_7BIT				(0x00000000UL)
#define  I2C_ADDRESSING_MODE_10BIT				(uint16)(1<<15)

// @ref: I2C_ACK_CONTROL_define:
#define  I2C_ACK_ENABLE							I2C_CR1_ACK
#define  I2C_ACK_DISABLE						(0x00000000UL)

// @ref: I2C_GENERALCALL_EN_define:
#define  I2C_GENERALCALL_ENABLE					I2C_CR1_ENGC
#define  I2C_GENERALCALL_DISABLE				(0x00000000UL)
/*=
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void MCAL_I2C_Init ( I2C_TypeDef* I2Cx , I2C_Config_t * I2C_Config);

void MCAL_I2C_DeInit ( I2C_TypeDef* I2Cx );

void MCAL_I2C_GPIO_Set_Pins ( I2C_TypeDef* I2Cx );

//Master polling mechanism
void MCAL_I2C_MASTER_TX ( I2C_TypeDef* I2Cx , uint16_t Slave_ADD , uint8_t* DATA ,\
						  uint32_t DATA_LENGTH , STOP_CONDITION STOP , RP_START START);

void MCAL_I2C_MASTER_RX ( I2C_TypeDef* I2Cx , uint16_t Slave_ADD , uint8_t* DATA ,\
						  uint32_t DATA_LENGTH , STOP_CONDITION STOP , RP_START START);

//Slave interrupt mechanism

//Generic APIs
void MCAL_I2C_GENERATE_START ( I2C_TypeDef* I2Cx , FUNCTIONAL_STATE STATE , RP_START START);

void MCAL_I2C_GENERATE_STOP  ( I2C_TypeDef* I2Cx , FUNCTIONAL_STATE STATE );

void MCAL_I2C_SEND_ADDRESS ( I2C_TypeDef* I2Cx , uint16_t ADDRESS , I2C_DIR I2C_Direction);

FLAGSTATUS MCAL_I2C_GETFLAG_STATUS (I2C_TypeDef* I2Cx  , STATUS FLAG );

FLAGSTATUS MCAL_I2C_GETFLAG_STATUS (I2C_TypeDef* I2Cx  , STATUS FLAG );

void MCAL_I2C_ACKConfig( I2C_TypeDef* I2Cx ,ACKN_STATE ACK_ST);

#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */

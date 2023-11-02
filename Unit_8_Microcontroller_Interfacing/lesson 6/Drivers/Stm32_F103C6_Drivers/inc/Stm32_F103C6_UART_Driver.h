/*
 * Stm32_F103C6_UART_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32_F103C6_UART_DRIVER_H_
#define INC_STM32_F103C6_UART_DRIVER_H_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"

//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
//UART Configuration structure
typedef struct
{
	uint8_t 				USART_MODE;				// Specifies the TX/RX Enable/Disable
													// @ref: USART_MODE_define found in "Stm32_F103C6_UART_Driver.h"

	uint32_t 				USART_BAUDRATE;			// Specifies Baudrate of the USART
													// @ref: USART_BAUDRATE_define found in "Stm32_F103C6_UARTDriver.h"

	uint8_t 				USART_PAYLOAD_LENGTH;	// Specifies the length of the data either 8 or 9 bits
													// @ref: USART_PAYLOAD_LENGTH_define found in "Stm32_F103C6_UART_Driver.h"

	uint8_t 				USART_PARITY;			// Specifies if there is parity and its type
													// @ref: USART_PARITY_define found in "Stm32_F103C6_UART_Driver.h"

	uint8_t 				USART_STOP;				// Specifies the number of stop bits
													// @ref: USART_STOP_define found in "Stm32_F103C6_UART_Driver.h"

	uint8_t 				USART_FLWCTRL;			// Specifies the flow control of the USART
													// @ref: USART_FLWCTRL_define found in "Stm32_F103C6_UART_Driver.h"

	uint8_t 				USART_IRQ_ENABLE;		// Enable or Disable USART Interrupts
													// @ref: USART_IRQ_ENABLE_define found in "Stm32_F103C6_UART_Driver.h"

	void			(*P_IRQ_CALLBACK)(void);		// Set the C Functions that will be called in the ISR

}UART_Config_t;

//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------

//@ref USART_MODE_define
#define USART_MODE_TX						(uint32_t) (1<<3)
#define USART_MODE_RX						(uint32_t) (1<<2)
#define USART_MODE_TX_RX					(uint32_t) (1<<3 | 1<<2)


//@ref USART_BAUDRATE_define
#define USART_BAUDRATE_2400						2400U
#define USART_BAUDRATE_9600						9600U
#define USART_BAUDRATE_19200					19200U
#define USART_BAUDRATE_57600					57600U
#define USART_BAUDRATE_115200					115200U
#define USART_BAUDRATE_230400					230400U
#define USART_BAUDRATE_460800					460800U
#define USART_BAUDRATE_921600					921600U
#define USART_BAUDRATE_2250000					2250000U
#define USART_BAUDRATE_4500000					4500000U

//@ref USART_PAYLOAD_LENGTH_defin
#define USART_PAYLOAD_LENGTH_8Bits				((uint32_t) 0)
#define USART_PAYLOAD_LENGTH_9Bits				(uint32_t) (1<<12)

//@ref USART_PARITY_define
#define USART_PARITY_NONE				((uint32_t) 0)
#define USART_PARITY_EVEN				 (uint32_t) (1<<10)
#define USART_PARITY_ODD				((uint32_t) (1<<10) | (1<<9))

// @ref: USART_STOP_define
#define USART_STOP_HALF				(uint32_t) (1<<12)
#define USART_STOP_ONE			((uint32_t) 0)
#define USART_STOP_ONE_HALF		(uint32_t) (3<<12)
#define USART_STOP_TWO			(uint32_t) (2<<12)

// @ref: USART_FLWCTRL_define
#define USART_FLWCTRL_NONE			((uint32_t) 0)
#define USART_FLWCTRL_RTS			(uint32_t) (1<<8)
#define USART_FLWCTRL_CTS			(uint32_t) (1<<9)
#define USART_FLWCTRL_RTS_CTS		((uint32_t) (1<<8) | (1<<9))

//@ref:  USART_IRQ_ENABLE_define
#define USART_IRQ_ENABLE_NONE		((uint32_t) 0)
#define USART_IRQ_ENABLE_TXE		(uint32_t) (1<<7)		//Transmit data register empty
#define USART_IRQ_ENABLE_TC			(uint32_t) (1<<6)		//Transmission complete
#define USART_IRQ_ENABLE_RXNEIE		(uint32_t) (1<<5)		//Received data ready to be read
#define USART_IRQ_ENABLE_PE			(uint32_t) (1<<8) 		//Parity error

enum Polling_Mechanism {
	enable,
	disable
};

/*=
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void MCAL_UART_Init (USART_TypeDef * USARTx , UART_Config_t * UART_Config);

void MCAL_UART_DeInit (USART_TypeDef * USARTx );

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx );

void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTXBuffer , enum Polling_Mechanism PollingEN);

void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t * pRXBuffer , enum Polling_Mechanism PollingEN);

void MCAL_UART_WAIT_TC (USART_TypeDef * USARTx);


#endif /* INC_STM32_F103C6_UART_DRIVER_H_ */

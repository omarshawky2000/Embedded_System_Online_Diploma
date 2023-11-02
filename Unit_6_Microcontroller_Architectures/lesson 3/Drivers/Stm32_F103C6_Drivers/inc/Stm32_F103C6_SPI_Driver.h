/*
 * Stm32_F103C6_SPI_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"

//----------------------------------------------------------
//User type definitions (structures)
//----------------------------------------------------------
//SPI Interrupt source structure
struct S_IRQ_SRC
{
	uint8_t 	TXE:1;			//TX buffer empty interrupt
	uint8_t 	RXNE:1;			//RX buffer not empty interrupt
	uint8_t 	ERRI:1;			//Error interrupt
	uint8_t 	Reserved:5;
};

//SPI Configuration structure
typedef struct
{
	uint16_t 				SPI_DEVICE_MODE;		// Specifies the Master/Slave mode
													// @ref: SPI_DEVICE_MODE_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_COMM_MODE;			// Specifies the SPI bidirectional mode state
													// @ref: SPI_COMM_MODE_define found in "Stm32_F103C6_SPIDriver.h"

	uint16_t 				SPI_FRAME_FORMAT;		// Specifies LSB or MSB
													// @ref: SSPI_FRAME_FORMAT_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_DATA_SIZE;			// Specifies if the data is 8 bits or 16 bits
													// @ref: SPI_DATA_SIZE_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_CLK_POLARITY;		// Specifies the clock polarity
													// @ref: SPI_CLK_POLARITY_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_CLK_PHASE;			// Specifies to sample on first edge or second edge
													// @ref: SPI_CLK_PHASE_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_IRQ_ENABLE;			// Enable or Disable SPI Interrupts
													// @ref: SPI_IRQ_ENABLE_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_NSS;				// Specifies whether the NSS signal is managed by hardware NSS Pin or software SSI bit
													// @ref: SPI_NSS_define found in "Stm32_F103C6_SPI_Driver.h"

	uint16_t 				SPI_BR_PRESC;			// Specifies the prescaler of the SPI clock
													// @ref: SPI_BR_PRESC_define found in "Stm32_F103C6_SPI_Driver.h"

	void			(*P_IRQ_CALLBACK)(struct S_IRQ_SRC irq_src);		// Set the C Functions that will be called in the ISR

}SPI_Config_t;

//----------------------------------------------------------
//Macros Configuration References
//----------------------------------------------------------

//@ref SPI_DEVICE_MODE_define
#define SPI_DEVICE_MODE_SLAVE						(uint32_t) (0<<2)
#define SPI_DEVICE_MODE_MASTER						(uint32_t) (1<<2)


//@ref SPI_COMM_MODE_define
#define SPI_COMM_MODE_DIR_2LINES					(uint32_t) (0<<10)				//CR1
#define SPI_COMM_MODE_DIR_2LINES_RX					(uint32_t) (1<<10)				//CR1
#define SPI_COMM_MODE_DIR_1LINE_RX					(uint32_t) (1<<15)				//CR1
#define SPI_COMM_MODE_DIR_1LINE_TX					(uint32_t) (1<<15) | (1<<14) 	//CR1


//@ref SPI_FRAME_FORMAT_define
#define SPI_FRAME_FORMAT_MSB_FIRST					(uint32_t) (0<<7)
#define SPI_FRAME_FORMAT_LSB_FIRST					(uint32_t) (1<<7)

//@ref SPI_DATA_SIZE_define
#define SPI_DATA_SIZE_8BITS							(uint32_t) (0<<11)
#define SPI_DATA_SIZE_16BITS						(uint32_t) (1<<11)


// @ref: SPI_CLK_POLARITY_define
#define SPI_CLK_POLARITY_IDLE_LOW					(uint32_t) (0<<1)
#define SPI_CLK_POLARITY_IDLE_HIGH					(uint32_t) (1<<1)


// @ref: SPI_CLK_PHASE_define
#define  SPI_CLK_PHASE_FIST_EDGE_SMPL				(uint32_t) (0<<0)
#define  SPI_CLK_PHASE_SEC_EDGE_SMPL				(uint32_t) (1<<0)


//@ref:  SPI_IRQ_ENABLE_define
#define SPI_IRQ_ENABLE_NONE							(uint32_t) (0<<7)
#define SPI_IRQ_ENABLE_TXEIE						(uint32_t) (1<<7)		//Transmit data register empty
#define SPI_IRQ_ENABLE_RXNEIE						(uint32_t) (1<<6)		//Received data ready to be read
#define SPI_IRQ_ENABLE_ERROR						(uint32_t) (1<<5) 		//Interrupt Error
// @ref: SPI_NSS_define
/* HARDWARE */
#define  SPI_NSS_HW_SLAVE							(uint32_t) (0<<9)
#define  SPI_NSS_HW_MASTER_SS_OUT_EN				(uint32_t) (1<<2)		//SPI_CR2 Bit
#define  SPI_NSS_HW_MASTER_SS_OUT_DIS				(uint32_t) (0<<2)		//SPI_CR2 Bit

/* SOFTWARE */
#define  SPI_NSS_SW_NSSI_RESET						(uint32_t) (1<<9)
#define  SPI_NSS_SW_NSSI_SET						(uint32_t) (1<<9) | (1<<8)


// @ref: SPI_BR_PRESC_define
#define  SPI_BR_PRESC_2								(uint32_t) (0<<3)
#define  SPI_BR_PRESC_4								(uint32_t) (0b001U<<3)
#define  SPI_BR_PRESC_8								(uint32_t) (0b010U<<3)
#define  SPI_BR_PRESC_16							(uint32_t) (0b011U<<3)
#define  SPI_BR_PRESC_32							(uint32_t) (0b100U<<3)
#define  SPI_BR_PRESC_64							(uint32_t) (0b101U<<3)
#define  SPI_BR_PRESC_128							(uint32_t) (0b110U<<3)
#define  SPI_BR_PRESC_256							(uint32_t) (0b111U<<3)

enum SPI_Polling_Mechanism {
	SPI_POLL_enable,
	SPI_POLL_disable
};

/*=
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/
void MCAL_SPI_Init (SPI_TypeDef * SPIx , SPI_Config_t * SPI_Config);

void MCAL_SPI_DeInit (SPI_TypeDef * SPIx );

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx );

void MCAL_SPI_SendData(SPI_TypeDef * SPIx , uint16_t * pTXBuffer , enum SPI_Polling_Mechanism PollingEN);

void MCAL_SPI_ReceiveData(SPI_TypeDef * SPIx , uint16_t * pRXBuffer , enum SPI_Polling_Mechanism PollingEN);

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx , uint16_t * pTXBuffer , enum SPI_Polling_Mechanism PollingEN);

void MCAL_SPI_WAIT_TC (SPI_TypeDef * SPIx);


#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */

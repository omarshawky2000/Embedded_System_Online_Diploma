/*
 * Stm32_F103C6_UART_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_GPIO_Driver.h"
 #include "Stm32_F103C6_UART_Driver.h"
 #include "Stm32_F103C6_RCC_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 UART_Config_t * _UART_Config;

 //========================================================================
 //								PRIVATE MACROS
 //========================================================================
 #define USARTDIV(_PCLK_,_BAUD_)			(uint32_t) ( _PCLK_/ (16*_BAUD_) )
 #define USARTDIV_MUL100(_PCLK_,_BAUD_)		(uint32_t) ( (25*_PCLK_) / (4 *_BAUD_) )
 #define Mantissa_MUL100(_PCLK_,_BAUD_)		(uint32_t) ( USARTDIV(_PCLK_,_BAUD_) * 100 )
 #define Mantissa(_PCLK_,_BAUD_)			(uint32_t) ( USARTDIV(_PCLK_,_BAUD_) )
 #define DIV_Fraction(_PCLK_,_BAUD_)		(uint32_t) ((( USARTDIV_MUL100(_PCLK_,_BAUD_)- Mantissa_MUL100(_PCLK_,_BAUD_) )* 16 )/ 100 )
 #define UART_BRR_Register(_PCLK_,_BAUD_)	( (Mantissa(_PCLK_,_BAUD_)) <<4 ) | ( (DIV_Fraction(_PCLK_,_BAUD_)) &0xF )
 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================


 //========================================================================
 //								       APIs
 //========================================================================
 /* ================================================================
  * @Fn				-MCAL_UART_Init
  *
  * @brief 			-Initializes the UART(N) where N is the number of USART
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @param [in] 	-UART_Config: Configuration structure of the USART.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_UART_Init (USART_TypeDef * USARTx , UART_Config_t * UART_Config)
 {
	 uint32_t pclk , BRR;

	 _UART_Config = UART_Config;
	 //enable the Clock for given USART peripheral
	 if(USARTx == USART1)
		 RCC_USART1_CLK_EN();
	 else if (USARTx == USART2)
		 RCC_USART2_CLK_EN();
	 else if (USARTx == USART3)
		 RCC_USART3_CLK_EN();

	 //Enable the USART Module
	 // Bit 13 UE: USART enable
	 USARTx->CR1 |= 1 <<13;

	 //Enable USART TX and RX according to the USART_Mode configuration item
	 //USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	 USARTx->CR1 |= UART_Config->USART_MODE;

	 //Payload Width
	 //USARTx->CR1 Bit 12 M: Word length
	 USARTx->CR1 |= UART_Config->USART_PAYLOAD_LENGTH;

	 //Parity control bit fields
	 //USARTx->CR1 Bit 10 PCE: Parity control enable Bit 9 PS: Parity selection
	 USARTx->CR1 |= UART_Config->USART_PARITY;

	 //Stop bits
	 //USARTx->CR2 Bit 13:12 STOP: STOP bits
	 USARTx->CR2 |= UART_Config->USART_STOP;

	 //Hardware flow control
	 //USART_CR3 Bit 9 CTSE: CTS enable Bit 8 RTSE: RTS enable
	 USARTx->CR3 |= UART_Config->USART_FLWCTRL;

	 //Configure the baudrate
	 //PCLK1 for USART2 , 3
	 //PCLK2 for USART1
	 if		 (USARTx == USART1) pclk = MCAL_RCC_GetPCLK2Freq();
	 else if (USARTx == USART2) pclk = MCAL_RCC_GetPCLK1Freq();

	 BRR = UART_BRR_Register(pclk , UART_Config->USART_BAUDRATE);

	 USARTx->BRR = BRR;

	 //ENABLE / DISABLE Interrupt
	 if (UART_Config->USART_IRQ_ENABLE != USART_IRQ_ENABLE_NONE)
	 {
		 USARTx->CR1 |= (UART_Config->USART_IRQ_ENABLE);
		 //Enable NVIC For USARTx IRQ
		 if (USARTx == USART1)
			 NVIC_IRQ37_USART1_EN();
		 else if (USARTx == USART2)
			 NVIC_IRQ38_USART2_EN();
		 else if (USARTx == USART3)
			 NVIC_IRQ39_USART3_EN();

	 }
	 else
	 {
		 //Disable NVIC For USARTx IRQ
		 if (USARTx == USART1)
			 NVIC_IRQ37_USART1_DIS();
		 else if (USARTx == USART2)
			 NVIC_IRQ38_USART2_DIS();
		 else if (USARTx == USART3)
			 NVIC_IRQ39_USART3_DIS();

	 }

 }

 /* ================================================================
  * @Fn				-MCAL_UART_DeInit
  *
  * @brief 			-DeInitializes the UART(N) where N is the number of USART
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_UART_DeInit (USART_TypeDef * USARTx )
 {
	 if (USARTx == USART1)
	 {
		 NVIC_IRQ37_USART1_DIS();
		 RCC_USART1_CLK_DIS();

	 }
	 else if (USARTx == USART2)
	 {
		 NVIC_IRQ38_USART2_DIS();
		 RCC_USART2_CLK_DIS();
	 }
	 else if (USARTx == USART3)
	 {
		 NVIC_IRQ39_USART3_DIS();
		 RCC_USART3_CLK_DIS();
	 }
 }
 /* ================================================================
  * @Fn				-MCAL_UART_SendData
  *
  * @brief 			-Sends date through the UART(N) where N is the number of USART either by polling or interrupt
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @param [in] 	-pTXBuffer: Pointer to the buffer that will be sent
  *
  * @param [in] 	-Polling_Mechanism : enum to enable or disable the polling mechanism
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t * pTXBuffer , enum Polling_Mechanism PollingEN)
 {
	 //Wait till TXE flag is set in the SR
	 if (PollingEN == enable)
	 {
		 while(! (USARTx->SR & 1<<7 ) ) ;
	 }

	 //Check the USART_WordLength item for 9 Bit or 8 Bit in a Frame
	 if (_UART_Config->USART_PAYLOAD_LENGTH == USART_PAYLOAD_LENGTH_9Bits)
		 USARTx->DR =  *pTXBuffer & (uint16_t)0x1FF ;
	 else if (_UART_Config->USART_PAYLOAD_LENGTH == USART_PAYLOAD_LENGTH_8Bits)
		 USARTx->DR =  *pTXBuffer & (uint16_t)0xFF ;

 }

 /* ================================================================
  * @Fn				-MCAL_UART_WAIT_TC
  *
  * @brief 			-Waiting function till the transmission is completed
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void  MCAL_UART_WAIT_TC (USART_TypeDef * USARTx)
 {
	 //Wait till TC flag is set in the SR
	 while ( ! (USARTx->SR & 1 << 6));
 }

 /* ================================================================
  * @Fn				-MCAL_UART_ReceiveData
  *
  * @brief 			-Sends date through the UART(N) where N is the number of USART either by polling or interrupt
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @param [in] 	-pTXBuffer: Pointer to the buffer that will be sent
  *
  * @param [in] 	-Polling_Mechanism : enum to enable or disable the polling mechanism
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t * pRXBuffer , enum Polling_Mechanism PollingEN )
 {
	 //wait till RXNE flag is set in the SR
	 if(PollingEN == enable)
	 {
		 while( !(USARTx->SR & 1<<5));
	 }
	 //Check the USART_WordLength item for 9 Bit or 8 Bit in a Frame
	 if (_UART_Config->USART_PAYLOAD_LENGTH == USART_PAYLOAD_LENGTH_9Bits)
	 {
		 //No parity so all 9 bit are considered data
		 if(_UART_Config->USART_PARITY == USART_PARITY_NONE)
			 *((uint16_t*) pRXBuffer) = USARTx->DR;
		 else
			 *((uint16_t*) pRXBuffer) = (USARTx->DR & 0xFF);
	 }
	 else if (_UART_Config->USART_PAYLOAD_LENGTH == USART_PAYLOAD_LENGTH_8Bits)
	 {
		 //No parity so all 9 bit are considered data
		 if(_UART_Config->USART_PARITY == USART_PARITY_NONE)
			 *((uint16_t*) pRXBuffer) = (USARTx->DR & (uint8_t) 0xFF);
		 else
			 *((uint16_t*) pRXBuffer) = (USARTx->DR & (uint8_t) 0x7F);
	 }
 }

 /* ================================================================
  * @Fn				-MCAL_UART_GPIO_Set_Pins
  *
  * @brief 			-Sets the GPIO pins for USART
  *
  * @param [in] 	-USARTx: The instant of USART to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx )
 {
	 if (USARTx == USART1 )
	 {
		 GPIO_PinConfig_t PinCfg;
		 //PA9  TX
		 //PA10 RX
		 //PA11 CTS
		 //PA12 RTS

		 //PA9  TX
		 PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		 MCAL_GPIO_Init(GPIOA, PinCfg);

		 //PA10 RX
		 PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		 MCAL_GPIO_Init(GPIOA, PinCfg);

		 if(_UART_Config->USART_FLWCTRL == USART_FLWCTRL_CTS || _UART_Config->USART_FLWCTRL == USART_FLWCTRL_RTS_CTS  )
		 {
			 PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

		 }
		 else if(_UART_Config->USART_FLWCTRL == USART_FLWCTRL_RTS || _UART_Config->USART_FLWCTRL == USART_FLWCTRL_RTS_CTS  )
		 {
			 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

		 }

	 }
	 //Implement USART2 , USART3
 }
/* ================================================================= */

 //========================================================================
 //								ISR Functions
 //========================================================================

void USART1_IRQHandler (void)
{
	_UART_Config->P_IRQ_CALLBACK() ;
}


void USART2_IRQHandler (void)
{
	 _UART_Config->P_IRQ_CALLBACK() ;
}

void USART3_IRQHandler (void)
{
	 _UART_Config->P_IRQ_CALLBACK() ;
}

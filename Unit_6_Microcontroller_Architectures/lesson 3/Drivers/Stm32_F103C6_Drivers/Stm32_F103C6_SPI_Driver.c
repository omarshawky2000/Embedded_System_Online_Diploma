/*
 * Stm32_F103C6_SPI_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_GPIO_Driver.h"
 #include "Stm32_F103C6_SPI_Driver.h"
 #include "Stm32_F103C6_RCC_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 SPI_Config_t * _SPI_Config[2] = { NULL , NULL };

 //========================================================================
 //								PRIVATE MACROS
 //========================================================================
 #define SPI1_INDEX				0
 #define SPI2_INDEX				1

 #define SPI_SR_TXE				((uint8_t)0x02)			/*!< Transmit buffer Empty */
 #define SPI_SR_RXNE			((uint8_t)0x01)			/*!< Receive buffer Not Empty */

 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================


 //========================================================================
 //								       APIs
 //========================================================================
 /* ================================================================
  * @Fn				-MCAL_SPI_Init
  *
  * @brief 			-Initializes the SPI(N) where N is the number of SPI
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
  *
  * @param [in] 	-SPI_Config: Configuration structure of the SPI.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_SPI_Init (SPI_TypeDef * SPIx , SPI_Config_t * SPI_Config)
 {
	 //Safety for register to write the configuration to it then write it to the registers later
	 uint16_t tmpreg_CR1 = 0;
	 uint16_t tmpreg_CR2 = 0;

	 //enable the Clock for given SPI peripheral
	 if(SPIx == SPI1)
	 {
		 _SPI_Config[SPI1_INDEX] = SPI_Config ;
		 RCC_SPI1_CLK_EN();
	 }
	 else if (SPIx == SPI2)
	 {
		 _SPI_Config[SPI2_INDEX] = SPI_Config ;
		 RCC_SPI2_CLK_EN();
	 }

	 //Enable the SPI Module
	 // CR1 Register Bit 6
	 tmpreg_CR1 = (1<<6);

	 //Master or Slave
	 tmpreg_CR1 |= SPI_Config->SPI_DEVICE_MODE;

	 //SPI_Communication mode
	 tmpreg_CR1 |= SPI_Config->SPI_COMM_MODE;

	 //SPI_Frame_Format
	 tmpreg_CR1 |= SPI_Config->SPI_FRAME_FORMAT;

	 //SPI Data size
	 tmpreg_CR1 |= SPI_Config->SPI_DATA_SIZE;

	 //SPI Clock Polarity
	 tmpreg_CR1 |= SPI_Config->SPI_CLK_POLARITY;

	 //SPI Clock Phase
	 tmpreg_CR1 |= SPI_Config->SPI_CLK_PHASE;

	 //========================NSS=====================
	 if (SPI_Config->SPI_NSS == SPI_NSS_HW_MASTER_SS_OUT_EN)
	 {
		 tmpreg_CR2 |= SPI_Config->SPI_NSS ;
	 }
	 else if (SPI_Config->SPI_NSS == SPI_NSS_HW_MASTER_SS_OUT_DIS)
	 {
		 tmpreg_CR2 &= ~(SPI_Config->SPI_NSS) ;
	 }
	 else
	 {
		 tmpreg_CR1 |= SPI_Config->SPI_NSS ;
	 }
	 //SPI_BAUDRATEPRESCALER
	 tmpreg_CR1 |= SPI_Config->SPI_BR_PRESC;

	 if(SPI_Config->SPI_IRQ_ENABLE != SPI_IRQ_ENABLE_NONE)
	 {
		 //SPI_IRQ_Enable_define
		 tmpreg_CR2 |= SPI_Config->SPI_IRQ_ENABLE;
		 if(SPIx == SPI1)
		 {
			 NVIC_IRQ35_SPI1_EN();
		 }
		 else if (SPIx == SPI2)
		 {
			 NVIC_IRQ36_SPI2_EN();
		 }
	 }
	 SPI1->CR1 = tmpreg_CR1 ;
	 SPI1->CR2 = tmpreg_CR2 ;

 }

 /* ================================================================
  * @Fn				-MCAL_SPI_DeInit
  *
  * @brief 			-DeInitializes the SPI(N) where N is the number of SPI
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_SPI_DeInit (SPI_TypeDef * SPIx )
 {
	 if (SPIx == SPI1)
	 {
		 NVIC_IRQ35_SPI1_DIS();
		 RCC_SPI1_CLK_DIS();

	 }
	 else if (SPIx == SPI2)
	 {
		 NVIC_IRQ36_SPI2_DIS();
		 RCC_SPI2_CLK_DIS();
	 }
 }
 /* ================================================================
  * @Fn				-MCAL_SPI_SendData
  *
  * @brief 			-Sends date through the SPI(N) where N is the number of SPI either by polling or interrupt
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
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
 void MCAL_SPI_SendData(SPI_TypeDef * SPIx , uint16_t * pTXBuffer , enum SPI_Polling_Mechanism PollingEN)
 {
	 //Wait till TXE flag is set in the SR
	 if (PollingEN == SPI_POLL_enable)
	 {
		 while(! (SPIx->SR & SPI_SR_TXE ) ) ;
	 }

	 //SPI is ready to send data
	 SPIx->DR = *pTXBuffer;
 }

 /* ================================================================
  * @Fn				-MCAL_SPI_TX_RX
  *
  * @brief 			-Send and Receive Data from the SPI simultaneously
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
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
 void  MCAL_SPI_TX_RX (SPI_TypeDef * SPIx , uint16_t * pTXBuffer , enum SPI_Polling_Mechanism PollingEN)
 {
	 //Wait till TXE flag is set in the SR
	 if (PollingEN == SPI_POLL_enable)
	 {
		 while(! (SPIx->SR & SPI_SR_TXE ) ) ;
	 }
	 //SPI is ready to send data
	 SPIx->DR = *pTXBuffer;

	 //wait till RXNE flag is set in the SR
	 if(PollingEN == SPI_POLL_enable)
	 {
		 while( !(SPIx->SR & SPI_SR_RXNE));
	 }
	 *pTXBuffer = SPIx->DR;
 }

 /* ================================================================
  * @Fn				-MCAL_SPI_ReceiveData
  *
  * @brief 			-Sends date through the SPI(N) where N is the number of SPI either by polling or interrupt
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
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
 void MCAL_SPI_ReceiveData(SPI_TypeDef * SPIx , uint16_t * pRXBuffer , enum SPI_Polling_Mechanism PollingEN )
 {
	 //wait till RXNE flag is set in the SR
	 if(PollingEN == SPI_POLL_enable)
	 {
		 while( !(SPIx->SR & SPI_SR_RXNE));
	 }
	 *pRXBuffer = SPIx->DR;
 }

 /* ================================================================
  * @Fn				-MCAL_SPI_GPIO_Set_Pins
  *
  * @brief 			-Sets the GPIO pins for SPI
  *
  * @param [in] 	-SPIx: The instant of SPI to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx )
 {

	 if (SPIx == SPI1 )
	 {
		 GPIO_PinConfig_t PinCfg;
		 //PA4   SPI1_NSS
		 //PA5   SPI1_SCK
		 //PA6   SPI1_MISO
		 //PA7   SPI1_MOSI

		 //PA4  SPI1_NSS
		 if(_SPI_Config[SPI1_INDEX]->SPI_DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		 {
			 //PA4 : SPI1_NSS
			 switch (_SPI_Config[SPI1_INDEX]->SPI_NSS)
			 {
			 	 case SPI_NSS_HW_MASTER_SS_OUT_DIS:

					 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					 MCAL_GPIO_Init(GPIOA, PinCfg);

			 		 break;

			 	 case SPI_NSS_HW_MASTER_SS_OUT_EN:
					 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
					 MCAL_GPIO_Init(GPIOA, PinCfg);

			 		 break;
			 }
			 //PA5 : SPI1_CLK
			 PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

			 //PA6 : SPI1_MISO
			 PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

			 //PA7 : SPI1_MOSI
			 PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOA, PinCfg);


		 }
		 else // Slave
		 {
			 //PA4 : SPI1_NSS
			 if (_SPI_Config[SPI1_INDEX]->SPI_NSS == SPI_NSS_HW_SLAVE)
			 {
				 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				 MCAL_GPIO_Init(GPIOA, PinCfg);
			 }

			 //PA5 : SPI1_CLK
			 PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

			 //PA6 : SPI1_MISO
			 PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

			 //PA7 : SPI1_MOSI
			 PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOA, PinCfg);

		 }



	 }
	 if (SPIx == SPI2 )
	 {
		 GPIO_PinConfig_t PinCfg;
		 //PB12  SPI2_NSS
		 //PB13  SPI2_SCK
		 //PB14  SPI2_MISO
		 //PB15  SPI2_MOSI
		 if(_SPI_Config[SPI1_INDEX]->SPI_DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		 {
			 //PB12 : SPI1_NSS
			 switch (_SPI_Config[SPI1_INDEX]->SPI_NSS)
			 {
			 	 case SPI_NSS_HW_MASTER_SS_OUT_DIS:

					 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					 MCAL_GPIO_Init(GPIOB, PinCfg);

			 		 break;

			 	 case SPI_NSS_HW_MASTER_SS_OUT_EN:
					 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
					 MCAL_GPIO_Init(GPIOB, PinCfg);

			 		 break;
			 }
			 //PB13 : SPI1_CLK
			 PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOB, PinCfg);

			 //PB14 : SPI1_MISO
			 PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOB, PinCfg);

			 //PB15 : SPI1_MOSI
			 PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOB, PinCfg);


		 }
		 else // Slave
		 {
			 //PB12 : SPI1_NSS
			 if (_SPI_Config[SPI1_INDEX]->SPI_NSS == SPI_NSS_HW_SLAVE)
			 {
				 PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				 MCAL_GPIO_Init(GPIOB, PinCfg);
			 }

			 //PB13 : SPI1_CLK
			 PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOB, PinCfg);

			 //PB14 : SPI1_MISO
			 PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			 PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			 PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			 MCAL_GPIO_Init(GPIOB, PinCfg);

			 //PB15 : SPI1_MOSI
			 PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			 PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			 MCAL_GPIO_Init(GPIOB, PinCfg);

		 }
	 }
 }
/* ================================================================= */

 //========================================================================
 //								ISR Functions
 //========================================================================

void SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE =  ( (SPI1->SR & (1<<1)) >> 1);
	irq_src.RXNE = ( (SPI1->SR & (1<<0)) >> 0);
	irq_src.ERRI = ( (SPI1->SR & (1<<4)) >> 4);

	_SPI_Config[SPI1_INDEX]->P_IRQ_CALLBACK(irq_src) ;
}


void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE =  ( (SPI2->SR & (1<<1)) >> 1);
	irq_src.RXNE = ( (SPI2->SR & (1<<0)) >> 0);
	irq_src.ERRI = ( (SPI2->SR & (1<<4)) >> 4);

	 _SPI_Config[SPI2_INDEX]->P_IRQ_CALLBACK(irq_src) ;
}



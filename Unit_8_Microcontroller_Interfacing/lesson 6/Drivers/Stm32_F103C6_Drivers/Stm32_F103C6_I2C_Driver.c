/*
 * Stm32_F103C6_I2C_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_GPIO_Driver.h"
 #include "Stm32_F103C6_I2C_Driver.h"
 #include "Stm32_F103C6_RCC_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 I2C_Config_t  _I2C_Config[2] ;

 //========================================================================
 //								PRIVATE MACROS
 //========================================================================
 #define I2C1_INDEX				0
 #define I2C2_INDEX				1


 //========================================================================
 //								PRIVATE PROTOTYPES
 //========================================================================


 //========================================================================
 //								       APIs
 //========================================================================
 /* ================================================================
  * @Fn				-MCAL_I2C_Init
  *
  * @brief 			-Initializes the I2C(N) where N is the number of I2C
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-I2C_Config: Configuration structure of the I2C.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_Init (I2C_TypeDef * I2Cx , I2C_Config_t * I2C_Config)
 {
	 //Safety for register to write the configuration to it then write it to the registers later
	 uint16_t tmpreg_CCR = 0;
	 uint16_t tmpreg_CR1 = 0;
	 uint16_t tmpreg_CR2 = 0;
	 uint16_t tmpreg_OAR = 0;
	 uint32_t PCLK1 = 0;
	 uint16_t result = 0;
	 uint8_t  freq_range = 0;

	 //Enable the RCC Clock
	 if (I2Cx == I2C1)
	 {
		 _I2C_Config[I2C1_INDEX] = *I2C_Config;
		 RCC_I2C1_CLK_EN();

	 }
	 else
	 {
		 _I2C_Config[I2C2_INDEX] = *I2C_Config;
		 RCC_I2C2_CLK_EN();
	 }

	 if ( I2C_Config->I2C_MODE == I2C_MODE_I2C)
	 {
		 /*---------------- INIT TIMING --------------*/
		 // ---I2C_CR2.FREQ[5:0}: Peripheral clock frequency
		 /*---------- Get the I2Cx CR2 Value ---------*/
		 tmpreg_CR2 = I2Cx->CR2;
		 /*-------- Clear Frequency FREQ[5:0] --------*/
		 tmpreg_CR2 &= ~(I2C_CR2_FREQ_Msk);
		 /*------------- get PL Frequency ------------*/
		 PCLK1 = MCAL_RCC_GetPCLK1Freq();
		 /*- set frequency depending on the PCLK1 Value -*/
		 freq_range =  (uint8_t) (PCLK1 / 1000000);
		 tmpreg_CR2 |= freq_range;
		 //Write to CR2
		 I2Cx->CR2 = tmpreg_CR2 ;
		 // . Configure the clock control registers (I2C_CCR)
		 /* Disable the I2C Peripheral to configure time */
		 I2Cx->CR1 &= ~(I2C_CR1_PE);
		 /* Configure the I2C speed to standard mode */
		 if((I2C_Config->I2C_CLOCK_SPEED == I2C_SCLK_SM_100K)| (I2C_Config->I2C_CLOCK_SPEED == I2C_SCLK_SM_50K))
		 {
			 /*Standard mode speed calculate */
			 // Tclk/2 = CCR * TPCLK1
			 // CRR = Tclk / (2* TPCLK1)
			 // CRR = FPCLK1 / (2 * I2C_ClockFrequency)
			 result = (uint16_t)(PCLK1 / (I2C_Config->I2C_CLOCK_SPEED <<1 ) );
			 tmpreg_CCR |= result;

			 /*  Write to I2Cx_CCR */
			 I2Cx->CCR = tmpreg_CCR;
			 /*-------------I2C_TRISE Configuration ------------*/
			 // For instance : in SM mode, the maximum allowed SCL rise time is 1000 ns.
			 // If, in the I2C_CR2 register , the value  of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			 // therefore the TRISE[5:0] bits must be programmed with 09h.
			 I2Cx->TRISE = freq_range + 1 ;
		 }
		 else
		 {
			 //Fast mode not supported
		 }
		 /*---------- Get the I2Cx CR1 Value ---------*/
		 tmpreg_CR1 = I2Cx->CR1;

		 tmpreg_CR1 |= (uint16_t)(I2C_Config->I2C_ACK_CONTROL | \
				 	 	 	 	  I2C_Config->I2C_GENERALCALL_EN | \
								  I2C_Config->I2C_MODE | \
								  I2C_Config->I2C_STRETCH_MODE
		 	 	 	 	 	 	  );
		 I2Cx->CR1 = tmpreg_CR1 ;

		 if ( I2C_Config->I2C_SLAVE_ADDRESS.EN_Dual_ADD == 1)
		 {
			 tmpreg_OAR  = I2C_OAR2_ENDUAL ;
			 tmpreg_OAR |= I2C_Config->I2C_SLAVE_ADDRESS.SECONDARY_SLAVE_ADDRESS << I2C_OAR2_ADD2_Pos;
			 I2Cx->OAR2  = tmpreg_OAR;
		 }
		 tmpreg_OAR = 0;
		 tmpreg_OAR |= I2C_Config->I2C_SLAVE_ADDRESS.PRIMARY_SLAVE_ADDRESS << 1;
		 tmpreg_OAR |= I2C_Config->I2C_SLAVE_ADDRESS.I2C_ADDRESSING_MODE ;
		 I2Cx->OAR1  = tmpreg_OAR;
	 }
	 else
	 {
		 //SMBUS Not Supported
	 }

	 //Interrupt Mode (Slave Mode) Check callback pointer != NULL
	 if ( I2C_Config->P_SLAVE_EV_IRQ_CALLBACK != NULL)
	 {
		 //Enable all IRQs
		 I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
		 I2Cx->CR2 |= (I2C_CR2_ITERREN);
		 I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

		 if ( I2Cx == I2C1 )
		 {
			NVIC_IRQ31_I2C1_EV_EN();
			NVIC_IRQ32_I2C1_ER_EN();
		 }
		 else if ( I2Cx == I2C2 )
		 {
			 NVIC_IRQ33_I2C2_EV_EN();
			 NVIC_IRQ34_I2C2_ER_EN();
		 }

		 I2Cx->SR1 = 0 ;
		 I2Cx->SR2 = 0 ;

	 }
	 /*Enable the selected I2C peripheral*/
	 I2Cx->CR1  |= I2C_CR1_PE;


 }

 /* ================================================================
  * @Fn				-MCAL_I2C_DeInit
  *
  * @brief 			-DeInitializes the I2C(N) where N is the number of I2C
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_DeInit (I2C_TypeDef * I2Cx )
 {
	 if (I2Cx == I2C1)
	 {
		 NVIC_IRQ31_I2C1_EV_DIS();
		 NVIC_IRQ32_I2C1_ER_DIS();
		 RCC_I2C1_CLK_DIS();

	 }
	 else if (I2Cx == I2C2)
	 {
		 NVIC_IRQ33_I2C2_EV_DIS();
		 NVIC_IRQ34_I2C2_ER_DIS();
		 RCC_I2C2_CLK_DIS();
	 }
 }
 /* ================================================================
  * @Fn				-MCAL_I2C_MASTER_TX
  *
  * @brief 			-Sends date through the I2C(N) where N is the number of I2C by polling.
  *
  * @param [in] 	-Slave_ADD: The Address of the slave.
  *
  * @param [in] 	-DATA: Pointer to the buffer that will be sent.
  *
  * @param [in] 	-DATA_LENGTH : Length of data to send.
  *
  * @param [in] 	-STOP : enumto specifies if there is a stop condition or not.
  *
  * @param [in] 	-START : enumto specifies if there is repeated start or not.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_MASTER_TX ( I2C_TypeDef* I2Cx , uint16_t Slave_ADD , uint8_t* DATA , \
 						   uint32_t DATA_LENGTH , STOP_CONDITION STOP , RP_START START)
 {
	 uint32_t CNT = 0;
	 //Generate a start condition
	 MCAL_I2C_GENERATE_START(I2Cx , FS_ENABLE , START);

	 //Wait till EV5 is set
	 while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV5) );

	 //Sending the Address
	 MCAL_I2C_SEND_ADDRESS(I2Cx, Slave_ADD, I2C_DIRECTION_TRANSMIT);

	 //Wait till EV6 is set
	 while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV6) );

	 //Check for /* TRA , BUSY , MSL , TXE Flags */ Custom Event
	 while ( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, MASTER_BYTE_TRANSMITTING) ) ;

	 //Start Sending Data
	 for (CNT = 0 ; CNT < DATA_LENGTH ; CNT++)
	 {
		 /* Write in the DR Register the data to be sent*/
		 I2Cx->DR = DATA[CNT];
		 // Wait for EV8 (ACK)
		 while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV8) );
	 }

	 //while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV8_2) );

	 if ( STOP == With_STOP )
	 {
		 //7. Send Stop Condition
		 MCAL_I2C_GENERATE_STOP(I2Cx,FS_ENABLE);
	 }
 }
 /* ================================================================
  * @Fn				-MCAL_I2C_MASTER_RX
  *
  * @brief 			-Receives date through the I2C(N) where N is the number of I2C by polling.
  *
  * @param [in] 	-Slave_ADD: The Address of the slave.
  *
  * @param [in] 	-DATA: Pointer to the buffer that will be received.
  *
  * @param [in] 	-DATA_LENGTH : Length of data to receive.
  *
  * @param [in] 	-STOP : enumto specifies if there is a stop condition or not.
  *
  * @param [in] 	-START : enumto specifies if there is repeated start or not.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_MASTER_RX ( I2C_TypeDef* I2Cx , uint16_t Slave_ADD , uint8_t* DATA , \
 						   uint32_t DATA_LENGTH , STOP_CONDITION STOP , RP_START START)
 {
	 uint8_t index = I2Cx == I2C1 ? I2C1_INDEX : I2C2_INDEX	;

	 uint32_t CNT = 0;
	 //Generate a start condition
	 MCAL_I2C_GENERATE_START(I2Cx , FS_ENABLE , START);

	 //Wait till EV5 is set
	 while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV5) );

	 //Sending the Address
	 MCAL_I2C_SEND_ADDRESS(I2Cx, Slave_ADD, I2C_DIRECTION_RECIEVE);

	 //Wait till EV6 is set
	 while( ! MCAL_I2C_GETFLAG_STATUS(I2Cx, EV6) );

	 MCAL_I2C_ACKConfig(I2Cx ,ACK_EN);

	 if(DATA_LENGTH)
	 {
		 //Start Receiving Data
		 for (CNT = DATA_LENGTH ; CNT > 0 ; CNT--)
		 {
			 /* Write in the DR Register the data to be sent*/
			 *DATA = I2Cx->DR ;
			 //increment the buffer address
			 DATA++;
		 }

		 MCAL_I2C_ACKConfig(I2Cx ,ACK_DIS);
	 }

	 //Sending the Stop condition
	 if(STOP == With_STOP )
	 {
		MCAL_I2C_GENERATE_STOP(I2Cx, FS_ENABLE);
	 }

	 //Re-enabling the ACK
	 if(_I2C_Config[index].I2C_ACK_CONTROL == I2C_ACK_ENABLE)
	 {
		 MCAL_I2C_ACKConfig(I2Cx ,ACK_EN);
	 }
 }

 /* ================================================================
  * @Fn				-MCAL_I2C_GENERATE_START
  *
  * @brief 			-Send and Receive Data from the I2C simultaneously
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-STATE: functional state either enable or disable
  *
  * @param [in] 	-START : enum to for normal start or repeated start
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_GENERATE_START ( I2C_TypeDef* I2Cx , FUNCTIONAL_STATE STATE , RP_START START)
 {
	 //Check if the start is a repeated start on normal start

	 if(START != REPEATED_START)
	 {
		 //TODO support a timeout timer for a specific duration
		 //Check if the BUS is idle
		 while(MCAL_I2C_GETFLAG_STATUS(I2Cx, I2C_FLAG_BUSY) );

	 }

	 if (STATE != FS_DISABLE )
	 {
		 /* Generate a START Condition */
		  I2Cx->CR1 |= I2C_CR1_START;

	 }
	 else
	 {
		 /* disable  START Condition */
		  I2Cx->CR1 &= ~(I2C_CR1_START);

	 }
 }

 /* ================================================================
  * @Fn				-MCAL_I2C_GENERATE_STOP
  *
  * @brief 			-Send and Receive Data from the I2C simultaneously
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-STATE: functional state either enable or disable
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_GENERATE_STOP  ( I2C_TypeDef* I2Cx , FUNCTIONAL_STATE STATE )
 {

	 if (STATE != FS_DISABLE )
	 {
		 /* Generate a START Condition */
		  I2Cx->CR1 |= I2C_CR1_STOP;

	 }
	 else
	 {
		 /* disable  START Condition */
		  I2Cx->CR1 &= ~(I2C_CR1_STOP);

	 }
 }
 /* ================================================================
  * @Fn				-MCAL_I2C_ACKConfig
  *
  * @brief 			-Enable or Disables the ACK
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-ACK_ST: Disable or enable the ACK
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_ACKConfig( I2C_TypeDef* I2Cx ,ACKN_STATE ACK_ST)
 {

	 if (ACK_ST != ACK_DIS)
	 {
		 /* Generate a START Condition */
		  I2Cx->CR1 |= I2C_CR1_ACK;

	 }
	 else
	 {
		 /* disable  START Condition */
		  I2Cx->CR1 &= ~(I2C_CR1_ACK);

	 }
 }

 /* ================================================================
  * @Fn				-MCAL_I2C_GETFLAG_STATUS
  *
  * @brief 			-Check for flags in the status register
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-FLAG: the flag to be checked
  *
  * @param [in] 	-Polling_Mechanism : enum to enable or disable the polling mechanism
  *
  * @retval 		-Return the flag status High / Low
  *
  * Note			-NONE
  * =================================================================
  */
 FLAGSTATUS MCAL_I2C_GETFLAG_STATUS (I2C_TypeDef* I2Cx  , STATUS FLAG )
 {
	 volatile uint32_t dummyRead = 0;
	 uint32_t flag1 = 0;
	 uint32_t flag2 = 0;
	 uint32_t lastevent = 0;
	 FLAGSTATUS bitstatus = FLAG_LOW;
	 switch (FLAG)
	 {
	 case I2C_FLAG_BUSY:
		 if ((I2Cx->SR2) & (I2C_SR2_BUSY))
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;
		 break;

	 case EV5:
		 if ((I2Cx->SR1) & (I2C_SR1_SB))
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;
		 break;

	 case EV6:
		 if ((I2Cx->SR1) & (I2C_SR1_ADDR))
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;
		 dummyRead = I2Cx->SR2;
		 break;

	 case EV7:
		 if ((I2Cx->SR1) & (I2C_SR1_RXNE))
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;
		 dummyRead = I2Cx->SR2;
		 break;

	 case MASTER_BYTE_TRANSMITTING:
		 flag1 = I2Cx->SR1;
		 flag2 = I2Cx->SR2;
		 flag2 = flag2 << 16 ;
		 /* Get the last event value from I2C status register */
		 lastevent = ( flag1 | flag2) & ( (uint32_t) 0x00FFFFFF );
		 if ( (lastevent & FLAG)   == FLAG )
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;

		 break;

	 case EV8_1:
	 case EV8:
		 if ((I2Cx->SR1) & (I2C_SR1_TXE))
			 bitstatus = FLAG_HIGH;
		 else
			 bitstatus = FLAG_LOW;
		 dummyRead = I2Cx->SR2;
		 break;

	 }
	 dummyRead = I2Cx->SR2;

	 return bitstatus;
 }
 /* ================================================================
  * @Fn				-MCAL_I2C_SEND_ADDRESS
  *
  * @brief 			-Sends the address of the slave that will be communicated
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @param [in] 	-ADDRESS: address of the slave
  *
  * @param [in] 	-I2C_Direction : direction of the communication
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_SEND_ADDRESS ( I2C_TypeDef* I2Cx , uint16_t ADDRESS , I2C_DIR I2C_Direction)
 {

	 ADDRESS = ADDRESS << 1;

	 if (I2C_Direction == I2C_DIRECTION_TRANSMIT)
	 {
		 /* Set the address bit 0 for read */
		 ADDRESS |= 1<< 0 ;
	 }
	 else
	 {
		 /* reSet the address bit 0 for read */
		 ADDRESS &= ~(1<< 0) ;
	 }
	 /* Send the Address */
	 I2Cx->DR = ADDRESS ;
 }
 /* ================================================================
  * @Fn				-MCAL_I2C_GPIO_Set_Pins
  *
  * @brief 			-Sets the GPIO pins for I2C
  *
  * @param [in] 	-I2Cx: The instant of I2C to configured.
  *
  * @retval 		-NONE
  *
  * Note			-NONE
  * =================================================================
  */
 void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef * I2Cx )
 {
	 GPIO_PinConfig_t PIN_CFG;

	 if (I2Cx == I2C1 )
	 {
		 //PB6   I2C1_SCL
		 //PB7   I2C1_SDA
		 PIN_CFG.GPIO_PinNumber = GPIO_PIN_6;
		 PIN_CFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		 PIN_CFG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;

		 MCAL_GPIO_Init(GPIOB, PIN_CFG);

		 PIN_CFG.GPIO_PinNumber = GPIO_PIN_7;
		 MCAL_GPIO_Init(GPIOB, PIN_CFG);


	 }
	 if (I2Cx == I2C2 )
	 {
		 //PB10  I2C2_SCL
		 //PB11  I2C2_SDA
		 PIN_CFG.GPIO_PinNumber = GPIO_PIN_10;
		 PIN_CFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		 PIN_CFG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;

		 MCAL_GPIO_Init(GPIOB, PIN_CFG);

		 PIN_CFG.GPIO_PinNumber = GPIO_PIN_11;
		 MCAL_GPIO_Init(GPIOB, PIN_CFG);


	 }
 }
/* ================================================================= */

 //========================================================================
 //								ISR Functions
 //========================================================================

 void	I2C1_EV_IRQHandler    (void)
 {

 }

 void	I2C1_ER_IRQHandler    (void)
 {

 }

 void	I2C2_EV_IRQHandler    (void)
 {

 }

 void	I2C2_ER_IRQHandler    (void)
 {

 }


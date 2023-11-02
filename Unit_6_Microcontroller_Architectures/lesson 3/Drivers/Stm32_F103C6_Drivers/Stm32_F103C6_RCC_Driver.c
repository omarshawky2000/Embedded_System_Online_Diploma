/*
 * Stm32_F103C6_RCC_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Stm32_F103C6_RCC_Driver.h"

 //========================================================================
 //								PRIVATE Variables
 //========================================================================
 const uint8_t APBPrescTable[8U]  = { 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 }; //Shift 1 right

 const uint8_t AHBPrescTable[16U] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 /
 	 	 	 	 	 	 	 	 	  1 , 2 , 3 , 4 , 6 , 7 , 8 , 9}; //Shift 1 right

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
  * @Fn				-MCAL_RCC_GetSYS_CLKFreq
  *
  * @brief 			-Returns the System clock
  *
  * @param [in] 	-NONE
  *
  * @retval 		-The Frequency of system clock
  *
  * Note			-NONE
  * =================================================================
  */
 uint32_t MCAL_RCC_GetSYS_CLKFreq(void)
 {
	 switch((RCC->CFGR >> 2)& 0b11)
	 {
	 	 case 0:
	 		 return HSI_RC_CLK;
	 		 break;

	 	 case 1:
	 		 return HSE_Clock;
	 		 break;

	 	 case 2:
	 		 return 16000000;
	 		 break;

	 	 default:
	 		 return 0;
	 		 break;
	 }
 }
 /* ================================================================
  * @Fn				-MCAL_RCC_GetSYS_CLKFreq
  *
  * @brief 			-Returns the System clock
  *
  * @param [in] 	-NONE
  *
  * @retval 		-The Frequency of system clock
  *
  * Note			-NONE
  * =================================================================
  */
 uint32_t MCAL_RCC_GetHCLKFreq(void)
 {
	 return ( MCAL_RCC_GetSYS_CLKFreq() >> AHBPrescTable[(RCC->CFGR>>4) & 0b1111] );
 }
 /* ================================================================
  * @Fn				-MCAL_RCC_GetSYS_CLKFreq
  *
  * @brief 			-Returns the System clock
  *
  * @param [in] 	-NONE
  *
  * @retval 		-The Frequency of system clock
  *
  * Note			-NONE
  * =================================================================
  */
 uint32_t MCAL_RCC_GetPCLK1Freq(void)
 {
	 return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR>>8)&0b111] );
 }
 /* ================================================================
  * @Fn				-MCAL_RCC_GetSYS_CLKFreq
  *
  * @brief 			-Returns the System clock
  *
  * @param [in] 	-NONE
  *
  * @retval 		-The Frequency of system clock
  *
  * Note			-NONE
  * =================================================================
  */
 uint32_t MCAL_RCC_GetPCLK2Freq(void)
 {
	 return ( MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR>>11)&0b111] );
 }

/* ================================================================= */



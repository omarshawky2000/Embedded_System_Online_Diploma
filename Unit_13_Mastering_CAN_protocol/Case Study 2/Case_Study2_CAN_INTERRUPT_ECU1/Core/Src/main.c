/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "main.h"

#define ACC		 1
#define NO_ACC 	 0
CAN_HandleTypeDef hcan;

unsigned char TX_DATA[8] ;
uint8_t FrameNo = 0;
unsigned char  RX_DATA[8] ;
uint16_t RXID , RXDLC , ACC_ON;
uint8_t Speed ;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
void CAN_TX(uint32_t ID , uint8_t DLC , uint8_t* payload , uint8_t polling_EN);
void CAN_RX(uint16_t* ID , uint16_t* DLC , uint8_t* payload , uint8_t polling_EN);

//IRQs
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{

}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	//Receive the speed from ECU2
	CAN_RX(&RXID, &RXDLC, RX_DATA, 0);
	Speed = RX_DATA[0];

}
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	if( (hcan->ErrorCode & HAL_CAN_ERROR_TX_TERR0) == 0 )
	{
		//Mailbox 0 transmit failure due to transmit error
	}
}
//Standard_ID
//Data Frame
void CAN_TX(uint32_t ID , uint8_t DLC , uint8_t* payload , uint8_t polling_EN)
{
	uint8_t  num_free_txMailBox = 0;
	uint32_t pTxMailbox ;
	CAN_TxHeaderTypeDef pHeader;

	pHeader.DLC = DLC ;
	pHeader.IDE = CAN_ID_STD ;
	pHeader.RTR = CAN_RTR_DATA ;
	pHeader.StdId = ID ;

	num_free_txMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);

	if(num_free_txMailBox)
	{
		if(HAL_CAN_AddTxMessage(&hcan, &pHeader, payload, &pTxMailbox) != HAL_OK)
		{
			Error_Handler();
		}

		if(polling_EN)
		{
		//Wait until TX Mailbox is transmitted
		while ( HAL_CAN_IsTxMessagePending(&hcan, pTxMailbox) );
		}
	}

}


void CAN_RX_Filter_init(uint16_t STD_FILETR_ID , uint16_t STD_FILETR_MASK )
{
	CAN_FilterTypeDef sFilterConfig;

	sFilterConfig.FilterActivation = CAN_FILTER_ENABLE ;
	sFilterConfig.FilterBank = 0 ;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0 ;
	sFilterConfig.FilterIdHigh = STD_FILETR_ID <<5 ;
	sFilterConfig.FilterIdLow = 0x0000 ;
	sFilterConfig.FilterMaskIdHigh = STD_FILETR_MASK <<5 ;
	sFilterConfig.FilterMaskIdLow = 0x0000 ;

	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK ;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;

	if( HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK )
		{
			Error_Handler();
		}
}

void CAN_RX(uint16_t* ID , uint16_t* DLC , uint8_t* payload , uint8_t polling_EN)
{
	CAN_RxHeaderTypeDef pHeader;

	//Wait until receive CAN Message
	if(polling_EN)
	{
	while( HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0) == 0 );
	}


	if (HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &pHeader, payload) != HAL_OK)
		{
			Error_Handler();
		}

	*ID = pHeader.StdId;
	*DLC = pHeader.DLC;
}

int main(void)
{

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_CAN_Init();

  CAN_RX_Filter_init(0x3AB,0x7ff);

  //Enable your interrupts
  if( HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	  {
	  	  Error_Handler();
	  }

   //Start bxCAN (running state)
   if(HAL_CAN_Start(&hcan) != HAL_OK)
   {
 	  Error_Handler();
   }

   TX_DATA[0] = ACC ;
   while (1)
   {
	  HAL_Delay(1000);

 	  CAN_TX(0x030 , 1 , TX_DATA , 0) ; //TX and wait until TX is Done
 	  TX_DATA[0] ^= 1 ;	//Toggle the ACC
   }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_CAN_Init(void)
{

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 1;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();

}



void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

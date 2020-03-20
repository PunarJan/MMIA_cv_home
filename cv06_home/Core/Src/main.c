/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sct.h"
#include "1wire.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DELAY 750
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int16_t *temp_18b20;
static const uint16_t adc_array[] = {1690,1670,1650,1630,1610,1590,1580,1560,1540,1520,1510,1490,1470,1460,1440,1430,1410,1400,1390,1370,1360,1350,1330,1320,1310,1300,1290,1270,1260,1250,1240,1230,1220,1210,1200,1190,1180,1170,1160,1150,1140,1130,1130,1120,1110,1100,1090,1090,1080,1070,1060,1060,1050,1040,1040,1030,1020,1020,1010,1000,1000,990,990,980,980,970,960,960,950,950,940,940,930,930,920,920,920,910,910,900,900,890,890,890,880,880,870,870,870,860,860,850,850,850,840,840,840,830,830,830,820,820,820,810,810,810,800,800,800,800,790,790,790,780,780,780,780,770,770,770,770,760,760,760,750,750,750,750,740,740,740,740,740,730,730,730,730,720,720,720,720,710,710,710,710,700,700,700,700,700,690,690,690,690,690,680,680,680,680,670,670,670,670,670,660,660,660,660,660,650,650,650,650,650,640,640,640,640,640,640,630,630,630,630,630,620,620,620,620,620,620,610,610,610,610,610,600,600,600,600,600,600,590,590,590,590,590,590,580,580,580,580,580,580,570,570,570,570,570,570,560,560,560,560,560,560,550,550,550,550,550,550,550,540,540,540,540,540,540,540,530,530,530,530,530,530,530,520,520,520,520,520,520,520,510,510,510,510,510,510,510,500,500,500,500,500,500,500,500,490,490,490,490,490,490,490,490,480,480,480,480,480,480,480,480,470,470,470,470,470,470,470,470,460,460,460,460,460,460,460,460,460,450,450,450,450,450,450,450,450,440,440,440,440,440,440,440,440,440,440,430,430,430,430,430,430,430,430,430,420,420,420,420,420,420,420,420,420,410,410,410,410,410,410,410,410,410,410,400,400,400,400,400,400,400,400,400,400,390,390,390,390,390,390,390,390,390,390,380,380,380,380,380,380,380,380,380,380,370,370,370,370,370,370,370,370,370,370,360,360,360,360,360,360,360,360,360,360,360,350,350,350,350,350,350,350,350,350,350,340,340,340,340,340,340,340,340,340,340,330,330,330,330,330,330,330,330,330,330,330,320,320,320,320,320,320,320,320,320,320,310,310,310,310,310,310,310,310,310,310,310,300,300,300,300,300,300,300,300,300,300,290,290,290,290,290,290,290,290,290,290,290,280,280,280,280,280,280,280,280,280,280,280,270,270,270,270,270,270,270,270,270,270,270,260,260,260,260,260,260,260,260,260,260,260,250,250,250,250,250,250,250,250,250,250,250,240,240,240,240,240,240,240,240,240,240,240,230,230,230,230,230,230,230,230,230,230,230,230,220,220,220,220,220,220,220,220,220,220,220,220,210,210,210,210,210,210,210,210,210,210,210,210,200,200,200,200,200,200,200,200,200,200,200,200,190,190,190,190,190,190,190,190,190,190,190,190,180,180,180,180,180,180,180,180,180,180,180,180,170,170,170,170,170,170,170,170,170,170,170,170,160,160,160,160,160,160,160,160,160,160,160,160,150,150,150,150,150,150,150,150,150,150,150,150,150,140,140,140,140,140,140,140,140,140,140,140,130,130,130,130,130,130,130,130,130,130,130,130,120,120,120,120,120,120,120,120,120,120,120,120,110,110,110,110,110,110,110,110,110,110,110,100,100,100,100,100,100,100,100,100,100,100,90,90,90,90,90,90,90,90,90,90,90,80,80,80,80,80,80,80,80,80,80,70,70,70,70,70,70,70,70,70,70,70,60,60,60,60,60,60,60,60,60,60,50,50,50,50,50,50,50,50,50,50,40,40,40,40,40,40,40,40,40,40,30,30,30,30,30,30,30,30,30,30,20,20,20,20,20,20,20,20,20,20,10,10,10,10,10,10,10,10,10,0,0,0,0,0,-0,-0,-0,-0,-0,-10,-10,-10,-10,-10,-10,-10,-10,-10,-20,-20,-20,-20,-20,-20,-20,-20,-20,-30,-30,-30,-30,-30,-30,-30,-30,-30,-40,-40,-40,-40,-40,-40,-40,-40,-40,-50,-50,-50,-50,-50,-50,-50,-50,-50,-60,-60,-60,-60,-60,-60,-60,-60,-70,-70,-70,-70,-70,-70,-70,-70,-80,-80,-80,-80,-80,-80,-80,-80,-90,-90,-90,-90,-90,-90,-90,-90,-100,-100,-100,-100,-100,-100,-100,-110,-110,-110,-110,-110,-110,-110,-120,-120,-120,-120,-120,-120,-120,-130,-130,-130,-130,-130,-130,-140,-140,-140,-140,-140,-140,-150,-150,-150,-150,-150,-150,-160,-160,-160,-160,-160,-160,-170,-170,-170,-170,-170,-180,-180,-180,-180,-180,-190,-190,-190,-190,-190,-200,-200,-200,-200,-200,-210,-210,-210,-210,-220,-220,-220,-220,-220,-230,-230,-230,-230,-240,-240,-240,-240,-250,-250,-250,-250,-260,-260,-260,-260,-270,-270,-270,-270,-280,-280,-280,-280,-290,-290,-290,-300,-300,-300,-300,-310,-310,-310,-310,-320,-320,-320,-330,-330,-330,-330,-340,-340,-340,-350,-350,-350,-360,-360,-360,-360,-370,-370,-370,-380,-380,-380,-380,-390,-390,-390,-400,-400,-400,-400,-410,-410,-410,-410,-420,-420,-420,-420,-430,-430,-430,-430,-440};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  OWInit();
  HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start(&hadc);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  static enum { SHOW_DS18B20, SHOW_NTC} state = SHOW_DS18B20;

	  if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin) == 0)
	  {
		  state = SHOW_DS18B20;
		  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
	  }
	  else if (HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin) == 0)
	  {
		  state = SHOW_NTC;
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
		  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
	  }

	  if (state == SHOW_DS18B20)
	  {
		  static int16_t temp_DS18B20;

		  OWConvertAll();
		  temp_DS18B20 = OWReadTemperature(temp_18b20);
		  sct_value(temp_DS18B20, 1);
		  HAL_Delay(750);

	  }

	  if (state == SHOW_NTC)
	  {
		  static int16_t temp_NTC;

		  temp_NTC = adc_array[HAL_ADC_GetValue(&hadc)];
		  sct_value(temp_NTC, 0);
		  HAL_Delay(750);
	  }
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_10B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|SCT_CLK_Pin|SCT_SDI_Pin|SCT_NLA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DQ_GPIO_Port, DQ_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : S2_Pin S1_Pin */
  GPIO_InitStruct.Pin = S2_Pin|S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin SCT_CLK_Pin SCT_SDI_Pin SCT_NLA_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|SCT_CLK_Pin|SCT_SDI_Pin|SCT_NLA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DQ_Pin */
  GPIO_InitStruct.Pin = DQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DQ_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

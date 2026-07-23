/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {

  uint32_t psc;
  uint32_t duration;

} note_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BPM 120.0f

#define BPS (BPM / 60.0f)
#define BPS_MS (1000.0f / BPS)

#define WHOLE_NOTE 4.0f * BPS_MS
#define HALF_NOTE 2.0f * BPS_MS
#define QUARTER_NOTE 1.0f * BPS_MS
#define EIGHTH_NOTE 0.5f * BPS_MS
#define SIXTEENTH_NOTE 0.25f * BPS_MS

/*
  Piano Pitch frequencies
  A0 27.5
  B0 30.868
  C1 32.703
  D1 36.708
  E1 41.203
  F1 43.654
  G1 48.999
  A1 55.000
  B1 61.735
  C2 65.406
  D2 73.416
  E2 82.407
  F2 87.307
  G2 97.999
  A2 110.00
  B2 123.47
  C3 130.81
  D3 146.83
  E3 164.81
  F3 174.61
  G3 196.00
  A3 220.00
  B3 246.94
  C4 261.63
  D4 293.67
  E4 329.63
  F4 349.23
  G4 392.00
  A4 440.00
  B4 493.88
  C5 523.25
  D5 587.33
  E5 659.26
  F5 698.46
  G5 783.99
  A5 880.00
  B5 987.77
  C6 1046.5
  D6 1174.7
  E6 1318.5
  F6 1396.9
  G6 1568.0
  A6 1760.0
  B6 1975.5
  C7 2093.0
  D7 2349.3
  E7 2637.0
  F7 2793.0
  G7 3136.0
  A7 3520.0
  B7 3951.1
  C8 4186.0
*/

// PSC values for TIM1 at ARR = 99 and f_timer = 60 MHz
#define REST 0 // not a real PSC value. Check for 0 to set Duty Cycle to 0%
#define A0 21817
#define B0 19437
#define C1 18346
#define D1 16344
#define E1 14561
#define F1 13743
#define G1 12244
#define A1 10908
#define B1 9718
#define C2 9172
#define D2 8172
#define E2 7280
#define F2 6871
#define G2 6122
#define A2 5454
#define B2 4858
#define C3 4586
#define D3 4085
#define E3 3640
#define F3 3435
#define G3 3060
#define A3 2726
#define B3 2429
#define C4 2292
#define D4 2042
#define E4 1819
#define F4 1717
#define G4 1530
#define A4 1363
#define B4 1214
#define C5 1146
#define D5 1021
#define E5 909
#define F5 858
#define G5 764
#define A5 681
#define B5 606
#define C6 572
#define D6 510
#define E6 454
#define F6 429
#define G6 382
#define A6 340
#define B6 303
#define C7 286
#define D7 254
#define E7 227
#define F7 214
#define G7 190
#define A7 169
#define B7 151
#define C8 142


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
#define SONG_SIZE 64

note_t song[SONG_SIZE] = {
  {A0, EIGHTH_NOTE},
  {B0, EIGHTH_NOTE},
  {C1, QUARTER_NOTE},
  {D1, EIGHTH_NOTE},
  {E1, EIGHTH_NOTE},
  {F1, EIGHTH_NOTE},
  {G1, EIGHTH_NOTE},
  {A1, EIGHTH_NOTE},
  {B1, EIGHTH_NOTE},
  {C2, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C2, EIGHTH_NOTE},
  {D2, EIGHTH_NOTE},
  {E2, EIGHTH_NOTE},
  {F2, EIGHTH_NOTE},
  {G2, EIGHTH_NOTE},
  {A2, EIGHTH_NOTE},
  {B2, EIGHTH_NOTE},
  {C3, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C3, EIGHTH_NOTE},
  {D3, EIGHTH_NOTE},
  {E3, EIGHTH_NOTE},
  {F3, EIGHTH_NOTE},
  {G3, EIGHTH_NOTE},
  {A3, EIGHTH_NOTE},
  {B3, EIGHTH_NOTE},
  {C4, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C4, EIGHTH_NOTE},
  {D4, EIGHTH_NOTE},
  {E4, EIGHTH_NOTE},
  {F4, EIGHTH_NOTE},
  {G4, EIGHTH_NOTE},
  {A4, EIGHTH_NOTE},
  {B4, EIGHTH_NOTE},
  {C5, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C5, EIGHTH_NOTE},
  {D5, EIGHTH_NOTE},
  {E5, EIGHTH_NOTE},
  {F5, EIGHTH_NOTE},
  {G5, EIGHTH_NOTE},
  {A5, EIGHTH_NOTE},
  {B5, EIGHTH_NOTE},
  {C6, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C6, EIGHTH_NOTE},
  {D6, EIGHTH_NOTE},
  {E6, EIGHTH_NOTE},
  {F6, EIGHTH_NOTE},
  {G6, EIGHTH_NOTE},
  {A6, EIGHTH_NOTE},
  {B6, EIGHTH_NOTE},
  {C7, QUARTER_NOTE},
  {REST, QUARTER_NOTE},
  {C7, EIGHTH_NOTE},
  {D7, EIGHTH_NOTE},
  {E7, EIGHTH_NOTE},
  {F7, EIGHTH_NOTE},
  {G7, EIGHTH_NOTE},
  {A7, EIGHTH_NOTE},
  {B7, EIGHTH_NOTE},
  {C8, QUARTER_NOTE}
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
static void play_song(TIM_TypeDef* TIMX, uint32_t song_size, note_t *song) ;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_ADC1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    play_song(TIM1, SONG_SIZE, song);
    HAL_Delay(1000);
    /* TIM1->PSC = C4;
    HAL_Delay(1000);
    TIM1->PSC = G4;
    HAL_Delay(1000); */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL15;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 4999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 99;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void play_song(TIM_TypeDef* TIMX, uint32_t song_size, note_t *song) {
  TIMX->CCR1 = 50; // start playing
  for (uint16_t note = 0; note < song_size; note++) {
    if (0 == song[note].psc) {
      TIMX->CCR1 = 0; // stop playing
    } else {
      TIMX->CCR1 = 50; // keep playing
      TIMX->PSC = song[note].psc;
    }
    HAL_Delay(song[note].duration);
  }
  TIMX->CCR1 = 0; // stop playing
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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

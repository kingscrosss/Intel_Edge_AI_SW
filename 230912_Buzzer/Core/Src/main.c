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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define Do  383     // prescaler
#define Re  340
#define Mi  304
#define Fa  287
#define Sol 255
#define Ra  227
#define si  203
#define DDO 191     // High Do

#define tNote 200
#define hNote 300
#define qNote 600
#define wNote 1800

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

enum {C,Cs,D,Ds,E,F,Fs,G,Gs,A,As,B}; // pitch
// octave, pitch
int scale[8][12] = { {33 ,35 ,37 ,39 ,41 ,44 ,46 ,49 ,52 ,55 ,58 ,62 },
    {65 ,69 ,73 ,78 ,82 ,87 ,92 ,98 ,104 ,110 ,117 ,123 },
    {131 ,139 ,147 ,156 ,165 ,175 ,185 ,196 ,208 ,220 ,233 ,247 },
    {262 ,277 ,294 ,311 ,330 ,349 ,370 ,392 ,415 ,440 ,466 ,494 },
    {523 ,554 ,587 ,622 ,659 ,698 ,740 ,784 ,831 ,880 ,932 ,988 },
    {1047 ,1109 ,1175 ,1245 ,1319 ,1397 ,1480 ,1568 ,1661 ,1760 ,1865 ,1976 },
    {2093 ,2217 ,2349 ,2489 ,2637 ,2794 ,2960 ,3136 ,3322 ,3520 ,3729 ,3951 },
    {4186 ,4435 ,4699 ,4978 ,5274 ,5588 ,5920 ,6272 ,6645 ,7040 ,7459 ,7902 } };



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

//  uint16_t song_pitch[] = {C,E,G,C,E,G,A,A,A,G,F,F,F,E,E,E,D,D,D,C};
//  uint16_t song_octave[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//  uint16_t time[]={qNote,qNote,qNote,qNote,qNote,qNote,qNote,qNote,qNote,wNote,qNote,qNote,qNote,qNote,qNote,qNote,qNote,qNote,qNote,wNote};

//  // LG sound
//  uint16_t song_pitch[] = {C, F, E, D, C, A, B-1, C, D, G, A, B-1, A, C, C, F, E, D, C, F, F, G, F, E, D, E, F};
//  uint16_t song_octave[] = {2,2,2,2,2,1,1,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
//  uint16_t time[] = {qNote,tNote,tNote,tNote,qNote,qNote,tNote,tNote,tNote,tNote,tNote,tNote,qNote,qNote,qNote,tNote,tNote,tNote,qNote,qNote,tNote,tNote,tNote,tNote,tNote,tNote,wNote};

  // graful ghoust
  uint16_t song_pitch[] = {};
  uint16_t song_octave[] = {2,2,2,2,2,1,1,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
  uint16_t time[] = {};


  for(int i=0;i<=sizeof(song_pitch);i++){
    TIM4->PSC = (int)100000/scale[song_octave[i]+2][song_pitch[i]]-1;
    HAL_Delay(time[i]);
    TIM4->CCR1 = 0;     // sound off
    HAL_Delay(10);
    TIM4->CCR1 = 500;   // sound on
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//    TIM4->PSC = 383;
//    HAL_Delay(600);
//    TIM4->CCR1 = 0; // sound off
//    HAL_Delay(10);
//    TIM4->CCR1 = 500; // sound on
    TIM4->CCR1 = 0; // sound off
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxData[3];
//uint8_t rxData2[1];
GPIO_TypeDef *led2_GPIO[8] =  // pin order: PA_5,6,7, PB_6, PC_7, PA_9,8, PB_10
    {
        GPIOA, GPIOA, GPIOA, GPIOB,
        GPIOC, GPIOA, GPIOA, GPIOB
    };
GPIO_TypeDef *led2_GPIO_PIN[8] =  // pin order: PA_5,6,7, PB_6, PC_7, PA_9,8, PB_10
    {
        GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_6,
        GPIO_PIN_7, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_10
    };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){    // cannot use Delay!
  HAL_UART_Receive_IT(&huart2, rxData, 1);
  HAL_UART_Receive_IT(&huart1, rxData, sizeof(rxData));

  static int state=0;
  // LED_All_Off(); // remove it!

  if(rxData[0]=='0'){
    LED_All_Off();
  }
  else if(rxData[0]=='a'){
    LED_All_On();
  }

  // All Off 1 LED On
  else if(rxData[0]=='b'){
    LED_All_Off();
    HAL_GPIO_WritePin(led2_GPIO[state], led2_GPIO_PIN[state], 1);
    state++;
    if(state>8) state = 0;
  }
  else if(rxData[0]=='c'){
    LED_All_Off();
    if(state>0) state--;
    HAL_GPIO_WritePin(led2_GPIO[state], led2_GPIO_PIN[state], 1);
    if(state<=0) state = 8;
  }

  // All ON 1 LED off
  else if(rxData[0]=='d'){
    LED_All_On();
    HAL_GPIO_WritePin(led2_GPIO[state], led2_GPIO_PIN[state], 0);
    state++;
    if(state>=8) state = 0;
  }
  else if(rxData[0]=='e'){
    if(state>0) state--;
    LED_All_On();
    HAL_GPIO_WritePin(led2_GPIO[state], led2_GPIO_PIN[state], 0);
    if(state<=0) state = 8;
  }

  // Toggle
  else if(rxData[0]=='t'){
    for(int j=0;j<8;j++){
      HAL_GPIO_TogglePin(led2_GPIO[j], led2_GPIO_PIN[j]);
    }
  }

  // rxData[0]='\0';
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LED_All_On(){
  for(int j=0; j<8; j++){
    HAL_GPIO_WritePin(led2_GPIO[j], led2_GPIO_PIN[j], 1);
  }
}
void LED_All_Off(){
  for(int j=0; j<8; j++){
      HAL_GPIO_WritePin(led2_GPIO[j], led2_GPIO_PIN[j], 0);
    }
}
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
  LED_All_Off();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, rxData, 1);
  HAL_UART_Receive_IT(&huart1, rxData, sizeof(rxData));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

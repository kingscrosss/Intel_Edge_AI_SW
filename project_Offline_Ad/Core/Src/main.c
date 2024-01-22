/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
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
typedef struct Fan{
    uint8_t Tracking_flag;  // init = 0
    uint8_t DC_State;       // 0
    int16_t DC_speed;       // 0? 500?
    uint8_t Servo_State;    // 0
    int16_t Servo_loc;      // 50
}fan;

// UART
uint8_t rxData;

// Servo Motor
//static uint8_t rot = 50;		// Init location
static uint8_t Tracking_flag =0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  uint8_t DC_cap = 100;
  uint8_t Servo_cap = 10;
  int16_t DC_speed = TIM3->CCR1;
  int16_t Servo_loc = TIM3->CCR2;

  if(huart->Instance==USART2){
    HAL_UART_Transmit_IT(&huart2, &rxData, sizeof(rxData));

    if(rxData == 'q')   // Stop
    {
      TIM3->CCR1 = 0;
//      TIM3->CCR2 = Servo_loc;
//      Tracking_flag = 0;
    }
    else if(rxData == 'e')      // FAN(DC) restart
    {
      TIM3->CCR1 = 500;
//      TIM3->CCR2 = Servo_loc;
      Tracking_flag = !Tracking_flag;

    }
    else if(rxData == 'w')      // FAN(DC) speed increse
    {
      DC_speed += DC_cap;
      if(DC_speed > 1000){
        DC_speed = 999;
      }
      TIM3->CCR1 = DC_speed;
    }
    else if(rxData == 's'){
      DC_speed -= DC_cap;
      if(DC_speed <= 0){
        DC_speed = 0;
      }
      TIM3->CCR1 = DC_speed;
    }
    else if(rxData == 'a'){
      Servo_loc += Servo_cap;
      if(Servo_loc >= 250){
        Servo_loc = 250;
      }
      TIM3->CCR2 = Servo_loc;
    }
    else if(rxData == 'd'){
      Servo_loc -= Servo_cap;
      if(Servo_loc <= 50){
        Servo_loc = 50;
      }
      TIM3->CCR2 = Servo_loc;
    }

    HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
  }
}
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
  static int16_t i=50;					// servo 50~250, 1~2ms
  static int8_t dir=1;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  // Motor
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // DC motor
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // servo motor

  // UART
  HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
//  HAL_UART_Transmit_DMA(&huart2, txData, sizeof(txData));

  // CCR
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 50;
  HAL_Delay(1000);
  // DC(FAN) Start
  TIM3->CCR1 = 500;
  Tracking_flag = 1;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  	// Servo
    if(Tracking_flag){
      TIM3->CCR1 = 500;
      TIM3->CCR2 = i;
      if(i<=50) dir=1;
      if(i>=250) dir=-1;
      i += dir*1;
    }


    HAL_Delay(10);


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

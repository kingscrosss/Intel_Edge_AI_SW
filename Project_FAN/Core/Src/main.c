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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "I2C_LCD.h"
#include "LED.h"

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
// speed
char *level = "Stop";

// timer
uint8_t tim_flag=0;
int timer = 0;
uint8_t timer_s = 0;
uint8_t timer_m = 0;

// Servo motor for rotate
uint8_t rotate = 0;
char *rotate_State = "OFF";

// LED
static GPIO led = {
    {GPIOC, GPIOC, GPIOC},
    {GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12}
};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void FAN_Init(){
	level = "STOP";     // LCD STOP
  TIM3->CCR1 = 0;     // FAN STOP
  changeLED(led, 0);  // LED ALL OFF
  rotate = 0;					// Fan rotate STOP
  rotate_State = "OFF";
  tim_flag = 0;				// Timer Init
  timer = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

  static uint32_t before_tick = 0;

  // Speed
  if(GPIO_Pin == BT_Stop_Pin){
  		FAN_Init();
  }
  if(GPIO_Pin == BT_Level1_Pin){
    level = " 01 ";     // LCD
    TIM3->CCR1 = 400;   // FAN
    changeLED(led, 1);  // LED
  }
  if(GPIO_Pin == BT_Level2_Pin){
    level = " 02 ";     // LCD
    TIM3->CCR1 = 700;   // FAN
    changeLED(led, 2);
  }
  if(GPIO_Pin == BT_Level3_Pin){
    level = " 03 ";     // LCD
    TIM3->CCR1 = 900;   // FAN
    changeLED(led, 3);  // LED
  }

  // rotate
  if(GPIO_Pin == BT_Rotate_Pin){
  	if(HAL_GetTick() - before_tick >= 300)		// Debounce
  	{
  		before_tick = HAL_GetTick();

    	if(TIM3->CCR1 != 0){       	// if Fan is work
        rotate = !rotate;
    	}else rotate = 0;
      if(rotate == 0) {
        rotate_State = "OFF";
      }
      else if(rotate == 1)	rotate_State = "ON ";
  	}
  }

  // Timer
  if(GPIO_Pin == BT_TIM_Pin){
  	if(HAL_GetTick() - before_tick >= 300)		// Debounce: 300ms
  	{
  		before_tick = HAL_GetTick();

  		if(TIM3->CCR1 != 0){       	// if Fan is work
  			tim_flag = 1;
  			timer += 10;
  		}
  	}
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if(htim->Instance == htim11.Instance){
  	static int count = 0;
  	if(tim_flag == 1){
  		count++;
  		if(timer<=count){
  			FAN_Init();
  			count = 0;
  		}
  		timer_m = (timer-count)/60;
  		timer_s = (timer-count)%60;
  	}
  	else{		//  if(tim_flag == 0)
  		count = 0;
  		timer_m = 0;
  		timer_s = 0;
  	}
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  // Timer
  HAL_TIM_Base_Start_IT(&htim11);

  // Motor
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // DC motor
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // servo motor

  // OCR = 0
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 0;

  // LED = 0
  changeLED(led, 0);

  //LCD
  lcd_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // LCD
    char temp_line1[20];
    char temp_line2[20];

    sprintf(temp_line1, "[%4s] Rot: %s", level, rotate_State);
    sprintf(temp_line2, "Timer: %2dm %2ds  ", timer_m, timer_s);

    lcd_put_cur(0, 0);
    lcd_send_string(temp_line1);
    lcd_put_cur(1, 0);
    lcd_send_string(temp_line2);

    HAL_Delay(50);

    // Servo Motor
    static uint8_t rot = 50;
    static int8_t i=1;

    if(rotate){
      if(rot>=250){
      	i=-1;
      }
      if(rot<=50){
      	i=1;
      }
      rot += i*5;
      TIM3->CCR2 = rot;
      //HAL_Delay(5);
    }
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

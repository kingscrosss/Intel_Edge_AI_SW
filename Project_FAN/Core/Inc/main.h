/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BT_TIM_Pin GPIO_PIN_4
#define BT_TIM_GPIO_Port GPIOC
#define BT_TIM_EXTI_IRQn EXTI4_IRQn
#define BT_Stop_Pin GPIO_PIN_1
#define BT_Stop_GPIO_Port GPIOB
#define BT_Stop_EXTI_IRQn EXTI1_IRQn
#define BT_Rotate_Pin GPIO_PIN_2
#define BT_Rotate_GPIO_Port GPIOB
#define BT_Rotate_EXTI_IRQn EXTI2_IRQn
#define BT_Level3_Pin GPIO_PIN_13
#define BT_Level3_GPIO_Port GPIOB
#define BT_Level3_EXTI_IRQn EXTI15_10_IRQn
#define BT_Level2_Pin GPIO_PIN_14
#define BT_Level2_GPIO_Port GPIOB
#define BT_Level2_EXTI_IRQn EXTI15_10_IRQn
#define BT_Level1_Pin GPIO_PIN_15
#define BT_Level1_GPIO_Port GPIOB
#define BT_Level1_EXTI_IRQn EXTI15_10_IRQn
#define LED_Level1_Pin GPIO_PIN_10
#define LED_Level1_GPIO_Port GPIOC
#define LED_Level2_Pin GPIO_PIN_11
#define LED_Level2_GPIO_Port GPIOC
#define LED_Level3_Pin GPIO_PIN_12
#define LED_Level3_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

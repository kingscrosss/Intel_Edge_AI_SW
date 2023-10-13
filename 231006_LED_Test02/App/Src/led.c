/*
 * led.c
 *
 *  Created on: Oct 6, 2023
 *      Author: user
 */

#include "led.h"

LED_TBL_CFG led_cfg[LED_MAX_CH] =
    {
	{GPIOA, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOC, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOA, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},
	{GPIOB, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET}
    };


bool ledInit(void)
{
  return true;
}

void ledOn(uint8_t ch)
{
  if(ch >= LED_MAX_CH) return;
  HAL_GPIO_WritePin(led_cfg[ch].port, led_cfg[ch].pin, led_cfg[ch].on_stater);
}

void ledOff(uint8_t ch)
{
  if(ch >= LED_MAX_CH) return;
  HAL_GPIO_WritePin(led_cfg[ch].port, led_cfg[ch].pin, led_cfg[ch].off_stater);
}

void ledToggle(uint8_t ch)
{
  if(ch >= LED_MAX_CH) return;
  HAL_GPIO_TogglePin(led_cfg[ch].port, led_cfg[ch].pin);
}

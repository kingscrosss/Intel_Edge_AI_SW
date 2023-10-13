/*
 * Button.c
 *
 *  Created on: Sep 6, 2023
 *      Author: user
 */


#include "Button.h"


void Button_Init(Button *btn, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  btn->GPIOx = GPIOx;
  btn->GPIO_Pin = GPIO_Pin;
  btn->prevState = RELEASED;
}

uint8_t Button_getState(Button *btn)
{
  uint8_t curState = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);
  if(curState == PUSHED && btn->prevState == RELEASED)
  {
    btn->prevState = PUSHED;
    return ACT_PUSH;
  }
  else if(curState != PUSHED && btn->prevState == PUSHED)
  {
    btn->prevState = RELEASED;
    return ACT_RELEASE;
  }
  return NO_ACT;
}

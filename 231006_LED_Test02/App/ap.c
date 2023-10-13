/*
 * ap.c
 *
 *  Created on: Oct 6, 2023
 *      Author: user
 */

#include "ap.h"

uint8_t state = 0;


// 하드웨어 Init
void apInit(void)
{

  ledInit();
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_10)
  {
    state=0;
  }
  if(GPIO_Pin == GPIO_PIN_11)
  {
    state=1;
  }
  if(GPIO_Pin == GPIO_PIN_12)
  {
    state=2;
  }

}

// main 함수
void apMain(void)
{

  while(1)
  {
    switch(state)
    {
      case 0:
	for(int i=0; i<8; i++)
	{
	  ledOn(i);
	  HAL_Delay(150);
	  ledOff(i);
	}
	break;
      case 1:
	for(int i=7; i>=0; i--)
	{
	  ledOn(i);
	  HAL_Delay(150);
	  ledOff(i);
	}
	break;
      case 2:
	for(int i=0; i<8; i++)
	{
	  ledOn(i);
	  HAL_Delay(150);
	  ledOff(i);
	}
	for(int i=7; i>=0; i--)
	{
	  ledOn(i);
	  HAL_Delay(150);
	  ledOff(i);
	}
	break;
      default:
    	  break;
    }
  }
}

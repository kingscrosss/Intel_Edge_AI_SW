/*
 * ap.c
 *
 *  Created on: Oct 6, 2023
 *      Author: user
 */

#include "ap.h"

// 하드웨어 Init
void apInit(void)
{
  ledInit();
}

// main 함수
void apMain(void)
{
  while(1)
  {
    ledToggle(_DEF_LED_CH1);
    delay(1000);
  }
}

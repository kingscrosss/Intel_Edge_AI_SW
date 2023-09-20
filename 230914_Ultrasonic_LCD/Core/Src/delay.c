/*
 * delay.c
 *
 *  Created on: Sep 12, 2023
 *      Author: user
 */
// ctrl+Tap: to move .h file

#include "delay.h"

void delay_us(uint16_t us){
  __HAL_TIM_SET_COUNTER(&htim3,0);     // _*2 두 개!, 타이머카운터10의 시작을 0부터 하겠다.
  while((__HAL_TIM_GET_COUNTER(&htim3))<us);       // 주어진 함수를 계속 읽어오겠다. 셋팅을 update event를 1us로 잡아놨으니까.
}


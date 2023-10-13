/*
 * led.h
 *
 *  Created on: Oct 6, 2023
 *      Author: user
 */

#ifndef INC_LED_H_
#define INC_LED_H_


#include "def.h"


#define LED_MAX_CH	1	// led 갯수
#define _DEF_LED_CH1	0	// 배열 정의

typedef struct{
  GPIO_TypeDef *port;
  uint16_t pin;
  GPIO_PinState on_stater;
  GPIO_PinState off_stater;
}LED_TBL_CFG;



bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);


#endif /* INC_LED_H_ */

/*
 * button.h
 *
 *  Created on: Sep 6, 2023
 *      Author: user
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "stm32f4xx_hal.h"      // like #include <avr/io.h>

enum {PUSHED, RELEASED};
enum {NO_ACT, ACT_PUSH, ACT_RELREASE};

typedef struct _button{
  GPIO_TypeDef *GPIOx;  // DDRA,B,C...
  uint16_t GPIO_Pin;    // number: PORTA1,2,3,4...
  uint8_t prevState;
}Button;

void Button_Init(Button *btn, GPIO_TypeDef *GPIOx, uint16_t GPIO_pin);
uint8_t Button_getState(Button *btn);



#endif /* SRC_BUTTON_H_ */

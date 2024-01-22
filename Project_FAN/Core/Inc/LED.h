/*
 * LED.h
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"

typedef struct GPIO {
    GPIO_TypeDef *LED_GPIO_Port[10];        // *port
    GPIO_TypeDef *LED_GPIO_Pin[10];         // pin
    uint8_t state;                          // On, OFF로 나눠서 구조체 배열 형태로 바꾸기
}GPIO;

static uint8_t STOP[3] = {0,0,0};
static uint8_t Level1[3] = {1,0,0};
static uint8_t Level2[3] = {1,1,0};
static uint8_t Level3[3] = {1,1,1};

void changeLED(GPIO led, uint8_t state);

#endif /* INC_LED_H_ */

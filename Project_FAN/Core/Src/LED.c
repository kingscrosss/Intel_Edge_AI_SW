/*
 * LED.c
 *
 *  Created on: Sep 26, 2023
 *      Author: user
 */

#include "LED.h"

void changeLED(GPIO led, uint8_t state){
  if(state == 0){
    for(int i = 0; i<3; i++){
      HAL_GPIO_WritePin(led.LED_GPIO_Port[i], led.LED_GPIO_Pin[i], STOP[i]);
    }
  }
  if(state == 1){
    for(int i = 0; i<3; i++){
      HAL_GPIO_WritePin(led.LED_GPIO_Port[i], led.LED_GPIO_Pin[i], Level1[i]);
    }
  }
  if(state == 2){
    for(int i = 0; i<3; i++){
      HAL_GPIO_WritePin(led.LED_GPIO_Port[i], led.LED_GPIO_Pin[i], Level2[i]);
    }
  }
  if(state == 3){
    for(int i = 0; i<3; i++){
      HAL_GPIO_WritePin(led.LED_GPIO_Port[i], led.LED_GPIO_Pin[i], Level3[i]);
    }
  }
}


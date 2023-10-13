/*
 * bsp.h
 *
 *  Created on: Oct 13, 2023
 *      Author: user
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_

#include "def.h"

#include "stm32f4xx_hal.h"      // core/main.h 폴더에서 가져옴






void bspInit();

void delay(uint32_t ms);
uint32_t millis(void);

void Error_Handler(void);

#endif /* SRC_BSP_BSP_H_ */

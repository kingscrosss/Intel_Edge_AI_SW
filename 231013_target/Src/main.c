/*
 * main.c
 *
 *  Created on: Oct 13, 2023
 *      Author: user
 */


#include "main.h"

int main(void){
  hwInit();
  apInit();

  apMain();

  return 0;
}

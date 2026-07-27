/**
   @file delay.h
*/

#ifndef DELAY_H
#define DELAY_H

#include "main.h"

extern TIM_HandleTypeDef htim1;

void delay_us(uint16_t us);

#endif /* DELAY_H */
/**
   @file delay.c
*/

#include "delay.h"

#define htimx htim1 // TODO: config this

void delay_us(uint16_t us) {
  (&htimx)->Instance->CNT = 0;

	while ((&htimx)->Instance->CNT < us);  // wait for the counter to reach the us input in the parameter
}
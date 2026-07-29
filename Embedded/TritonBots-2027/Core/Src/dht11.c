/**

   @file dht11.c
*/

#include "dht11.h"


void GPIO_SetInput(GPIO_TypeDef* PORTx, uint16_t pin) {
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   GPIO_InitStruct.Pin = pin;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(PORTx, &GPIO_InitStruct);
}

void GPIO_SetOutput(GPIO_TypeDef* PORTx, uint16_t pin) {
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   GPIO_InitStruct.Pin = pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   HAL_GPIO_Init(PORTx, &GPIO_InitStruct);
}


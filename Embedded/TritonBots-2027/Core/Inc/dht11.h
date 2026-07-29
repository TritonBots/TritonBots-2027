/**
   @file dht11.h


*/

#ifndef DHT11_H
#define DHT11_H

#include "main.h"

/*

DHT11 Timing Information

 Start Signal:
 VCC ──┐       ┏─20-40 us─┐       ┏─80 us─┐
 GND   └─18 ms─┛          └─80 us─┛       └─Start Data Transmission

 Data '0':
 VCC ──┐       ┏─26-28 us = '0'─┐
 GND   └─50 us─┛                └─Start to transmit next bit data

 Data '1':
 VCC ──┐       ┏─70 us = '1'─┐
 GND   └─50 us─┛             └─Start to transmit next bit data

*/
#define START_SIGNAL_DELAY_MS 18U
#define START_ACK_DELAY_US 80U
#define START_DATA_DELAY_US 50U
#define MIN_DATA_ZERO_DELAY_US 26U
#define MAX_DATA_ZERO_DELAY_US 28U
#define DATA_ONE_DELAY_US 70U

// TODO: config this for your setup
#define DHT11_DATA_PORT GPIOB
#define DHT11_DATA_PIN GPIO_PIN_11

void GPIO_SetInput(GPIO_TypeDef* PORTx, uint16_t pin);
void GPIO_SetOutput(GPIO_TypeDef* PORTx, uint16_t pin);


#endif /* DHT11_H */
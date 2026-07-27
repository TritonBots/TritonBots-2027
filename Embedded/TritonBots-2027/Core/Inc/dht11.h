/**
   @file dht11.h


*/

#ifndef DHT11_H
#define DHT11_H

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
#define START_SIGNAL_DELAY_MS 18
#define START_ACK_DELAY_US 80
#define START_DATA_DELAY_US 50
#define MIN_DATA_ZERO_DELAY_US 26
#define MAX_DATA_ZERO_DELAY_US 28
#define DATA_ONE_DELAY_US 70


#endif /* DHT11_H */
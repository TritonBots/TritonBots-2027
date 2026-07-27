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


#endif /* DHT11_H */
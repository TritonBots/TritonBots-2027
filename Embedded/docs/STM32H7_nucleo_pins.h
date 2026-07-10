/**
   @file STM32H7_nucleo_pins.h

   @brief pin information for the STM32H7 nucleo board.

   This should act as a quick lookup for commonly used pins.
   From this, the list will be short.
   CAN is the most important to us, so it is one of the only pins listed. 

   @see Embedded\docs\STM32H7 Nucleo-144 boards User Manual.pdf

   Information is from datasheet pages: 40-44.
*/

// CAN pins are on CN9 ZIO connector
#define CAN1_RX "PD0" // STM32 pin. pin 25. pin D67
#define CAN1_TX "PD1" // STM32 pin. pin 27. pin D66
/**
   @file STM32H7_nucleo_pins.h

   @brief pin information for the STM32H7 nucleo board.

   This should act as a quick lookup for commonly used pins.
   From this, the list will be short.
   CAN is the most important to us, so it is one of the only pins listed. 

   @see Embedded\docs\STM32H7 Nucleo-144 boards User Manual.pdf

   Information is from datasheet pages: 40-44.
*/

#define FDCAN1_RX "PA11"
#define FDCAN1_TX "PA12"

#define SPI_A_SCK "PA5"
#define SPI_A_MOSI "PA7"
#define SPI_A_MISO "PA6"
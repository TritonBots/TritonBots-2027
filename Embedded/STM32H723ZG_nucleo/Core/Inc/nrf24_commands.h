/**
   @file nrf24_commands.h

   @brief Declares the SPI Commands for the NRF24L01+ Radio Module

   @see Embedded\docs\pdf\nRF24L01P_Product_Specification_1_0.pdf

   Pages: 50-52
*/

#ifndef NRF24_COMMANDS_H
#define NRF24_COMMANDS_H

#include "nrf24_registers.h"

/*

   Every new command must be started by a high to low transition on CSN

   The STATUS register is serially shifted out on the MISO pin simultaneously to the SPI command word shifting to the MOSI pin.

   The serial shifting SPI commands is in the following format:
      <Command word: MSBit to LSBit (one byte)>
      <Data bytes: LSByte to MSByte, MSBit in each byte first>

*/

/**
   @brief drive the CSN signal HIGH
*/
void nrf24_write_csn_high(void);

/**
   @brief drive the CSN signal LOW
*/
void nrf24_write_csn_low(void);

/**
   @brief start a new spi command by driving CSN LOW

   @note this is the same as nrf24_write_csn_low()
*/
void nrf24_start_spi_command(void);

/**
   @brief end a spi command by driving CSN HIGH

   @note this is the same as nrf24_write_csn_high()
*/
void nrf24_end_spi_command(void);

/**
   @brief Read command and status registers.
   
   @param registerMapAddress 5 bit register address
   @param status 1 byte return status of the specified register
   @param data 2 bytes return data from the specified register
*/
void nrf24_read_register(const uint8_t registerMapAddress, uint8_t* status, uint16_t *data);

#endif /* NRF24_COMMANDS_H */
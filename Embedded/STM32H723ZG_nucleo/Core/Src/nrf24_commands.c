/**
   @file nrf24_commands.c

   @brief Defines 

   @see 

   Pages: 50-52
*/

#define STM32H7xx // TODO: this is for development. delete this later
#include "nrf24.h"
#include "nrf24_commands.h"

void nrf24_write_csn_high(void) {
	HAL_GPIO_WritePin(
		CSN_GPIO_PORT,
		CSN_GPIO_PIN,
		GPIO_PIN_SET
	);
}

void nrf24_write_csn_low(void) {
	HAL_GPIO_WritePin(
		CSN_GPIO_PORT,
		CSN_GPIO_PIN,
		GPIO_PIN_RESET
	);
}

void nrf24_start_spi_command(void) {
   HAL_GPIO_WritePin(
		CSN_GPIO_PORT,
		CSN_GPIO_PIN,
		GPIO_PIN_RESET
	);
}

void nrf24_end_spi_command(void) {
   HAL_GPIO_WritePin(
		CSN_GPIO_PORT,
		CSN_GPIO_PIN,
		GPIO_PIN_SET
	);
}

void nrf24_read_register(const uint8_t registerMapAddress, uint8_t* status, uint16_t *data) {

   status &= 0b00000000; // set status to 0s
   data &= 0x0000; // set data to 0s
   
   const uint8_t commandWord = R_REGISTER | registerMapAddress; // build Command word
   const uint8_t dataSize = 2; // bytes TODO: replace 2 (bytes) with a macro
   const uint8_t statusSize = 1; // bytes TODO: replace 1 (bytes) with a macro
   /**
      [0]: LSByte
      [1]: MSByte
   */
   uint8_t dataBits[dataSize] = {0x00, 0x00};

   nrf24_start_spi_command();

   // TODO: SPI TransmitReceive commandWord in MSBit to LSBit order
   HAL_SPI_TransmitReceive(
      &hspi1,
      commandWord,
      status,
      statusSize,
      HAL_MAX_DELAY
   ); // TODO: replace hspi1 with a pass by pointer argument
   
   HAL_SPI_Receive(
      &hspi1,
      dataBits,
      dataSize,
      HAL_MAX_DELAY
   ); // TODO: replace hspi1 with a pass by pointer argument
   nrf24_end_spi_command();

   data |= (uint16_t)(dataBits[1] << 8) | dataBits[0];
   
}
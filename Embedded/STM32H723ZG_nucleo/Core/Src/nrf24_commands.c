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


void nrf24_read_register(
   SPI_HandleTypeDef *hspiX,
   const uint8_t registerMapAddress,
   uint8_t *status,
   uint8_t *data,
   const uint8_t dataSize
)
{
   /* Mask address to 5 bits per datasheet: command = 000AAAAA */
   uint8_t commandWord = R_REGISTER | (registerMapAddress & 0x1F);

   nrf24_start_spi_command();  /* CSN low — begins SPI transaction */

   /*
   * Phase 1: Send command byte, simultaneously receive STATUS register.
   * Blocking call — must complete before Phase 2 begins.
   */
   HAL_SPI_TransmitReceive(hspiX, &commandWord, status, 1, HAL_MAX_DELAY);

   /*
   * Phase 2: Receive register data bytes.
   * LSByte first, per datasheet Section 8.3.1.
   */
   HAL_SPI_Receive(hspiX, data, dataSize, HAL_MAX_DELAY);

   nrf24_end_spi_command();    /* CSN high — ends SPI transaction */
}


HAL_StatusTypeDef nrf24_write_register(
   SPI_HandleTypeDef *hspiX,
   const uint8_t     registerMapAddress,
   uint8_t          *status,
   const uint8_t    *data,
   const uint8_t     dataSize
)
{
   HAL_StatusTypeDef result;

   /* Mask address to 5 bits: command encodes as 001AAAAA per datasheet */
   uint8_t commandWord = W_REGISTER | (registerMapAddress & 0x1F);

   nrf24_start_spi_command();  /* CSN low — begins SPI transaction */

   /*
   * Phase 1: Send command byte, simultaneously receive STATUS register.
   * STATUS is always shifted out on MISO during the command byte per datasheet.
   */
   result = HAL_SPI_TransmitReceive(
      hspiX,
      &commandWord,
      status,
      1,              /* command word is always exactly 1 byte */
      HAL_MAX_DELAY
   );

   /*
   * Phase 2: Write data bytes only if command phase succeeded.
   * LSByte first, per datasheet Section 8.3.1.
   */
   if (result == HAL_OK) {
      result = HAL_SPI_Transmit(
         hspiX,
         (uint8_t *)data,    /* cast away const: HAL param is non-const but won't modify */
         dataSize,
         HAL_MAX_DELAY
      );
   }

   nrf24_end_spi_command();    /* CSN high — always end transaction, even on error */

   return result;
}

HAL_StatusTypeDef nrf24_read_rx_payload(
   SPI_HandleTypeDef *hspiX,
   uint8_t           *status,
   uint8_t           *payload,
   const uint8_t      payloadSize
)
{
   HAL_StatusTypeDef result;

   /* R_RX_PAYLOAD command = 0b01100001 per datasheet Table 20 */
   uint8_t commandWord = R_RX_PAYLOAD;

   nrf24_start_spi_command();  /* CSN low — begins SPI transaction */

   /*
   * Phase 1: Send command byte, simultaneously receive STATUS register.
   * STATUS is always shifted out on MISO during the command byte.
   */
   result = HAL_SPI_TransmitReceive(
      hspiX,
      &commandWord,
      status,
      1,              /* command word is always exactly 1 byte */
      HAL_MAX_DELAY
   );

   /*
   * Phase 2: Read payload bytes from RX FIFO.
   * LSByte first per datasheet. Only proceed if command phase succeeded.
   */
   if (result == HAL_OK) {
      result = HAL_SPI_Receive(
         hspiX,
         payload,
         payloadSize,
         HAL_MAX_DELAY
      );
   }

   nrf24_end_spi_command();    /* CSN high — always end transaction, even on error */

   return result;
}

HAL_StatusTypeDef nrf24_write_tx_payload(
   SPI_HandleTypeDef *hspiX,
   uint8_t           *status,
   const uint8_t     *payload,
   const uint8_t      payloadSize
)
{
   HAL_StatusTypeDef result;

   /* W_TX_PAYLOAD = 0b10100000 per datasheet Table 20 */
   uint8_t commandWord = W_TX_PAYLOAD;

   nrf24_start_spi_command();  /* CSN low — begins SPI transaction */

   /*
   * Phase 1: Send command byte, simultaneously receive STATUS register.
   * STATUS is always shifted out on MISO during the command byte.
   */
   result = HAL_SPI_TransmitReceive(
      hspiX,
      &commandWord,
      status,
      1,              /* command word is always exactly 1 byte */
      HAL_MAX_DELAY
   );

   /*
   * Phase 2: Write payload bytes into TX FIFO.
   * LSByte first per datasheet Section 8.3.1.
   * Only transmit if command phase succeeded.
   */
   if (result == HAL_OK) {
      result = HAL_SPI_Transmit(
         hspiX,
         (uint8_t *)payload,     /* cast away const: HAL param is non-const but won't modify */
         payloadSize,
         HAL_MAX_DELAY
      );
   }

   nrf24_end_spi_command();    /* CSN high — always end transaction, even on error */

   return result;
}
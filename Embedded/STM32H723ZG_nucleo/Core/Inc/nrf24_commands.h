/**
   @file nrf24_commands.h

   @brief Declares the SPI Commands for the NRF24L01+ Radio Module

   @see Embedded\docs\pdf\nRF24L01P_Product_Specification_1_0.pdf

   Pages: 50-52
*/

#ifndef NRF24_COMMANDS_H
#define NRF24_COMMANDS_H

#include "nrf24_registers.h"

#define COMMAND_WORD_SIZE 1 // bytes

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
 * @brief  Read 1–5 bytes from an nRF24L01+ register via SPI.
 *
 * Per datasheet Section 8.3.1:
 *   - Command word (R_REGISTER | address) is sent on MOSI
 *   - STATUS register is simultaneously received on MISO
 *   - Data bytes follow: LSByte first, MSBit in each byte first
 *
 * @param  hspiX              SPI handle
 * @param  registerMapAddress 5-bit register address (AAAAA in 000AAAAA)
 * @param  status             Output: STATUS register byte received during command
 * @param  data               Output: buffer for register data (caller-allocated, min dataSize bytes)
 * @param  dataSize           Number of bytes to read (1 for most registers, up to 5 for address regs)
*/
void nrf24_read_register(
   SPI_HandleTypeDef *hspiX,
   const uint8_t registerMapAddress,
   uint8_t *status,
   uint8_t *data,
   const uint8_t dataSize
)

/**
 * @brief  Write 1–5 bytes to an nRF24L01+ register via SPI.
 *
 * Per datasheet Section 8.3.1:
 *   - Command word (W_REGISTER | address) sent on MOSI: encoding 001AAAAA
 *   - STATUS register simultaneously received on MISO during command byte
 *   - Data bytes follow: LSByte first, MSBit in each byte first
 *   - Executable in power down or standby modes only (per register map table)
 *
 * @param  hspiX              SPI handle
 * @param  registerMapAddress 5-bit register address (AAAAA in 001AAAAA)
 * @param  status             Output: STATUS register byte received during command phase
 * @param  data               Input:  buffer of bytes to write (caller-allocated, min dataSize bytes)
 * @param  dataSize           Number of bytes to write (1 for most registers, up to 5 for address regs)
 * @return HAL_OK on success, HAL_ERROR or HAL_TIMEOUT on failure
 */
HAL_StatusTypeDef nrf24_write_register(
   SPI_HandleTypeDef *hspiX,
   const uint8_t     registerMapAddress,
   uint8_t          *status,
   const uint8_t    *data,
   const uint8_t     dataSize
);

/**
 * @brief  Read RX payload from the nRF24L01+ RX FIFO via SPI.
 *
 * Per datasheet Section 8.3.1 (R_RX_PAYLOAD command = 0b01100001):
 *   - Reads 1–32 bytes from RX FIFO, starting at byte 0
 *   - Payload is deleted from FIFO after it is read
 *   - STATUS register is shifted out on MISO during the command byte
 *   - Used in RX mode
 *
 * For Dynamic Payload Length (DPL): caller must first issue R_RX_PL_WID
 * to determine payloadSize before calling this function. Per datasheet,
 * if R_RX_PL_WID returns > 32, the packet is corrupt — flush RX FIFO
 * with FLUSH_RX and do NOT call this function.
 *
 * For Static Payload Length: payloadSize must match the configured
 * RX_PW_Px register value for the receiving pipe.
 *
 * @param  hspiX       SPI handle
 * @param  status      Output: STATUS register byte received during command phase
 * @param  payload     Output: caller-allocated buffer, minimum payloadSize bytes
 * @param  payloadSize Number of bytes to read from RX FIFO (1–32)
 * @return HAL_OK on success, HAL_ERROR or HAL_TIMEOUT on failure
 */
HAL_StatusTypeDef nrf24_read_rx_payload(
   SPI_HandleTypeDef *hspiX,
   uint8_t           *status,
   uint8_t           *payload,
   const uint8_t      payloadSize
);

/**
 * @brief  Write TX payload to the nRF24L01+ TX FIFO via SPI.
 *
 * Per datasheet Section 8.3.1, Table 20 (W_TX_PAYLOAD = 0b10100000):
 *   - Writes 1–32 bytes into the TX FIFO, starting at byte 0
 *   - Data is LSByte first, MSBit in each byte first
 *   - STATUS register is shifted out on MISO during the command byte
 *   - Used in TX mode only
 *
 * The TX FIFO has three 32-byte levels. Check FIFO_STATUS.TX_FULL
 * before calling to avoid overflowing the FIFO.
 *
 * After writing, pulse CE high for >= 10us to begin transmission.
 * If MAX_RT IRQ is asserted, the payload is NOT removed from TX FIFO —
 * caller must handle retransmission or call FLUSH_TX explicitly.
 *
 * @param  hspiX       SPI handle
 * @param  status      Output: STATUS register byte received during command phase
 * @param  payload     Input: caller-allocated buffer of bytes to write
 * @param  payloadSize Number of bytes to write to TX FIFO (1–32)
 * @return HAL_OK on success, HAL_ERROR or HAL_TIMEOUT on failure
 */
HAL_StatusTypeDef nrf24_write_tx_payload(
   SPI_HandleTypeDef *hspiX,
   uint8_t           *status,
   const uint8_t     *payload,
   const uint8_t      payloadSize
);

#endif /* NRF24_COMMANDS_H */
/**
 * @file moteus_can.h
 * @brief HAL FDCAN wrapper for Moteus communication
 *
 * Provides initialization and TX/RX functions for STM32 FDCAN peripheral.
 * Configured for use with Moteus motor controllers.
 *
 * NOTE: Bit timing is configured in CubeMX, not here. This file only handles
 * filter setup, starting the peripheral, and enabling interrupts.
 */

#ifndef MOTEUS_CAN_H
#define MOTEUS_CAN_H

#include "moteus.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * FDCAN Initialization
 *
 * Bit timing must be configured in CubeMX.
 *
 * In this project we target 1 Mbps arbitration and a 170 MHz FDCAN clock.
 * The specific example values are:
 *   - Prescaler = 1
 *   - TimeSeg1  = 135
 *   - TimeSeg2  = 34
 *   - SyncJumpWidth = 34
 *
 * Invariants/assumptions:
 *   - moteus_can_init only configures filters + starts the peripheral.
 *   - Higher-level moteus_* logic handles protocol parsing and routing.
 *   - Moteus may send replies that the STM32 hardware classifies as either
 *     standard or extended IDs; our software parsing tolerates this.
 * ============================================================================ */


HAL_StatusTypeDef moteus_can_init(FDCAN_HandleTypeDef* hfdcan);

/* ============================================================================
 * Transmit Functions
 * ============================================================================ */

/**
 * @brief Convert payload length (bytes) to FDCAN DLC encoding
 *
 * @param len Payload length in bytes (0-64)
 * @return FDCAN DLC code to be stored in the TX header
 *
 * @note FDCAN DLC is not 1:1 with byte count for classic/non-linear DLC values.
 */
static uint32_t get_fdcan_dlc(uint8_t len);

/**
 * @brief Convert FDCAN DLC encoding back to payload length in bytes
 *
 * @param dlc FDCAN TX/RX DLC field value
 * @return Payload length in bytes (8/12/16/20/24/32/48/64 depending on DLC)
 *
 * @warning If an unknown DLC value is provided by the hardware, this returns 8.
 */
static uint8_t get_data_length(uint32_t dlc);

/**
 * @brief Transmit a moteus CAN frame using STM32 FDCAN HAL
 *
 * @param hfdcan HAL FDCAN handle
 * @param frame Frame to transmit
 *
 * @return HAL_OK on success, HAL_ERROR otherwise
 *
 * @note This function always treats CAN IDs as 29-bit extended IDs.
 * @note Data padding: the TX buffer is padded up to the selected DLC.
 */
HAL_StatusTypeDef moteus_can_transmit(FDCAN_HandleTypeDef* hfdcan,
                                       const moteus_can_frame_t* frame);

/* ============================================================================
 * Receive Functions
 * ============================================================================ */

/**
 * @brief Receive a moteus CAN frame with optional timeout
 *
 * @param hfdcan HAL FDCAN handle
 * @param frame Output frame structure (payload, length, flags)
 * @param timeout_ms Timeout in milliseconds
 *
 * @return HAL_OK on success, HAL_TIMEOUT if no message is available within timeout
 * @return HAL_ERROR on invalid parameters or HAL receive errors
 *
 * @note If @p timeout_ms is 0, the function performs a single non-blocking attempt.
 */
HAL_StatusTypeDef moteus_can_receive(FDCAN_HandleTypeDef* hfdcan,
                                      moteus_can_frame_t* frame,
                                      uint32_t timeout_ms);

/* ============================================================================
 * Helper function to process RX in interrupt context
 * ============================================================================ */

/**
 * @brief FDCAN RX FIFO0 interrupt handler helper
 *
 * @param hfdcan HAL FDCAN handle
 *
 * @return void
 *
 * @warning Intended to be called from the HAL RX callback context.
 *          This function drains FIFO0 and forwards each received frame to
 *          moteus_process_rx().
 */
void moteus_fdcan_rx_callback(FDCAN_HandleTypeDef* hfdcan);

#ifdef __cplusplus
}
#endif

#endif /* MOTEUS_CAN_H */
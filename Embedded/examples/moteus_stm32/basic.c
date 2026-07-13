/**
 * @file basic.c
 * @brief Basic single-motor example using blocking commands
 *
 * This example demonstrates:
 * - Motor initialization
 * - Blocking commands (Set*)
 * - Reading motor state
 * - Position and torque control
 *
 * Prerequisites:
 * - FDCAN configured in CubeMX (see README for timing settings)
 * - FDCAN global interrupt enabled
 */

#include "moteus.h"
#include "main.h"  // For hfdcan1

extern FDCAN_HandleTypeDef hfdcan1;

static moteus_motor_t* motor;

/**
 * @brief FDCAN RX callback - add to main.c
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    (void)RxFifo0ITs;
    moteus_fdcan_rx_callback(hfdcan);
}

/**
 * @brief Initialize motor
 */
void motor_init(void)
{
    // Initialize CAN peripheral
    moteus_can_init(&hfdcan1);

    // Create motor instance (ID 1)
    motor = moteus_init(&hfdcan1, 1);
    if (!motor) {
        printf("Failed to initialize motor\n");
        return;
    }

    // Optional: reduce timeout for faster failure detection
    motor->timeout_ms = 50;
}

/**
 * @brief Query and print motor state
 */
void print_motor_state(void)
{
    const moteus_result_t* r = moteus_set_query(motor);
    if (r) {
        printf("Mode: %s\n", moteus_mode_str(r->mode));
        printf("Position: %.3f rev\n", r->position);
        printf("Velocity: %.3f rev/s\n", r->velocity);
        printf("Torque: %.3f Nm\n", r->torque);
        printf("Voltage: %.1f V\n", r->voltage);
        printf("Temperature: %.1f C\n", r->temperature);

        if (r->fault != MOTEUS_FAULT_NONE) {
            printf("FAULT: %s\n", moteus_fault_str(r->fault));
        }
    } else {
        printf("Query failed: %s\n", moteus_error_str(motor->last_error));
    }
}

/**
 * @brief Move to position and wait
 */
void move_to_position(float target_rev)
{
    moteus_position_cmd_t cmd = MOTEUS_POSITION_CMD_DEFAULT;
    cmd.position = target_rev;
    cmd.velocity = 1.0f;      // Limit velocity to 1 rev/s
    cmd.max_torque = 2.0f;    // Limit torque to 2 Nm

    printf("Moving to %.2f rev...\n", target_rev);

    const moteus_result_t* r = moteus_set_position(motor, &cmd);
    if (r) {
        printf("Command sent. Current position: %.3f rev\n", r->position);
    } else {
        printf("Command failed: %s\n", moteus_error_str(motor->last_error));
    }
}

/**
 * @brief Apply constant torque
 */
void apply_torque(float torque_nm)
{
    printf("Applying %.2f Nm torque...\n", torque_nm);

    const moteus_result_t* r = moteus_set_torque(motor, torque_nm);
    if (r) {
        printf("Torque applied. Measured: %.3f Nm\n", r->torque);
    } else {
        printf("Command failed: %s\n", moteus_error_str(motor->last_error));
    }
}

/**
 * @brief Stop motor safely
 */
void motor_stop(void)
{
    const moteus_result_t* r = moteus_set_stop(motor);
    if (r) {
        printf("Motor stopped.\n");
    }
}

/**
 * @brief Example main loop
 */
void example_main(void)
{
    motor_init();

    // Check motor is responding
    print_motor_state();

    // Move to position 0 (home)
    move_to_position(0.0f);
    HAL_Delay(1000);

    // Move to 0.5 revolutions
    move_to_position(0.5f);
    HAL_Delay(1000);

    // Move back to 0
    move_to_position(0.0f);
    HAL_Delay(1000);

    // Apply small torque for 2 seconds
    apply_torque(0.1f);
    HAL_Delay(2000);

    // Stop
    motor_stop();

    printf("Example complete.\n");
}

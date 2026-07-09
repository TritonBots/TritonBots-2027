# Moteus STM32 Library

A C library for controlling [Moteus](https://mjbots.com/products/moteus-r4-11) brushless motor controllers via CAN-FD on STM32 microcontrollers using the HAL.

## Features

- **Simple API** - Blocking (`Set*`) and non-blocking (`Begin*`) command variants
- **Full Protocol Support** - Stop, Brake, Query, Position, and Torque commands
- **CAN-FD with BRS** - 5 Mbps data phase for fast communication
- **Configurable Resolution** - Optimize bandwidth vs precision per application
- **Multi-Motor Support** - Up to 8 motors (configurable)
- **Interrupt-Driven RX** - Efficient response handling via HAL callbacks
- **Minimal Dependencies** - Only requires STM32 HAL

## Quick Start

### 1. CubeMX Configuration

Configure FDCAN1 for CAN-FD with BRS (Bit Rate Switching).

**Critical:** Moteus requires **66.6% sample point** and **maximized SJW** for both phases.

#### For 170 MHz FDCAN Clock (STM32G4):

**Nominal Phase (1 Mbps, 66.6% sample point):**
| Parameter | Value |
|-----------|-------|
| Prescaler | 1 |
| TimeSeg1 | 112 |
| TimeSeg2 | 57 |
| SyncJumpWidth | 57 |

**Data Phase (5 Mbps, 67.6% sample point):**
| Parameter | Value |
|-----------|-------|
| Prescaler | 1 |
| TimeSeg1 | 22 |
| TimeSeg2 | 11 |
| SyncJumpWidth | 11 |

**Other Settings:**
| Parameter | Value |
|-----------|-------|
| Frame Format | FDCAN_FRAME_FD_BRS |
| Mode | FDCAN_MODE_NORMAL |
| Auto Retransmission | ENABLE |

**TDC (Transmitter Delay Compensation):**
```c
HAL_FDCAN_ConfigTxDelayCompensation(&hfdcan1, 23, 0);  // TDCO = DataTimeSeg1 + 1
HAL_FDCAN_EnableTxDelayCompensation(&hfdcan1);
```

Enable FDCAN1 global interrupt in NVIC.

> **Note:** Using the wrong sample point (e.g., 80%) will cause communication failures. See [CAN-FD BRS Configuration](https://mjbots.github.io/moteus/integration/can-fd/) for details.

#### Non-BRS Configuration (1 Mbps only)

If you disable BRS (`MOTEUS_ENABLE_BRS=0`), you can use simpler timing:

| Parameter | Value |
|-----------|-------|
| Frame Format | FDCAN_FRAME_FD_NO_BRS |
| Prescaler | 1 |
| TimeSeg1 | 135 |
| TimeSeg2 | 34 |
| SyncJumpWidth | 34 |

TDC is not required for non-BRS mode.

### 2. Basic Usage

```c
#include "moteus.h"

// In main():
moteus_can_init(&hfdcan1);
moteus_motor_t* motor = moteus_init(&hfdcan1, 1);  // Motor ID 1

// Send stop command and wait for response
const moteus_result_t* r = moteus_set_stop(motor);
if (r) {
    printf("Position: %.3f rev\n", r->position);
}

// Send position command
moteus_position_cmd_t cmd = MOTEUS_POSITION_CMD_DEFAULT;
cmd.position = 0.5f;  // Target: 0.5 revolutions
moteus_set_position(motor, &cmd);
```

### 3. CAN RX Callback

Add to your main.c:

```c
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    (void)RxFifo0ITs;
    moteus_fdcan_rx_callback(hfdcan);
}
```

## Examples

See the `examples/` directory for complete examples:

- **`basic.c`** - Single motor with blocking commands
- **`multi_motor.c`** - Multiple motors with batch commands and polling

### Blocking vs Non-Blocking

**Blocking (Set*)** - Sends command, waits for response:

```c
const moteus_result_t* r = moteus_set_position(motor, &cmd);
if (r) printf("Position: %.3f\n", r->position);
```

**Non-Blocking (Begin*)** - Sends command, returns immediately:

```c
moteus_begin_position(motor, &cmd);
// ... do other work ...
if (moteus_poll(motor)) {
    printf("Position: %.3f\n", motor->result.position);
}
```

For multi-motor systems, non-blocking commands allow batch sending to all motors before waiting for responses, which is significantly faster than blocking on each motor sequentially.

## API Reference

### Initialization

| Function | Description |
|----------|-------------|
| `moteus_can_init()` | Initialize FDCAN peripheral for Moteus communication |
| `moteus_init()` | Create a motor instance for a given ID |
| `moteus_deinit()` | Deinitialize a motor instance |

### Blocking Commands (Set*)

These functions send a command and wait for the response. Returns a pointer to the result, or `NULL` on timeout/error.

| Function | Description |
|----------|-------------|
| `moteus_set_stop()` | Stop the motor (disables PWM output) |
| `moteus_set_brake()` | Brake mode (resists movement, allows backdrive) |
| `moteus_set_query()` | Query motor state without changing mode |
| `moteus_set_position()` | Position/velocity/torque control |
| `moteus_set_torque()` | Pure torque control |

### Non-Blocking Commands (Begin*)

These functions send a command and return immediately. Use `moteus_poll()` to check for response.

| Function | Description |
|----------|-------------|
| `moteus_begin_stop()` | Send stop command (non-blocking) |
| `moteus_begin_brake()` | Send brake command (non-blocking) |
| `moteus_begin_query()` | Send query (non-blocking) |
| `moteus_begin_position()` | Send position command (non-blocking) |
| `moteus_begin_torque()` | Send torque command (non-blocking) |

### Response Handling

| Function | Description |
|----------|-------------|
| `moteus_poll()` | Check if response received (non-blocking) |
| `moteus_process_rx()` | Process received CAN frame |
| `moteus_fdcan_rx_callback()` | HAL callback helper |

### Configuration

| Function | Description |
|----------|-------------|
| `moteus_set_query_resolution()` | Set resolution for query responses |
| `moteus_set_command_resolution()` | Set resolution for position commands |
| `moteus_set_response_callback()` | Set callback for responses |
| `moteus_set_error_callback()` | Set callback for errors |

## Motor State

After any command, motor state is available in `motor->result`:

```c
typedef struct {
    uint8_t mode;       // Current mode (see MOTEUS_MODE_*)
    uint8_t fault;      // Fault code (see MOTEUS_FAULT_*)
    float position;     // Position in revolutions
    float velocity;     // Velocity in rev/s
    float torque;       // Torque in Nm
    float q_current;    // Q-axis current in A
    float d_current;    // D-axis current in A
    float voltage;      // Bus voltage in V
    float temperature;  // Temperature in C
    bool trajectory_complete;
} moteus_result_t;
```

## Position Command

```c
typedef struct {
    float position;         // Target position (rev) - NAN to ignore
    float velocity;         // Target velocity (rev/s) - NAN to ignore
    float feedforward_torque;  // Feedforward torque (Nm)
    float kp_scale;         // Position gain scale (0-1)
    float kd_scale;         // Velocity gain scale (0-1)
    float maximum_torque;   // Torque limit (Nm)
    float stop_position;    // Position to stop at (rev) - NAN to ignore
    float watchdog_timeout; // Watchdog timeout (s) - NAN for default
} moteus_position_cmd_t;
```

Use `MOTEUS_POSITION_CMD_DEFAULT` for sensible defaults.

## Motor Modes

| Mode | Description |
|------|-------------|
| `MOTEUS_MODE_STOPPED` | Motor stopped, PWM disabled |
| `MOTEUS_MODE_FAULT` | Fault condition |
| `MOTEUS_MODE_POSITION` | Position/velocity/torque control active |
| `MOTEUS_MODE_BRAKE` | Brake mode (resists movement) |
| `MOTEUS_MODE_TIMEOUT` | Communication timeout |

## Configuration Options

Define these before including `moteus.h`:

```c
#define MOTEUS_MAX_MOTORS 8       // Max motors (default: 8)
#define MOTEUS_SOURCE_ID 0        // CAN source ID (default: 0)
#define MOTEUS_DEFAULT_TIMEOUT_MS 100  // Blocking timeout (default: 100ms)
#define MOTEUS_ENABLE_BRS 1       // Enable BRS for 5 Mbps data phase (default: 1)
```

Per-motor timeout can be changed:
```c
motor->timeout_ms = 50;  // 50ms timeout for this motor
```

### BRS (Bit Rate Switching)

BRS is enabled by default (`MOTEUS_ENABLE_BRS=1`). With BRS:
- Arbitration phase: 1 Mbps
- Data phase: 5 Mbps
- ~5x faster data transfer

To disable BRS (use 1 Mbps for everything):
```c
#define MOTEUS_ENABLE_BRS 0
```

**Important:** BRS requires specific FDCAN timing configuration. See the CubeMX Configuration section above.

## Installation

Copy all `.c` and `.h` files to your project and add them to your build.

## Files

| File | Description |
|------|-------------|
| `moteus.h` | Main API header |
| `moteus.c` | API implementation |
| `moteus_can.c` | CAN peripheral handling |
| `moteus_protocol.h` | Protocol encoding/decoding |
| `moteus_protocol.c` | Protocol implementation |
| `moteus_types.h` | Type definitions |
| `moteus_registers.h` | Register and mode definitions |
| `examples/` | Example code |

## License

MIT License - See LICENSE file for details.


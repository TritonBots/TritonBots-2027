# Deprecated UNO R4 Implementation

> ⚠️ **This implementation is deprecated.** It is preserved here for historical
> reference only. Do not use this code as a base for new development.

---

## Overview

`robocup.ino` is the main firmware entry point for the legacy RoboCup robot
controller, targeting the **Arduino UNO R4**. It initializes all hardware
subsystems and runs a continuous control loop that processes incoming UDP
commands to drive the robot's motors and actuators.

---

## Hardware Dependencies

- **Arduino UNO R4** — primary microcontroller
- **MCP2517FD** — SPI-attached CAN-FD controller (chip select: `MCP2517_CS`,
  interrupt: `MCP2517_INT`)
- **Moteus motor controllers** — one per motor slot, addressed over CAN-FD
- **Kicker solenoid** — driven via a dedicated GPIO pin (`KICKER_PIN`)
- **Built-in WiFi module** — used for UDP command reception
- *(Removed)* SSD1306 OLED display — wiring and display logic are fully
  commented out and no longer functional

---

## Configuration & Preprocessor Flags

All tuneable parameters are defined in external headers:

- `commands.h` — command structures, motor/wheel counts, watchdog timeout,
  CAN-FD settings helpers, and packet handlers
- `credentials.h` — network credentials (`WIFI_SSID`, `WIFI_PASSWORD`),
  IP configuration (`LOCAL_IP_ADDRESS`, `GATEWAY_IP_ADDRESS`, `SUBNET_MASK`),
  and `UDP_PORT`

### Key compile-time flags

- **`ENABLE_MOTORS`** (`0` / `1`) — gates all CAN-FD bus initialization and
  motor object creation. Set to `0` to run the firmware without physical motors
  attached.
- **`ENABLE_TEST_MOTORS`** (`0` / `1`) — switches between the full 5-motor
  layout and a reduced test layout.
- **`NUM_TEST_MOTORS`** (`1`–`5`) — controls how many motor slots are compiled
  in during test mode.
- **`HAS_DRIBBLER`** (`0` / `1`) — conditionally includes dribbler drop logic
  in the watchdog stop sequence.

---

## Motor Layout

### Full Mode (`ENABLE_TEST_MOTORS == 0`)

Five motor slots are active:

- `FrontLeftWheelCmd`
- `FrontRightWheelCmd`
- `BackRightWheelCmd`
- `BackLeftWheelCmd`
- `DribblerCmd`

`MotorCommands[]` holds all five. `WheelCommands[]` holds only the four drive
wheels and is used exclusively by dash/turn motion commands.

### Test Mode (`ENABLE_TEST_MOTORS == 1`)

Only the first `NUM_TEST_MOTORS` slots are compiled into both
`MotorCommands[]` and `WheelCommands[]` to conserve memory during
hardware-limited testing.

---

## Initialization Sequence (`setup()`)

The `setup()` function executes the following steps **in order**. Each stage
includes a `delay(1000)` to allow hardware to stabilize between steps.

1. **Serial** — opens at `115200` baud
2. **GPIO** — configures `KICKER_PIN` as an output
3. **SPI** — initializes the SPI bus for the CAN controller
4. **CAN-FD** — configures the `ACAN2517FD` driver at `OSC_20MHz` with a
   `x1` data bit rate factor via `configCANFDSettings()`
5. **Position commands** — calls `initPositionCommands()` to zero-initialize
   all `PositionCommand` structs
6. **WiFi module check** — halts if the WiFi module is unresponsive
7. **Firmware version check** — warns via Serial if firmware is out of date
8. **WiFi connection** — calls `connectWiFi()` with a **60-second timeout**;
   halts in an infinite loop if connection fails
9. **UDP socket** — binds to `UDP_PORT`
10. **CAN bus + Motor objects** *(if `ENABLE_MOTORS == 1`)* — begins CAN-FD,
    retries on error, then instantiates one `Moteus` object per slot (IDs
    start at `1`); each motor is issued a `BeginStop()` to clear faults

---

## Main Loop (`loop()`)

Each iteration of `loop()` performs four tasks:

1. **UDP packet handling** — `handleUdpPackets()` reads and dispatches any
   incoming motion/actuator commands, updating `WheelCommands`, `MotorCommands`,
   and `lastUdpCommandMs`
2. **Kicker servicing** — `serviceKicker()` de-asserts `KICKER_PIN` once the
   configured pulse duration has elapsed
3. **Watchdog enforcement** — if no UDP packet has been received within
   `WATCHDOG_TIMEOUT` milliseconds after the first command, the robot is
   commanded to stop (`stop()`) and the dribbler is dropped
   (`dribblerDrop()`, if `HAS_DRIBBLER`); `watchdogStopped` prevents
   repeated triggering
4. **CAN-FD transmission** *(if `ENABLE_MOTORS == 1`)* — `sendPositionCommands()`
   pushes the latest `PositionCommand` state to each Moteus controller
5. **Periodic velocity logging** — once per second, `printMotorVelocities()`
   dumps the current commanded velocities over Serial for debugging

---

## Network Configuration

WiFi uses a **static IP** applied via `WiFi.config()` before `WiFi.begin()`.
All relevant network parameters (`LOCAL_IP_ADDRESS`, `GATEWAY_IP_ADDRESS`,
`SUBNET_MASK`, `WIFI_SSID`, `WIFI_PASSWORD`, `UDP_PORT`) must be defined in
`credentials.h`.

---

## Known Limitations & Reasons for Deprecation

- **OLED display support was never completed** — all `Adafruit_SSD1306` and
  I2C scanner code is commented out
- **Blocking WiFi connect** — the firmware enters an infinite loop on
  connection failure, requiring a manual reset
- **Blocking CAN-FD retry** — a bus error with no motors connected also
  loops indefinitely
- **No reconnection logic** — if WiFi drops mid-operation, the robot will
  only be stopped by the watchdog; it cannot recover the network link
- **`new` allocations without `delete`** — `Moteus` objects are heap-allocated
  but never freed; not an issue for the embedded target but a maintenance concern
- **Arduino UNO R4 platform constraints** — limited flash/RAM headroom
  necessitated the conditional test-motor compile flags; successor hardware
  removes this constraint
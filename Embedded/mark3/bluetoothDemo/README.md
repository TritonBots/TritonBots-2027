# TritonBots Bluetooth Low Energy (BLE) 4-Wheel Controller Demo

This demo allows real-time manual control of the 4 omnidirectional drive wheels on the TritonBots robot using a standard PlayStation 4 (DualShock 4) controller plugged into a computer via USB.

> [!NOTE]
> This demo **only** drives the 4 wheel motors (Front-Left, Front-Right, Back-Right, Back-Left). **No dribbler** (Motor 5) and **no kicker** are initialized or energized.

---

## 1. Architecture Overview

```
[ PS4 Controller (USB) ] 
         |
         v
[ Laptop / PC ] ---> Runs ps4_ble_bridge.py (pygame + Bleak)
         |
         | (Bluetooth Low Energy / BLE)
         v
[ Arduino UNO R4 WiFi ] ---> Runs bluetoothDemo.ino (ArduinoBLE + ACAN2517FD)
         |
         | (CAN-FD Bus)
         v
[ 4x Moteus Controllers ] ---> Wheels: FL (1), FR (2), BR (3), BL (4)
```

- **Safety Watchdog**: If Bluetooth disconnects, the computer sleeps, or no command packet arrives within **500 ms**, the Arduino automatically commands all 4 motors to stop immediately (`SetStop()`).
- **Emergency Stop**: Pressing **Circle** or **Square** on the controller immediately stops all wheel movement.

---

## 2. Hardware Wiring

- **Microcontroller**: Arduino UNO R4 WiFi
- **CAN Controller**: MCP2517FD (SPI)
  - `SCK`  -> Pin 13
  - `MOSI` -> Pin 11 (or Pin 12 depending on shield)
  - `MISO` -> Pin 12 (or Pin 11 depending on shield)
  - `CS`   -> **Digital Pin 9**
  - `INT`  -> **Digital Pin 7**
- **Motors**:
  - `FL` (Front-Left)  -> CAN ID 1
  - `FR` (Front-Right) -> CAN ID 2
  - `BR` (Back-Right)  -> CAN ID 3
  - `BL` (Back-Left)   -> CAN ID 4

---

## 3. Quick Start Guide

### Step 1: Flash the Arduino
1. Open `bluetoothDemo.ino` in Arduino IDE or compile via CLI:
   ```bash
   arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi --upload -p <PORT> Embedded/mark3/bluetoothDemo
   ```
2. Open Serial Monitor at **115200 baud** to verify:
   ```text
   CAN-FD bus initialized successfully.
   All 4 wheel motors stopped & initialized.
   Bluetooth LE advertising started: 'TritonBot-Demo'
   ```

### Step 2: Install PC Dependencies
On your computer:
```bash
pip install pygame bleak
```

### Step 3: Run the Controller Bridge
1. Plug your **PS4 controller into your PC via USB**.
2. Run the bridge script:
   ```bash
   python ps4_ble_bridge.py
   ```
3. The script will automatically discover and connect to `"TritonBot-Demo"`. The onboard LED on the UNO R4 WiFi will illuminate solid when connected.

---

## 4. PS4 Controller Layout

| Control | Action |
| :--- | :--- |
| **Left Stick** | 360° Holonomic Translation (Forward, Backward, Strafe Left / Right) |
| **Right Stick X** | In-Place Rotation (Clockwise / Counter-Clockwise) |
| **Hold R1** | **Turbo Boost** (100% Speed) |
| **Hold L1** | **Precision Mode** (25% Speed) |
| **D-Pad Up / Down** | Adjust default speed scale in 10% increments |
| **Circle / Square** | **Emergency Stop / Brake** |
| **Ctrl + C** | Safely stop all robot motors and exit |

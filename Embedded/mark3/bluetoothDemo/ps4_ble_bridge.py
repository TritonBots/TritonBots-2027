#!/usr/bin/env python3
"""
ps4_ble_bridge.py - PS4 Controller to Bluetooth Low Energy (BLE) Bridge for TritonBots

Reads a USB-connected PlayStation 4 controller (DualShock 4) using pygame and transmits
holonomic velocity vectors over BLE to the Arduino UNO R4 WiFi running bluetoothDemo.ino.

Requirements:
    pip install pygame bleak

Usage:
    python ps4_ble_bridge.py
    python ps4_ble_bridge.py --address "XX:XX:XX:XX:XX:XX"
"""

import sys
import time
import math
import asyncio
import threading
import argparse

try:
    import pygame
except ImportError:
    print("\n[ERROR] pygame is not installed. Please install it using:\n    pip install pygame\n")
    sys.exit(1)

try:
    from bleak import BleakClient, BleakScanner
except ImportError:
    print("\n[ERROR] bleak is not installed. Please install it using:\n    pip install bleak\n")
    sys.exit(1)

# BLE Service and Characteristic UUIDs matching bluetoothDemo.ino
BLE_DEVICE_NAME = "TritonBot-Demo"
SERVICE_UUID    = "19b10000-e8f2-537e-4f6c-d104768a1214"
CHAR_UUID       = "19b10001-e8f2-537e-4f6c-d104768a1214"

# Control Tuning
DEADZONE = 0.08            # Joystick deadband to prevent drift
LOOP_RATE_HZ = 30.0        # Telemetry transmission rate (30 Hz)
DEFAULT_SPEED_SCALE = 0.50 # Default speed multiplier (50%)
TURBO_SPEED_SCALE   = 1.00 # Held R1 / Boost multiplier (100%)
SLOW_SPEED_SCALE    = 0.25 # Held L1 / Precision multiplier (25%)


def apply_deadzone(value: float, threshold: float = DEADZONE) -> float:
    """Applies a deadzone and rescales remaining input to [0, 1]."""
    if abs(value) < threshold:
        return 0.0
    sign = 1.0 if value > 0 else -1.0
    return sign * (abs(value) - threshold) / (1.0 - threshold)


class RobotState:
    """Thread-safe state bridge between Pygame main thread and Bleak BLE worker thread."""
    def __init__(self):
        self._command = "S\n"
        self._lock = threading.Lock()
        self.connected = False
        self.running = True
        self.connect_failed = False

    def set_command(self, cmd: str):
        with self._lock:
            self._command = cmd

    def get_command(self) -> str:
        with self._lock:
            return self._command


async def find_device(target_address: str = None):
    """Scans for the robot BLE peripheral by name or MAC address."""
    print(f"Scanning for BLE device (Target: '{BLE_DEVICE_NAME}'" + (f" or {target_address}" if target_address else "") + ")...")
    
    if target_address:
        device = await BleakScanner.find_device_by_address(target_address, timeout=10.0)
        if device:
            return device

    devices = await BleakScanner.discover(timeout=7.0)
    for d in devices:
        if d.name and BLE_DEVICE_NAME.lower() in d.name.lower():
            return d
    return None


async def ble_worker_task(target_address: str, state: RobotState):
    """Async task running in dedicated MTA worker thread to handle Bleak WinRT callbacks."""
    device = await find_device(target_address)
    if not device:
        print(f"\n[ERROR] Could not find '{BLE_DEVICE_NAME}'.")
        print("Ensure the Arduino UNO R4 WiFi is powered on and running bluetoothDemo.ino.")
        state.connect_failed = True
        state.running = False
        return

    print(f"[OK] Connecting to {device.name} ({device.address})...")
    try:
        async with BleakClient(device) as client:
            if not client.is_connected:
                print("[ERROR] Failed to establish BLE connection.")
                state.connect_failed = True
                state.running = False
                return

            state.connected = True
            print(f"[CONNECTED] Connected to {device.name}!")
            print("=" * 65)
            print("CONTROLS:")
            print("  Left Stick:          Holonomic translation (Forward/Back & Strafe Left/Right)")
            print("  Right Stick X:       Rotate In-Place (Clockwise / Counter-Clockwise)")
            print("  Hold R1 (RB):        Turbo Mode (100% Speed)")
            print("  Hold L1 (LB):        Precision Mode (25% Speed)")
            print("  Circle / Square:     Emergency Stop / Brake")
            print("  D-Pad Up / Down:     Increase / Decrease Base Speed")
            print("  Ctrl+C:              Safely stop robot and quit")
            print("=" * 65)

            interval = 1.0 / LOOP_RATE_HZ
            while state.running and client.is_connected:
                start_time = time.time()
                cmd = state.get_command()

                try:
                    await client.write_gatt_char(CHAR_UUID, cmd.encode("ascii"), response=False)
                except Exception as e:
                    print(f"\n[WARN] BLE write error: {e}")
                    break

                elapsed = time.time() - start_time
                if elapsed < interval:
                    await asyncio.sleep(interval - elapsed)

            # Emergency stop on exit
            try:
                await client.write_gatt_char(CHAR_UUID, b"S\n", response=False)
                await asyncio.sleep(0.1)
            except Exception:
                pass

    except Exception as e:
        print(f"\n[ERROR] BLE connection error: {e}")
    finally:
        state.connected = False
        state.running = False
        print("\n[DISCONNECTED] Robot safely stopped.")


def run_ble_thread(target_address: str, state: RobotState):
    """Runs Bleak asyncio loop in a clean MTA thread, isolated from Pygame's STA context."""
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    try:
        loop.run_until_complete(ble_worker_task(target_address, state))
    finally:
        loop.close()


def main():
    parser = argparse.ArgumentParser(description="PS4 Controller to TritonBots BLE Bridge")
    parser.add_argument("--address", type=str, default=None, help="Optional MAC or BLE UUID of the Arduino UNO R4 WiFi")
    args = parser.parse_args()

    # 1. Initialize Pygame & Controller on main thread
    pygame.init()
    pygame.joystick.init()

    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        print("\n[ERROR] No game controller detected!")
        print("Please plug in your PS4 controller via USB and run this script again.\n")
        return

    controller = pygame.joystick.Joystick(0)
    controller.init()
    print(f"[OK] Controller detected: {controller.get_name()}")
    print(f"     Axes: {controller.get_numaxes()}, Buttons: {controller.get_numbuttons()}\n")

    # 2. Start BLE Worker Thread (MTA isolated from SDL STA)
    state = RobotState()
    ble_thread = threading.Thread(
        target=run_ble_thread,
        args=(args.address, state),
        daemon=True
    )
    ble_thread.start()

    # Wait for BLE to connect or fail
    while state.running and not state.connected:
        time.sleep(0.1)

    if not state.connected:
        return

    # 3. Main Pygame Controller Loop
    base_speed = DEFAULT_SPEED_SCALE
    last_dpad_up = False
    last_dpad_down = False

    try:
        while state.running and state.connected:
            pygame.event.pump()

            # --- Read Buttons & Adjust Speed Scale ---
            # Check D-Pad for base speed adjustment
            hats = controller.get_numhats()
            if hats > 0:
                hat_x, hat_y = controller.get_hat(0)
                if hat_y == 1 and not last_dpad_up:
                    base_speed = min(1.0, base_speed + 0.10)
                    print(f"\nBase Speed increased: {base_speed*100:.0f}%")
                elif hat_y == -1 and not last_dpad_down:
                    base_speed = max(0.10, base_speed - 0.10)
                    print(f"\nBase Speed decreased: {base_speed*100:.0f}%")
                last_dpad_up = (hat_y == 1)
                last_dpad_down = (hat_y == -1)

            # Buttons:
            # Button 1: Circle, Button 2: Square (Emergency Stop)
            # Button 9: L1 (Precision), Button 10: R1 (Turbo)
            e_stop = False
            boost = False
            slow = False

            num_buttons = controller.get_numbuttons()
            if num_buttons > 2:
                e_stop = controller.get_button(1) or controller.get_button(2)
            elif num_buttons > 1:
                e_stop = controller.get_button(1)

            if num_buttons > 10:
                boost = bool(controller.get_button(10))
                slow = bool(controller.get_button(9))

            # Calculate active speed multiplier
            if boost:
                active_speed = TURBO_SPEED_SCALE
                mode_str = "TURBO (100%)"
            elif slow:
                active_speed = SLOW_SPEED_SCALE
                mode_str = "PRECISION (25%)"
            else:
                active_speed = base_speed
                mode_str = f"NORMAL ({active_speed*100:.0f}%)"

            # --- Read Joystick Axes ---
            # Left Stick: Axis 1 is Up(-)/Down(+), Axis 0 is Left(-)/Right(+)
            raw_vx = -controller.get_axis(1) if controller.get_numaxes() > 1 else 0.0
            raw_vy = controller.get_axis(0) if controller.get_numaxes() > 0 else 0.0

            # Right Stick: Axis 2 or 3 is Left(-)/Right(+)
            raw_omega = 0.0
            if controller.get_numaxes() >= 4:
                raw_omega = controller.get_axis(2 if abs(controller.get_axis(2)) > abs(controller.get_axis(3)) else 3)
            elif controller.get_numaxes() >= 3:
                raw_omega = controller.get_axis(2)

            # Invert Vy so Left is +Vy and Right is -Vy
            raw_vy = -raw_vy

            # Invert Omega so Left is +Omega (CCW) and Right is -Omega (CW)
            raw_omega = -raw_omega

            # Apply deadbands
            norm_vx = apply_deadzone(raw_vx)
            norm_vy = apply_deadzone(raw_vy)
            norm_omega = apply_deadzone(raw_omega)

            # Check for Emergency Stop button
            if e_stop:
                command = "S\n"
                sys.stdout.write(f"\r[EMERGENCY STOP] All motors stopped!                       ")
            else:
                # Scale to -100 to 100 percentage range for Arduino
                vx = norm_vx * active_speed * 100.0
                vy = norm_vy * active_speed * 100.0
                omega = norm_omega * active_speed * 100.0

                command = f"V {vx:.1f} {vy:.1f} {omega:.1f}\n"
                sys.stdout.write(
                    f"\r[{mode_str}] Vx: {vx:6.1f} | Vy: {vy:6.1f} | Omega: {omega:6.1f}  "
                )
            sys.stdout.flush()

            # Push command to BLE worker thread
            state.set_command(command)

            time.sleep(1.0 / LOOP_RATE_HZ)

    except KeyboardInterrupt:
        print("\n\nUser interrupted. Safely stopping robot...")
    finally:
        state.running = False
        state.set_command("S\n")
        ble_thread.join(timeout=2.0)
        pygame.quit()
        print("Bridge closed.")


if __name__ == "__main__":
    main()

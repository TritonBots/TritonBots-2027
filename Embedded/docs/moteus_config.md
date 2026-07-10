# Moteus Servo Configuration Notes

This document summarizes the configuration values and open questions for the Moteus drives used on this robot.

> Tip: Parameter names are written in backticks so they’re easy to copy/paste into a config.

---

## Motor ID mapping

The `id` assignment is arbitrary but **must be consistent** across firmware/config files.

| Location | Motor | `id` |
|---|---|---:|
| Front Left wheel | Wheel motor | 1 |
| Front Right wheel | Wheel motor | 2 |
| Back Right wheel | Wheel motor | 3 |
| Back Left | Wheel motor | 4 |
| Dribbler | Dribbler motor | 5 |

---

## Core configuration

- `id`: set to the motor’s corresponding ID number based on its location.
- `servopos.position_min` = `NaN`
- `servopos.position_max` = `NaN`

---

## Safety / limit configuration

- `servo.fault_position_error` = `NaN`
- `servo.fault_velocity_error` = `NaN`

### TODO (Safety tuning)

- TODO: look into configuring `servo.max_position_slip` because it can be used to prevent "catching up" in velocity mode
- TODO: look into configuring `servo.max_velocity_slip` because it can be used to ensure acceleration limits are obeyed in velocity mode
- TODO: ask Electrical team what `servo.max_voltage` should be configured to. This configuration should be for safety rather than changing motor behavior
- TODO: configure `servo.derate_temperature` and `servo.motor_derate_temperature` to a safe temperature to prevent the motors from overheating from applying a torque too high for too long
- TODO: `servo.fault_temperature` and `servo.motor_fault_temperature` configure these as a safety limit. The default value is most likely already good enough.
- TODO: ask Electrical team what `servo.max_current_A` should be configured to. Previously, it was set to 8 Amps.
- TODO: configure `servo.max_velocity` as a safety limit for absurd velocities. Absurd velocities are values 40+ rev/s.
- TODO: look into `servo.default_timeout_s`. Set this to `nan` to prevent the motor from ever entering a timeout state.


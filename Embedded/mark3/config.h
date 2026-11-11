#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <cmath>
#include "ACAN2517FD.h"
#include <MoteusAcan2517fd.h>
#include "Moteus.h"

typedef Moteus::Options Options;
typedef Moteus::PositionMode::Command PositionCommand;
typedef ACAN2517FD CANDriver;
typedef ACAN2517FDSettings CANSettings;

// Put consts that need regular configuration below
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "password"
#define LOCAL_PORT 1234

#define HOST_IP "255.255.0.0"
#define HOST_PORT 1000

// Put consts that need one-time configuration below
#define DRIBBLER_SPEED 10
#define DRIBBLER_DROP STOP_MOTOR

#define VELOCITY_MODE NAN
#define MIN_VELOCITY 0
#define MAX_VELOCITY 100
#define STOP_MOTOR 0
#define MIN_DASH_POWER 0
#define MAX_DASH_POWER 100

#define MCP2517_SCK 9  // SCK input of MCP2517 
#define MCP2517_SDI 10 // SDI input of MCP2517 
#define MCP2517_SDO 11 // SDO output of MCP2517
#define MCP2517_CS 17  // CS input of MCP2517  
#define MCP2517_INT 7  // INT output of MCP2517

#define KICKER_PIN 4
#define KICK_PULSE_DURATION_MS 15 // Safe solenoid pulse duration in ms at 100% power
#define KICK_COOLDOWN_MS 1000      // Minimum time between kicks for capacitor recharge in ms

#define PACKET_BUFFER_SIZE 255
#define NO_SOCKET_AVAILABLE 0
#define EMPTY_PACKET_BUFFER 0

#define FL_WHEEL_ANGLE 0.349066f // in radians (~20 deg)
#define FR_WHEEL_ANGLE -0.349066f // in radians (~-20 deg)
#define BR_WHEEL_ANGLE 1.0472f // in radians (~60 deg)
#define BL_WHEEL_ANGLE -1.0472f // in radians (~-60 deg)

#define ROBOT_DIAMETER 0.2f // Robot chassis diameter in meters.
#define WHEEL_DIAMETER 0.06f // Wheel diameter in meters.
#define ROBOT_CIRCUMFERENCE ((ROBOT_DIAMETER) * PI) // Robot circumference in meters.
#define WHEEL_CIRCUMFERENCE ((WHEEL_DIAMETER) * PI) // Wheel circumference in meters.
#define ROBOT_TO_WHEEL_CIRCUMFERENCE_RATIO ((ROBOT_CIRCUMFERENCE) / (WHEEL_CIRCUMFERENCE)) // Converts robot rotation to wheel travel.

#define ROBOT_ID_INDEX 0
#define CMD_CHAR_INDEX 2

// Robot identity
#define THIS_ROBOT_ID 1 // ID of this specific robot (1-6). Set to 0 to accept commands for any ID.
#define MIN_ROBOT_ID 1
#define MAX_ROBOT_ID 6

// Command strings matching ai-team basic_commands.py, naive.py, and networking
#define DASH_CMD_STR   "dash"
#define TURN_CMD_STR   "turn"
#define KICK_CMD_STR   "kick"
#define DONE_CMD_STR   "done"
#define FAILED_CMD_STR "failed"
#define STOP_CMD_STR   "stop"
#define CATCH_CMD_STR  "catch"
#define DROP_CMD_STR   "drop"
#define NONE_CMD_STR   "none"

#define NUM_CMDS 6
#define DASH_CMD_CHAR 'd'
#define TURN_CMD_CHAR 't'
#define KICK_CMD_CHAR 'k'
#define DROP_CMD_CHAR 'o'
#define CATCH_CMD_CHAR 'c'
#define STOP_CMD_CHAR 'q'

// Put consts that should never need configuration below
#define BAUD_RATE 115200

#define FL_MOTOR_ID 1
#define FR_MOTOR_ID 2
#define BR_MOTOR_ID 3
#define BL_MOTOR_ID 4
#define DR_MOTOR_ID 5

#define NUM_MOTORS 5
#define NUM_WHEELS ((NUM_MOTORS) - 1)

#define MIN_NUM_ARGS 2
#define MAX_NUM_ARGS 4

#define CAN_BITRATE (1000ll * 1000ll)
#define CAN_SJW 2
#define CAN_TX_FIFO_SIZE (NUM_MOTORS)
#define CAN_RX_FIFO_SIZE (NUM_MOTORS)

#define CAN_OK_CODE 0

#endif /* CONFIG_H */

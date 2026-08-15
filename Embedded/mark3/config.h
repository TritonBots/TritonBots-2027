#ifndef CONFIG_H
#define CONFIG_H

#include "ACAN2517FD.h"
#include <MoteusAcan2517fd.h>
#include "Moteus.h"

typedef Moteus::Options Options;
typedef Moteus::PositionMode::Command PositionCommand;
typedef ACAN2517FD CANDriver;
typedef ACAN2517FDSettings CANSettings;

#define BAUD_RATE 115200

#define NUM_MOTORS 5
#define NUM_WHEELS (NUM_MOTORS) - 1

#define FL_MOTOR_ID 1
#define FR_MOTOR_ID 2
#define BR_MOTOR_ID 3
#define BL_MOTOR_ID 4
#define DR_MOTOR_ID 5

#define FL_WHEEL_ANGLE 0.349066 // in radians
#define FR_WHEEL_ANGLE -0.349066 // in radians
#define BR_WHEEL_ANGLE 1.0472 // in radians
#define BL_WHEEL_ANGLE -1.0472 // in radians

#define ROBOT_DIAMETER 0.2 // Robot chassis diameter in meters.
#define WHEEL_DIAMETER 0.06 // Wheel diameter in meters.
#define ROBOT_CIRCUMFERENCE ROBOT_DIAMETER * PI // Robot circumference in meters.
#define WHEEL_CIRCUMFERENCE WHEEL_DIAMETER * PI // Wheel circumference in meters.
#define ROBOT_TO_WHEEL_CIRCUMFERENCE_RATIO ROBOT_CIRCUMFERENCE / WHEEL_CIRCUMFERENCE // Converts robot rotation to wheel travel.

#define MCP2517_SCK 9  // SCK input of MCP2517 
#define MCP2517_SDI 10 // SDI input of MCP2517 
#define MCP2517_SDO 11 // SDO output of MCP2517
#define MCP2517_CS 17  // CS input of MCP2517  
#define MCP2517_INT 7  // INT output of MCP2517

#define CAN_BITRATE 1000ll * 1000ll
#define CAN_SJW 2
#define CAN_TX_FIFO_SIZE NUM_MOTORS
#define CAN_RX_FIFO_SIZE NUM_MOTORS

#define CAN_OK_CODE 0

#define VELOCITY_MODE NaN
#define MIN_VELOCITY 0
#define MAX_VELOCITY 100
#define STOP_MOTOR 0
#define MIN_DASH_POWER 0
#define MAX_DASH_POWER 100

#define DRIBBLER_SPEED 10
#define DRIBBLER_DROP STOP_MOTOR





#endif /* CONFIG_H */
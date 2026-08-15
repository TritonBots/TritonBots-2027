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

#define FL_MOTOR_ID 1
#define FR_MOTOR_ID 2
#define BR_MOTOR_ID 3
#define BL_MOTOR_ID 4
#define DR_MOTOR_ID 5

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



#endif /* CONFIG_H */
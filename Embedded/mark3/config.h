#ifndef CONFIG_H
#define CONFIG_H

#include "ACAN2517FD.h"
#include <MoteusAcan2517fd.h>

typedef Moteus::Options Options;
typedef Moteus::PositionMode::Command PositionCommand;
typedef ACAN2517FDSettings CANSettings;

#define BAUD_RATE 115200

#define NUM_MOTORS 2

#define MOTOR_ID_1 1
#define MOTOR_ID_2 2

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

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

#define CAN_ERROR_CODE 0

#define VELOCITY_MODE NaN

static uint32_t gNextSendMillis = 0;
uint16_t gLoopCount = 0;

// ACAN2517FD Driver
ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);

Moteus moteus1(can, []() {
   Options options;
   options.id = MOTOR_ID_1;
   return options;
}());
Moteus moteus2(can, []() {
   Options options;
   options.id = MOTOR_ID_2;
   return options;
}());

PositionCommand position_cmd;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);

   Serial.begin(BAUD_RATE);
   while (!Serial) {}

   SPI.begin();

   CANSettings settings(
      ACAN2517FDSettings::OSC_20MHz, 
      CAN_BITRATE, 
      DataBitRateFactor::x1
   );

   /*
   A higher SJW value allows a node to tolerate larger clock discrepancies between different devices on the network. However, an excessively high SJW can make the system more vulnerable to noise on the bus.
   */
   settings.mArbitrationSJW = CAN_SJW;
   settings.mDriverTransmitFIFOSize = CAN_TX_FIFO_SIZE;
   settings.mDriverReceiveFIFOSize = CAN_RX_FIFO_SIZE;

   const uint32_t errorCode = can.begin(settings, [] { can.isr(); });

   while (errorCode != CAN_ERROR_CODE) {
      Serial.print(F("CAN error 0x"));
      Serial.println(errorCode, HEX);
      delay(1000);
   }

   // To clear any faults the controllers may have, we start by sending
   // a stop command to each.
   moteus1.SetStop();
   moteus2.SetStop();
}

void loop() {
   PositionCommand cmd;
   cmd.position = VELOCITY_MODE;
   cmd.velocity = 0.2;

   moteus1.SetPosition(cmd);
   moteus2.SetBrake();
   delay(20);
}
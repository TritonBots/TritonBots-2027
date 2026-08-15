#include "MotorController.h"

static uint32_t gNextSendMillis = 0;
uint16_t gLoopCount = 0;

// ACAN2517FD Driver
ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);

Moteus moteus1(can, []() {
   Options options;
   options.id = MOTOR_ID_1;
   return options;
}());
PositionCommand motorCmd1;

Motor motor1(&moteus1, &motorCmd1);

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);

   Serial.begin(BAUD_RATE);

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
   // configs how many commands the CAN sends/receives at a time
   settings.mDriverTransmitFIFOSize = CAN_TX_FIFO_SIZE;
   settings.mDriverReceiveFIFOSize = CAN_RX_FIFO_SIZE;

   const uint32_t errorCode = can.begin(settings, [] { can.isr(); });

   // while the CAN bus has an error, print the error code
   while (errorCode != CAN_OK_CODE) {
      Serial.print(F("CAN error 0x"));
      Serial.println(errorCode, HEX);
      delay(1000);
   }

   moteus1.SetStop();
}

void loop() {
   PositionCommand cmd;
   cmd.position = VELOCITY_MODE;
   cmd.velocity = 0.2;

   moteus1.SetPosition(cmd);
   delay(20);
}
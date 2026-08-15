#include "MotorController.h"

// ACAN2517FD Driver
ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);

Moteus moteus1(can, []() {
   Options options;
   options.id = MOTOR_ID_1;
   return options;
}());
PositionCommand motorCmd1;

Moteus moteus2(can, []() {
   Options options;
   options.id = MOTOR_ID_2;
   return options;
}());
PositionCommand motorCmd2;

Motor motor1(&moteus1, &motorCmd1);
Motor motor2(&moteus2, &motorCmd2);

Motor* motors[NUM_MOTORS] = {
   &motor1,
   &motor2
};

CANSettings settings(
   ACAN2517FDSettings::OSC_20MHz, 
   CAN_BITRATE, 
   DataBitRateFactor::x1
);

MotorController controller(&can, *motors, &settings);

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);

   Serial.begin(BAUD_RATE);

   SPI.begin();

   controller.begin([] { can.isr(); });

   controller.setStop();
}

void loop() {
   controller.setVelocity(0.2f);
   controller.sendCommand();
   delay(20);
}
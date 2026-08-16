#include "MotorController.h"
#include "WiFiController.h"

// ACAN2517FD Driver
static ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);

static Moteus moteus1(can, []() {
   Options options;
   options.id = FL_MOTOR_ID;
   return options;
}());
static PositionCommand motorCmd1;

static Moteus moteus2(can, []() {
   Options options;
   options.id = FR_MOTOR_ID;
   return options;
}());
static PositionCommand motorCmd2;

static Moteus moteus3(can, []() {
   Options options;
   options.id = BR_MOTOR_ID;
   return options;
}());
static PositionCommand motorCmd3;

static Moteus moteus4(can, []() {
   Options options;
   options.id = BL_MOTOR_ID;
   return options;
}());
static PositionCommand motorCmd4;

static Moteus moteus5(can, []() {
   Options options;
   options.id = DR_MOTOR_ID;
   return options;
}());
static PositionCommand motorCmd5;

static Motor motor1(&moteus1, &motorCmd1);
static Motor motor2(&moteus2, &motorCmd2);
static Motor motor3(&moteus3, &motorCmd3);
static Motor motor4(&moteus4, &motorCmd4);
static Motor motor5(&moteus5, &motorCmd5);

static Motor* motors[NUM_MOTORS] = {
   &motor1,
   &motor2,
   &motor3,
   &motor4,
   &motor5
};

static CANSettings settings(
   ACAN2517FDSettings::OSC_20MHz, 
   CAN_BITRATE, 
   DataBitRateFactor::x1
);

static MotorController motorController(&can, *motors, &settings);

static WiFiController wifiController(WIFI_SSID, WIFI_PASSWORD, LOCAL_PORT);


// TODO: create a kicker controller

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);

   Serial.begin(BAUD_RATE);

   SPI.begin();

   motorController.begin([] { can.isr(); });

   motorController.setStop();
}

void loop() {
   motorController.setVelocity(0.2f);
   motorController.sendCommand();
   delay(20);
}
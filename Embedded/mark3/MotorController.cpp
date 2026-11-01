#include "MotorController.h"

MotorController::MotorController(CANDriver *driver, Motor **motors, CANSettings *settings) {
   this->driver = driver;
   this->motors = motors;
   this->settings = settings;
}

void MotorController::configSettings() {
   /*
   A higher SJW value allows a node to tolerate larger clock discrepancies between different devices on the network. However, an excessively high SJW can make the system more vulnerable to noise on the bus.
   */
   settings->mArbitrationSJW = CAN_SJW;
   // configs how many commands the CAN sends/receives at a time
   settings->mDriverTransmitFIFOSize = CAN_TX_FIFO_SIZE;
   settings->mDriverReceiveFIFOSize = CAN_RX_FIFO_SIZE;
}

// Convert degrees to radians.
float MotorController::degToRad(const float angle) {
  return angle * PI / 180.0f;
}

// Convert angular speed from degrees per second into wheel revolutions per second.
float MotorController::degPerSecondToRPS(const float degPerSecond) {
  return (degPerSecond * ROBOT_TO_WHEEL_CIRCUMFERENCE_RATIO) / 360.0f;
}

void MotorController::begin(void (*isrCallback)()) {
   configSettings();
   const uint32_t errorCode = driver->begin(*settings, isrCallback);

   while (errorCode != CAN_OK_CODE) {
      Serial.print(F("CAN error 0x"));
      Serial.println(errorCode, HEX);
      delay(1000);
   }
}

void MotorController::setStop() {
   for (int motorIndex = 0; motorIndex < NUM_MOTORS; motorIndex++) {
      motors[motorIndex]->setStop();
   }
}

void MotorController::setStop(unsigned int motorID) {
   if (motorID >= 1 && motorID <= NUM_MOTORS) {
      motors[motorID - 1]->setStop();
   }
}

void MotorController::setVelocity(unsigned int motorID, float vel) {
   if (motorID >= 1 && motorID <= NUM_MOTORS) {
      motors[motorID - 1]->setVelocity(vel);
   }
}

void MotorController::setVelocity(float vel) {
   for (int motorIndex = 0; motorIndex < NUM_MOTORS; motorIndex++) {
      motors[motorIndex]->setVelocity(vel);
   }
}

void MotorController::turn(float speed) {
   static const float arbitraryMultiplier = 0.2f;
   float rps = degPerSecondToRPS(speed) * arbitraryMultiplier;
   // Only drive locomotion wheels (1 to NUM_WHEELS), not the dribbler
   for (unsigned int motorID = 1; motorID <= NUM_WHEELS; motorID++) {
      setVelocity(motorID, -rps);
   }
}

void MotorController::dash(float power, float direction) {
   direction = degToRad(direction);
   power = ((power - MIN_DASH_POWER) 
   * (MAX_VELOCITY - STOP_MOTOR)) 
   / (MAX_DASH_POWER - MIN_DASH_POWER) 
   + STOP_MOTOR;

   static const float motorAngles[NUM_WHEELS] = {
      FL_WHEEL_ANGLE,
      FR_WHEEL_ANGLE,
      BR_WHEEL_ANGLE,
      BL_WHEEL_ANGLE
   };

   for (unsigned int motorID = 1; motorID <= NUM_WHEELS; motorID++) {
      setVelocity(motorID, power * cos(motorAngles[motorID - 1] - direction));
   }
}

void MotorController::dribblerCatch() {
   setVelocity(DR_MOTOR_ID, DRIBBLER_SPEED);
}

void MotorController::dribblerDrop() {
   setVelocity(DR_MOTOR_ID, DRIBBLER_DROP);
}

void MotorController::stopLocomotion() {
   for (unsigned int motorID = 1; motorID <= NUM_WHEELS; motorID++) {
     setVelocity(motorID, STOP_MOTOR);
   }
}

void MotorController::stop() {
   setVelocity(STOP_MOTOR);
}

void MotorController::sendCommand() {
   for (int motorIndex = 0; motorIndex < NUM_MOTORS; motorIndex++) {
      motors[motorIndex]->sendCommand();
   }
}

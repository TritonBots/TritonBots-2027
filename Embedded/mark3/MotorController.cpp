#include "MotorController.h"

MotorController::MotorController(CANDriver *driver, Motor *motors, CANSettings *settings) {
   this->driver = driver;
   this->motors = motors;
   this->settings = settings;
   configSettings(); // TODO: might cause a runtime error because it's not called inside of setup()
}

void MotorController::setStop() {
   for (int motorIndex=0;motorIndex<NUM_MOTORS;motorIndex++) {
      motors[motorIndex].setStop();
   }
}

void MotorController::setStop(unsigned int motorID) {
   motors[motorID].setStop();
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

void MotorController::begin(void (*isrCallback)()) {
   const uint32_t errorCode = driver->begin(*settings, isrCallback);

   while (errorCode != CAN_OK_CODE) {
      Serial.print(F("CAN error 0x"));
      Serial.println(errorCode, HEX);
      delay(1000);
   }
}

void MotorController::setVelocity(unsigned int motorID, float vel) {
   motors[motorID-1].setVelocity(vel);
}

void MotorController::setVelocity(float vel) {
   for (int motorIndex=0;motorIndex<NUM_MOTORS;motorIndex++) {
      motors[motorIndex].setVelocity(vel);
   }
}

void MotorController::sendCommand() {
   for (int motorIndex=0;motorIndex<NUM_MOTORS;motorIndex++) {
      motors[motorIndex].sendCommand();
   }
}
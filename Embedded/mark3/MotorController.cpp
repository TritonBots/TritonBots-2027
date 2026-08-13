#include "MotorController.h"

MotorController::MotorController(CANDriver *driver, Motor *motors, CANSettings *settings) {
   this->driver = driver;
   this->motors = motors;
   this->settings = settings;
}
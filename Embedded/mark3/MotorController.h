#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

class MotorController {

   private:

   CANDriver *driver;

   Motor *motors;

   CANSettings *settings;


   public:

  MotorController(CANDriver *driver, Motor *motors, CANSettings *settings);



};



#endif /* MOTOR_CONTROLLER_H */
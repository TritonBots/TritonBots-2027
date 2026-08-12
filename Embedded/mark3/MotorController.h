#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

class MotorController {

   private:

   ACAN2517FD canDriver;

   Motor motors[NUM_MOTORS];

   CANSettings settings;


   public:

   MotorController(ACAN2517FD canDriver, Motor motors[NUM_MOTORS], CANSettings settings);



};



#endif /* MOTOR_CONTROLLER_H */
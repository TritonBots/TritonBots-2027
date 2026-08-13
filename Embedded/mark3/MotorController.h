#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

class MotorController {

   private:

   ACAN2517FD *canDriver;

   Motor *motors;

   CANSettings *settings;


   public:

  



};



#endif /* MOTOR_CONTROLLER_H */
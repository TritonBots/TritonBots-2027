#ifndef MOTOR_H
#define MOTOR_H

#include "config.h"

class Motor {

   private:

   Moteus *motor;
   PositionCommand *motorCommand;

   public:

   Motor(Moteus *motor, PositionCommand *motorCommand);

   void setStop();
   
   void setVelocity(float vel);

   void sendCommand();
};


#endif /* MOTOR_H */
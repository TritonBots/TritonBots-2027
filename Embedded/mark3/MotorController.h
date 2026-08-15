#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

class MotorController {

  private:

  CANDriver *driver;

  Motor *motors;

  CANSettings *settings;

   
  void configSettings();

  public:

  MotorController(CANDriver *driver, Motor *motors, CANSettings *settings);

  void begin(void (*isrCallback)());

  void setStop();

  void setStop(unsigned int motorID);

  void setVelocity(unsigned int motorID, float vel);

  void setVelocity(float vel);

  void sendCommand();

};



#endif /* MOTOR_CONTROLLER_H */
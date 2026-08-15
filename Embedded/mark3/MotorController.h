#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include "Motor.h"

class MotorController {

  private:

  CANDriver *driver;

  Motor *motors;

  CANSettings *settings;

  void configSettings();
  
  float degToRad(const float angle);
  float degPerSecondToRPS(const float degPerSecond);

  public:

  MotorController(CANDriver *driver, Motor *motors, CANSettings *settings);

  void begin(void (*isrCallback)());

  void setStop();

  void setStop(unsigned int motorID);

  void setVelocity(unsigned int motorID, float vel);

  void setVelocity(float vel);

  void turn(float speed);

  void dash(float power, float direction);

  void dribblerCatch();

  void sendCommand();

};



#endif /* MOTOR_CONTROLLER_H */
#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "MotorController.h"
#include "WiFiController.h"
#include "KickerController.h"
#include "config.h"

class RobotController {

   private:

   MotorController* motorController;

   WiFiController* wifiController;

   KickerController* kickerController;

   bool isValidCommandChar(const char command);

   public:

   RobotController(
      MotorController* motorController, 
      WiFiController* wifiController,
      KickerController* kickerController
   );

   void parsePacket();

   void sendCommand();

   void stopMotors();

   void beginMotorControl(void (*isrCallback)());

   void pollKicker();
};


#endif /* ROBOT_CONTROLLER_H */
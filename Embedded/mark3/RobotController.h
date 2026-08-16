#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "MotorController.h"
#include "WiFiController.h"

#define ROBOT_ID_INDEX 0
#define CMD_CHAR_INDEX 2

#define MIN_ROBOT_ID 1
#define MAX_ROBOT_ID 6

#define NUM_CMDS 6
#define DASH_CMD_CHAR 'd'
#define TURN_CMD_CHAR 't'
#define KICK_CMD_CHAR 'k'
#define DROP_CMD_CHAR 'o'
#define CATCH_CMD_CHAR 'c'
#define STOP_CMD_CHAR 'q'

class RobotController {

   private:

   MotorController* motorController;

   WiFiController* wifiController;

   bool isValidCommandChar(const char command);

   public:

   RobotController(MotorController* motorController, WiFiController* wifiController);

   void parsePacketAndSendCommand();
};


#endif /* ROBOT_CONTROLLER_H */
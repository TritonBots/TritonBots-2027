#include "RobotController.h"

RobotController::RobotController(
   MotorController* motorController, 
   WiFiController* wifiController
)
 : motorController(motorController), 
 wifiController(wifiController) {

}

void RobotController::parsePacketAndSendCommand() {
   if (!wifiController->isPacketAvailable()) {
      Serial.println(F("No Packets Available to parse!"));
      return;
   }
   char* udpPacket = wifiController->parsePacket();

   /*
   
   Command format:

   "<robot ID> <command char> <float arg1> <float arg2>"
   
   
   */

   const unsigned int robotID = udpPacket[ROBOT_ID_INDEX] - '0';

   if (MIN_ROBOT_ID > robotID || MAX_ROBOT_ID < robotID) {
      Serial.println(F("Invalid Robot ID parsed!"));
      return;
   }

   const char command = udpPacket[CMD_CHAR_INDEX];

   if (!isValidCommandChar(command)) {
      Serial.println(F("Invalid Command Character parsed!"));
      return;
   }

   // TODO: parse the commands


}

bool RobotController::isValidCommandChar(const char command) {
   static const char validCommandChars[NUM_CMDS] = {
      DASH_CMD_CHAR,
      TURN_CMD_CHAR,
      KICK_CMD_CHAR,
      DROP_CMD_CHAR,
      CATCH_CMD_CHAR,
      STOP_CMD_CHAR
   };

   for (int i=0;i<NUM_CMDS;i++) {
      if (validCommandChars[i] == command) {
         return true;
      }
   }
   return false;
}
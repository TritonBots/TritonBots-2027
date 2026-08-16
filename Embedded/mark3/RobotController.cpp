#include "RobotController.h"

RobotController::RobotController(
   MotorController* motorController, 
   WiFiController* wifiController,
   KickerController* kickerController
)
 : motorController(motorController), 
 wifiController(wifiController),
 kickerController(kickerController) {

}

void RobotController::parsePacket() {
   if (!wifiController->isPacketAvailable()) {
      Serial.println(F("No Packets Available to parse!"));
      return;
   }
   char* udpPacket = wifiController->parsePacket();

   /*
   
   Command format:
   "<robot ID> <command char> <float arg1> <float arg2>"
   
   
   */

   const char command = udpPacket[CMD_CHAR_INDEX];

   // 1. Create variables to hold the parsed values
   int parsedRobotID = 0;
   char parsedCommand = '\0';
   float arg1 = 0.0f;
   float arg2 = 0.0f;

   // 2. Use sscanf to safely parse variable-length tokens from the char array
   // %d = integer, %c = character, %f = float
   int parsedItems = sscanf(udpPacket, "%d %c %f %f", &parsedRobotID, &parsedCommand, &arg1, &arg2);

   // 3. Verify that all 4 expected items were successfully successfully read
   if (parsedItems < MIN_NUM_ARGS && parsedItems > MAX_NUM_ARGS ) {
      Serial.println(F("Invalid number of arguments in command!"));
      return;
   }

   // 4. Run validation checks on the safely parsed values
   if (MIN_ROBOT_ID > parsedRobotID || MAX_ROBOT_ID < parsedRobotID) {
      Serial.println(F("Invalid Robot ID parsed!"));
      return;
   }

   if (!isValidCommandChar(parsedCommand)) {
      Serial.println(F("Invalid Command Character parsed!"));
      return;
   }

   switch(parsedCommand) {
      case 'q':
         motorController->stop();
         break;
      case 'd':
         motorController->dash(arg1, arg2);
         break;
      case 't':
         motorController->turn(arg1);
         break;
      case 'k':
         kickerController->kick();
         break;
      case 'c':
         motorController->dribblerCatch();
         break;
      case 'o':
         motorController->dribblerDrop();
         break;
      default:
         Serial.println(F("Invalid Command reached!"));
         return;
   }
}

void RobotController::sendCommand() {
   motorController->sendCommand();
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
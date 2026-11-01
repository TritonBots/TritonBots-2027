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

void RobotController::begin(void (*isrCallback)()) {
   kickerController->begin();
   wifiController->begin();
   motorController->begin(isrCallback);
   motorController->stop();
}

void RobotController::parsePacket() {
   char* udpPacket = wifiController->parsePacket();
   if (udpPacket == nullptr) {
      return;
   }

   /*
   Command format:
   "<robot ID> <command char> <float arg1> <float arg2>"
   */

   // 1. Create variables to hold the parsed values
   int parsedRobotID = 0;
   char parsedCommand = '\0';
   float arg1 = 0.0f;
   float arg2 = 0.0f;

   // 2. Use sscanf to safely parse variable-length tokens from the char array
   // %d = integer, %c = character, %f = float
   int parsedItems = sscanf(udpPacket, "%d %c %f %f", &parsedRobotID, &parsedCommand, &arg1, &arg2);

   // 3. Verify that at least robot ID and command char were read
   if (parsedItems < MIN_NUM_ARGS || parsedItems > MAX_NUM_ARGS) {
      Serial.println(F("Invalid number of arguments in command!"));
      return;
   }

   // 4. Run validation checks on the safely parsed values
   if (parsedRobotID < MIN_ROBOT_ID || parsedRobotID > MAX_ROBOT_ID) {
      Serial.println(F("Invalid Robot ID parsed!"));
      return;
   }

   if (!isValidCommandChar(parsedCommand)) {
      Serial.println(F("Invalid Command Character parsed!"));
      return;
   }

   switch(parsedCommand) {
      case STOP_CMD_CHAR:
         motorController->stop();
         break;
      case DASH_CMD_CHAR:
         if (parsedItems < 4) {
            Serial.println(F("Dash command requires power and direction arguments!"));
            return;
         }
         motorController->dash(arg1, arg2);
         break;
      case TURN_CMD_CHAR:
         if (parsedItems < 3) {
            Serial.println(F("Turn command requires speed argument!"));
            return;
         }
         motorController->turn(arg1);
         break;
      case KICK_CMD_CHAR:
         kickerController->kick();
         break;
      case CATCH_CMD_CHAR:
         motorController->dribblerCatch();
         break;
      case DROP_CMD_CHAR:
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

   for (int i = 0; i < NUM_CMDS; i++) {
      if (validCommandChars[i] == command) {
         return true;
      }
   }
   return false;
}

void RobotController::stopMotors() {
   motorController->stop();
}

void RobotController::beginMotorControl(void (*isrCallback)()) {
   motorController->begin(isrCallback);
}

void RobotController::pollKicker() {
   kickerController->handleKickerStatus();
}

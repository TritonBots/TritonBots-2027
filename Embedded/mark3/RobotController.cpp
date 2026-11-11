#include "RobotController.h"
#include <cctype>
#include <cstring>
#include <cmath>

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
   if (udpPacket == nullptr || udpPacket[0] == '\0') {
      return;
   }

   // A single UDP packet may contain multiple newline-separated lines (e.g. from ai-team robot_serialize)
   char* saveptr = nullptr;
   char* line = strtok_r(udpPacket, "\r\n", &saveptr);
   while (line != nullptr) {
      processCommandLine(line);
      line = strtok_r(nullptr, "\r\n", &saveptr);
   }
}

void RobotController::processCommandLine(char* line) {
   if (line == nullptr || line[0] == '\0') {
      return;
   }

   /*
   Command format:
     With Robot ID:    "<robot ID> <command> [float arg1] [float arg2]"
     Without Robot ID: "<command> [float arg1] [float arg2]"

   Supported commands matching ai-team basic_commands.py, naive.py, and networking:
     - "dash <power> <direction>" / "d <power> <direction>"
     - "turn <speed/angle>"       / "t <speed/angle>"
     - "kick [power] [angle]"     / "k [power] [angle]"
     - "done"
     - "failed"
     - "none"
     - "stop"                     / "q"
     - "catch"                    / "c"
     - "drop"                     / "o"
   */

   int parsedRobotID = 0;
   char cmdStr[32] = {0};
   float arg1 = 0.0f;
   float arg2 = 0.0f;
   char* cmdPtr = line;

   // Check if the line begins with a Robot ID integer
   int tempID = 0;
   int charsRead = 0;
   bool hasRobotID = false;
   if (sscanf(line, "%d %n", &tempID, &charsRead) == 1 && tempID >= MIN_ROBOT_ID && tempID <= MAX_ROBOT_ID) {
      hasRobotID = true;
      parsedRobotID = tempID;
      cmdPtr = line + charsRead;
   }

   // If a robot ID was specified and THIS_ROBOT_ID is set (non-zero), filter out commands meant for other robots
   if (hasRobotID && THIS_ROBOT_ID != 0 && parsedRobotID != THIS_ROBOT_ID) {
      return;
   }

   // Parse command string and up to two float arguments using strtof for nano.specs compatibility
   charsRead = 0;
   if (sscanf(cmdPtr, "%31s%n", cmdStr, &charsRead) < 1) {
      return;
   }
   cmdPtr += charsRead;

   int parsedItems = 1;
   char* endPtr = nullptr;
   arg1 = strtof(cmdPtr, &endPtr);
   if (endPtr != cmdPtr) {
      parsedItems++;
      cmdPtr = endPtr;
      arg2 = strtof(cmdPtr, &endPtr);
      if (endPtr != cmdPtr) {
         parsedItems++;
      }
   }

   // Convert command to lowercase for case-insensitive matching
   for (int i = 0; cmdStr[i] != '\0'; i++) {
      cmdStr[i] = tolower((unsigned char)cmdStr[i]);
   }

   if (!isValidCommand(cmdStr)) {
      Serial.print(F("Invalid Command: "));
      Serial.println(cmdStr);
      return;
   }

   if (strcmp(cmdStr, DASH_CMD_STR) == 0 || strcmp(cmdStr, "d") == 0) {
      if (parsedItems < 3) {
         Serial.println(F("Dash command requires power and direction arguments!"));
         return;
      }
      motorController->dash(arg1, arg2);
   } else if (strcmp(cmdStr, TURN_CMD_STR) == 0 || strcmp(cmdStr, "t") == 0) {
      if (parsedItems < 2) {
         Serial.println(F("Turn command requires speed/angle argument!"));
         return;
      }
      motorController->turn(arg1);
   } else if (strcmp(cmdStr, KICK_CMD_STR) == 0 || strcmp(cmdStr, "k") == 0) {
      float kickPower = (parsedItems >= 2) ? arg1 : 100.0f;
      // In shoot(): "kick 80 <angle_diff>"
      if (parsedItems >= 3) {
         if (fabs(arg2) > 1.0f) {
            motorController->turn(arg2);
         } else {
            motorController->stopLocomotion();
         }
      }
      kickerController->kick(kickPower);
   } else if (strcmp(cmdStr, DONE_CMD_STR) == 0 || 
              strcmp(cmdStr, FAILED_CMD_STR) == 0 || 
              strcmp(cmdStr, STOP_CMD_STR) == 0 || 
              strcmp(cmdStr, NONE_CMD_STR) == 0 || 
              strcmp(cmdStr, "q") == 0) {
      motorController->stopLocomotion();
   } else if (strcmp(cmdStr, CATCH_CMD_STR) == 0 || strcmp(cmdStr, "c") == 0) {
      motorController->dribblerCatch();
   } else if (strcmp(cmdStr, DROP_CMD_STR) == 0 || strcmp(cmdStr, "o") == 0) {
      motorController->dribblerDrop();
   }
}

void RobotController::sendCommand() {
   motorController->sendCommand();
}

bool RobotController::isValidCommand(const char* command) {
   if (command == nullptr || command[0] == '\0') {
      return false;
   }

   static const char* const validCommands[] = {
      DASH_CMD_STR,   "d",
      TURN_CMD_STR,   "t",
      KICK_CMD_STR,   "k",
      DONE_CMD_STR,
      FAILED_CMD_STR,
      NONE_CMD_STR,
      STOP_CMD_STR,   "q",
      CATCH_CMD_STR,  "c",
      DROP_CMD_STR,   "o"
   };
   const size_t numValidCommands = sizeof(validCommands) / sizeof(validCommands[0]);

   for (size_t i = 0; i < numValidCommands; i++) {
      if (strcmp(validCommands[i], command) == 0) {
         return true;
      }
   }
   return false;
}

bool RobotController::isValidCommandChar(const char command) {
   char str[2] = { command, '\0' };
   return isValidCommand(str);
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

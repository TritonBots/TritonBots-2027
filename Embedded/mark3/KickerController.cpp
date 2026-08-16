#include "KickerController.h"

KickerController::KickerController(unsigned int kickerPin)
 : kickerPin(kickerPin) {
   timeSinceLastKick = 10000; // some arbitrary, large number about >1000
}

void KickerController::kick() {
   digitalWrite(kickerPin, HIGH);
   timeSinceLastKick = millis();
}

/**
   @brief poll kickerPin and set it LOW if a KICK_DELAY amount of time has passed since kicking
*/
void KickerController::handleKickerStatus() {
   if (digitalRead(kickerPin) == HIGH // attempt short-circuit evaluation first 
   && millis() - timeSinceLastKick > KICK_DELAY) { // more likely to be true more often
      digitalWrite(kickerPin, LOW);
   }
}
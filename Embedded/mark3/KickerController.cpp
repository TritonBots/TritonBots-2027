#include "KickerController.h"

KickerController::KickerController(unsigned int kickerPin)
 : kickerPin(kickerPin), kickStartTime(0), lastKickTime(0), isKicking(false) {
}

void KickerController::begin() {
   pinMode(kickerPin, OUTPUT);
   digitalWrite(kickerPin, LOW);
}

void KickerController::kick() {
   unsigned long now = millis();
   // Prevent kicking if already in a pulse or if capacitor recharge cooldown hasn't elapsed
   if (isKicking || (now - lastKickTime < KICK_COOLDOWN_MS)) {
      return;
   }
   digitalWrite(kickerPin, HIGH);
   kickStartTime = now;
   isKicking = true;
}

/**
   @brief Poll kicker status and set kickerPin LOW once KICK_PULSE_DURATION_MS has passed.
*/
void KickerController::handleKickerStatus() {
   if (isKicking && (millis() - kickStartTime >= KICK_PULSE_DURATION_MS)) {
      digitalWrite(kickerPin, LOW);
      isKicking = false;
      lastKickTime = millis();
   }
}

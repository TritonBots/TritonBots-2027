#include "KickerController.h"

KickerController::KickerController(unsigned int kickerPin)
 : kickerPin(kickerPin), kickStartTime(0), lastKickTime(0), currentPulseDuration(KICK_PULSE_DURATION_MS), isKicking(false) {
}

void KickerController::begin() {
   pinMode(kickerPin, OUTPUT);
   digitalWrite(kickerPin, LOW);
}

void KickerController::kick(float power) {
   unsigned long now = millis();
   // Prevent kicking if already in a pulse or if capacitor recharge cooldown hasn't elapsed
   if (isKicking || (now - lastKickTime < KICK_COOLDOWN_MS)) {
      return;
   }
   if (power <= 0.0f) {
      return;
   }
   if (power > 100.0f) {
      power = 100.0f;
   }
   currentPulseDuration = (unsigned long)(KICK_PULSE_DURATION_MS * (power / 100.0f));
   if (currentPulseDuration < 1) {
      currentPulseDuration = 1;
   }

   digitalWrite(kickerPin, HIGH);
   kickStartTime = now;
   isKicking = true;
}

/**
   @brief Poll kicker status and set kickerPin LOW once currentPulseDuration has passed.
*/
void KickerController::handleKickerStatus() {
   if (isKicking && (millis() - kickStartTime >= currentPulseDuration)) {
      digitalWrite(kickerPin, LOW);
      isKicking = false;
      lastKickTime = millis();
   }
}

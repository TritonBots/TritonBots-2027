#ifndef KICKER_CONTROLLER_H
#define KICKER_CONTROLLER_H

#include "Arduino.h"

#define KICK_DELAY 1000

class KickerController {

   private:

   unsigned int kickerPin;

   unsigned long timeSinceLastKick; // in milliseconds

   public:

   KickerController(unsigned int kickerPin);

   void kick();

   void handleKickerStatus();

};


#endif /* KICKER_CONTROLLER_H */
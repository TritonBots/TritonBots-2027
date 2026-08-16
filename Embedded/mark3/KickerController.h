#ifndef KICKER_CONTROLLER_H
#define KICKER_CONTROLLER_H

#include "Arduino.h"
#include "config.h"

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
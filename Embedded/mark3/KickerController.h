#ifndef KICKER_CONTROLLER_H
#define KICKER_CONTROLLER_H

#include "Arduino.h"
#include "config.h"

class KickerController {

   private:

   unsigned int kickerPin;

   unsigned long kickStartTime;
   unsigned long lastKickTime;
   bool isKicking;

   public:

   KickerController(unsigned int kickerPin);

   void begin();

   void kick();

   void handleKickerStatus();

};

#endif /* KICKER_CONTROLLER_H */

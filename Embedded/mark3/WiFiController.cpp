#include "WiFiController.h"

WiFiController::WiFiController(char* ssid, char* password, unsigned int localPort)
 : ssid(ssid), password(password), localPort(localPort) {
   if (NO_SOCKET_AVAILABLE == udp.begin(localPort)) {
      Serial.println(F("No socket available"));
   }
 }
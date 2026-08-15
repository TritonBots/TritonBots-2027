#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFiS3.h>

#define NO_SOCKET_AVAILABLE 0

#define PACKET_BUFFER_SIZE 255

class WiFiController {
   private:

   char* ssid;
   char* password;

   unsigned int localPort;

   char packetBuffer[PACKET_BUFFER_SIZE];

   WiFiUDP udp;

   public:

   WiFiController(char* ssid, char* password, unsigned int localPort);


};



#endif /* WIFI_CONTROLLER_H */
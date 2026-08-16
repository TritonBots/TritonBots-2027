#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFiS3.h>
#include "config.h"

class WiFiController {
   private:

   char* ssid;
   char* password;

   unsigned int localPort;

   char packetBuffer[PACKET_BUFFER_SIZE];

   WiFiUDP udp;

   public:

   WiFiController(char* ssid, char* password, unsigned int localPort);

   ~WiFiController();
   
   unsigned int numBytesAvailable();

   bool sendPacket(char* buffer, unsigned int bufferSize);

   char* parsePacket();

   bool isPacketAvailable();

};



#endif /* WIFI_CONTROLLER_H */
#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFiS3.h>
#include "config.h"

class WiFiController {
   private:

   const char* ssid;
   const char* password;

   unsigned int localPort;

   char packetBuffer[PACKET_BUFFER_SIZE];

   WiFiUDP udp;

   public:

   WiFiController(const char* ssid, const char* password, unsigned int localPort);

   ~WiFiController();

   void begin();
   
   unsigned int numBytesAvailable();

   bool sendPacket(const char* buffer, unsigned int bufferSize);

   char* parsePacket();

   bool isPacketAvailable();

};

#endif /* WIFI_CONTROLLER_H */

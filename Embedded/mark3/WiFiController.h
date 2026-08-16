#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFiS3.h>

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "password"
#define LOCAL_PORT 1234

#define NO_SOCKET_AVAILABLE 0

#define PACKET_BUFFER_SIZE 255
#define HOST_IP "255.255.0.0"
#define HOST_PORT 1000

#define EMPTY_PACKET_BUFFER 0

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
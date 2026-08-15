#include "WiFiController.h"

WiFiController::WiFiController(char* ssid, char* password, unsigned int localPort)
 : ssid(ssid), password(password), localPort(localPort) {
   if (NO_SOCKET_AVAILABLE == udp.begin(localPort)) {
      Serial.println(F("No socket available"));
   }
 }

unsigned int WiFiController::numBytesAvailable() {
   return udp.available();
}

bool WiFiController::sendPacket(char* buffer, unsigned int bufferSize) {
   udp.flush();
   udp.beginPacket(HOST_IP, HOST_PORT);
   udp.write(buffer, bufferSize);
   return udp.endPacket(); // return 1 if success
}

void WiFiController::parsePacket() {
   unsigned int numBytes = udp.parsePacket();
   IPAddress incomingPacketHostAddress = udp.remoteIP();
   udp.read(packetBuffer, PACKET_BUFFER_SIZE);
}

WiFiController::~WiFiController() {
   udp.flush();
   udp.stop();
}
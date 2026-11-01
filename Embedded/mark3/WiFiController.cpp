#include "WiFiController.h"

WiFiController::WiFiController(const char* ssid, const char* password, unsigned int localPort)
 : ssid(ssid), password(password), localPort(localPort) {
   packetBuffer[0] = '\0';
}

void WiFiController::begin() {
   Serial.print(F("Connecting to WiFi: "));
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   unsigned long start = millis();
   // Wait up to 5 seconds for connection without hanging indefinitely
   while (WiFi.status() != WL_CONNECTED && (millis() - start < 5000)) {
      delay(250);
      Serial.print(F("."));
   }
   Serial.println();

   if (WiFi.status() == WL_CONNECTED) {
      Serial.print(F("WiFi connected! IP: "));
      Serial.println(WiFi.localIP());
   } else {
      Serial.println(F("WiFi connection timed out. Proceeding..."));
   }

   if (udp.begin(localPort) == NO_SOCKET_AVAILABLE) {
      Serial.println(F("No socket available for UDP"));
   } else {
      Serial.print(F("UDP listening on port: "));
      Serial.println(localPort);
   }
}

unsigned int WiFiController::numBytesAvailable() {
   return udp.available();
}

bool WiFiController::sendPacket(const char* buffer, unsigned int bufferSize) {
   udp.flush();
   udp.beginPacket(HOST_IP, HOST_PORT);
   udp.write((const uint8_t*)buffer, bufferSize);
   return udp.endPacket(); // return 1 if success
}

char* WiFiController::parsePacket() {
   int packetSize = udp.parsePacket();
   if (packetSize <= 0) {
      return nullptr;
   }

   int bytesToRead = (packetSize < PACKET_BUFFER_SIZE - 1) ? packetSize : (PACKET_BUFFER_SIZE - 1);
   int bytesRead = udp.read(packetBuffer, bytesToRead);
   if (bytesRead > 0) {
      packetBuffer[bytesRead] = '\0';
   } else {
      packetBuffer[0] = '\0';
      return nullptr;
   }

   return packetBuffer;
}

bool WiFiController::isPacketAvailable() {
   return udp.available() > 0;
}

WiFiController::~WiFiController() {
   udp.flush();
   udp.stop();
}

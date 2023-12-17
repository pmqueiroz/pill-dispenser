#include <ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "password";
const char* ip = "192.168.0.177";
#define TIMEOUT 500
#define MAX_BUFFER 300

WiFiServer server(80);
uint8_t buffer[MAX_BUFFER];

void setup() {
   Serial.begin(115200);

   WiFi.disconnect();
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
   }

   IPAddress ipAddress;
   ipAddress.fromString(ip);
   WiFi.config(ipAddress, WiFi.gatewayIP(), WiFi.subnetMask());

   server.begin();
}

void loop() {
   WiFiClient client = server.available();
   if (!client) {
      return;
   }

   uint32_t connectedTime = millis();
   int bytesRead = 0;
   while(client.connected()) {
      uint32_t now = millis();
      uint32_t ellapsed = now - connectedTime;
      if(ellapsed > TIMEOUT && bytesRead == 0) {
         client.stop();
         break;
      }

      int available = client.available();
      if(available) {
         int bufferSize = available < MAX_BUFFER ? available : MAX_BUFFER;
         int readCount = client.read(buffer, bufferSize);
         Serial.write(buffer, readCount);
         Serial.flush();
         bytesRead += readCount;
      }

      available = Serial.available();
      
      if(available) {
         int bufferSize = available < MAX_BUFFER ? available : MAX_BUFFER;
         Serial.readBytes(buffer, bufferSize);
         if(buffer[bufferSize-1] == 127) {
            client.write(buffer, bufferSize-1);
            client.flush();
            delay(100);
            client.stop();
            break;
         }

         client.write(buffer, bufferSize);
      }
   }
}

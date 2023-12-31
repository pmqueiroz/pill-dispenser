#include <ESP8266WiFi.h>

const char* ssid = "Helcio";
const char* password = "hehp3287";
#define TIMEOUT 1500
#define MAX_BUFFER 300

WiFiServer server(80);

int getBufferSize(const int bufferAvailable) {
  int bufferSize = bufferAvailable < MAX_BUFFER ? bufferAvailable : MAX_BUFFER;
  return bufferSize;
}

char* readSerial() {
  char* request = (char*)malloc(MAX_BUFFER);
  int i = 0;

  while (Serial.available() > 0) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    request[i] = c;
    i++;
  }

  request[i] = '\0';
  return request;
}

void setup() {
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
  Serial.print("Server iniciado em: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  uint32_t connectedTime = millis();
  int bytesRead = 0;
  bool serialAnswered = false;
   
  while(client.connected()) {
    uint32_t now = millis();
    uint32_t ellapsed = now - connectedTime;
    if(ellapsed > TIMEOUT && bytesRead == 0) {
      Serial.print("[ERROR] timed out listening to the client");
      client.stop();
      break;
    } else if (ellapsed > TIMEOUT && !serialAnswered) {
      client.print(
        "HTTP/1.0 504 Gateway Timeout\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n");
      client.println("[ERROR] timed out listening to the arduino serial");
      client.stop();
      break;
    }

    int clientAvailable = client.available();
    int clientBufferSize = getBufferSize(clientAvailable);
    uint8_t clientBuffer[clientBufferSize];
    if(clientBufferSize > 0) {
      int readCount = client.read(clientBuffer, clientBufferSize);
      Serial.write(clientBuffer, readCount);
      Serial.flush();
      bytesRead += readCount;
    }

    int serialAvailable = Serial.available();
    if(serialAvailable > 0) {
      char* request = readSerial();
      client.println(request);
      client.flush();
      delay(100);
      client.stop();
      break;
    }
  }
}

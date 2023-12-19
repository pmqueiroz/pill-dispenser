#include "./includes/http-client.h"
#include "./includes/html.h"
#include "./includes/time.h"
#include <Arduino.h>
#define MAX_BUFFER 300

HttpClient::HttpClient(void (*callback)(char *request)): onRequest(callback) {}

void HttpClient::listen() {
  const int serialAvailable = Serial.available();
  const int bufferSize = serialAvailable < MAX_BUFFER ? serialAvailable : MAX_BUFFER;

  if (serialAvailable) {
    char* request = readRequest(bufferSize);

    if(strstr(request, "favicon") == NULL) {
      onRequest(request);

      httpResponse(200);
      Html::write(request);
    } else {
      httpResponse(404);
    }

    Serial.write(127);

    free(request);
  }
}

void HttpClient::httpResponse(int code) {
   switch (code) {
   case 200:
      Serial.print(
      "HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html; charset=UTF-8\r\n"
      "Connection: close\r\n"
      "\r\n");
      break;
   case 404:
      Serial.print(
      "HTTP/1.1 404 Not Found\r\n"
      "Content-Length: 0\r\n"
      "Connection: close\r\n"
      "\r\n");
      break;
   default:
      break;
   }
}

char* HttpClient::readRequest(const int bufferSize) {
  char* request = (char*)malloc(bufferSize + 1);
  int i = 0;

  while (Serial.available() > 0) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();

    if (c == '\n'){ // only the first line is needed
      i++;
      break;
    } else {
      request[i] = c;
      i++;
    }
  }

  request[i] = '\0';
  return request;
}

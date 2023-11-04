#include "./includes/http-client.h"
#include "./includes/html.h"
#include "./includes/time.h"
#include <Arduino.h>

HttpClient::HttpClient(void (*callback)(char *request)): onRequest(callback) {}

void HttpClient::watch() {
  if (Serial.available()) { 
    char* request = readRequest();

    if(strstr(request, "favicon") == NULL) {
      onRequest(request);

      httpResponse(200);
      Html::write();
    } else {
      httpResponse(404);
    }

    Serial.write(127);
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

char* HttpClient::readRequest() {
  bool currentLineIsBlank = true;
  char request[50];
  int i = 0;
  bool firstLine = true;

  while (true){
    while(!Serial.available());
    char c = Serial.read();
    
    if(firstLine){
      request[i] = c;
      i++;
    }
    if (c == '\n'){
        if(currentLineIsBlank){
            break;
        }

        currentLineIsBlank = true;
        firstLine = false;
    }
    else if (c != '\r'){
      currentLineIsBlank = false;
    }
  }

  return request;
}

// void HttpClient::processRequest(char *request) {
//   String action = getStringBetween(request, '?', '=');
//   String value = getStringBetween(request, '=', ' ');

//   if (action == "set-alarm") {
//     Time alarmTime = parseTimeString(action);
//   }
// }

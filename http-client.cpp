#include "./includes/http-client.h"
#include "./includes/helpers.h"
#include <Arduino.h>

HttpClient::HttpClient(int rx_pin, int tx_pin): espRxPin(rx_pin), espTxPin(tx_pin) {}

void HttpClient::watch() {
  if (Serial.available()) { 
    char* request = readRequest();

    if(strstr(request, "favicon") == NULL) {
      processRequest(request);

      sendResponse();
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

void HttpClient::processRequest(char *request) {
   String action = getStringBetween(request, '?', '=');
   String value = getStringBetween(request, '=', ' ');

  // if(action == "on" || action == "off") {

  // }
}

void HttpClient::sendResponse() {
   httpResponse(200);

   Serial.println("<!DOCTYPE HTML>");
   Serial.println("<html>");
   head();
   body();
   Serial.println("</html>");
}

void HttpClient::head() {
  Serial.println(F("<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<style>"
        "* {"
            "box-sizing: border-box;"
            "margin: 0;"
            "padding: 0;"
        "}"
    "</style>"
  "</head>"));
}

void HttpClient::body() {
    Serial.println("<body>");
    // String buttons = "";
    // for(int i=0; i<PINS_COUNT; i++) {
    //     buttons.concat(button(i));
    // }
    // Serial.println(buttons);
    Serial.println("</body>");
}

#ifndef HttpClient_h
#define HttpClient_h

#include <Arduino.h>

class HttpClient {
private:
  int espRxPin;
  int espTxPin;
  void httpResponse(int code);
  char* readRequest();
  void processRequest(char *request);
  void sendResponse();
  void body();
  void head();
public:
  HttpClient(int rx_pin, int tx_pin);
  void watch();
};

#endif

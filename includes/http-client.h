#ifndef HttpClient_h
#define HttpClient_h

#include <Arduino.h>
#include "./time.h"

class HttpClient {
private:
  void (*onRequest)(char *request);
  void httpResponse(int code);
  char* readRequest(const int bufferSize);
public:
  HttpClient(void (*onRequest)(char *request));
  void listen();
};

#endif

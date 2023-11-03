#ifndef EspWifi_h
#define EspWifi_h

#include <Arduino.h>

class EspWifi {
private:
  int espRxPin;
  int espTxPin;
public:
  EspWifi(int rx_pin, int tx_pin);
  void connect(const char* ssid, const char* password, const char* ip);
};

#endif

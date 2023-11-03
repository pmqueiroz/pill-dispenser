#include "./includes/esp-wifi.h"
#include <Arduino.h>

#define TIMEOUT 500
#define MAX_BUFFER 300

EspWifi::EspWifi(int rx_pin, int tx_pin): espRxPin(rx_pin), espTxPin(tx_pin) {
   // WiFiServer server(80);
}

void EspWifi::connect(const char* ssid, const char* password, const char* ip) {

}

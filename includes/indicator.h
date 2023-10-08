#ifndef Indicator_h
#define Indicator_h

#include <Arduino.h>

class Indicator {
private:
  int *ledPins;
  int ledLineCount;
public:
  Indicator(int *pinsIds, int count);
  void turnLineOn(int id);
  void turnLineOff(int id);
};

#endif

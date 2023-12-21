#ifndef RandomIndicator_h
#define RandomIndicator_h

#include <Arduino.h>

class IndicatorLooper {
private:
  int currentLed;
  int ledsAmount;
  int boundaries(int num);
public:
  IndicatorLooper(int indicatorAmount);
  int getIndicator();
};

#endif

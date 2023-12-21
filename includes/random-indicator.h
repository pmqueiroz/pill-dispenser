#ifndef RandomIndicator_h
#define RandomIndicator_h

#include <Arduino.h>

class RandomIndicator {
private:
  int ledsAmount;
  int minimumLed;
  int toMax(int num);
  int toMin(int num);
public:
  RandomIndicator(int indicatorAmount);
  int getRandomIndicator();
};

#endif

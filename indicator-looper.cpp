#include "./includes/indicator-looper.h"
#include <Arduino.h>

IndicatorLooper::IndicatorLooper(int _ledsAmount)
  : currentLed(1), ledsAmount(_ledsAmount) {
}

int IndicatorLooper::getIndicator() {
  int indicatorLed = boundaries(currentLed);
  currentLed = indicatorLed + 1;
  return indicatorLed;
}

int IndicatorLooper::boundaries(int num) {
  if (num > ledsAmount) {
    return 1;
  }

  return num;
}

#include "./includes/random-indicator.h"
#include <Arduino.h>

RandomIndicator::RandomIndicator(int indicatorAmount)
  : minimumLed(1), ledsAmount(indicatorAmount) {
}

int RandomIndicator::getRandomIndicator() {
  int maxLed = toMax(minimumLed);
  int ledNumber = random(minimumLed, toMax(minimumLed));
  minimumLed = toMin(maxLed);
  return ledNumber;
}

int RandomIndicator::toMax(int num) {
  switch (num) {
  case 7:
    return 13;
    break;
  case 13:
    return 19;
    break;
  case 19:
    return 25;
    break;
  default:
    return 7;
    break;
  }
}

int RandomIndicator::toMin(int num) {
  if (num > ledsAmount) {
    return 1;
  }

  return num;
}

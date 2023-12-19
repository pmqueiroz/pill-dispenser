#include "./includes/indicator.h"
#include <Arduino.h>

Indicator::Indicator(int shiftRegLatchPin, int shiftRegDataPin, int shiftRegClockPin, int shiftRegAmount)
  : ledsAmount(shiftRegAmount * 8) {
  shiftRegister = new ShiftOutMega(shiftRegLatchPin, shiftRegDataPin, shiftRegClockPin, shiftRegAmount);
}

void Indicator::turnOn(int id) {
  shiftRegister->shiftWrite(id, HIGH);
}

void Indicator::turnOff(int id = 0) {
  if (id > 0) {
    shiftRegister->shiftWrite(id, LOW);
  } else {
    for (int i = 0; i < ledsAmount; ++i) {
      shiftRegister->shiftWrite(i + 1, LOW);
    }
  }
}

Indicator::~Indicator() {
  delete shiftRegister;
}

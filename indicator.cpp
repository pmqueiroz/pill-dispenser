#include "./includes/indicator.h"
#include <Arduino.h>

Indicator::Indicator(int shiftRegLatchPin, int shiftRegDataPin, int shiftRegClockPin, int shiftRegAmount) {
  shiftRegister = new ShiftOutMega(shiftRegLatchPin, shiftRegDataPin, shiftRegClockPin, shiftRegAmount);
}

void Indicator::turnLineOn(int id) {
  shiftRegister->shiftWrite(id, HIGH);
}

void Indicator::turnLineOff(int id) {
  shiftRegister->shiftWrite(id, LOW);
}

Indicator::~Indicator() {
  delete shiftRegister;
}

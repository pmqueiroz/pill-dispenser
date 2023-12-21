#ifndef Indicator_h
#define Indicator_h

#include <Arduino.h>
#include <ShiftOutMega.h>

class Indicator {
private:
  ShiftOutMega* shiftRegister;
  int ledsAmount;
public:
  Indicator(int shiftRegLatchPin, int shiftRegDataPin, int shiftRegClockPin, int shiftRegAmount);
  ~Indicator();
  void turnOn(int id);
  void turnOff(int id = 0);
};

#endif

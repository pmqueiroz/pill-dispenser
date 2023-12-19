#ifndef Indicator_h
#define Indicator_h

#include <Arduino.h>
#include <ShiftOutMega.h>

#define SHIFT_REG_CLOCK__PIN 5
#define SHIFT_REG_LATCH__PIN 6
#define SHIFT_REG_DATA__PIN 7
#define SHIFT_REG__AMOUNT 3

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

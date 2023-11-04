#ifndef Alarm_h
#define Alarm_h

#include <Arduino.h>

struct Time {
  int hour;
  int minute;
  int daysOfWeek[7];

  Time() {
    for (int i = 0; i < 7; ++i) {
      daysOfWeek[i] = 0;
    }
  }
};

Time parseTimeString(String input);

#endif

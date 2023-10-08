#ifndef Alarm_h
#define Alarm_h

#include <Arduino.h>

class Alarm {
private:
  bool isAlarmActive;
  int buzzerPin;

  void playAlarm();
  void turnOffAlarm();

public:
  Alarm(int pin);
  void activateAlarm();
  void deactivateAlarm();
  bool isAlarmActivated() const;
  void powerOffAlarm();
};

#endif

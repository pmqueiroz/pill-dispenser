#include "./includes/alarm.h"
#include <Arduino.h>

Alarm::Alarm(int pin) : isAlarmActive(false), buzzerPin(pin) {
  pinMode(buzzerPin, OUTPUT);
}

void Alarm::playAlarm() {
  tone(buzzerPin, 500);
}

void Alarm::turnOffAlarm() {
  noTone(buzzerPin);
}

void Alarm::activateAlarm() {
  isAlarmActive = true;
  playAlarm();
}

void Alarm::deactivateAlarm() {
  isAlarmActive = false;
  turnOffAlarm();
}

bool Alarm::isAlarmActivated() const {
  return isAlarmActive;
}

void Alarm::powerOffAlarm() {
  noTone(buzzerPin);
}

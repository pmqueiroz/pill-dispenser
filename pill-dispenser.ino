#include "alarm.h"
#include "cover.h"
#include "indicator.h"

#define BUZZER__PIN 2
#define COVER_BUTTON__PIN 3
#define DEBUG_LED__PIN 4
#define LED_LINE__COUNT 4
int INDICATOR_LEDS__MAP[LED_LINE__COUNT] = {A1, A2, A3, A4};

Alarm alarm(BUZZER__PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(INDICATOR_LEDS__MAP, LED_LINE__COUNT);

void setup() {
  Serial.begin(9600);
  alarm.activateAlarm();
  cover.onCoverOpen([]() { alarm.deactivateAlarm(); });
  cover.onCoverClosed([]() {
     // digitalWrite(DEBUG_LED__PIN, LOW);
     alarm.activateAlarm();
   });
}

void loop() {
  if(alarm.isAlarmActivated()) {
    digitalWrite(DEBUG_LED__PIN, HIGH);
  } else {
    digitalWrite(DEBUG_LED__PIN, LOW);
  }

  cover.checkState();
}

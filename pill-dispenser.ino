#include "./includes/alarm.h"
#include "./includes/cover.h"
#include "./includes/indicator.h"
#include "virtuabotixRTC.h"

#define BUZZER__PIN 2
#define COVER_BUTTON__PIN 3
#define DEBUG_LED__PIN 4
#define LED_LINE__COUNT 4
#define RTC_CLK__PIN 10
#define RTC_DAT__PIN 11
#define RTC_RST__PIN 12
#define ESP_RX__PIN 5
#define ESP_TX__PIN 6
int INDICATOR_LEDS__MAP[LED_LINE__COUNT] = {A1, A2, A3, A4};

Alarm alarm(BUZZER__PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(INDICATOR_LEDS__MAP, LED_LINE__COUNT);
virtuabotixRTC rtc_controller(RTC_CLK__PIN, RTC_DAT__PIN, RTC_RST__PIN);

void setup() {
  Serial.begin(9600);
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // rtc_controller.setDS1302Time(00, 39, 17, 6, 3, 11, 2023);

  alarm.activateAlarm();
  cover.onCoverOpen([]() { 
    indicator.turnLineOff(3);
    alarm.deactivateAlarm();
  });
  cover.onCoverClosed([]() {
    indicator.turnLineOn(3);
    alarm.activateAlarm();
  });
  Serial.println("passando pelo setup");
}

void loop() {
  rtc_controller.updateTime();

  if (rtc_controller.seconds % 2 == 0)
    digitalWrite(DEBUG_LED__PIN, HIGH);
  else
    digitalWrite(DEBUG_LED__PIN, LOW);

  cover.checkState();
}

#include "./includes/alarm.h"
#include "./includes/cover.h"
#include "./includes/indicator.h"
#include "./includes/indicator-looper.h"
#include "./includes/helpers.h"
#include "virtuabotixRTC.h"

#define BUZZER__PIN 2
#define COVER_BUTTON__PIN 9
#define RTC_CLK__PIN 10
#define RTC_DAT__PIN 11
#define RTC_RST__PIN 12
#define SHIFT_REG_LATCH__PIN 6
#define SHIFT_REG_DATA__PIN 7
#define SHIFT_REG_CLOCK__PIN 5
#define SHIFT_REG__AMOUNT 3
#define THIRTY_SECONDS 30 * 1000

Alarm alarm(BUZZER__PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(SHIFT_REG_LATCH__PIN, SHIFT_REG_DATA__PIN, SHIFT_REG_CLOCK__PIN, SHIFT_REG__AMOUNT);
IndicatorLooper indicatorLooper(6);
virtuabotixRTC rtc_controller(RTC_CLK__PIN, RTC_DAT__PIN, RTC_RST__PIN);

void startupFeedback() {
  alarm.activateAlarm();
  timeout([]() { alarm.deactivateAlarm(); }, 200);
  timeout([]() { alarm.activateAlarm(); }, 300);
  timeout([]() { alarm.deactivateAlarm(); }, 200);
}

void setup() {
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // rtc_controller.setDS1302Time(00, 39, 17, 6, 3, 11, 2023);

  cover.onCoverOpen([]() {
    alarm.deactivateAlarm();
  });

  cover.onCoverClose([]() {
    indicator.turnOff();
  });

  startupFeedback();
}

void loop() {
  static unsigned long initializedTime = millis();
  long now = millis();
  long ellapsed = now - initializedTime;

  if (ellapsed > THIRTY_SECONDS) {
    int ledToTurnOn = indicatorLooper.getIndicator();

    if (!cover.isCoverOpened()) {
      alarm.activateAlarm();
    }

    indicator.turnOn(ledToTurnOn);
    initializedTime = now;
  }

  rtc_controller.updateTime();
  cover.checkState();
}

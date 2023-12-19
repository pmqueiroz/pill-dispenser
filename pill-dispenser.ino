#include "./includes/alarm.h"
#include "./includes/cover.h"
#include "./includes/indicator.h"
#include "./includes/http-client.h"
#include "./includes/helpers.h"
#include "./includes/time.h"
#include "virtuabotixRTC.h"

#define BUZZER__PIN 2
#define COVER_BUTTON__PIN 3
#define DEBUG_LED__PIN 4
#define LED_LINE__COUNT 4
#define RTC_CLK__PIN 10
#define RTC_DAT__PIN 11
#define RTC_RST__PIN 12
#define SHIFT_REG_LATCH__PIN 6
#define SHIFT_REG_DATA__PIN 7
#define SHIFT_REG_CLOCK__PIN 5
#define SHIFT_REG__AMOUNT 1

Alarm alarm(BUZZER__PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(SHIFT_REG_LATCH__PIN, SHIFT_REG_DATA__PIN, SHIFT_REG_CLOCK__PIN, SHIFT_REG__AMOUNT);
HttpClient httpClient([](char *request) {
  // String action = getStringBetween(request, '?', '=');
  // String value = getStringBetween(request, '=', ' ');


  // if (action == "set-alarm") {
    // Time alarmTime = parseTimeString(action);
  // }
});
virtuabotixRTC rtc_controller(RTC_CLK__PIN, RTC_DAT__PIN, RTC_RST__PIN);

void setup() {
  Serial.begin(115200);
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // rtc_controller.setDS1302Time(00, 39, 17, 6, 3, 11, 2023);

  cover.onCoverOpen([]() { 
    indicator.turnLineOff(3);
    alarm.deactivateAlarm();
  });
  cover.onCoverClosed([]() {
    indicator.turnLineOn(3);
    alarm.activateAlarm();
  });
}

void loop() {
  rtc_controller.updateTime();
  httpClient.listen();
  cover.checkState();
}

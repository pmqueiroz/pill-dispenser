#include "./includes/alarm.h"
#include "./includes/cover.h"
#include "./includes/indicator.h"
#include "./includes/random-indicator.h"
#include "./includes/helpers.h"
#include "./includes/time.h"
#include "virtuabotixRTC.h"

#define BUZZER__PIN 2
#define COVER_BUTTON__PIN 9
#define LED_LINE__COUNT 4
#define RTC_CLK__PIN 10
#define RTC_DAT__PIN 11
#define RTC_RST__PIN 12
#define SHIFT_REG_LATCH__PIN 6
#define SHIFT_REG_DATA__PIN 7
#define SHIFT_REG_CLOCK__PIN 5
#define SHIFT_REG__AMOUNT 3
#define THIRTY_SECONDS 30 * 1000
int number;

Alarm alarm(BUZZER__PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(SHIFT_REG_LATCH__PIN, SHIFT_REG_DATA__PIN, SHIFT_REG_CLOCK__PIN, SHIFT_REG__AMOUNT);
RandomIndicator randomIndicator(SHIFT_REG__AMOUNT * 8);
virtuabotixRTC rtc_controller(RTC_CLK__PIN, RTC_DAT__PIN, RTC_RST__PIN);

void setup() {
  Serial.begin(115200);
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // rtc_controller.setDS1302Time(00, 39, 17, 6, 3, 11, 2023);

  cover.onCoverOpen([]() {
    alarm.deactivateAlarm();
  });

  cover.onCoverClose([]() {
    indicator.turnOff();
  });
}

int lastMinimumLed = 1;
void loop() {
  static unsigned long initializedTime = millis();
  long now = millis();
  long ellapsed = now - initializedTime;

  if (ellapsed > THIRTY_SECONDS) {
    int ledToTurnOn = randomIndicator.getRandomIndicator();

    if (!cover.isCoverOpened()) {
      alarm.activateAlarm();
    }

    Serial.print("Turning the led ");
    Serial.print(ledToTurnOn);
    Serial.println(" on");

    indicator.turnOn(ledToTurnOn);
    initializedTime = now;
  }

  rtc_controller.updateTime();
  cover.checkState();
}

#include "indicator.h"
#include <Arduino.h>

Indicator::Indicator(int *pinsIds, int count) : ledPins(pinsIds), ledLineCount(count) {
    for (int i = 0; i < ledLineCount; i++) {
        pinMode(ledPins[i], OUTPUT);
        analogWrite(ledPins[i], 0);
    }
}

void Indicator::turnLineOn(int id) {
    analogWrite(ledPins[id], 255);
}

void Indicator::turnLineOff(int id) {
    analogWrite(ledPins[id], 0);
}
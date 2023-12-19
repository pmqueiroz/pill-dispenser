#include "./includes/cover.h"
#include <Arduino.h>

Cover::Cover(int pin) : buttonPin(pin), coverState(LOW), lastCoverState(LOW) {
  pinMode(buttonPin, INPUT);
}

void Cover::checkState() {
    coverState = digitalRead(buttonPin);

    if(coverState != lastCoverState) {
        if (coverState == HIGH) {
            coverOpenCallback();
        } else {
            coverClosedCallback();
        }
    }

    lastCoverState = coverState;
}

void Cover::onCoverOpen(void (*callback)(void)) {
    coverOpenCallback = callback;
}

bool Cover::isCoverOpened() {
    return coverState == HIGH;
}

void Cover::onCoverClose(void (*callback)(void)) {
    coverClosedCallback = callback;
}

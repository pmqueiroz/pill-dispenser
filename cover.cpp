#include "./includes/cover.h"
#include <Arduino.h>

Cover::Cover(int pin) : buttonPin(pin), buttonState(LOW), lastButtonState(LOW) {
  pinMode(buttonPin, INPUT);
}

void Cover::checkState() {
    buttonState = digitalRead(buttonPin);

    if(buttonState != lastButtonState) {
        if (buttonState == HIGH) {
            coverOpenCallback();
        } else {
            coverClosedCallback();
        }
    }

    lastButtonState = buttonState;
}

void Cover::onCoverOpen(void (*callback)(void)) {
    coverOpenCallback = callback;
}
void Cover::onCoverClosed(void (*callback)(void)) {
    coverClosedCallback = callback;
}
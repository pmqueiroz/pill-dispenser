#define COVER_BUTTON__PIN 3
#define BUZZER_PIN 2
#define LED_PIN 8
#define LED_LINES 4
int ledPinsIds[LED_LINES] = {A1, A2, A3, A4};

class Cover {
private:
  const int buttonPin;
  int buttonState;
  int lastButtonState;
  void (*coverOpenCallback)(void);
  void (*coverClosedCallback)(void);
public:
  Cover(int pin) : buttonPin(pin), buttonState(LOW), lastButtonState(LOW) {
    pinMode(buttonPin, INPUT);
  }

  void checkState() {
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
  
  void onCoverOpen(void (*callback)(void)) {
    coverOpenCallback = callback;
  }
  void onCoverClosed(void (*callback)(void)) {
    coverClosedCallback = callback;
  }
};
  
class Alarm {
private:
  bool isAlarmActive;
  int buzzerPin;
    	
  void playAlarm() {
    tone(buzzerPin, 500);
  }
  
  void turnOffAlarm() {
    noTone(buzzerPin);
  }
public:
  Alarm(int pin) : isAlarmActive(false), buzzerPin(pin) {
    pinMode(buzzerPin, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
  }

  void activateAlarm() {
    isAlarmActive = true;
    playAlarm();
  }

  void deactivateAlarm() {
    isAlarmActive = false;
    turnOffAlarm();
  }

  bool isAlarmActivated() const {
    return isAlarmActive;
  }

  void powerOffAlarm() {
    noTone(buzzerPin);
  };
};

class Indicator {
private:
  int *ledPins;
public:
  Indicator(int *pinsIds) : ledPins(pinsIds) {
    for (int i = 0; i < LED_LINES; i++) {
      pinMode(ledPins[i], OUTPUT);
      analogWrite(ledPins[i], 0);
    }
  }
  
  void turnLineOn(int id) {
    analogWrite(ledPins[id], 255);
  }

  void turnLineOff(int id) {
    analogWrite(ledPins[id], 0);
  }
};

Alarm alarm(BUZZER_PIN);
Cover cover(COVER_BUTTON__PIN);
Indicator indicator(ledPinsIds);

void setup() {
  Serial.begin(9600);
  alarm.activateAlarm();
  cover.onCoverOpen([]() { alarm.deactivateAlarm(); });
  cover.onCoverClosed([]() {
     // digitalWrite(LED_PIN, LOW);
     alarm.activateAlarm();
   });
}

void loop() {
  if(alarm.isAlarmActivated()) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  cover.checkState();
}

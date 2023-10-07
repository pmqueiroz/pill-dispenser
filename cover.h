#ifndef Cover_h
#define Cover_h

#include <Arduino.h>

class Cover {
private:
  const int buttonPin;
  int buttonState;
  int lastButtonState;
  void (*coverOpenCallback)(void);
  void (*coverClosedCallback)(void);
public:
  Cover(int pin);
  void checkState();
  void onCoverOpen(void (*callback)(void));
  void onCoverClosed(void (*callback)(void));
};

#endif


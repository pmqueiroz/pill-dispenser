#ifndef Cover_h
#define Cover_h

#include <Arduino.h>

class Cover {
private:
  const int buttonPin;
  int coverState;
  int lastCoverState;
  void (*coverOpenCallback)(void);
  void (*coverClosedCallback)(void);
public:
  Cover(int pin);
  void checkState();
  bool isCoverOpened();
  void onCoverOpen(void (*callback)(void));
  void onCoverClose(void (*callback)(void));
};

#endif

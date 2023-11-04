#ifndef Html_h
#define Html_h

#include <Arduino.h>

class Html {
private:
   static void head();
   static void body();
public:
   static void write();
};

#endif

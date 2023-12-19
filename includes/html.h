#ifndef Html_h
#define Html_h

#include <Arduino.h>

class Html {
private:
   static void head();
   static void body(char* debug_string);
public:
   static void write(char* debug_string);
};

#endif

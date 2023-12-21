#ifndef Helpers_h
#define Helpers_h

String getStringBetween(char* input, char start, char end) {
  String str = "";
  char* c = strchr(input, start);

  if(c == NULL) {
    return "";
  }

  c++;

  while(*c != end && *c!='\0') {
    str += *c;
    c++;
  }

  return str;
}

void timeout(void (*func)(), int timeout) {
  delay(timeout);
  func();
}

#endif

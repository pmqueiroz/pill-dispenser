#include "./includes/html.h"
#include <Arduino.h>

void Html::head() {
  Serial.println(F("<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<style>"
        "* {"
          "box-sizing: border-box;"
          "margin: 0;"
          "padding: 0;"
        "}"
        ".debug {"
          "border: 1px solid red;"
        "}"
    "</style>"
  "</head>"));
}

void Html::body(char* debug_string) {
    Serial.println("<body>");
    Serial.println("<p>some body</p>");
    // String buttons = "";
    // for(int i=0; i<PINS_COUNT; i++) {
    //     buttons.concat(button(i));
    // }
    // Serial.println(buttons);
    Serial.println("<p class=\"debug\">");
    Serial.println(debug_string);
    Serial.println("</p>");
    Serial.println("</body>");
}

void Html::write(char* debug_string) {
   Serial.println("<!DOCTYPE HTML>");
   Serial.println("<html>");
   head();
   body(debug_string);
   Serial.println("</html>");
}

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
    "</style>"
  "</head>"));
}

void Html::body() {
    Serial.println("<body>");
    Serial.println("<p>some body</p>");
    // String buttons = "";
    // for(int i=0; i<PINS_COUNT; i++) {
    //     buttons.concat(button(i));
    // }
    // Serial.println(buttons);
    Serial.println("</body>");
}

void Html::write() {
   Serial.println("<!DOCTYPE HTML>");
   Serial.println("<html>");
   head();
   body();
   Serial.println("</html>");
}

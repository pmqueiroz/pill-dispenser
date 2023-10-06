void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{
  static unsigned long previousMillis = 0;
  static int toneValue = 200;
  static int toneDuration = 200;
  
  unsigned long currentMillis = millis();
  
  tone(2, toneValue);
  if (currentMillis - previousMillis >= toneDuration) {
    previousMillis = currentMillis;
    
   

    toneValue += 200;
    if (toneValue > 1000) {
      toneValue = 200;
      noTone(2);
      delay(1000); // Wait for 1000 milliseconds
    }
  }
}

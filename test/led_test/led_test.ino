#include <LedControl.h>

LedControl eyes = LedControl(12, 11, 10, 2);

void setup() {
  Serial.begin(9600);
  eyes.shutdown(0, false);
  eyes.shutdown(1, false);
  eyes.setIntensity(0, 15);
  eyes.setIntensity(1, 15);
  eyes.clearDisplay(0);
  eyes.clearDisplay(1);
}

void loop() {
  eyes.clearDisplay(0);
  eyes.clearDisplay(1);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      eyes.setLed(0, i, j, true);
      eyes.setLed(1, 7-i, 7-j, true);
      delay(50);
    }
  }
}

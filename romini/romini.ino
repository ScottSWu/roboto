#include <Servo.h>

Servo s;

void setup() {
  Serial.begin(9600);
  s.attach(2);
  s.write(90);
}

#define PAUSE() delay(500);
void loop() {
  s.write(45);
  PAUSE();
  s.write(90);
  PAUSE();
  s.write(45);
  PAUSE();
  s.write(90);
  PAUSE();
  s.write(135);
  PAUSE();
  s.write(90);
  PAUSE();
  s.write(135);
  PAUSE();
  s.write(90);
  PAUSE();
}

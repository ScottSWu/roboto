#include <Servo.h>

Servo pan, tilt, neck, ears, tail;

void setup() {
  Serial.begin(115200);

  pan.attach(2);
  tilt.attach(3);
  neck.attach(4);
  ears.attach(5);
  tail.attach(6);

  pan.write(90);
  tilt.write(90);
  neck.write(90);
  ears.write(90);
  tail.write(90);
}

#define TEST_SERVO(s, min_angle, max_angle) \
    s.write(min_angle); \
    delay(500); \
    s.write(90); \
    delay(500); \
    s.write(max_angle); \
    delay(500); \
    s.write(90); \
    delay(1000);

void loop() {
  // Test panning
  TEST_SERVO(pan, 80, 100);

  // Test tilting
  TEST_SERVO(tilt, 75, 105);

  // Test neck
  TEST_SERVO(neck, 45, 135);

  // Test ears
  // TODO

  // Test tail
  // TODO

  // Restore original positions
  pan.write(90);
  tilt.write(90);
  neck.write(90);
  ears.write(90);
  tail.write(90);
  delay(5000);
}

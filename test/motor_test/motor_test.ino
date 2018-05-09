#include <Servo.h>

Servo s;

int mode = 0; // Standard servo mode
void setup() {
  Serial.begin(9600);
  s.attach(2);
  pinMode(A0, INPUT_PULLUP);
  delay(1000);
  if (analogRead(A0) > 1000) {
    // Open pullup, feedback not connected, standard servo
    Serial.println("Standard servo mode");
    mode = 0;
  }
  else {
    // Feedback is connected, 360 degree servo
    Serial.println("360 servo mode");
    //mode = 1;
    mode = 3;
  }
}

void move_to_90(int speed) {
  s.write(speed);
  int pos = pulseIn(A0, HIGH, 2000); // Timeout after 2ms (>910Hz)
  int new_pos = pos;
  // Halfway duty cycle microseconds
  while (!(pos < 1099 / 2 && new_pos > 1099 / 2 || pos > 1099 / 2 &&  new_pos < 1099 / 2)) {
    pos = new_pos;
    new_pos = pulseIn(A0, HIGH, 2000);
  }
}

int samples;
void loop() {
  if (mode == 0) {
    Serial.print("Servo at: ");
    Serial.println(45);
    s.write(45);
    delay(2000);
    Serial.print("Servo at: ");
    Serial.println(90);
    s.write(90);
    delay(2000);
    Serial.print("Servo at: ");
    Serial.println(135);
    s.write(135);
    delay(2000);
  }
  else if (mode == 1) {
    // Move roughly to 90
    move_to_90(120);

    // Figure out where 0 is
    int rest = 90;
    int pos = pulseIn(A0, HIGH, 2000);
    int new_pos = pos;
    while (true) {
      Serial.println("Trying speed: ");
      Serial.println(rest);
      pos = pulseIn(A0, HIGH, 2000);
      s.write(rest);
      delay(500);
      new_pos = pulseIn(A0, HIGH, 2000);
      Serial.println(pos);
      Serial.println(new_pos);
      if (new_pos > pos) { // Moving clockwise
        rest++;
        move_to_90(rest + 10);
      }
      else if (new_pos < pos) { // Moving counterclockwise
        rest--;
        move_to_90(rest - 10);
      }
      else { // Success
        break;
      }
    }

    Serial.println(rest);
    move_to_90(rest + 5);
    mode = 2;
  }
  else if (mode == 2) {
    pulseIn(A0, HIGH, 2000);
  }
  else if (mode == 3) {
    int pos = pulseIn(A0, HIGH, 2000);
    if (pos < 30) {
      return;
    }
    Serial.println(pos);
    int delta = pos - 1099 / 2;
    if (delta == 0) {
      s.write(90);
    }
    else {
      s.write(90 + constrain(delta / 2, -45, 45));
    }
  }
}

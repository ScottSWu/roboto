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
  setEyes(0); // Normal
  delay(1000);
  setEyes(1); // Normal blink
  delay(1000);
  setEyes(10); // Happy
  delay(1000);
  setEyes(11); // Happy blink
  delay(1000);
  setEyes(20); // Unamused
  delay(1000);
  setEyes(21); // Unamused blink
  delay(1000);
  setEyes(30); // Angry
  delay(1000);
  setEyes(40); // Sad
  delay(1000);
}

// Matrix eyes
byte normal[2][8] = {
  { B00111100, B01111110, B11111111, B11111111, B11111111, B11111111, B01111110, B00111100 },
  { B00111100, B01111110, B11111111, B11111111, B11111111, B11111111, B01111110, B00111100 }
};
byte normal_blink[2][8] = {
  { B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000 },
  { B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000 }
};

byte happy[2][8] = {
  { B00111100, B00011110, B00001111, B00001111, B00001111, B00001111, B00011110, B00111100 },
  { B00111100, B00011110, B00001111, B00001111, B00001111, B00001111, B00011110, B00111100 }
};
byte happy_blink[2][8] = {
  { B00100000, B00010000, B00001000, B00001000, B00001000, B00001000, B00010000, B00100000 },
  { B00100000, B00010000, B00001000, B00001000, B00001000, B00001000, B00010000, B00100000 }
};

byte unamused[2][8] = {
  { B00111000, B01111000, B11111000, B11111000, B11111000, B11111000, B01111000, B00111000 },
  { B00111000, B01111000, B11111000, B11111000, B11111000, B11111000, B01111000, B00111000 }
};
byte unamused_blink[2][8] = {
  { B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000 },
  { B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000 }
};

byte angry[2][8] = {
  { B01000000, B01100000, B11110000, B11111000, B11111100, B11111110, B01111101, B00111000 },
  { B00111000, B01111101, B11111110, B11111100, B11111000, B11110000, B01100000, B01000000 }
};

byte sad[2][8] = {
  { B00111000, B01111101, B11111110, B11111100, B11111000, B11110000, B01100000, B01000000 },
  { B01000000, B01100000, B11110000, B11111000, B11111100, B11111110, B01111101, B00111000 }
};

byte sleepy[2][8] = {
  { B00011000, B00011000, B00011001, B00011001, B00011001, B00011001, B00011000, B00011000 },
  { B00011000, B00011000, B00011001, B00011001, B00011001, B00011001, B00011000, B00011000 }
};

#define SHOW_EYES(mat) \
    for (int r = 0; r < 8; r++) { \
      eyes.setRow(0, r, mat[0][r]); \
      eyes.setRow(1, r, mat[1][r]); \
    } \
    break;

void setEyes(int t) {
  switch (t) {
    case 0: // Normal
      SHOW_EYES(normal);
    case 1: // Normal blink
      SHOW_EYES(normal_blink);
    case 10: // Happy
      SHOW_EYES(happy);
    case 11: // Happy blink
      SHOW_EYES(happy_blink);
    case 20: // Unamused
      SHOW_EYES(unamused);
    case 21: // Unamused blink
      SHOW_EYES(unamused_blink);
    case 30: // Angry
      SHOW_EYES(angry);
    case 40: // Sad
      SHOW_EYES(sad);
    case 50: // Sleepy
      SHOW_EYES(sleepy);
    default:
      break;
  }
}

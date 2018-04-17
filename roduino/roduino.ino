#include <Servo.h>
#include <LEDContro.h>

Servo pan, tilt, neck, ears, tail;
LedControl eyes = LedControl(11, 13, 10, 2);

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

  eyes.shutdown(addrL,false);
  eyes.shutdown(addrR,false);

  eyes.setIntensity(addrL,15);
  eyes.setIntensity(addrR,15);

  eyes.clearDisplay(addrL);
  eyes.clearDisplay(addrR);
}

char buffer[5];
int buffer_index = 0;
void loop() {
  if (Serial.available() > 0) {
    byte b = Serial.read();
    buffer[buffer_index] = b;
    buffer_index++;
    if (b == '\n') {
      char t = buffer[0];
      int v = (buffer[1] - '0') * 100 + (buffer[2] - '0') * 10 + (buffer[3] - '0');
      switch (t) {
        case 'p': // Pan
          if (45 <= v && v <= 135) {
            pan.write(v);
          }
          break;
        case 't': // Tilt
          if (75 <= v && v <= 105) {
            tilt.write(v);
          }
          break;
        case 'n': // Neck
          if (45 <= v && v <= 135) {
            neck.write(v);
          }
          break;
        case 'e': // Eyes
          setEyes(v);
          break;
      }
    }
    else if (buffer_index > 4) {
      buffer_index = 0;
    }
  }
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
  { B00111000, B01111101, B11111110, B11111100, B11111000, B11110000, B01100000, B01000000 },
  { B01000000, B01100000, B11110000, B11111000, B11111100, B11111110, B01111101, B00111000 }
};

byte sad[2][8] = {
  { B01000000, B01100000, B11110000, B11111000, B11111100, B11111110, B01111101, B00111000 },
  { B00111000, B01111101, B11111110, B11111100, B11111000, B11110000, B01100000, B01000000 }
};

byte sleepy[2][8] = {
  { B00111100, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000 },
  { B00111100, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000 }
};

#define SHOW_EYES(mat) \
    for (int i = 0; i < 8; i++) { \
      lc.setRow(0, i, mat[0][i]); \
      lc.setRow(1, i, mat[1][i]); \
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

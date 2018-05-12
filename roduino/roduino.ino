#include <Servo.h>
#include <LedControl.h>

Servo pan, tilt, neck, tail, earL, earR;
LedControl eyes = LedControl(12, 11, 10, 2);

#define SERIALIO Serial

byte flip[256];
void setup() {
  SERIALIO.begin(115200);

  // Generate flipped bytes
  for (int i = 0; i < 256; i++) {
    flip[i] = ((i & 1) << 7) | ((i & 2) << 5) | ((i & 4) << 3) | ((i & 8) << 1) |
              ((i & 16) >> 1) | ((i & 32) >> 3) | ((i & 64) >> 5) | ((i & 128) >> 7);
  }

  pinMode(A0, INPUT);
  
  pan.attach(2);
  tilt.attach(3);
  neck.attach(4);
  tail.attach(5);
  earL.attach(7);
  earR.attach(6);

  pan.write(90);
  tilt.write(90);
  neck.write(90);
  tail.write(90);
  earL.write(90);
  earR.write(90);

  eyes.shutdown(0, false);
  eyes.shutdown(1, false);

  eyes.setIntensity(0, 1);
  eyes.setIntensity(1, 1);

  eyes.clearDisplay(0);
  eyes.clearDisplay(1);

  setEyes(0);
}

#define PAN_CENTER 235

char buffer[5];
int buffer_index = 0;
int pan_target = PAN_CENTER;
long avg_feedback = ((long) pan_target * 1100) / 360;
void loop() {
  if (SERIALIO.available() > 0) {
    byte b = SERIALIO.read();
    buffer[buffer_index] = b;
    buffer_index++;
    if (buffer_index == 5 && b == '\n') {
      char t = buffer[0];
      int v = (buffer[1] - '0') * 100 + (buffer[2] - '0') * 10 + (buffer[3] - '0');
      switch (t) {
        case ' ': // Ping
          SERIALIO.println("Roboto!");
          break;
        case 'p': // Pan
          if (PAN_CENTER - 30 <= v && v <= PAN_CENTER + 30) {
            pan_target = v;
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
        case 'a': // Tail
          if (75 <= v && v <= 105) {
            tail.write(v);
          }
          break;
        case 'l': // Left Ear
          if (75 <= v <= 105) {
            earL.write(v);
          }
          break;
        case 'r': // Right Ear
          if (75 <= v <= 105) {
            earR.write(v);
          }
          break;
        case 'e': // Eyes
          setEyes(v);
          break;
      }
      buffer_index = 0;
    }
    else if (b == '\n' || buffer_index == 5) {
      buffer_index = 0;
    }
  }
  long feedback = pulseIn(A0, HIGH, 2000);
  if (feedback > 30) {
    avg_feedback = (avg_feedback + feedback) / 2;
    long delta = avg_feedback - ((long) pan_target * 1100) / 360;
    /*
    SERIALIO.print(avg_feedback);
    SERIALIO.print(" ");
    SERIALIO.print(feedback);
    SERIALIO.print(" ");
    SERIALIO.print(pan_target);
    SERIALIO.print(" ");
    SERIALIO.print(delta);
    SERIALIO.print("\n");
    */
    if (delta == 0) {
      pan.write(90);
    }
    else {
      pan.write(90 + constrain(delta, -15, 15));
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
    for (int i = 0; i < 8; i++) { \
      eyes.setColumn(0, i, flip[mat[1][i]]); \
      eyes.setColumn(1, i, flip[mat[0][i]]); \
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



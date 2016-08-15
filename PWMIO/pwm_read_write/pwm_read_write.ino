#include <Servo.h>

//read line from Serial
int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case 48: // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len - 1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  return -1;
}
#define ELEV_INPUTPIN 3
#define RUDD_INPUTPIN 5
#define AUX2_INPUTPIN 11
Servo elevOutputServo, ruddOutputServo;
void setup() {
  pinMode(ELEV_INPUTPIN, INPUT);
  pinMode(RUDD_INPUTPIN, INPUT);
  pinMode(AUX2_INPUTPIN, INPUT);
  elevOutputServo.attach(6);
  ruddOutputServo.attach(9);
  Serial.begin(9600);
}
int count = 0;
bool readFromRC = true;
void loop() {
  int elevInputPWM = pulseIn(ELEV_INPUTPIN, HIGH);
  int ruddInputPWM = pulseIn(RUDD_INPUTPIN, HIGH);
  int aux2InputPWM = pulseIn(AUX2_INPUTPIN, HIGH);
  if (readFromRC) {
    if (elevInputPWM > 1500 || elevInputPWM < 1460) {
      elevOutputServo.writeMicroseconds(elevInputPWM);
    } else {
      elevOutputServo.writeMicroseconds(1500);
    }
    if (ruddInputPWM > 1500 || ruddInputPWM < 1460) {
      ruddOutputServo.writeMicroseconds(ruddInputPWM);
    } else {
      ruddOutputServo.writeMicroseconds(1500);
    }
    Serial.print("elevInputPWM : ");
    Serial.print(elevInputPWM);
    //Serial.print("   \n");
    Serial.print("  ruddInputPWM : ");
    Serial.print(ruddInputPWM);
    //Serial.print("   \n");
    Serial.print("  aux2InputPWM : ");
    Serial.print(aux2InputPWM);
    Serial.print("   \n");
  }

  if (aux2InputPWM > 1500 && count == 0) {
//    elevOutputServo.writeMicroseconds(1400);
//    delay(400);
//    elevOutputServo.writeMicroseconds(1600);
//    delay(400);
    ruddOutputServo.writeMicroseconds(1400);
    delay(2000);
    ruddOutputServo.writeMicroseconds(1600);
    delay(2000);
    readFromRC = false;
    count = 1;
  } else {
    readFromRC = true;
  }

  if (aux2InputPWM > 1800) {
    count = 0;
  }

  static char buffer[80];
  int len = 0;
  if ((len = readline(Serial.read(), buffer, 80)) > 0) {
    if (strncmp(buffer, "l", len) == 0) {
      elevOutputServo.writeMicroseconds(1200);
      readFromRC = false;
      Serial.println("l");
    } else if (strncmp(buffer, "r", len) == 0) {
      elevOutputServo.writeMicroseconds(1700);
      readFromRC = false;
      Serial.println("r");
    } else if (strncmp(buffer, "b", len) == 0) {
      ruddOutputServo.writeMicroseconds(1200);
      readFromRC = false;
      Serial.println("b");
    } else if (strncmp(buffer, "f", len) == 0) {
      ruddOutputServo.writeMicroseconds(1700);
      readFromRC = false;
      Serial.println("f");
    } else if (strncmp(buffer, "s", len) == 0) {
      readFromRC = true;
      Serial.println("s");
    }
  }
  //delay(200);
}

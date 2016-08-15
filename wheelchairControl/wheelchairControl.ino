int fbPort = 6;
int fbPort2 = 7;
int rlPort = 2;
int rlPort2 = 3;
bool forwardBackFlag = false;
bool forwardBackFlag2 = true;
bool rightLeftFlag = false;
bool rightLeftFlag2 = true;
String forwardCommand = "f";
String backCommand = "b";
String leftCommand = "l";
String rightCommand = "r";
String stopCommand = "s";

//read command from Serial
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
  // No end of line has been found, so return -1.
  return -1;
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1
  };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{
  Serial.begin(9600);
  pinMode(rlPort, OUTPUT);
  pinMode(rlPort2, OUTPUT);
  pinMode(fbPort, OUTPUT);
  pinMode(fbPort2, OUTPUT);
  Serial.println("arduino start");
}

int ctl = 0;
void loop()
{
  static char buffer[80];
  int len = 0;

  if ((len = readline(Serial.read(), buffer, 80)) > 0) {
    if (strncmp(buffer, leftCommand.c_str(), leftCommand.length()) == 0) {
      Serial.println(leftCommand.length());
      rightLeftFlag = true;
      rightLeftFlag2 = true;
      Serial.println("l");
    } else if (strncmp(buffer, rightCommand.c_str(), len) == 0) {
      rightLeftFlag = false;
      rightLeftFlag2 = false;
      Serial.println("r");
    } else if (strncmp(buffer, backCommand.c_str(), len) == 0) {
      forwardBackFlag = true;
      forwardBackFlag2 = true;
      Serial.println("b");
    } else if (strncmp(buffer, forwardCommand.c_str(), len) == 0) {
      forwardBackFlag = false;
      forwardBackFlag2 = false;
      Serial.println("f");
    }  else if (strncmp(buffer, stopCommand.c_str(), len) == 0) {
      forwardBackFlag = false;
      forwardBackFlag2 = true;
      rightLeftFlag = false;
      rightLeftFlag2 = true;
      Serial.println("stop");
    }
  }
  if (forwardBackFlag) {
    digitalWrite(fbPort, HIGH);
  } else {
    digitalWrite(fbPort, LOW);
  }
  if (forwardBackFlag2) {
    digitalWrite(fbPort2, HIGH);
  } else {
    digitalWrite(fbPort2, LOW);
  }
  if (rightLeftFlag) {
    digitalWrite(rlPort, HIGH);
  } else {
    digitalWrite(rlPort, LOW);
  }
  if (rightLeftFlag2) {
    digitalWrite(rlPort2, HIGH);
  } else {
    digitalWrite(rlPort2, LOW);
  }
}

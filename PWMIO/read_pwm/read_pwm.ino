#include <Servo.h> 
Servo s1,s2;
void setup() {
  pinMode(3, INPUT);             
  pinMode(5, INPUT);
  s1.attach(6);
  s2.attach(9);                   
  Serial.begin(9600);                   
}

void loop() {
  int value1 = pulseIn(3, HIGH);
  int value2 = pulseIn(5, HIGH);
  s1.writeMicroseconds(value1);
  s2.writeMicroseconds(value2);
  Serial.print("3 : ");
  Serial.print(value1);
  Serial.print("   \n");
  Serial.print("5 : ");
  Serial.print(value2);
  Serial.print("   \n");
  delay(200);
}

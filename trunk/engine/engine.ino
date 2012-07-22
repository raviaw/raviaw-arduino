#include <Servo.h>

Servo servo1;

void setup() {
  pinMode(10, OUTPUT);
  servo1.attach(11);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(12, LOW); 
  for (int i = 0; i < 180; i += 1) {
    analogWrite(10, i);
    servo1.write(i);
    delay(5);
  }
  for (int i = 180; i >= 0; i -= 1) {
    analogWrite(10, i);
    servo1.write(i);
    delay(5);
  }
  servo1.write(90);
  delay(2000);
/*  digitalWrite(12, HIGH); 
  for (int i = 0; i < 255; i += 20) {
    analogWrite(10, i);
    analogWrite(11, i);
    delay(100);
  }
  delay(1000);
  for (int i = 255; i >= 0; i -= 20) {
    analogWrite(10, i);
    analogWrite(11, i);
    delay(100);
  }*/
}

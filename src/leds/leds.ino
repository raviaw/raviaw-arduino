/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 11;
int led2 = 10;
int led3 = 9;
int led4 = 6;
int led5 = 5;
int led6 = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);     
  pinMode(led4, OUTPUT);     
  pinMode(led5, OUTPUT);     
  pinMode(led6, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < 255; i+=11) {
    int sensorValue = analogRead(A0);
    analogWrite(led1, i);
    analogWrite(led2, 255 - i);
    delay(calculateDelay(sensorValue));
  }
  for (int i = 255; i>= 0; i-=11) {
    int sensorValue = analogRead(A0);
    analogWrite(led1, i);
    analogWrite(led2, 255 - i);
    delay(calculateDelay(sensorValue));
  }
}

int calculateDelay(int v) {
//  Serial.println(v);
  return (v - 50) / 15;
}

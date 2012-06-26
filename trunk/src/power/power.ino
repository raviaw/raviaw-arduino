/*
Da power
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
    int sensorValue = analogRead(A0);
    analogWrite(led1, ledOutput(sensorValue, ( 1024 / 6 ) * 0 , (1024 / 6) * 1));
    analogWrite(led2, ledOutput(sensorValue, ( 1024 / 6 ) * 1 , (1024 / 6) * 2));
    analogWrite(led3, ledOutput(sensorValue, ( 1024 / 6 ) * 2 , (1024 / 6) * 3));
    analogWrite(led4, ledOutput(sensorValue, ( 1024 / 6 ) * 3 , (1024 / 6) * 4));
    analogWrite(led5, ledOutput(sensorValue, ( 1024 / 6 ) * 4 , (1024 / 6) * 5));
    analogWrite(led6, ledOutput(sensorValue, ( 1024 / 6 ) * 5 , (1024 / 6) * 6));
}

int ledOutput(int currentValue, int startRange, int endRange) {
  if (currentValue < startRange ) {
    return 0;
  }
  if (currentValue > endRange) {
    return 255;
  }
  else {
    int range = endRange - startRange;
    int onSpan = currentValue - startRange;
    return (onSpan * range) / 255;
  }
}

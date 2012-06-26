  /*
Da power
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int def1 = 2;
int def2 = 3;
int def3 = 4;
int def4 = 5;
int def5 = 8;
int def6 = 10;
int def7 = 11;
int def8 = 12;

int led1 = def1;
int led2 = def2;
int led3 = def6;
int led4 = def4;
int led5 = def7;
int led6 = def8;
int led7 = def5;
int led8 = def3;

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
  pinMode(led7, OUTPUT);     
  pinMode(led8, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
    int sensorValue = analogRead(A0);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
    for (int x = 0; x < 5; x++) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);

      digitalWrite(led1, HIGH);
      delay(200);
      digitalWrite(led2, HIGH);
      delay(200);
      digitalWrite(led3, HIGH);
      delay(200);
      digitalWrite(led4, HIGH);
      delay(200);
      digitalWrite(led5, HIGH);
      delay(200);
      digitalWrite(led6, HIGH);
      delay(200);
      digitalWrite(led7, HIGH);
      delay(200);
      digitalWrite(led8, HIGH);
      delay(200);
      
      delay(100);
    }
      for (int i = 0; i < 30; i++) {
        number(i);
        delay(200);
      }
      for (int i = 0; i < 50; i++) {
        number(i);
        delay(100);
      }
    
    delay(500);
  }

int number(int number) {
  if ((number % 10 )== 1) {
    leds(LOW , HIGH, HIGH, LOW , LOW , LOW , LOW , LOW);
  } else if ((number % 10 ) == 2) {
    leds(HIGH, HIGH, LOW , HIGH, HIGH, LOW , HIGH, LOW);
  } else if ((number % 10 ) == 3) {
    leds(HIGH, HIGH, HIGH, HIGH, LOW , LOW , HIGH, LOW);
  } else if ((number % 10 ) == 4) {
    leds(LOW , HIGH, HIGH, LOW , LOW , HIGH , HIGH, LOW);
  } else if ((number % 10 ) == 5) {
    leds(HIGH, LOW, HIGH, HIGH , LOW , HIGH , HIGH, LOW);
  } else if ((number % 10 ) == 6) {
    leds(HIGH, LOW, HIGH, HIGH , HIGH , HIGH , HIGH , LOW);
  } else if ((number % 10 ) == 7) {
    leds(HIGH, HIGH, HIGH, LOW , LOW , LOW , LOW , LOW);
  } else if ((number % 10 ) == 8) {
    leds(HIGH , HIGH, HIGH, HIGH , HIGH , HIGH , HIGH , LOW);
  } else if ((number % 10 ) == 9) {
    leds(HIGH , HIGH, HIGH, HIGH , LOW,HIGH , HIGH , LOW);
  } else if ((number % 10 ) == 0) {
    leds(HIGH,HIGH, HIGH, HIGH , HIGH , HIGH , LOW , LOW);
  }
}

void leds(int led1val, int led2val, int led3val, int led4val, int led5val, int led6val, int led7val, int led8val) {
  digitalWrite(led1, led1val); 
  digitalWrite(led2, led2val); 
  digitalWrite(led3, led3val); 
  digitalWrite(led4, led4val); 
  digitalWrite(led5, led5val); 
  digitalWrite(led6, led6val); 
  digitalWrite(led7, led7val); 
  digitalWrite(led8, led8val); 
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

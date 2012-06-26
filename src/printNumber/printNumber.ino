int ledArraySize = 7;

int leds[] = { 2,3,4,5,6,7,8 };
int legs[] = { leds[6], leds[1], leds[4], leds[3], leds[5], leds[2], leds[0] };

int n0[] = { 1,1,1,1,1,1,0 };
int n1[] = { 0,1,1,0,0,0,0 };
int n2[] = { 1,1,0,1,1,0,1 };
int n3[] = { 1,1,1,1,0,0,1 };
int n4[] = { 0,1,1,0,0,1,1 };
int n5[] = { 1,0,1,1,0,1,1 };
int n6[] = { 1,0,1,1,1,1,1 };
int n7[] = { 1,1,1,0,0,0,0 };
int n8[] = { 1,1,1,1,1,1,1 };
int n9[] = { 1,1,1,1,0,1,1 };
int nA[] = { 1,1,1,0,1,1,1 };

void setup() {
  for (int i = 0; i < ledArraySize; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  
  randomSeed(analogRead(A4));
}

void loop() {
  for (int i = 0; i < ledArraySize; i++) {
    digitalWrite(legs[i], LOW);
  }
  for (int i = 0; i < ledArraySize; i++) {
    digitalWrite(legs[i], HIGH);
    delay(50);
  }
  for (int i = 0; i < ledArraySize; i++) {
    digitalWrite(legs[i], LOW);
  }
  /*for (int i = 0; i < 10; i++) {
    number(i);
    delay(50);
  }*/
  for (int i = 0; i < 5; i++) {
    switchIndicators(1, 1, 1, 1, 1);
    delay(100);
    switchIndicators(0, 0, 0, 0, 0);
  }
  
  printNumber(0, analogRead(A0));
  printNumber(1, analogRead(A1));
  printNumber(2, analogRead(A2));

  for (int i = 0; i < ledArraySize; i++) {
    digitalWrite(legs[i], LOW);
  }
  for (int i = 0; i < 100; i++) {
    int leg = random(2, 13);
    digitalWrite(leg, HIGH);
    delay(50);
    digitalWrite(leg, LOW);
    delay(50);
  }
  
}

void printNumber(int sensor, int in) {
  Serial.print("Sensor A");
  Serial.print(sensor);
  Serial.print(": ");
  Serial.println(in);

  int d0 = in / 1000;
  int d1 = in / 100;
  int d2 = in / 10;
  int d3 = in;
  
  for (int i = 0; i < 10; i++) {
    switchIndicators(1, 0, 0, 0, 0);
    delay(50);
    switchIndicators(0, 0, 0, 0, 0);
    delay(50);
  }

  delay(200);
  letter('A');
  delay(500);
  number(sensor);
  delay(500);

  for (int i = 0; i < ledArraySize; i++) {
    digitalWrite(legs[i], LOW);
  }
  switchIndicators(1, 0, 0, 0, 0);

  delay(500);
  switchIndicators(1, 1, 0, 0, 0);
  number(d0);
  delay(500);
  switchIndicators(1, 1, 1, 0, 0);
  number(d1);
  delay(500);
  switchIndicators(1, 1, 1, 1, 0);
  number(d2);
  delay(500);
  switchIndicators(1, 1, 1, 1, 1);
  number(d3);
  delay(500);
}

void letter(char letter) {
  if (letter == 'A') {
    switchLeds(nA);
  }
}

void number(int n) {
  switch(n % 10) {
    case 0:
      switchLeds(n0);
      break;
    case 1:
      switchLeds(n1);
      break;
    case 2:
      switchLeds(n2);
      break;
    case 3:
      switchLeds(n3);
      break;
    case 4:
      switchLeds(n4);
      break;
    case 5:
      switchLeds(n5);
      break;
    case 6:
      switchLeds(n6);
      break;
    case 7:
      switchLeds(n7);
      break;
    case 8:
      switchLeds(n8);
      break;
    case 9:
      switchLeds(n9);
      break;
  }
}

void switchIndicators(int i0, int i1, int i2, int i3, int i4) {
  if (i0 == 0) digitalWrite(13, LOW); else digitalWrite(13, HIGH);
  if (i1 == 0) digitalWrite(12, LOW); else digitalWrite(12, HIGH);
  if (i2 == 0) digitalWrite(11, LOW); else digitalWrite(11, HIGH);
  if (i3 == 0) digitalWrite(10, LOW); else digitalWrite(10, HIGH);
  if (i4 == 0) digitalWrite(9, LOW); else digitalWrite(9, HIGH);
}

void switchLeds(int values[]) {
  for (int i = 0; i < ledArraySize; i++) {
     if (values[i] == 0) {
       digitalWrite(legs[i], LOW);
     } else {
       digitalWrite(legs[i], HIGH);
     }
  }
}



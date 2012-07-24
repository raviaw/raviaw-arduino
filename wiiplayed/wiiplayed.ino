/*
 */
#include <Wire.h>
#include <Servo.h> 
#include <LiquidCrystal.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;
int loop_play_cnt = 0;
int accx,accy,accz,zbut,cbut,joyx,joyy,prevcbut,prevzbut,xval,yval;

int out = 0;
int running = 0;

Servo servo1;
Servo servo2;
Servo servo3;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int bin [] = {000, 1, 10, 11, 100, 101, 110, 111};//

int arrayx[] = {0, 0, 0, 0, 0};
int arrayy[] = {0, 0, 0, 0, 0};
int pointer = 0;

int applicationMode = 0;

#define IDLE 0
#define MOVING_CAR 1
#define POSITIONING_LIGHT 2
#define PLAYING 3

void setup()
{
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  
  lcd.begin(16, 2);

  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(8);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  prevcbut = 0; 
  prevzbut = 0;
  cbut = 0;
  zbut = 0;
}

void loop()
{
    if( loop_cnt > 20 ) { // every 20 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();
        calculate_axis();

        accx  = nunchuck_accelx();
        accy  = nunchuck_accely();
        accz  = nunchuck_accelz();
        joyx  = nunchuck_joyx();
        joyy  = nunchuck_joyy();
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton();
        
        if (zbut > 0 && prevzbut == 0) {
          zbut_down();
        } else if (zbut == 0 && prevzbut > 0) {
          zbut_up();
        }
        
        if (cbut > 0 && prevcbut == 0) {
          cbut_down();
        } else if (cbut == 0 && prevcbut > 0) {
          cbut_up();
        }
        
        // joyx - 26 - 129
        // 129 - 217
        
        // joyx - 134 - 223
        // 30 - 134
        
        if (applicationMode == MOVING_CAR) {
          movingCarCycle();
        } else if (applicationMode == POSITIONING_LIGHT) {
          positioningLightCycle();
        }
          
        statusOnLcd();

        prevcbut = cbut;
        prevzbut = zbut;
    }

    loop_play_cnt++;
    loop_cnt++;
    
    if (applicationMode == PLAYING && loop_play_cnt > 1000) {
      play();
      loop_play_cnt = 0;
    }    
    
    // 1 ms delay is enough
    delay(1);
}

void movingCarCycle() {
  int servo1val = valueInRange(joyx, 26, 217, 0, 180);
  servo1.write(servo1val);
  
  int enginePower = valueInRange(joyy, 30, 223, -500, 500);
  if (enginePower < 80 && enginePower > -80) {
    analogWrite(6, 0);
  } else if (enginePower < 0) {
    digitalWrite(7, LOW);
    analogWrite(6, map(enginePower, -500, 0, 255, 0));
  } else {
    digitalWrite(7, HIGH);
    analogWrite(6, map(enginePower, 0, 500, 0, 255));
  }
}

void positioningLightCycle() {
  xval = valueInRange(joyx, 26, 217, 180, 0);
  yval = valueInRange(joyy, 30, 223, 180, 0);
  if (cbut > 0) {
    servo3.write(xval);
    servo2.write(yval);
  }
}

void cbut_down() {
  switchMode(POSITIONING_LIGHT);

  // Disable engine
  digitalWrite(7, LOW);
  analogWrite(6, 0);
}

void cbut_up() {
  if (applicationMode == POSITIONING_LIGHT) {
    record();
  }
  
  switchMode(IDLE);
}

void zbut_down() {
}

void zbut_up() {
  if (applicationMode == MOVING_CAR) {
    pointer = 0;
    switchMode(PLAYING);
  } else {
    switchMode(MOVING_CAR);
  }
}

void switchMode(int newMode) {
  if (newMode == applicationMode) {
    // No change
    return;
  }
  
  applicationMode = newMode;
  switch(newMode) {
    case IDLE:
    case PLAYING:
    case POSITIONING_LIGHT:
      digitalWrite(7, LOW);
      analogWrite(6, 0);
      break;
    case MOVING_CAR:
      break;
  }
}

void play() {
  servo3.write(arrayx[pointer]);
  servo2.write(arrayy[pointer]);
  pointer++;
  if (pointer >= sizeof(arrayx) / sizeof(int)) {
    pointer = 0;
  }
}

void record() {
  arrayx[pointer] = xval;
  arrayy[pointer] = yval;
  pointer++;
  if (pointer >= sizeof(arrayx) / sizeof(int)) {
    pointer = 0;
  }
}

int valueInRange(int value, int valueMin, int valueMax, int rangeMin, int rangeMax) {
  if (value < valueMin) {
    return map(valueMin, valueMin, valueMax, rangeMin, rangeMax);
  } else if (value > valueMax) {
    return map(valueMax, valueMin, valueMax, rangeMin, rangeMax);
  } else {
    return map(value, valueMin, valueMax, rangeMin, rangeMax);
  }
}

void statusOnLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print((int)accx,DEC);
  lcd.setCursor(5, 0);
  lcd.print((int)accy,DEC);
  lcd.setCursor(10, 0);
  lcd.print((int)accz,DEC);
  
  lcd.setCursor(0, 1);
  lcd.print((byte)zbut,DEC);
  lcd.setCursor(2, 1);
  lcd.print((byte)cbut,DEC);
  if (applicationMode == PLAYING) {
    lcd.setCursor(3, 1);
    lcd.print(">");
    lcd.setCursor(4, 1);
    lcd.print((byte)arrayx[pointer],DEC);
    lcd.setCursor(8, 1);
    lcd.print((byte)arrayy[pointer],DEC);
  } else {
    lcd.setCursor(3, 1);
    lcd.print("<");
    lcd.setCursor(4, 1);
    lcd.print((byte)joyx,DEC);
    lcd.setCursor(8, 1);
    lcd.print((byte)joyy,DEC);
  }

  lcd.setCursor(12, 1);
  lcd.print(running,DEC);
  lcd.setCursor(13, 1);
  lcd.print(pointer,DEC);
  
  // #define IDLE = 0;
  // #define MOVING_CAR = 1;
  // #define POSITIONING_LIGHT = 2;
  // #define PLAYING = 3;

  if (applicationMode == IDLE) {
    lcd.setCursor(15, 1);
    lcd.print("*");
  } else if (applicationMode == MOVING_CAR) {
    lcd.setCursor(15, 1);
    lcd.print("M");
  } else if (applicationMode == POSITIONING_LIGHT) {
    lcd.setCursor(15, 1);
    lcd.print("L");
  } else if (applicationMode == PLAYING) {
    lcd.setCursor(15, 1);
    lcd.print("P");
  }
}

void plexOut(int count, int value) {
  int row = bin[count];
  int r0 = row & 0x01;
  int r1 = (row>>1) & 0x01;
  int r2 = (row>>2) & 0x01;

  lcd.setCursor(13, 1);
  lcd.print((byte)r0,DEC);
  lcd.setCursor(14, 1);
  lcd.print((byte)r1,DEC);
  lcd.setCursor(15, 1);
  lcd.print((byte)r2,DEC);

  digitalWrite(7, r0);
  digitalWrite(8, r1);
  digitalWrite(13, r2);
  analogWrite(6, value);
}


/*
 */
#include <Wire.h>
#include <Servo.h> 
#include <LiquidCrystal.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;
int loop_play_cnt = 0;
int accx,accy,accz,zbut,cbut,joyx,joyy;

int out = 0;
int running = 0;

Servo servo1;
Servo servo2;
Servo servo3;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int bin [] = {000, 1, 10, 11, 100, 101, 110, 111};//

int recording = 1;

int arrayx[] = {0, 0, 0, 0, 0};
int arrayy[] = {0, 0, 0, 0, 0};
int pointer = 0;

int playing = 0;

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
        
        applyRunningLogic();
        
        // joyx - 26 - 129
        // 129 - 217
        
        // joyx - 134 - 223
        // 30 - 134
        
        if (running) {
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
        } else {
          digitalWrite(7, LOW);
          analogWrite(6, 0);

          int xval = valueInRange(joyx, 26, 217, 180, 0);
          int yval = valueInRange(joyy, 30, 223, 180, 0);
          if (cbut > 0) {
            servo3.write(xval);
            servo2.write(yval);
          }
          
          // cbut... records the sequence
          if (cbut == 0) {
            if (recording) {
              record(xval, yval);
              recording = 0;
            }
          } else {
            recording = 1;
          }
        }
          
        statusOnLcd();
    }

    loop_play_cnt++;
    loop_cnt++;
    
    if (playing && loop_play_cnt > 1000) {
      play();
      loop_play_cnt = 0;
    }    
    delay(1);
}

void record(int xval, int yval) {
  arrayx[pointer] = xval;
  arrayy[pointer] = yval;
  pointer++;
  if (pointer >= sizeof(arrayx) / sizeof(int)) {
    pointer = 0;
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

int valueInRange(int value, int valueMin, int valueMax, int rangeMin, int rangeMax) {
  if (value < valueMin) {
    return map(valueMin, valueMin, valueMax, rangeMin, rangeMax);
  } else if (value > valueMax) {
    return map(valueMax, valueMin, valueMax, rangeMin, rangeMax);
  } else {
    return map(value, valueMin, valueMax, rangeMin, rangeMax);
  }
}

void applyRunningLogic() {
  if (cbut > 0 && zbut > 0) {
    playing = 1;
    running = 0;
    recording = 0;
  } else if (zbut > 0) {
    playing = 0;
    running = 1;
    recording = 0;
  } else if (cbut > 0) {
    playing = 0;
    running = 0;
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
  if (playing) {
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
  
  if (recording) {
    lcd.setCursor(15, 1);
    lcd.print("R");
  } else if (running) {
    lcd.setCursor(15, 1);
    lcd.print(">");
  } else if (playing) {
    lcd.setCursor(15, 1);
    lcd.print("P");
  } else {
    lcd.setCursor(15, 1);
    lcd.print("!");
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


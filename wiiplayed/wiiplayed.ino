/*
 */
#include <Wire.h>
#include <Servo.h> 
#include <LiquidCrystal.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;
int accx,accy,accz,zbut,cbut,joyx,joyy;

int out = 0;
int running = 0;

Servo servo1;
Servo servo2;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int bin [] = {000, 1, 10, 11, 100, 101, 110, 111};//

void setup()
{
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  
  lcd.begin(16, 2);

  servo1.attach(9);
  servo2.attach(10);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  //pinMode(8, OUTPUT);
  //pinMode(13, OUTPUT);
}

int flow = +1;
// Plexer is 7, 8, 13, Output is 6
void loop()
{
    if( loop_cnt > 20 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuck_get_data();
        calculate_axis();

        accx  = nunchuck_accelx(); // ranges from approx 70 - 182
        accy  = nunchuck_accely(); // ranges from approx 65 - 173
        accz  = nunchuck_accelz(); // ranges from approx 65 - 173
        joyx  = nunchuck_joyx(); // ranges from approx 70 - 182
        joyy  = nunchuck_joyy(); // ranges from approx 65 - 173
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 
        
        int servo1val = map(joyx, 60, 240, 180, 0);
        int servo2val = map(joyy, 30, 230, 180, 0);
//        int servo1val = map(accx, 70, 182, 0, 180);
//        int servo2val = map(accy, 65, 173, 0, 180);
            
        /*Serial.print("accx: "); Serial.print((byte)accx,DEC);
        Serial.print("\taccy: "); Serial.print((byte)accy,DEC);
        Serial.print("\tzbut: "); Serial.print((byte)zbut,DEC);
        Serial.print("\tcbut: "); Serial.println((byte)cbut,DEC);*/
        
        servo1.write(servo1val);
        servo2.write(servo2val);
        
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
        lcd.setCursor(4, 1);
        lcd.print((byte)joyx,DEC);
        lcd.setCursor(8, 1);
        lcd.print((byte)joyy,DEC);

        if (zbut > 0) {
          running = 1;
        } else if (cbut > 0) {
          running = 0;
        }
        int direction1val = map(accx, 280, 750, -3, +3);
        if (direction1val < -1) {
          digitalWrite(7, LOW);
        } else if (direction1val > 1) {
          digitalWrite(7, HIGH);
        }
        if (running > 0) {
          if (accy > 300 && accy < 740) {
            analogWrite(6, map(accy, 300, 740, 0, 255));
          }
        } else {
          digitalWrite(6, LOW);
        }
    }

    loop_cnt++;
    delay(1);
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


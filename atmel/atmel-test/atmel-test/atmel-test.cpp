/*
Blink Example
Turns on an LED on for one second,
then off for one second, repeatedly.
 
This example code is in the public domain.
Modified - MegunoLink 2012
*/
 
#include <arduino.h>
 
//Function Prototypes (In Atmel Studio you need to have function prototypes)
void serialMessage();
 
void setup()
{
  // set digital pin as an output.
  // Pin 13 has an LED connected on most Arduino's:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
 
 
void loop()
{
  digitalWrite(13, HIGH);    // set the LED on
  delay(1000);               // wait for a second
  digitalWrite(13, LOW);     // set the LED off
  delay(1000);               // wait for a second 
  serialMessage();
}
 
void serialMessage()
{
  Serial.println("Hello Word!");
}
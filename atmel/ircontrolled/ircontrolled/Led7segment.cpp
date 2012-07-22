/*
* led7segment.cpp
*
* Created: 6/28/2012 5:06:31 PM
*  Author: raviw
*/
#include <arduino.h>

#include "Led7segment.h"

const int ledArraySize = 7;

const int leds[] = { 5,6,7,8,9,10,12 };
const int legs[] = { leds[5], leds[6], leds[2], leds[1], leds[0], leds[4], leds[3] };

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

int Led7Segment() {
	srand( analogRead(A5) );
}

void Led7Segment::initializeLedPins() {
  for (int i = 0; i < ledArraySize; i++) {
	  pinMode(leds[i], OUTPUT);
  }
}

void Led7Segment::showSequence(int waitTimeMs) {
	low();
	for (int i = 0; i < ledArraySize; i++) {
		digitalWrite(legs[i], HIGH);
		delay(waitTimeMs);
	}
	low();
}

void Led7Segment::low() {
	for (int i = 0; i < ledArraySize; i++) {
		digitalWrite(legs[i], LOW);
	}
}

void Led7Segment::randomBlinkLeds(int cycles, int upTimeMs) {
}

void Led7Segment::randomSwitchLeds(int cycles, int upTimeMs) {
	int ledsStatus[ledArraySize];
	memset(ledsStatus, 0, sizeof(ledsStatus));
	low();
	for (int i = 0; i < cycles; i++) {
		int next = rand() % ledArraySize;
		if (ledsStatus[next] == 1) {
			ledsStatus[next] = 0;
			digitalWrite(leds[next], LOW);
		} else {
			ledsStatus[next] = 1;
			digitalWrite(leds[next], HIGH);
		}
		delay(upTimeMs);
	}
}

void Led7Segment::printNumber(int n) {
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

void Led7Segment::switchLeds(int values[]) {
	for (int i = 0; i < ledArraySize; i++) {
		if (values[i] == 0) {
			digitalWrite(legs[i], LOW);
		} else {
			digitalWrite(legs[i], HIGH);
		}
	}
}
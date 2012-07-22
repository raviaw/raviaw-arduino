/*
* ircontrolled.cpp
*
* Created: 6/28/2012 5:05:28 PM
*  Author: raviw
*/

#include <arduino.h>
#include "Led7segment.h"

#define IRpin_PIN PIND
#define IRpin 2
#define PIN_HIGH ( IRpin_PIN & _BV(IRpin) )

#define STOP_CODE 3944004165
#define PLAY_CODE 3927292485
#define KEY_1 4261526085
#define KEY_2 4244814405
#define KEY_3 4228102725
#define KEY_4 4211391045
#define KEY_5 4194679365
#define KEY_6 4177967685
#define KEY_7 4161256005
#define KEY_8 4144544325
#define KEY_9 4127832645
#define KEY_0 4111120965
#define KEY_SKIP_REV 3693328965
#define KEY_SKIP_FWD 3676617285
#define KEY_REV 3860445765
#define KEY_FWD 3960715845

#define KEY_UP 2139142725
#define KEY_RIGHT 2991438405
#define KEY_DOWN 2122431045
#define KEY_LEFT 2924591685

#define KEY_ENTER 3726752325

#define MAXPULSE 1000
#define RESOLUTION 20
#define MAX_PULSES 60
#define PULSE_ARRAY_SIZE 100

#define PLAY_PIN 3
#define BLINK_PIN 4
#define HIGH_POWER_LED 11

#define MOTOR_REVERSE_PIN 12
#define MOTOR_POWER_PIN 11
#define MOTOR_STATUS_PIN 10

unsigned int pulses[100][2];  // pair is high and low pulse
unsigned short currentpulse = 0; // index for pulses we're storing

int currentPower = 0;

// 0, 1, 2, 3, 4
int currentEnginePower = 0;
const int maxEnginePower = 10;

void onPulse(void);
void processCommand(unsigned long command);
int calculateCurrentPowerIncrement();
void adjustPower(int increment);
void engineForward();
void engineReverse();
void enginePowerIncrease();
void enginePowerDecrease();
void engineStop();

int translateToPower(int currentPower);
void 	setPower(int power);

void setup()
{
	Serial.begin(9600);
	Serial.println("Ready to go");
	//Led7Segment::initializeLedPins();
	pinMode(IRpin, INPUT);
	pinMode(PLAY_PIN, OUTPUT);
	pinMode(HIGH_POWER_LED, OUTPUT);
	pinMode(MOTOR_POWER_PIN, OUTPUT);
	pinMode(MOTOR_REVERSE_PIN, OUTPUT);
	pinMode(MOTOR_STATUS_PIN, OUTPUT);
}

void loop()
{
	/*int analogReadValue = analogRead(A0);
	Serial.print("{A0,T,");
	Serial.print(analogReadValue);
	Serial.println("}");
	if (1 == 1) {
		return;
	}*/

	unsigned int highpulse, lowpulse;  // temporary storage timing
	highpulse = lowpulse = 0; // start out with no pulse length
	
	while (PIN_HIGH) {
		highpulse++;
		delayMicroseconds(RESOLUTION);
		
		// If the pulse is too long, we 'timed out' - either nothing
		// was received or the code is finished, so print what
		// we've grabbed so far, and then reset
		if (highpulse > MAXPULSE && currentpulse != 0) {
			onPulse();
			currentpulse = 0;
			return;
		}
	}

	while (!PIN_HIGH) {
		lowpulse++;
		delayMicroseconds(RESOLUTION);
		if (lowpulse > MAXPULSE && currentpulse != 0) {
			onPulse();
			currentpulse = 0;
			return;
		}
	}
	
	// No start was received, ignore anything else until something is actually received in the input
	if (highpulse > 10 && lowpulse > 10) {
		pulses[currentpulse][0] = highpulse;
		pulses[currentpulse][1] = lowpulse;
		
		// we read one high-low pulse successfully, continue!
		currentpulse++;
		if(currentpulse >= MAX_PULSES) {
			// Do something... Can't reach MAX_PULSES
			onPulse();
			currentpulse = 0;
		}
	}
}

void onPulse(void) {
	unsigned long final = 0;
	unsigned long n = 1;
	for (int i = 1; i < currentpulse; i++) {
		if (pulses[i][0] > 20 && pulses[i][0] < 50) {
			n *= 2;
		}  else if (pulses[i][0] > 60 && pulses[i][0] < 100) {
			final += n;
			n *= 2;
		}
	}
	
	if (final == 0) {
		return;
	}

	Serial.print("Doing something: ");
	Serial.println(final);
	processCommand(final);
	
	for (int i = 0; i < PULSE_ARRAY_SIZE; i++) {
		pulses[i][0] = 0;
		pulses[i][1] = 0;
	}
}

void processCommand(unsigned long command) {
	if (command == KEY_RIGHT) {
		engineForward();
	} else if (command == KEY_LEFT) {
		engineReverse();
	} else if (command == KEY_UP) {
		enginePowerIncrease();
	} else if (command == KEY_DOWN) {
		enginePowerDecrease();
	} else if (command == KEY_ENTER) {
		engineStop();
	}
}	

void engineForward() {
	int oldPower = currentEnginePower;
	digitalWrite(MOTOR_REVERSE_PIN, HIGH);
	setPower(oldPower);
}

void engineReverse() {
	int oldPower = currentEnginePower;
	digitalWrite(MOTOR_REVERSE_PIN, LOW);
	setPower(oldPower);
}

void engineStop() {
	currentEnginePower = 0;
	setPower(currentEnginePower);
}

void enginePowerIncrease() {
	currentEnginePower++;
	if (currentEnginePower > maxEnginePower) {
		currentEnginePower = maxEnginePower;
	}
	setPower(currentEnginePower);
}

void enginePowerDecrease()
{
	currentEnginePower--;
	if (currentEnginePower < 0) {
		currentEnginePower = 0;
	}
	setPower(currentEnginePower);
}	

void setPower(int currentPowerFactor) {
	int power = translateToPower(currentPowerFactor);
	//analogWrite(MOTOR_POWER_PIN, power);
	analogWrite(MOTOR_STATUS_PIN, power);
}

int translateToPower(int currentPower) {
	switch(currentPower) {
		case 0:
		return 0;
		case 1:
		return 78;
		case 2:
		return 80;
		case 3:
		return 82;
		case 4:
		return 85;
		case 5:
		return 90;
		case 6:
		return 100;
		case 7:
		return 110;
		case 8:
		return 120;
		case 9:
		return 140;
		case 10:
		return 160;
	}
}

/*void processCommand(unsigned long command) {
	if (command == PLAY_CODE) {
		digitalWrite(PLAY_PIN, HIGH);
	} else if (command == STOP_CODE) {
		digitalWrite(PLAY_PIN, LOW);
	} else if (command == KEY_1) {
		Led7Segment::printNumber(1);
	} else if (command == KEY_2) {
		Led7Segment::printNumber(2);
	} else if (command == KEY_3) {
		Led7Segment::printNumber(3);
	} else if (command == KEY_4) {
		Led7Segment::printNumber(4);
	} else if (command == KEY_5) {
		Led7Segment::printNumber(5);
	} else if (command == KEY_6) {
		Led7Segment::printNumber(6);
	} else if (command == KEY_7) {
		Led7Segment::printNumber(7);
	} else if (command == KEY_8) {
		Led7Segment::printNumber(8);
	} else if (command == KEY_9) {
		Led7Segment::printNumber(9);
	} else if (command == KEY_0) {
		Led7Segment::printNumber(0);
	} else if (command == KEY_SKIP_REV) {
		adjustPower(-255);
	} else if (command == KEY_SKIP_FWD) {
		adjustPower(255);
	} else if (command == KEY_REV) {
		adjustPower(-1 * calculateCurrentPowerIncrement());
	} else if (command == KEY_FWD) {
		adjustPower(calculateCurrentPowerIncrement());
	} else if (command == KEY_UP) {
		Serial.println("KEY_UP");
		Led7Segment::randomSwitchLeds(400, 5);
	} else if (command == KEY_RIGHT) {
		Serial.println("KEY_RIGHT");
		Led7Segment::randomSwitchLeds(200, 15);
	} else if (command == KEY_DOWN) {
		Serial.println("KEY_DOWN");
		Led7Segment::randomSwitchLeds(100, 30);
	} else if (command == KEY_LEFT) {
		Serial.println("KEY_LEFT");
		Led7Segment::randomSwitchLeds(25, 50);
	}		
}*/

int calculateCurrentPowerIncrement() {
	if (currentPower > 5) {
		return currentPower / 5;
	} else {
		return 1;
	}
}

void adjustPower(int increment) {
	currentPower += increment;
	if (currentPower > 255) {
		currentPower = 255;
	} else if (currentPower < 0) {
		currentPower = 0;
	}
	analogWrite(HIGH_POWER_LED, currentPower);
}


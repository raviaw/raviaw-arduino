#define IRpin_PIN      PIND
#define IRpin          2
 
#define MAXPULSE 65000
#define RESOLUTION 20 

#define PLAY_CODE 496550
#define STOP_CODE 531878
#define KEY_1 919462
#define KEY_2 854438
#define KEY_3 657830
#define KEY_4 789926
#define KEY_5 723878
#define KEY_6 691622
#define KEY_7 658342
#define KEY_8 726438
#define KEY_9 659366
#define KEY_0 627110

#define MAX_PULSES 34

#define PLAY_PIN 3
#define BLINK_PIN 4
 
#define PULSE_ARRAY_SIZE 100

unsigned int pulses[100][2];  // pair is high and low pulse 
unsigned short currentpulse = 0; // index for pulses we're storing

int ledArraySize = 7;

int leds[] = { 5,6,7,8,9,10,11 };
int legs[] = { leds[5], leds[6], leds[2], leds[1], leds[0], leds[4], leds[3] };

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
 
void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
  pinMode(PLAY_PIN, OUTPUT);
  pinMode(BLINK_PIN, OUTPUT);

  for (int i = 0; i < ledArraySize; i++) {
    pinMode(leds[i], OUTPUT);
  }
}
 
void loop(void) {
  uint16_t highpulse, lowpulse;  // temporary storage timing
  highpulse = lowpulse = 0; // start out with no pulse length
 
  while (IRpin_PIN & _BV(IRpin)) {
    highpulse++;
    delayMicroseconds(RESOLUTION);
   
     // If the pulse is too long, we 'timed out' - either nothing
     // was received or the code is finished, so print what
     // we've grabbed so far, and then reset
     if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
       onPulse();
       currentpulse = 0;
       return;
     }
  }

  while (!(IRpin_PIN & _BV(IRpin))) {
     lowpulse++;
     delayMicroseconds(RESOLUTION);
     if ((lowpulse >= MAXPULSE)  && (currentpulse != 0)) {
       onPulse();
       currentpulse = 0;
       return;
     }
  }
  
  // No start was received, ignore anything else until something is actually received in the input
  if (highpulse > 200 && lowpulse > 200) {
    // Reset!
    currentpulse = 1;
    highpulse = 0;
    lowpulse = 0;
  } else {
    if (highpulse > 10 && lowpulse > 10) {
      pulses[currentpulse][0] = highpulse;
      pulses[currentpulse][1] = lowpulse;
     
      // we read one high-low pulse successfully, continue!
      currentpulse++;
      if(currentpulse >= MAX_PULSES) {
        onPulse();
        currentpulse = 0;
      }
    }
  }
}
 
void onPulse(void) {
  unsigned long final = 0;
  unsigned long n = 1;
  for (uint8_t i = 0; i < currentpulse; i++) {
    if (pulses[i][0] > 20 && pulses[i][0] < 50) {
      n *= 2;
    }  else if (pulses[i][0] > 60 && pulses[i][0] < 100) {
      final += (n * 2);
    }
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
  if (command == PLAY_CODE) {
    digitalWrite(PLAY_PIN, HIGH);
  } else if (command == STOP_CODE) {
    digitalWrite(PLAY_PIN, LOW);
  } else if (command == KEY_1) {
    number(1);
  } else if (command == KEY_2) {
    number(2);
  } else if (command == KEY_3) {
    number(3);
  } else if (command == KEY_4) {
    number(4);
  } else if (command == KEY_5) {
    number(5);
  } else if (command == KEY_6) {
    number(6);
  } else if (command == KEY_7) {
    number(7);
  } else if (command == KEY_8) {
    number(8);
  } else if (command == KEY_9) {
    number(9);
  } else if (command == KEY_0) {
    number(0);
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

void switchLeds(int values[]) {
  for (int i = 0; i < ledArraySize; i++) {
     if (values[i] == 0) {
       digitalWrite(legs[i], LOW);
     } else {
       digitalWrite(legs[i], HIGH);
     }
  }
}


/*
 * led7segment.h
 *
 * Created: 6/28/2012 5:06:57 PM
 *  Author: raviw
 */ 


#ifndef LED7SEGMENT_H_
#define LED7SEGMENT_H_

class Led7Segment {
	public:
		static void initializeLedPins();
		static void showSequence(int waitTimeMs);
		static void printNumber(int n);
	private:
		static void switchLeds(int values[]);
};

#endif /* LED7SEGMENT_H_ */
/*
 * EC450 HW#1 Blink LED1 in S-O-S Morse code
 * Jeffrey Kittredge
 * January 28, 2014
 */
#include <msp430g2553.h>
#include <intrinsics.h>

#define DOT 1
#define DASH 3
#define SYMBOL_SEPERATOR 1
#define LETTER_SEPERATOR 3
#define MESSAGE_SEPERATOR 4 			//only 4 because every letter already terminates with LETTER_SEPERATOR which is 3

#define DUMMY_COUNTER 10000				//this is the pulse width scalar

void dummyLoop( const char waitValue);
void pulseOut( const char pulseStream[], const char[]);

const char S[6] = { DOT, SYMBOL_SEPERATOR, DOT, SYMBOL_SEPERATOR, DOT, LETTER_SEPERATOR };
const char Sstate[6] = { 1, 0, 1, 0, 1, 0};	//1 is on, 0 is off
const char O[6] = { DASH, SYMBOL_SEPERATOR, DASH, SYMBOL_SEPERATOR, DASH, LETTER_SEPERATOR };
const char Ostate[6] = { 1, 0, 1, 0, 1, 0};	//1 is on, 0 is off

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;    		// Stop watchdog timer
	P1DIR |= BIT0;               		// Configure P1.0 as output
	P1OUT &= ~BIT0;				 		//turn of the LED to start

	for (;;)
	{
		pulseOut( S, Sstate);
		pulseOut( O, Ostate);
		pulseOut( S, Sstate);

		dummyLoop( MESSAGE_SEPERATOR );
	}
}

//Software delay
void dummyLoop( const char waitValue){
	volatile int x, y;
	for( x=0; x< waitValue; x++)
		for ( y=0; y< DUMMY_COUNTER; y++)
			;								//do nothing in the inner loop
		;									//do nothing in the outer loop
}

//Indexes through sequence
void pulseOut( const char pulseStream[], const char state[]){
	volatile char letterIncrementer;

	for( letterIncrementer =0; letterIncrementer <6; letterIncrementer++)
	{
		state[ letterIncrementer] == 1 ? (P1OUT |= BIT0) : (P1OUT &= ~BIT0);

		dummyLoop( pulseStream[ letterIncrementer]);
	}
}

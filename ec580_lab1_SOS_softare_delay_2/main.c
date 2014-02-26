#include <msp430g2553.h>
#include <intrinsics.h>


#define DOT 1
#define DASH 3
#define SYMBOLSEPERATOR 1
#define LETTERSEPERATOR 3
#define MESSAGESEPERATOR 4 		//only 4 because every letter already terminates with LETTERSEPERATOR which is 3

#define DUMMYCOUNTER 20000

void dummyLoop( int waitValue);

const int S[6] = { DOT, SYMBOLSEPERATOR, DOT, SYMBOLSEPERATOR, DOT, LETTERSEPERATOR };
const char Sstate[6] = { 1, 0, 1, 0, 1, 0};
const int O[6] = { DASH, SYMBOLSEPERATOR, DASH, SYMBOLSEPERATOR, DASH, LETTERSEPERATOR };
const char Ostate[6] = { 1, 0, 1, 0, 1, 0};

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer
	P1DIR |= BIT0;               // Configure P1.0 as output
	P1OUT &= ~BIT0;				 //turn of the LED to start

	volatile unsigned char letterStepper = 0;

	for (;;)
	{
		for( letterStepper =0; letterStepper <6; letterStepper++)
		{
			Sstate[ letterStepper] == 1 ? (P1OUT |= BIT0) : (P1OUT &= ~BIT0);

			dummyLoop( S[ letterStepper]);
		}

		for( letterStepper =0; letterStepper <6; letterStepper++)
		{
			Ostate[ letterStepper] == 1 ? (P1OUT |= BIT0) : (P1OUT &= ~BIT0);

			dummyLoop( O[ letterStepper]);
		}

		for( letterStepper =0; letterStepper <6; letterStepper++)
		{
			Sstate[ letterStepper] == 1 ? (P1OUT |= BIT0) : (P1OUT &= ~BIT0);

			dummyLoop( S[ letterStepper]);
		}

		dummyLoop( MESSAGESEPERATOR );
	}
}


void dummyLoop( int waitValue){
	volatile int x, y;
	for( x=0; x< waitValue; x++)
		for ( y=0; y< DUMMYCOUNTER; y++)
			;								//do nothing on the inner loop
		;									//do nothing on the outer loop
}

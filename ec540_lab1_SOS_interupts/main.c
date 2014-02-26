//blink S-O-S using Watch Dog Timer interrupts, ec450 hw 1, jeff kittredge
#include <msp430g2553.h>
#include <intrinsics.h>
#include "SOS_letters_and_symbols.h"

#define PULSE_STRETCHER 7 //this stretches everything to make human perceivable

static inline void updateLEDandMaybeStep( const char symbolArray[], const int symbolArrayLength, const char stateArray[], char nextState, const char nextSymbolArray[] );

volatile unsigned char downEveryWDT = 0; //decrement every WDT
volatile unsigned char whichLetter = FIRST_S;
volatile unsigned char symbolIncrementer = 0;

void main(void){
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	//password + IntervalTimerMode + ClearCount + (SMCLK=source) + /32k
	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL ;

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	IE1 |= WDTIE;

	_bis_SR_register(GIE + LPM0_bits);
}

static inline void updateLEDandMaybeStep( const char symbolArray[], const int symbolArrayLength, const char stateArray[], char nextState, const char nextSymbolArray[] ){
	stateArray[symbolIncrementer]==1 ? (P1OUT |= BIT0) : (P1OUT &= ~BIT0); //update the LED

	if( symbolIncrementer == symbolArrayLength){
		whichLetter = nextState;
		symbolIncrementer = 0;
		downEveryWDT = nextSymbolArray[0];
	}
	else
		downEveryWDT = symbolArray[symbolIncrementer++]*PULSE_STRETCHER;
}
//only really do anything if downEveryWDT has expired (reached 0)
interrupt void WDT_interval_handler(){
	if (--downEveryWDT==0){
		switch (whichLetter){//all the cases
			case FIRST_S:{
				updateLEDandMaybeStep( S, sizeof(S)/sizeof(S[0]), Sstate, theO, O );
				break;
			}
			case THE_O:{
				updateLEDandMaybeStep( O, sizeof(O)/sizeof(O[0]), Ostate, secondS, S );
				break;
			}
			case SECOND_S:{
				updateLEDandMaybeStep( S, sizeof(S)/sizeof(S[0]), Sstate, nowMS, MS );
				break;
			}
			case NOW_MS:{
				updateLEDandMaybeStep( MS, sizeof(MS)/sizeof(MS[0]), MSstate, firstS, S );
				break;
			}
		}
	}
}


//macro to create the ISR and assign it the correct address in the interrupt vector table
ISR_VECTOR(WDT_interval_handler, ".int10")

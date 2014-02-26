#include <msp430g2553.h>
#include <intrinsics.h>
#include <stdint.h>
//test to see if button presses are correctly de-bounced
/*
 * main.c
 */
#define RED BIT0
#define GREEN BIT6
#define BUTTON BIT3

volatile uint8_t buttonState = 0;

//GPIO (button press) interrupt handler
interrupt void button_isr_handler(){
	switch (buttonState){
		case 0:{
			P1OUT |= GREEN;
			P1IES &= ~BUTTON;
			buttonState = 1;
			break;
		}
		case 1:{
			P1OUT &= ~(GREEN);
			P1IES |= BUTTON;
			buttonState = 0;
			break;
		}
	}


	//P1OUT ^= GREEN;
	//P1IES &= ~(BUTTON);


	P1IFG = 0;
}
ISR_VECTOR( button_isr_handler, ".int02")

void main(void) {
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1OUT &= ~(RED + GREEN);			//start with both LEDs off
	P1DIR |= RED + GREEN;				//LEDs as outputs
	P1DIR &= ~BUTTON;					//button as input
	P1OUT |= BUTTON;					//button is normally high
	P1REN |= BUTTON;					//button is pulled normally high by resistor
	P1IE |= BUTTON;						//enable interrupts on button pin
	P1IES &= ~(BUTTON);					//start by watching to downward going edge
	
	_bis_SR_register( GIE + LPM0_bits);
}

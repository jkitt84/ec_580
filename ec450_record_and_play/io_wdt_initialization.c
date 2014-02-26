/*
 * io_wdt_initialization.c
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */
#include <msp430.h>
#include <intrinsics.h>
#include "io_wdt_initialization.h"

void init_wdt(){
	//password + IntervalTimerMode + ClearCount + (SMCLK=source) + /32k
	/*
	 * password +
	 * interval timer mode +
	 * clear the count +
	 * (source = SMCLK) +
	 * source / 8192
	 */
	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + BIT0;

	IE1 |= WDTIE; 				//enable the WDT Interrupt

}

void init_GPIO(){
	P1OUT &= ~(RED + GREEN);			//start with both LEDs off
	P1DIR |= RED + GREEN;				//LEDs as outputs
	P1DIR &= ~BUTTON;					//button as input
	P1OUT |= BUTTON;					//button is normally high
	P1REN |= BUTTON;					//button is pulled normally high by resistor
	P1IE |= BUTTON;						//enable interrupts on button pin
	P1IES |= BUTTON;					//start by watching for downward going edge
}

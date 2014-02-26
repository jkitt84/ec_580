//EC450 HW#2 record and play back button presses on an LED, jeffrey kittredge, Feb 16, 2014

/*
 *button is not debounced, prone to errors from bouncing
 *if record is not correct... try again
 */

/*
 * Hold down button P1.3 for 6 seconds to start record.
 * Record lasts 10 seconds
 * up to 20 presses can be recorded
 *
 * playback starts automatically
 *
 * playbacks are seperated by a series of flashes
 */

#include <msp430g2553.h>
#include <intrinsics.h>
#include <stdint.h>

#include "unused_interrupts.h"
#include "io_wdt_initialization.h"
#include "wdt_isr.h"
#include "button_isr.h"
#include "recording_parameters.h"
#include "play_state_machine.h"
#include "record_State_Machine.h"

//1 if recording, 0 if playing
//start in "play"
volatile uint8_t recordActive = 0;

//an array of int's that records presses ( and releases) as there
//displacement in WDT pulses from start of record
volatile uint16_t pressStamps[ MAX_NUMBER_OF_PRESSES +1 ] = {0} ;
volatile uint16_t releaseStamps[ MAX_NUMBER_OF_PRESSES +1 ] = {0};

//where in the array of press/ release program is currently
volatile uint8_t pressStampIndex = 0;
volatile uint8_t releaseStampIndex = 0;

//increments every WDT
volatile uint16_t playStepper = 0;

//increments every WDT
volatile uint16_t recordStepper = 0;

//counts down to see if button has been held for RECORD_TIMEOUT_LIMIT
//and a record should start
volatile uint16_t recordTimeoutCounter = 0; //start at 0 to prevent counting down and going into record at start of run

//keeps track of the state of the button, start UP
volatile uint8_t buttonState = UP;		//start with it in the high state

void main(void) {
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	init_wdt();
	init_GPIO();
	
	_bis_SR_register( GIE + LPM0_bits);
}

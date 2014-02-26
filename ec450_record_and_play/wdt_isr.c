/*
 * wdt_isr.c
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */
#include <msp430g2553.h>
#include "wdt_isr.h"
#include <stdint.h>
#include "io_wdt_initialization.h"
#include "recording_parameters.h"
#include "play_state_machine.h"

extern uint8_t recordActive;
extern uint16_t playStepper;
extern uint16_t recordStepper;

extern uint16_t pressStamps[];
extern uint16_t releaseStamps[];

extern uint8_t pressStampIndex;
extern uint8_t releaseStampIndex;

extern uint16_t recordTimeoutCounter;

volatile uint16_t pauseAndPreambleCounter = PAUSE_DURATION;
volatile uint16_t preamblePulseCounter = PREAMBLE_PULSES;

interrupt void WDT_interval_handler(){
	static uint8_t playPhase;

	//===== PLAY MODE =====
	if ( recordActive == 0){
		switch (playPhase){
			case FIRST_PAUSE:{
				P1OUT &= ~RED;//might need to add green
				if( --pauseAndPreambleCounter == 0){
					playPhase = PREAMBLE;
					pauseAndPreambleCounter = PREAMBLE_PULSE_DURATION;
				}
				break;
			}
			case PREAMBLE:{
				if( --pauseAndPreambleCounter == 0){
					P1OUT ^= (RED + GREEN );
					pauseAndPreambleCounter = PREAMBLE_PULSE_DURATION;
					preamblePulseCounter--;
				}

				if( preamblePulseCounter == 0){
					playPhase = SECOND_PAUSE;
					P1OUT &= ~(RED + GREEN );
					pauseAndPreambleCounter = PAUSE_DURATION;
					preamblePulseCounter = PREAMBLE_PULSES;
				}
				break;
			}
			case SECOND_PAUSE:{
				if( --pauseAndPreambleCounter == 0){
					playPhase = PLAYBACK_ACTIVE;
					pauseAndPreambleCounter = PAUSE_DURATION;
				}
				break;
			}
			case PLAYBACK_ACTIVE:{
				if( ++playStepper == pressStamps[ pressStampIndex]){
					P1OUT |= RED;
					++pressStampIndex; //can combine with above if
				}
				else if( playStepper == releaseStamps[ releaseStampIndex]){
					P1OUT &= ~RED;
					++releaseStampIndex; //can combine with above if
				}
				//check for the end and loop the play cycle
				if( playStepper == RECORD_LENGTH){
					playPhase = FIRST_PAUSE;
					playStepper = 0;
					pressStampIndex = 0;
					releaseStampIndex =0;
				}
				break;
			}
		}
	}

	//=====IN RECORD MODE =====
	else if ( recordActive == 1){


		//=====HOW TO GET BACK TO PLAY=====
		if ( ++recordStepper >= RECORD_LENGTH){
			recordActive = 0;
			recordStepper = 0;
			playStepper = 0;
			P1OUT &= ~(GREEN+RED);

			pressStampIndex = 0;
			releaseStampIndex =0;

			playPhase = FIRST_PAUSE;
			pauseAndPreambleCounter = PAUSE_DURATION;

		}
	}

	//====== ENTER RECORD MODE (asynchronous)=====
	//======ONLY WAY TO GET INTO RECORD MODE=====
	if ( recordTimeoutCounter && (--recordTimeoutCounter == 0)){
		recordActive = 1;

		//need to reset the index's for the record
		pressStampIndex = 0;
		releaseStampIndex =0;

		//clear out the stamp array's to get ready for the next record
		uint8_t i = 0;
		for( i=0; i <= MAX_NUMBER_OF_PRESSES ; i++){
			pressStamps[ i ] = 0;
			releaseStamps[ i ] = 0;
		}

		P1OUT |= GREEN; //indicates that Record is active to user
		P1OUT &= ~RED;	//if RED by chance it was on; turn it off

		playStepper = 0;
	}

}

ISR_VECTOR( WDT_interval_handler, ".int10")

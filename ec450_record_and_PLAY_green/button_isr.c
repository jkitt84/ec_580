/*
 * button_isr.c
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */
#include <msp430g2553.h>
#include <stdint.h>
#include "button_isr.h"
#include "wdt_isr.h"
#include "io_wdt_initialization.h"
#include "recording_parameters.h"
#include "record_state_machine.h"

extern uint16_t pressStamps[];
extern uint16_t releaseStamps[];

extern uint16_t recordTimeoutCounter;

extern uint8_t buttonState;

extern uint8_t recordActive;
extern uint16_t recordStepper;

extern uint8_t pressStampIndex;
extern uint8_t releaseStampIndex;

//GPIO (button press P1.3) interrupt handler
interrupt void button_isr_handler(){

	switch (buttonState){
		case UP:{  //this case happens when the button is pressed
			recordTimeoutCounter = RECORD_TIMEOUT_LIMIT; //set it to max, the WDT will count it down

			if( (recordActive == 1) && (pressStampIndex <= MAX_NUMBER_OF_PRESSES)){
				pressStamps[ pressStampIndex] = recordStepper;
				pressStampIndex++;
			}
			P1OUT |= GREEN; //wed
			P1IES &= ~(BUTTON);
			buttonState = DOWN;
			break;
		}
		case DOWN:{ //this case happens when the button is released
			recordTimeoutCounter = 0; //set it to 0, the WDT should have already put in record mode if the hold was long enough

			if( (recordActive == 1) && (releaseStampIndex <= MAX_NUMBER_OF_PRESSES)){
				releaseStamps[ releaseStampIndex] = recordStepper;
				releaseStampIndex++;
			}
			P1OUT &= ~GREEN;//wed
			P1IES |= BUTTON;
			buttonState = UP;
			break;
		}
	}


	P1IFG &= ~BUTTON;
}
ISR_VECTOR( button_isr_handler, ".int02")

/*
 * play_state_machine.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */

#ifndef PLAY_STATE_MACHINE_H_
#define PLAY_STATE_MACHINE_H_

//possible states of the PLAY state machine
#define FIRST_PAUSE 0
#define PREAMBLE 1
#define SECOND_PAUSE 2
#define PLAYBACK_ACTIVE 3

//pause on either side of the preamble
#define PAUSE_DURATION 164

#define PREAMBLE_PULSES 20					//double the quantity of pulses in the preamble
#define PREAMBLE_PULSE_DURATION 9 			//duration (in WDT occurrences) of a half a preamble pulse

#endif /* PLAY_STATE_MACHINE_H_ */

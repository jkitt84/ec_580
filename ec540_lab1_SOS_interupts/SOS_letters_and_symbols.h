/*
 * SOS_letters_and_symbols.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Jeff
 */

#ifndef SOS_LETTERS_AND_SYMBOLS_H_
#define SOS_LETTERS_AND_SYMBOLS_H_


#define DOT 1
#define DASH 3
#define SYMBOLSEPERATOR 1
#define LETTERSEPERATOR 3
#define MESSAGESEPERATOR 7 	//i have this at 7 so the messages are distinct.  Technically to Professor sheet I think this
							//should be 4.  Because every letter terminates with a letter seperator (3) already.
							//I like it at 7 because the messages are more distinct.  Change to 4 if you wish.

//possible states of the state machine
#define FIRST_S 0
#define THE_O 1
#define SECOND_S 2
#define NOW_MS 3

//this are needed so they can be passed as arguments
const char firstS = FIRST_S;
const char theO = THE_O;
const char secondS = SECOND_S;
const char nowMS = NOW_MS;

//the symbol arrays
const char S[6] = { DOT, SYMBOLSEPERATOR, DOT, SYMBOLSEPERATOR, DOT, LETTERSEPERATOR };
const char Sstate[6] = { 1, 0, 1, 0, 1, 0};

const char O[6] = { DASH, SYMBOLSEPERATOR, DASH, SYMBOLSEPERATOR, DASH, LETTERSEPERATOR };
const char Ostate[6] = { 1, 0, 1, 0, 1, 0};

const char MS[1] = { MESSAGESEPERATOR };
const char MSstate[1] = {0};


#endif /* SOS_LETTERS_AND_SYMBOLS_H_ */

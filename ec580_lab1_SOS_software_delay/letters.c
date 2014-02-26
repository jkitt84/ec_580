/*
 * letters.c
 *
 *  Created on: Jan 28, 2014
 *      Author: Jeff
 */

#include "pulses.h"
#include "letters.h"
#include <stdint.h>

uint16_t S[6] = { DOT, LETTERSEPERATOR, DOT, LETTERSEPERATOR, DOT, WORDSEPERATOR };

uint16_t O[6] = { DASH, LETTERSEPERATOR, DASH, LETTERSEPERATOR, DASH, WORDSEPERATOR };

int spaceBetweenMessages = WORDSEPERATOR;

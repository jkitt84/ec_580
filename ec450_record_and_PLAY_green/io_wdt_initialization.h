/*
 * io_wdt_initialization.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */

#ifndef IO_WDT_INITIALIZATION_H_
#define IO_WDT_INITIALIZATION_H_

#define RED BIT0
#define GREEN BIT6
#define BUTTON BIT3

//set up the watch dog timer
void init_wdt();

//set up the general purpose input & output
void init_GPIO();


#endif /* IO_WDT_INITIALIZATION_H_ */

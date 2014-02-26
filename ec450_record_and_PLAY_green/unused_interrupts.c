/*
 * unused_interrupts.c
 *
 *  Created on: Feb 16, 2014
 *      Author: Jeff
 */
#include "unused_interrupts.h"
#include <msp430g2553.h>



interrupt void port2_isr_handler(){
	//do nothing
}
ISR_VECTOR( port2_isr_handler, ".int03")

interrupt void ADC10_isr_handler(){
	//do nothing
}
ISR_VECTOR( ADC10_isr_handler, ".int05")

interrupt void USCIAB0Tx_isr_handler(){
	//do nothing
}
ISR_VECTOR( USCIAB0Tx_isr_handler, ".int06")

interrupt void USCIAB0Rx_isr_handler(){
	//do nothing
}
ISR_VECTOR( USCIAB0Rx_isr_handler, ".int07")

interrupt void TIMER0_A1_isr_handler(){
	//do nothing
}
ISR_VECTOR( TIMER0_A1_isr_handler, ".int08")

interrupt void TIMER0_A0_isr_handler(){
	//do nothing
}
ISR_VECTOR( TIMER0_A0_isr_handler, ".int09")

interrupt void CompareA_isr_handler(){
	//do nothing
}
ISR_VECTOR( CompareA_isr_handler, ".int11")

interrupt void TIMER1_A1_isr_handler(){
	//do nothing
}
ISR_VECTOR( TIMER1_A1_isr_handler, ".int12")

interrupt void TIMER1_A0_isr_handler(){
	//do nothing
}
ISR_VECTOR( TIMER1_A0_isr_handler, ".int13")

interrupt void NMI_isr_handler(){
	//do nothing
}
ISR_VECTOR( NMI_isr_handler, ".int14")

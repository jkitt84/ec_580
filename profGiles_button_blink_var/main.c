#include <msp430g2553.h>

/* Constant Parameter */
#define SHORTFLASH 30
#define LONGFLASH 90
#define PRESS_TICKS 60

//Bitmasks for the output pins and button
#define GREEN BIT6
#define RED BIT0
#define BUTTON BIT3

/*Global Variables*/
unsigned char bstate;					//current button input state
unsigned int timeout_counter;			//down counter for the button timeout
unsigned char led_flash;				//flashing button bitmask
unsigned int flash_counter;				//down counter to the next flash
unsigned int current_flash_interval;	//flash interval

void init_gpio(){
	P1OUT &= ~(RED + GREEN);
	P1DIR |= (RED + GREEN);
	P1DIR &= ~BUTTON;
	P1REN |= BUTTON;
	P1IE |= BUTTON;
}

void init_wdt(){
	WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + 0 + BIT0;  //??might need to use 1 instead of bit0
	IE1 |= WDTIE; 						//enable the WDT in system interrupt register IE1
}

void reset_button_input_state(){
	bstate = 0;
	timeout_counter = 0;
	P1IES |= BUTTON;			//set to interrupt on down going edge
	P1IFG &= ~BUTTON;			//clear the interrupt flag
}

void flash_green_slowly(){
	led_flash = GREEN;
	current_flash_interval = LONGFLASH;
	flash_counter = current_flash_interval;
	P1OUT &= ~(RED + GREEN); 	//LEDs both off
}

void flash_red_rapidly(){
	led_flash = RED;
	current_flash_interval = SHORTFLASH;
	flash_counter = current_flash_interval;
	P1OUT &= ~(GREEN);
}

void flash_alternate_rapidly(){
	led_flash = RED + GREEN;
	led_flash = RED + GREEN;
	current_flash_interval = SHORTFLASH;
	flash_counter = current_flash_interval;
	P1OUT |= GREEN;				//might have to do this verbatim
	P1OUT &= ~RED;
}

interrupt void button_handler(){
	switch (bstate){
		case 0:{					//was in initial state, called because of falling edge
			bstate = 1;				//next state for the button interrupt
			P1IES &= ~BUTTON; 		//set to trigger next rising edge
			timeout_counter = PRESS_TICKS;	//activate WDT run timeout mechanism
			break;
		}
		case 1:{
			bstate = 2;
			P1IES |= BUTTON;		//look for falling edge (possible double press)
			timeout_counter = PRESS_TICKS;	//activate WDT run timeout mechanism
			break;
		}
		case 2:{
			bstate = 3;
			P1IES &= ~BUTTON;		//look for the rising edge
			timeout_counter = PRESS_TICKS;	//activate WDT run timeout mechanism
			break;
		}
		case 3:{ //just caught the end of a double press, Respond to it!!!!
			flash_alternate_rapidly();	//flash both LEDs
			reset_button_input_state();
			break;
		}
	}
	P1IFG &= ~BUTTON;	//reset the gpio interrupt flag for the button pin!
}
//declare function button_handler as handler for interrupt 10
//using a macro defined in the msp430g2553.h include file
ISR_VECTOR(button_handler,".int02")

//====Button Timeout Action (procedure called by WDT handler after timeout ========
void timeout_action(){
	switch (bstate){
		case 1: 			//it is action the same way as the 3
		case 3:{
			flash_green_slowly();
			break;
		}
		case 2: {			//timeout waiting for start of second press ++> single short press
			flash_red_rapidly();
			break;
		}
	}//ALWAYS reset the button system
	reset_button_input_state();
}

//===== Watch dog Timer Interupt Handler =====
//This event handler is callled to handle the watch dog timer ipterrupts
//which occur regularly at intervals of about 8K/1MHz = 8.192mS
interrupt void WDT_interval_handler(){
	/*Flash Action*/
	if (--flash_counter == 0){  //decrement flash_counter
		P1OUT ^= led_flash; 	//toggle on or more of the LEDs
		flash_counter = current_flash_interval;
	}
	//???try to make this less confusing
	if ( timeout_counter && (--timeout_counter == 0)){
		timeout_action();
	}
}
//DECLARE function WDT_interval_handler as a handler for interrupt 10
//using a macro define in the msp430g2553.h include file
ISR_VECTOR(WDT_interval_handler,".int10")

void main( void){
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	
	init_wdt();
	init_gpio();
	flash_green_slowly();
	reset_button_input_state();
	_bis_SR_register( GIE + LPM0_bits);
}

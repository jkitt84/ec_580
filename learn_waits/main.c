#include  <msp430g2553.h>

unsigned int i = 0;           // Initialize variables. This will keep count of how many cycles between LED toggles

void dummyWait( int waitValue);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;

  P1DIR |= 0x01;               // P1DIR is a register that configures the direction (DIR) of a port pin as an output or an input.


  for (;;)                     // This empty for-loop will cause the lines of code within to loop infinitely
  {



    P1OUT ^= 0x01;
    //for(i=0; i< 20000; i++);
    dummyWait( 4);
  }
}

void dummyWait( int waitValue){
	volatile int x;
	volatile int y;
	for( x=0; x< waitValue; x++)
		for ( y=0; y< 5000; y++)
			;								//do nothing on the inner loop
		;									//do nothing on the outer loop

}

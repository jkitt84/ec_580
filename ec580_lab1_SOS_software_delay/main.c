#include <msp430g2553.h>
#include <intrinsics.h>

unsigned int i = 0;           // Initialize variables. This will keep count of how many cycles between LED toggles


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer

  P1DIR |= 0x01;               // P1DIR is a register that configures the direction (DIR) of a port pin as an output or an input.

                               // P1DIR = 0x01     <-- this is the hexadecimal conversion of 0000 0001



  for (;;)                     // This empty for-loop will cause the lines of code within to loop infinitely
  {



    P1OUT ^= 0x01;             // Toggle P1.0 using exclusive-OR operation (^=)

                               // P1OUT is another register which holds the status of the LED.
                               // '1' specifies that it's ON or HIGH, while '0' specifies that it's OFF or LOW
                               // Since our LED is tied to P1.0, we will toggle the 0 bit of the P1OUT register



    for(i=0; i< 20000; i++);   // Delay between LED toggles. This for-loop will run until the condition is met.
                               //In this case, it will loop until the variable i increments to 20000.
  }
}

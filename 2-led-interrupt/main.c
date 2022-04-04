//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include <stdio.h>

int sel;

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */

  char c;
  do {
    printf("Type 'r' to turn on red LED, 'g' for green LED, or 'b' for both LEDs\n");
    switch (c = getchar()) {
    case 'r':
      sel = LED_RED;
      break;
    case 'g':
      sel = LED_GREEN;
      break;
    case 'b':
      sel = LEDS;
      break;
    default:
      printf("Not a valid selection\n");
      sel = 0;
    }
  } while (sel == 0);

  or_sr(0x18);		/* CPU off, GIE on */
}


void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  P1OUT ^= sel;
} 


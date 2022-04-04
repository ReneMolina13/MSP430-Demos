//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include <stdio.h>

int main(void) {
  char c;
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
  printf("Type 'r' to turn on red led, 'g' to turn on green led, ");
  printf("'b' to turn on both leds, and 'o' to turn off leds\n");

  while (1)
    switch(c = getchar()) {
    case 'r':
      P1OUT = LED_RED;
      break;
    case 'g':
      P1OUT = LED_GREEN;
      break;
    case 'b':
      P1OUT = LEDS;
      break;
    case 'o':
      P1OUT = 0;
      break;
    default:
      printf("Not a valid option\n");
  }
  or_sr(0x18);		/* CPU off, GIE on */
}

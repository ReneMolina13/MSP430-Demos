//Alternate LEDs from Off, Green, and Red
#include <stdio.h>
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int blink;

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */

  char c;
  do {
    printf("Select how quickly the LEDs blink: 'f' = fast, 'm' = medium, 's' = slow\n");
    switch (c = getchar()) {
    case 'f':
      blink = 125;
      break;
    case 'm':
      blink = 250;
      break;
    case 's':
      blink = 500;
      break;
    default:
      printf("Not a valid selection\n");
      blink = 0;
    }
  } while (blink == 0);

  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars to count time and alternate LEDs
volatile int secondCount = 0;
volatile int selectLED = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount >= blink) { 	/* once each sec... */
    secondCount = 0;		/* reset count */
    if (selectLED == 0) {
      selectLED = 1;
      P1OUT ^= LED_RED;         /* toggle red LED */
    }
    else {
      selectLED = 0;
      P1OUT ^= LED_GREEN;	/* toggle green LED */
    }
  }
} 


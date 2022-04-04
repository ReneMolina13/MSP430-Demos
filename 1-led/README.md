## Description
This program turns on the red led

Be sure to understand the manipulation of P1OUT and P1DIR.

## Suggested Activities

* Modify so that different combinations of LEDs are illuminated.

* Determine the impact of not setting one of the LED bits in P1DIR (and why).

Not setting one of the LED bits in P1DIR makes it so the direction of that pin
becomes whatever it was previously set to. This could lead to the currect pin
direction but it also may not.

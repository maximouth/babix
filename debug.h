/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/** Turn the LED wired to pin 13 on by directly addressing its register.
    See SAM3x8E datasheet 32.7.10 page 660. */
#define LED_PIN13_SEND_HIGH (REG_PIOB_SODR = 0x1 << 27)


/** Turn the LED wired to pin 13 off by directly addressing its register.
    See SAM3x8E datasheet 32.7.11 page 661. */
#define LED_PIN13_SEND_LOW (REG_PIOB_CODR = 0x1 << 27)
#endif

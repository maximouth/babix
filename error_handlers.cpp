/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#include <Arduino.h>
#include "context.h"

extern "C" { /* Start of extern "C" for redefinition of weak functions. */

/** Some handlers for the error exceptions. May mostly print nothing in case
    of severe error since the CPU will have turned nut :/
    May be the onboard LED blinking at different speeds depending on the
    error would be a better idea. */
void HardFault_Handler ()
{
  Serial.print ("Hard Fault: ") ;
  Serial.println (*((mcu_word_t*)0x02C), BIN) ;
}

void MemManage_Handler () { Serial.println ("MemManage") ; }

void BusFault_Handler () { Serial.println ("Bus Fault") ; }

void UsageFault_Handler () { Serial.println ("Usage Fault") ; }

void DebugMon_Handler () { Serial.println ("DebugMon") ; }

} /* End of extern "C" redefinition of weak functions. */

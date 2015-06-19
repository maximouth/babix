
/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  François Pessaux 04/2015.
  This code can be freely distributed.
*/
// #define SERIAL_PRINT

#include <Arduino.h>
#include "kernel.h"
#include "context.h"
#include "process.h"
#include "mutex.h"
#include "user_tasks.h"
#include <LiquidCrystal.h>


void setup ()
{
#ifdef SERIAL_PRINT
  Serial.begin (9600) ;     /* Enable serial printing. */
#endif
setup_lcd();
  pinMode (13, OUTPUT) ;    /* Set onboard LED as an output. */
  digitalWrite (13, LOW) ;  /* Turn is low. */
 
  /* Create some processes. */

#ifdef SERIAL_PRINT
  Serial.println ("Creating process #0") ;
#endif
  create_process (process0) ;

#ifdef SERIAL_PRINT
  Serial.println ("Creating process #1") ;
#endif
  create_process (process1) ;

#ifdef SERIAL_PRINT
  Serial.println ("Creating process #2") ;
#endif
  create_process (process2) ;

#ifdef SERIAL_PRINT
    Serial.println ("Creating process #3") ;
#endif
  create_process (process3) ;
   
  /* Set interrupts to be preemptive. Change the grouping to set no
     sub-priority.
     See SAM3x8E datasheet 12.6.6 page 84 and 12.21.6.1 page 177. */
  NVIC_SetPriorityGrouping (0b011) ;
  /* Configure the system tick frequency to adjust the time quantum allocated
     to processes. */
  SysTick_Config (SystemCoreClock / SYSTICK_FREQUENCY_HZ) ;
  /* Set the base priority register to 0 to allow any exception to be
     handled.
     See SAM3x8E datasheet 12.4.3.14 page 62. */
  __set_BASEPRI (0) ;
  /* Force the PendSV exception to have the lowest priority to avoid killing
     other interrupts.
     See SAM3x8E datasheet 12.20.10.1 page 168. */
  NVIC_SetPriority (PendSV_IRQn, 0xFF) ;
  /* NVIC_EnableIRQ (SVCall_IRQn) ;  Seems useless O_o */


}



uint32_t dummy_counter = 0 ;

/** Main process. Will only be executed if no more processes are running. */
void loop ()
{
  delay (500) ;
  dummy_counter++ ;
//lcd.print("Mainprocess");
#ifdef SERIAL_PRINT
  Serial.print ("Main process: ") ;
  Serial.println (dummy_counter) ;
#endif
}

/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  François Pessaux 04/2015.
  This code can be freely distributed.
*/

#include <Arduino.h>
#include "kernel.h"
#include "context.h"
#include "process.h"
#include "mutex.h"

//  asm volatile ("\n\t");
int cpt = 0;


void toto(int t) {
  takeU();
 
  int x = cpt;
  delay (t);
  x ++;
  cpt = x;
  // Serial.print(t);
  Serial.println(cpt);
  
  return;

  freeU();
}


/** Some examples of user processes. */
void process0 () { for (;;) { 
    toto(500);
  }
}
void process1 () { for (;;) { 
    toto (250);
  }
}
void process2 () { for (;;) {
    toto (780);
  }
}
void process3 () {
  for (;;) {
    Serial.println ("HIGH") ;
    digitalWrite (13, HIGH) ;
    delay (1000) ;
    Serial.println ("LOW") ;
    digitalWrite (13, LOW) ;
    delay (1000) ;
  }
}


void setup ()
{
  Serial.begin (9600) ;     /* Enable serial printing. */
  pinMode (13, OUTPUT) ;    /* Set onboard LED as an output. */
  digitalWrite (13, LOW) ;  /* Turn is low. */

 
  /* Create some processes. */
  Serial.println ("Creating process #0") ;
  create_process (process0) ;
  Serial.println ("Creating process #1") ;
  create_process (process1) ;
  Serial.println ("Creating process #2") ;
  create_process (process2) ;
  Serial.println ("Creating process #3") ;
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
  Serial.print ("Main process: ") ;
  Serial.println (dummy_counter) ;
}

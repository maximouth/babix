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
#include <LiquidCrystal.h>

// pin for the lcd screen
#define RS (49)
#define E  (45)
#define D0 (44)
#define D1 (43)
#define D2 (42)
#define D3 (41)
#define D4 (40)
#define D5 (39)
#define D6 (38)
#define D7 (37)

// lcd screen object
LiquidCrystal lcd (RS,E,D0,D1,D2,D3,D4,D5,D6,D7);

// global variable, nearly all the process modify it
volatile uint32_t cpt = 0 ;
/* The lock to protect the shared variable. 0 == free, 1 == taken. */
static uint32_t mutex = 0;

// the critical section
// read cpt, wait, cpt = cpt + 1, print cpt
// t is the time to wait in the funtion
void concurrent_increment (int t)
{
  int x ;

  /* Claim the lock to prevent several processes from modifying the kernel
     tables concurrently if they attempt to create processes "at the same
     time". */
  mutex_acquire (&mutex) ;

#ifdef SERIAL_DEBUG
  Serial.println(mutex);
#endif
  
  // read cpt and place it into x
  x = cpt;
  //wait t ms
  delay(t);
  // increment cpt
  cpt = x+1;

#ifdef SERIAL_DEBUG
  Serial.println(cpt);
#endif
  //print cpt on the second raw
  lcd.setCursor (0,1) ;
  lcd.print (cpt) ;
  
  /* Release the mutex to leave the critical section. */
  mutex_release (&mutex) ;

#ifdef SERIAL_DEBUG
  Serial.println(mutex);
#endif

  return ;
}


/** Some examples of user processes. */

void process0 () {
  for (;;) {
#ifdef SERIAL_DEBUG
    Serial.print("I'm 1 ") ;
#endif 
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('1');
    concurrent_increment(15);
    delay(70);
  }
}
void process1 () { 
    for (;;) { 
#ifdef SERIAL_DEBUG
    Serial.print("I'm 2 ") ;
#endif
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('2');
    concurrent_increment (99);
    delay(470);
  }
}
void process2 () { 
      for (;;) {
#ifdef SERIAL_DEBUG
    Serial.print("I'm 3 ")
#endif
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('3');
    concurrent_increment (24) ;
    delay(3700);
  }
}
void process3 () {
  for (;;) {
#ifdef SERIAL_DEBUG
    Serial.println ("HIGH") ;
#endif
    digitalWrite (13, HIGH) ;
    delay (1000) ;
#ifdef SERIAL_DEBUG
    Serial.println ("LOW") ;
#endif
    digitalWrite (13, LOW) ;
    delay (1000) ;
  }
}


void setup ()
{
#ifdef SERIAL_DEBUG
  Serial.begin (9600) ;     /* Enable serial printing. */
#endif
  lcd.begin(16,2);          /* Enable lcd screen ( 16 char per row, 2 rows )*/
  lcd.clear();              /* clear the possible previous thing on the screen*/
  pinMode (13, OUTPUT) ;    /* Set onboard LED as an output. */
  digitalWrite (13, LOW) ;  /* Turn is low. */
 
  /* Create some processes. */

#ifdef SERIAL_DEBUG
  Serial.println ("Creating process #0") ;
#endif
  create_process (process0) ;

#ifdef SERIAL_DEBUG
  Serial.println ("Creating process #1") ;
#endif
  create_process (process1) ;

#ifdef SERIAL_DEBUG
  Serial.println ("Creating process #2") ;
#endif
  create_process (process2) ;

#ifdef SERIAL_DEBUG
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
  lcd.print("Mainprocess");
#ifdef SERIAL_DEBUG
  Serial.print ("Main process: ") ;
  Serial.println (dummy_counter) ;
#endif
}

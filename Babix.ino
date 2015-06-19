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

LiquidCrystal lcd (49,45,44,43,42,41,40,39,38,37);


//  asm volatile ("\n\t");
volatile uint32_t cpt = 0;
uint32_t mutex = 0;


void toto (int t) {
  int x ;
  int i = 0 ;
  takeM(&mutex);
  //  Serial.println(mutex);
  x = cpt;
  for (i = 0; i < t; i++ ) asm volatile (".daube: nop  \n\t") ;
  delay(50);
  
  cpt = x+1;
  //Serial.println(cpt);
  //
  //lcd.clear();
  lcd.setCursor (0,1) ;
  lcd.print (cpt) ;
  
  freeM (&mutex) ;
  //Serial.println(mutex);
  return;
}





/** Some examples of user processes. */
void process0 () {
  for (;;) {
    //Serial.print("I'm 1 ") ;
    lcd.setCursor(0,0);
    lcd.print('1');
    //lcd.clear(); 
    //set cursor
  //        lcd.write8bits(0x80 | ( 1+ 0x00));
    toto(10500);
    delay(70);
  }
}
void process1 () { for (;;) { 
    //Serial.print("I'm 2 ") ;
    lcd.setCursor(0,0);
    lcd.print('2');
    //lcd.clear();  
//  lcd.write8bits(0x80 | ( 1+ 0x00));
    toto (990);
    delay(470);
  }
}
void process2 () { for (;;) {
    //Serial.print("I'm 3 ")
    lcd.setCursor(0,0);
    lcd.print('3');
    //lcd.clear();
//    lcd.write8bits(0x80 | ( 1+ 0x00));
    toto (1224);
    delay(3700);
  }
}
void process3 () {
  for (;;) {
    //Serial.println ("HIGH") ;
    digitalWrite (13, HIGH) ;
    //lcd.clear();
    delay (1000) ;
    //Serial.println ("LOW") ;
    digitalWrite (13, LOW) ;
    delay (1000) ;
  }
}


void setup ()
{
#ifdef SERIAL_DEBUG
  Serial.begin (9600) ;     /* Enable serial printing. */
#endif
  lcd.begin(16,2);  
  lcd.clear();
  pinMode (13, OUTPUT) ;    /* Set onboard LED as an output. */
  digitalWrite (13, LOW) ;  /* Turn is low. */
  //lcd.autoscroll();
 
  /* Create some processes. */
  asm volatile ("pop { r2, r3 }  \n\t") ;
#ifdef SERIAL_DEBUG
  //Serial.println ("Creating process #0") ;
#endif
  // lcd.print("CRT #0");
  create_process (process0) ;
  //  lcd.print("suite");
  //lcd.setCursor(0,0);
  //lcd.print("CRT #1");
#ifdef SERIAL_DEBUG
  //Serial.println ("Creating process #1") ;
#endif
  create_process (process1) ;

#ifdef SERIAL_DEBUG
  //Serial.println ("Creating process #2") ;
#endif
  create_process (process2) ;

#ifdef SERIAL_DEBUG
  //  Serial.println ("Creating process #3") ;
#endif
  create_process (process3) ;
  //lcd.clear();
  
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

  //lcd.clear();

}



uint32_t dummy_counter = 0 ;
/** Main process. Will only be executed if no more processes are running. */
void loop ()
{
  delay (500) ;
  dummy_counter++ ;
  lcd.print("Mainprocess");
#ifdef SERIAL_DEBUG
// Serial.print ("Main process: ") ;
//Serial.println (dummy_counter) ;
#endif
}

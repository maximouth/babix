#include "user_tasks.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "kernel.h"
#include "mutex.h"
#include "semaphore.h"
#include "process.h"

//#define SERIAL_DEBUG

// lcd screen object
LiquidCrystal lcd (RS,E,D0,D1,D2,D3,D4,D5,D6,D7);

void setup_lcd() {
  lcd.begin(16,2);          /* Enable lcd screen ( 16 char per row, 2 rows )*/
  lcd.clear();              /* clear the possible previous thing on the screen*/
}

/** Global variable to increment concurrently by several processes. */
volatile uint32_t cpt = 0 ;
/** The lock to protect the shared variable. 0 == free, 1 == taken. */
static mutex_t mutex = 0 ;

// the critical section
// read cpt, wait, cpt = cpt + 1, print cpt
// t is the time to wait in the funtion
void concurrent_increment (int t)
{
  int tmp ;

  /* Claim the lock to prevent several processes from modifying the kernel
     tables concurrently if they attempt to create processes "at the same
     time". */
  mutex_acquire (&mutex) ;
  
  //sem_acquire(0);


#ifdef SERIAL_DEBUG
  Serial.println (mutex) ;
#endif
  
  // read cpt and place it into x
  tmp = cpt;
  //wait t ms
  delay(t);
  // increment cpt
  cpt = tmp + 1 ;

#ifdef SERIAL_DEBUG
  Serial.println (cpt) ;
#endif
  //print cpt on the second raw
  //lcd.clear();
  lcd.setCursor (0, 1) ;
  lcd.print (cpt) ;
  
  /* Release the mutex to leave the critical section. */
  mutex_release (&mutex) ;
  //sem_release(0);


#ifdef SERIAL_DEBUG
  Serial.println (mutex) ;
#endif
  return ;
}


/** Some examples of user processes. */

void process1 ()
{
 int i = 0 ;
   for (i = 0;i < 20 ; i ++) {
 //  for(;;) {
#ifdef SERIAL_DEBUG
    Serial.print("I'm 1 ") ;
#endif 
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('1');
    concurrent_increment(15);
    delay(70);
  }
  lcd.print("  fin 1" );
    end_process ();
}

void process2 ()
{ 
  int i = 0 ;
   for (i = 0;i < 30;i ++) { 
  // for(;;) {
#ifdef SERIAL_DEBUG
    Serial.print("I'm 2 ") ;
#endif
    Serial.println(kernel.main_task_sp, HEX);
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('2');
    concurrent_increment (99);
    delay(770);
  }
  lcd.print("  fin 2" );
  end_process ();
}

void process3 ()
{ 
  int i = 0;
  for (i = 0;i < 8; i ++) {
  //for(;;) {
#ifdef SERIAL_DEBUG
    Serial.print("I'm 3 ") ;
#endif
    //print on the first raw
    lcd.setCursor(0,0);
    lcd.print('3');
    concurrent_increment (24) ;
    delay(1000);
  }
  lcd.print("  fin 3" );
  end_process();
}

void process4 ()
{
  int i = 0;
  for (i = 0;i < 9; i ++) {
    //for(;;) {
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
  lcd.print("  fin 4" );
  end_process();
}

/***
 Print on the lcd, it is use in the main loop.
 ***/
void lcdMain(int cpt) {
  lcd.setCursor (0,0);
  lcd.print("Main proccess ");
  lcd.setCursor (0,1);
  lcd.print(cpt);
}

/***
    Print the value passed in argument, use for debug in semaphore.cpp
 ***/
void lcdDebug(int val) {
  lcd.setCursor (3,0);
  lcd.print(val);
  return;
}


void lcd_crnb() {
  lcd.setCursor(5, 0);
  lcd.print(kernel.queue.cur_nb);
}

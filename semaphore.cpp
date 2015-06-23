
#include <Arduino.h>
#include "user_tasks.h"

#ifdef DEBUG
static volatile uint32_t DebugSem = 0;
#endif

static volatile uint32_t S[5] = {0,0,0,0,0};

/* Initialise the semaphore number "num" to the value "val". */
void sem_init (int num, int val)
 {
  S[num] = val;
  return;
}


/***
    Attempt to acquire one of the lock. This function used the number of the 
    lock you are going to use as argument
 ***/
void sem_acquire (int num)
{
/*  No need to save the registers used in this function. In effect, we only
    use scratch registers r1 and r2. Gcc seems to store our argument in r0
    which is also a scratch register. */

/* The label. */
 sem:
  /* Ask an exclusive access on the lock and get its value by the way
     (c.f. datasheet section 12.5.7 page 78 and section 12.12.8 page 112.  */
  asm volatile ("ldrex r1, [%0]   \n\t" :: "r" (&S[num]) : "r1", "memory") ;

#ifdef DEBUG
  /* If you want to print the lock value use one the this.
     We need to save the used register before calling a function. */
  asm volatile ("push {r1, r0 }  \n\t") ;
  /* 
     //Print on the serial port.
     asm volatile ("mov %0, r1 \n\t" : "=r" (DebugSem) :: "memory" ) ;
     Serial.print ("S ") ;
     Serial.println (DebugSem) ;
  */
  // print on the lcd screen.
  lcdDebug(S[0]);
  asm volatile ("pop {r1, r0 }  \n\t") ;
#endif

  /* Check the value of the lock. If it is full (==0) we must retry.  */
  asm volatile ("mov r2, #0  \n\t" ::: "r2") ;
  asm volatile ("cmp r2, r1  \n\t") ;
  /* Attention: must use an asm goto to make sure that gcc will know that 
     we need to go back and re exec the previous code, to avoid register 
     problem.
     If you are not going to use that, gcc will not kown that a label exist,
     and  you can kill the register with the lock address.
 */
  asm volatile goto ("beq %0   \n\t" :::: sem) ;  /* Loop back. */

  /* Lock is not == 0, hence is not full. Let's try to acquire it and 
     decrement it's value. */
  asm volatile ("sub r1, r1, #1  \n\t" ::: "r1") ;
  /* And stock it in the right lock */
  asm volatile ("strex r2, r1, [%0]  \n\t" :: "r" (&S[num]) : "r2", "memory") ;

  /*  Check return value: if 0 write succeeded otherwise failure. In case of
      failure we must retry the whole process (i.e. reading the lock's value
      and if possible trying to write 1 inside. */
  asm volatile ("mov r1, #1  \n\t" ::: "r1") ;
  asm volatile ("cmp r2, r1      \n\t") ;
  asm volatile goto ("beq %0   \n\t" :::: sem) ;  /* Loop back. */

  return ;

}

/***
    Release one lock whose number is passed as argument.
    Typically, this is to call after the critical section.
***/
void sem_release (int num) 
{
  S[num] += 1 ;
}

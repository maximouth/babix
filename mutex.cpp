/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  François Pessaux 04/2015.
  Maxime Ayrault 19/06/2015.
  This code can be freely distributed.
*/

#include <Arduino.h>
#include "mutex.h"


/**
  Attempt to acquire the lock. This function used the lock whose address is
  provided as argument.
*/
void mutex_acquire (mutex_t *mutex)
{
  /* No need to save the registers used in this function. In effect, we only
     use scratch registers r2 and r3. Gcc seems to store our argument in r0
     which is also a scratch register. */
  asm volatile (".take:           \n\t") ;
  /* Ask an exclusive access on the lock and get its value by the way
     (c.f. datasheet section 12.5.7 page 78 and section 12.12.8 page 112. */
  asm volatile ("ldrex r3, [%0]   \n\t" :: "r" (mutex) : "memory") ;
  /* Check the value of the lock. If it is taken (==1) we must retry. */
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3  \n\t") ;
  asm volatile ("beq .take   \n\t") ;  /* Loop back. */
  
  /* Lock is not == 1, hence is free. Let's try to acquire it by trying
     storing 1 inside. 
     Not-success value returned value in r3.
     Value to store in r2 (i.e. value 1).
     Address of the lock is 'mutex'. */
  asm volatile ("strex r3, r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  
  /* Check return value: if 0 write succeeded otherwise failure. In case of
     failure we must retry the whole process (i.e. reading the lock's value
     and if possible trying to write 1 inside. */
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3      \n\t") ;
  asm volatile ("beq .take       \n\t") ;  /* Failure: loop back. */
  return ;
}



/** Release the lock whose adress is passed as argument.
    Typically, this is to call after the critical section. */
void mutex_release (mutex_t *mutex)
{
  /* No need to save the register, we use a scratch register. */
  asm volatile ("mov r2, #0    \n\t") ;
  asm volatile ("str r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  return ;
}

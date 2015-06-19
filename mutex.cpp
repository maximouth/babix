#include <Arduino.h>
#include "mutex.h"

int Debug = 1;


/**
  Attempt to acquire the lock. This function used the lock whose address is
  provided as argument.
*/
void takeM (volatile uint32_t *mutex)
{
  /* No need to save the registers used in this function. In effect, we only
     use scratch registers r2 and r3. Gcc seems to store our argument in r0
     which is also a scratch register. */
  // int daube ;
  asm volatile (".take:           \n\t") ;
  
  /* DEBUG
     read the mutex value before load
     asm volatile ("ldrex %0, [%1]   \n\t" : "=r" (daube): "r" (mutex) : "memory");
     Serial.print ("Daube ") ; Serial.println (daube) ;
  */

  /* Ask an exclusive access on the lock and get its value by the way
     (c.f. datasheet section 12.5.7 page 78 and section 12.12.8 page 112. */
  asm volatile ("ldrex r3, [%0]   \n\t" :: "r" (mutex) : "memory") ;
 
  /* DEBUG
     read the mutex value after load
     asm volatile ("mov %0, r3 \n\t" : "+r" (Debug)) ;
     Serial.print ("D ") ;
     Serial.println (Debug) ;
  */

  // check the value
  // if it is taken (==1) re start the function
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3  \n\t") ;
  asm volatile ("beq .take   \n\t") ;
  
  //if not, try to take the lock
  //return value in r3
  //value to store in r2 (1)
  //and the adress of the lock
  asm volatile ("strex r3, r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  
  //check return value
  // if 0 done
  // if 1 fail and re stat the function
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3      \n\t") ;
  asm volatile ("beq .take       \n\t") ;
  return ;
}


// free the lock (to call after the critical section)
// no need to save the register, we use a scratch register
void freeM (volatile uint32_t *mutex)
{
  asm volatile ("mov r2, #0    \n\t") ;
  asm volatile ("str r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  return ;
}

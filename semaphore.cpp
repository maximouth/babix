
#include <Arduino.h>
#include "user_tasks.h"

#ifdef DEBUG
static volatile uint32_t DebugSem = 70;
#endif

static volatile uint32_t S[5] = {0,0,0,0,0};

/*initialise le semaphore numero "num" à la valeur "val"  */
void sem_init (int num, int val) {
  S[num] = val;
  return;
}

void sem_acquire (int num)
{
 sem:
  //valeur du semaphore dans r3
  asm volatile ("ldrex r1, [%0]   \n\t" :: "r" (&S[num]) : "r1", "memory") ;

  /*
#ifdef DEBUG
  asm volatile ("push {r1, r0 }  \n\t");
  // asm volatile ("mov %0, r1 \n\t" : "=r" (DebugSem) :: "memory" );
  // Serial.print("S ");
  // Serial.println(DebugSem);
  //lcdDebug(S[0]);
  asm volatile ("pop {r1, r0 }  \n\t");
#endif
  */

  /* test si le semaphore est plein ou non (==0 plein) (superieur vide)   */
  asm volatile ("mov r2, #0  \n\t" ::: "r2") ;
  asm volatile ("cmp r2, r1  \n\t") ;
  /* Attention: must use an asm goto to make sure that gcc. */
  asm volatile goto ("beq %0   \n\t" :::: sem) ;  /* Loop back. */

 /* si non plein decrementer la valeur du semaphore  */
  asm volatile ("sub r1, r1, #1  \n\t" ::: "r1") ;
  /* et stocker ca dans le bon semaphore  */
  asm volatile ("strex r2, r1, [%0]  \n\t" :: "r" (&S[num]) : "r2", "memory") ;

  /* tester si la valeur à bien été ecrite  */
  asm volatile ("mov r1, #1  \n\t" ::: "r1") ;
  asm volatile ("cmp r2, r1      \n\t") ;

  asm volatile goto ("beq %0   \n\t" :::: sem) ;  /* Loop back. */

  return ;

}


void sem_release (int num) {

  S[num] += 1 ;

}

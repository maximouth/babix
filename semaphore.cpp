
#include <Arduino.h>

int S[5] = {0,0,0,0,0};

/*initialise le semaphore numero "num" à la valeur "val"  */
void init (int num, int val) {
  S[num] = val;
  return;;
}

void sem_acquire (int num) {

  asm volatile (".sem:           \n\t") ;

  //valeur du semaphore dans r3
  asm volatile ("ldrex r3, [%0]   \n\t" :: "r" (&S[num]) : "memory") ;
  
  /* test si le semaphore est plein ou non (==0 plein) (superieur vide)   */
  asm volatile ("mov r2, #0  \n\t") ;
  asm volatile ("cmp r2, r3  \n\t") ;
  asm volatile ("beq .sem   \n\t") ;  /* Loop back. */
  
  /* si non plein decrementer la valeur du semaphore  */
  asm volatile ("add r3, #-1  \n\t") ;
  /* et stocker ca dans le bon semaphore  */
  asm volatile ("strex r2, r3, [%0]  \n\t" :: "r" (&S[num]) : "memory") ;

  /* tester si la valeur à bien été ecrite  */
  asm volatile ("mov r1, #1  \n\t") ;
  asm volatile ("cmp r2, r1      \n\t") ;
  asm volatile ("beq .take       \n\t") ;  /* Failure: loop back. */
  return ;

}


void sem_release (int num) {

  S[num] = S[num] + 1;
}

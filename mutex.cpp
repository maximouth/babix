#include <Arduino.h>
#include "mutex.h"

int Debug = 1;


//essayer de prendre le mutex, fini quand on l'obtient
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
  //lire la valeur du mutex
  /* DEBUG
  asm volatile ("ldrex %0, [%1]   \n\t" : "=r" (daube): "r" (mutex) : "memory");
  Serial.print ("Daube ") ; Serial.println (daube) ;
  */
  /* Ask an exclusive access on the lock and get its value by the way
     (c.f. datasheet section 12.5.7 page 78 and section 12.12.8 page 112. */
  asm volatile ("ldrex r3, [%0]   \n\t" :: "r" (mutex) : "memory") ;
  /* DEBUG
     asm volatile ("mov %0, r3 \n\t" : "+r" (Debug)) ;
     Serial.print ("D ") ;
     Serial.println (Debug) ;
  */

  //regarder sa valeur
  // si prise(==1) recommencer la fonction
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3  \n\t") ;
  asm volatile ("beq .take   \n\t") ;
  
  //sinon essayer de prendre le verrou
  //valeur retour dans R0 tester avec la valeur prise dans R1, a l'adresse du
  //mutex
  asm volatile ("strex r3, r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  
  //regarder si la valeur de retour est bonne ou pas
  // 0 reussite 1 fail
  // Si non retourner au debut
  asm volatile ("mov r2, #1  \n\t") ;
  asm volatile ("cmp r2, r3      \n\t") ;
  asm volatile ("beq .take       \n\t") ;
  return ;
}


// libere le mutex (à appeller à la fin de la section critique)
void freeM (volatile uint32_t *mutex)
{
  asm volatile ("push { r2 }   \n\t") ;
  asm volatile ("mov r2, #0    \n\t") ;
  asm volatile ("str r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;
  asm volatile ("pop { r2 }    \n\t") ;
  return ;
}

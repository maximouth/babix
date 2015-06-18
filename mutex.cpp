#include <Arduino.h>
#include "mutex.h"
//  Serial.println("");

int Debug = 1;


//essayer de prendre le mutex, fini quand on l'obtient
void takeM (int *mutex)
{
  // int daube ;
  asm volatile (".take:           \n\t");
  asm volatile ("push { r2, r5 }  \n\t") ;
  //lire la valeur du mutex
  /*
  asm volatile ("ldrex %0, [%1]   \n\t" : "=r" (daube): "r" (mutex) : "memory");
  Serial.print ("Daube ") ; Serial.println (daube) ;
  */

  asm volatile ("ldrex r5, [%0]   \n\t" :: "r" (mutex) : "memory");
  /* Debug
     asm volatile ("mov %0, r5 \n\t" : "+r" (Debug));
     Serial.print("D ");
     Serial.println(Debug);
  */

  //regarder sa valeur
  // si prise(==1) recommencer la fonction
  asm volatile ("mov r2, #1  \n\t");
  asm volatile ("cmp r2, r5  \n\t");
  asm volatile ("beq .take   \n\t");
  
  //sinon essayer de prendre le verrou
  //valeur retour dans R0 tester avec la valeur prise dans R1, a l'adresse du
  //mutex
  asm volatile ("strex r5, r2, [%0]  \n\t" :: "r" (mutex) : "memory") ;

  //regarder si la valeur de retour est bonne ou pas
  // 0 reussite 1 fail
  // Si non retourner au debut
  asm volatile ("cmp r2, r5      \n\t") ;
  asm volatile ("beq .take       \n\t") ;
  asm volatile ("pop { r2, r5 }  \n\t") ;
  return;

}


// libere le mutex (à appeller à la fin de la section critique)
void freeM(int *mutex) {
  asm volatile ("push { r2 }   \n\t") ;
  asm volatile ("mov r2, #0    \n\t");
  asm volatile ("str r2, [%0]  \n\t" :: "r" (mutex) : "memory");
  asm volatile ("pop { r2 }    \n\t") ;
  return;
}

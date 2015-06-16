#include <Arduino.h>
#include "mutex.h"

//  Serial.println("");

int tabM[5] = {0,0,0,0,0};
//int *tabM = 0;


//essayer de prendre le mutex, fini quand on l'obtient
void takeM (int *mutex) {


  //valeur du mutex pris
  asm volatile ("mov r1, #1  \n\t");
  asm volatile ("mov r2, #0x0  \n\t");

  asm volatile (".take:  \n\t");
  //lire la valeur du mutex
  asm volatile ("ldrex r5, [%0]   \n\t" :: "r" (mutex));
  
  //regarder sa valeur
  // si prise(==1) recommencer la fonction
  asm volatile ("subs r3, r2, r5  \n\t");
  asm volatile ("blt .take  \n\t");
  
  //sinon essayer de prendre le verrou
  //valeur retour dans R0 tester avec la valeur prise dans R1, a l'adresse du mutex
  asm volatile ("strex r5, r1, [%0]  \n\t" : "=r" (mutex));
  


  //regarder si la valeur de retour est bonne ou pas
  // 0 reussite 1 fail
  // Si non retourner au debut
  asm volatile ("subs r3, r2, r5  \n\t");
  asm volatile ("blt .take  \n\t");
  // Si oui on à pris le verrou et on fait ce qu'on à a faire
  //Serial.println("b");  
  return;

}


// libere le mutex (à appeller à la fin de la section critique)
void freeM(int *mutex) {
  asm volatile ("mov r2, #0  \n\t");
  asm volatile ("str r2, [%0]  \n\t" : "=r" (mutex) );
  return;
}


void takeU () {
  takeM(&tabM[1]);
  // Serial.println(tabM[1]);
}
void freeU () {
  freeM(&tabM[1]);
  //Serial.println(tabM[1]);
}

#include "mutex.h"


//essayer de prendre le mutex, fini quand on l'obtient
void takeM (int *mutex) {

  //valeur du mutex pris
  asm volatile ("mov r1, #0x1  \n\t");


  asm volatile (".take:  \n\t");
  //lire la valeur du mutex
  asm volatile ("ldrex r0, [%0]   \n\t" :: "r" (mutex));
  //regarder sa valeur
  // si prise(==1) recommencer la fonction
  asm volatile ("cmp r0, #0  \n\t");
  asm volatile ("bne .take  \n\t");

  //sinon essayer de prendre le verrou
  //valeur retour dans R0 tester avec la valeur prise dans R1, a l'adresse du mutex
  asm volatile ("strex r0, r1, [%0]  \n\t" : "=r" (mutex));

  //regarder si la valeur de retour est bonne ou pas
  // 0 reussite 1 fail
  // Si non retourner au debut
  asm volatile ("cmp r0, #0  \n\t");
  asm volatile ("bne .take  \n\t");
  // Si oui on à pris le verrou et on fait ce qu'on à a faire
  return;

}


// libere le mutex (à appeller à la fin de la section critique)
void freeM(int *mutex) {
  asm volatile ("str r0, [%0]  \n\t" : "=r" (mutex)  );
  return;
}

#ifndef _SEMAPHORE_
#define _SEMAPHORE_

void sem_init (int num, int val) ;

void sem_acquire (int *num) ;
void sem_release (int *num) ;


#endif

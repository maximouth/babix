#ifndef _MUTEX_
#define _MUTEX_

#define pris (OX1)
#define libre (0X0)

#define reussi (0)
#define failed (1)


void takeM(int *mutex);
void freeM(int *mutex);


#endif

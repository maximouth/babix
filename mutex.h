#ifndef _MUTEX_
#define _MUTEX_

#ifdef __cplusplus
extern "C" {
#endif

#define pris (OX1)
#define libre (0X0)

#define reussi (0)
#define failed (1)


void takeM (volatile uint32_t *mutex);
void freeM (volatile uint32_t *mutex);
void takeU ();
void freeU ();

#ifdef __cplusplus
}
#endif
#endif

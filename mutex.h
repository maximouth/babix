#ifndef _MUTEX_
#define _MUTEX_

#ifdef __cplusplus
extern "C" {
#endif

void takeM (volatile uint32_t *mutex) ;
void freeM (volatile uint32_t *mutex) ;

#ifdef __cplusplus
}
#endif
#endif

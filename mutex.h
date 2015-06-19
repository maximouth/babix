/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  François Pessaux 04/2015.
  Maxime Ayrault 19/06/2015.
  This code can be freely distributed.
*/

#ifndef _MUTEX_
#define _MUTEX_

#ifdef __cplusplus
extern "C" {
#endif

/** Type of a mutex lock. */
typedef volatile uint32_t mutex_t ;
void mutex_acquire (mutex_t *mutex) ;
void mutex_release (mutex_t *mutex) ;

#ifdef __cplusplus
}
#endif
#endif

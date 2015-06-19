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

void mutex_acquire (volatile uint32_t *mutex) ;
void mutex_release (volatile uint32_t *mutex) ;

#ifdef __cplusplus
}
#endif
#endif

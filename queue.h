/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <Arduino.h>
#include "kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

proc_id_t take (struct pid_queue_t *q) ;
bool enqueue (struct pid_queue_t *q, proc_id_t id) ;

#ifdef __cplusplus
}
#endif
#endif

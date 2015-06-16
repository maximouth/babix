/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#include <Arduino.h>
#include "kernel.h"


/** Extract the first process identifier from the queue and return it. If no
    process identifier is in the queue (empty queue), then return the identifier
    of the main process. */
proc_id_t take (struct pid_queue_t *q)
{
  proc_id_t res ;
  if ((q == NULL) || (q->cur_nb == 0)) {
    /* If the queue is empty, return the pid of the system task. */
    return (MAIN_PROCESS_ID) ;
  }
  res = q->pids[q->first] ;
  q->first = (q->first + 1) % MAX_PROCESSES ;
  q->cur_nb-- ;
  return (res) ;
}



/** Insert a process identifier in the queue. Returns true in case of success,
    false otherwise. This function should never return false if the function
    create_process () really takes care of not creating more processes than
    authorized. */
bool enqueue (struct pid_queue_t *q, proc_id_t id)
{
  if ((q == NULL) || (q->cur_nb == MAX_PROCESSES)) {
    /* Full queue. Should never happen since the process creation function
       should ensure that is does not create more processes than allowed. */
    return (false) ;
  }
  q->pids[(q->first + q->cur_nb) % MAX_PROCESSES] = id ;
  q->cur_nb++ ;
  return (true) ;
}

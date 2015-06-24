/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#ifndef __PROCESS_H__
#define __PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif

extern struct kernel_t kernel ;
proc_id_t create_process (void (*code)()) ;
  __attribute__ ( ( naked ) ) void end_process ();

#ifdef __cplusplus
}
#endif
#endif

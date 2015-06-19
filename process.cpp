/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#include <Arduino.h>
#include "kernel.h"
#include "context.h"
#include "process.h"
#include "queue.h"
#include "mutex.h"


// mutex
uint32_t M[4] = {0,0,0,0};


/** The main and global structure of the kernel. */
struct kernel_t kernel = {
  0,      /* kernel_sp. Nevermind its init value, it will be smashed as soon
             as a process will be made active. And before, this value is not
             used. */
  { 0 },  /* processes */
  MAIN_PROCESS_ID,     /* current_process_id */
  {       /* queue */
    0,    /* cur_nb */
    0,    /* first */
    { 0 } /* pids */
  }
};



/** Creates a new process with a new stack and the code address given as
    argument and put this new process in the scheduling queue. */
proc_id_t create_process (void (*code)())
{
 
  /* Try to acquire mutex 0. */
  mutex_acquire (&M[0]) ;

  /** Stack top as allocated with malloc. Reminded for liberation. */
  mcu_word_t *stack_top ;
  /** Pointer to the stack once a hardware stack frame has been pushed. */
  struct hard_save_t *sp_after_hard_save ;
  /** Pointer to the stack once a software stack frame has been pushed. */
  struct soft_save_t *sp_after_soft_save ;
  int16_t nb_processes = kernel.queue.cur_nb ;

  /* Check for enough room for a new process. */
  if (nb_processes > MAX_PROCESSES) return (MAIN_PROCESS_ID) ;
  /* Register the process in the processes table. */
  kernel.processes[nb_processes].pid = nb_processes ;

  /* Allocate a stack segment. */
  stack_top = (mcu_word_t*) malloc (sizeof (mcu_word_t) * STACK_SIZE) ;
  if (stack_top == NULL) return (MAIN_PROCESS_ID) ;
  /* Record the top of the stack to free it later. */
  kernel.processes[nb_processes].top_stack = stack_top ;

  /* Compute the stack pointer position after a hardware stack frame will have
     been pushed.
     ATTENTION: the SAM3x8E implements a full descending stack. This means
     that the stack pointer indicates the last stacked item on the stack
     memory. See SAM3x8E datasheet 12.4.2 page 60. */
  sp_after_hard_save = (struct hard_save_t*)
    (((uint32_t) &stack_top[STACK_SIZE - 1]) - sizeof (struct hard_save_t)) ;
  /* Initialise PC with the process' function code. */
  sp_after_hard_save->pc = (mcu_word_t) code ;
  /* Clear the SR. */
  sp_after_hard_save->psr = 0x01000000 ;

  /* Compute the stack pointer position after a software stack frame will have
     been pushed. */
  sp_after_soft_save = (struct soft_save_t*)
    (((uint32_t) sp_after_hard_save) - sizeof (struct soft_save_t)) ;
  /* Initialize the software-saved LR to the value telling to return from
     exception. This way, the first time the process will be ran, the scheduler
     will think it had been swaped, when will restore the LR (signal that the
     exception handler is ended) to return from the exception to the code
     registered in the PC on the hardware stack frame, i.e. the code of the
     beginning of the function.
     Use the bitmask to tell to go on using the MSP. We do not implement a
     separate stack pointer register for "system" and "user" mode. Everybody
     runs with the MSP (i.e. the one that would be ideally reserved to the
     "system" mode).
     See SAM3x8E datasheet 16.6.7.6 page 86. */
  sp_after_soft_save->lr = 0xFFFFFFF9 ;

  /* Record the process handler to the context, i.e. only its stack pointer. */
  kernel.processes[nb_processes].sp = (mcu_word_t*) sp_after_soft_save ;

  /* One more process is in the pipe... Enqueue it. */
  enqueue (&kernel.queue, nb_processes) ;
  kernel.queue.cur_nb = nb_processes + 1 ;

  /* Release the mutex 0 acquired at the begining of the function. */
  mutex_release (&M[0]) ;
 
  return (nb_processes) ;
}

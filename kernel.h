/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Type of the CPU word. */
typedef uint32_t mcu_word_t ;


/** Type of a process identifier. */
typedef int16_t proc_id_t ;

/** Max number of user processes. Does not include the main process, i.e. the
    standard loop () function. */
#define MAX_PROCESSES (8)


  int tabM[4] = {0,0,0,0};  


struct pid_queue_t {
  int16_t cur_nb ;      /* Current number of elements. */
  int16_t first ;       /* Index of the first element. */
  proc_id_t pids[MAX_PROCESSES] ;
};


/** Default stack size for user processes.
    2 Kb (1 << 9 = 512 but are 32 bits words --> 512 * 4 = 2048. */
#define STACK_SIZE (1 << 9)
struct process_t {
  proc_id_t pid ;
  mcu_word_t *top_stack ;
  mcu_word_t *sp ;
};


/** Process identifier of the main process, i.e. the standard loop ()
    function. */
#define MAIN_PROCESS_ID (-1)


/** Structure grouping all the kernel state information. */
struct kernel_t {
  /** Saved stack pointer of the main process. */
  mcu_word_t main_task_sp ;
  /** Array containing all the living processes. */
  struct process_t processes[MAX_PROCESSES] ;
  /** Identifier of the currently active process. */
  proc_id_t current_process_id ;
  /** FIFO for round-robin simple scheduling. */
  struct pid_queue_t queue ;
};


/** The frequency at which to switch of active process. In other words, the
    inverse of the quantum of time given to each process. */
#define SYSTICK_FREQUENCY_HZ (1000)

#ifdef __cplusplus
}
#endif
#endif

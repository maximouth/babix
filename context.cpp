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


/* The following variables are made global to avoid having them on the context
   switcher stack. This avoids the stack frame being modified and simplifies
   the context switch. */
/** Process to make running. */
static struct process_t *incoming_proc ;
static proc_id_t incoming_proc_id ;       /** Its id. */

/** Process to stop running. */
static struct process_t *outgoing_proc ;
static proc_id_t outgoing_proc_id ;       /** Its id. */



extern "C" { /* Start of extern "C" for svcHook (). */


/** The pendSVC instruction (system call) handler.
    Overrides the weak symbol of the Arduino "standard library".
    ATTENTION: must be extern "C" otherwise ignored by the linker, hence
    never called (no effective overriding).

    ATTENTION: Must be "naked" to prevent GCC from making its own stack frame.
    Since all the registers will be trashed by this function when restoring a
    context, there is no need for any registers backup. Even more, this would
    change our expected stack frame !

    The SAM3X8E automatically saves r0, r1, r2, r3, r12, the return address,
    psr and lr at exception entry. See SAM3x8E datasheet 16.6.7.5 page 85.
*/
__attribute__ ( ( naked ) ) void pendSVHook (void)
{
  /* Push the context on the current process's stack.
     push is a synonym for STMDB sp!, relist */
  asm volatile (".save_outgoin_context: \n") ;
  asm volatile ("push    {r4 - r11, lr} \n\t") ;

  /* Guess the outgoing process id. */
  outgoing_proc_id = kernel.current_process_id ;
  /* Only enqueue the outcomming process if it is not the "Idle" task. */
  if (outgoing_proc_id != MAIN_PROCESS_ID)
    enqueue (&kernel.queue, outgoing_proc_id) ;
  /* Guess the incoming process id. */
  incoming_proc_id = take (&kernel.queue) ;
  /* Record the new running process. incoming_proc_id could be removed and
     replaced by kernel.current_process_id in fact. */
  kernel.current_process_id = incoming_proc_id ;

  /* Save the outgoing process' SP.
     If the process is the main process, then save its SP in the kernel
     structure, otherwise in the process's structure.
     r1 = outgoing stack pointer. */
  if (outgoing_proc_id != MAIN_PROCESS_ID) {
    outgoing_proc = &kernel.processes[outgoing_proc_id] ;
    asm volatile ("mov r1, %0     \n\t" :: "r" (&outgoing_proc->sp)) ;
  }
  else asm volatile ("mov r1, %0     \n\t" :: "r" (&kernel.main_task_sp)) ;


  /* Really save outgoing SP. */
  asm volatile ("mrs r2, msp    \n\t") ;
  asm volatile ("str r2, [r1]   \n\t") ;

  /* Restore the incoming process' SP.
     If the process is the main process, then load its SP from the kernel
     structure, otherwise from the process's structure.
     r0 = incoming stack pointer. */
  if (incoming_proc_id != MAIN_PROCESS_ID) {
    incoming_proc = &kernel.processes[incoming_proc_id] ;
    asm volatile ("mov r0, %0     \n\t" :: "r" (incoming_proc->sp)) ;
  }
  else asm volatile ("mov r0, %0     \n\t" :: "r" (kernel.main_task_sp)) ;
  /* Really write incoming SP. */
  asm volatile ("msr msp, r0    \n\t") ;

  /* Pop the context of the incoming process on its (the current process's)
     stack.
     pop is a synonym for LDMIA sp! reglist */
  asm volatile (".restore_incoming_context: \n\t") ;
  asm volatile ("pop {r4 - r11, lr}          \n\t") ;
  /* Exit from exception by jumping at LR which must be 0xFFFFFFF9.
     See SAM3x8E datasheet 16.6.7.6 page 86. */
  asm volatile ("bx lr                       \n\t") ;
}

} /* End of extern "C" for svcHook (). */



extern "C" {

/** Handler for the sysTick interrupt. It fires a PendSV exception. This
    exception will be processed by pendSVHook to swap processes.

    ATTENTION: must be extern "C" otherwise ignored by the linker, hence
    never called (no effective overriding).
*/
int sysTickHook ()
{
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
  return (0) ;
}

} /* End of extern "C" for sysTickHook (). */

/*

Why we don't use a CLREX with our LDREX and STREX

-> what is CLREX

CLREX is an instruction wich will fail the next STREX that will appear, so the 
store fail too.
(see 12.12.9 page 114)

-> why we need it generally

There is an example to explain why we need to use CLREX :

There is 2 variables A and B and 3 processes P1, P2 and P3.

P1 do a LDREX on B and up the exclusive tag.
P1 is switch, and somethings are done.
P3 do a LDREX on B,and up the tag that is already up.
And do a STREX on B that succed beacause the tag is up.
The exclusive access tag is now down.
P3 is switch.
P2 up the tag and do a LDREX on A.
P2 is switch.
P1 come and do is STREX on B wich succed because P2 up the tag.

So the memory is corrupt.
That is why the need a CLREX, and each context switch so we can down the tag 
for the following thread.


-> why we don't need it here

There 3 conditions that make the processor remove the exclusive acces tag:
- exec a CLREX instruction,
- exec a STREX instruction wich succed or failed,
- if an exception occurs.
(see 12.5.7.2 p 78)

and here the task switching is doing by an exception, so each time we switch of
thread, a CLREX is done automatically, and we don't need to use one ourself.

 */

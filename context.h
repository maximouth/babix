/*
  Babix - An educational little preemptive multitask kernel for Arduino Due.
  Francois Pessaux 04/2015.
  This code can be freely distributed.
*/

#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t mcu_word_t ;

/** Structure of data saved by the task-switcher onto the switched process's
    stack.
*/
struct soft_save_t {
  mcu_word_t r4 ;
  mcu_word_t r5 ;
  mcu_word_t r6 ;
  mcu_word_t r7 ;
  mcu_word_t r8 ;
  mcu_word_t r9 ;
  mcu_word_t r10 ;
  mcu_word_t r11 ;
  mcu_word_t lr ;
};


/** Structure of data saved by the hardware onto the switched process's
    stack when entering an exception.
    See SAM3x8E datasheet 16.6.7.5 page 85.
*/
struct hard_save_t {
  mcu_word_t r0 ;
  mcu_word_t r1 ;
  mcu_word_t r2 ;
  mcu_word_t r3 ;
  mcu_word_t r12 ;
  mcu_word_t lr ;
  mcu_word_t pc ;
  mcu_word_t psr ;
};

/* For debug only. */
extern volatile mcu_word_t dump_stack[8] ;

#ifdef __cplusplus
}
#endif
#endif

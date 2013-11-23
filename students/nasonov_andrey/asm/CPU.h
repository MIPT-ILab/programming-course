//{============================================================================
//! @file CPU.h
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains description of structure CPU
//!
//}============================================================================

#ifndef CPU_H_
#define CPU_H_

//!-------- Headers -----------------------------------------------------------
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//!----------------------------------------------------------------------------

//!-------- Structure ---------------------------------------------------------
struct CPU
  {
    struct stack CPU_stack;
    int ax;
    int bx;
    int cx;
    int *code;
  };
//!----------------------------------------------------------------------------

//!-------- Macros ------------------------------------------------------------
#define ASSERT_CPU( x ) {                                                     \
                          switch ( CPU_OK ( x ) )                             \
                            {                                                 \
                              case 0 : break;                                 \
                              case 1 : printf ( "CPU_STACK IS DEAD\n" );      \
                                       CPU_dump ( x );                        \
                                       assert ( 0 );                          \
                              case 2 : printf ( "CPU_STACK IS OVERFLOWN\n" ); \
                                       CPU_dump ( x );                        \
                                       assert ( 0 );                          \
                              case 3 : printf ( "CPU_STACK IS WEIRD\n" );     \
                                       CPU_dump ( x );                        \
                                       assert ( 0 );                          \
                              case 4 : printf ( "SOME REGS ARE DEAD\n" );     \
                                       CPU_dump ( x );                        \
                                       assert ( 0 );                          \
                              case 5 : printf ( "CPU_STACK IS DEAD\n" );      \
                                       printf ( "SOME REGS ARE DEAD\n" );     \
                                       assert ( 0 );                          \
                              case 6 : printf ( "CPU_STACK IS OVERFLOWN\n" ); \
                                       printf ( "SOME REGS ARE DEAD\n" );     \
                                       assert ( 0 );                          \
                              case 7 : printf ( "CPU_STACK IS WEIRD\n" );     \
                                       printf ( "SOME REGS ARE DEAD\n" );     \
                                       assert ( 0 );                          \
                            }                                                 \
                        }
//!----------------------------------------------------------------------------

//!-------- Prototypes --------------------------------------------------------
void CPU_construct ( struct CPU *pr, int n_size, int code_size );
void CPU_destruct ( struct CPU *pr );
void CPU_dump ( struct CPU *pr );
int CPU_OK ( struct CPU *pr );
int reg_push ( struct CPU *pr, int element, int reg );
int reg_pop ( struct CPU *pr, int reg );
//!----------------------------------------------------------------------------

#endif /* CPU_H_ */

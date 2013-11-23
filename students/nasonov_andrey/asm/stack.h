//{============================================================================
//! @file stack.h
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains description of structure stack
//!
//}============================================================================


#ifndef STACK_H_
#define STACK_H_

//!-------- Headers -----------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//!----------------------------------------------------------------------------

//!-------- Structure ---------------------------------------------------------
struct stack
  {
    int counter;
    int size;
    int* data;
  };
//!----------------------------------------------------------------------------

//!-------- Macros ------------------------------------------------------------
#define ASSERT_STACK( x ) {                                                   \
                            switch ( stack_OK ( x ) )                         \
                              {                                               \
                                case 0 : break;                               \
                                case 1 : printf ( "STACK IS DEAD\n" );        \
                                         stack_dump ( x );                    \
                                         assert ( 0 );                        \
                                case 2 : printf ( "STACK IS OVERFLOWN\n" );   \
                                         stack_dump ( x );                    \
                                         assert ( 0 );                        \
                                case 3 : printf ( "STACK IS WEIRD\n" );       \
                                         stack_dump ( x );                    \
                                         assert ( 0 );                        \
                              }                                               \
                          }
//!----------------------------------------------------------------------------

//!-------- Prototypes --------------------------------------------------------
void stack_construct ( struct stack *st, int n_size );
void stack_destruct ( struct stack *st );
void stack_dump ( struct stack *st );
int stack_OK ( struct stack *st );
void stack_push ( struct stack *st, int element );
int stack_pop ( struct stack *st );
void stack_add ( struct stack *st );
void stack_sub ( struct stack *st );
void stack_mul ( struct stack *st );
void stack_div ( struct stack *st );
int stack_compare ( struct stack *st );
//!----------------------------------------------------------------------------

#endif /* STACK_H_ */

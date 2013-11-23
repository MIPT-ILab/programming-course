//{============================================================================
//! @file stack.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains functions for structure stack
//!
//}============================================================================

#include "stack.h"

void stack_construct ( struct stack *st, int n_size )
  {
    assert ( st != NULL );
    ( st -> counter ) = 1;
    ( st -> size ) = n_size;
    ( st -> data ) = (int*) calloc ( n_size, sizeof ( int ) );
  }

void stack_destruct ( struct stack *st )
  {
    assert ( st != NULL );
    ( st -> size ) = 0;
    ( st -> counter ) = 0xDEADBEAF;
    free ( st -> data );
  }

void stack_dump ( struct stack *st )
  {
    assert ( st != NULL );
    printf ( "stack dump:" );
    if ( ( ( st -> counter ) <= ( ( st -> size ) + 1 ) ) && ( ( st -> counter ) > 0 ) )
      {
        printf ( " /ok\n" );
        printf ( "size : %d\n", ( st -> size ) );
        printf ( "counter : %d\n", ( st -> counter ) );
        for ( int i = 1; i < ( st -> counter ); i++ )
          {
            printf ( "%d\n", (st -> data)[i] );
          }
      }
    else
      {
        printf ( " /EVERYTHING'S BAD\n" );
        printf ( "NEEDS DIAGNOSIS\n" );
      }
  }

int stack_OK ( struct stack *st )
  {
    assert ( st != NULL );
    if ( ( ( st -> counter ) <= ( ( st -> size ) + 1 ) ) && ( ( st -> counter ) > 0 ) )
      {
        return 0;
      }
    else
      {
        if ( ( st -> counter ) == 0xDEADBEAF )
          {
            return 1;
          }
        else
          {
            if ( ( st -> counter ) >= ( st -> size ) )
              {
                return 2;
              }
            else
              {
                return 3;
              }
          }
      }
  }

void stack_push ( struct stack *st, int element )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    ( st -> data )[( st -> counter )] = element;
    ( st -> counter )++;
    ASSERT_STACK ( st );
  }

int stack_pop ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    ( st -> counter )--;
    return ( st -> data )[( st -> counter )];
  }

void stack_add ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    int var1 = stack_pop ( st );
    int var2 = stack_pop ( st );
    stack_push ( st, var2+var1 );
  }

void stack_sub ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    int var1 = stack_pop ( st );
    int var2 = stack_pop ( st );
    stack_push ( st, var2-var1 );
  }

void stack_mul ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    int var1 = stack_pop ( st );
    int var2 = stack_pop ( st );
    stack_push ( st, var2*var1 );
  }

void stack_div ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    int var1 = stack_pop ( st );
    int var2 = stack_pop ( st );
    stack_push ( st, var2/var1 );
  }

int stack_compare ( struct stack *st )
  {
    assert ( st != NULL );
    ASSERT_STACK ( st );
    int var1 = stack_pop ( st );
    int var2 = stack_pop ( st );
    int h = var1 - var2;
    stack_push ( st, var2 );
    stack_push ( st, var1 );
    return h;
   }

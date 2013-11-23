//{============================================================================
//! @file CPU.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains functions for structure CPU
//!
//}============================================================================

#include "CPU.h"

void CPU_construct ( struct CPU *pr, int n_size, int code_size )
  {
// Change int to size_t
    assert ( pr != NULL );
    stack_construct ( &( pr -> CPU_stack ), n_size );
    ( pr -> ax ) = 0;
    ( pr -> bx ) = 0;
    ( pr -> cx ) = 0;
    ( pr -> code ) = (int*) calloc ( code_size, sizeof ( int ) );
  }

void CPU_destruct ( struct CPU *pr )
  {
    assert ( pr != NULL );
    stack_destruct ( &( pr -> CPU_stack ) );
    free ( pr -> code );
    ( pr -> ax ) = 0xDEADBEAF;
    ( pr -> bx ) = 0xDEADBEAF;
    ( pr -> cx ) = 0xDEADBEAF;
  }

void CPU_dump ( struct CPU *pr )
  {
    assert ( pr != NULL );
    printf ( "CPU_dump:\n" );
    printf ( "Stack:\n" );
    stack_dump ( &( pr -> CPU_stack ) );
    printf ( "Registers:\n" );
    printf ( "%d\n", ( pr -> ax ) );
    printf ( "%d\n", ( pr -> bx ) );
    printf ( "%d\n", ( pr -> cx ) );
  }

int CPU_OK ( struct CPU *pr ) //! Переделать все
  {
    assert ( pr != NULL );
    int ax = ( pr -> ax );
    int bx = ( pr -> bx );
    int cx = ( pr -> cx );
    int h = 0;
    if ( ( ax == 0xDEADBEAF ) || ( bx == 0xDEADBEAF ) || ( cx == 0xDEADBEAF ) )
      {
        h = 1;
      }
    if ( h == 0 )
      {
        return ( stack_OK ( &( pr -> CPU_stack ) ) );
      }
    else
      {
        return ( stack_OK ( &( pr -> CPU_stack ) ) + h );
      }
  }

int reg_push ( struct CPU *pr, int element, int reg )
  {
    assert ( pr != NULL );
    ASSERT_CPU ( pr );
    switch ( reg )
      {
        case 0x01 : ( pr -> ax ) = element;
                    return 1;
        case 0x02 : ( pr -> bx ) = element;
                    return 1;
        case 0x03 : ( pr -> cx ) = element;
                    return 1;
        default   : return 0;
      }
  }

int reg_pop ( struct CPU *pr, int reg )
  {
    assert ( pr != NULL );
    ASSERT_CPU ( pr );
    switch ( reg )
      {
        case 0x01 : return ( ( pr -> ax ) );
        case 0x02 : return ( ( pr -> bx ) );
        case 0x03 : return ( ( pr -> cx ) );
        default   : return 0xDEADBEAF;
      }
  }

//{============================================================================
//! @file parser.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains function "parser" for machine code
//!
//}============================================================================

#include "CPU.h"
#include "stack.h"

int parser ( struct CPU *pr, int *code )
  {
    int i    = 0;
    int word = code[i++];
    while ( word != 0 )
      {
        switch ( word )
          {
            case 0x80 : word = code[i];    i++; //! Merge
                        if ( word == 0xAA ) //! Fix AA (different commands)
                          {
                            word = code[i];
                            i++;
                            stack_push ( &( pr -> CPU_stack ), reg_pop ( pr, word ) );
                          }
                        else
                            stack_push ( &( pr -> CPU_stack ), word );
                        break;
            case 0x81 : word = code[i];    i++;
                        if ( word != 0xAA )
                          return 1; //! Not address
                        word = code[i];    i++;
                        reg_push ( pr, stack_pop ( &( pr -> CPU_stack ) ), word );
                        break;
            case 0x82 : stack_add ( &( pr -> CPU_stack ) );
                        break;
            case 0x83 : stack_mul ( &( pr -> CPU_stack ) );
                        break;
            case 0x84 : stack_sub ( &( pr -> CPU_stack ) );
                        break;
            case 0x85 : stack_div ( &( pr -> CPU_stack ) );
                        break;
            case 0x86 : word = code[i];
                        i = word;
                        break;
            case 0x87 : if ( ( stack_compare ( &( pr -> CPU_stack ) ) == 0 ) )
                          {
                            i++;
                          }
                        break;
            case 0x89 : if ( ( stack_compare ( &( pr -> CPU_stack ) ) > 0 ) )
                          {
                            i++;
                          }
                        break;
            case 0x90 : if ( ( stack_compare ( &( pr -> CPU_stack ) ) < 0 ) )
                          {
                            i++;
                          }
                        break;
            case 0x88 : word = code[i];    i++;  //Enum?
                        if ( word == 0xAA )
                          {
                            word = code[i];
                            i++;
                            printf ( "%d\n", reg_pop ( pr, word ) );
                          }
                        else
                            printf ( "%d\n", word );
                        break;
            default   : break;
          }
        word = code[i];    i++;
      }
    return 0;
  }

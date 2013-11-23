//{============================================================================
//! @file CPU.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains functions for translating assembly language into machine code
//!
//}============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void places ( int *code, int *place )
  {
    int i = 0;
    char str[5] = {};
    scanf ( "%s", str );
    while ( strcmp ( str, "end" ) != 0 )
      {
        if ( str[0] == ':' )
          {
            i--;
            int h = (str[1])-'0';
            place[(str[1])-'0'] = i + 1;
          }
        i++;
        scanf ( "%s", str );
      }
   }

int translate ( int *code, int *place )
  {
    int i = 0;
    char str[5] = {};
    int h = 0;
    scanf ( "%s", str );
    while ( strcmp ( str, "end" ) != 0 )
      {
        if ( str[0] != ':' )
          {
            if ( str[1] != 'x' )
              {
                if ( str[1] == '\0' )
                  {
                    code[i] = atof(str);
                  }
                else
                  {
                    switch ( str[2] )
                      {
                        case 's' : code[i] = 0x80; //! push
                                   break;
                        case 'p' : switch ( str[0] )
                                     {
                                       case 'p' : code[i] = 0x81; //! pop
                                                  break;
                                       case 'j' : code[i] = 0x86;    i++; //! jmp
                                                  scanf ( "%s", str );
                                                  code[i] = place[str[0]-'0'];
                                                  break;
                                       default  : return 2; //! Unknown command;
                                     }
                                   break;
                        case 'd' : code[i] = 0x82; //! add
                                   break;
                        case 'l' : code[i] = 0x83; //! mul
                                   break;
                        case 'b' : code[i] = 0x84; //! sub
                                   break;
                        case 'v' : code[i] = 0x85; //! div
                                   break;
                        case 'q' : code[i] = 0x87; //! ifq
                                   break;
                        case 't' : code[i] = 0x88; //! out
                                   break;
                        case 'm' : code[i] = 0x90; //! ifm
                                   break;
                        case 'f' : code[i] = 0x89; //! iff
                                   break;
                        default  : h = atof(str);
                                   code[i] = h; //! else
                                   break;
                      }
                  }
              }
            else
              {
                code[i] = 0xAA;
                i++;
                switch ( str[0] )
                  {
                    case 'a' : code[i] = 0x01;
                               break;
                    case 'b' : code[i] = 0x02;
                               break;
                    case 'c' : code[i] = 0x03;
                               break;
                    default  : return 1; //! Unknown address
                               break;
                  }
              }
          }
        else
          {
            i--;
          }
        scanf ( "%s", str );
        i++;
      }
    code[i] = 0x00;
  }

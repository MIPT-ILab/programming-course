//{============================================================================
//! @file main.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Contains application of parser.c and translator.c
//!
//}============================================================================

#include "CPU.h"
#include "stack.h"

int parser ( struct CPU *pr, int *code );
int translate ( int *code, int *place );
void places ( int *code, int *place );

int main ()
  {
    struct CPU mCPU;
    int place[10];
    CPU_construct ( &mCPU, 80, 80 );
    FILE* input;
    fclose ( stdin );
    stdin = fopen ( "input", "rb" );
    places ( mCPU.code, place );
    fclose ( stdin );
    stdin = fopen ( "input", "rb" );
    translate ( mCPU.code, place );
    parser ( &mCPU, mCPU.code );
    CPU_dump ( &mCPU );
    CPU_destruct ( &mCPU );
    return 0;
  }

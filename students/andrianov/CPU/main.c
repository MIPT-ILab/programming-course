#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "CPU_function.h"
#include <math.h>

int main()
{
    FILE* fcode = fopen ( "code.txt", "rb");
    CPU cpu = {} ;
    CPU_construct ( &cpu );
    CPU_read ( &cpu, fcode );
    //CPU_dump ( &cpu );
    CPU_run ( &cpu );
    fclose ( fcode );
    return 0;
}

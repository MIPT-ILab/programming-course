#ifndef CPU_FUNCTION_H_INCLUDED
#define CPU_FUNCTION_H_INCLUDED

#define MAX_CODE_SIZE 100
#include "stack_function.h"

struct computer
{
    float code[MAX_CODE_SIZE] ;
    int position;
    Stack_t st;
    Stack_t ret;
    float ax;
    float bx;
    float cx;
};

typedef struct computer CPU;

int CPU_construct ( CPU* cpu);

int CPU_OK ( CPU* cpu);

int CPU_dump ( CPU* cpu );

int CPU_mov_ax ( CPU* cpu, float x );

int CPU_mov_bx ( CPU* cpu, float y );

int CPU_mov_cx ( CPU* cpu, float z );

int CPU_push ( CPU* cpu, float val );

int CPU_push_ret ( CPU* cpu, float val );

float CPU_pop ( CPU* cpu);

float CPU_pop_ret ( CPU* cpu);

int CPU_destruct ( CPU* cpu );

int CPU_read ( CPU* cpu, FILE* fcode );

int CPU_run ( CPU* cpu);



#endif // CPU_FUNCTION_H_INCLUDED

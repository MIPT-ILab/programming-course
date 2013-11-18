//!{====================================================================================
//! @file CPU_function.c
//! @date    2013-11-15 16:05
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! This file consists of function of the stack
//!
//!}====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack_function.h"
#include "list_comands.h"
#include "CPU_function.h"
#include <math.h>


#define ASSERT_OK(name) if ( !CPU_OK( name ) )\
        { CPU_dump ( name ); assert(!"__LINE__"); }\
        else

#define MAX_POINTER_SIZE 50

//!{============================================================================
//! CPU_construct - function calls stack_construct for two stacks of CPU and reset
//!                 registers, array of code and position
//!
//! @param      cpu        pointer on struct which will be reseted
//!
//! @return                0
//!}============================================================================

int CPU_construct ( CPU* cpu)
{
    assert ( cpu );
    stack_construct ( &cpu->st );
    stack_construct ( &cpu->ret );
    cpu->ax = 0;
    cpu->bx = 0;
    cpu->cx = 0;
    cpu->position = 0;
    int i = 0;
    for ( i = 0; i < MAX_CODE_SIZE; i++ )
    {
        cpu->code[i] = 0;
    }
    return 0;
}

//!{============================================================================
//! CPU_construct - checks pointer of cpu, stacks and position
//!
//! @param      cpu        pointer on struct which will be checked
//!
//! @return                0 if cpu is bad
//!                        1 if cpu is good
//!}============================================================================

int CPU_OK ( CPU* cpu)
{
    return ( cpu && stack_OK ( &cpu->st ) && stack_OK ( &cpu->ret ) && ( 0 <= cpu->position ) && ( cpu->position < MAX_CODE_SIZE ) );
}

//!{============================================================================
//! CPU_dump - function printf information about both stacks, registers, position
//!            and code array
//!
//! @param      cpu   pointer on struct
//!
//! @return           0
//!}============================================================================

int CPU_dump ( CPU* cpu )
{
    ASSERT_OK ( cpu )
    printf ( "CPU_dump\n");
    if ( CPU_OK ( cpu ) )
    {
        printf ( "ok\n" );
    }
    else
    {
        printf ( "BAD\n" );
    }
    stack_dump ( &cpu->st );
    stack_dump ( &cpu->ret );
    printf ( "position = %i\n", cpu->position );
    printf ( "ax = %f\n", cpu->ax);
    printf ( "bx = %f\n", cpu->bx);
    printf ( "cx = %f\n", cpu->cx);
    int i = 0;
    for ( i = 0; i < MAX_CODE_SIZE; i++ )
    {
        printf ( "code[%i] = %f\n", i, cpu->code[i] );
    }
    return 0;
}

//!{============================================================================
//! CPU_mov_ax - function put number to register ax
//!
//! @param      cpu   pointer on struct
//! @param      x     number
//!
//! @return                0
//!}============================================================================

int CPU_mov_ax ( CPU* cpu, float x )
{
    ASSERT_OK ( cpu )
    cpu->ax = x;
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_mov_bx - function put number to register bx
//!
//! @param      cpu   pointer on struct
//! @param      y     number
//!
//! @return                0
//!}============================================================================

int CPU_mov_bx ( CPU* cpu, float y )
{
    ASSERT_OK ( cpu )
    cpu->bx = y;
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_mov_cx - function put number to register cx
//!
//! @param      cpu   pointer on struct
//! @param      z     number
//!
//! @return                0
//!}============================================================================

int CPU_mov_cx ( CPU* cpu, float z )
{
    ASSERT_OK ( cpu )
    cpu->cx = z;
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_push - function push number to stack for calculations in cpu
//!
//! @param      cpu   pointer on struct
//! @param      val   number
//!
//! @return                0
//!}============================================================================

int CPU_push ( CPU* cpu, float val )
{
    ASSERT_OK ( cpu )
    stack_push ( &cpu->st, val );
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_push_ret - function push number to stack for pointers in cpu
//!
//! @param      cpu   pointer on struct
//! @param      val   number
//!
//! @return                0
//!}============================================================================

int CPU_push_ret ( CPU* cpu, float val )
{
    ASSERT_OK ( cpu )
    stack_push ( &cpu->ret, val );
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_pop_ret - function pop number from stack for pointers in cpu
//!
//! @param      cpu   pointer on struct
//!
//! @return           poping value
//!}============================================================================

float CPU_pop_ret ( CPU* cpu)
{
    ASSERT_OK ( cpu )
    if ( ( cpu->ret.count ) <= 0 )
    {
        CPU_dump ( cpu );
        assert (!" CPU_pop_ret  " );
    }
    return stack_pop ( &cpu->ret );
}

//!{============================================================================
//! CPU_pop - function pop number from stack for calculations in cpu
//!
//! @param      cpu   pointer on struct
//!
//! @return           poping value
//!}============================================================================

float CPU_pop ( CPU* cpu)
{
    ASSERT_OK ( cpu )
    if ( ( cpu->st.count ) <= 0 )
    {
        CPU_dump ( cpu );
        assert (!" CPU_pop  " );
    }
    return stack_pop ( &cpu->st );
}

//!{============================================================================
//! CPU_destruct - function spoils registers and position and calls stack_dextruct
//!
//! @param      cpu   pointer on struct
//!
//! @return           0
//!}============================================================================

int CPU_destruct ( CPU* cpu )
{
    ASSERT_OK ( cpu )
    stack_destruct ( &cpu->ret );
    stack_destruct ( &cpu->st );
    cpu->ax = 666;
    cpu->bx = 666;
    cpu->cx = 666;
    int i = 0;
    for ( i = 0; i < MAX_CODE_SIZE; i++)
    {
        cpu->code[i] = 666;
    }
    cpu->position = -1;
    return 0;
}

//!{============================================================================
//! CPU_read - function read number of commands from file and put it to array of code
//!
//! @param      cpu     pointer on struct
//! @param      fcode   file with number commands
//!
//! @return           0
//!}============================================================================

int CPU_read ( CPU* cpu, FILE* fcode )
{
    assert ( fcode );
    // j = i++ + ++i;
    ASSERT_OK ( cpu )
    cpu->position = 0;
    int pointers[MAX_POINTER_SIZE] = {};
    fseek ( fcode, 0, SEEK_END );
    int last = ftell ( fcode );
    rewind ( fcode );
    fread ( cpu->code, sizeof ( float ), last, fcode);
    ASSERT_OK ( cpu )
    return 0;
}

//!{============================================================================
//! CPU_run - function do commands which are in the code array
//!
//! @param      cpu   pointer on struct
//!
//! @return           0
//!}============================================================================

int CPU_run ( CPU* cpu )
{
    ASSERT_OK ( cpu )
    cpu->position = 0;
    while ( cpu->code[cpu->position] != CMD_END )
    {
        //CPU_dump ( cpu );
        #define SET_CMD_(name, num, code) case CMD_##name: code; break;
        switch ( (int)cpu->code[cpu->position] )
        {
            #include "commands.h"
        }
        //cpu->position++;
        #undef SET_CMD_
    }
    return 0;
}

/*int main ()
{
    CPU cpu;
    CPU_construct ( &cpu );
    CPU_push ( &cpu, 10 );
    float y = CPU_pop ( &cpu );
    printf ("%f", y);
    //printf ("%i", cpu.st.count );
}*/


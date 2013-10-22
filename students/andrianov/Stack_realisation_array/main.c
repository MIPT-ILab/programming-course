//!{====================================================================================
//! @file Stack_realisation_array.c
//! @date    2013-10-22 13:10
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! File include function which work with stack
//! Stack is an array with counter
//!
//!}====================================================================================

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define ST_SIZE 10


//!{====================================================================================
//! Stack consists of array and counter
//!
//!}====================================================================================


struct Stack_t
{
    int count;
    double data[ST_SIZE];
};

typedef struct Stack_t Stack_t;


int stack_construct ( Stack_t* st );

int stack_destruct ( Stack_t* st );

int stack_OK ( const Stack_t* st );

int stack_push ( Stack_t* st, double val );

double stack_pop ( Stack_t* st );

int stack_full ( Stack_t* st );

int stack_empty ( Stack_t* st );

int stack_dump ( Stack_t* st );


int main()
{
    return 0;
}

//!{============================================================================
//! stack_construct - function nullifies elements of array and counter
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_construct ( Stack_t* st )
{
    int i = 0;
    for ( i = 0; i < ST_SIZE; i++ )
    {
        st->data[i] = 0;
    }
    st->count = 0;
    return 0;
}

//!{============================================================================
//! stack_destruct - function spoils counter and array in stack
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_destruct ( Stack_t* st )
{
    int i = 0;
    for ( i = 0; i < ST_SIZE; i++ )
    {
        st->data[i] = 0xBADF00D;
    }
    st->count = -1;
    return 0;
}

//!{============================================================================
//! stack_OK - function check counter, of stack and its adress
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_OK ( const Stack_t* st )
{
    return ( st && 0 <= st->count && st->count <= ST_SIZE );
}

//!{============================================================================
//! stack_push - function puts number in stack
//!
//! @param      st   adress of stack in memory
//! @param      val  value of number, which is pushing to stack
//!
//! @return         0
//!}============================================================================

int stack_push ( Stack_t* st, double val )
{
    if ( !stack_OK ( st ) )
    {
        stack_dump ( st );
        assert(!" stack_push " );
    }
    else
    {
        st->data[st->count] = val;
        (st->count)++;
    }
    if ( !stack_OK ( st ) )
    {
        stack_dump ( st );
        assert(!" stack_push " );
    }
    return 0;
}

//!{============================================================================
//! stack_pop - function takes number from stack
//!
//! @param      st   adress of stack in memory
//!
//! @return          function returns value of taking element
//!}============================================================================

double stack_pop ( Stack_t* st )
{
    double pop = 0;
    if ( !(st && 0 <= st->count-1 && st->count <= ST_SIZE)  )
    {
        stack_dump ( st );
        assert(!" stack_pop" );
    }
    else
    {
        (st->count)--;
        return st->data[st->count];
    }
    if ( !stack_OK ( st ) )
    {
        stack_dump ( st );
        assert(!" stack_pop" );
    }
}

//!{============================================================================
//! stack_full - function checks is stack full or not
//!
//! @param      st   adress of stack in memory
//!
//! @return         1 if stack is full
//!                 2 if stack is not full
//!}============================================================================

int stack_full ( Stack_t* st )
{
    if ( !stack_OK ( st ) )
    {
        stack_dump ( st );
        assert(!" stack_full " );
    }
    if ( st->count = ST_SIZE-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//!{============================================================================
//! stack_empry - function checks is stack empty or not
//!
//! @param      st   adress of stack in memory
//!
//! @return         1 if stack is empty
//!                 2 if stack is not empty
//!}============================================================================

int stack_empty ( Stack_t* st )
{
    if ( !stack_OK ( st ) )
    {
        stack_dump ( st );
        assert(!" stack_empty " );
    }
    if ( st->count == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//!{============================================================================
//! stack_dump - function prints information about stack -
//!              ST_SIZE, elements of stack, counter of stack and is stack OK or not
//!
//! @param      st   adress of stack in memory
//!
//! @return      0
//!}============================================================================

int stack_dump ( Stack_t* st )
{
    printf ( "Stack\n" );
    if (stack_OK ( st ) )
    {
        printf ( "ok\n" );
    }
    else
    {
        printf ( "BAD\n");
    }
    printf ( "count = %i\n", st->count );
    printf ( "size of stack = %i\n", ST_SIZE );
    int i = 0;
    for (i = 0; i < ST_SIZE; i++)
    {
        if ( i < st->count )
        {
            printf ( "data[%i] = %lf *\n", i, st->data[i] );
        }
        else
        {
            printf ( "data[%i] = %lf\n", i, st->data[i] );
        }
    }
    return 0;
}

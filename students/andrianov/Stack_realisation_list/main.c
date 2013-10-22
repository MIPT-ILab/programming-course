//!{====================================================================================
//! @file Stack_realisation.c
//! @date    2013-10-22 13:10
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! File include function which work with stack
//! Stack is a list of elements
//!
//!}====================================================================================


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define elem int

//!{============================================================================
//! elem_stack_t - consists of pointer on last element and value of element
//!
//!}============================================================================

struct elem_stack_t
{
    elem x;
    struct elem_stack_t* previos;
};


typedef struct elem_stack_t elem_stack_t;

//!{============================================================================
//! Stack_t - consists of pointer on last element and number od size of stack
//!
//!}============================================================================

struct Stack_t
{
    elem_stack_t* last;
    int stack_size;
};

typedef struct Stack_t Stack_t;

int stack_OK ( const Stack_t* st );

int stack_construct ( Stack_t* st );

int stack_push ( Stack_t* st, elem val );

elem stack_pop ( Stack_t* st );

int stack_destruct ( Stack_t* st);

int stack_empty ( Stack_t* st );

int stack_dump ( Stack_t* st );

int main()
{
    return 0;
}

//!{============================================================================
//! stack_OK - function check counter of stack and its pointer
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_OK ( const Stack_t* st )
{
    return ( st && 0 <= st->stack_size );
}

//!{============================================================================
//! stack_construct - function nullifies last element and pointer on last element
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_construct ( Stack_t* st )
{
    st->last = NULL;
    st->stack_size = 0;
    return 0;
}

//!{============================================================================
//! stack_push - function puts number in stack
//!
//! @param      st   adress of stack in memory
//! @param      val  value of number, which is pushing to stack
//!
//! @return         0
//!}============================================================================

int stack_push ( Stack_t* st, elem val )
{
    if ( !stack_OK ( st ) )
    {
        assert( !"stack_push" );
    }
    else
    {
        if ( (st->last) == NULL)
        {
            st->last = (elem_stack_t*) calloc ( 1, sizeof ( elem_stack_t ) );
            (st->last)->x = val;
            (st->last)->previos = NULL;
            (st->stack_size)++;
        }
        else
        {
            elem_stack_t* lastref = st->last;
            st->last = (elem_stack_t*) calloc ( 1, sizeof ( elem_stack_t ) );
            (st->last)->previos = lastref;
            (st->last)->x = val;
            (st->stack_size)++;
        }
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

elem stack_pop ( Stack_t* st )
{
    if ( !stack_OK ( st ) || (st->last) == NULL )
    {
        assert( !"stack_push");
    }
    else
    {
        elem lastelem;
        lastelem = (st->last)->x;
        st->last = (st->last)->previos;
        return lastelem;
    }
}

//!{============================================================================
//! stack_destruct - function free all part of memory, where stack was situated
//!
//! @param      st   adress of stack in memory
//!
//! @return         0
//!}============================================================================

int stack_destruct ( Stack_t* st)
{
    elem_stack_t* tmpElement = (st ? st->last : 0);
    while ( tmpElement != NULL )
    {
        elem_stack_t* lastelem = tmpElement->previos;
        free ( tmpElement );
        tmpElement = lastelem;
    }
    free ( st );
    return 0;
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
    if ( st->last == NULL)
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
//!              elements of stack, size of stack and is stack OK or not
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
    printf ( "size = %i\n", st->stack_size);
    elem_stack_t* tmpElement = (st ? st->last : 0);
    int i = 0;
    while ( tmpElement != NULL )
    {
        elem_stack_t* lastelem = tmpElement->previos;
        elem d = tmpElement->x;
        printf("%i element of stack = %i\n", st->stack_size - i, d);
        tmpElement = lastelem;
        i++;
    }
}








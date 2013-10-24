//!{====================================================================================
//! @file Var1TaskA.c
//! @date    2013-10-14 23:21
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Programm finds NOK of two numbers
//!
//! @par The programme takes two numbers
//!      It needs to output NOK of numbers
//!}====================================================================================

#include <stdio.h>
#include <math.h>

long NOK ( long a, long b );

int main ()
{
    long a = 0,
         b = 0;
    printf ( "#Enter numbers\n" );
    scanf ( "%i %i", &a, &b );
    long result = NOK ( a, b );
    printf ( "%i - is NOK of %i and %i\n", result, a, b);
    return 0;
}

//!{============================================================================
//! NOK         - finds NOK of two numbers
//!
//! @param      a   first number
//! @param      b   second number
//!
//! @return         NOK of numbers
//!}===================================================================================

long NOK ( long a, long b )
{

    long i = 0,
         maximum = 0;
    if ( a > b )
    {
        maximum = a;
    }
    else
    {
        maximum = b;
    }
    for ( i = maximum ; i < a * b; i++)
    {
        if ( ( i % a == 0 ) && ( i % b == 0) )
        {
            return i;
        }
    }
}

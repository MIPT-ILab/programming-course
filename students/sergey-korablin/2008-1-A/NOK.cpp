//{=================================================================================
//! @file    NOK.cpp
//! @date    2013-10-06 21:20
//! @author  Sergey Korablin <ogneej@gmail.com>
//!
//! Calculation of least common multiple
//!
//! @par     Statement
//!          Calculation of least common multiple
//}=================================================================================

#include <stdio.h>

//{=================================================================================
//! NOD - calculation of greatest common divisor.
//!
//! @param      a    Input 1
//! @param      b    Input 2
//!
//! @return          NOD of a and b
//!
//! @note            NOD defined, if at least one of inputs isn't a zero.
//}=================================================================================
unsigned long NOD ( unsigned long a,
                    unsigned long b );

//{=================================================================================
//! NOK - calculation of least common multiple, based on NOD
//!
//! @param      a    Input 1
//! @param      b    Input 2
//!
//! @return          NOK of a and b
//}=================================================================================
unsigned long NOK ( unsigned long a,
                    unsigned long b );


int main () {
    unsigned long x = 1,
                  y = 1;
    
    bool isInputCorrect = false;
    printf ( "# Calculation of least common multiple, based on NOD\n"
             "# Author: Korablin S.\n" );
    while ( !isInputCorrect ) {
        printf ( "# Please, enter two natural numbers\n" );
        isInputCorrect = ( scanf ( "%lu %lu", &x, &y ) == 2 );
    }

    printf ( "#LCM of this numbers:\n"
             "%ld\n", NOK ( x, y ) );
    return 0; 
}

unsigned long NOD ( unsigned long a, unsigned long b ) {
    unsigned long c;
    while ( a != b ) {
        if ( a < b ) {
            c = a;
            a = b;
            b = c;
        }
        c = ( a - b ) / b;
        if ( c == 0 ) {
            c = 1;
        }
        a -= c * b;
    }

    return a;
}

unsigned long NOK ( unsigned long a, unsigned long b ) {
    return ( a * b ) / NOD ( a, b );
}

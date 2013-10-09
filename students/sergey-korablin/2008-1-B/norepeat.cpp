//{=================================================================================
//! @file    norepeat.cpp
//! @date    2013-10-09 21:15
//! @author  Sergey Korablin <ogneej@gmail.com>
//!
//! Deleting recurring numbers
//!
//! @par     Statement
//!          Deleting recurring numbers
//! @par     Input
//!          Number of numbers N[1..100000], after this - N natural numbers [1..MAXNUMBER]
//! @par     Output
//!          Non-recurring number(s) from the input, or -1 if none
//}=================================================================================

#include <stdio.h>

//! Maximal value of number of numbers in input
#define MAXNUMBER 1000

//! Public array of initial appearances of input numbers. [0] not used, it makes code more readable, but requires 1 bit more.
bool WasEntered [ MAXNUMBER + 1 ] = { 0 }; // Zero is 'false'. I use auto-initialization (all other items also will be 'false')

//! Public array of repeated numbers. [0] not used, same as above.
bool WasRepeated [ MAXNUMBER + 1 ] = { 0 }; // same as above

//{=================================================================================
//! GetInput - read input data and set up arrays WasEntered and WasRepeated
//!
//! @param      N    Number of numbers to read
//!
//! @return          0, if there was non-recurring number(s)
//!                  -1, if all number were recurring
//}=================================================================================
int GetInput ( int N );

//{=================================================================================
//! PrintAnswer - print non-recurring numbers, if exists, or -1 if none.
//!
//! @note         print -1, if none.
//}=================================================================================
void PrintAnswer ();


int main () {
    int N;
    bool InputIsCorrect = false;
    printf ( "# Deleting recurring numbers\n"
             "# Author: Korablin S.\n" );
    do {
        printf ( "# Please, enter number of input numbers (1..100000)\n" );
        InputIsCorrect = ( scanf ( "%d", &N ) == 1 );
    }
    while ( !InputIsCorrect );
    printf ( "# Please, enter %d natural numbers (each in 1..1000)\n", N );
    if ( GetInput ( N ) == 0 ) {
        printf ( "# Non-recurring numbers:\n" );
        PrintAnswer ();
    }
    else {
        printf ( "# There are no non-recurring numbers. Code:\n" );
        printf ( "-1\n" );
    }
    return 0;
}

int GetInput ( int N ) {
    int i = 0,
        inp = 1;
    int counter = 0;
    for ( i = 1; i <= N; i++ ) {
        scanf ( "%d", &inp );
        if ( !WasEntered [inp] ) {
            WasEntered [inp] = true;
            counter += 1;
        }
        else {
            if ( !WasRepeated [inp] ) {
                WasRepeated [inp] = true;
                counter -= 1;
            }
        }
    }
    return ( counter == 0 )?-1:0; //not sure that it looks great
}

void PrintAnswer ()
{
    int i;
    for ( i = 1; i <= MAXNUMBER + 1; i++ ) {
        if ( WasEntered [i] && !WasRepeated [i] )
            printf ( "%d ", i );
    }
    printf ( "\n" );
}

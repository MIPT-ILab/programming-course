//{=================================================================================
//! @file    summ.cpp
//! @date    2013-11-09 21:00
//! @author  Sergey Korablin <ogneej@gmail.com>
//!
//! Calculating sums on diagonals
//!
//! @par     Statement
//!          Calculating sums on diagonals
//! @par     Input
//!          Matrix size N[1..50], after this - N*N int numbers [-1000000..1000000]
//! @par     Output
//!          Sums on diagonals (2*N-1 int numbers)
//}=================================================================================

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

//{=================================================================================
//! CalcSums - read input data, calculate sums and fill sums array.
//!
//! @param      N    Number of columns and strings
//! @param      *s   Sums array (integer, must be at least 2*N-1)
//}=================================================================================
void CalcSums ( int N, int *s );

//{=================================================================================
//! PrintAnswer - print sums, if exists (2N-1).
//! @param      N    Number of columns and strings
//! @param      *s   Sums array (integer, must be at least 2*N-1)
//}=================================================================================
void PrintAnswer ( int N, int *s );


int main () {
    int N;
    bool InputIsCorrect = false;
    printf ( "# Calculating sums on diagonals\n"
             "# Author: Korablin S.\n" );
    do {
        printf ( "# Please, enter the size of matrix N*N (one natural number N)\n" );
        InputIsCorrect = ( scanf ( "%d", &N ) == 1 );
    }
    while ( !InputIsCorrect );
    int *s = ( int* ) malloc ( ( 2*N - 1) * sizeof ( int ) );
    assert ( s != NULL );
    printf ( "# Please, enter %d elements of matrix (%d columns, %d strings)\n", N*N, N, N );
    CalcSums ( N, s );
    printf ( "# Summs:\n" );
    PrintAnswer ( N, s );
    return 0;
}

void CalcSums ( int N, int *s ) {   
    assert ( s != NULL );
    int i = 0,
        j = 0,
        inp = 1;
    int sum = 0;
    int **m = ( int** ) malloc ( N * sizeof ( int* ) );
    assert (m != NULL);
    for ( i = 0; i < N; i++ ) {
        m[i] = ( int* ) malloc ( N * sizeof ( int ) );
        assert ( m[i] != NULL);
    }
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < N; j++ ) {
            scanf ( "%d", &inp );
            m[i][j] = inp;
        }
    }
    for ( i = 0; i < N; i++ ) {     //number of diagonal-1, below main with it
        sum = 0;        
        for ( j = 0; j <= i; j++ ) {
            sum += m[N - i + j - 1][j];
        }
        s[i] = sum;
    }
    for ( i = N; i < ( 2 * N - 1 ); i++ ) {     //number of diagonal-1, upper main without it
        sum = 0;        
        for ( j = 0; j < ( 2 * N - i - 1 ); j++) {
            sum += m[j][i - N + 1 + j];
        }
        s[i] = sum;
    }
    //i know, this code can't be named "readable"
    //how can I improve this?
}

void PrintAnswer ( int N, int *s)
{
    assert ( s != NULL );
    int i;
    for ( i = 0; i < (2*N - 1); i++ ) {
            printf ( "%d ", s[i] );
    }
    printf ( "\n" );
}

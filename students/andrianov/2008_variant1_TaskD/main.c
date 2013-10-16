//!{====================================================================================
//! @file   Var1TaskD2008.c
//! @date    2013-10-15 23:10
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Finding numbers of 	decomposition on summand with not more than one repetition of number
//!
//! @par The programme takes number
//!      It needs to output number of decomposition on summand with not more than one repetition
//!}====================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

long data[100][100];

long q2 ( int n, int k, long data[100][100] );

int main ()
{
    int n = 0,
        i = 0,
        j = 0;
    printf ( "#Enter a number\n" );
    scanf ( "%i", &n );
    for ( i = 0; i <= n; i++ )
    {
        for ( j = 0; j <= n; j++ )
        {
            assert ( 0 <= i && i <= n );
            assert ( 0 <= j && j <= n );
            data[i][j] = -2;
        }
    }
    q2 ( n, n, data );
    long result = data[n][n];
    printf ( "%i\n", result );
    printf ( "# is number of decompositions %i with not more than one repetition\n", n );
    return 0;
}

//!{============================================================================
//! q2          -      find number of decompositions
//!
//! @param      n      number
//! @param      k      number of summand
//! @param      data   array where calculated value of function are
//!
//! @return            numer of decompositions
//!}===================================================================================


long q2 ( int n, int k, long data[100][100] )
{
    if ( n < 0 || k < 0)
        {
            return 0;
        }
    if ( data[n][k] != -2 )
    {
        return data[n][k];
    }
    else
    {
        if ( n < 0 || k < 0 )
        {
            return 0;
        }
        else
        {
            if ( n == 0 )
            {
                data[n][k] = 1;
                return data[n][k];
            }
            else
            {
                if ( k == 0 )
                {
                    data[n][k] = 0;
                    return data[n][k];
                }
                else
                {
                    data[n][k] = q2 ( n - 2*k, k - 1, data ) + q2 ( n - k, k - 1, data ) + q2 ( n, k - 1, data );
                    return data[n][k];

                }
            }
        }
    }
}


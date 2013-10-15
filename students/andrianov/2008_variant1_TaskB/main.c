//!{====================================================================================
//! @file Var1TaskB.c
//! @date    2013-10-14 23:21
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Programm take sequence and output it without same elements
//!
//! @par The programme takes number of length of sequence and
//!      It needs to output number of roots
//!}====================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

int main ()
{
    long n = 0,
         k = 0,
         i = 0,
         j = 0;
    int* data;
    printf ("#Enter length of array\n");
    scanf ( "%i", &n );
    data = ( int* ) calloc ( n, sizeof ( int ) );
    assert ( data != NULL );
    printf( "#Enter elements of array\n" );
    for ( i = 0; i < n; i++)
    {
        scanf ( "%i", &data[i] );
    }

//! sorting of array in ascending order

    for ( i = 0; i < n - 1; i++ )
    {
        for ( j = 0; j < n - i - 1; j++ )
        {
            assert( j < n);
            assert( j + 1 < n);
            if ( data[j] > data [j + 1] )
            {
                k = data[j];
                data[j] = data[j+1];
                data[j+1] = k;
            }
        }
    }

//! printing not same elements

    for ( i = 0; i < n - 1; i++ )
    {
        if ( data[i] != data[i+1] )
        {
            printf ( "%i ", data[i] );
        }
    }
    printf ( "%i ", data[n-1] );
    return 0;
}

//!{====================================================================================
//! @file Var1TaskC2008.c
//! @date    2013-10-15 23:39
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Program opens file and deletes Streak-reaching spaces
//!
//! @par The programme takes file
//!}====================================================================================

#include <stdio.h>
#include <math.h>

char data[100000];

int main ()
{
    FILE *f;
    int i = 0,
        j = 0;
    char c1 = '0';

//! opening file

    f = fopen ( "filetext.txt", "r+" );
    c1 = fgetc ( f );
    i = 0;

//! reading all file

    while ( c1 != EOF )
    {
        data[i] = c1;
        i++;
        c1 = fgetc ( f );
    }
    close ( f );
    f = fopen ( "filetext.txt", "w+" );

//! inputing in file without Streak-reaching spaces

    for ( j = 0; j < i; j++ )
    {
        if ( data[j] == ' ' && data [j+1] == ' ')
        {

        }
        else
        {
            fputc ( data[j], f );
        }
    }
    close ( f );
    return 0;
}

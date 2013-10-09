/*************************************************************************************
* @file    prog2A.cpp
* @date    2013-10-06 19:00
* @author  Alex Nenashev <a.nenash95@gmail.com>
*
* Transponation of the table
*
* @version v1.1
*
* What's new in this version:
* - Doxygen texts
* - More good language
*
* @par     Program gets matrix and transponate it
*
*************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//-----------------------------------------------------------------------------------------
#define _EJC
//-----------------------------------------------------------------------------------------
#ifdef _EJC
    #define OUT printf
#else
    #define OUT if(0) printf
#endif

/** ******************************************************
* 20-string function main()
* 
* @par size       size of the table
* @par i, j       counters
* @par table[]    main work part - table
*
*********************************************************/

int main()
{
    int size = 0, i = 0, j = 0, table[2] = {};
    OUT("# Enter size of table: ");
    scanf("%d", &size);
    table = (int *)calloc(size, sizeof( int ));
    OUT("# Enter table of %d * %d:", size, size);
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            scanf("%d", &table[ i * size + j ]);
        }
    }
    OUT("# Transponated matrix:\n");
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d  ", table[ j * size + i ]);
        }
        printf("\n");
    }
    return 0;
}

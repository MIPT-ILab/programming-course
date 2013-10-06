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

int main()
{
    int size = 0, i = 0, j = 0, table[50][50];
    OUT("# Enter size of table: ");
    scanf("%d", &size);
    OUT("# Enter table of %d * %d:", size, size);
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            scanf("%d", &table[i][j]);
        }
    }
    OUT("# Transponated matrix:\n");
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d  ", table[j][i]);
        }
        printf("\n");
    }
    return 0;
}

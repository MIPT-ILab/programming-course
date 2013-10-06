/* Напишите программу, которая транспонирует введенную таблицу целых чисел
Формат ввода : В первой строке N - размер таблицы. В следующих N строках дано по N чисел, разделенных пробелом.
Формат вывода : Транспонированная таблица */

//{====================================================================================
//! @file V2_1.c
//! @date    2013-10-06 13:00
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Programm transpose matrix
//!
//! @par The programm enters size of matrix and matrix
//!      The programm outputs transpose of matrix
//}====================================================================================

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
    printf ("PROGRAM: TRANSPOSING\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER THE SIZE OF ARRAY\n");

    int n = 0, i = 0, j = 0, k = 0;
    scanf ("%d", &n);

    printf ("ENTER THE ARRAY\n");

    int **data;
    data = (int**) malloc(n * sizeof(int*));
    for (i = 0; i < n; ++i)
        data[i] = (int*) malloc(n * sizeof(int));
    for ( i = 0; i < n; i++)
        for ( j = 0; j < n; j++)
            scanf ("%d", &data[i][j]);
    i = 0;
    j = 0;
    while ( i < n)
        {
        while ( j < i)
            {
                 k = data[j][i];
                 data[j][i] = data[i][j];
                 data[i][j] = k;
                 j++;
            }
       j = 0;
       i++;
       }
    printf ("TRANSPOSED ARRAY\n");
    for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
                printf ("%d ", data[i][j]);
            printf("\n");
        }

    free (data);
    printf ("\n");
    return 0;
}

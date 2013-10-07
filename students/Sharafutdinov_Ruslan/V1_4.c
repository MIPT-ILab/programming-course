/* �������� ���������, ������� ������� ������� ����� b(n,k) (0 <= n, k <= N),
��� b(n,k) ���� ���������� �������� ���� ����� n, � ������� ����� k ������ � ��� ���� ������ ������ ������.
������ �����. ����� ����� N, 0 <= N < 48.
������ ������ . �������� N+1 ������. ������ � ������� n (n = 0,1,2...,N) �������� �����
b(n,0), b(n,1), ... �� ���������� ���������� ����� ������������ */

//{====================================================================================
//! @file V1_4.c
//! @date    2013-10-06 16:03
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Finding numbers of binary sequence, where there are no
//! two following units
//!
//! @par The programme enters number
//!      It needs to output n+1 strings with number b(n,k)
//!      there n - length of sequence
//!            k - number of units
//}====================================================================================


#include <stdio.h>
#include <math.h>

int main ()
{
    int n = 0, i = 0, j =0, k = 0;
    long long C[100][500];

    printf ("PROGRAM: GOOD NUMBERS\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER THE NUMBER\n");
    scanf ("%d", &n);

    for ( i = 0; i <= 50; ++i)
        C[i][0] = 1;
    for ( i = 0; i <= 50; ++i)
        for ( j = 1; j <= 499 ; ++j)
            C[i][j] = 0;
   for( i = 1; i <= 50; ++i)
        for( j = 1; j <= i; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    for( i = 0; i <= n;  i++)
   {
       for( k=0; k <= i && i-k+1 >= k; k++)
            printf("%ld ", C[i - k + 1][k]);
       printf ("\n");
   }
return 0;
}

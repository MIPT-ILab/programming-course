//{====================================================================================
//! @file V2_2.c
//! @date    2013-10-06 16:06
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Programm simplifies root of number
//!
//! @par The programm number
//!      The programm outputs number of the rational part
//!                       and numger of the irrational part
//}====================================================================================

#include <stdio.h>
#include <math.h>

int check ( int i);
int normalization_of_the_root_coefficient_a (int n);
int normalization_of_the_root_coefficient_b (int n);

int main()
{
    printf ("PROGRAM: NORMALIZATION OF THE ROOT\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER N\n");

    int n = 0, a = 0 , b = 0;
    scanf ("%d", &n);
    a = normalization_of_the_root_coefficient_a(n);
    b = normalization_of_the_root_coefficient_b(n);

    printf ("COEFFICIENT A = %d\n", a);
    printf ("COEFFICIENT B = %d\n", b);
    return 0;

}
//! check - determine is number square of another number or not
//!
//! @param      i   number
//!
//! @return         1 - if number is square of other number
//!                 0 - if number is not square of other number
int check ( int i)
{
    int p = 1;
    for ( p = 2; p <= sqrt (i); ++p)
        if (i % p == 0)
            return 1;
    return 0;
}
//!  normalization_of_the_root_coefficient_b - determine the coefficient b
//! @param      n   number
//!
//! @return        b -  the coefficient b
int normalization_of_the_root_coefficient_b (int n)
{
    int i = 0, b = 1;

    for ( i = 1; i <= sqrt(n); ++i)
    {

        if ( (n % (i * i)) == 0  && check(i) == 0)
            b = b * i;
    }

    return b;
}
//!  normalization_of_the_root_coefficient_b - determine the coefficient a
//! @param      n   number
//!
//! @return        a -  the coefficient a
int normalization_of_the_root_coefficient_a (int n)
{
    int a = 0;
    a = n / (normalization_of_the_root_coefficient_b(n) * normalization_of_the_root_coefficient_b(n));
    return a;
}


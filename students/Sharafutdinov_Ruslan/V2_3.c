//{====================================================================================
//! @file Var2taskCotv.c
//! @date    2013-09-29 21:20
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Programm calculate prime number with number N
//!
//! @par The programm inputs number
//!      The programm outputs N-th prime number
//}====================================================================================

#include <stdio.h>
#include <math.h>

long int Search_prime_number (int n);
int prime (int i);

int main()
{
    printf ("PROGRAM: SEARCH N-th PRIME NUMBER\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER N\n");

    int n = 0;
    long int prime_number = 0;
    scanf("%d", &n);
    prime_number = Search_prime_number (n);
    printf ("%d-th PRIME NUMBER IS: %ld\n", n, prime_number);
    return 0;
}

//! Search_prime_number -  calculate N-th prime number
//!
//! @param      n   number
//!
//! @return     i - 1  N-th prime number

long int Search_prime_number (int n)
{
    int counter = 0, i = 2;
    while (counter < n)
        {
            if (prime (i) == 0)
                counter++;
            i++;
        }
    return i - 1;
}

//! prime - determines whether a number is prime
//! @param      i   number
//!
//! @return     0  if number is prime
//!             1 if  number is not prime

int prime (int i)
{
    int j = 0;
    for ( j = 2; j <= sqrt (i); j++)
        if (i % j == 0)
            return 1;
    return 0;
}

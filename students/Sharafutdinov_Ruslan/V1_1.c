//{=================================================================================
//! @file    V1_1.c
//! @date    2013-6-10 12:18
//! @author  Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Finding prime numbers in a string of numbers.
//!
//}=================================================================================

# include <stdio.h>
# include <math.h>

int prime ( int number);

int main()
{
    int n = 0, i = 1 , number = 0;

    printf ("PROGRAM: SEARCH FOR PRIME NUMBERS\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.1 \n");
    printf ("ENTER THE AMOUNT NUMBERS\n");
    scanf ("%ld",& n);
    printf ("ENTER %ld NUMBERS\n",  n);

    for ( i = 1; i <= n; ++i )
    {
        scanf ("%ld", &number);
        if (prime(number)) printf("%ld ",number);
        number = 0;
    }

    return 0;
}

//! prime - determine is number prime or not prime
//!
//! @param   number   number
//!
//! @return  1 - if number is prime
//!          0 - if number is not prime

int prime( int number)
{

    int i = 2;
    double sq_number = sqrt(number);
    if (number == 1)
        return 0;
    for ( i = 2; i <= sq_number; ++i)
        if ( number % i == 0) return 0;
    return 1;
}

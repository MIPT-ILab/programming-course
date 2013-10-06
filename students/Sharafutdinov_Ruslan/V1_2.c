//{====================================================================================
//! @file V1_2.c
//! @date    2013-10-06 15:53
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Finding squares among divisors of number
//!
//! @par The programme enters number
//!      It needs to output YES if there are squares among divisors of number
//!                          NO if there are no squares among divisors of number
//}====================================================================================

# include <stdio.h>
# include <math.h>

int SquareDivider ( int number);

int main ()
{
    int number = 0;

    printf ("PROGRAM: FINDING THE SQUARE DIVIDER\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER THE NUMBER\n");
    scanf ("%d", &number);

    if (SquareDivider(number))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;

}
//! SquareDivider - determine are there any squares among divisors of number
//!
//! @param      number   number
//!
//! @return         1 - if there are sqaures among divisors of number
//!                 0 - if there aren't any sqaures among divisors of number

int SquareDivider ( int number)
{
    int i = 0;
    double sqrt_number = sqrt(number);
    for ( i = 2; i <= sqrt_number; ++i  )
    {
        if ( number % (i*i) == 0) return 1;
    }
    return 0;
}

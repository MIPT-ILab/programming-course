//{====================================================================================
//! @file V2_4.c
//! @date    2013-10-06 15:37
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Programm calculate number of decomposition of has not repeated numbers
//!
//! @par The programm enters number
//!      The programm outputs number of decomposition
//}====================================================================================

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int decomposition(int a, int b);


int main()
{
    int number = 0, nDecomp = 0;
    printf("ENTER THE NUMBER\n");
    scanf("%d", &number);
    nDecomp = decomposition(number , number);
    printf("%d IS A NUMBER OF DECOMPOSITION OF %d", nDecomp, number);
    return 0;
}

//! decomposition - calculate number of decomposition number n on not repeated numbers
//!                 all of them smaller or equal then k
//!
//! @param      n  number
//! @param      k   number
//!
//! @return         number of decomposition


int decomposition(int n, int k)
{
    if (k <= 0)
        return 0;
    else

        if ((n == 0) || (n == 1))
            return 1;

        else
            if (n > 0)
                return decomposition(n-k, k-1) + decomposition(n, k-1);
            else
                return 0;
}

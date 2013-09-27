//{=================================================================================
//! @file    a1.cpp
//! @date    2013-09-28 00:48
//! @author  Anton Samsonov <Fivapr...@inbox.ru>
//!
//! @mainpage   Hello! This is documentation for control 2007.
//!             You'd better check warning.
//!
//! Program checking if number is prime
//!
//! @par    Program gets n numbers (n < 10000).             \
            Check if they are prime (each number < 100000). \
            Output prime ones in the order they were input.
//!
//! @note   Version 0.1
//!         - Added OUT    (ifdef _EJC).
//!         - Added ASSERT (ifdef DEBUG).
//!         - Added is_prime (a) function.
//!         - First aim of program is succeed
//!
//! @todo   - Long arithmetic for is_prime (a)
//!         - Change some assert's to if's
//!
//! @warning  Keep calm and do science!
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _EJC
    #define OUT printf
#else
    #define OUT if(0) printf
#endif //!< Macro for ejudge system.
//----------------------------------------
#define DEBUG
//----------------------------------------

#ifdef DEBUG
    #define ASSERT( cond )                          \
    if (!(cond)) {                                  \
        fprintf (stderr, "# Assertion fail : %s."   \
                        "File %s, line %d\n",       \
                        #cond, __FILE__, __LINE__); \
        abort();                                    \
    }
#else
    #define ASSERT( cond )
#endif //!< ASSERT is active only when DEBUG is defined.

//! we can use 0.000001, because sqrt(100000) - sqrt(99999) >> 0.000001
const double EPSILON = 0.e-6;

int is_prime (int a);

int main()
{
    OUT ("# This is %s. It's compiled %s %s by Anton Samsonov\n", __FILE__, __DATE__, __TIME__);

//! amount of input numbers
    int n = 0;
    OUT ("# Input an amount of numbers you will enter.\n");

//! checking scanf return
    int scanf_ret = scanf("%d", &n);
    ASSERT (scanf_ret == 1);
    if (n <= 0) { OUT ("# Amount of numbers must be positive.\n"); return 1; }

    OUT ("OK, now enter %d number%s.\n", n, (n == 1)? "" : "s");
    int scanned = 0; //!< scanned number
    int i = 0; //!< counter

    scanf_ret = scanf("%d", &scanned);
    ASSERT (scanf_ret == 1);
    OUT ("# Here are prime ones:\n");
    if (is_prime (scanned)) {
        printf("%d ", scanned);
    }

    for (i = 1; i < n; i ++) {
        scanf_ret = scanf("%d", &scanned);
        ASSERT (scanf_ret == 1);

        if (is_prime (scanned)) {
            printf("%d ", scanned);
        }
    }
    printf ("\n");

    return 0;
}

/**
    is_prime - checking if number is prime or not.

    @param    a    Number

    @return        1 if a is prime, 0 if not.

    @note          It doesn.t work for long arithmetic
**/

int is_prime (int a)
{
//! we store value of sqrt (a) to save time.
    double sqrt_val = sqrt (a) + EPSILON;

//! It works 2 times faster if we check only odd counter values.\
    That's why we need to check these values of a.
    if (a == 1)     return 0;
    if (a == 2)     return 1;
    if (a % 2 == 0) return 0;

    int i = 0; //!< counter
    for (i = 3; i < sqrt_val; i += 2) {
        if (a % i == 0) return 0;
    }

    return 1;
}

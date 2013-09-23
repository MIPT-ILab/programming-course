//{=================================================================================
//! @file    solve_square.cpp
//! @date    2013-09-22 23:00
//! @author  Anton Samsonov <Fi...@inbox.ru>
//!
//! Program finding solutions of square (linear) equation.
//!
//! @par     Parametres of task
//!          Program gets 3 coefficients of square equation. Need to output
//!          amount of equation roots (-1 whether it's infinite) and roots themselves.
//!
//! @warning Keep calm and do science!
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>

const int SS_INFINITE_ROOTS = -1; //!< Value solve_square returns if it has infinite roots.

const int SS_EPIC_FAIL      =  3; //!< Value solve_square shouldn't return.

/** ********************************************************************************
 *  is_zero - checking if a is equal to 0 or not.
 *
 *  @param      a   Number
 *
 *  @return         1 if a is equal to 0, 0 if not.
 *
 *  @note           Calculation precision is considered to be DBL_EPSILON.
 ***********************************************************************************/
int is_zero (double a);

/** ********************************************************************************
 *  solve_square - solve a square or linear equation specified by its coefficients.
 *
 *  @param      a   Equation a-coefficient
 *  @param      b   Equation b-coefficient
 *  @param      c   Equation c-coefficient
 *  @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
 *  @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
 *
 *  @return         Number of roots or zero if none, -1 if infinite number of roots, 3 if smthing failed.
 *
 *  @note           Calculation precision is considered to be DBL_EPSILON.
 ***********************************************************************************/
int solve_square (double a, double b, double c, double *x1, double *x2);

int main ()
{
    double a = 0, b = 0, c = 0;

    printf ("# Put a, b and c from ax^2 + bx + c in.\n");
    int scanned = scanf ("%lg %lg %lg", &a, &b, &c);
    if (scanned < 3) return printf ("Input is not valid.\n"), 1;

    double x1 = 0, x2 = 0;
    int nRoots = solve_square (a, b, c, &x1, &x2);

    // Return check block.

    switch (nRoots) {
        case  2: printf ("# Number of different roots:\n%d\n# Roots of equal:\n%.3lg %.3lg\n", nRoots, x1, x2);  break;
        case  1: printf ("# Number of different roots:\n%d\n# Roots of equal:\n%.3lg\n", nRoots, x1);            break;
        case  0: printf ("%d\n# This equal has no roots in R set.\n", nRoots);                                   break;
        case -1: printf ("%d\n# This equal has infinite number of roots.\n", nRoots);                            break;
        default: printf ("# ERROR! Undocumented return: %d!\n", nRoots);                                         return 1;
    }

    return 0; //...
}

int solve_square(double a, double b, double c, double *x1, double *x2)
{
    assert(x1); assert(x2); assert(x1 != x2);  // <<< Pre-condition.

    double d = b*b - 4*a*c;

    if (is_zero (a)) { // If it's linear equation (а = 0).

        /* bx + c = 0; bx = -c; x = -c/ b*/
        if      (is_zero (b) && !is_zero (c)) return 0;                 // No roots in R.
        else if (is_zero (b) &&  is_zero (c)) return SS_INFINITE_ROOTS; // Root - any number in R.
        else {
            *x1 = (-c / b);
            return 1; // One root.
        }
    }
    else {
        if (d > DBL_EPSILON) { // Discriminant > 0.
            d = sqrt(d);
            *x1 = (-b - d) / (2 * a);
            *x2 = (-b + d) / (2 * a);
            return 2; // Two roots *Das ist fantastisch!*.
        }
        else if (is_zero (d)) { // Discriminant = 0.
            *x1 = (-b / (2 * a));
            return 1; // One root.
        }
        else { return 0; } // No roots in R.
    }
    return SS_EPIC_FAIL; // Undocumented fail in function.
}

int is_zero (double a)
{
    return !!(fabs (a) < DBL_EPSILON);
}

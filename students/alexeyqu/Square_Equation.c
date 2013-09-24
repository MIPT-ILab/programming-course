/** **********************************************************************************
 * @file    main.c
 * @date    2013-09-23 08:30
 * @author  Alexey Kulikov <alexeyqu@gmail.com>
 *
 * Solve a quadratic equation considering particular cases
 *
 * @par     Task.
 *          The program gets 3 coefficients of a quadratic equation
 *          and prints number of roots (-1 if infinite) and roots themselves.
 *
 * @warning Do not enter invalid set of coefficients!
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define _EJC

#ifdef _EJC
#define DBG printf ("# ");
#else
#define DBG if (0)
#endif

#define ASSERT(cond)                                            \
if (!cond) {printf ("Critical failure in assertion '%s', file %s, line %d!\n"\
, #cond, __FILE__, __LINE__);                                   \
abort();}

const double EPS = 0.00001; //!< Value equal to zero while comparing double numbers
const int SS_INFINITE_ROOTS = -1; //!< Value returned by SolveSquare function if number of roots is infinite

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2);

int main()
{
    double a = 0, b = 0, c = 0;
    DBG printf ("a*x^2 + b*x + c = 0 \n# Enter a, b, c: \n");
    DBG printf ("a = ");
    int resa = scanf ("%lg", &a);
    DBG printf ("b = ");
    int resb = scanf ("%lg", &b);
    DBG printf ("c = ");
    int resc = scanf ("%lg", &c);
    ASSERT (resa); ASSERT (resb); ASSERT (resc);

    double x1 = 0, x2 = 0;
    int NRoots = SolveSquare (a, b, c, &x1, &x2);

    DBG printf ("Number of roots: \n");
    printf ("%d\n", NRoots);
    if (NRoots == -1) {DBG printf ("The equation is invalid.\n");}
    if (NRoots == 1) {DBG printf ("x1 =\n"); printf ("%lg\n", x1);}
    if (NRoots == 2) {DBG printf ("x1, x2 = \n"); printf ("%lg %lg\n", x1, x2);}

    return 0;
}

/** ********************************************************************************
 * SolveSquare - solve a quadratic or linear equation specified by its coefficients.
 *
 * @param      a   Equation a-coefficient
 * @param      b   Equation b-coefficient
 * @param      c   Equation c-coefficient
 * @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
 * @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
 *
 * @return         Number of roots or zero if none, -1 if infinite number of roots or invalid equation
 *
 * @note           Calculation precision is considered to be EPS.
************************************************************************************/
int SolveSquare (double a, double b, double c,
                 double* x1, double* x2)
{
    ASSERT (x1); ASSERT (x2);
    ASSERT ((x1 != x2));

    if (fabs (a) <= EPS && fabs (b) <= EPS)
    {
        if (fabs (c) <= EPS) {DBG printf ("0 = 0. The equation lacks numerical stability. \n");}
        else DBG printf ("0 != 0. Invalid equation. \n");

        return -1;
    }

    if (fabs (a) <= EPS)
    {
        DBG printf ("Linear equation. \n");
        DBG printf ("x*%lg + %lg = 0 \n", b, c);

        *x1 = (double) -c/b;

        return 1;
    }

    DBG printf ("Quadratic equation. \n");
    DBG printf ("%lg*x^2 + %lg*x + %lg = 0 \n", a, b, c);

    double D = b*b - 4*a*c;

    if (D < 0)
    {
        DBG printf ("Discriminant is negative. 0 real roots. \n");
        return 0;
    }

    if (fabs (D) <= EPS)
    {
        DBG printf ("Discriminant = 0. 1 real root. \n");

        *x1 = (double) -b/2*a;

        return 1;
    }

    DBG printf ("Discriminant is positive. 2 real roots. \n");

    *x1 = (double) (-b + sqrt (D))/(2*a);
    *x2 = (double) (-b - sqrt (D))/(2*a);

    return 2;
}

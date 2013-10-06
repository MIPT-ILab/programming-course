/** **********************************************************************************
 * @file    Square_Equations.c
 * @mainpage
 * @date    2013-09-28 00:50
 * @author  Alexey Kulikov <alexeyqu@gmail.com>, group 376, DCAM MIPT
 * @version 1.031
 *
 * @note    V1.00:
 *          - added SolveSquare() function
 *          - added some debug prints
 *          - gets 3 coefficients, prints number of solutions and roots themselves.
 *
 * @note    V1.01
 *          - added standart assert check of correct input and variables
 *          - double values are comparing with defined EPS instead of zero
 *
 * @note    V1.02
 *          - added Doxygen comments
 *          - added preprocessor commands support
 *          -- realised full-functional ASSERT macros
 *          -- added optional extra debug user-friendly output conrolled by flag _EJC
 *             (if defined, then debug mode is on and program prints debug info
 *             automatically precessed by '#' at the beginning of each line)
 *
 * @par     V1.03
 *          - updated Doxygen comments
 *          - added inline functions comparing double value with zero
 *            (is_zero, above_zero, below_zero)
 *
 * @par     V1.031
 *          - style of define flags determinig ASSERT is standart now
 *          - gcc doesn't allow to use constants in cases, does it? For now, define is used.
 *
 * Solve a quadratic equation considering particular cases.
 *
 * @par     Task.
 *          The program gets 3 coefficients of a quadratic equation,
 *          determines the type of the equation, solves it
 *          and prints number of solutions (-1 if infinite) and roots themselves.
 *
 * @warning Do not enter invalid set of coefficients!
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define SS_INVALID_EQUATION -1 //!< @def Value returned by SolveSquare function if number of roots is infinite

#ifndef NDEBUG
    #define DBG printf ("# "),
    #define ASSERT(cond)                                                            \
    if (!cond)                                                                      \
    {                                                                               \
        printf ("Critical failure in assertion '%s'! \nfile %s, line %d \n"         \
                "Now keep calm and EXTERMINATE! EXTERMINATE! EXTERMINATE!!!\n"      \
                , #cond, __FILE__, __LINE__);                                           \
        abort();                                                                        \
    }
#else
    #define DBG if (0)
    #define ASSERT(cond)
#endif

/** ********************************************************************************
 * SolveSquare - solves a quadratic or linear equation specified by its coefficients.
 *
 * @param      a   Equation a-coefficient
 * @param      b   Equation b-coefficient
 * @param      c   Equation c-coefficient
 * @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
 * @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
 *
 * @return         Number of roots or zero if none, -1 if infinite number of roots or equation is invalid
 *
 * @note           Calculation precision is considered to be DBL_EPSILON.
************************************************************************************/
int SolveSquare (double a, double b, double c,
                 double* x1, double* x2);

inline int is_zero (double x);
inline int above_zero (double x);
inline int below_zero (double x);

/** **********************************************************************************
 * main - gets coefficients, checks input, prints answers.
 *
 * @return main: solves an equation with factors given. Returns 1 in case of error, otherwise returns 0.
**************************************************************************************/
int main()
{
    double a = 0, b = 0, c = 0; //!< Coefficients of an equation
    int resa = 0, resb = 0, resc = 0; //!< Correct input flags

    DBG printf ("a*x^2 + b*x + c = 0 \n# Enter a, b, c: \n");
    DBG printf ("a = ");
    resa = scanf ("%lg", &a);
    DBG printf ("b = ");
    resb = scanf ("%lg", &b);
    DBG printf ("c = ");
    resc = scanf ("%lg", &c);
    ASSERT (resa); ASSERT (resb); ASSERT (resc);

    double x1 = 0, x2 = 0; //!< Roots of an equation
    int NRoots = SolveSquare (a, b, c, &x1, &x2); //!< Number of roots

    DBG printf ("Number of roots: \n");
    printf ("%d\n", NRoots);

    switch (NRoots)
    {
        case 2: DBG printf ("x1, x2 = \n"); printf ("%lg %lg\n", x1, x2);         break;
        case 1: DBG printf ("x1 =\n"); printf ("%lg\n", x1);                      break;
        case 0:                                                                   break;
        case SS_INVALID_EQUATION: DBG printf ("The equation is invalid.\n");      break;
        default: DBG printf ("Error! Undocumented return value (%d)!\n", NRoots); return 1;
    }

    return 0;
}

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2)
{
    ASSERT (x1); ASSERT (x2);
    ASSERT ((x1 != x2));

    if (is_zero (a) && is_zero (b))
    {
        if (is_zero (c)) {DBG printf ("0 = 0. The equation lacks numerical stability. \n");}
        else DBG printf ("0 != 0. Invalid equation. \n");

        return SS_INVALID_EQUATION;
    }

    if (is_zero (a))
    {
        DBG printf ("Linear equation. \n");
        DBG printf ("x*%lg + %lg = 0 \n", b, c);

        *x1 = (double) -c/b;

        return 1;
    }

    DBG printf ("Quadratic equation. \n");
    DBG printf ("%lg*x^2 + %lg*x + %lg = 0 \n", a, b, c);

    double D = b*b - 4*a*c;

    if (below_zero (D))
    {
        DBG printf ("Discriminant is negative. 0 real roots. \n");
        return 0;
    }

    if (is_zero (D))
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

inline int is_zero (double x)
{
    return (fabs (x) <= DBL_EPSILON)? 1 : 0;
}

inline int above_zero (double x)
{
    return (x > DBL_EPSILON)? 1 : 0;
}

inline int below_zero (double x)
{
    return (x < -DBL_EPSILON)? 1 : 0;
}

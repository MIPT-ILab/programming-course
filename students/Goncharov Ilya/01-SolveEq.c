//{=================================================================================
//! @file    01-SolveEq.c
//! @date    2013-10-18 23:46
//! @author  Ilya Goncharov <ilgonmic@gmail.ru>
//!
//! Solving square equation
//!
//! @par     Conditions
//!          Program enter 3 coefficients of square equation.
//!          It return all roots of equation, and if equation
//!          hasn't got roots, program return message.
//}=================================================================================

#include <stdio.h>
#include <math.h>

int kolvoResheniy (double a, double b, double c, double* x1, double* x2);

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    printf("# Please, enter coefficients of square equation\n");
    scanf("%lg %lg %lg", &a, &b, &c);
        switch (kolvoResheniy(a, b, c, &x1, &x2))
        {
            case 0: printf("# This equation hasn't got roots\n");
                break;
            case 1: printf("# One root\nx = %lg\n", x1);
                break;
            case 2: printf("# Two roots\nx1 = %lg\nx2 = %lg\n", x1, x2);
                break;
            case -1: printf("# This equation has infinite count of roots\n");
                break;
            default: printf("# Something went wrong!");
                break;
        }

    return 0;
}

//{=================================================================================
//! KolvoResheniy - solve a square or linear equation specified by its coefficients.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist
//! @param[out] x2  2nd root of equation, if exist
//!
//! @return         Number of roots or zero if none, -1 if infinite number of roots
//!
//! @note           Calculation precision is considered to be DBL_EPSILON.
//}=================================================================================

int kolvoResheniy (double a, double b, double c, double* x1, double* x2)
{
    //! need for compare with 0
    const double EPSILON = 0.00000001;
    //! Discriminant
    double D = 0;

    if ( a != 0 )
    {
        D = b*b - 4*a*c;

        if ( ( D < EPSILON ) && ( D > -EPSILON))
        {
            if ( b != 0)
                *x1 = -b/(2*a);
            else
                *x1 = 0;
            return 1;
        }
        else if ( D > EPSILON )
        {
            *x1 = (-b+sqrt(D))/(2*a);
            *x2 = (-b-sqrt(D))/(2*a);
            return 2;
        }

        else
        {
            return 0;
        }
    }
    else
    {
        if ( b != 0 )
        {
            if( c != 0)
                *x1 = -c/b;
            else
                *x1 = 0;
            return 1;
        }
        else
        {
            if ( c != 0 )
            {
                return 0;
            }
            else
                return -1;
        }
    }
}

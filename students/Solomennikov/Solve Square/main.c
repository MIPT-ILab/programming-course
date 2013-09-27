//{=================================================================================
//! @file    Solve Square.cpp
//! @date    2013-09-25 20:09
//! @author  Solomennikov Semen, 999solom.s.v.999@gmail.com
//!
//! The solution of a quadratic equation with an honest analysis of particular cases.
//!
//! @par     Condition of the task:
//!          We enter 3 coefficients of the square equation. Program should print
//!          the number of solutions and roots. (-1 whether it's infinite) and roots.
//!
//! @warning Math!
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//Input the function which will calculate our equation.
int calc(double a, double b, double c, double *x1, double *x2);

//Input the main function.
int main()
{
    //Input all variables and constants.
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int NOS;                                                              //Number Of Solutions.

    printf("# Vvedite koefficienti kvadratnogo uravneniya (a, b, c):\n"); // Enter coefficients
    scanf("%lg %lg %lg", &a, &b, &c);                                     // of the square equation.

    //We call the function 'calc'.
    NOS = calc (a, b , c, &x1, &x2);

    switch (NOS)
    {
        case -1 : printf("# Beskonechnoe mnozhestvo resheniy\n");                         break;
        case 0  : printf("# Uravnenie ne imeet resheniy");                                break;
        case 1  : printf("# Kol-vo resheniy:\n%i\n# Korni:\n%lg", NOS, x1);               break;
        case 2  : printf("# Kol-vo resheniy:\n%i\n# Korni:\n%lg %lg", NOS, x1, x2);       break;
        default : printf("# ERROR!!!");                                                   return 0;
    }
     return 0;
}

//{============================================================================================
//!SolveSquare - solve a square or linear equation specified by its coefficients.

//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
//!
//! @return         Number of roots or zero if none, -1 if infinite number of roots

//}============================================================================================


//Input the function which will calculate our equation.
int calc(double a, double b, double c, double *x1, double *x2)
{
    double D = pow(b,2) - 4*a*c;

    // First, we check whether the coefficients are equal to zero.If it is, the equation hasn`t solutions.
    if (a == 0 & b == 0 & c == 0)
    return -1;

    //Check, if the 'a' and 'b' aren`t equal to zero. Equation like: ax^2 + bx + c = 0 (c can be equal to zero). So there is two solutions (Unless D != 0).
    if (b != 0 & a != 0 & D >= 0)
    {
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = (-b - sqrt(D))/(2*a);

        if (*x1 == *x2)
        return 1;

        else
        return 2;
    }

    //Then, we can see equation: ax^2 + c = 0. So there is two solutions (Unless X != 0).
    if (a != 0 & b == 0)
    {
        if (c > 0)
        return 0;

        else
        {
        *x1 =  sqrt (-c/a);
        *x2 = -sqrt (-c/a);

        if (*x1 == 0)
        return 1;

        else
        return 2;
        }
    }

    //Equation like:bx + c = 0. So there is one solution.
    if (a == 0 & b != 0)
    {
        *x1 = (-c)/b;
        return 1;
    }

    //If diskriminant of the equation like:ax^2 + bx + c = 0, is equal to zero. So there isn`t solutions.
    if (D < 0)
    return 0;
}
//One question: programm outputs -0 instead of 0. Why?

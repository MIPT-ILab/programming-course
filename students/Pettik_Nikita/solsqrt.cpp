//{===================================================================================
//! @file    solsqrt.cpp
//! @date    2013-10-03 23:40
//! @author  Nikita Pettik 377 group  <kitnerh@gmail.com>
//! @version 1.1
//!
//! Solution of the square equation
//!
//! @par     Condition of the problem
//!
//! The program needs to enter three coefficients of the quadratic equation.
//! The program prints the roots of equation.
//!
//}===================================================================================



#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>


#define ASSERT( cond )                \
    {                                 \
    if (!(cond))                      \
        {                             \
        printf ("%s is false!, "  \
                "file %s, line %d\n", \
                #cond,                \
                __FILE__,__LINE__);   \
       abort();                       \
       }                              \
    }



//! The value returned SolveSquare in the case of infinitely many roots.

const int SS_INTINITE_ROOTS = -1;

//! Very small constant to compare variables of type "double" with zero.
const double EPS = 1e-9;

//{===================================================================================
//! SolveSquare - solve a square or linear equation specified by its coefficients.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
//!
//! @return         Number of roots or zero if none, -1 if infinite number of roots
//!
//! @note           Calculation precision is considered to be DBL_EPSILON.
//}===================================================================================

int SolveSquare (double a, double b, double c, double *x1, double *x2);

//{===================================================================================
//! iszero - function compares the variable of type "double" with zero
//!
//! @return  it returns 0 if the absolute value of the  parameter is less then epsilon
//!          otherwise returns 1
//}===================================================================================

int iszero (double c);

int main()
{

 	double a=0, b=0, c=0;
 	double x1 = 0, x2 = 0;
 	printf ("#Enter the coefficients of the quadratic equation ax^2+bx+c=0\n");
 	int ret = scanf ("%lg %lg %lg", &a, &b, &c);
    if (ret < 3) return printf("#ERROR: Input is not correct!");

 	int nRoots=SolveSquare(a, b, c, &x1, &x2);
    switch (nRoots)
    {
	 	 case 0 : printf("#The equation has no solution");break;
	 	 case 1 : printf("#Root of the quadratic equation is x=%lg", x1);break;
	 	 case 2 : printf("#Roots of the quadratic equation are x=%lg and x=%lg",x1,x2);break;
	 	 case SS_INTINITE_ROOTS : printf("#The equation has an infinite number of roots");break;
	 	 default : printf("#Unexpected return of SolveSquare(): %d", nRoots);
    }
 	system("Pause");
 	return 0;
}


int iszero (double c)
{
 	return(fabs (c) < EPS);
}


int SolveSquare (double a, double b, double c, double *x1, double *x2)
{

 	ASSERT (x1 != NULL);           /*Verification of address variables*/
 	ASSERT (x2 != NULL);
 	ASSERT (x1 != x2);


 	if (iszero(a) && iszero(b) &&  iszero(c)) return SS_INTINITE_ROOTS;

 	if (iszero(a) && iszero(b) && !iszero(c)) return 0;

 	if (iszero(a))
 	{
		*x1 = c / (-b);
		return 1;
    }
    double discr = b*b - 4*a*c;
    if (iszero(discr))
    {
	 	 *x1 = -b / (2 * a);
	 	 return 1;
    }
    if (discr < EPS) return 0;
    else
    {
	 	*x1 = (- b + sqrt(discr)) / (2 * a);
		*x2 = (- b - sqrt(discr)) / (2 * a);
		return 2;
    }
    return 4;
}





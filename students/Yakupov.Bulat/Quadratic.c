//{=================================================================================
//! @file    Quadratic.cpp
//! @date    2013-09-22 21:01
//! @author  Yakupov Bulat <yakupov.bulat@gmail.com> 313 group DREC MIPT
//!
//! Program solves quadratic equation and makes out particualar cases.
//!
//! @par     Condition of the problem
//!			 Program enters 3 coefficients of quadratic. The roots and the their
//!			 number should be printed (-1 if it is infinitly).  
//}=================================================================================
#include <stdio.h>
#include <math.h>
#include <assert.h>
//{=================================================================================
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
//}=================================================================================
int SolveQuadratic(double a, double b, double c, double* x1, double* x2);
int main ()
{
	printf ("Here you can see program which solves quadratic equation. Type coefficients and the free term a, b, c separated by space\n");
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	scanf ("%lg %lg %lg", &a, &b, &c);
	int nRoots = SolveQuadratic(a, b, c, &x1, &x2);
	if (nRoots == 2)
		printf ("There are %d solutions:\n x1 = %lg \n x2 = %lg\n", nRoots, x1, x2);
	if (nRoots == 1)
		printf ("There is %d solution: \n x = %lg\n", nRoots, x1);
	if (nRoots == 0)
		printf ("There is not any solution.\n");
	return 0;
	if (nRoots == -1)
		printf ("The number of roots is infinitly.");
}
int SolveQuadratic(double a, double b, double c, double* x1, double* x2)
{
	assert (x1 != NULL);
	assert (x2);
	assert (x1 != x2);
	if ((a == 0) && (c == 0) && (b == 0))
		return -1;
	if (a == 0)
	{
		*x1 = (-1)* c / b;
		return 1;
	}
	if ((a == 0) && (b == 0) && (c != 0))
		return 0;
	double D = 0;								// D is discriminant;
	if ((D = b * b - 4 * a * c) > 0)
	{
		*x1 = ((-1) * b + sqrt(D)) / (2 * a);
		*x2 = ((-1) * b - sqrt(D)) / (2 * a);
		return 2;
	}
	if (D == 0)
	{
		*x1 = (-1) * b / (2 * a);
		return 1;
	}
	if (D < 0)
	{
		return 0;
	}
}
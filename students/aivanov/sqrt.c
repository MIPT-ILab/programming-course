//{=================================================================================
//! @file    sqrt.c
//! @date    2013-10-04 12:20
//! @author  Andrey Ivanov <ivanov.greyant@gmail.com>
//! @version 0.3
//!
//! Solving a square equation
//!
//! @par     Condition
//!          Input: the coefficients of the square equation
//!          Outpt: count of roots and roots or message: "no roots", "infinitie roots"
//}=================================================================================

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond,message)   \
	if (!(cond))   \
	{   \
		printf("%s\n%s is not true, file %s, line %d\n", message,#cond, __FILE__, __LINE__);   \
		abort();   \
	}

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
//}=================================================================================

int SolveSquare(double a, double b, double c, double* x1, double* x2);

int main()
{
	double a = 0, b = 0, c = 0;
	double x1 = 0, x2 = 0; //Roots
	int nRoots = 0; // Count of roots

	printf("#Solve a*x*x+b*x+c=0\n#Usage: a b c\n");
	scanf("%lg%lg%lg", &a, &b, &c);

	nRoots = SolveSquare(a, b, c, &x1, &x2); 
       
	switch (nRoots)
	{
		case -1: 
			printf("Infinite roots\n");
			break;
		case 0: 
			printf("No roots.\n");
			break;
		case 1: 
			printf("x1 = x2 = %lg\n", x1);
			break;
		case 2: 
			printf("x1 = %lg\nx2 = %lg\n", x1, x2);
			break;
		default: printf("Variable nRoots is not defined\n");
	}

	system("pause");
	return 0;
}

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	const double LOW = 0.00000000001;
	int nRoots = 0;
	double d = 0;

	ASSERT(x1 != NULL,"pointer to first root is NULL");
	ASSERT(x2 != NULL,"pointer to second root is NULL"); 
	ASSERT(x1 != x2,"pointers to the first and second roots are equal");

	if (fabs(a) < LOW) 
	{
		if (fabs(b) < LOW)
		{
			if (fabs(c) < LOW)
			{
				nRoots = -1; // infinite roots
			}
			else
			{
				nRoots = 0;
			}
		}
		else
		{
			*x1 = *x2 = -c/b;
			nRoots = 1;
		}
	}
	else
	{
		d = b*b-4*a*c;
		if (fabs(d) <= LOW) 
		{
				*x1 = *x2 = -b/(2*a);
				nRoots = 1;
		}
		else if (d < -LOW) 
				nRoots = 0;
		else if (d > LOW) 
		{
				*x1 = (-b-sqrt(d))/(2*a);
				*x2 = (-b+sqrt(d))/(2*a);
				nRoots = 2;
		}
	}

	if (fabs(*x1) <= LOW) *x1 = 0; 
	if (fabs(*x2) <= LOW) *x2 = 0; 

	return nRoots;
}
//{====================================================================================
//! @file solveSquare.c
//! @author Fokina Darya <dashfok@gmail.com>
//!
//! Solution for quadratic equations
//!
//! @par The programme enters 3 coefficients. 
//!      It needs to output number of roots or -1 
//!      (if equation is has infinitely many roots)
//!====================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>
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
//}===================================================================================
int SolveSquare(double a, double b, double c, double* x1, double* x2);
int main()
{
	double a=0,b=0,c=0,x1=0,x2=0,d=0;
	int nRoots;
	printf("Hello. \n");
	printf("This is a programme for solution of a quadratic equation. \n");
	printf("Enter the coefficients a,b,c.\n");
	scanf_s("%lg %lg %lg",&a,&b,&c);
	nRoots=SolveSquare(a,b,c,&x1,&x2);
	switch (nRoots) {
		case 2: 
			printf("# The equaton has number of roots:\n %d\n# Roots: %lg, %lg \n", nRoots, x1, x2);
			break;
		case 1: 
			printf("# The equaton has number of roots:\n %d\n# Roots: %lg \n", nRoots, x1);
			break;
		case 0:
			printf("# The equaton has no roots.");
			break;
		case -1:
			printf("# The equation is has infinitely many roots.");
	}
	getchar();
	getchar();
	return 0;
}
int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	double d=0;
	assert(x1!=NULL);
	assert(x2);
	assert(x1!=x2);\\
	d=b*b-4*a*c;
	if(a!=0)
	{
		if(d>0)
		{
			*x1=(-b+sqrt(d))/(2*a);
            *x2=(-b-sqrt(d))/(2*a);
			return 2;
		}
		else
		{
			if(d==0)
			{
				*x1=-b/(2*a);
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		if(b!=0)
		{
			*x1=-c/b;
			return 1;
		}
		else
		{
			if(c!=0)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}
}

			

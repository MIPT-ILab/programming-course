//{=================================================================================
//! @file    SolveSquare.c
//! @date    2013-10-03 21:23
//! @author  Andrey Ivanov <ivanov.greyant@gmail.com>
//!
//! Решение квадратного уравнения с честным разбором частных случаев.
//!
//! @par     Условие задачи
//!          Программа вводит 3 коэффициента квадратного уравнения. Надо вывести
//!          количество его корней (-1 в случае бесконечного их к-ва) и сами корни.
//!          Условие, разумеется, копируется оттуда, откуда взята задача, или
//!          пишется самостоятельно.
//}=================================================================================

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

		printf("#Solve a*x*x+b*x+c=0\n//Usage: a b c\n");
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

        assert(x1 != NULL);
        assert(x2 != NULL);
        assert(x1 != x2);

		if (a==0) 
		{
			if (b==0)
			{
				if (c==0)
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
			if (fabs(d) < LOW) // d = 0
			{
					*x1 = *x2 = -b/(2*a);
					nRoots = 1;
			}
			else if (d < 0) // (fabs(d)<LOW) => (d != 0)
					nRoots = 0;
			else if (d > 0) // (fabs(d)<LOW) => (d != 0)
			{
					*x1 = (-b-sqrt(d))/(2*a);
					*x2 = (-b+sqrt(d))/(2*a);
					nRoots = 2;
			}
		}

		if (*x1 == -0) *x1 = *x2 = 0;
        return nRoots;
}

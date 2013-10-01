#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
int SolveSquare (double a, double b, double c, double* X1, double* X2);
const double KON=0.0000001;
//{=================================================================================
//! @file    SolveSquare.cpp
//! @date    2013-09-27 22:39
//! @author  Anastasiya Ruzhanskaya <Anastasiya.Ruzhanskaya>
//!
//! Решение квадратного уравнения с честным разбором частных случаев.
//!
//! @par     Условие задачи
//!          Программа вводит 3 коэффициента квадратного уравнения. Надо вывести
//!          количество его корней (-1 в случае бесконечного их к-ва) и сами корни.
//!          Условие, разумеется, копируется оттуда, откуда взята задача, или
//!          пишется самостоятельно.
//!
//! @warning Круглые уравнения не вводить!
//}=================================================================================



int main()
{ 
	double a=0, b=0, c=0, X1=0, X2=0;
	int k=0;
	printf("Enter the coefficients of quadratic equacation: a*x^2+b*x+c=0\n");
	printf("a=");
	scanf("%lg", &a);
	printf("b=");
	scanf("%lg", &b);
	printf("c=");
	scanf("%lg", &c);


	k=SolveSquare(a, b, c, &X1, &X2);
	if (k==-1) printf("Infinite number of roots\n");
	if (k==0) printf("No roots\n");
	if (k==1)  printf("There is 1 root. X=%lg\n", X1);
	if (k==2)  printf("There are two roots. X1=%lg\n, X2=%lg\n", X2);
	system("pause");
	return 0;
}
//{=================================================================================
//! SolveSquare - solve a square or linear equation specified by its coefficients.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation 
//! @param[out] x2  2nd root of equation
//!
//! @return         Number of roots or zero if none, -1 if infinite number of roots
//!
//! @note           Calculation precision is considered to be DBL_EPSILON.
//}=================================================================================
int SolveSquare (double a, double b, double c, double* X1, double* X2)
{
    assert (X1!=NULL);
    assert (X2!=NULL);
    assert (X1!=X2);
	
	if (abs(a)<KON)
	{
		if (abs(b)<KON)
			{
				if (abs(c)<KON)
				  return -1;
				else
				  return 0;
		     }
		else
		{
			*X1=(-c)/b;
		    return 1;
		}
	}
	else
	  {
		double d=(b*b-4*a*c);
		if (abs(d)<KON)
			{
		*X1=(-b)/(2*a);
		 return 1;
		 }
		else
		{
			 *X1=(-b + sqrt(d))/(2 * a);
             *X2=(-b - sqrt(d))/(2 * a);
			 return 2;
		}

	}
	}

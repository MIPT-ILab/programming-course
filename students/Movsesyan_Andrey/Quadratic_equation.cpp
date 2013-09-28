#include <math.h>
#include <stdio.h>
#include <float.h>
#include <iostream>

int SolveSquare(double a, double b, double c, double *x1, double *x2);
int main()
{
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	int nRoots=0;

	printf("Enter the coefficients of the quadratic equation\n");
	scanf("%lg %lg %lg", &a, &b, &c);
	nRoots = SolveSquare(a, b, c, &x1, &x2);
	switch (nRoots)
	{
		case -2:
			printf("Not a quadratic equation");
			break;
		case -1:
			printf("Infinity NSE.");
			break;
		case 0:
			printf("No solution.");
			break;
		case 1:
			printf("one solution:\n");
			printf("x1=%.3lg.", x1);
			break;
		case 2:
			printf("Two solutions:\n");
			printf("x1=%.3lg,\nx2=%.3lg.", x1, x2);
			break;
	}

}

int SolveSquare(double a, double b, double c, double *x1, double *x2)
{
	if ((fabs(a) < DBL_EPSILON) && (fabs(b) < DBL_EPSILON) && (fabs(c) < DBL_EPSILON))
		return(-1);
	if (fabs(a) < DBL_EPSILON)                          
		return (-2);
	double D = b*b-4*a*c;
	if (D < -DBL_EPSILON)
		return(0);
	if (fabs(D) < DBL_EPSILON) 
	{
		*x1 = (-b)/(2*a);
		return (1);
	}
	if (D > DBL_EPSILON)
	{
		*x1 = (-b + sqrt(D))/(2*a);
		*x2 = (-b - sqrt(D))/(2*a);
		return(2);
	}
	return(0);	
}
	
		
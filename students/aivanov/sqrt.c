#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define LOW 0.00000000001 

int SolveSquare(double a, double b, double c, double* x1, double* x2);

int main()
{
	double a = 0, b = 0, c = 0; 
	double x1 = 0, x2 = 0; //Roots
	int nRoots = 0; // Count of roots

	printf("//Solve a*x*x+b*x+c=0\n//Usage: a b c\n"); 
	scanf("%lg%lg%lg", &a, &b, &c);

	nRoots = SolveSquare(a, b, c, &x1, &x2);
	
	if (nRoots == 0) printf("No roots.\n");
	else if (nRoots == 1) printf("x1 = x2 = %lg\n", x1);
	else if (nRoots == 2) printf("x1 = %lg\nx2 = %lg\n", x1, x2);

	system("pause");
	return 0;
}

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	int nRoots = 0;
	double d = 0;

	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	d = b*b-4*a*c;

	if (fabs(d) < LOW) // d = 0
	{
		*x1 = *x2 = -b/(2*a);
		nRoots = 1;
	}
	else if (d < 0) 
		nRoots = 0;
	else if (d > 0)
	{
		*x1 = (-b-sqrt(d))/(2*a);
		*x2 = (-b+sqrt(d))/(2*a);
		nRoots = 2;
	}

	return nRoots;
}
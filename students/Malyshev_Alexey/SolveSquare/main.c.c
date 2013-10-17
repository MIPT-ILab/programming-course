//{===================================================================
//! @file		SolveSquare.c
//! @date		2013-10-16 00:20
//! @author 	Malyshev Alexey <samymnyi2008@gmail.com>
//! @version 	1.00
//!
//! Allows to solve quadratic equation determined by its coefficients
//!
//! @par		Program reads three real numbers - coefficients of
//!				quadratic equation a*(x*x)+b*x+c=0.
//!				Returns quantity of solutions and their values
//!
//}===================================================================



#include <stdio.h>  //allows to use printf(), scanf()
#include <math.h>   //allows to use sqrt()
#include <assert.h> //allows to use assert()

int SolveLinear(double a, double b, double* x);
int SolveSquare(double a, double b, double c, double* x1, double* x2);

//--------------------------------------------------------------------
double const EPS=0.0000001; //!<Allows to compare double variables
//--------------------------------------------------------------------

int main()
{
	printf("#This program is created to help a user and solve as many quadratic equations\nas it's possible.\n");
	printf("\n#You have opened this program on %s %s\n", __TIME__, __DATE__);
	printf("\n#Please, enter coefficients of quadratic square you'd like to be solved.\n\n");


	double a = 0, b = 0, c = 0;
	double x1 = 0, x2 = 0;
	int QuantityOfSolutions = 0;

	scanf("%lg", &a);
	scanf("%lg", &b);
	scanf("%lg", &c);

	QuantityOfSolutions = SolveSquare(a, b, c, &x1, &x2);

	//From here program analyzes received results of SolveSquare function

	if (QuantityOfSolutions == -1)
	{
		printf("\n#Well, this equation is really nice: every x from R is a root of this equation.");
	}
	else if (QuantityOfSolutions == 0)
		{
			printf("\n#Unfortunately this equation has no decisions at all\n");
		}
		else if (QuantityOfSolutions == 1)
			{
				printf("\n#Well, this equation has the only one root and its value is:\n\nx1 = x2 = x = %lg\n", x1);
			}
			else
			{
				printf("\n#This equation has two roots and their values are:\n\nx1 = %lg\nx2 = %lg\n", x1, x2);
			}

	return 0;
}



//{========================================================================================================
//! SolveSquare - allows to solve quadratic equation determined by its coefficients
//!
//! @param		a - Equation a-coefficient (relates to (x*x))
//! @param 		b - Equation b-coefficient (relates to x)
//!	@param		c - Equation c-coefficient (free term)
//!	@param[out]	x1 - First root of equation, if exist (otherwise will be unchanged)
//! @param[out] x2 - Second root of equation, if exist (otherwise will be unchanged)
//!
//! @return 	Number of roots, or zero if roots do not exist, or (-1) if there is infinite number of roots
//}=========================================================================================================

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL); // Checks the correctness of entered x1 value
	assert(x2 != NULL); // Checks the correctness of entered x2 value
	assert(x1 != x2);	// Checks whether x1 matches with x2 (it's an ERROR!)

	//From here function analyzes special cases of quadratic equation

	if (((-EPS) < a) && (a < EPS)) 		//That case when equation is linear
	{
		if (((-EPS) < b) && (b < EPS)) 	// Nontrivial linear equation (0 + c = 0)
	   {
	   	if ((c < (-EPS)) || (EPS < c) ) // Determines x due to c
		{
			return (0); 				// Linear equation (0 = -c) has no real solutions
		}
		else
		{
			return (-1);				// Each x from R is root of (0 = 0) linear equation
		}
	   }
	   else								// "Classic" linear equation
	   	{
	   		*x1 = *x2 = (-c)/b;

			return (1);					// Only one x from R is root of (bx = -c) linear equation
	   	}

	}
	else
	{
		double D = 0; 					// Variable, which has value of quadratic equation's discriminant
        D = (b*b) - 4*a*c;				// Finding the value of discriminant

        // From here function is looking for other special cases

        if (D < (-EPS))
		{
			return (0);					// Equation has no real solutions
		}
		else
		{
			if (((-EPS) < D) && (D < EPS))
			{
				*x1 = *x2 = (-b)/(2*a);

				return (1);				// Equation has the only real solution and x1 = x2
			}
			else
			{
				*x1 = ((-b) + sqrt(D))/(2*a);
				*x2 = ((-b) - sqrt(D))/(2*a);

				return (2);				// Equation has two different real solutions
			}
		}
	}
}



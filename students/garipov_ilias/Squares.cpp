/**
*	@file    Squares.cpp
*	@date    2013-09-30 19:25
*	@author  Il'yas Garipov <logirz728@gmail.com>
*
*	Quadratic equations solving apparatus.
*
*	@version 1.0.1
*
*	@par The input consists of a, b and c in 'a*x^2 + b*x + c'
*	formula. Output consists of up to two rows of numbers:
*	"Roots' amount" and "Roots", wherein
*	"Roots' amount" represents the amount of roots the equation has.
*	"Roots" either holds those roots, or doesn't exist at all
*	if amount of roots isn't a natural number.
*/


#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define IS_ZERO( x ) (fabs(x) <= DBL_EPSILON)
#define IS_BELOW_ZERO( x ) (x < -DBL_EPSILON)

#ifndef NDEBUG
	#define DOUT( toprint ) printf( "\n# " toprint )
	#define DPUT( toput , x ) printf( "\n# " toput , x )
	#define DLN
	#define DPUTCLOSURE	DOUT("=============================================================================");\
						DPUT("FILE: %s", __FILE__ );\
						DPUT("TIME OF COMPILATION: %s", __TIME__ )
#else
	#define DOUT
	#define DPUT
	#define DLN if(0)
	#define DPUTCLOSURE
#endif



/**
*		SolveSqr - solve a quadratic equation defined by its coefficients
*
*	@note 1)In documentation below, (1) is a*x^2 + b*x + c = 0;
*		2)If the amount of roots isn't a natural number we do nothing with x1 and x2;
*		3)Also, we take calculation precision as DBL_EPSILON
*
*	@param		a	The 'a' in (1)
*	@param		b	The 'b' in (1)
*	@param		c	The 'c' in (1)
*	@param[out]	x1	First root
*	@param[out]	x2	Second root
*
*	@return If roots exist, their quantity.
*	If there are none, 0.
*	If there are all the roots in the world, -1.
*
*/
int SolvSqr(float a, float b, float c,
            float* x1, float* x2);

const int ALLRTS = -1; //!< SolveSqr returns this if any real X is a root

int main()
{
	DOUT("YOUR_REQUEST: Quadratic equations solver");
	DOUT("=============================================================================");
	DOUT("Enter 3 numbers that correspond to a, b and c in the equation");
	DOUT("\t a*x^2 + b*x + c = 0");
	DOUT(">");

	float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	scanf("%f %f %f", &a, &b, &c);

	int Rts = SolvSqr(a, b, c, &x1, &x2);

	if( IS_ZERO(x1) ) x1 = 0;
	if( IS_ZERO(x2) ) x2 = 0;

	DLN printf("\n");		//!< For a neatly formatted output
	printf("%d\n", Rts);

	switch(Rts) {
		case(0) :
			DOUT("There are no roots in real numbers for the given equation\n\n");
			break;

		case(1) :
			DOUT("There is only one root for the given equation:\n\n");
			printf("%lg", x1);
			break;

		case(2) :
			DOUT("The given equation possesses two roots in real numbers:\n\n");
			printf("%lg %lg", x1, x2);
			break;

		case(ALLRTS) :
			DOUT("Any real number can be a root of the given equation\n\n");
			break;

		default :
			DOUT("Something's rotten here:");
			DOUT("\tUnhandled exception in solver's return value.");
			DPUTCLOSURE;
			return 1;
	}

	DLN printf("\n");		//!< Yet again, for a neatly formatted output.
	DOUT("=============================================================================");
	DOUT("Request processed and result delivered successfully.");
	DOUT("\tRestart application to process another quadratic equation.");
	DPUTCLOSURE;
	return 0;
}


int SolvSqr(float a, float b, float c,
            float* x1, float* x2)
{
	DLN assert(( "We've processed pointer to x1 alright", (x1 != NULL) ));
	DLN assert(( "We've processed pointer to x2 alright, too", (x2 != NULL) ));

	if( !(IS_ZERO(a)) ) {
		float D = b * b - (4 * a * c);

		if(IS_BELOW_ZERO(D)) return 0;

		else if(IS_ZERO(D)) {
			*x1 = (-b) / (2 * a);
			return 1;
		} else {
			D = sqrt(D);
			*x1 = (-b - D) / (2 * a);
			*x2 = (-b + D) / (2 * a);
			return 2;
		}
	} else if( !(IS_ZERO(b)) ) {
		*x1 = (-c) / b;
		return 1;
	} else if( !(IS_ZERO(c)) ) {
		return 0;
	} else
		return ALLRTS;

}

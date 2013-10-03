//TODO: doxygen description of functions
//TODO: do smth with tabs
//TODO: make template
//TODO: own static library
//TODO: solving of linear equations

//{====================================================================================
//! @file quadratic_equation.c
//! @author Nasonov Andrey <drnetzah@gmail.com>
//!
//! Solving quadratic equation.
//!
//! @par This program is purposed for solving quadratic equations.
//!      It enters three coefficients of given equation and analyzes it.
//}====================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>

//! Function is of a type int, because its value is number of roots of given equations. 
//! Roots themselves change as a values at given adresses.
//-------- Prototypes -----------------------------------------------------------------
int square_roots ( double, double, double, double*, double* ); //prototype
//-------------------------------------------------------------------------------------

int main()
{
	double a = 0,
               b = 0,
               c = 0;
	printf ( "# Please, enter coefficients of quadratic equation (first coefficient doesn's equal zero)\n" );
	scanf ( "%lg %lg %lg", &a, &b, &c );
	assert ( a != 0 ); //! safety check (program is purposed for solving quadratic equations, not linear)

	double x1 = 0,
               x2 = 0;
	int number_of_roots = square_roots ( a, b, c, &x1, &x2 );

	//! Analysis of possible cases
	switch ( number_of_roots )
	{
		case 0 :
			printf ( "# This equation doesn't have any roots\n" );
			break;
		case 1 :
			printf ( "# This equation has one root:\n"
			         "%8lg\n", x1 );
			break;
		case 2 :
			printf ( "# This equation has two roots:\n" );
			printf ( "%8lg %8lg\n", x1, x2 );
			break;
//               default
	}
	return 0;
}


int square_roots ( double a, double b, double c, double* x1, double* x2 )
{
	//! Necessary safety	
	assert ( a  != 0    );
	assert ( x1 != NULL );
	assert ( x2 != NULL );

	//! Discriminant
	double d = ( pow ( b, 2 ) ) - 4 * a * c;

	//! Analysis of three porssible cases
	if ( d < 0 )
	{
		return 0;
	}
	else
	{
		if ( d == 0 )
		{
			*x1 = - b / ( 2 * a );
			return 1;
		}
		else
		{
			*x1 = ( - b + sqrt ( d ) ) / ( 2 * a );
			*x2 = ( - b - sqrt ( d ) ) / ( 2 * a );
			return 2;
		}
	}
}

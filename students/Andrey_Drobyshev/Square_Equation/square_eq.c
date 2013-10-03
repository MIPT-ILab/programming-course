//{=======================================================================
//! @file square_eq.c
//! @date 30.09.2013 23:39
//! @author Andrey Drobyshev <immortalguardian1@gmail.com>
//! @ version 1.02
//! @note V1.01:
//!
//!	    - variables for coefficients (a, b, c) are double now;
//!	    - doxygen comments added;
//!	    - filename was changed from <ssq.c> to <square_eq.c>.
//!
//! @note V1.02:
//!
//!        - bug with returning -0 in equations like
//!        0 + b*x + 0 = 0 is corrected.
//!
//! The program just solves a quadratic equation.
//!
//! @par	Conditions:
//! 		The program reads coefficients of quadratic equation
//!		and calculates its roots.
//}=======================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ASSERT(condition) if (!(condition))\
			  {\
				printf("#Assertion failed: wrong variables addresses (%s)\n", #condition);\
				printf("#File %s\n#Line %d", __FILE__, __LINE__);\
                		abort();\
			  }

const double eps=0.000001; //!< Calculation precision constant.

//{=================================================================================
//! Function ssq - solves a square or linear equation specified by its coefficients.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
//!
//! @return         Number of roots or zero if none, 3 if infinite number of roots
//!
//! @note           Calculation precision is considered to be eps=0.000001.
//! @note	    The function has assertion checks.
//}==================================================================================

int ssq ( double a, double b, double c, double* x1, double* x2);

int main ()
{
        double a, b, c, x1, x2;

	a = b = c = x1 = x2 = 0;
        printf ( "#Please enter real coefficients of quadratic equation:\n");
        scanf ( "%lg %lg %lg", &a, &b, &c);
        printf ("\n");
        switch ( ssq ( a, b, c, &x1, &x2))
        {
                case 3:
                        printf ( "#All x from R\n");
                        break;
                case 2:
                        printf ( "#The equation has 2 roots:\n#x1 = %f, x2 = %f\n", x1, x2);
                        break;
                case 1:
                        printf ( "#The equation has 1 root:\n#x1 = %f\n", x1);
                        break;
                case 0:
                        printf ( "#The equation has no roots\n");
                        break;
        }
        return 0;
}

int ssq ( double a, double b, double c, double* x1, double* x2)
{
        double discriminant;

        ASSERT ( x1 != 0);
        ASSERT ( x2 != 0);
        ASSERT ( x1 != x2);

        if ( fabs (a) > eps) // Check out if the equation is quadratical
        {
                discriminant = b*b - 4*a*c;
                if ( ( discriminant-eps) > 0)
                {
                        *x1 = ( -b - sqrt(discriminant)) / ( 2*a);
                        *x2 = ( -b + sqrt(discriminant)) / ( 2*a);
                        return 2;
                }
                else
                        if ( ( discriminant + eps) < 0)
                                return 0;
                        else
                        {
                                *x1 = (-b) / (2*a);
                                return 1;
                        }
        }
        else  // The equation is linear
                if ( fabs(b) > eps)
                {
                        if ( fabs(c) > eps)  //If c == 0 x1 will keep 0
                            *x1 = ( ( -c) / b);
                        return 1;
                }
                else
                        if ( fabs(c) < eps)
                                return 3;
                        else
                                return 0;
}

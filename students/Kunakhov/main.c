

//{===================================================================
//!@file  main.c
//!asks the number of quadratic equations and The factors
//!displays the roots
//!@date 2013-10-08
//!@author Kunakhov Ivan <Ivan.Kunakhov@frtk.ru>
//!@version 1.03
//!@note v1.01
//!-added documentation
//!-added added a multiple equations solving
//!
//!@note v1.02
//!-added ASSERT define
//!-added some coments
//!@note v1.03
//! -fixed ASSERT
//!@note v1.04
//! -ASSERT may display an error message and the place where it is made
//! -improved codestyle
//!- Removed description to main
//}===================================================================


#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <stdlib.h>


#define ASSERT( cond, txt)                      \
    if ( !( cond ) )                        \
    {                                       \
        printf ("Error: %s \n file: %s, line: %d \n",#txt, __FILE__, __LINE__);         \
        abort();                            \
    }


/**
    solve_sqare solve square equation with coefficients
    @param  a         -   x^2 coefficient
    @param  b         -  x^1 coefficient
    @param  c         -  x^0 coefficient
    @param[out] x1    -  root
    @param[out] x2    -  root
    @note ASSERT for checking the input and Solve_Square function data
**/


int solve_sqare ( double a, double b, double c, double *x1, double *x2)
{
    double d = 0, x = 0;


    ASSERT(x1 != NULL, " adress of the x1 is zero");
    ASSERT(x2 != NULL, " adress of the x2 is zero");
    ASSERT(x1 != x2, "adresses of x1 and x2 is the same");



    if (fabs(a) <= DBL_EPSILON)
    {
        if (fabs (b) <= DBL_EPSILON)
        {
            if (fabs(c) <= DBL_EPSILON)
            {
                return(-1);
            }
            return(0);
        }
        *x1 = -c/b;
        return(1);
    }

    d = b*b - 4*a*c;


    if (d < -DBL_EPSILON)
    {
        return(0);
    }
    if (fabs(d) <= DBL_EPSILON)
    {
        x = -b/(2*a);
        *x1 = *x2 = x;
        return(1);
    }


    *x1 = (-b + sqrt(d))/(2*a);
    *x2 = (-b - sqrt(d))/(2*a);
    return(2);
}






 int main ()
{

	double a = 0, b = 0, c = 0;
	double x1 = 0, x2 = 0;
	int n = 0, k = 0, i = 0;


	printf("insert how many equations you would have\n");
	scanf("%d", &k);


    for (i = 1; i <= k; i++)
    {
        printf("insert a, b, c\n");
        scanf("%lf %lf %lf", &a,&b,&c);
        n = solve_sqare(a, b, c, &x1, &x2);


        if (n == 0)
        {
            printf("no solutions\n");
        }
        if (n == 1)
        {
            printf("solution is %lg\n",x1);
        }
        if (n == 2)
        {
            printf("solutions are %lg %lg\n",x1,x2);
        }
        if (n == -1)
        {
            printf("there is infinite number of solutions\n");\
        }
    }

    return(0);

}

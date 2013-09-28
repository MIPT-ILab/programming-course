//---------------------------------------------------------------------------
//{====================================================================================
//! @file solveSquare.c
//! @date    2013-09-26 16:30
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Solution for quadratic equations
//!
//! @par The programme enters 3 coefficients.
//!      It needs to output number of roots
//!====================================================================================

#include <stdio.h>
#include <math.h>

int SolveSquare( double a, double b, double c, double *x1, double *x2)  ;
//---------------------------------------------------------------------------

int main()
{
        double a=0,b=0,c=0, x1=0,x2=0;
        int nRoots=0;
        printf("a*x^2+b*x+c=0,  enter a b c \n");
        scanf("%lf %lf %lf", &a, &b,&c) ;
        nRoots=SolveSquare(a,b,c,&x1,&x2);
        if (nRoots==2)
            {
            printf("nRoots = %i, x1=%lf, x2=%lf\n", nRoots, x1, x2);
            }
        if (nRoots==1)
            {
            printf("nRoots= %i, x=%lf", nRoots, x1);
            }
        if (nRoots==-1)
            {
            printf("No answers");
            }
        return 0;
}

//! SolveSquare - solve a square or linear equation specified by its coefficients.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
//!
//! @return         Number of roots or zero if none
//}===================================================================================

int SolveSquare( double a, double b, double c, double *x1, double *x2)
        {
        if (a==0)
                {
                *x1=-c/b;
                return 1;
                }
        else
                {
                double d=b*b-4*a*c;
                if (d<0)
                        {
                         return -1;
                         }
                else if(d>0)
                        {
                        *x1 = (-b + sqrt(d))/(2 * a);
                        *x2 = (-b - sqrt(d)) /(2 * a);
                        return 2;
                        }
                        else
                            {
                            *x1=-b/(2*a);
                            return 1;
                            }
                }
        }
//---------------------------------------------------------------------------



//{=================================================================================
//! @file    Square_Equation.c
//! @date    2013-10-04 04:01
//! @author  Anna Saenko <HannaSanoke@gmail.com>
//!
//! The solution of the quadratic equation
//!
//! @par     The program enters 3 coefficients of the quadratic equation.
//!          It is necessary to bring the number of its roots
//!          (-1 for infinite number of roots) and the roots.
//}=================================================================================


#include <stdio.h>
#include <math.h>
#include <assert.h>


    int SolveSquare(double a, double b, double c, double* x1, double* x2);

    int main()
    {
      double x1, x2;
      double a, b, c;

      printf("# Enter coefficients\n");
      scanf("%lf %lf %lf",&a,&b,&c);

      int nRoots=SolveSquare(a,b,c,&x1,&x2);

      printf("# Equation has %i roots:\n",nRoots);

      if(nRoots==2)
        {printf("%e %e\n",x1,x2);}
      else
        {
          if(nRoots==1) {printf("%e\n",x1);}
          if(nRoots==-1) {printf("# Equation has infinite roots \n");}
        }
    }

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

    int SolveSquare(double a, double b, double c, double  *x1, double *x2)
    {
      //Precondition tests
      assert(x1!=NULL);
      assert(x2!=NULL);
      assert(x1!=x2);

      double D=b*b-4*a*c;

      if((a==0)&&(b!=0)&&(c!=0))
        {
          *x1=-c/b;
          return 1;
        }

      if((a==0)&&(b==0)&&(c==0))
        {return -1;}

      if(D>0)
        {
          *x1=(-b+sqrt(D))/(2*a);
          *x2=(-b-sqrt(D))/(2*a);
          return 2;
        }
      else
        {
         if(D==0)
         {
           *x1=-b/(2*a);
           return 1;
         }
         else return 0;
        }
    }




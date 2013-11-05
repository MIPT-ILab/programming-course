//{=================================================================================
//! @file    1-square_eq.cpp
//! @date    2013-10-27 20:00
//! @author  Alexey Neganov <neganovalexey@gmail.com>
//!
//! Solve a square or linear equation specified by its coefficients.
//!
//! @par     Keys: "r" if you want to see only real roots
//!          Input: 3 coefficients (a, b, c) of the equation
//!          Output: roots of the equation or message if there is no roots or infinitely large number of.
//}=================================================================================
#include <stdio.h>
#include <math.h>
#include <assert.h>
//#include <float.h>
#define DBL_EPSILON 10e-6
#define IS_ZERO(x) fabs(x)<DBL_EPSILON
#define IS_NEGATIVE(x) x<-DBL_EPSILON
//! Value, that is retunted in the case of infinitely large number of solutions
const int KN_INFINITE_ROOTS = -1;
const int KN_NO_ROOTS = 0;
const int KN_ONE_ROOT = 1;
const int KN_TWO_ROOTS = 2;
const int OK = 1;
const int ERROR = 0;
//{=================================================================================
//! trueroot - function, that return root correctly, even it is zero.
//!
//! @param      x   Root of an equation
//!
//! @return     x, if fabs(x)>DBL_EPSILON, or zero, if not.
//}=================================================================================
double trueroot(double x)
   {
   if(IS_ZERO(x)) return 0;
   else return x;
   }
//{=================================================================================
//! LinearSolve - solve a linear equation.
//!
//! @param      b   Equation bx+c=0 b-coefficient
//! @param      c   Equation bx+c=0 c-coefficient
//! @param[out] x1   Root of equation, if exist (if not, value will be unchanged)
//!
//! @return         Number of roots or zero if none, KN_INFINITE_ROOTS if infinite number of roots
//!
//! @note           Calculation precision is considered to be DBL_EPSILON.
//}=================================================================================
int LinearSolve (double b, double c, double *x1)
   {
      assert(x1);
      if(IS_ZERO(b))
         {
         if(IS_ZERO(c))
            return KN_INFINITE_ROOTS;
         else return KN_NO_ROOTS;
         }

      else
         {
         *x1 = trueroot(-c/b);
         return KN_ONE_ROOT;
         }
    }
//{=================================================================================
//! SquareSolve - solve an square equation with non-zero first coefficient.
//!
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] r   a part of the roots of equation without discriminant
//! @param[out] s   an unsigned part of the roots of equation with discriminant
//!
//! @return         Number of real roots or zero if none
//!
//! @note           Calculation precision is considered to be DBL_EPSILON.
//}=================================================================================n
int SquareSolve(double a, double b, double c, double *r, double *s)
      {
      assert(r && s);
      double d = b*b - 4*a*c;
      *r = -b/(2*a);
      if(IS_NEGATIVE(d))
         {
         *s = sqrt(-d)/(2*a);
         return KN_NO_ROOTS;
         }

      else
         {
         if(IS_ZERO(d))
            return KN_ONE_ROOT;
         else
            {
            *s = sqrt(d)/(2*a);
            return KN_TWO_ROOTS;
            }
         }
      }
//{==================================================================================
//! complexprintf - function to print complex values
//!
//! @param      r   Real part of the complex value
//! @param      i   Imaginary part of the complex value
//!
//! @return     OK
//}===================================================================================
int complexprintf(double r, double i)
   {
   if (IS_ZERO(r))
      printf("%lgi ", i);
   else
      {
      if (IS_ZERO(i))
         printf("%lg ", r);
      else
         {
         if(IS_NEGATIVE(i))
            printf("%lg%lgi ", r, i);
         else printf("%lg+%lgi ", r, i);
         }
      }
    return OK;
   }
//{==================================================================================
//! warriorscanf - function, that provides correct input
//!
//! @message         "Please enter your coefficiens\n"
//!
//! @param[out]      a   equation a-coefficient
//! @param[out]      b   equation a-coefficient
//! @param[out]      c   equation a-coefficient
//!
//! @return     OK or ERROR
//}===================================================================================
int warriorscanf(double *a, double *b, double *c)
   {
   if (!a||!b||!c) return ERROR;
   printf("Please enter your coefficiens\n");
   if (!scanf("%lg", a)) return ERROR;
   if (!scanf("%lg", b)) return ERROR;
   if (!scanf("%lg", c)) return ERROR;
   return OK;
   }
//{==================================================================================
//! main_output
//!
//! @param      a    equation a-coefficient
//! @param      b    equation a-coefficient
//! @param      c    equation a-coefficient
//! @param      arg  argument to print all roots or only real roots
//!
//! @message    roots of the equation ("xi = root"), \
or "Infinitely large number of roots", or "No roots", or "No real roots"
//!
//! @return     OK
//}===================================================================================
int main_output (double a, double b, double c, int arg)
   {
    double r=0;
    if(IS_ZERO(a))
      {
      switch( LinearSolve(b,c,&r) )
         {
         case KN_INFINITE_ROOTS: printf("Infinitely large number of roots"); break;
         case KN_NO_ROOTS: printf("No roots"); break;
         case KN_ONE_ROOT: printf("x=%lg", r); break;
         }
      }

   else
      {
      double s=0;
      switch( SquareSolve(a,b,c,&r,&s) )
         {
         case KN_NO_ROOTS:
            if (arg>1)
               printf("No real roots");
            else
               {
               complexprintf(r,s);
               complexprintf(r,-s);
               }
            break;
         case KN_ONE_ROOT: printf("x=%lg", trueroot(r)); break;
         case KN_TWO_ROOTS: printf("x1=%lg, x2=%lg", trueroot(r+s), trueroot(r-s)); break;
         }
      }
   printf("\n");
   return OK;
   }


int main(int argc, char * argv[])
   {
   double a=0,b=0,c=0;
   if ( warriorscanf(&a,&b,&c)==ERROR )
      {
      printf("ERROR!\nIt was wrong input there. Be more careful and try again.");
      return 0;
      }
   main_output(a, b, c, argc);
   return 0;
   }

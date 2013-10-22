//{===========================================================================================
//! @file SquareSolve.cpp
//! @date 2013-10-15
//! @author Igor Matveev <science.creation96@gmail.com>, 312 group, DREC MIPT
//! @version 1.01
//! @note V1.01
//!   - create main, which
//!   -- read the factors of square equation
//!   -- analyze the factors
//!   -- handle and induce the functions about data
//!   - create functions SolveLine and SolveSquare
//}===========================================================================================
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define ZERO(x) (fabs(x) < DBL_EPSILON)
#define BELOW_ZERO(x) (x < -DBL_EPSILON)

#define ASSERT(cond)                           \
if (!(cond)) {                                 \
      printf("All is bad: %s is FALSE!!!11\n"  \
             "File: %s\nLine: $d\n",           \
             #cond, __FILE__, __LINE__);       \
      abort();                                 \
      }

int SolveLine(double b, double c, double* x1);
int SolveSquare(double a, double b, double c, double *x1, double *x2);

/**
 main - Requests the factors, scans them and prints the tipe of the equation

      @param a    first factor (of x ^ 2)
      @param b    second factor (of x)
      @param c    free term
      @param D    discriminant
      @param x1   first root
      @param x2   second root

      @return main: Standart return

      @note Answers  - "Well done: ANY number is a root of the square equation."
                              means    a == 0, b == 0, c == 0

                     - "THERE ISN'T any root of this equation!"
                              means -- a == 0, b == 0, c != 0
                                    -- D < 0

                     - "It's a LINE equation and a root is..."
                              means    a == 0, b != 0, c != 0

                     - "Good! There are 2 roots of the square equation:..."
                              means -- a != 0, b != 0, c != 0
                                    -- x1 != x2

                     - "So, we have a root:..."
                              means -- a != 0, b != 0, c != 0
                                    -- x1 == x2
**/

int main()
{
      printf("\nHello! I can solve a square equation. "
                 "Please, bring in A, B, C factors.\n\n");
      printf("      A * x^2 + B * x + C = 0\n\n");
      double a = 0, b = 0, c = 0;
      double *x1 = NULL, *x2 = NULL;
      printf("A = ");
      scanf("%lf", &a);
      printf("\nB = ");
      scanf("%lf", &b);
      printf("\nC = ");
      scanf("%lf", &c);
      // FIXME [crady@cradylap Matveev_Igor]$ ./a.out 
      //
      // Hello! I can solve a square equation. Please, bring in A, B, C factors.
      //
      //       A * x^2 + B * x + C = 0
      //
      //       A = w
      //
      //       B = 
      //       C = Well done: ANY number is a root of the square equation.
      // You should to add some checks over user's input!
      x1 = (double*) calloc( 1, sizeof(double) );
      x2 = (double*) calloc( 1, sizeof(double) );


      if (ZERO(a))
      {
            if ( !(SolveLine(b, c, x1)) )
            {
                  printf("It's a LINE equation and a root is\nx = %f", *x1);
            }
            return 0;
      }
      if ( !(SolveSquare(a, b, c, x1, x2)) )
      {
            printf("Good! There are 2 roots of the square equation:\nx1 = %f\nx2 = %f", *x1, *x2);
      }
      free(x1);
      free(x2);
      return 0;
}

//-------------------------------------------------------------------------------------------

//

/**
 SolveLine - solve a line equaton of the form: b * x + c = 0
            (if parameter a = 0)

      @param b          factor of x
      @param c          free term
      @param[out] x1    unicque root

      @return           1 - if the root is any number or nothing,
                        then fuction print the answer
                        0 - if the solution is usual
**/

int SolveLine(double b, double c, double *x1)
{
      ASSERT(x1 != NULL);
      // FIXME This can be simplified.
      // if (ZERO(B) && ZERO(C)) printf ("Any number...");
      // if (ZERO(C)) printf("No roots...");
      // solve equation...
      // return result;
      if (ZERO(b))
      {
            if (ZERO(c))
            {
                  printf("Well done: ANY number is a root of the square equation.");
                  // FIXME It is not obvious what function returns.
                  // You can do this in the following way:
                  // #define SOLVER_ERR -1
                  // #define SOLVER_OK 0
                  // and so on. You can study 'enum' thing, it will be preferable
                  // solution here.
                  return 1;
            }
            printf("THERE ISN'T any root of this equation!");
            return 1;
      }
      *x1 = - c / b;
      return 0;
}

//----------------------------------------------------------------------------------------

/**
 SolveSquare - solve the square equation with nonzero a

      @param a          first factor (of x ^ 2)
      @param b          second factor (of x)
      @param c          free term
      @param D          discriminant
      @param[out] x1    first root
      @param[out] x2    second root


**/

int SolveSquare(double a, double b, double c, double *x1, double *x2)
{
      ASSERT(x1 != x2);
      ASSERT(x1 != NULL);
      // FIXME And if x2 is equal 0?
      double D = b * b - 4 * a * c;
      if (BELOW_ZERO(D))
      {
            printf("THERE ISN'T any root of this equation!");
            return 1;
      }
      *x1 = (- b + sqrt (D)) / (2 * a);
      *x2 = (- b - sqrt (D)) / (2 * a);
      if (*x1 == *x2)
      {
            printf("So, we have a root:\nx = %f", *x1);
            return 1;
      }
      return 0;
}


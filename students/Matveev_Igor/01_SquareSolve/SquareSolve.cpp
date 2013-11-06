//{================================================================================================
//! @file SquareSolve.cpp
//! @date 2013-10-15
//! @author Igor Matveev <science.creation96@gmail.com>, 312 group, DREC MIPT
//! @version 1.02
//! @note V1.01
//!   - create main, which
//!   -- read the factors of square equation
//!   -- analyze the factors
//!   -- handle and induce the functions about data
//!   - create functions SolveLine and SolveSquare
//! @note V1.02
//!   - changed the main and functions SolveLine and SolveSquare
//!   -- deleted main output from these functions
//!   - created new function Output
//!   - added constants, which organize returns of functions and simplify the output
//!   - added chaeck over user's input
//}================================================================================================
//-------------------------------------------------------------------------------------------------

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
int Output(int numrt, double* x1, double* x2);

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

                     - "It's a LINE equation!
                        So, we have a root:..."
                              means    a == 0, b != 0, c != 0

                     - "Good! There are 2 roots of the square equation:..."
                              means -- a != 0, b != 0, c != 0
                                    -- x1 != x2

                     - "So, we have a root:..."
                              means -- a != 0, b != 0, c != 0
                                    -- x1 == x2
**/
const int TWOROOTS = 0;
const int ONEROOT  = 1;
const int ANYROOT  = 2;
const int NOROOT   = 3;

//
//-------------------------------------------------------------------------------------------------

int main()
{
      printf("\nHello! I can solve a square equation. "
                 "Please, bring in A, B, C factors.\n\n");
      printf("      A * x^2 + B * x + C = 0\n\n");
      double a = 0, b = 0, c = 0;
      double *x1 = NULL, *x2 = NULL;
      printf("A = ");
      ASSERT((scanf("%lf", &a)) != 0);
      printf("\nB = ");
      ASSERT((scanf("%lf", &b)) != 0);
      printf("\nC = ");
      ASSERT((scanf("%lf", &c)) != 0);
      //--// You should to add some checks over user's input!
      x1 = (double*) calloc( 1, sizeof(double) );
      x2 = (double*) calloc( 1, sizeof(double) );


      if (ZERO(a))
      {
            printf("\n              Answer\n\n");
            Output(SolveLine(b, c, x1), x1, x2);
      }
      else
      {
            printf("\n              Answer\n\n");
            Output(SolveSquare(a, b, c, x1, x2), x1, x2);
      }
      free(x1);
      free(x2);
      return 0;
}

//-------------------------------------------------------------------------------------------------
//

/**
 SolveLine - solve a line equaton of the form: b * x + c = 0
            (if parameter a = 0)

      @param b          factor of x
      @param c          free term
      @param[out] x1    unicque root

      @return           ANYROOT - if any number is a root
                        NOROOT  - if there isn't any root
                        ONEROOT - if there is a root
**/

int SolveLine(double b, double c, double *x1)
{
      ASSERT(x1 != NULL);
      if (ZERO(b) && ZERO(c))
      {
            return ANYROOT;
      }
      if (ZERO(c))
      {
            return NOROOT;
      }
      printf("It's a LINE equation!\n");
      *x1 = - c / b;
      return ONEROOT;
}

/**
 SolveSquare - solve the square equation with nonzero a

      @param a          first factor (of x ^ 2)
      @param b          second factor (of x)
      @param c          free term
      @param D          discriminant
      @param[out] x1    first root
      @param[out] x2    second root

      @return           ANYROOT  - if any number is a root
                        ONEROOT  - if there is a root
                        TWOROOTS - if there are two roots


**/

int SolveSquare(double a, double b, double c, double *x1, double *x2)
{
      ASSERT(x1 != x2);
      ASSERT(x1 != NULL);
      ASSERT(x2 != NULL);
      double D = b * b - 4 * a * c;
      if (BELOW_ZERO(D))
      {
            return ANYROOT;
      }
      *x1 = (- b + sqrt (D)) / (2 * a);
      *x2 = (- b - sqrt (D)) / (2 * a);
      if (*x1 == *x2)
      {
            return ONEROOT;
      }
      return TWOROOTS;
}

/**
 Output - main output of this program

      @param numrt - number of roots, which return another functions
      @param x1 |
                | - the answers of the equation
      @param x2 |
**/

int Output(int numrt, double* x1, double* x2)
{
      switch (numrt)
      {
            case TWOROOTS:
                printf("Good! There are 2 roots of the square equation:"
                       "\nx1 = %f\nx2 = %f\n", *x1, *x2);
                break;
            case ONEROOT:
                printf("So, we have a root:\nx = %f\n", *x1);
                break;
            case ANYROOT:
                printf("Well done: ANY number is a root of the square equation.\n");
                break;
            case NOROOT:
                printf("THERE ISN'T any root of this equation!\n");
                break;
            default:
                printf("--------------------BIG BAGGA BOOM--------------------"
                       "The program work's WRONG!! You could kill the author. :)");
                break;
      }
      return 0;
}


                  // and so on. You can study 'enum' thing, it will be preferable

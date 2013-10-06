/** *********************************************************

 Program for solving square equations
 
 @file Solve_Square.c
 @date September 21, 2013
 @author Kirill Korolev <kirill.korolef@gmail.com>
 @version 1.02 (October 2, 2013)

 @note Ver. 1.01 (October 2, 2013)
     - a documentation added
     - added the DBL_EPSILON accuracy to all comparisons
     - assert comments added
     - ASSERT define added
     - Changed name from "main.c"
 
 @note Ver. 1.02 (October 4, 2013)
     - added a multiple equations solving
     - added a constant EPS instead system DBL_EPSILON
     - added a standart ASSERT arguments type

************************************************************/

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define ASSERT( cond )                 \
    if ( !( cond ) )                   \
    {                                  \
        printf ("Fatal error: %s, "    \
        "file: %s, line: %d \n",       \
        #cond, __FILE__, __LINE__);    \
        abort();                       \
    }

const double EPS = 0.000001;

/** **********************************************************************************

 Solve_Square - solve square equation by 3 coefficients.
 
 @param a  The first coefficient of the equation
 @param b  The second coefficient of the equation
 @param c  The third coefficient of the equation
 @param[out] x1  The first solution (will be change, if it exists)
 @param[out] x2  the second solution (will be change, if it exists)
 
 @return  The number of solutions, or -1, if there is an infinite number of them
 
 @note - A comparison accuracy is taken as DBL_EPSILON
       - Uses a define ASSERT for checking the function arguments.
 
*************************************************************************************/

int Solve_Square(double, double, double, double *, double *);

/** **********************************************************************************
 
 main - takes 3 coefficients from the keyboard, put it in Solve_Square function
 and write the result on the screen.
 
 @return  0
 
 @note - Write the solutions with an accuracy of 6 ymbols after a point.
       - Use a define ASSERT for checking the input and Solve_Square function data.
 
*************************************************************************************/

int main()
{
    double a = 0, b = 0, c =0, x1 = 0, x2 = 0;
    int solv_num = 0, eq_num = 0, i = 0;
    
    printf("Please, write, how many equations you want to solve:\n");
    scanf("%d", &eq_num);
    
    for (i = 0; i < eq_num; i++)
    {
        printf("The equation number %d:\n", i + 1);
        
        printf("Please, write a, b and c:\n");
    
        int coef_num = 0;
        coef_num = scanf("%lf %lf %lf", &a, &b, &c);                               /**< Takes from the keyboard 3 coef. */
        ASSERT(coef_num == 3);                                                     /**< Checking the number of coef. */
    
        printf("The current equation: %lg*x^2 + %lg*x + %lg = 0\n", a, b, c);
    
        solv_num = Solve_Square(a, b, c, &x1, &x2);                                /**< Running the Solve_Square function. */
        ASSERT((solv_num >= -1) || (solv_num <= 2));                               /**< Checking the number of solutions. */
    
        if (solv_num == 2)
            printf("There are two solutions:\nx1 = %lg  x2 = %lg", x1 , x2);       /**< Output for 2 differernt solutions */
        else if (solv_num == -1)
            printf("There is an infinite number of solutions.");                   /**< Output for infinitly many solutions. */
        else if (solv_num == 1)
            printf("There is one solution:\nx = %lg", x1);                         /**< Outbut for 1 solution. */
        else
            printf("There is no solutions");                                       /**< Output for an absence of any solutions. */
    
        printf("\n\n");
    }
    return 0;
}

int Solve_Square(double a, double b, double c, double * x1, double * x2)
{
    ASSERT(x1 != NULL);                               /**< Checking the correctness of the "x1" adress */
    ASSERT(x2 != NULL);                               /**< Checking the correctness of the "x2" adress */
    ASSERT(x1 != x2);                                 /**< Checking the difference of "x1" and "x2" adresses */
    
    if (fabs(a) < EPS)                                /**< For a case "a == 0" */
    {
        if (fabs(b) > EPS)
        {
            if (fabs(c) < EPS)
            {
                * x1 = 0;
                return 1;
            }
            else
            {
                * x1 = - c/b;
                return 1;
            }
        }
        else
        {
            if (fabs(c) > EPS)
                return 0;
            else
                return -1;
        }
    }
    else                                             /**< For a case "a != 0" */
    {
        double d = b*b - 4*a*c;
        if (fabs(d) < EPS)
        {
            if (fabs(b) < EPS)
                * x1 = 0;
            else
                * x1 = - b/(2*a);
            return 1;
        }
        if (d > EPS)
        {
            if (fabs(- b + sqrt(d)) < EPS)
                * x1 = 0;
            else
                * x1 = (- b + sqrt(d))/(2*a);
            * x2 = (- b - sqrt(d))/(2*a);
            return 2;
        }
        if (d < EPS)
            return 0;
    }
    return 0;
}

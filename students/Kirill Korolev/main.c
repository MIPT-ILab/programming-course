#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

int SolveSquare(double, double, double, double *, double *);

int main()
{
    printf("Program for solving square equations a*x^2 + b*x + c = 0\n");
    printf("Author: Kirill korolev\n");
    printf("Date: September 21, 2013\n");
    printf("Please, insert a, b, c...\n");
    
    double a = 0, b = 0, c =0, x1 = 0, x2 = 0;
    int solvnum = 0;
    
    int ret = scanf("%lf %lf %lf", &a, &b, &c);
    assert(ret == 3);
    
    printf("%lf*x^2 + %lf*x + %lf = 0\n", a, b, c);
    
    solvnum = SolveSquare(a, b, c, &x1, &x2);
    assert((solvnum >= -1) && (solvnum <= 2));
    
    if (solvnum == 2)
        printf("There are two solutions:\n%lf %lf", x1 , x2);
    else if (solvnum == -1)
        printf("There is an infinite number of solutions.");
    else if (solvnum == 1)
        printf("There is one solution:\n%lf", x1);
    else
        printf("There is no solutions");
    
    return 0;
}

int SolveSquare(double a, double b, double c, double * x1, double * x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);
    
    if (fabs(a) < DBL_EPSILON)
    {
        if (fabs(b) > DBL_EPSILON)
        {
            * x1 = - c/b;
            return 1;
        }
        else
        {
            if (fabs(c) > DBL_EPSILON)
                return 0;
            else
                return -1;
        }
    }
    else
    {
        double d = b*b - 4*a*c;
        if (d > 0)
        {
            * x1 = (- b + sqrt(d))/(2*a);
            * x2 = (- b - sqrt(d))/(2*a);
            return 2;
        }
        else if (fabs(d) < DBL_EPSILON)
        {
            * x1 = - b/(2*a);
            return 1;
        }
        else
            return 0;
    }
}

#include <stdio.h>
#include <math.h>
#include <assert.h>


int SolveSquare (double a, double b, double c,
            double * x1, double * x2);
double abs ( double a);

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    printf ("PROGRAM: SOLUTION OF QUADRATIC EQUATION\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.1 \n");
    printf ("A*x^2 + B*x + C = 0, ENTER A, B, C:\n");
    scanf ("%lf %lf %lf", &a, &b, &c);

    int nRoots = SolveSquare (a, b, c, &x1, &x2);

    if (nRoots == 1)
        printf ("NUMBER OF ROOTS: %d\n %lf", nRoots, x1);
    if (nRoots == 0)
        printf ("NUMBER OF ROOTS: %d\n", nRoots);
    if (nRoots == 2)
        printf ("NUMBER OF ROOTS: %d\n %lf %lf", nRoots, x1, x2);
    if (nRoots == -1)
        printf ("INFINITELY ROOTS");
return 0;
}

int SolveSquare (double a, double b, double c,
            double* x1, double* x2)
{
    assert ( x1 != NULL);
    assert ( x2 != NULL);
    assert ( x1 != x2);

    double EPS = 1e-9;
    double d = b * b - 4 * a * c;
    if ( abs(a) < EPS)
    {
        if ( abs (b) < EPS )
        {
            if ( abs (c) < EPS)
                return -1;
            else
                return 0;
        }
        else
        {
            *x1 = -c / b;
            return 1;
        }

    }
    if ( abs(d) < EPS)
    {
        *x1 = -b / (2 * a);
        return 1;
    }
    if ( abs(d) > EPS && d < 0)
        return 0;
    double sqrt_d = sqrt(d);
    *x1 = (-b + sqrt_d)/(2 * a);
    *x2 = (-b - sqrt_d) /(2 * a);
    return 2;
}

double abs ( double a)
{
    if ( a < 0)
        return -a;
    return a;
}







#include <stdio.h>
#include <math.h>

int kolvoResheniy (double a, double b, double c, double* x1, double* x2);

int main()
{
    double a, b, c, x1=0, x2=0;

    printf("# Please, enter coefficients of square equation\n");
    scanf("%lg %lg %lg", &a, &b, &c);
    switch (kolvoResheniy(a, b, c, &x1, &x2))
    {
        case 0: printf("This equation hasn't got roots\n");
            break;
        case 1: printf("One root\nx = %lg\n", x1);
            break;
        case 2: printf("Two roots\nx1 = %lg\nx2 = %lg", x1, x2);
            break;
        default: printf("Something went wrong!");
            break;
    }
    return 0;
}

int kolvoResheniy (double a, double b, double c, double* x1, double* x2)
{
    const double EPSILON = 0.00000001;
    double D=0;

    D = b*b - 4*a*c;

    if ((D<EPSILON)&&(D>-EPSILON))
    {
        *x1 = -b/(2*a);
        return 1;
    }
    else if (D>0)
    {
        *x1 = (-b+sqrt(D))/(2*a);
        *x2 = (-b-sqrt(D))/(2*a);
        return 2;
    }

    else if (D<0)
    {
        return 0;
    }
}

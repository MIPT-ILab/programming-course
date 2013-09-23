
#include <stdio.h>
#include <assert.h>
#include <math.h>

int solvesquare(double a, double b, double c, double * x1, double * x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);       
                              
    if (a == 0)
    {                         
        if (b != 0)
        {
            * x1 = - c/b;
            return 1;
        }
        else
        {
            if (c != 0)
                return 0;
            else
                return -1;
        }
    }
    else
    {
        double e = 0.000001;  
        double d = b*b - 4*a*c;
        if (d > 0)
        {
            * x1 = (- b + sqrt(d))/(2*a);
            * x2 = (- b - sqrt(d))/(2*a);
            return 2;
        }
        else if ((fabs(d) - e < 0) && (fabs(d) + e > 0))  
                                                          
        {
            * x1 = - b/(2*a);
            return 1;
        }
        else
            return 0;
    }
}

int main()
{
    printf("Program for solving square equations a*x^2 + b*x + c = 0\n");
    printf("Author: Kirill korolev\n");
    printf("Date: the 21th of september, 2013\n");              

    printf("Please, insert a, b, c...\n");
    double a = 0, b = 0, c =0, x1 = 0, x2 = 0;
    int solvnum = 0;
    scanf("%lf %lf %lf", &a, &b, &c);                           
    printf("%d*x^2 + %d*x + %d = 0\n", (int)a, (int)b, (int)c); 
    solvnum = solvesquare(a, b, c, &x1, &x2);
    if (solvnum == 2)
        printf("There are 2 solutions:\n%lf %lf", x1 , x2);
    else if (solvnum == -1)
        printf("There is an endless number of solutions.");     
    else if (solvnum == 1)
        printf("There is 1 solution:\n%lf", x1);
    else
        printf("There is no solutions");                        
                                                                
    return 0;
} 

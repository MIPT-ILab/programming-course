#include <stdio.h>
#include <math.h>
#include <assert.h>

const double eps=0.000001;

int ssq (double a, double b, double c, double* x1, double* x2);

int main ()
{
        int a, b, c;
        double x1, x2;
        
        printf("Please enter coefficients of quadratic equation:\n");
        scanf("%d %d %d", &a, &b, &c);
        x1=0;
        x2=0;
        //int n=ssq(a, b, c, &x1, &x2);
        switch (ssq(a, b, c, &x1, &x2))
        {
                case 3:
                        printf("All x from R\n");
                        break;
                case 2:
                        printf("The equitation has 2 roots:\nx1 = %f, x2 = %f\n", x1, x2);
                        break;
                case 1:
                        printf("The equitation has 1 root:\nx1 = %f\n", x1);
                        break;
                case 0:
                        printf("The equitation has no roots\n");
                        break;
        }
        return 0;
}

int ssq (double a, double b, double c, double* x1, double* x2) // This function solves the equation
{
        int D; // Discriminant of the equation
        
        assert (x1!=0); // Check out if the adresses of variables
        assert (x2!=0); // are not equal to zero
        assert(x1!=x2); // And aren't equal to each other
        
        if (fabs(a)>eps) // Check out if the equation is quadratical
        {
                D=b*b-4*a*c; // Count the discriminant
                if ((D-eps)>0) // That means equation has 2 roots
                {
                        *x1=(-b-sqrt(D))/(2*a);
                        *x2=(-b+sqrt(D))/(2*a);
                        return 2;
                }
                else
                        if ((D+eps)<0) // And here we have no roots
                                return 0;
                        else // The discriminant is equal to zero, and here is only 1 root
                        {
                                *x1=(-b)/(2*a);
                                return 1;
                        }
        }
        else  // The equation is linear
                if (fabs(b)>eps) 
                {
                        *x1=(-c)/b;
                        return 1;
                }
                else    
                        if ((b==0) && (c==0)) // Here we have the equation like 0*x=0. It will be an infinity roots
                                return 3;
                        else 
                                return 0; // And here is const = 0. No roots
}

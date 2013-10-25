//{=================================================================================
//! @file    main.c
//! @date    2013-10-17 00:17
//! @author  Igor Yadrov <igor.yafrov@frtk>
//!
//! solving a quadratic equation with the analysis all cases.
//!
//! @par     condition of task
//!          You must enter the coefficients
//!          program print solve equation or print no solution
//!
//}=================================================================================
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SOLVER_ERR -1
#define SOLVER_OK 1
#define SOLVER_INFINITY 0

int solve(double a, double b, double c,
        double *x1, double *x2);

double discriminant(double a, double b, double c);

int main (int argc, char* argv[]) {
    double a=0;
    double b=0;
    double c=0;
    double x1=0, x2=0;
    int result=0;
    assert (argc==4);

    a=atof(argv[1]);
    b=atof(argv[2]);
    c=atof(argv[3]);
    printf ("\n%g %g %g\n",a, b, c);
    int i=0, k=0;
    int boolean=1;
    char str[1]={'0'};
    // Nice trick. :)
    for (i=1;i<=3;i++) {
            k=strcmp(argv[i], str);
            if ((atof(argv[i])==0)&&(k!=0))
                boolean=0;
    }
    assert(boolean==1);

    result=solve(a,b,c, &x1, &x2);

    switch(result) {
    case SOLVER_INFINITY:
        printf("infinity\n");
        break;
    case SOLVER_ERR:
        printf("no solution\n");
        break;
    case SOLVER_OK:
        printf("%g %g\n",x1,x2);
        break;
    }
    return 0;
}
//{==============================================================================
//! @param      a   Equation a-coefficient
//! @param      b   Equation b-coefficient
//! @param      c   Equation c-coefficient
//! @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
//! @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
//}==============================================================================
int solve(double a, double b, double c,
        double *x1, double *x2) {
    // FIXME And what if x1 or x2 will be equal to 0? Or x1 will be equal to x2?
    // Check this!
    double D;
    double m;
    int cases=SOLVER_OK;
    // FIXME You can't compare doubles directly because of ceiling.
    // For example,
    // double x = 5.;
    // printf("%f", x); // outputs 5.00000000000000000000000001
    // printf("%f", x); // outputs 5.00000000000000000000000002
    // x ==5.; sometimes will be true, sometimes false.
    // Add some parameter 'tolerance' and macro to check doubles.
    if ((a==0)&&(b==0)&&(c==0))
        cases=SOLVER_INFINITY;

    if ((a==0)&&(b==0)&&(c!=0))
        cases=SOLVER_ERR;

    if (a==0) {
            *x1=-c/b;
            *x2=*x1;

    }

    if (a!=0) {
        D=discriminant(a,b,c);
    if (D<0)
        cases=SOLVER_ERR;
    else {
        if (D==0) {
            *x1=(-b)/(2*a);
            *x2=*x1;
        }
        else {
            *x1=(-b+sqrt(D))/(2*a);
            *x2=(-b-sqrt(D))/(2*a);
            if (*x1<*x2) {
                m=*x2;
                *x2=*x1;
                *x1=m;
            }
        }
    }
    }
    return cases;
}

double discriminant(double a, double b, double c) {
    return (b*b-4*a*c);
}

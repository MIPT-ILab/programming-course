/*
 * kv.c
 *
 *  Created on: 12.10.2013
 *      Author: c-dev
 */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

int reshenie(double a, double b, double c,
        double *x1, double *x2);
double diskrimin(double a, double b, double c);

int main (int argc, char* argv[]) {
    double a=0;
    double b=0;
    double c=0;
    double x1=0, x2=0;
    int f=0;

    assert (argc==4);

    a=atof(argv[1]);
    b=atof(argv[2]);
    c=atof(argv[3]);

    f=reshenie(a,b,c, &x1, &x2);

    switch(f) {
    case 0:
        printf("\ninfinity\n");
        break;
    case -1:
        printf("\nnet\n");
        break;
    case 1:
        printf("\n%g %g\n",x1,x2);
        break;
    }
    return 0;
}

int reshenie(double a, double b, double c,
        double *x1, double *x2) {
    double D;
    double m;
    int f=1;

    if ((a==0)&&(b==0)&&(c==0))
        f=0;

    if ((a==0)&&(b==0)&&(c!=0))
        f=-1;

    if (a==0) {
        f=f*1;
        if (c==0) {
            *x1=0;
            *x2=*x1;
        }
        else {
            *x1=-c/b;
            *x2=*x1;
        }
    }

    D=diskrimin(a,b,c);
    if (D<0)
        f=-1;
    else {
        f=1*f;
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
    return f;
}

double diskrimin(double a, double b, double c) {
    return (b*b-4*a*c);
}

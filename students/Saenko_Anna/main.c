#include <stdio.h>
#include <math.h>
#include <assert.h>
    int SolveSquare(double a, double b, double c, double* x1, double* x2);
    int main()
    { double x1, x2;
      double a, b, c;
      printf("# Enter coefficients\n");
      scanf("%lf %lf %lf",&a,&b,&c);
      int nRoots=SolveSquare(a,b,c,&x1,&x2);
      printf("# Equation has %i roots:\n",nRoots);
      if(nRoots==2)
        {printf("%e %e\n",x1,x2);}
      else
        { if(nRoots==1) {printf("%e\n",x1);}
          else {printf(" \n");  }
        }
    }
    int SolveSquare(double a, double b, double c, double  *x1, double *x2)
    { assert(x1!=NULL); assert(x2!=NULL); assert(x1!=x2);   //Precondition tests
      double D=b*b-4*a*c;
      if(D>0)
      { *x1=(-b+sqrt(D))/(2*a);
        *x2=(-b-sqrt(D))/(2*a);
        return 2;
      }
      else
      {  if(D==0) { *x1=-b/(2*a); return 1;}
         else return 0; }
    }




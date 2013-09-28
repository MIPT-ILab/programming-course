#include <stdio.h>
#include <assert.h>
#include <math.h>


#define eps 0.000001

int solve(double a,double b,double c,double* x1,double* x2);

int main()
{
	double a=0, b=0, c=0;
	double x1=0, x2=0;
   
	printf("#enter the coefficients of the equation a*x^2+b*x+c=0\n");
	printf("\n#please enter the coefficient a=");
	scanf("%lg",&a);
   
	printf("#please enter the coefficient b=");
	scanf("%lg",&b);
   
	printf("#please enter the coefficient c=");
	scanf("%lg",&c);
   
    int num = solve(a, b, c, &x1, &x2);
    
    if (num == -1)
    {
        printf("\n#This equation has an infinite number of solutions");
    }
    else if (num == 0)
    {
        printf("\n#This equation has not got solutions");
    }
    else if (num == 1)
    {
        printf("\n#This equation has 1 solution\n");
        printf("%lg",x1);
    }
    else if (num == 2)
    {
        printf("\n#This equation has 2 solutions\n");
        printf("%lg %lg", x1, x2);
    }
    return num;
}




/** ********************************************************************************
 *  solve - solve a square or linear equation specified by its coefficients.
 *
 *  @param      a   Equation a-coefficient
 *  @param      b   Equation b-coefficient
 *  @param      c   Equation c-coefficient
 *  @param[out] x1  1st root of equation, if exist (if not, value will be unchanged)
 *  @param[out] x2  2nd root of equation, if exist (if not, value will be unchanged)
 *
 *  @return         Number of roots or zero if none, -1 if infinite number of roots
 *
 *  @note           Calculation precision is considered to be DBL_EPSILON.
 ***********************************************************************************/



int solve(double a,double b,double c,double* x1,double* x2)
{

    /*Ïðîâåðêà âõîäíûõ äàííûõ*/
    assert(x1!=NULL);
    assert(x2);
    assert(x1!=x2);
    double d=b*b-4*a*c;

    int number=0;
    if (fabs(a)<=eps)
    {
        if (fabs(b)>=eps)
        {
            number=1;
            *x1=-c/b;
        }
        else
        {
            if (fabs(c)<=eps)
            {
                number=-1;//áåñêîíå÷íî ìíîãî ðåøåíèé
            }
            else
            {
                number=0;//ðåøåíèé íåò
            }
        }
        return number;
    }
    if (d>eps)//d>0
    {
        number=2;
        *x1=(-b-sqrt(d))/(2*a);
        *x2=(-b+sqrt(d))/(2*a);
    }
    else if (fabs(d)<=eps)//d==0
    {
        number=1;
        *x1=(-b)/(2*a);
    }
    else //d<0
    {
        number=0;
    }
    return number;
}

#include <math.h>
#include <stdio.h>
#include <assert.h>
#define DOUBLE_EPSILON 1e-16
// FIXME Add commentaries!

int Solve_qv_equation(double a,double b,double c,double *x1,double *x2);
int Solve_lin_equation(double b,double c,double *x);

int main()
{
	double x1=0, x2=0, a=0, b=0, c=0;

	printf("Vvedite kojefficienty kvadratnogo uravnenija(ax^2+bx+c=0) v tom zhe porjadke, chto i v uravnenii:\n");
	assert(scanf("%lg %lg %lg",&a,&b,&c)==3);
  // FIXME And if I will input text instead of numbers?
	int nRoots=Solve_qv_equation(a,b,c,&x1,&x2);

	if(nRoots==0)
		printf("Kornej net.\n");

	if(nRoots==1)
		printf("Uravnenie imeet edinstvennyj koren':\n x=%lg\n",x1);

	if(nRoots==2)
		printf("Korni uravnenija:\n x1=%lg\n x2=%lg\n",x1,x2);

	if(nRoots==-1)
        printf("kornej beskonechnoe mnozhestvo.");

	return 0;
}

/*
функция решает квадратное уравнение,исходя из полученных коэфициентов,
и возвращает
  -1 если корней бесконечной множество
  0 если корней нет
  1 если корень единственный (значнение записывается в x1)
  2 если корня два
*/
int Solve_qv_equation(double a,double b,double c,double *x1,double *x2)
{
    assert(x1!=NULL);
    assert(x2!=NULL);
    assert(x1!=x2);

	double d=0;

/* FIXME You can't check equality of double numbers directly.*/
/*For example,*/
/*double x = 5;*/
/*printf("%f", x); // outputs 5.0000000000000000000000001*/
/*printf("%f", x); // outputs 5.0000000000000000000000002*/
/*bool isEqual = x == 5; // it can be true and false randomly.*/
/*You have to define some macro to solve this issue.
 * Add some 'tolerance' parameter and use it! In this case, conditions below
 * and above can be always 'true'.*/

	if(a==0)
        return Solve_lin_equation( b, c, x1);

	d=pow(b,2)-4*a*c;

  	if(d<=DOUBLE_EPSILON){
		*x2=((-1)*b)/(2*a);
		*x1=*x2;
		return 1;
	}
	if(d>0){
		*x1=((-1)*b+sqrt(d))/(2*a);
		*x2=((-1)*b-sqrt(d))/(2*a);
		return 2;
	}
	else
		return 0;
}

/*
 функция решает линейное уравнение,исходя из полученных коэфициентов,
  и возвращает:
  -1 если корней бесконечной множество
  0 если корней нет
  1 если корень есть,записвая значение в аргумент
*/
int Solve_lin_equation(double b,double c,double *x)
{
    assert(x!=NULL);

    if(b==0 && c==0)
        return -1;
    if(b==0)
        return 0;
    else{
        *x=(-1)*c/b;
        return 1;
    }
}

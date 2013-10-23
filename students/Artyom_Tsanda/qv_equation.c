#include <math.h>
#include <stdio.h>
#include <assert.h>
int Solve_qv_equation(double a,double b,double c,double *x1,double *x2);
int Solve_lin_equation(double b,double c,double *x);

int main()
{
	double x1=0, x2=0, a=0, b=0, c=0;

	printf("Vvedite kojefficienty kvadratnogo uravnenija(ax^2+bx+c=0) v tom zhe porjadke, chto i v uravnenii:\n");
	scanf("%lg %lg %lg",&a,&b,&c);
    // FIXME I think, that you should to add some checks over input
    // [crady@cradylap Artyom_Tsanda]$ ./a.out
    // Vvedite kojefficienty kvadratnogo uravnenija(ax^2+bx+c=0) v tom zhe porjadke, chto i v uravnenii:
    // q
    // kornej beskonechnoe mnozhestvo.
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
// FIXME You can't compare doubles directly because of ceiling.
// For example,
// double x = 5.;
// printf("%f", x); // outputs 5.00000000000000000000000001
// printf("%f", x); // outputs 5.00000000000000000000000002
// x ==5.; sometimes will be true, sometimes false.
// Add some parameter 'tolerance' and macro to check doubles.
	if(a==0)
        return Solve_lin_equation( b, c, x1);

	d=pow(b,2)-4*a*c;

	if(d==0){
		*x2=((-1)*b)/(2*a);
		*x1=*x2;
        // FIXME It is not obvious, what is returned by the function.
        // You can do following:
        // #define SOLVER_OK -1
        // #define SOLVER_ERR 0
        // and so on. If you want, you can study 'enum' thing, it will be preferable solution here
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

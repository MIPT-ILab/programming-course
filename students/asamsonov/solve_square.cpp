#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include <assert.h> 

// Программа решает квадратное уравнение. 

#define LITTLE 0.000001 // LITTLE верхним регистром смотрится необычно. :) 

int solve_square(double a, double b, double c, double *x1, double *x2); //Возвращает в х1, х2 корни квадратного уравнения. 

int main(int argc, const char *argv[])
{
    double a = 0, b = 0, c = 0; 

    printf ("Put a, b and c from ax^2 + bx + c in.\n"); //>>> Input ;) >>> input - noun, put in - verb.                  
    //>>> Неплохо бы проверить, что возвращает сканф! 
	  if (scanf ("%lg %lg %lg", &a, &b, &c) == NULL) return printf ("Input is not valid.\n"), 1;

    double x1 = 0, x2 = 0; 
	  int nRoots = solve_square (a, b, c, &x1, &x2);       

    // Return check block. 

	  switch (nRoots) 
    { 
		    case 0: printf ("Solutions: x1 = %lg; x2 = %lg\n", x1, x2);   break; 
	      case 1: printf ("Solution: x1 = x2 = %lg\n", x1);             break; 
        case 2: printf ("No solutions in R set.\n");                  break; 
        case 3: printf ("Solution: x1 = x2 = any number in R.\n");    break; 
        default: printf ("ERROR! Undocumented return %d!\n", nRoots); return 1; 
    } 

	  return 0; //...
} 

int solve_square(double a, double b, double c, double *x1, double *x2) // Возвращает в х1, х2 корни квадратного уравнения. 
{ 
	  assert(x1); assert(x2); assert(x1 != x2);  // <<< Pre-condition. 

	  double D = b*b - 4*a*c; 
    //const double LITTLE = 0.000001; // Константа для сравнения Double с нулем. 
		// Что лучше использовать: глобальные константы или define?

    if (fabs (a) < LITTLE) {// Если коэффициент а = 0. --- Лучше fabs (a) < EPS 
        /* bx + c = 0; bx = -c; x = -c/ b*/ 
	      if ((fabs (b) < LITTLE) && (fabs (c) > LITTLE)) { return 2; }      // Нет решений в R. 
        else if ((fabs (b) < LITTLE) && (fabs (c) < LITTLE)) { return 3; } // Решение - любое число в R. 
        else { 
			      *x1 = (-c / b); 
            return 1; // Один корень. >>> one team, one love, one root)) -- nostalgy?
        } 
	  } 
    else { 
		    if (D > LITTLE) { // Дискриминант > 0. 
			      D = sqrt(D); 
		        *x1 = (-b - D) / (2 * a); 
		        *x2 = (-b + D) / (2 * a); 
	          return 0; // Два корня, все отлично. 
		    } 
		    else if ((D < LITTLE) && (D > -LITTLE)) { // Дискриминант = 0. 
			      *x1 = (-b / (2 * a)); 
			      return 1; // Один корень. 
		    } 
		    else { return 2; } // Нет корней в R. 
    } 
	  /* DOCS OF RETURN. 
    : 0 - 2 корня. 
	  : 1 - 1 корень. 
    : 2 - Нет корней. 
    : 3 - Корень - любое действительное число. 
    : 4 - Некий EF. // EF - Epic Fail.
    */  
	  return 4; 
}
// Кстати, когда делаю commit, табуляция бьется. (Если в edit copy-paste делать - то же.) Как с этим бороться?
// И что насчет комментов? Какие-то проблемы с кодировкой. "регистр" -> "ðåãèñòð" не радует.
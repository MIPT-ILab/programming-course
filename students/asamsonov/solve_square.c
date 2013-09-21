#include <stdio.h>
#include <math.h>
#include <assert.h>
// Программа решает квадратное уравнение.
int solve_square(double a, double b, double c, double *x1, double *x2); // Возвращает в х1, х2 корни квадратного уравнения.

int main(int argc, const char *argv[]) // Is it really such a main thing?
{
	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0; 
	int nRoots = 0;
	printf("Put a, b, c from ax^2 + b + c in.\n");
	scanf_s("%lg %lg %lg", &a, &b, &c);
	nRoots = solve_square(a, b, c, &x1, &x2);
	// Return check block.
	if (nRoots == 0) { printf("Solutions: x1 = %lg; x2 = %lg\n", x1, x2); }
	else if (nRoots == 1) { printf("Solution: x1 = x2 = %lg\n", x1); }
	else if (nRoots == 2) { printf("No solutions in set R.\n"); }
	else if (nRoots == 3) { printf("Solution: x1 = x2 = any number in R.\n"); }
	else { printf("ERROR! Undocumented return!\n"); }
	return 0; // It returns 0.
}

int solve_square(double a, double b, double c, double *x1, double *x2) // Возвращает в х1, х2 корни квадратного уравнения.
{
	double D = b*b - 4*a*c;
	// Pre-condition.
	assert(x1); assert(x2); assert(x1 != x2);
	if ((a < 0.000001) && (a > -0.000001)) { // Если коэффициент а = 0.
		/* bx + c = 0; bx = -c; x = -c/ b*/
		if ((b == 0) && (c != 0)) { return 2; } // Нет решений в R.
		else if ((b == 0) && (c == 0)) { return 3; } // Решение - любое число в R.
		else { 
			*x1 = (-c / b); 
			return 1; // Один корень.
		}
	}
	else {
		if (D > 0.000001) { // Дискриминант > 0.
			D = sqrt(D);
			*x1 = (-b - D) / (2 * a);
			*x2 = (-b + D) / (2 * a);
			return 0; // Два корня, все отлично.
		}
		else if ((D < 0.000001) && (D > -0.000001)) { // Дискриминант = 0.
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
	: 4 - Некий EF.
	*/
	return 4;
}
#include <stdio.h>
#include <math.h>
#include <assert.h>
// ��������� ������ ���������� ���������.
int solve_square(double a, double b, double c, double *x1, double *x2); // ���������� � �1, �2 ����� ����������� ���������.

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

int solve_square(double a, double b, double c, double *x1, double *x2) // ���������� � �1, �2 ����� ����������� ���������.
{
	double D = b*b - 4*a*c;
	// Pre-condition.
	assert(x1); assert(x2); assert(x1 != x2);
	if ((a < 0.000001) && (a > -0.000001)) { // ���� ����������� � = 0.
		/* bx + c = 0; bx = -c; x = -c/ b*/
		if ((b == 0) && (c != 0)) { return 2; } // ��� ������� � R.
		else if ((b == 0) && (c == 0)) { return 3; } // ������� - ����� ����� � R.
		else { 
			*x1 = (-c / b); 
			return 1; // ���� ������.
		}
	}
	else {
		if (D > 0.000001) { // ������������ > 0.
			D = sqrt(D);
			*x1 = (-b - D) / (2 * a);
			*x2 = (-b + D) / (2 * a);
			return 0; // ��� �����, ��� �������.
		}
		else if ((D < 0.000001) && (D > -0.000001)) { // ������������ = 0.
			*x1 = (-b / (2 * a));
			return 1; // ���� ������.
		}
		else { return 2; } // ��� ������ � R.
	}
	/* DOCS OF RETURN.
	: 0 - 2 �����.
	: 1 - 1 ������.
	: 2 - ��� ������.
	: 3 - ������ - ����� �������������� �����.
	: 4 - ����� EF.
	*/
	return 4;
}
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include <assert.h> 

// ��������� ������ ���������� ���������. 

#define LITTLE 0.000001 // LITTLE ������� ��������� ��������� ��������. :) 

int solve_square(double a, double b, double c, double *x1, double *x2); //���������� � �1, �2 ����� ����������� ���������. 

int main(int argc, const char *argv[])
{
	double a = 0, b = 0, c = 0; 

    printf ("Put a, b and c from ax^2 + bx + c in.\n"); //>>> Input ;) >>> input - noun, put in - verb.                  //>>> ������� �� ���������, ��� ���������� �����! 
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

int solve_square(double a, double b, double c, double *x1, double *x2) // ���������� � �1, �2 ����� ����������� ���������. 
{ 
	assert(x1); assert(x2); assert(x1 != x2);  // <<< Pre-condition. 

	double D = b*b - 4*a*c; 
        //const double LITTLE = 0.000001; // ��������� ��� ��������� Double � �����. 
		// ��� ����� ������������: ���������� ��������� ��� define?

    if (fabs (a) < LITTLE) {                 // ���� ����������� � = 0. --- ����� fabs (a) < EPS 
                /* bx + c = 0; bx = -c; x = -c/ b*/ 
		if ((fabs (b) < LITTLE) && (fabs (c) > LITTLE)) { return 2; }      // ��� ������� � R. 
        else if ((fabs (b) < LITTLE) && (fabs (c) < LITTLE)) { return 3; } // ������� - ����� ����� � R. 
        else { 
			*x1 = (-c / b); 
            return 1; // ���� ������. >>> one team, one love, one root)) -- nostalgy?
        } 
	} 
    else { 
		if (D > LITTLE) { // ������������ > 0. 
			D = sqrt(D); 
		    *x1 = (-b - D) / (2 * a); 
		    *x2 = (-b + D) / (2 * a); 
	        return 0; // ��� �����, ��� �������. 
		} 
		else if ((D < LITTLE) && (D > -LITTLE)) { // ������������ = 0. 
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
    : 4 - ����� EF. // EF - Epic Fail.
    */  
	return 4; 
} 

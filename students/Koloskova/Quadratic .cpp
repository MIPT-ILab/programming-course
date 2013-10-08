//{=================================================================================
//! @file    Quadratic.cpp
//! @date    2013-10-06 21:40
//! @author  Nastya Koloskova <anastasia.kolosok@gmail.com>
//!
//! Решение квадратного уравнения.
//!
//! @par     Условие задачи
//!          Программа вводит 3 коэффициента квадратного уравнения. Надо вывести его
//!          корни.
//}=================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>

enum QuadraticalRet {
	NO_ROOTS,
	ONE_ROOT,
	TWO_ROOTS,
	INFINITE_ROOTS,
	ERROR
};

QuadraticalRet SloveQuadratical(double coeffs[3], double *root1, double *root2);

int main()
{
    int i;
    double coeffs[3];
    printf("Hello! This program solves quadratic equations.\nEnter the coefficients of ax^2+bx+c\na, b, c = ");
    for (i = 0; i < 3; i++)
        scanf("%lg", &coeffs[i]);
    double x1 = 0, x2 = 0;
    QuadraticalRet nRoots = SloveQuadratical(coeffs, &x1, &x2);

    if (nRoots == NO_ROOTS)
        printf("Equation with given coefficients has no solution\n");
    if (nRoots == ONE_ROOT)
        printf("x=%lg\n", x1);
    if (nRoots == TWO_ROOTS)
        printf("x1=%lg, x2=%lg\n", x1, x2);
    if (nRoots == INFINITE_ROOTS)
        printf("Equation has infinitely many solutions\n");
    return 0;
}

//{=================================================================================
//! SolveQuadratical - Решает квадратное уравнение, заданное своими коэффициентами.
//!
//! @param      coeffs[3]  массив коэффициентов a, b, c
//! @param[out] root1      1-ый корень уравнения (если не существует, не изменяется)
//! @param[out] root2      2-ой корень уравнения (если не существует, не изменяется)
//!
//! @return                Количество корней уравнения (ONE_ROOT, TWO_ROOTS, NO_ROOTS,
//!                        INFINITE_ROOTS).
//!
//! @note                  Точность вычислений 0.00001.
//}=================================================================================

QuadraticalRet SloveQuadratical(double coeffs[3], double *root1, double *root2)
{
    assert(root1);
    assert(root2);
    assert(root1 != root2);
    const double EPS = 0.00001;

    double d = coeffs[1] * coeffs[1] - 4 * coeffs[2] * coeffs[0];

    if ((fabs(coeffs[0])) < (EPS))
    {
        if ((fabs(coeffs[1])) < (EPS))
            if ((fabs(coeffs[2])) > (EPS))      // (a == 0 && b == 0 && c != 0)
                return NO_ROOTS;
            else            // (a == 0 && b == 0 && c == 0)
                return INFINITE_ROOTS;
        else                // (a == 0 && b != 0)
        {
            *root1 = -coeffs[2]/coeffs[1];
            return ONE_ROOT;
        }

    }
    else                    // (a != 0)
        if ((fabs(d)) < (EPS))   // (a != 0 && d == 0)
        {
            *root1 = -coeffs[1]/(2 * coeffs[0]);
            return ONE_ROOT;
        }
        else
            if (d < 0)           // (a != 0 && d < 0)
                return NO_ROOTS;
            else                // (a != 0 && d > 0)
            {
                *root1 = (-coeffs[1] + sqrt(d))/(2 * coeffs[0]);
                *root2 = (-coeffs[1] - sqrt(d))/(2 * coeffs[0]);
                return TWO_ROOTS;
            }
}

//{=================================================================================
//! @file    SolveSquare.c
//! @date    2013-10-16 21:50
//! @author  Vladimir Panov <volodka.1995@gmail.com>
//!
//! Решение квадратного уравнения с честным разбором частных случаев.
//!
//! @par     Условие задачи
//!          Программа вводит 3 коэффициента квадратного уравнения. Надо вывести
//!          количество его корней (-1 в случае бесконечного их к-ва) и сами корни.
//}=================================================================================

#include <stdio.h>
#include <math.h>

//{=================================================================================
//! LineSolve - Решает линейное уравнения по заданным коэффициентам
//!
//! @param      b   Коэффициент при X
//! @param      c   Свободный член
//!
//! @return         Возвращает число корней, или -1, если их нет,
//! 				или 3, если их бесконечно много
//!
//! @note           Вычисляет корень линейного уравнения, если такой имеется.
//}=================================================================================
// FIXME And if I want to use results from the solver? Return them!
int LineSolve( const double b, const double c) {
	double x = 0; //! Единственный возможный корень уравнения
    // FIXME You can't compare doubles directly because of ceiling.
    // For example,
    // double x = 5.;
    // printf("%f", x); // outputs 5.00000000000000000000000001
    // printf("%f", x); // outputs 5.00000000000000000000000002
    // x ==5.; sometimes will be true, sometimes false.
    // Add some parameter 'tolerance' and macro to check doubles.
	if( b != 0) {
		x = -c / b;
		printf("# Число корней:\n1 \n # Его значение:\n%lg \n", x);
		return 1;
	}
	else{
		if(c != 0) {
			printf("# Нет решения \n-1 \n");
			return -1;
		}
		else {
			printf("# Бесконечно много корней \n3 \n");
			return 3;
		}
	}
}

//{=================================================================================
// FIXME Linear or square? :)
//! LineSolve - Решает линейное уравнения по заданным коэффициентам
//!
//! @param      a   Коэффициент при X^2
//! @param      b   Коэффициент при X
//! @param      c   Свободный член
//!
//! @return         Возвращает число корней, или -1, если их нет,
//! 				или 3, если их бесконечно много
//!
//! @note           Вычисляет корни квадратного уравнения, если такие имеется.
//!					Либо выводит сообщение об их отсутствии
//}=================================================================================
// FIXME And if I want to use results from the solver? Return them!
int SquareSolve( const double a, const double b, const double c) {
	double D = b*b - 4 * a * c; //! Дискрименант уравнения
	if( D < 0) {
		printf("# Нет решения \n-1 \n");
		return -1;
	}
	else {
		if(D == 0) {
			double x = -b / (2 * a);
			printf("# Число корней:\n1 \n# Его значениe: \n%lg \n", x);
			return 1;
		}
		else {
			double x1 = (-b + sqrt( D )) / (2 * a);
			double x2 = (-b - sqrt( D )) / (2 * a);
			printf("# Число корней: \n2 \n# Их значения: \n%lg %lg \n", x1, x2);
			return 2;
		}
	}
}

int main(int argc, char* argv[]) {
	double a = 0; //! Коэффициент при X^2
	double b = 0; //! Коэффициент при X
	double c = 0; //! Свободный член
	char ScanfComplite = 0; //! Число удачных считываний коэффициентов
	char TerminalScanf = 0; //! Флаг, показывающий удачный ввод с терминала
	if( argc == 4) {
		ScanfComplite += sscanf(argv[1], "%lg", &a);
		ScanfComplite += sscanf(argv[2], "%lg", &b);
		ScanfComplite += sscanf(argv[3], "%lg", &c);
		if(ScanfComplite == 3) TerminalScanf = 1;
	}
	if(! TerminalScanf)
    //FIXME
    // [crady@cradylap solve]$ ./a.out 
    // s
    // # Infinite number of roots
    // 3 
    // You should to add some checks over user's input
		scanf("%lg %lg %lg", &a, &b, &c); //! Если не было воода с терминала считать с окна
    // FIXME You can't compare doubles directly because of ceiling.
    // For example,
    // double x = 5.;
    // printf("%f", x); // outputs 5.00000000000000000000000001
    // printf("%f", x); // outputs 5.00000000000000000000000002
    // x ==5.; sometimes will be true, sometimes false.
    // Add some parameter 'tolerance' and macro to check doubles.
	if(a == 0)
		LineSolve( b, c); //! Решение линейного уравнения
	else
		SquareSolve( a, b, c); //! Решение квадратного уравнения
	return 0;
}

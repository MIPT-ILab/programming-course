//{=================================================================================
//! @file    SolveSquare.c
//! @date    2013-10-16 21:50
//! @author  Vladimir Panov <volodka.1995@gmail.com>
//!
//! ������� ����������� ��������� � ������� �������� ������� �������.
//!
//! @par     ������� ������
//!          ��������� ������ 3 ������������ ����������� ���������. ���� �������
//!          ���������� ��� ������ (-1 � ������ ������������ �� �-��) � ���� �����.
//}=================================================================================

#include <stdio.h>
#include <math.h>

//{=================================================================================
//! LineSolve - ������ �������� ��������� �� �������� �������������
//!
//! @param      b   ����������� ��� X
//! @param      c   ��������� ����
//!
//! @return         ���������� ����� ������, ��� -1, ���� �� ���,
//! 				��� 3, ���� �� ���������� �����
//!
//! @note           ��������� ������ ��������� ���������, ���� ����� �������.
//}=================================================================================
// FIXME And if I want to use results from the solver? Return them!
int LineSolve( const double b, const double c) {
	double x = 0; //! ������������ ��������� ������ ���������
    // FIXME You can't compare doubles directly because of ceiling.
    // For example,
    // double x = 5.;
    // printf("%f", x); // outputs 5.00000000000000000000000001
    // printf("%f", x); // outputs 5.00000000000000000000000002
    // x ==5.; sometimes will be true, sometimes false.
    // Add some parameter 'tolerance' and macro to check doubles.
	if( b != 0) {
		x = -c / b;
		printf("# ����� ������:\n1 \n # ��� ��������:\n%lg \n", x);
		return 1;
	}
	else{
		if(c != 0) {
			printf("# ��� ������� \n-1 \n");
			return -1;
		}
		else {
			printf("# ���������� ����� ������ \n3 \n");
			return 3;
		}
	}
}

//{=================================================================================
// FIXME Linear or square? :)
//! LineSolve - ������ �������� ��������� �� �������� �������������
//!
//! @param      a   ����������� ��� X^2
//! @param      b   ����������� ��� X
//! @param      c   ��������� ����
//!
//! @return         ���������� ����� ������, ��� -1, ���� �� ���,
//! 				��� 3, ���� �� ���������� �����
//!
//! @note           ��������� ����� ����������� ���������, ���� ����� �������.
//!					���� ������� ��������� �� �� ����������
//}=================================================================================
// FIXME And if I want to use results from the solver? Return them!
int SquareSolve( const double a, const double b, const double c) {
	double D = b*b - 4 * a * c; //! ������������ ���������
	if( D < 0) {
		printf("# ��� ������� \n-1 \n");
		return -1;
	}
	else {
		if(D == 0) {
			double x = -b / (2 * a);
			printf("# ����� ������:\n1 \n# ��� �������e: \n%lg \n", x);
			return 1;
		}
		else {
			double x1 = (-b + sqrt( D )) / (2 * a);
			double x2 = (-b - sqrt( D )) / (2 * a);
			printf("# ����� ������: \n2 \n# �� ��������: \n%lg %lg \n", x1, x2);
			return 2;
		}
	}
}

int main(int argc, char* argv[]) {
	double a = 0; //! ����������� ��� X^2
	double b = 0; //! ����������� ��� X
	double c = 0; //! ��������� ����
	char ScanfComplite = 0; //! ����� ������� ���������� �������������
	char TerminalScanf = 0; //! ����, ������������ ������� ���� � ���������
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
		scanf("%lg %lg %lg", &a, &b, &c); //! ���� �� ���� ����� � ��������� ������� � ����
    // FIXME You can't compare doubles directly because of ceiling.
    // For example,
    // double x = 5.;
    // printf("%f", x); // outputs 5.00000000000000000000000001
    // printf("%f", x); // outputs 5.00000000000000000000000002
    // x ==5.; sometimes will be true, sometimes false.
    // Add some parameter 'tolerance' and macro to check doubles.
	if(a == 0)
		LineSolve( b, c); //! ������� ��������� ���������
	else
		SquareSolve( a, b, c); //! ������� ����������� ���������
	return 0;
}

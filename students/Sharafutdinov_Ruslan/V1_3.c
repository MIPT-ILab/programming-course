/* �������� ���������, ������� ��������� ����� �� ������ ����� "��������" �� ������������ ����� �������� � ������ 1, 4^1, 4^2 ...
������ ������ ���� ������ � ����� ����������. ��������, ��� ����� ���� 4*n+2 ���������� �������� ��������� �������.
����� 4*n, 4*n+1, 4*n -1 , ����� �������� ����� � ������ �����, ����� ����� �������� n.
������ �����. ����������� ����� N, 0<= N <2^31.
������ ������. ���� ������, ���������� "YES" ��� "NO". */


#include <stdio.h>
#include <math.h>

int Hang( int number);

int main()
{
    int number = 0;

    printf ("PROGRAM: HANGING\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER THE NUMBER\n");
    scanf ("%ld", &number);

    if (Hang(number))
        printf ("YES");
    else
        printf ("NO");
    return 0;
}

int Hang( int number)
{
    if ( number == 0)
        return 0;
    while ( number >= 4)
    {
        if ( number % 4 == 2)
            return 0;
        else
        {
                if ( number % 4 == 3)
                    number = (number / 4) +1;
                else
                    number  = number / 4;
        }
    }
    if ( number == 0 || number == 1 )
        return 1;
    else
        return 0;

}

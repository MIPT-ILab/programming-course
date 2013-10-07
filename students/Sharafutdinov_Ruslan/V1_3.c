/* Напишите программу, которая проверяет можно ли данное число "взвесить" на двухчашечных весах гирьками с весами 1, 4^1, 4^2 ...
Каждая гирька есть только в одном экземпляре. Известно, что числа вида 4*n+2 невозможно взвесить указанным образом.
Числа 4*n, 4*n+1, 4*n -1 , можно взвесить тогда и только тогда, когда можно взвесить n.
Формат ввода. Натуральное число N, 0<= N <2^31.
Формат вывода. Одна строка, содержащая "YES" или "NO". */

//{====================================================================================
//! @file V1_3.c
//! @date    2013-09-29 20:45
//! @author Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Programm checks, can you weigh number on balance with
//! mass = 4 ^ k (k = 0, 1, 2...
//!
//! @par The programme enters number
//!      It needs to output YES if you can weigh this number
//!                         NO if you cannot weigh this number
//}====================================================================================


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
//! Hang - checks, can you weight this number or not
//!
//! @param      number  number
//!
//! @return         1 - if you can
//!                 0 - if you can not

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

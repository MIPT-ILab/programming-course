//{=================================================================================
//! @file    double_qsort.c
//! @date    2013-10-04 00:25
//! @author  Evgeny Orekhov <orekhovyevgeniy@gmail.com>
//!
//! Сортировка по возростанию массива чисел, с плавающей точкой.
//!
//! @par     Условие задачи:
//!          Программа вводит длинну массива и его элементы. Надо вывести
//!          отсортированый по возрастанию массив.
//!          
//! @warning Длина массива не должна превышать 1000 элементов!
//}=================================================================================

#include <stdio.h>

//{=================================================================================
//! min - returns to significance of function a smaller element.
//!
//! @param      p   first element
//! @param      q   second element
//!
//! @return         -1 if first element bigger then second, 1 if second element
//!                 bigger then first, 0 if they are equal.
//}=================================================================================

int min(double *p, double *q)
{
    if ((*p-*q)<0) 
       return -1;
    else
       if ((*p-*q)>0)
          return 1;
       else
          return 0;         
}    

int main ()
{
    int n=0,i=0;
    double a[99];
    printf("#Enter the massif length:\n");
    scanf("%i",&n);
    printf("#Enter massif's elements:\n");
    for(i=0;i<=(n-1);i++)
       scanf("%lg",&a[i]);
    qsort(a,n,sizeof(double),min);
    printf("The sorted massif:\n");
    for(i=0;i<=(n-1);i++)
       printf("%lg ",a[i]);
    system("pause");
    return 0;
}

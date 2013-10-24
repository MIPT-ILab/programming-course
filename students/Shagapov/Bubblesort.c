//{=================================================================================
//! @file    Buble-sort.cpp
//! @date    2013-10-05 20:10
//! @author  Ayaz Shagapov <ayaz.shagapov@frtk.ru>
//!
//! Реализация сортировки массива пузырьковым методом
//!
//! @par     Условие задачи
//!            1.Требуется написать функцию  с именем BubleSort, принимающую
//!          указатель на начало массива, который необходимо отсортировать, и длину
//!          этого массива. Функция сортирует массив, не сохраняя исходные порядок данных.
//!            2. Функция реализована для типа Integer, в перспективе реализация для произвольного
//!          типа данных.
//!
//! @warning   1.Функция BubleSort может изменить или уничтожить исходные данные, так как работает
//!          непосредственно с указтелями!
//!            3.Функция по умолчанию сортирует данные в порядке возрастания.
//}================================================================================


    /* choose for realise */
//#define  dbg  if(0)

    /* chosee for debugging */
#define  dbg  if(1)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^
//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^     NEW FUNCTION       ^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^ ^_^^_^^_^^_^^_^^_^^_^^_^^_^^^
//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^


//{=================================================================================
//!
//! Bubble_sort - array of double or integer numbers sorted by bubble-algorithm
//!
//! @param         DatePoint,   int*,   Point to DataArray (point on zero element)
//! @param         DateSize,    int ,    Size of DataArray  (element's number)
//!
//! @param[out]    *DataPoint,  int*,   Point to sorted DataArray (point on zero element)
//!
//! @return        1 if sorted success, 0  if sorted isn't success or function not sorted dates,
//!                and -1 if input isnt correct
//!
//}===========================================================================

int Bubble_sort (int* DataPoint, int DataSize)
{
//----------------------------------------------- Input check-----------------

dbg  assert ( DataPoint             !=  NULL         );
dbg  assert ( sizeof (DataPoint[0]) ==  sizeof (int) );
     if     ( sizeof (DataPoint[0]) !=  sizeof (int) )                        // Если вес полученной переменной не совпадает
             return -1;                                                       // с весом int, то это плохо, поэтому вернем -1.

//----------------------------------------------- Input check-----------------

     int i = 0, j = 0;                                                        //! Just counters for circle i and j :)
     int Buffer = 0;                                                          //! It is buffer value for swap

     for ( i = 0; i < DataSize; i++ )                                          // Это обычный
         {                                                                     // "пузырьковый"
            for ( j = 0; j < DataSize-1; j++ )                                 // алгоритм
                {
                    if ( DataPoint[j]  > DataPoint[j+1])                       // Сравним по величине 2 элемента
                                                                               // И если они стоят в неверном порядке.
                       {
                           Buffer            =  DataPoint [j+1];               // Поменяем
                           DataPoint [j+1]   =  DataPoint [j];                 // Их
                           DataPoint [j]     =  Buffer;                        // Местами

dbg                        assert ( DataPoint [j] < DataPoint [j+1] );         // Убедимся что смена элементов верно реализована.
                       }
                }
         }

dbg  assert ( i == DataSize );                                                  // Убедимся, что первичный цикл прошел полностью,
                                                                                // Это необходимо для полной сортировки.

//-----------------------------------------------Output-------------------------

     for( i = 0; i < DataSize ; i++ )                                           // Проверим массив на упорядоченность.
     if     ( DataPoint[i+1] > DataPoint[i] )                                   // Если это не так, то все очень плохо(
         return 0;                                                              // Вернем 0.

         return 1;                                                              // А если все хорошо-вернем 1 :)

//-----------------------------------------------Output-------------------------

}

//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^
//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^     MAIN FUNCTION       ^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^ ^_^^_^^_^^_^^_^^_^^_^^_^^_^^^
//^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^^_^

int main()
{
    int i = 0,
        massive [10] = { 2, 1, 1, 4, 5, 6, 8, 7, 4, 10 };

    Bubble_sort ( &massive[0], 10 );                // демонстрация
                                                    // работы
    for ( i = 0; i < 10; i++ )                      // функций
         printf (" %i ", massive[ i ] );            // Bubble_sort

    return 0;

}

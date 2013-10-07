//{=================================================================================
//! @file    qSort_1.2.c
//! @date    07.10.2013
//! @author  Dmitry Stupakov <dmitry.stupakov@frtk.ru>
//!
//!          Sort array of integer
//!
//! @par     Task
//!          Программа получает на вход мощность массива <30000, затем сам массив
//!          На выходе выдается отсортированный по возрастанию массив.
//}=================================================================================

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/** ********************************************************************************
 Minimum - compare 2 numbers
 
 @param      *arg1   first argument
 @param      *arg2   second argument
 
 @return         0,  if arg1=arg2
                 -1, if arg1<arg2
                 1,  if arg1>arg2
************************************************************************************/

int Minimum(double* arg1, double* arg2)
{
	if (*arg1 < *arg2)
		return -1;
	else
		if (*arg1 > *arg2)
			return 1;
		else
			return 0;
}

const int MAX_DataSize = 30000; // Max length of array

int main()
{
	int i = 0, DataSize = 0, RED = 0;
	double Data[30000] = {0};  // Data[MAX_DataSize] only in C++

	printf("#Author Dmitry Stupakov\n"                              
		   "#Version 1.2\n"
		   "#07.10.2013\n"
		   "#Enter the number of array elements:\n");
	RED = scanf("%i", &DataSize);
	assert(RED == 1);
	assert(0 < DataSize && DataSize <= MAX_DataSize);

	printf("#Enter elements:\n");                      
    for (i = 0; i < DataSize; i++)
	{
	    RED = scanf("%lg", &Data[i]);
		assert(RED == 1);	
	}

    qsort(Data, DataSize, sizeof(double), Minimum);   

    printf("#Sorted array:\n");
    for(i = 0; i < DataSize; i++)
	    printf("%lg ", Data[i]);
	printf("\n");

	system("pause");
	return 0;
}
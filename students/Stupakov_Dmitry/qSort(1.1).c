//{=================================================================================
//! @file    qSort.c
//! @date    03.10.2013
//! @author  Dmitry Stupakov <dmitry.stupakov@frtk>
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
 
 @param      arg1   first arguement
 @param      arg2   second arguement
 
 @return         0, if arg1=arg2
                 -1, if arg1<arg2
				 1, if arg1>arg2
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

int main()
{
	int i = 0, DataSize = 0;
	double Data[30000] = {0};

	printf("#Author Dmitry Stupakov\n"                              
		   "#Version 1.1\n"
		   "#03.10.2013\n"
		   "#Enter the number of array elements:\n");
	scanf("%i", &DataSize);
	printf("#Enter elements:\n");

	assert(DataSize < 30001);                                       
	assert(DataSize > 0);

    for(i = 0; i < DataSize; i++)
	    scanf("%lg", &Data[i]);
    qsort(Data, DataSize, sizeof(double), Minimum);

	printf("#Sorted array:\n");
    for(i = 0; i < DataSize; i++)
	    printf("%lg ", Data[i]);
	printf("\n");

	system("pause");
	return 0;
}
//{=================================================================================
//! @file    qSort_1.2.c
//! @date    08.10.2013
//! @author  Dmitry Stupakov <dmitry.stupakov@frtk.ru>
//!
//!          Sort array of integer
//!
//! @par     Task
//!          In - length of array of doble
//!          Out - sort array (min to max)
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
	int i = 0, DataSize = 0, proof = 0;
	double Data[30000] = {0};  // Data[MAX_DataSize] only in C++
                               // Don't work at Visual Studio 2100 and Devian C++

	printf("#Author Dmitry Stupakov\n"                              
		   "#Version 1.3\n"
		   "#08.10.2013\n"
		   "#Enter the number of array elements:\n");
	proof = scanf("%i", &DataSize);
	assert(proof == 1);
	assert(0 < DataSize && DataSize <= MAX_DataSize);

	printf("#Enter elements:\n");                      
    for (i = 0; i < DataSize; i++)
	{
	    proof = scanf("%lg", &Data[i]);
		assert(proof == 1);	
	}

    qsort(Data, DataSize, sizeof(double), Minimum);   

    printf("#Sorted array:\n");
	for(i = 0; i < DataSize; i++)
		printf("%lg ", Data[i]);
	printf("\n");

	system("pause");
	return 0;
}
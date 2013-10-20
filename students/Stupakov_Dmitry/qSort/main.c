//{=================================================================================
//! @file    main.c
//! @date    18.10.2013
//! @author  Dmitry Stupakov <dmitry.stupakov@frtk.ru>
//!
//!          Sort array of integer
//!
//! @par     Task
//!          In - length of array of doble
//!          Out - sort array (min to max)
//!          Do it with dynamic memory allocation
//}=================================================================================

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int Compare(const void* arg1, const void* arg2);

int main()
{
	int i = 0, DataSize, proof = 0;
	double *Data;

	printf("#Author Dmitry Stupakov\n"                              
			"#Version 1.5\n"
			"#18.10.2013\n"
			"#Enter the number of array elements:\n");
	proof = scanf("%i", &DataSize);
	assert(proof == 1);

	Data = (double*) calloc(DataSize, sizeof (Data[0]));
	assert(Data != NULL);

	printf("#Enter elements:\n");                      
	for (i = 0; i < DataSize; i++)
	{
		proof = scanf("%lg", &Data[i]);
		assert(proof == 1);	
	}

	qsort(Data, DataSize, sizeof (Data[0]), Compare);   

	printf("#Sorted array:\n");
	for(i = 0; i < DataSize; i++)
		printf("%lg ", Data[i]);
	printf("\n");

	free(Data);

	system("pause");
	return 0;
}

/** ********************************************************************************
 Compare  -  compare 2 numbers
 
 @param      *arg1   first argument
 @param      *arg2   second argument
 
 @return         0,  if arg1=arg2
                 -1, if arg1<arg2
                 1,  if arg1>arg2
************************************************************************************/

int Compare(const void* arg1, const void* arg2)  
{
	double* a = (double*) arg1;
	double* b = (double*) arg2;
	if (*a < *b)
		return -1;
	else
		if (*a > *b)
			return 1;
		else
			return 0;
}

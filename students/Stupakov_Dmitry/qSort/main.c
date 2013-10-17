//{=================================================================================
//! @file    main.c
//! @date    15.10.2013
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

int Compare(const double* arg1, const double* arg2);

int main()
{
	int i = 0, DataSize, proof = 0;
	double *Data;

	printf("#Author Dmitry Stupakov\n"                              
		   "#Version 1.4\n"
		   "#15.10.2013\n"
		   "#Enter the number of array elements:\n");
	proof = scanf("%i", &DataSize);
	assert(proof == 1);

	Data = (double*) calloc(DataSize, sizeof (double));
	
	printf("#Enter elements:\n");                      
    for (i = 0; i < DataSize; i++)
	{
	    proof = scanf("%lg", &Data[i]);
		assert(proof == 1);	
	}

    qsort(Data, DataSize, sizeof (double), Compare);   

    printf("#Sorted array:\n");
	for(i = 0; i < DataSize; i++)
		printf("%lg ", Data[i]);
	printf("\n");

	free(Data);

	system("pause");
	return 0;
}

/** ********************************************************************************
 Compare - compare 2 numbers
 
 @param      *arg1   first argument
 @param      *arg2   second argument
 
 @return         0,  if arg1=arg2
                 -1, if arg1<arg2
                 1,  if arg1>arg2
************************************************************************************/
int Compare(const double* arg1, const double* arg2)                                 // int Compare(const void* arg1, const void* arg2)
{																					// { 
	if (*arg1 < *arg2)																//	   if (*(double*) arg1 < *(double*) arg2)  
		return -1;																	//			return -1;
	else																			// else
		if (*arg1 > *arg2)															//	   if (*(double*) arg2 > *(double) arg2)
			return 1;																//		    return 1;
		else																		//     else
			return 0;																//          return 0;
}																					// }
																					// Выдает варнинги : фомальный праметр 1 (2) отличается от объявления
                                                                                    // Не могу понять почему так, поскольку на семинаре работало
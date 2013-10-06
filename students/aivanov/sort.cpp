//{=================================================================================
//! @file    sort.cpp
//! @date    2013-10-06 15:33
//! @author  Andrey Ivanov <ivanov.greyant@gmail.com>
//! @version 1.0
//!
//! Merge sort algorithm.
//! Program generates random numbers and sorts them with merge algorithm.
//! 
//}=================================================================================

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ASSERT(cond,message) \
	if (!(cond)) \
	{ \
		printf("%s\n%s is not true, file %s, line %d\n", message,#cond, __FILE__, __LINE__); \
		abort(); \
	}

//{=================================================================================
//! merge_sort - sorts the array, starting from some element(left) and ending with some other element(right)
//!
//! @param[out] data  Array whose elements are to be sorted
//! @param      left  Starting sort from this element
//! @param      right Last element to sort
//!
//! @return           Nothing
//}=================================================================================
void merge_sort(double *data, int left, int right);

//{=================================================================================
//! swap_d - swaps the two double variables
//!
//! @param[out] a First element to swap with second element
//! @param[out] b Second element to swap with first element
//!
//! @return       Nothing
//}=================================================================================
void swap_d(double *a, double *b);

const int DATA_SIZE = 10000;

int main()
{	
	double data[DATA_SIZE] = {};

	printf("Randomly generated array of numbers\n");
	srand( time( NULL ) );
	for ( int i = 0; i < DATA_SIZE; i++)
	{
		ASSERT((0 <= i) && (i < DATA_SIZE),"Out of array data size");
		data[i] = ((double) (rand()-(RAND_MAX/2)))/ ((double) rand()); 
		printf("%lg ", data[i]);
	}
	printf("\n\n");

	merge_sort(&data[0], 0, DATA_SIZE-1);

	printf("Sorted array of numbers\n");
	for ( int i = 0; i < DATA_SIZE; i++)
	{
		printf("%lg ", data[i]);
	}
	printf("\n");

	system("PAUSE");
	return 0;
}

void merge_sort(double *data, int left, int right)
{
	if (right - left == 1) 
	{
		if (data[left] > data[right]) 
		{
			swap_d(&data[left], &data[right]);
		}
	}
	else
	{
		int mid = (left + right) / 2;

		if (left != mid) merge_sort(data, left, mid);
		if (mid+1 != right) merge_sort(data, mid+1, right);

		double* temp_data = (double*) calloc(right - left + 1, sizeof(double));
		for (int c = 0; c < right-left+1; c++)
		{
			ASSERT((0 <= left+c) && (left+c < DATA_SIZE),"Out of array data size");
			ASSERT((0 <= c) && (c < right - left + 1),"Out of array temp_data size");
			temp_data[c] = data[left+c];
		}
		
		int i = 0, j = 0;
		i = left;
		j = mid + 1;
		int counter = 0;
		while ((i <= mid) && (j <= right))
		{
			if (temp_data[i - left] < temp_data[j - left]) 
			{
				ASSERT((0 <= left+counter) && (left+counter < DATA_SIZE),"Out of array data size");
				ASSERT((0 <= i - left) && (i - left < right - left + 1),"Out of array temp_data size");
				data[left+counter] = temp_data[i - left];
				i++;
			}
			else
			{
				ASSERT((0 <= left+counter) && (left+counter < DATA_SIZE),"Out of array data size");
				ASSERT((0 <= j - left) && (j - left < right - left + 1),"Out of array temp_data size");
				data[left+counter] = temp_data[j - left];
				j++;
			}
			counter++;
		}

		while (i <= mid) 
		{	
			ASSERT((0 <= left+counter) && (left+counter < DATA_SIZE),"Out of array data size");
			ASSERT((0 <= i - left) && (i - left < right - left + 1),"Out of array temp_data size");
			data[left + counter] = temp_data[i - left];
			i++;	
			counter++;
		}
		while (j <= right) 
		{			
			ASSERT((0 <= left+counter) && (left+counter < DATA_SIZE),"Out of array data size");
			ASSERT((0 <= j - left) && (j - left < right - left + 1),"Out of array temp_data size");
			data[left + counter] = temp_data[j - left];
			j++;
			counter++;
		}


		free(temp_data);
		temp_data = NULL;
	}
}

void swap_d(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
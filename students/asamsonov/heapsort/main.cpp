//{-------------head----------------------------------
//
//! @file    main.cpp
//! @mainpage
//! @brief   I've just written heapsort.
//!
//!          $Version: 1.00, Revision: 1 $
//!          $Date: 2013-10-07 23:05 $
//!
//!          There is my test of heapsort function.
//!			 It can be modified to work with any 
//!			 other type (not only int like here).
//!
//! @todo	 write:
//!			 - Timsort in a very long time.
//!
//}-------------head---------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------defines---------------------------------

#ifdef _EJC
    #define OUT printf
    #define EJC_OUT if (0) printf
#else
    #define OUT if (0) printf
    #define EJC_OUT printf
#endif //!< Macro for EJudge Client to output correctly.

//-------------debugging------------------------------

#define DEBUG

//-------------debugging------------------------------

#ifdef DEBUG
    #define ASSERT( cond )                          \
    if (!(cond)) {                                  \
        fprintf (stderr, "# Assertion fail : %s. "  \
                        "File %s, line %d\n",       \
                        #cond, __FILE__, __LINE__); \
        abort();                                    \
    }
#else
    #define ASSERT( cond )
#endif //!< My own assert. It's Godlike! :P

#define SMTH_VERY_BIG 1000000000

//-------------defines---------------------------------

//{-------------heapsort-------------------------------
//! @brief   This is swap function, just to swap values of 2 variables.
//!
//! @param[out]		a	first variable
//! @param[out]		b	second variable
//!
//! @see     sift_down(), make_heap(), heap_sort()
//}-------------heapsort--------------------------------

void swap (int *a, int *b);

//{-------------heapsort-------------------------------
//! @brief   This is function checking if root of heap is correct.
//!			 If it's not, function is expected to correct it.
//!
//! @param			i	root index in array
//! @param[out]		a	array with heap in it.
//! @param			n	"length" of array
//!
//! @see     make_heap(), heap_sort()
//}-------------heapsort--------------------------------

void sift_down(int i, int *a, int n);

//{-------------heapsort-------------------------------
//! @brief   This function builds heap from array it got.
//!
//! @param[out]		a	array with heap in it.
//! @param			n	"length" of array
//!
//! @see     sift_down(), heap_sort()
//}-------------heapsort--------------------------------

void make_heap(int *a, int n);

//{-------------heapsort-------------------------------
//! @brief   This function sorts "heapified" array.
//!
//! @param[out]		a	array with heap in it.
//! @param			n	"length" of array
//!
//! @see     sift_down(), make_heap()
//}-------------heapsort--------------------------------

void heap_sort(int *a, int n);

int main(int argc, const char **argv)
{
	int *arr = NULL;
	int nValues = 0;
	int i = 0;
	int scanned = 0;

	OUT ("# Hello @! This is %s. \n# It's compiled %s at %s by Anton Samsonov\n",\
						 strrchr (argv[0], '\\' ) + 1, __DATE__, __TIME__);
	OUT ("# Input a number of elements of array you want me to sort.\n");
	scanned = scanf ("%d", &nValues);
	if (scanned == 0) { OUT ("Do smth with your input. It's not valid.\n"); return 1; }
	if (nValues <= 0) { OUT ("# Hmm, do you think input mustn't be a natural number? I do.\n"); return 1; }
	if (nValues >= SMTH_VERY_BIG) {OUT ("# Do you REALLY think I've got enough memory to do this?\n"); return 1; }

	arr = (int *)calloc (nValues, sizeof (*arr));

	OUT ("# Great! Now enter %d values of this array.\n", nValues);
	for (i = 0; i < nValues; i++) { 
		ASSERT (0 <= i && i < nValues);
		scanf ("%d", &arr[i]);
	}
	OUT ("# ...\n");
	heap_sort (arr, nValues);

	OUT ("# Here it is! As you can see, it's sorted now!\n");
	for (i = nValues - 1; i >= 0; i--) {
		ASSERT (0 <= i && i < nValues);
		printf("%d ", arr[i]);
	}
	putchar ('\n');

	free(arr);
	return 0;
}

void swap (int *a, int *b)
{
	ASSERT (a && b);
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sift_down(int i, int *a, int n)
{
	int j = i;
	ASSERT (a);
	ASSERT (0 <= i && i < n);
	while (true) {
		if (2 * i + 1 < n && a[2 * i + 1] > a[j]) {// Should I place assert here instead of condition of if?
			ASSERT (0 <= 2 * i + 1 && 2 * i + 1 < n)
			j = 2 * i + 1;
		}
		if (2 * i + 2 < n && a[2 * i + 2] > a[j]) {// Just I think it's ok as it is.
			ASSERT (0 <= 2 * i + 1 && 2 * i + 1 < n)
			j = 2 * i + 2;
		}
		if (j == i) break;
		swap (&a[i], &a[j]);
		i = j;
	}
}

void make_heap(int *a, int n)
{
	int i = 0;
	ASSERT (a);
	for (i = n - 1; i >= 0; i--) 
		sift_down (i, a, n);
	//OUT ("# Iterations done: %d.\n", n - i);
}

void heap_sort(int *a, int n)
{
	int i = 0;
	ASSERT (a);
	//OUT ("# Building heap...\n");
	make_heap(a, n);
	//OUT ("# Heap is built.\n");
	for (i = n - 1; i > 0; i--) {
		ASSERT (0 <= i && i < n);
		swap (&a[0], &a[i]);
		sift_down (0, a, i);
	}
}
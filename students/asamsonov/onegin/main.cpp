//{-------------head----------------------------------
//
//! @file    main.cpp
//! @mainpage
//! @brief   I've just written heapsort which is 
//!			 sorting strings in block of text.
//!
//!          $Version: 1.02, Revision: 5 $
//!          $Date: 2013-10-17 17:01 $
//!
//!          - Heapsort was modified to work with strings correctly.
//!			 - It reads text from a file.
//!			 - It might be modified to write sorted text in a file.
//!
//! @warning - symbols like '(' or '\"' will be less than letters.
//!
//! @todo	 write:
//!			 - Do smth, bro!
//!
//}-------------head---------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>

//-------------defines---------------------------------

#define SWAP( a, b, type )  { type t = a; a = b; b = t; }

#ifdef _EJC //!< Macro for EJudge Client to output correctly.
	#ifdef OUT
		#undef OUT
	#endif
    #define OUT printf
    #define EJC_OUT if (0) printf
#else
	#ifdef OUT
		#undef OUT
	#endif
    #define OUT if (0) printf
    #define EJC_OUT printf
#endif

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

//-------------defines---------------------------------

//{-------------heapsort-------------------------------
//! @brief   This is function checking if root of heap is correct.
//!			 If it's not, function is expected to correct it.
//!			 It sifts the heap, while correcting.
//!			 P.S. "sift" <=> "npoceuBaTb".
//!
//! @param			index	root index in array
//! @param[out]		h_arr	array with heap in it.
//! @param			n		length of array
//!
//! @see     make_heap(), heap_sort()
//}-------------heapsort--------------------------------

void sift_down(int index, char **h_arr, int n);

//{-------------heapsort-------------------------------
//! @brief   This function builds heap from array.
//!
//! @param[out]		h_arr	array with heap in it.
//! @param			n		length of array
//!
//! @see     sift_down(), heap_sort()
//}-------------heapsort--------------------------------

void make_heap(char **h_arr, int n);

//{-------------heapsort-------------------------------
//! @brief   This function sorts a heap in array.
//!
//! @param[out]		h_arr	array with heap in it.
//! @param			n		length of array
//!
//! @see     sift_down(), make_heap()
//}-------------heapsort--------------------------------

void heap_sort(char **h_arr, int n);

//{-------------text-----------------------------------
//! @brief   This function reads text from a file.
//!
//! @param			file			file to read from.
//! @param[out]		my_precious		pointer to the block of memory. 
//!									You have to free it after all.
//! @param[out]		strings			Array of strings read.			
//!
//! @see     print_text()
//}-------------text------------------------------------

int read_my_text(FILE* file, void **my_precious, char ***strings);

//{-------------text-----------------------------------
//! @brief   This function prints array of strings in stdin.
//!
//! @param		text_pointer	array with strings in it.
//! @param		nStrings		length of array
//!
//! @see     read_my_text()
//}-------------text------------------------------------

void print_text(char **text_pointer, int nStrings);

int main(int argc, const char *argv[])
{
	FILE  *f1 = fopen ("input.txt", "r");
	void  *which_to_free = NULL;
	char **text_pointer  = NULL;
	int nStrings = read_my_text (f1, &which_to_free, &text_pointer);
	//OUT("# %08X %08X \n", text_pointer, which_to_free);
	//OUT("# %d.\n", nStrings);

	OUT ("# Hello @! This is %s. \n# It's compiled %s at %s by Anton Samsonov\n",\
						 strrchr (argv[0], '\\' ) + 1, __DATE__, __TIME__);
	OUT ("# If you don't know, what does this program do, keep calm, open \"input.txt\" file and write smth there.\n"
		 "# Program will sort your text in rising order. Thank you for your \"Thank you!\".\n");
	if (f1 == NULL) {OUT("# input.txt is either locked for reading or not existing.\n");}


	// Russian letters - now OK. See windows.h.
	_wsetlocale (LC_ALL, L"Russian_Russia.ACP");
	SetConsoleCP (1251);
    SetConsoleOutputCP (1251);

	fclose (f1);

	heap_sort  (text_pointer, nStrings);
	print_text (text_pointer, nStrings);

	//Don'y forget to free memory.
	free (which_to_free);
	which_to_free = NULL;
	text_pointer  = NULL;
	return 0;
}

void sift_down(int index, char *h_arr[], int n)
{
	int ind_new = index;
	ASSERT (h_arr);
	ASSERT (0 <= index && index < n);
	while (true) {
		if (2 * index + 1 < n && strcmp (h_arr[2 * index + 1], h_arr[ind_new]) == 1) {
			ASSERT (0 <= 2 * index + 1 && 2 * index + 1 < n)
			ind_new = 2 * index + 1;
		}
		if (2 * index + 2 < n && strcmp (h_arr[2 * index + 2], h_arr[ind_new]) == 1) {
			ASSERT (0 <= 2 * index + 2 && 2 * index + 2 < n)
			ind_new = 2 * index + 2;
		}
		if (ind_new == index) break;
		SWAP (h_arr[index], h_arr[ind_new], char *);
		index = ind_new;
	}
}

void make_heap(char *h_arr[], int n)
{
	int i = 0;
	ASSERT (h_arr);

	for (i = n - 1; i >= 0; i--)
		sift_down (i, h_arr, n);
	//OUT ("# Iterations done: %d.\n", n - i);
}

void heap_sort(char *h_arr[], int n)
{
	int i = 0;
	ASSERT (h_arr);

	//OUT ("# Building heap...\n");
	make_heap(h_arr, n);
	//OUT ("# Heap is built.\n");

	for (i = n - 1; i > 0; i--) {
		ASSERT (0 <= i && i < n);
		SWAP (h_arr[0], h_arr[i], char *);
		sift_down (0, h_arr, i);
	}
}

int read_my_text(FILE* file, void **my_precious, char ***strings)
{
	int curr_c = 0, prev_c = 0;
	int nChars = 0, nStrings = 0, j = 0;
	while ((curr_c = getc (file)) != EOF) {
		if (curr_c == '\n')
			nStrings++;
		//-------------
			nChars++;
		prev_c = curr_c;
	}
	if (prev_c != '\n') {
		nStrings++; 
		nChars++;
	}

	*my_precious = malloc (nStrings * sizeof (void *) + nChars * sizeof (char));
	*strings = (char **)*my_precious;
	char  *chars   = (char *)((int)*my_precious + nStrings * sizeof (void *));

	//OUT("# %08X %08X \n", *strings, *my_precious);

	fseek(file, 0, SEEK_SET);

	int i = 0, top = 0;
	for (i = 0; i < nStrings; i++) {
		(*strings)[i] = chars + top;
		while ((int)(curr_c = getc (file)) != EOF && curr_c != '\n') {
			chars[top++] = curr_c;
		}
		chars[top++] = '\0';
	}

	return nStrings;
}

void print_text(char **text_pointer, int nStrings)
{
	int i = 0;
	OUT ("# Just get it and like it.\n\n");
	for (i = 0; i < nStrings; i++) 
		printf("%s\n", text_pointer[i]);
}
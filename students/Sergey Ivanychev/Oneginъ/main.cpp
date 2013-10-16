/**
		@file				main.c
		@mainpage
		@author				Ivanychev Sergey, DCAM MIPT, 376 group
		@version			1.00

		@par				Program requires file input.txt, where the source text is located. It creates for it a special memory area.

							MEMORY AREA  == [Pointers to string begins, which are sorted in string ascending order][Strings of text]

							Program scans the input text, creates the pointers to each string, sorts it and prints in dictionary.txt file
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

/**
		swap				function replaces each pointer with another one
		@return				void
**/
void swap(char** first, char** second);

//void string_qsort(char** pointers, int size, int (*comp)(const char* first,const char* second));

/**
		string_heapsort			functions that sorts the array of pointers, comparing strings which are pointed by them. I know that it's possible to do without
								function pointer but I wanted to use it for the first time. Function uses heap algorythm.
		@param[out] pointers	the pointer to the beginning of string pointers array
		@param		size		the size of array
		@param[out]	comp		function that is used to compare pointers

		@return					void
**/
void string_heapsort(char** pointers, int size, int (*comp)(const char* first,const char* second));

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

/**
		text_s						Contains the information about text memory area. The object is generated after the text is already scanned and area is done
		@param[out]	str_pointers	Pointer to the beginning of string pointers
		@param		str_amount		The length of string pointers array
		@param[out]	source			The pointer to the beginning of text
**/
struct text_s
{
	char** str_pointers;
	int str_amount;
	int char_amount;
	char* source;
};

typedef text_s text;

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 


int get_text(FILE* stream, text * save_text)
{
	register int c = 0;
	if ((c = getc(stream)) == EOF) return -1;
	ungetc(c, stream);

	int char_counter = 0;
	int str_counter = 1;
	bool last_enter = 0;

	while ((c = getc(stream)) != EOF)
	{
		char_counter++;
		if (c == '\n') 
		{	
			str_counter++;
			last_enter = 1;
		}
		else last_enter = 0;
	}

	if (last_enter == 0) char_counter++;
	
	
	int ret = fseek(stream, 0, SEEK_SET);
	assert(!(ret));

	void* inp_text = malloc((char_counter) * sizeof(char) + str_counter * sizeof(char*));
	char* text_begin = (char*)((int)inp_text + str_counter * sizeof(char*));
	
	char** pointer_current = (char**)text_begin - 1;
	*(pointer_current--) = text_begin;
	char* char_current = text_begin;


	while ( (c = getc(stream)) != EOF)
	{
		*(char_current) = c;
		if (*(char_current) == '\n')
		{
			*(char_current) = '\0';
			*(pointer_current--) = char_current + 1;
		}
		char_current++;
	}
	*char_current = '\0';

	save_text -> str_pointers = (char**) inp_text;
	save_text -> str_amount = str_counter;
	save_text -> source = text_begin;
	save_text -> char_amount = char_counter;

	return 0;
}

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

int main()
{

	FILE* fi = fopen("input.txt", "r");
	FILE* fo = fopen("dictionary.txt", "w");
	assert(fi);
	assert(fo);

	text *onegin = (text*) malloc(sizeof(text)); 
	assert(onegin);
	int ret = get_text(fi, onegin);

	if (ret == -1)
	{
		printf("Text scanning failed\n");
		return 0;
	}
	/*
	for (int i = onegin -> str_amount - 1; i >= 0; --i) 
		{
			fprintf(fo, "%s\n", *(onegin -> str_pointers + i));
		}
	
	fprintf(fo, "*****************************************************************************************************\n");
	*/
	string_heapsort(onegin -> str_pointers, onegin -> str_amount, stricmp);
	for (int i = onegin -> str_amount - 1; i >= 0; --i) 
		{
			fprintf(fo, "%s\n", *(onegin -> str_pointers + i));
		}
	
	free(onegin -> str_pointers);
	onegin -> str_pointers = NULL;
	free(onegin);
	onegin = NULL;

	return 0;
}


//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

void swap(char** first, char** second)
{
	char* temp = *first;
	*first = *second;
	*second = temp;
}

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 


void string_heapsort(char** pointers, int size, int (*comp)(const char* first,const char* second))
{
	assert(pointers);
	assert(comp);
	while (size > 1)
	{
		int last_father = size / 2 - 1;
		int father = last_father;
		while (father >= 0)
		{
			if (father == last_father)
			{
				if ((size > father * 2 + 2) && ((*comp)(pointers[father * 2 + 2], pointers[father]) < 0)) swap (pointers + father * 2 + 2, pointers + father);
				if ((*comp)(pointers[father * 2 + 1], pointers[father]) < 0) swap(pointers + father * 2 + 1, pointers + father);
			}
			else
			{
				if ((*comp)(pointers[father * 2 + 2], pointers[father]) < 0) swap(pointers + father * 2 + 2, pointers + father);
				if ((*comp)(pointers[father * 2 + 1], pointers[father]) < 0) swap(pointers + father * 2 + 1, pointers + father);
			}
			father--;
		}
		swap( pointers, pointers + size - 1);
		size--;
	}
}

/*
void string_qsort(char** pointers, int size, int (*comp)(const char* first,const char* second))
{
	
	int l = 0, r = size - 1;
	int i = l, j = r;
	int random = rand()%(size);
	char** temp = pointers + random;
	//printf("\nSize = %d, temp = %d, st[temp] = [%s]\n", size, random, *(pointers + random));
	for (int i = 0; i < size; ++i) printf("%s ", *(pointers + i));
	//putchar('\n');
	while (i <= j)
	{
		while ((*comp)(*temp, pointers[i]) < 0) ++i;
		while ((*comp)(*temp, pointers[j]) > 0) --j;
		if (i <= j) 
		{
			swap(pointers + i , pointers + j);
			++i;
			--j;
		}
	}
	printf("i = %d, j = %d\n", i, j);
	for (int i = 0; i < size; ++i) printf("%s ", *(pointers + i));
	putchar('\n');
	putchar('\n');
	if (l < j) string_qsort(pointers, j + 1, comp);
	if (i < r) string_qsort(pointers + i, r - i + 1, comp);
}
*/

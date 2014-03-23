#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NDEBUG

#ifndef NDEBUG
	#define ASSERT( cond, messege )           \
		if ( !( cond ) )                      \
		{                                     \
			printf ("Fatal error: %s, "       \
				"file: %s, line: %d \n",      \
			#messege, __FILE__, __LINE__);    \
			abort();                          \
		}
#else
	# define ASSERT( cond, messege )
#endif

Stack_t * Stack_Construct (long Size)
{
	if (Size <= 0)
		return 0;
	Stack_t * St = (Stack_t *) calloc (1, sizeof(Stack_t));
	St -> Last = -1;
	St -> Size = Size;
	St -> Arr = (Arr_type *) calloc (Size, sizeof(Arr_type));
	return St;
}

int Stack_Reconstruct (Stack_t * St)
{
	Stack_OK (St);
	Arr_type * Arr_cpy = (Arr_type *) calloc (St -> Size, sizeof(Arr_type));
	for (int i = 0; i <= St -> Last; i++)
		Arr_cpy[i] = St -> Arr[i];
	free(St -> Arr);
	St -> Size = St -> Size + 10;
	St -> Arr = (Arr_type *) calloc (St -> Size, sizeof(Arr_type));
	for (int i = 0; i <= St -> Last; i++)
		St -> Arr[i] = Arr_cpy[i];
	free(Arr_cpy);
	Stack_OK (St);
	return 1;
}

int Stack_Distruct (Stack_t * St)
{
	St -> Last = 0;
	St -> Size = 0;
	free(St -> Arr);
	free(St);
	return 1;
}

int Stack_Push (Stack_t * St, Arr_type val)
{
	Stack_OK (St);
	if (St -> Last + 1  >=  St -> Size)
		Stack_Reconstruct (St);
	(St -> Last) ++;
	St -> Arr [St -> Last] = val;
	Stack_OK (St);
	return 1;
}

Arr_type Stack_Pop (Stack_t * St)
{
	Stack_OK (St);
	if (St -> Last  ==  -1)
		return 0;
	Arr_type val = St -> Arr [St -> Last];
	St -> Arr [St-> Last] = 0;
	(St -> Last) --;
	Stack_OK (St);
	return val;
}

Arr_type Stack_Top (Stack_t * St)
{
	Stack_OK (St);
	if (St -> Last  ==  -1)
		return 0;
	Arr_type val = St -> Arr [St -> Last];
	return val;
}

int Stack_OK (Stack_t * St)
{
	int state = 0;
	if (St == NULL)
		state = -1;
	if (St -> Last  >=  St -> Size)
		state = -1;
	if (St -> Last  <  -1)
		state = -1;
	if (St -> Size  <=  0)
		state = -1;
	if (state == -1)
	{
		Stack_Dump(St);
		return -1;
	}
	return 1;
}

void Stack_Dump (Stack_t * St)
{
	printf("[***__________***__________***__________***]\n"
		   "ERROR: Stack ¹%d\n"
		   "Inappropriate for working."
		   "Size: %d  Number of elements: %d\n"
		   "Type of elements: double\n", St -> Num, St -> Size, St -> Last + 1);
	
	if (St -> Last >= St -> Size)
		St -> Last = St -> Size - 1;
	if (St -> Last >= 0)
	{
		printf("The elements of the stack:\n");
		for(int i = 0; i <= St -> Last; i++)
			printf("[%d]: %lg\n", i, (double) St -> Arr[i]);
	}
	else
		printf("\nThere are no elements in the stack.\n\n");
	Stack_Distruct (St);
}

int Func_Strlen (const char * str)
{
	ASSERT(str != NULL, "str[0] is a NULL address");
	
	char sym = str[0];
	int length = 0;
	while (sym != '\0')
	{
		length++;
		sym = str[length];
	}
	return length;
}

int Func_Strcmp (const char * str1, const char * str2)
{
	ASSERT(str1 != NULL, "str1[0] is a NULL address.");
	ASSERT(str2 != NULL, "str2[0] is a NULL address.");
	
	int length1 = Func_Strlen(str1);
	int length2 = Func_Strlen(str2);
	
	if (length1 > length2) return 1;
	if (length1 < length2) return -1;
	if (length1 == length2)
	{
		for (int i = 0; i < length1; i++)
		{
			if (str1[i] > str2[i]) return 1;
			if (str1[i] < str2[i]) return -1;
		}
		return 0;
	}
}

int Stack_Sum (Stack_t * St)
{
	Stack_OK (St);

	if (St -> Last < 1)
		return -1;

	Arr_type el1 = Stack_Pop (St);
	Arr_type el2 = Stack_Pop (St);
	Stack_Push (St, el1 + el2);
	
	return 1;
}

int Stack_Sub (Stack_t * St)
{
	Stack_OK (St);

	if (St -> Last < 1)
		return -1;
	
	Arr_type el1 = Stack_Pop (St);
	Arr_type el2 = Stack_Pop (St);
	Stack_Push (St, el2 - el1);
	
	return 1;
}

int Stack_Mul (Stack_t * St)
{
	Stack_OK (St);

	if (St -> Last < 1)
		return -1;
	
	Arr_type el1 = Stack_Pop (St);
	Arr_type el2 = Stack_Pop (St);
	Stack_Push (St, el2 * el1);
	
	return 1;
}

int Stack_Div (Stack_t * St)
{
	Stack_OK (St);

	if (St -> Last < 1)
		return -1;
	
	Arr_type el1 = Stack_Pop (St);
	Arr_type el2 = Stack_Pop (St);
	Stack_Push (St, (Arr_type) ( (double) el2 / (double) el1 ) );
	
	return 1;
}

int Stack_Exp (Stack_t * St)
{
	Stack_OK (St);
	
	if (St -> Last < 0)
		return -1;

	Arr_type el = Stack_Pop (St);
	Stack_Push (St, exp(el));
	
	return 1;
}

int Stack_Pow (Stack_t * St)
{
	Stack_OK (St);

	if (St -> Last < 1)
		return -1;

	Arr_type el1 = Stack_Pop (St);
	Arr_type el2 = Stack_Pop (St);
	Stack_Push (St, pow(el2, el1));

	return 1;
}
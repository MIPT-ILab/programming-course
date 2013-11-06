//{-------------head----------------------------------
//
//! @file    stack.cpp
//! @brief   Now it's Stack for CPU.
//!
//}-------------head---------------------------------

#include "CPUheader.h"

#ifndef CPUHEADER 
	fprintf (stderr, "CPUwork.h is not existing.\n");
	abort ();
#endif

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------declarations----------------------------
/* 

Stack *Stack_create (int size);

void Stack_delete (Stack *myStack);

int Stack_OK (const Stack *myStack);

void Stack_dump (const Stack *myStack);

int Stack_push (Stack *myStack, double value);

double Stack_pop (Stack *myStack);

int Stack_getsize (Stack *myStack);

*/
//}-------------declarations----------------------------

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------stackstack------------------------------
//! @brief   This function creates Stack 
//!			 with Stack->maxsize = max_size.
//!
//! @param		max_size	size of created Stack
//!
//! @return		pointer of the new Stack.	
//!
//! @see     Stack_OK(), Stack_delete()
//}-------------stackstack-----------------------------

Stack* Stack_new (int max_size)
{
	if (max_size <= 0) 
		return NULL;
	Stack *temp = (Stack *)malloc (sizeof (*temp));
	temp->data = (double *)calloc (max_size, sizeof (*temp->data));
	temp->size = 0;
	temp->maxsize = max_size;
	
	ASSERT_OK (temp);
	return temp;
}

//{-------------stackstack------------------------------
//! @brief   This function deletes Stack given.
//!
//! @param		myStack		Stack
//!
//! @see     Stack_OK, Stack_create()
//}-------------stackstack-----------------------------

void Stack_delete (Stack *myStack)
{
	free (myStack->data);
	myStack->data = NULL;
	myStack->size = -1;
	free (myStack);
	myStack = NULL;
}

//{-------------stackstack------------------------------
//! @brief   This function checks if Stack is ok.
//!
//! @param		myStack		Stack	
//!
//! @return		!0 if Stack is ok. 0 if Stack is not.
//!
//! @see     Stack_dump(), Stack_push(), Stack_pop()
//}-------------stackstack-----------------------------

int Stack_OK (const Stack *myStack)
{
	return (myStack && 0 <= myStack->size && myStack->size <= myStack->maxsize);
}

//{-------------stackstack------------------------------
//! @brief   This function prints info about Stack.
//!
//! @param		myStack		Stack
//!
//! @par		It prints:
//!				- That it's Stack;
//!				- Adress of this Stack;
//!				- If Stack is ok or not;
//!				- Size of the Stack;
//!				- Maxsize of the Stack;
//!				- Every value from data of Stack;
//!				- '*' sign for usable values of data;
//!
//! @see     Stack_OK()
//}-------------stackstack-----------------------------

void Stack_dump (const Stack *myStack)
{
	int ok = Stack_OK (myStack);
	printf ("Hello @, I'm Stack. %.8X. // %s\n", myStack, ok? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!");
	printf ("\t" "size = %d\n", myStack->size);
	printf ("\t" "maxsize = %d\n", myStack->maxsize);
	int i = 0;
	for (i = 0; i < myStack->size; i++)
		printf ("\t" "data[%d] = %.3lg *\n", i, myStack->data[i]);
	for (i = myStack->size; i < myStack->maxsize; i++)
		printf ("\t" "data[%d] = %.3lg\n", i, myStack->data[i]);
	printf ("Stack: That's all.\n\n");
}

//{-------------stackstack------------------------------
//! @brief   This function adds new element in the end of Stack.
//!
//! @param		myStack		Stack
//! @param		value		new element	
//!
//! @return		1 if you can add element, 0 if Stack is full.
//!
//! @see     Stack_OK(), Stack_pop()
//}-------------stackstack-----------------------------

int Stack_push (Stack *myStack, double value)
{
	ASSERT_OK (myStack);
	if (myStack->size >= myStack->maxsize)
		return 0;
	myStack->data[myStack->size++] = value;

	ASSERT_OK (myStack);
	return 1;
}

//{-------------stackstack------------------------------
//! @brief   This function takes last element from Stack deleting it.
//!
//! @param		myStack		Stack
//!
//! @return		Last element of this Stack.	
//!
//! @see     Stack_OK(), Stack_push()
//}-------------stackstack-----------------------------

double Stack_pop (Stack *myStack)
{
	ASSERT_OK (myStack);
	ASSERT (myStack->size != 0);
	return myStack->data[--myStack->size];
}

//{-------------stackstack------------------------------
//! @brief   This function returns size of Stack given.
//!
//! @param		myStack		Stack
//!
//! @return		number of elements in this Stack.	
//}-------------stackstack-----------------------------

int Stack_getsize (Stack *myStack)
{
	ASSERT_OK  (myStack);
	return myStack->size;
}
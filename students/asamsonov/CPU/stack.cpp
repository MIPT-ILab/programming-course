//{-------------head----------------------------------
//
//! @file    stack.cpp
//! @mainpage
//! @brief   Now it's Stack for CPU.
//!
//!          $Version: 1.52, Revision: 4 $
//!          $Date: 2013-10-19 18:40 $
//!
//!          - CPU header added so we check it's define now.
//!			 - improved Stack_dump for using in processor.cpp
//!
//! @todo	 or not todo
//!
//}-------------head---------------------------------

#include "CPUwork.h"

//{-------------defines---------------------------------

#if ( !defined ( CPUHEADER ) )
//{-------------if-(-!header-)--------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//{-------------debugging------------------------------

#define DEBUG

//}-------------debugging------------------------------

#ifdef DEBUG
    #define ASSERT( cond )                                 \
    if (!(cond)) {                                         \
        fprintf (stderr, "# Assertion fail : %s. "         \
                 "File %s, line %d\n",                     \
                 #cond, __FILE__, __LINE__, __FUNCTION__); \
        abort();                                           \
    }
	#define ASSERT_OK( stack )                             \
	if ( !Stack_OK ( stack ) ) {                           \
		Stack_dump ( stack );                              \
		ASSERT ( !"stack is ok" );                         \
	}	
#else
    #define ASSERT( cond )
	#define ASSERT_OK( stack )
#endif

//{-------------strucutures-----------------------------

typedef struct Stack Stack;

struct Stack {
	int *data;							/* type = int */
	int size;
	int maxsize;
	int x;
};

//}-------------strucutures----------------------------

//{-------------if-(-!header-)--------------------------
#endif

//}-------------defines---------------------------------

//{-------------declarations----------------------------
/* 

Stack *Stack_create( int size );

void Stack_delete( Stack *myStack );

int Stack_OK( const Stack *myStack );

void Stack_dump( const Stack *myStack );

int Stack_push( Stack *myStack, int value );

int Stack_pop( Stack *myStack );

int Stack_getsize( Stack *myStack );

*/
//}-------------declarations----------------------------

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

Stack* Stack_create( int max_size )
{
	if ( max_size <= 0 ) 
		return NULL;
	Stack *temp = (Stack *)malloc ( sizeof (*temp) );
	temp->data = (int *)calloc ( max_size, sizeof (*temp->data) );
	temp->size = 0;
	temp->maxsize = max_size;
	return temp;
}

//{-------------stackstack------------------------------
//! @brief   This function deletes Stack given.
//!
//! @param		myStack		Stack
//!
//! @see     Stack_OK, Stack_create()
//}-------------stackstack-----------------------------

void Stack_delete( Stack *myStack )
{
	free ( myStack->data );
	myStack->data = NULL;
	myStack->size = -1;
	free ( myStack );
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

int Stack_OK( const Stack *myStack )
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
//!				- Number of appeals to the Stack
//!				- Every value from data of Stack;
//!
//! @see     Stack_OK()
//}-------------stackstack-----------------------------

void Stack_dump( const Stack *myStack )
{
	int ok = Stack_OK ( myStack );
	printf ( "Hello @, I'm Stack. %.8X. // %s\n", myStack, ok? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!" );
	printf ( "\t" "size = %d\n", myStack->size );
	printf ( "\t" "maxsize = %d\n", myStack->maxsize );
	printf ( "\t" "x = %d\n", myStack->x );
	int i = 0;
	for (i = 0; i < myStack->size; i++)
		printf ( "\t" "data[%d] = %d\n", i, myStack->data[i] );
	printf ( "Stack: That's all.\n\n" );
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

int Stack_push( Stack *myStack, int value )
{
	ASSERT_OK ( myStack );
	if (myStack->size == myStack->maxsize)
		return 0;
	myStack->data[myStack->size++] = value;

	ASSERT_OK ( myStack );
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

int Stack_pop( Stack *myStack )
{
	ASSERT_OK ( myStack );
	ASSERT ( myStack->size != 0 );
	return myStack->data[--myStack->size];
}

//{-------------stackstack------------------------------
//! @brief   This function returns size of Stack given.
//!
//! @param		myStack		Stack
//!
//! @return		number of elements in this Stack.	
//}-------------stackstack-----------------------------

int Stack_getsize( Stack *myStack )
{
	return myStack->size;
}
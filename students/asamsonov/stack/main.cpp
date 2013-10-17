//{-------------head----------------------------------
//
//! @file    main.cpp
//! @mainpage
//! @brief   I tested stack here.
//!
//!          $Version: 1.00, Revision: 1 $
//!          $Date: 2013-10-17 21:01 $
//!
//!          - ASSERT was modified with __FUNCTION__ here and later
//!			 - Some news in codestyle. Even more spaces now.
//!
//! @todo	 write:
//!			 - queue.
//!
//}-------------head---------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------defines---------------------------------

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
    #define ASSERT( cond )                                 \
    if (!(cond)) {                                         \
        fprintf (stderr, "# Assertion fail : %s. "         \
                 "File %s, line %d\n",                     \
                 #cond, __FILE__, __LINE__, __FUNCTION__); \
        abort();                                           \
    }
#else
    #define ASSERT( cond )
#endif //!< My own assert. It's Godlike! :P

//-------------defines---------------------------------

typedef struct stack stack;

struct stack {
	int *start;
	int *end;
	int maxsize;
};

//{-------------stackstack------------------------------
//! @brief   This function creates stack with stack->maxsize = size.
//!
//! @param		size	size of created stack
//!
//! @return		pointer of the new stack.	
//!
//! @see     stack_push(), stack_pop(), stack_delete()
//}-------------stackstack-----------------------------

stack *stack_create( int size );

//{-------------stackstack------------------------------
//! @brief   This function adds new element in the end of stack.
//!
//! @param		my_stack	stack
//! @param		value		new element	
//!
//! @return		1 if you cann add element, 0 if stack is full.
//!
//! @see     stack_pop()
//}-------------stackstack-----------------------------

int stack_push( stack *my_stack, int value );

//{-------------stackstack------------------------------
//! @brief   This function takes last element from stack deleting it.
//!
//! @param		my_stack	stack
//!
//! @return		Last element of this stack.	
//!
//! @see     stack_push()
//}-------------stackstack-----------------------------

int stack_pop( stack *my_stack );

//{-------------stackstack------------------------------
//! @brief   This function deletes stack given.
//!
//! @param		my_stack	stack
//!
//! @see     stack_create()
//}-------------stackstack-----------------------------

void stack_delete( stack *my_stack );

//{-------------stackstack------------------------------
//! @brief   This function returns size of stack given.
//!
//! @param		my_stack	stack
//!
//! @return		number of elements in this stack.	
//!
//! @see     stack_push(), stack_pop()
//}-------------stackstack-----------------------------

int stack_getsize( stack *my_stack );

int main( int argc, const char *argv[] )
{
	int nValues = 1;
	OUT ( "# Hello @! This is %s. \n# It's compiled %s at %s by Anton Samsonov\n",\
		  strrchr (argv[0], '\\' ) + 1, __DATE__, __TIME__ );
	OUT ( "# Input amount of values you will enter.\n" );
	int scanned = scanf ( "%d", &nValues );
	if ( !scanned || nValues < 1 ) { 
		OUT ( "# Input is not valid.\n" );
		return 1; 
	}
	stack *my_stack = stack_create ( nValues );

	OUT ( "# Enter %d numbers.\n", nValues );
	int tmp_value = 0;
	while ( nValues-- ) {
		if ( !( scanned = scanf ( "%d", &tmp_value ) ) )
		{ 
			OUT ( "# Input is not valid.\n" ); 
			return 1; 
		}
		if (stack_push ( my_stack, tmp_value ) == 0) OUT ( "# Stack's full.\n" );
	}
	nValues = stack_getsize ( my_stack );
	while ( nValues-- ) 
		printf ( "%d ", stack_pop ( my_stack ) );
	printf ( "\n" );

	stack_delete ( my_stack );
	return 0;
}

stack *stack_create( int max_size )
{
	ASSERT(max_size > 0);
	stack *temp = (stack *)malloc ( sizeof (*temp) );
	temp->start = (int *)calloc ( max_size, sizeof (int) );

	temp->end = temp->start;
	temp->maxsize = max_size;
	return temp;
}

int stack_push( stack *my_stack, int value )
{
	if ( (int)( my_stack->end - my_stack->start ) == my_stack->maxsize )
		return 0;
	ASSERT ( my_stack->end - my_stack->start < my_stack->maxsize  );
	*( my_stack->end) = value;
	my_stack->end ++;

	return 1;
}

int stack_pop( stack *my_stack )
{
	return *( -- my_stack->end );
}

void stack_delete( stack *my_stack )
{
	free ( my_stack->start );
	my_stack->start = NULL;
	my_stack->end = NULL;
	free ( my_stack );
	my_stack = NULL;
}

int stack_getsize( stack *my_stack )
{
	return ( (int)(my_stack->end - my_stack->start) );
}
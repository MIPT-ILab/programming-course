//{-------------defines---------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CPUHEADER 1

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

//}-------------defines---------------------------------




//{-------------strucutures-----------------------------

typedef struct Stack Stack;

struct Stack {
	int *data;
	int size;
	int maxsize;
	int x;
};

//}-------------strucutures-----------------------------

//{-------------declarations----------------------------

Stack *Stack_create( int size );

void Stack_delete( Stack *myStack );

int Stack_OK( const Stack *myStack );

void Stack_dump( const Stack *myStack );

int Stack_push( Stack *myStack, int value );

int Stack_pop( Stack *myStack );

int Stack_getsize( Stack *myStack );

//}-------------declarations----------------------------
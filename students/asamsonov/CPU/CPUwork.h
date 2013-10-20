//{-------------defines---------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CPUHEADER 1

//{-------------assembler-defines-------------------------

#define END   0x0
#define PUSH  0x1
#define POP   0x2
#define ADD   0x3
#define SUB   0x4
#define MUL   0x5
#define DIV   0x6
#define SQRT  0x7
#define POW   0x8
#define SIN   0x9
#define COS   0xA

//}-------------assembler-defines-------------------------

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
	#define ASSERT_CPU( CPU )                              \
	if ( !CPU_OK ( CPU ) ) {						       \
		CPU_dump ( CPU );                                  \
		ASSERT ( !"CPU is ok" );                           \
	}
#else
    #define ASSERT( cond )
	#define ASSERT_OK( stack )
	#define ASSERT_CPU( CPU )
#endif

#define  INPUT "input.txt"
#define		MC    "mc.txt"

//}-------------defines---------------------------------




//{-------------strucutures-----------------------------

typedef struct Stack Stack;

struct Stack {
	int *data;
	int size;
	int maxsize;
	int x;
};

//------------------------------------------------------

typedef struct CPU CPU;

struct CPU {
	Stack *myStack;
	int ax;
};

//}-------------strucutures-----------------------------

//{-------------declarations----------------------------

//==------------stack.cpp-------------------------------

Stack *Stack_create( int size );

void Stack_delete( Stack *myStack );

int Stack_OK( const Stack *myStack );

void Stack_dump( const Stack *myStack );

int Stack_push( Stack *myStack, int value );

int Stack_pop( Stack *myStack );

int Stack_getsize( Stack *myStack );

//==------------assembler.cpp---------------------------

int id_command ( char *str_4 );

int as_command( int command, int x, FILE* fi, FILE* fo );

int assemble( FILE *fi, FILE *fo ); // see INPUT and OUTPUT in assembler.cpp.

//==-------------processor.cpp--------------------------

CPU* CPU_create( int Stack_size );

void CPU_delete( CPU *myCPU );

int CPU_OK( CPU *myCPU );

int CPU_get_ax( CPU *myCPU );

int CPU_do_command ( CPU *myCPU, int command, FILE* fi);

int CPU_do_file( CPU *myCPU );

//}-------------declarations----------------------------
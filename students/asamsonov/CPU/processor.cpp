//{-------------head----------------------------------
//
//! @file    processor.cpp
//! @brief   Now it's CPU for CPU.
//!
//! @todo	 write:
//!			 - check of registers in CPU_do_command;
//!
//}-------------head---------------------------------

#include "CPUwork.h"

//{-------------defines---------------------------------

#if ( !defined ( CPUHEADER ) )
//{-------------if-(-!header-)--------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

//{-------------strucutures-----------------------------

typedef struct CPU CPU;

struct CPU {
	Stack *myStack;
	int ax;
};

//}-------------strucutures----------------------------

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

#define  MC  "mc.txt"

//{-------------if-(-!header-)--------------------------
#endif

//}-------------defines---------------------------------

//{-------------declarations----------------------------
/* 

CPU* CPU_create( void );

void CPU_delete( CPU *myCPU );

int CPU_OK( CPU *myCPU );

int CPU_get_ax( CPU *myCPU );

int CPU_do_command ( CPU *myCPU, int command, FILE* fi);

int CPU_do_file( void );

*/
//}-------------declarations----------------------------

//{-------------processor-------------------------------
//! @brief   This function creates CPU 
//!			 with CPU->myStack->maxsize = Stack_size.
//!
//! @param		Stack_size	size of Stack of created CPU
//!
//! @return		pointer of the new CPU.	
//!
//! @see     CPU_OK(), CPU_delete()
//}-------------processor-------------------------------

CPU* CPU_create( int Stack_size )
{
	CPU *temp = (CPU *)malloc ( sizeof ( *temp ) );
	temp->myStack = Stack_create ( Stack_size );
	temp->ax = 0;
	return temp;
}

//{-------------processor-------------------------------
//! @brief   This function deletes CPU given.
//!
//! @param		myCPU		CPU
//!
//! @see     CPU_OK, CPU_create()
//}-------------processor--------------------------------

void CPU_delete( CPU *myCPU )
{
	if ( !myCPU ) return;
	Stack_delete ( myCPU->myStack );
	myCPU->ax = -314;
	free ( myCPU );
	myCPU = NULL;
}

//{-------------processor-------------------------------
//! @brief   This function checks if CPU is ok.
//!
//! @param		myCPU		CPU	
//!
//! @return		!0 if CPU is ok. 0 if CPU is not.
//!
//! @see     CPU_dump(), CPU_get_ax(), CPU_do_command()
//}-------------processor-------------------------------

int CPU_OK( CPU *myCPU )
{
	return Stack_OK ( myCPU->myStack );
}

//{-------------processor-------------------------------
//! @brief   This function prints info about CPU.
//!
//! @param		myCPU		CPU
//!
//! @par		It prints:
//!				- That it's CPU;
//!				- Adress of this CPU;
//!				- If CPU is ok or not;
//!				- ax register of the CPU;
//!				- Info about Stack of this CPU;
//!
//! @see     CPU_OK()
//}-------------processor-------------------------------

void CPU_dump( CPU *myCPU )
{
	int ok = CPU_OK ( myCPU );
	printf ( "Hello @, I'm CPU. %.8X. // %s\n", myCPU, ok? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!" );
	printf ( "\t" "ax = %d\n", myCPU->ax );
	printf ( "\t" "I have got a Stack: \n" );
	Stack_dump ( myCPU->myStack );
	printf ( "CPU: That's all.\n\n" );
}

//{-------------processor------------------------------
//! @brief   This function returns ax register of CPU.
//!
//! @param		myCPU		CPU	
//!
//! @return		myCPU->ax
//!
//! @see     CPU_OK()
//}-------------processor-------------------------------

int CPU_get_ax( CPU *myCPU )
{
	ASSERT_CPU ( myCPU );
	return myCPU->ax;
}

//{-------------processor------------------------------
//! @brief   This function indentifies what this command 
//!			 is to do and read missing components 
//!			 from a file given if it's necessary.
//!			 After all, function performs this command 
//!			 using it's components.
//!
//! @param		myCPU		CPU	which does this command.
//! @param		command		command in 0x. form.
//! @param		fi			file to read from.
//!
//! @return		 0 if it's ok, 
//!				-1 if command was to STOP doing commands,
//!				 1 if smth got wrong.
//!
//! @see     CPU_OK()
//}-------------processor-------------------------------

int CPU_do_command ( CPU *myCPU, int command, FILE* fi)
{
	ASSERT_CPU ( myCPU );
	int extra = 0;
	char reg1[3] = {0};
	int str = 0;

	myCPU->myStack->x++;

	switch ( command ) {
	case END  : { return -1; }
	case PUSH : { if ( !fscanf ( fi, "%d", &extra ) ) { str = 1; if ( !fscanf ( fi, "%s", reg1 ) ) return 1; }
				  str? /* switch (reg1)*/ Stack_push ( myCPU->myStack, myCPU->ax ) : Stack_push ( myCPU->myStack, extra ); 
				  return  0; }
	case POP  : { if ( !fscanf ( fi, "%s", reg1 ) ) return 1; 
				  (reg1 == "n")? Stack_pop ( myCPU->myStack ): myCPU->ax = Stack_pop ( myCPU->myStack );
				  return  0; }
	case ADD  : { if ( myCPU->myStack->size < 2 ) return 1; 
				  Stack_push ( myCPU->myStack, Stack_pop ( myCPU->myStack ) + Stack_pop ( myCPU->myStack ) );
				  return  0; }
	case SUB  : { if ( myCPU->myStack->size < 2 ) return 1; 
				  Stack_push ( myCPU->myStack, -Stack_pop ( myCPU->myStack ) + Stack_pop ( myCPU->myStack ) );
				  return  0; }
	case MUL  : { if ( myCPU->myStack->size < 2 ) return 1; 
				  Stack_push ( myCPU->myStack, Stack_pop ( myCPU->myStack ) * Stack_pop ( myCPU->myStack ) );
				  return  0; }
	case DIV  : { if ( myCPU->myStack->size < 2 ) return 1; 
				  extra = Stack_pop ( myCPU->myStack );
				  Stack_push ( myCPU->myStack, Stack_pop ( myCPU->myStack ) / extra );
				  return  0; }
	case SQRT  : { if ( myCPU->myStack->size < 1 ) return 1; 
				  Stack_push ( myCPU->myStack, (int)sqrt ( (double)Stack_pop ( myCPU->myStack ) ) );
				  return  0; }
	case POW  : { if ( myCPU->myStack->size < 2 ) return 1; 
				  extra = Stack_pop ( myCPU->myStack );
				  Stack_push ( myCPU->myStack, (int)pow ( (double)Stack_pop ( myCPU->myStack ), (double)extra) );
				  return  0; }
	case SIN  : { if ( myCPU->myStack->size < 1 ) return 1; 
				  Stack_push ( myCPU->myStack, (int)sin ( (double)Stack_pop ( myCPU->myStack ) ) );
				  return  0; }
	case COS  : { if ( myCPU->myStack->size < 1 ) return 1; 
				  Stack_push ( myCPU->myStack, (int)cos ( (double)Stack_pop ( myCPU->myStack ) ) );
				  return  0; }
	default   : { return  1; }
	}
	ASSERT_CPU ( myCPU );
}

//{-------------processor------------------------------
//! @brief   This function executes assembled MC file.
//!
//! @param		myCPU		CPU	
//!
//! @return		0 if it's ok, or num of line (starting with 1)
//!				where is error if it's not ok.
//!
//! @see     CPU_do_command()
//}-------------processor-------------------------------

int CPU_do_file( CPU *myCPU )
{
	FILE *fi = fopen ( MC, "r" );
	int x = 1;
	int ok = 1;
	int scanned = 0;
	int res = 0;

	while ( ok = fscanf ( fi, "%d", &scanned ) ) {
		x++;
		ASSERT ( myCPU != NULL );
		res = CPU_do_command ( myCPU, scanned, fi );
		if ( res == 1) break;
		if ( res ) { x = 0; break; }
	}
	fclose ( fi );

	return x;
}
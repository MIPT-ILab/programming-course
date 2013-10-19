//{-------------head----------------------------------
//
//! @file    assembler.cpp
//! @mainpage
//! @brief   Now it's (!)Assembler(!) for CPU.
//!
//!          $Version: 1.00, Revision: 1 $
//!          $Date: 2013-10-19 14:53 $
//!
//! @todo	 write:
//!			 - R_defines in 0x.system;
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

//{-------------if-(-!header-)--------------------------
#endif

#define  INPUT "input.txt"
#define OUTPUT    "mc.txt"

//{-------------read-defines------------------------------

//#define R_ABCD   ('a' << 24) | ('b' << 16) | ('c' << 8) | ('d')

#define R_END   1701733376
#define R_PUSH  1886745448
#define R_POP   1886351360
#define R_ADD   1633969152
#define R_SUB   1937072640
#define R_MUL   1836411904
#define R_DIV   1684633088
#define R_SQRT  1936814708
#define R_POW   1886353152
#define R_SIN   1936289280
#define R_COS   1668248320

//}-------------read-defines------------------------------

//}-------------defines---------------------------------



//{-------------declarations----------------------------
/* 

int id_command ( char *str_4 );

int as_command( int command, int x, FILE* fi, FILE* fo );

int assemble()

*/
//}-------------declarations----------------------------

//{-------------Assembler-------------------------------
//! @brief   This function makes 0x. code from command
//!			 stored in string (4 chars).
//!
//! @param		str_4	command
//!
//! @return		0x. code of this command.	
//!
//! @see     as_command()
//}-------------Assembler------------------------------

int id_command ( char *str_4 )
{
	return (str_4[0] << 24) | 
		   (str_4[1] << 16) | 
		   (str_4[2] <<  8) | 
		   (str_4[3]      );
}

//{-------------Assembler-------------------------------
//! @brief   This function indentifies what this command 
//!			 is to do and read missing components 
//!			 from a file given if it's necessary.
//!			 After all, function writes command  
//!			 and it's components in another file given.
//!
//! @param		command		command.
//! @param		x			line of file we read on.
//! @param		fi			file to read from.
//! @param		fo			file to write to.
//!
//! @return		0 if it's ok, 1 if smth's wrong	
//!
//! @see     id_command(), assemble()
//}-------------Assembler------------------------------

int as_command( int command, int x, FILE* fi, FILE* fo )
{
	int as_c = END;
	int extra = 0;
	char reg[3] = {};
	int str = 0;

	switch ( command ) {
		case R_END  : { as_c =  END; fprintf ( fo, "%d\n", as_c ); break; }

		//{-------------command-with-argument------------------------------
		case R_PUSH : { as_c = PUSH; fprintf ( fo, "%d ", as_c ); str = 0;
					    if ( !fscanf ( fi, "%d", &extra ) ) { 
							str = 1;
							if ( !fscanf ( fi, "%s", reg ) )
								return 1;
						}
					    str? fprintf ( fo, "%s\n", reg ) : 
							 fprintf ( fo, "%d\n", extra ); 	   break; }
		//}-------------command-with-argument------------------------------

		//{-------------command-with-argument------------------------------
		case R_POP  : { as_c =  POP; fprintf ( fo, "%d ", as_c ); 
						if ( !fscanf ( fi, "%s", reg ) )
							return 1;
						fprintf ( fo, "%s\n", reg );			   break; }
		//}-------------command-with-argument------------------------------

		case R_ADD  : { as_c =  ADD; fprintf ( fo, "%d\n", as_c ); break; }
		case R_SUB  : { as_c =  SUB; fprintf ( fo, "%d\n", as_c ); break; }
		case R_MUL  : { as_c =  MUL; fprintf ( fo, "%d\n", as_c ); break; }
		case R_DIV  : { as_c =  DIV; fprintf ( fo, "%d\n", as_c ); break; }
		case R_SQRT : { as_c = SQRT; fprintf ( fo, "%d\n", as_c ); break; }
		case R_POW  : { as_c =  POW; fprintf ( fo, "%d\n", as_c ); break; }
		case R_SIN  : { as_c =  SIN; fprintf ( fo, "%d\n", as_c ); break; }
		case R_COS  : { as_c =  COS; fprintf ( fo, "%d\n", as_c ); break; }
		default     : { return x; } 
	}
	return 0;
}

//{-------------Assembler-------------------------------
//! @brief   reads from INPUT file all commands, 
//!			 interprete them and write in OUTPUT file
//!
//! @return		0 if it's ok, or num of line (starting with 1)
//!				where is error if it' not ok.
//!				
//! @see     id_command(), as_command()
//}-------------Assembler-----------------------------

int assemble( void )
{
	FILE *fi = fopen (  INPUT, "r");
	FILE *fo = fopen ( OUTPUT, "w");

	int ok = 1;
	char scanned[5] = {0};
	unsigned int command = 0;
	int x = 0;

	while ( ok = fscanf ( fi, "%s", scanned ) ) {
		x ++;
		ASSERT ( sizeof ( int ) >= 4 );
		command = id_command ( scanned );

		scanned[0] = '\0';
		scanned[1] = '\0';
		scanned[2] = '\0';
		scanned[3] = '\0';

		if ( as_command ( command, x, fi, fo ) ) return x;
	}
	fclose ( fi );
	fclose ( fo );
	return 0;
}
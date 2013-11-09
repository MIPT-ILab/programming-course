//{-------------head----------------------------------
//
//! @file    CPUheader.h
//! @brief   Now it's (!)Assembler(!) for CPU.
//!
//}-------------head---------------------------------

//{-------------defines---------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

#ifdef CPUHEADER
	#undef CPUHEADER
#endif
#define CPUHEADER 1

#ifdef CPUVERSION
	#undef CPUVERSION
#endif
#define CPUVERSION 401

//{-------------assembler-defines-------------------------

#define END   0x00
#define PUSH  0x01
	#define NUM  0x0
	#define REG  0x1
		#define AX  0x0
		#define BX  0x1
		#define CX  0x2
		#define DX  0x3
		#define BAD -12
#define POP   0x02
#define ADD   0x03
#define SUB   0x04
#define MUL   0x05
#define DIV   0x06
#define SQRT  0x07
#define POW   0x08
#define SIN   0x09
#define COS   0x0A
#define DUB   0x0B
#define OUT   0x0C
#define JMP   0x0D
#define JBE   0x0E
#define JAE   0x0F
#define JNE   0x10
#define JE    0x11
#define JB    0x12
#define JA    0x13
#define JF    0x14
#define MOV   0x15
#define IN	  0x16
#define DUMP  0x17
#define FUNC  0x18
#define CALL  0x19
#define RET   0x1A
#define HLT   0x1B
#define OR    0x1C
#define AND   0x1D
#define NOT   0x1F
#define XOR   0x1E

//{-------------read-defines------------------------------

//#define R_ABCD   ('a' << 24) | ('b' << 16) | ('c' << 8) | ('d')

#define R_END   0x656E6400
#define R_PUSH  0x70757368
#define R_POP   0x706F7000
#define R_ADD   0x61646400
#define R_SUB   0x73756200
#define R_MUL   0x6D756C00
#define R_DIV   0x64697600
#define R_SQRT  0x73717274
#define R_POW   0x706F7700
#define R_SIN   0x73696E00
#define R_COS   0x636F7300
#define R_DUB   0x64756200
#define R_OUT   0x6F757400
#define R_JMP   0x6A6D7000
#define R_JBE   0x6A626500
#define R_JAE   0x6A616500
#define R_JNE   0x6A6E6500
#define R_JE    0x6A650000
#define R_JB    0x6A620000
#define R_JA    0x6A610000
#define R_JF    0x6A660000
#define R_MOV   0x6D6F7600
#define R_IN	0x696E0000
#define R_DUMP	0x64756D70
#define R_FUNC	0x66756E63
#define R_CALL	0x63616C6C
#define R_RET	0x72657400
#define R_HLT	0x686C7400
#define R_OR    0x6F720000
#define R_AND   0x616E6400
#define R_NOT   0x6E6F7400
#define R_XOR   0x786F7200

//}-------------read-defines------------------------------

//}-------------assembler-defines-------------------------

//{-------------debugging------------------------------

#define DEBUG

//}-------------debugging------------------------------

#ifdef DEBUG
    #define ASSERT(cond)                                   \
    if (!(cond)) {                                         \
        fprintf (stderr, "# Assertion fail : %s. "         \
                 "File %s, line %d\n",                     \
                 #cond, __FILE__, __LINE__, __FUNCTION__); \
        abort();                                           \
    }
	#define ASSERT_OK(stack)                               \
	if (!Stack_OK (stack)) {                               \
		Stack_dump (stack);                                \
		ASSERT (!"stack is ok");                           \
	}
	#define ASSERT_CPU(CPU)                                \
	if (!CPU_OK (CPU)) {						           \
		CPU_dump (CPU);                                    \
		ASSERT (!"CPU is ok");                             \
	}
	#define CENSORED  printf
#else
    #define ASSERT(cond)
	#define ASSERT_OK(stack)
	#define ASSERT_CPU(CPU)
	#define CENSORED  if (0) printf
#endif

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

#define FRIDAY 1
#define PRECISE 1e-10
#define IS_EQUAL(x1, x2)  (fabs ((x1) - (x2)) < PRECISE) 

#define  INPUT  "input.txt"
#define		MC     "mc.txt"
#define OUTPUT "output.txt"
#define STDERR   "logs.txt"

//}-------------defines---------------------------------

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------strucutures-----------------------------

//==------------stack.cpp-------------------------------

typedef struct Stack Stack;

struct Stack {
	double *data;
	int size;
	int maxsize;
};

//==-------------CPU.cpp--------------------------------

typedef struct CPU CPU;

struct CPU {
	Stack *CPU_Stack;
	Stack *CPU_fcall;
	double ax;
	double bx;
	double cx;
	double dx;
};

//}-------------strucutures-----------------------------

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------declarations----------------------------

//==------------stack.cpp-------------------------------

Stack *Stack_new (int size);

void Stack_delete (Stack *myStack);

int Stack_OK (const Stack *myStack);

void Stack_dump (const Stack *myStack);

int Stack_push (Stack *myStack, double value);

double Stack_pop (Stack *myStack);

int Stack_getsize (Stack *myStack);

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//==------------assembler.cpp---------------------------

int id_command (char *str_4);

int asm_reg (char reg[]);

void asm_mark (char mark[], int pos, int mkdata[]);

int asm_set_marks (int *x, FILE* fi, int mkdata[]);

int asm_len_command (int command, int *x, FILE *fi, int mkdata[]);

int asm_command (int command, int x, FILE* fi, FILE* fo);

int asm_run (FILE *fi, FILE *fo); // see INPUT and OUTPUT in assembler.cpp.

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//==-------------CPU.cpp--------------------------------

CPU* CPU_new (int Stack_size);

void CPU_delete (CPU *myCPU);

int CPU_OK (const CPU *myCPU);

void CPU_dump (const CPU *myCPU);

double CPU_get_reg (const CPU *myCPU, const int regnum);

void CPU_set_reg (CPU *myCPU, const int regnum, double value);

Stack* CPU_get_Stack (const CPU *myCPU);

int CPU_push (CPU *myCPU, double value);

double CPU_pop (CPU *myCPU);

int CPU_run (const double *const data, CPU *myCPU, FILE *fo);

int CPU_do (const double *const data, CPU *myCPU, int *index, FILE *fo, FILE *logs);

//}-------------declarations----------------------------
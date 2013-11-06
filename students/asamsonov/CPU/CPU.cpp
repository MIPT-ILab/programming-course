//{-------------head----------------------------------
//
//! @file    CPU.cpp
//! @brief   CPU is done. It needs some improvements though.
//!
//}-------------head--------------------------------

#include "CPUheader.h"

#ifndef CPUHEADER 
	fprintf (stderr, "CPUwork.h is not existing.\n");
	abort ();
#endif

#ifdef INFO
	#undef INFO
#endif
	#define INFO  if (logs != NULL) fprintf

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

/*
CPU* CPU_create(int Stack_size);

void CPU_delete(CPU *myCPU);

int CPU_OK(const CPU *myCPU);

void CPU_dump(const CPU *myCPU);

double CPU_get_reg(const CPU *myCPU, const int reg);

void CPU_set_reg(CPU *myCPU, const int reg, double value);

Stack* CPU_get_Stack(const CPU *myCPU);

double CPU_push(CPU *myCPU, double value);

CPU* CPU_pop(CPU *myCPU);

int CPU_run (FILE* fi, CPU* myCPU);

int CPU_do(const int *const data, CPU* myCPU, int cur);
*/

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

//{-------------CPU------------------------------------
//! @brief		Creates new CPU
//!
//! @param		Stack_size		size of stack of the new CPU.
//!
//! @return		pointer on the new CPU	
//!
//! @see     CPU_delete(), CPU_OK()
//}-------------CPU-------------------------------------

CPU* CPU_new(int Stack_size)
{
	CPU *temp = (CPU *)malloc (sizeof (*temp));
	temp->CPU_Stack = Stack_new (Stack_size);
	temp->ax = 0;
	temp->bx = 0;
	temp->cx = 0;
	temp->dx = 0;
	return temp;
}

//{-------------CPU------------------------------------
//! @brief		Deletes CPU one.
//!
//! @param		myCPU		CPU to delete.
//!
//! @see     CPU_new(), CPU_OK()
//}-------------CPU-------------------------------------

void CPU_delete(CPU* myCPU)
{
	if (!myCPU) return;
	Stack_delete (myCPU->CPU_Stack);
	myCPU->ax = BAD;
	myCPU->bx = BAD;
	myCPU->cx = BAD;
	myCPU->dx = BAD;
	free (myCPU);
	myCPU = NULL;
}

//{-------------CPU------------------------------------
//! @brief		Diagnoses CPU.
//!
//! @param		myCPU		CPU to diagnose.
//!
//! @return		if CPU is ok or not (1 || 0).
//!
//! @see     CPU_dump()
//}-------------CPU-------------------------------------

int CPU_OK(const CPU* myCPU)
{
	return (myCPU && Stack_OK (myCPU->CPU_Stack));
}

//{-------------CPU------------------------------------
//! @brief   This function prints info about CPU.
//!
//! @param		myCPU		CPU given
//!
//! @par		It prints:
//!				- That it's CPU;
//!				- Adress of this CPU;
//!				- If CPU is ok or not;
//!				- CPU regs;
//!				- CPU_Stack dump;
//!
//! @see     CPU_OK()
//}-------------CPU-------------------------------------

void CPU_dump(const CPU* myCPU)
{
	int ok = CPU_OK (myCPU);
	printf ("Hello @, I'm CPU. %.8X. // %s\n", myCPU, ok? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!");

	printf ("\t" "ax = %d\n", myCPU->ax);
	printf ("\t" "bx = %d\n", myCPU->bx);
	printf ("\t" "cx = %d\n", myCPU->cx);
	printf ("\t" "dx = %d\n", myCPU->dx);

	printf ("\t" "I have got a Stack: \n");
	Stack_dump (myCPU->CPU_Stack);
	printf ("CPU: That's all.\n\n");
}

//{-------------CPU------------------------------------
//! @brief		returns reg of CPU
//!
//! @param		myCPU	CPU given.
//! @param		reg		const reg that is defined in CPUheader.h
//!
//! @return		reg value	
//!
//! @see     CPU_set_reg(), CPU_get_Stack()
//}-------------CPU-------------------------------------

double CPU_get_reg(const CPU *myCPU, const int reg)
{
	ASSERT_CPU (myCPU);
	return (reg == AX)? myCPU->ax : 
		   (reg == BX)? myCPU->bx : 
		   (reg == CX)? myCPU->cx : 
		   (reg == DX)? myCPU->dx : 
	BAD;
}

//{-------------CPU------------------------------------
//! @brief		assigns a value to the reg of CPU
//!
//! @param		myCPU	CPU given.
//! @param		reg		const reg that is defined in CPUheader.h
//! @param		value	well, value to assign to.	
//!
//! @see     CPU_get_reg(), CPU_get_Stack()
//}-------------CPU-------------------------------------

void CPU_set_reg(CPU *myCPU, const int reg, double value)
{
	ASSERT_CPU (myCPU);
	(reg == AX)? myCPU->ax = value : 
	(reg == BX)? myCPU->bx = value : 
	(reg == CX)? myCPU->cx = value : 
	(reg == DX)? myCPU->dx = value : 
	BAD;
}

//{-------------CPU------------------------------------
//! @brief		returns Stack of CPU
//!
//! @param		myCPU	CPU given.
//!
//! @return		pointer of the Stack.	
//!
//! @see     CPU_push(), CPU_pop()
//}-------------CPU-------------------------------------

Stack* CPU_get_Stack(const CPU *myCPU)
{
	ASSERT_CPU (myCPU);
	return myCPU->CPU_Stack;
}

//{-------------CPU------------------------------------
//! @brief   This function adds new element in the end of CPU Stack.
//!
//! @param		myCPU		CPU that includes a Stack
//! @param		value		new element	
//!
//! @return		1 if you can add element, 0 if Stack is full.
//!
//! @see     CPU_OK(), CPU_pop()
//}-------------CPU-------------------------------------

int CPU_push(CPU *myCPU, double value)
{
	ASSERT_CPU (myCPU);
	if (myCPU->CPU_Stack->size >= myCPU->CPU_Stack->maxsize)
		return 0;
	myCPU->CPU_Stack->data[myCPU->CPU_Stack->size++] = value;

	ASSERT_CPU (myCPU);
	return 1;
}

//{-------------CPU------------------------------------
//! @brief   This function takes last element from CPU Stack deleting it.
//!
//! @param		myCPU		CPU
//!
//! @return		Last element of this Stack.	
//!
//! @see     CPU_OK(), CPU_push()
//}-------------CPU-------------------------------------

double CPU_pop(CPU *myCPU)
{
	ASSERT_CPU (myCPU);
	ASSERT_OK (myCPU->CPU_Stack);
	ASSERT (myCPU->CPU_Stack->size != 0);
	return myCPU->CPU_Stack->data[--myCPU->CPU_Stack->size];
}

//{-------------CPU------------------------------------
//! @brief   This function takes data with some commands in it 
//!			 and executes them all.
//!
//! @param		data	absolutely const array of commands.
//! @param		myCPU	CPU executing these commands.
//! @param		fo		file to output results to.
//!
//! @return		1 if Well done, 0 if there was an interruption or an error found.
//!
//! @see     CPU_do()
//}-------------CPU-------------------------------------

int CPU_run (const double *const data, CPU* myCPU, FILE *fo)
{
	ASSERT (myCPU);
	ASSERT (data);

	FILE *logs = fopen (STDERR, "w");
	int cur = 0;
	int ret = 0;

	while (ret = CPU_do (data, myCPU, &cur, fo, logs))
		if (ret == -1) {
			fclose (logs);
			return 1;
		}

	fclose (logs);
	return 0;
}

#define DO_SMTH(command, code)  case command : { code; *cur += 1; return 1; }
#define DO_ARG(command, code1, code2, strcom, fail)  \
	case command : { \
		if (IS_EQUAL(data[*cur + 1], NUM)) {\
			code1; \
			return 1; \
		}\
		if (IS_EQUAL(data[*cur + 1], REG)) {\
			code2; \
			return 1; \
		}\
		INFO (logs, "# %d, %s: %s.\n", *cur, strcom, fail);\
		return 0;\
	}
#define DO_JUMP(command, cond)  case command : { if (cond) { *cur = (int)data[*cur + 1]; return 1; } *cur += 2; return 1; }

//{-------------CPU------------------------------------
//! @brief   This function takes an index of command to execute 
//!			 and executes it with, maybe, some args.
//!
//! @param		data	absolutely const array of commands.
//! @param		myCPU	CPU executing these commands.
//! @param		cur		current index.
//! @param		fo		file to output results to.
//! @param		logs	file containing logs.
//!
//! @return		-1 if END found, 0 if there was an interruption or an error found.
//!				+1 means "to be continued".
//!
//! @see     CPU_run(), CPU_push(), CPU_pop()
//}-------------CPU-------------------------------------

int CPU_do(const double *const data, CPU* myCPU, int *cur, FILE *fo, FILE *logs)
{
	ASSERT (myCPU);
	ASSERT (data);
	int command = (int)data[*cur]; 

	switch (command) {
		
		DO_ARG (PUSH, { CPU_push (myCPU, data[*cur + 2]);	*cur += 3; }, 
				{ CPU_push (myCPU, CPU_get_reg (myCPU, (int)data[*cur + 2])); *cur += 3; },
				"push", "args interrupt");
		DO_ARG (POP, { fprintf (fo, "%lg ", CPU_pop (myCPU)); *cur += 2; }, 
				{ CPU_set_reg (myCPU, (int)data[*cur + 2], CPU_pop (myCPU)); *cur+= 3; },
				"pop", "args interrupt");
		DO_SMTH ( END, return -1;);

		DO_SMTH ( ADD, CPU_push (myCPU, +CPU_pop (myCPU) + CPU_pop (myCPU)););

		DO_SMTH ( SUB, CPU_push (myCPU, -CPU_pop (myCPU) + CPU_pop (myCPU)););

		DO_SMTH ( MUL, CPU_push (myCPU, +CPU_pop (myCPU) * CPU_pop (myCPU)););

		DO_SMTH ( DIV, double extra = CPU_pop (myCPU); 
					   if (IS_EQUAL (extra, 0)) {
						   INFO (logs, "# %d, div: division by zero interrupt.\n, *cur");
						   return 0;
					   }
					   CPU_push (myCPU, CPU_pop (myCPU) / extra););

		DO_SMTH (SQRT, double extra = CPU_pop (myCPU);
					   if (extra < 0) {
						   INFO (logs, "# %d, sqrt: negative number interrupt.\n, *cur");
						   return 0;
					   }
					   CPU_push (myCPU, sqrt (extra)););

		DO_SMTH ( POW, double extra = CPU_pop (myCPU); 
					   CPU_push (myCPU, pow  (CPU_pop (myCPU), extra)););

		DO_SMTH ( SIN, CPU_push (myCPU, sin  (CPU_pop (myCPU))););

		DO_SMTH ( COS, CPU_push (myCPU, cos  (CPU_pop (myCPU))););

		DO_SMTH ( DUB, double extra = CPU_pop (myCPU); 
					   CPU_push (myCPU, extra);
					   CPU_push (myCPU, extra));
		DO_ARG ( OUT, { double extra = CPU_pop (myCPU); fprintf (fo, "%lg" "\t" "%lg\n", CPU_pop (myCPU), extra);  *cur += 2; }, 
				{ double extra = CPU_pop (myCPU); fprintf (fo, "%lg\n", CPU_get_reg (myCPU, (int)data[*cur + 2])); *cur += 3; },
				  "out", "args interrupt");
		DO_ARG ( MOV, { CPU_set_reg (myCPU, (int)data[*cur + 2], data[*cur + 3]); *cur += 4; }, 
				{ CPU_set_reg (myCPU, (int)data[*cur + 2], CPU_get_reg (myCPU, (int)data[*cur + 3])); *cur += 4; },
				  "mov", "args interrupt");
		DO_JUMP ( JMP, 1);
		DO_JUMP ( JBE, CPU_pop (myCPU) >= CPU_pop (myCPU));
		DO_JUMP ( JAE, CPU_pop (myCPU) <= CPU_pop (myCPU));
		DO_JUMP ( JNE, !IS_EQUAL (CPU_pop (myCPU), CPU_pop (myCPU)));
		DO_JUMP (  JB, CPU_pop (myCPU) >  CPU_pop (myCPU));
		DO_JUMP (  JA, CPU_pop (myCPU) <  CPU_pop (myCPU));
		DO_JUMP (  JE, IS_EQUAL (CPU_pop (myCPU), CPU_pop (myCPU)));
		DO_JUMP (  JF, FRIDAY);
		default : INFO (logs, "# %d, default: undefined command interrupt\n",*cur); return 0;
	}

	INFO (logs, "# %d, EOswitch: smthing wrong interrupt\n", *cur);
	return 0;
}

#undef DO_SMTH
#undef DO_ARG
#undef DO_JUMP
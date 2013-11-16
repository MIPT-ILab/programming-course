#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "DEFINES.h"
#include "CONSTS.h"
#include <float.h>



typedef struct stack_s
    {
        double* data;
        int  max_size;
        int  size_now;
    } stack;

typedef struct cpu_s
    {
        stack*  cpu_stack;
        double  ax, bx, cx, dx, ex, fx, gx;
		double* codes;
		stack*  call_funcs;
    } cpu;


int the_asm (FILE* my_program, FILE* binary, FILE* the_log);
int add_code (double codes[], int* cur_code, double code);
int asm_print (double codes[], int nCodes, FILE* binary);


cpu*	Cpu_Construct ();
void	Cpu_Destruct (cpu* my_cpu);
int		Cpu_OK (cpu* my_cpu);
void	Cpu_Dump (cpu* my_cpu, FILE* my_log);
int		Check_Error (int error, FILE* my_log);
int		Cpu_Push (cpu* my_cpu, int* cur, int command);
int		Cpu_Dup (cpu* my_cpu);
int		Cpu_Pop (cpu* my_cpu, int* cur);
int		Cpu_Mov (cpu* my_cpu, int* cur, int command);
int		Cpu_Out (cpu* my_cpu, int* cur, int command, FILE* output);
int		Cpu_In (cpu* my_cpu, int* cur, int command);
int		Cpu_End (cpu* my_cpu, FILE* output, int* exit);

int		Cpu_Load (cpu* my_cpu, FILE* binary);
int		Cpu_Run  (cpu* my_cpu, FILE* output, FILE* my_log);

int Cpu_Add (cpu* my_cpu);
int Cpu_Sub (cpu* my_cpu);
int Cpu_Mul (cpu* my_cpu);
int Cpu_Div (cpu* my_cpu);
int Cpu_Sqr (cpu* my_cpu);
int Cpu_Pow (cpu* my_cpu);
int Cpu_Sqrt (cpu* my_cpu);
int Cpu_Sin (cpu* my_cpu);
int Cpu_Cos (cpu* my_cpu);
int Cpu_Tan (cpu* my_cpu);
int Cpu_Ctan (cpu* my_cpu);




stack* Stack_Construct (int stack_size);
void   Stack_Destruct (stack* the_stack);
int    Stack_OK (const stack* the_stack);
void   Stack_Dump (stack* the_stack, FILE* my_log);
int    Stack_Full (stack* the_stack);
int    Stack_Empty (stack* the_stack);
int	   Stack_Push (stack* the_stack, double item);
int    Stack_Pop (stack* the_stack, double* pop);

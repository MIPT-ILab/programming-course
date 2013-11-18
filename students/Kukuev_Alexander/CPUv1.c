//#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cpu.c"

#define PUSH    1
#define POP     2
#define PUSH_AX 3
#define POP_AX  4
#define ADD     5
#define SUBT    6
#define MUL     7
#define DIV     8
#define DUMP    9
#define END     10





int main()
{
	struct CPU_t cpu;
	cpu_construct(&cpu);
	
	printf("push    1\n");
	printf("pop     2\n");
	printf("push_ax 3\n");
	printf("pop_ax  4\n");
	printf("add     5\n");
	printf("subt    6\n");
	printf("mul     7\n");
	printf("div     8\n");
	printf("dump    9\n");
	printf("end     10\n\n");
	
	int    op    = 0;
	elem_t digit = 0;
	scanf("%d", &op);
	while (op != END)
	{
		switch (op)
		{
			case PUSH   : scanf("%d", &digit); cpu_push(&cpu, digit); break;
			case POP    : cpu_pop(&cpu);                              break;
			case PUSH_AX: cpu_push_ax(&cpu);                          break;
			case POP_AX : cpu_pop_ax(&cpu);                           break;
			case ADD    : cpu_add(&cpu);                              break;
			case SUBT   : cpu_subt(&cpu);                             break;
			case MUL    : cpu_mul(&cpu);                              break;
			case DIV    : cpu_div(&cpu);                              break;
			case DUMP   : cpu_dump(&cpu);                             break;
			case END    : cpu_destruct(&cpu);                         break;
			default: assert(!"сommand not found"); break;
		
		}
		scanf("%d", &op);
	}
	return 0;
}

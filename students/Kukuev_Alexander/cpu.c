#include "stack.c"

struct CPU_t 
{
	struct Stack_t st;
	elem_t ax;
};

void cpu_construct(struct CPU_t *cpu)
{
	stack_construct(&(cpu->st));
	cpu->ax = 0;
}
void cpu_destruct(struct CPU_t *cpu)
{
	stack_destruct(&(cpu->st));
	cpu->ax = 0xBAD;
}

int cpu_ok(struct CPU_t *cpu)
{
	return (cpu && stack_ok(&(cpu->st)));
}

void cpu_dump(struct CPU_t *cpu)
{
	stack_dump(&(cpu->st));
	printf("ax = %d\n\n", cpu->ax);
}

elem_t cpu_push(struct CPU_t *cpu, elem_t digit)
{
	if (cpu_ok(cpu))
		return stack_push(&(cpu->st),digit);	
	else
	{
		cpu_dump(cpu);
		assert(!"push don't complite");
		return 0;
	} 
}

elem_t cpu_pop(struct CPU_t *cpu)
{
	if (cpu_ok(cpu))
		return stack_pop(&(cpu->st));
	else
	{	
		cpu_dump(cpu);
		assert(!"pop don't complete");
		return 0;
	}
}

elem_t cpu_push_ax(struct CPU_t *cpu)
{
	if (cpu_ok(cpu))
	{
		return cpu_push(cpu, cpu->ax);
	}
	else
	{
		cpu_dump(cpu);
		assert(!"push ax don't complete");
		return 0;
	}
}

elem_t cpu_pop_ax(struct CPU_t *cpu)
{
	if(cpu_ok(cpu))
	{
		cpu->ax = cpu_pop(cpu);
		return cpu->ax;
	}
	else 
	{
		cpu_dump(cpu);
		assert(!"pop ax don't complete");
		return 0;
	}
}


////////###################

elem_t cpu_add(struct CPU_t *cpu)
{
	elem_t num1 = 0, num2 = 0;
	if(cpu_ok(cpu))
	{
		num1 = cpu_pop(cpu);
		num2 = cpu_pop(cpu);
		return cpu_push(cpu, num1 + num2); 
	}
	else
	{
		cpu_dump(cpu);
		assert(!"add don't complete, stack not ok");
		return 0;
	}
	
}

elem_t cpu_subt(struct CPU_t *cpu)
{
	elem_t num1 = 0, num2 = 0;
	if(cpu_ok(cpu))
	{
		num2 = cpu_pop(cpu);
		num1 = cpu_pop(cpu);
		return cpu_push(cpu, num1 - num2);
	}
	else
	{
		cpu_dump(cpu);
		assert(!"subt don't complete, stack not ok");
		return 0;
	}
}

elem_t cpu_mul(struct CPU_t *cpu)
{
	elem_t num1 = 0, num2 = 0;
	if(cpu_ok(cpu))
	{
		num2 = cpu_pop(cpu);
		num1 = cpu_pop(cpu);
		return cpu_push(cpu, num1 * num2);
	}
	else
	{
		cpu_dump(cpu);
		assert(!"mul don't complete, stack not ok");
		return 0;
	}
}

elem_t cpu_div(struct CPU_t *cpu)
{
	elem_t num1 = 0, num2 = 0;
	if(cpu_ok(cpu))
	{
		num2 = cpu_pop(cpu);
		num1 = cpu_pop(cpu);
		if ( num2 == 0) 
			assert(!"i can't div in null");
		return cpu_push(cpu, num1 / num2);
	}
	else
	{
		cpu_dump(cpu);
		assert(!"div don't complete, stack not ok");
		return 0;
	}
	
}


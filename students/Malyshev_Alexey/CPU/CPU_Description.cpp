#include "Stack_Description.c"
#define CPU_type st_type

const int Code_SIZE = 30;
const int Marks_Quant = 10;


struct CPU
{
	struct Stack_t CPU_stack;
	double code[Code_SIZE];
	int marks[Marks_Quant];
	int cur;
	CPU_type ax;
};

void CPU_Construct(CPU* cpu)
{
	Stack_Construct(&(cpu->CPU_stack));
	cpu->ax = 0;
	cpu->cur = 0;
	int i = 0;
	for (i = 0; i < Code_SIZE; i++)
	{
		cpu->code[i] = -1;
	}
	for (i = 0; i < Marks_Quant; i++)
	{
		cpu->marks[i] = -1;
	}
    return;
}

void CPU_Destruct(CPU* cpu)
{
	Stack_Destruct(&(cpu->CPU_stack));
	cpu->ax = 0xBAD;
	return;
}

void CPU_PUSH(CPU* cpu, CPU_type elem)
{
	Stack_PUSH(&(cpu->CPU_stack), elem);
	return;
}

void CPU_PUSH_AX(CPU* cpu)
{
	CPU_PUSH(cpu, cpu->ax);
	//printf("ax = %lg\n", &cpu->ax);
	return;
}

void CPU_POP_AX(CPU* cpu)
{
	cpu->ax = Stack_POP(&(cpu->CPU_stack));
	//printf("ax = %lg\n", &cpu->ax);
	return;
}

void CPU_ADD(CPU* cpu)
{
	CPU_type a = Stack_POP(&(cpu->CPU_stack));
	a += Stack_POP(&(cpu->CPU_stack));
	CPU_PUSH(cpu, a);
	return;
}

void CPU_SUB(CPU* cpu)
{
	CPU_type a = Stack_POP(&(cpu->CPU_stack));
	a = (-a);
	a += Stack_POP(&(cpu->CPU_stack));
	CPU_PUSH(cpu, a);
	return;
}

void CPU_MUL(CPU* cpu)
{
	CPU_type a = Stack_POP(&(cpu->CPU_stack));
	a *= Stack_POP(&(cpu->CPU_stack));
	CPU_PUSH(cpu, a);
	return;
}

void CPU_OUT(CPU* cpu)
{
	printf("%lg\n", cpu->CPU_stack.Data[(cpu->CPU_stack.Top)-1]);
	return;
}

void CPU_JMP(CPU* cpu, int JMP_POS)
{
	cpu->cur = JMP_POS;
	//printf("JUMP!");
	return;
}

void CPU_JBE(CPU* cpu, int JMP_POS)
{
	CPU_type a = cpu->CPU_stack.Data[cpu->CPU_stack.Top-2];
	CPU_type b = cpu->CPU_stack.Data[cpu->CPU_stack.Top-1];
	//printf("JBE_a=%lg\n", a);
	//printf("JBE_b=%lg\n", b);
	if (a <= b)
	{
		cpu->cur = JMP_POS;
		//printf("JBE!\n");
	}
	else
	{
		cpu->cur += 2;
	}
	return;
}

void CPU_RUN(CPU* cpu)
{
	cpu->cur = 0;
	while (cpu->code[cpu->cur])
	{
		switch (int(cpu->code[cpu->cur]))
		{
			case 1:
				{
					CPU_PUSH(cpu, cpu->code[++cpu->cur]);
					cpu->cur++;
					break;
				}
			case 2:
				{
					CPU_PUSH_AX(cpu);
					cpu->cur++;
					break;
				}
			case 3:
				{
					CPU_POP_AX(cpu);
					cpu->cur++;
					break;
				}
			case 4:
				{
					CPU_ADD(cpu);
					cpu->cur++;
					break;
				}
			case 5:
				{
					CPU_SUB(cpu);
					cpu->cur++;
					break;
				}
			case 6:
				{
					CPU_MUL(cpu);
					cpu->cur++;
					break;
				}
			case 7:
				{
					CPU_OUT(cpu);
					cpu->cur++;
					break;
				}
			case 8:
				{
					CPU_JMP(cpu, cpu->code[cpu->cur+1]);
					//cpu->cur++;
					break;
				}
			case 9:
				{
					CPU_JBE(cpu, cpu->code[cpu->cur+1]);
					break;
				}

		}
		//printf("cpu->cur==%d", cpu->cur);


	}
	return;
}

void ASM(CPU* cpu, const char* CMDS_FILE)
{
	freopen(CMDS_FILE, "r", stdin);
	double val = 0;
	int i=0;
	char c = 0;
	int marknum = 0;
	int JMP_POS = 0;
	char command[100]={};
	//gets(command);
	//printf("%s", command);
	while (gets(command))
	{
		//printf("%s\n", command);
		//gets(command);
		//printf("%s\n", command);
		if (!strcmp(command, "end"))
		{
			cpu->code[cpu->cur++] = 0;

		}
		if (!strcmp(command, "push"))
		{
			cpu->code[cpu->cur++] = 1;
			scanf("%lg", &val);
			cpu->code[cpu->cur++] = val;
		}
		if (!strcmp(command, "push_ax"))
		{
			cpu->code[cpu->cur++]=2;
		}
		if (!strcmp(command, "pop_ax"))
		{
			cpu->code[cpu->cur++] = 3;
		}
		if (!strcmp(command, "add"))
		{
			cpu->code[cpu->cur++] = 4;
		}
		if (!strcmp(command, "sub"))
		{
			cpu->code[cpu->cur++] = 5;
		}
		if (!strcmp(command, "mul"))
		{
			cpu->code[cpu->cur++] = 6;
		}
		if (!strcmp(command, "out"))
		{
			cpu->code[cpu->cur++] = 7;
		}
		if (!strcmp(command, "jmp"))
		{
			cpu->code[cpu->cur++] = 8;
			scanf("%c", &c);
			cpu->cur++;
		}
		if (!strcmp(command, "jbe"))
		{
			cpu->code[cpu->cur++] = 9;
			scanf("%c", &c);
			cpu->cur++;
		}
		if (command[0] == ':')
		{
			marknum = command[1]-'0';
			cpu->marks[marknum] = cpu->cur;
		}
	}
	freopen(CMDS_FILE, "r", stdin);
	cpu->cur = 0;
	while (gets(command))
	{
		//printf("%s\n", command);
		if (!strcmp(command, "end"))
		{
			cpu->code[cpu->cur++] = 0;

		}
		if (!strcmp(command, "push"))
		{
			cpu->code[cpu->cur++] = 1;
			scanf("%lg", &val);
			cpu->code[cpu->cur++] = val;
		}
		if (!strcmp(command, "push_ax"))
		{
			cpu->code[cpu->cur++]=2;
		}
		if (!strcmp(command, "pop_ax"))
		{
			cpu->code[cpu->cur++] = 3;
		}
		if (!strcmp(command, "add"))
		{
			cpu->code[cpu->cur++] = 4;
		}
		if (!strcmp(command, "sub"))
		{
			cpu->code[cpu->cur++] = 5;
		}
		if (!strcmp(command, "mul"))
		{
			cpu->code[cpu->cur++] = 6;
		}
		if (!strcmp(command, "out"))
		{
			cpu->code[cpu->cur++] = 7;
		}
		if (!strcmp(command, "jmp"))
		{
			cpu->code[cpu->cur++] = 8;
			scanf("%c", &c);
			scanf("%d", &JMP_POS);
			cpu->code[cpu->cur++] = cpu->marks[JMP_POS];
			//cpu->cur++;
		}
		if (!strcmp(command, "jbe"))
		{
			cpu->code[cpu->cur++] = 9;
			scanf("%c", &c);
			scanf("%d", &JMP_POS);
			cpu->code[cpu->cur++] = cpu->marks[JMP_POS];
			//cpu->cur++;
		}
	}
	return;

}
int main()
{
	CPU cpu;
	int i=0;
	CPU_Construct(&cpu);
	/*for (i = 0; i<Code_SIZE; i++)
	{
		printf("%lg\n", cpu.code[i]);
	}*/
    ASM(&cpu, "CommandsFile.txt");
    for (i = 0; i < Code_SIZE; i++)
	{
		printf("Code#%d == %lg\n",i, cpu.code[i]);
	}
	for (i = 0; i < Marks_Quant; i++)
	{
		printf("Mark number %d: %d\n", i, cpu.marks[i]);
	}
    CPU_RUN(&cpu);
	return 0;
}

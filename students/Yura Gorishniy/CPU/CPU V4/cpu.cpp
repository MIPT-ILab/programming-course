#include "cpu.h"

cpu* Cpu_Construct ()
{
    cpu* new_cpu = (cpu*) calloc (1, sizeof(cpu));
    new_cpu -> cpu_stack = Stack_Construct (10);
	new_cpu -> codes = (double*)  calloc (COMMANDS_SIZE, sizeof(double));
	new_cpu -> call_funcs = Stack_Construct (10);

return new_cpu;
}

void Cpu_Destruct (cpu* my_cpu)
{
    Stack_Destruct (my_cpu -> cpu_stack);
	Stack_Destruct (my_cpu -> call_funcs);

    my_cpu -> ax = POiSON;
    my_cpu -> bx = POiSON;
    my_cpu -> cx = POiSON;
    my_cpu -> dx = POiSON;
    my_cpu -> ex = POiSON;
    my_cpu -> fx = POiSON;
    my_cpu -> gx = POiSON;

	free (my_cpu -> codes);
    free (my_cpu);
}

int Cpu_OK (cpu* my_cpu)
{
    return Stack_OK (my_cpu -> cpu_stack);
}

void Cpu_Dump (cpu* my_cpu, FILE* my_log)
{
    if (Cpu_OK (my_cpu))              fprintf (my_log, "\n" "Your CPU [%.8x] is ok\n",     my_cpu);
    else                              fprintf (my_log, "\n" "Your CPU [%.8x] is NOT ok\n", my_cpu);

    fprintf (my_log, "Register [ax] = %lg\n", my_cpu -> ax);
    fprintf (my_log, "Register [bx] = %lg\n", my_cpu -> bx);
    fprintf (my_log, "Register [cx] = %lg\n", my_cpu -> cx);
    fprintf (my_log, "Register [dx] = %lg\n", my_cpu -> dx);
    fprintf (my_log, "Register [ex] = %lg\n", my_cpu -> ex);
    fprintf (my_log, "Register [fx] = %lg\n", my_cpu -> fx);
    fprintf (my_log, "Register [gx] = %lg\n\n", my_cpu -> gx);

    Stack_Dump (my_cpu -> cpu_stack, my_log);
}

int Check_Error (int error, FILE* my_log)
{
    switch (error)
    {
        case HAPPY:
            return HAPPY;
            break;

        CHOOSE_ERR;

        default:
            fprintf (my_log, "\n" "Something went strange\n");
            abort();
            break;
    }

}

int Cpu_End (cpu* my_cpu, FILE* output, int* exit)
{
	ASSERT_CPU_OK (my_cpu);
	fclose (output);
	*exit = 1;
	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Push (cpu* my_cpu, int* cur, int command)
{
    ASSERT_CPU_OK (my_cpu);

	++*cur;
	if (!(command - CMD_PUSH)) Stack_Push (my_cpu -> cpu_stack, my_cpu -> codes[*cur]);
	else
	{
		int reg = int (my_cpu -> codes[*cur]);
		switch (reg)
		{
			case AX:
				Stack_Push (my_cpu -> cpu_stack, my_cpu -> ax);
				break;

			case BX:
				Stack_Push (my_cpu -> cpu_stack, my_cpu -> bx);
				break;

			case CX:
				Stack_Push (my_cpu -> cpu_stack, my_cpu -> cx);
				break;

			case DX:
				Stack_Push (my_cpu -> cpu_stack, my_cpu -> dx);
				break;
		}
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Dup (cpu* my_cpu)
{
	ASSERT_CPU_OK (my_cpu);
	if (my_cpu -> cpu_stack -> size_now == 0) return ERR_DUP;

	double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
	Stack_Push (my_cpu -> cpu_stack, a);
	Stack_Push (my_cpu -> cpu_stack, a);

	ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Pop (cpu* my_cpu, int* cur)
{
	ASSERT_CPU_OK (my_cpu);
	if (my_cpu -> cpu_stack -> size_now == 0) return ERR_CPU_POP;

	++*cur;
	double pop = 0;
	Stack_Pop (my_cpu -> cpu_stack, &pop);
	int reg = int (my_cpu -> codes[*cur]);
	switch (reg)
	{
		CASE_REG_MOV (AX, my_cpu -> ax, pop);
		CASE_REG_MOV (BX, my_cpu -> bx, pop);
		CASE_REG_MOV (CX, my_cpu -> cx, pop);
		CASE_REG_MOV (DX, my_cpu -> dx, pop);
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Mov (cpu* my_cpu, int* cur, int command)
{
	ASSERT_CPU_OK (my_cpu);

	++*cur;

	if (!(command - CMD_MOV))
	{
		int reg = int (my_cpu -> codes[*cur]);
		++*cur;
		double mov = my_cpu -> codes[*cur];
		switch (reg)
		{
			case AX:
				my_cpu -> ax = mov;
				break;
				CASE_REG_MOV (BX, my_cpu -> bx, mov);
			CASE_REG_MOV (CX, my_cpu -> cx, mov);
			CASE_REG_MOV (DX, my_cpu -> dx, mov);
		}
	}

	else
	{
		int reg = int (my_cpu -> codes[*cur + 1]);
		double mov = 0;
		switch (reg)
		{
			CASE_REG_MOV (AX, mov, my_cpu -> ax);
			CASE_REG_MOV (BX, mov, my_cpu -> bx);
			CASE_REG_MOV (CX, mov, my_cpu -> cx);
			CASE_REG_MOV (DX, mov, my_cpu -> dx);
		}
		
		reg = int (my_cpu -> codes[*cur]);
		switch (reg)
		{
			CASE_REG_MOV (AX, my_cpu -> ax, mov);
			CASE_REG_MOV (BX, my_cpu -> bx, mov);
			CASE_REG_MOV (CX, my_cpu -> cx, mov);
			CASE_REG_MOV (DX, my_cpu -> dx, mov);
		}
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_In (cpu* my_cpu, int* cur, int command)
{
	ASSERT_CPU_OK (my_cpu);

	double in = 0;
	if (!(command - CMD_IN))
	{
		printf ("\n# Push in Stack: ");
		scanf ("%lg", &in);
		Stack_Push (my_cpu -> cpu_stack, in);
	}

	else
	{
		++*cur;
		int reg = int (my_cpu -> codes[*cur]);
		printf ("\n# Push in register[%d]: ", reg - 800);
		scanf ("%lg", &in);
		switch (reg)
		{
			CASE_REG_MOV (AX, my_cpu -> ax, in);
			CASE_REG_MOV (BX, my_cpu -> bx, in);
			CASE_REG_MOV (CX, my_cpu -> cx, in);
			CASE_REG_MOV (DX, my_cpu -> dx, in);
		}
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Out (cpu* my_cpu, int* cur, int command, FILE* output)
{
	ASSERT_CPU_OK (my_cpu);

	if (!(command - CMD_OUT))
	{
		double out = 0;
		Stack_Pop (my_cpu -> cpu_stack, &out);
		fprintf (output, "%lg\n", out);
	}
	else
	{
		++*cur;
		int reg = int (my_cpu -> codes[*cur]);
		switch (reg)
		{
			case AX:
				fprintf (output, "%lg\n", my_cpu -> ax);
				break;

			case BX:
				fprintf (output, "%lg", my_cpu -> bx);
				break;

			case CX:
				fprintf (output, "%lg", my_cpu -> cx);
				break;

			case DX:
				fprintf (output, "%lg", my_cpu -> dx);
				break;
		}
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Add (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now < 2) return ERR_ADD;

    double a = 0;
    double b = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);
    Stack_Pop (my_cpu -> cpu_stack, &b);

    Stack_Push (my_cpu -> cpu_stack, b + a);

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Sub (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now < 2) return ERR_SUB;

    double a = 0;
    double b = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);
    Stack_Pop (my_cpu -> cpu_stack, &b);

    Stack_Push (my_cpu -> cpu_stack, b - a);

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Mul (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now < 2) return ERR_MUL;

    double a = 0;
    double b = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);
    Stack_Pop (my_cpu -> cpu_stack, &b);

    Stack_Push (my_cpu -> cpu_stack, b * a);

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Div (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now < 2) return ERR_DIV;

    double a = 0;
    double b = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);
    Stack_Pop (my_cpu -> cpu_stack, &b);
    if (a == 0) return ERR_DIV_ZERO;

    Stack_Push (my_cpu -> cpu_stack, b / a);

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Sqr (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_SQR;

    double a = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);

    Stack_Push (my_cpu -> cpu_stack, a * a);

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Pow (cpu* my_cpu)					//<<!!! FIX NEGATIVE BASE
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now < 2) return ERR_POW;

    double a = 0;
    double b = 0;
    Stack_Pop (my_cpu -> cpu_stack, &a);
    Stack_Pop (my_cpu -> cpu_stack, &b);

    if (a == 0 && b == 0) return ERR_POW_ZEROES;

    Stack_Push (my_cpu -> cpu_stack, pow (b, a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Sqrt (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_SQRT;

    double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
    if (a < 0) return ERR_SQRT_NEG;

    Stack_Push (my_cpu -> cpu_stack, sqrt (a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Sin (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_SIN;

    double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
    Stack_Push (my_cpu -> cpu_stack, sin (a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Cos (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_COS;

    double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
    Stack_Push (my_cpu -> cpu_stack, cos (a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Tan (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_TAN;

    double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
	if (fabs (cos(a)) <= ZERO) return ERR_TAN_INF;
    Stack_Push (my_cpu -> cpu_stack, sin (a) / cos (a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}

int Cpu_Ctan (cpu* my_cpu)
{
    ASSERT_CPU_OK (my_cpu);
    if (my_cpu -> cpu_stack -> size_now == 0) return ERR_CTAN;

    double a = 0;
    Stack_Pop  (my_cpu -> cpu_stack, &a);
    if (cos (a) == 1) return ERR_CTAN_INF;
    Stack_Push (my_cpu -> cpu_stack, cos (a) / sin (a));

    ASSERT_CPU_OK (my_cpu);

return HAPPY;
}


int Cpu_Load (cpu* my_cpu, FILE* binary)
{
	ASSERT_CPU_OK (my_cpu);

	double code = 0;
	int cur = 0;

	while (1)
	{
		if (fscanf (binary, "%lg", &code) > 0)
		{
			my_cpu -> codes[cur] = code;
			++cur;
		}
		else break;
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}

int Cpu_Run (cpu* my_cpu, FILE* output, FILE* my_log)
{
	ASSERT_CPU_OK (my_cpu);

	int cur = 0;
	int command = 0;
	int exit = 0;

	double a = 0; //temporary value 
	double b = 0; //temporary value

	for (cur = 0; cur < COMMANDS_SIZE; ++cur)
	{
		if (exit) break;
		command = int (my_cpu -> codes[cur]);
		OUT printf ("***%d\n", command);
		switch (command)
		{
			case CMD_PUSH: case CMD_PUSH_RX:
				Check_Error (Cpu_Push (my_cpu, &cur, command), my_log);
				break;

			case CMD_DUP:
				Check_Error (Cpu_Dup (my_cpu), my_log);
				break;

			case CMD_POP:
				Check_Error (Cpu_Pop (my_cpu, &cur), my_log);
				break;

			case CMD_IN: case CMD_IN_RX:
				Check_Error (Cpu_In (my_cpu, &cur, command), my_log);
				break;

			case CMD_OUT: case CMD_OUT_RX:
				Check_Error (Cpu_Out (my_cpu, &cur, command, output), my_log);
				break;

			case CMD_MOV: case CMD_MOV_RX:
				Check_Error (Cpu_Mov (my_cpu, &cur, command), my_log);
				break;

			case CMD_ADD:
				Check_Error (Cpu_Add (my_cpu), my_log);
				break;

			case CMD_SUB:
				Check_Error (Cpu_Sub (my_cpu), my_log);
				break;

			case CMD_MUL:
				Check_Error (Cpu_Mul (my_cpu), my_log);
				break;

			case CMD_DIV:
				Check_Error (Cpu_Div (my_cpu), my_log);
				break;

			case CMD_SQR:
				Check_Error (Cpu_Sqr (my_cpu), my_log);
				break;

			case CMD_POW:
				Check_Error (Cpu_Pow (my_cpu), my_log);
				break;

			case CMD_SQRT:
				Check_Error (Cpu_Sqrt (my_cpu), my_log);
				break;

			case CMD_SIN:
				Check_Error (Cpu_Sin (my_cpu), my_log);
				break;

			case CMD_COS:
				Check_Error (Cpu_Cos (my_cpu), my_log);
				break;

			case CMD_TAN:
				Check_Error (Cpu_Tan (my_cpu), my_log);
				break;

			case CMD_CTAN:
				Check_Error (Cpu_Ctan (my_cpu), my_log);
				break;

			case CMD_DUMP:
				Cpu_Dump (my_cpu, my_log);
				break;

			case CMD_END:
				Check_Error (Cpu_End (my_cpu, output, &exit), my_log);
				break;

			case CMD_CALL:
				Stack_Push (my_cpu -> call_funcs, cur + 1);
				cur = my_cpu -> codes[cur + 1] - 1;
				break;

			case CMD_RET:
				Stack_Pop (my_cpu -> call_funcs, &a);
				cur = int(a);
				break;

			case CMD_JMP:
				cur = my_cpu -> codes[cur + 1] - 1;
				break;

			case CMD_JB:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a < b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;

			case CMD_JBE:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a <= b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;

			case CMD_JE:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a == b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;

			case CMD_JAE:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a >= b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;

			case CMD_JA:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a > b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;

			case CMD_JUE:
				Stack_Pop (my_cpu -> cpu_stack, &b);
				Stack_Pop (my_cpu -> cpu_stack, &a);
				if (a != b) cur = my_cpu -> codes[cur + 1] - 1;
				else ++cur;
				break;


			default:
				fprintf (my_log, "\nCPU ERROR\n"
								 "Your command doesn't exist. Current command = [%d], your command = [%d]\n", cur, command);
				break;
		}
		//OUT frintf
	}

	ASSERT_CPU_OK (my_cpu);
return HAPPY;
}
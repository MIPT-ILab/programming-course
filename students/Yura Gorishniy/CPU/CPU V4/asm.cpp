#include "cpu.h"

int the_asm (FILE* my_program, FILE* binary, FILE* my_log)
{
	double codes[COMMANDS_SIZE] = {};
	static int labels[LABELS_SIZE]; //= {}
	int cur_code = 0;

	char str_command[10] = {};
    int  command = -1;
	char str_label[5] = {};
	int  label = 0;

	int exit = 0;
	char str_input[MAX_LINE] = {};
	int  input = -1;
	double push = 0;
	double mov = 0;

	while (1)
	{
		command = 0;
		if (exit) break;
		fscanf (my_program, "%s", str_command);
		
		if (str_command[0] != ':')
		{
			DEF_CMD (str_command);

			switch (command)
			{
				CHOOSE_CMD_ASM;

				case CMD_PUSH:
					if (fscanf (my_program, "%lg", &push))
					{
						add_code (codes, &cur_code, command);
						add_code (codes, &cur_code, push);
					}

					else
					{
						add_code (codes, &cur_code, CMD_PUSH_RX);
						fscanf (my_program, "%s", str_input);
						DEF_INPUT_REG (str_input);
						switch (input)
						{   
							CASE_REG_ASM (AX);			
							CASE_REG_ASM (BX);			
							CASE_REG_ASM (CX);			
							CASE_REG_ASM (DX);							
						}
					}
					break;

				case CMD_POP:
					add_code (codes, &cur_code, command);
					fscanf (my_program, "%s", str_input);
					DEF_INPUT_REG (str_input);
					switch (input)
					{
						CASE_REG_ASM (AX);			
						CASE_REG_ASM (BX);			
						CASE_REG_ASM (CX);			
						CASE_REG_ASM (DX);		
					}
					break;

				case CMD_IN:
					fscanf (my_program, "%s", str_input);
					if (strcmp (strupr (str_input), "ST") == 0) add_code (codes, &cur_code, command);
					else
					{
						add_code (codes, &cur_code, CMD_IN_RX);
						DEF_INPUT_REG (str_input);
						switch (input)
						{
							CASE_REG_ASM (AX);			
							CASE_REG_ASM (BX);			
							CASE_REG_ASM (CX);			
							CASE_REG_ASM (DX);
						}
					}
					break;

				case CMD_OUT:
					fscanf (my_program, "%s", str_input);
					if (strcmp (strupr (str_input), "ST") == 0) add_code (codes, &cur_code, command);
					else
					{
						add_code (codes, &cur_code, CMD_OUT_RX);
						DEF_INPUT_REG (str_input);
						switch (input)
						{
							CASE_REG_ASM (AX);			
							CASE_REG_ASM (BX);			
							CASE_REG_ASM (CX);			
							CASE_REG_ASM (DX);
						}
					}
					break;

				case CMD_MOV:
					fscanf (my_program, "%s", str_input);
					DEF_INPUT_REG (str_input);
					if (fscanf (my_program, "%lg", &mov))
					{
						add_code (codes, &cur_code, command);
						add_code (codes, &cur_code, input);
						add_code (codes, &cur_code, mov);
					}
					else
					{
						add_code (codes, &cur_code, CMD_MOV_RX);
						add_code (codes, &cur_code, input);
						fscanf (my_program, "%s", str_input);
						DEF_INPUT_REG (str_input);
						add_code (codes, &cur_code, input);
					}
					break;

				case CMD_END:
					add_code (codes, &cur_code, command);
					exit = 1;
					break;

				case CMD_CALL:
					add_code (codes, &cur_code, command);
					fscanf (my_program, "%s", str_label);
					sscanf (&(str_label[1]),"%d", &label);
					add_code (codes, &cur_code, labels[label]);
					break;

				case CMD_FUNC:
					fscanf (my_program, "%s", str_label);
					sscanf (&(str_label[1]),"%d", &label);
					labels[label] = cur_code;					
					break;

				CASE_LABEL (JMP);
				CASE_LABEL (JB);
				CASE_LABEL (JBE);
				CASE_LABEL (JE);
				CASE_LABEL (JAE);
				CASE_LABEL (JA);
				CASE_LABEL (JUE);

				default:
					fprintf (my_log, "\n" "ASSEMBLER ERROR\nYour command doesn't exist: "
									 "current command = [%d], your command = [%s]"
									 "\n", cur_code, str_command);
					break;
			}
		}

		else
		{
			sscanf (&(str_command[1]), "%d", &label);
			labels[label] = cur_code;
		}
	}

//OUT printf ("\n%d", cur_code);
asm_print (codes, cur_code, binary);

return HAPPY;
}

int add_code (double codes[], int* cur_code, double code)
{
	ASSERT (0 <= *cur_code && *cur_code < COMMANDS_SIZE);
	codes[*cur_code] = code;
	//OUT printf ("\n%lg", code);
	++*cur_code;
return HAPPY;
}

int asm_print (double codes[], int nCodes, FILE* binary)
{
	int cur = 0, j = 0;

	for (cur = 0; cur < nCodes; ++cur)
	{
		int cmd = int (codes[cur]);
		switch (cmd)
		{
			case CMD_MOV: case CMD_MOV_RX:
				for (j = 0; j <= 2; ++j)
				{
					fprintf (binary, "%lg ", codes[cur]);
					++cur;
				}
				--cur;
				fprintf (binary, "\n");
				break;

			case CMD_OUT: case CMD_OUT_RX: case CMD_POP:  case CMD_PUSH: case CMD_PUSH_RX:
			case CMD_JMP: case CMD_JB:	   case CMD_JBE:  case CMD_JE:   case CMD_JAE: 
			case CMD_JA:  case CMD_JUE:    case CMD_CALL: case CMD_IN:   case CMD_IN_RX:
				for (j = 0; j <= 1; ++j)
				{
					fprintf (binary, "%lg ", codes[cur]);
					++cur;
				}
				--cur;
				fprintf (binary, "\n");
				break;

			default:
				fprintf (binary, "%lg\n", codes[cur]);
				break;
		}
	}

return HAPPY;
}
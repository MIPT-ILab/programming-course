//{==================================================================================================
//! @file "assembler.h"
//! @date 2013-11-09
//! @mainpage CPU assembler functions
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#include <stdlib.h>
#include <string.h>
//----------------------------------------------------------------------------------------------------
#include "../../debug_defines.h"
#include "../cpu_consts.h"
//****************************************************************************************************

//****************************************************************************************************
#define ASSEMBLE_ITERATIONS 2
//****************************************************************************************************

short int assemble_file (FILE *input_file, double *memory_for_assembled_code, int *memory_for_goto_labels, unsigned int *out_used_memory_size)
{
    OUT ("\n"
         "# called assemble_file\n");

    RETURN_ASSERT (memory_for_assembled_code != NULL, -1);
    RETURN_ASSERT (memory_for_goto_labels != NULL, -1);
    RETURN_ASSERT (out_used_memory_size != NULL, -1);

    RETURN_ASSERT (input_file != NULL, -1);
    rewind (input_file);
    RETURN_ASSERT (input_file != NULL, -1);

    *out_used_memory_size = 0;

    enum SWITCH_MASHINE_STAT
    {
        SEARCH_ASM_COMMAND		= 0,
        SEARCH_DOUBLE_PARAM 	= 1,
        SEARCH_REGISTER_NAME 	= 2
    };

    char *buffer = (char*)calloc (5, sizeof(char));
    RETURN_ASSERT (buffer != NULL, -1);

    short int   switch_key = SEARCH_ASM_COMMAND,
                need_link_addr = 0,
                wrong_code = 0,
                fscan_result = 0;

	#define BUG_END( message )                      \
        free (memory_for_assembled_code);           \
        free (memory_for_goto_labels);				\
        free (buffer);                              \
        memory_for_assembled_code = NULL;			\
        memory_for_goto_labels = NULL;              \
        buffer = NULL;                              \
        RETURN_ASSERT (message == 0, -1);

    fscan_result = fscanf (input_file, "%s", buffer);

    while (fscan_result  != EOF)
    {
        switch (switch_key)
        {
			case SEARCH_ASM_COMMAND:
			{
				OUT ("# analyse asm command, buffer = %s\n", buffer);
				need_link_addr = 0;

				if (buffer[0] == ':')
				{
					int label_number = (int)atoi (buffer + 1);
					OUT ("# finded label %d, new value %d\n", label_number, *out_used_memory_size);
					if (label_number < 0 || label_number >= LABEL_MEMORY_MAX_SIZE)
					{
                        fprintf (OUT_DEVICE, "(%d) Invalid  goto %d\n",
							 *out_used_memory_size, label_number);
                        wrong_code = 1;
                    }
					memory_for_goto_labels[label_number] = *out_used_memory_size;
					break;
				}

				#define IF_CMP( asm_command, internal_command )				    				    \
				if (strcmp (buffer, asm_command) == 0)										 	    \
				{																		        	\
						OUT ("# finded command %s\n", buffer);										\
						memory_for_assembled_code[(*out_used_memory_size)++] = internal_command;	\
						break;																  		\
				}

				IF_CMP ("end", CPU_CMD_HALT);
				IF_CMP ("dub", CPU_CMD_DUB);
				IF_CMP ("sum", CPU_CMD_SUM);
				IF_CMP ("sub", CPU_CMD_SUB);
				IF_CMP ("mul", CPU_CMD_MUL);
				IF_CMP ("div", CPU_CMD_DIV);
				IF_CMP ("sin", CPU_CMD_SIN);
				IF_CMP ("cos", CPU_CMD_COS);
				IF_CMP ("tan", CPU_CMD_TAN);
				IF_CMP ("asin", CPU_CMD_ASIN);
				IF_CMP ("acos", CPU_CMD_ACOS);
				IF_CMP ("atan", CPU_CMD_ATAN);
				IF_CMP ("log", CPU_CMD_LOG);
				IF_CMP ("sqrt", CPU_CMD_SQRT);
				IF_CMP ("in", CPU_CMD_IN);
				IF_CMP ("ret", CPU_CMD_RET);

				#undef IF_CMP

				#define IF_CMP_NEW_KEY( asm_command, internal_command, new_sw_key, value )  			\
				if (strcmp(buffer, asm_command) == 0)                                               	\
				{                                                                                   	\
						OUT ("# finded command %s\n", buffer);										    \
						memory_for_assembled_code[(*out_used_memory_size)++] = internal_command;    	\
						switch_key = new_sw_key;                                                   		\
						need_link_addr = value;                                             		    \
						break;                                                                     		\
				}

				IF_CMP_NEW_KEY ("push", CPU_CMD_PUSH_STACK, SEARCH_DOUBLE_PARAM, 0);
				IF_CMP_NEW_KEY ("pop", CPU_CMD_PUSH_REGISTER_FROM_STACK, SEARCH_REGISTER_NAME, 0);
				IF_CMP_NEW_KEY ("out", CPU_CMD_OUT_TEXT, SEARCH_DOUBLE_PARAM, 0);
				IF_CMP_NEW_KEY ("mov", CPU_CMD_PUSH_REGISTER, SEARCH_REGISTER_NAME, 0);

				IF_CMP_NEW_KEY ("jmp", CPU_CMD_JMP, SEARCH_DOUBLE_PARAM,1);
				IF_CMP_NEW_KEY ("je", CPU_CMD_JE, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("jne", CPU_CMD_JNE, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("ja", CPU_CMD_JA, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("jae", CPU_CMD_JAE, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("jb", CPU_CMD_JB, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("jbe", CPU_CMD_JBE, SEARCH_DOUBLE_PARAM, 1);
				IF_CMP_NEW_KEY ("call", CPU_CMD_CALL, SEARCH_DOUBLE_PARAM, 1);

				#undef IF_CMP_NEW_KEY

				fprintf (OUT_DEVICE, "(%d) Invalid assembler command %s\n", *out_used_memory_size, buffer);
				wrong_code = 1;
				break;
			}

			#define COMMAND_IS( command ) (memory_for_assembled_code[(*out_used_memory_size)-1] == command)

			case SEARCH_DOUBLE_PARAM:
			{
				OUT ("\n"
                     "# analyse search_double_param\n");

				double param_buffer = 0.0;
				int temp = fscanf (input_file, "%lg", &param_buffer);
				OUT ("# readed temp and param_buffer\n");

				if ((COMMAND_IS (CPU_CMD_PUSH_STACK)) && (temp != 1))
				{
					OUT ("# prev command is cpu_cmd_push_stack\n");
					memory_for_assembled_code[(*out_used_memory_size)-1] = CPU_CMD_PUSH_REGISTER_TO_STACK;
					OUT ("#  it looks like cpu_cmd_push_register_to_stack\n");
					switch_key = SEARCH_REGISTER_NAME;
					break;
				}

				if ((COMMAND_IS (CPU_CMD_OUT_TEXT)) && (temp != 1))
				{
					OUT ("# command is cpu_cmd_out_text\n");
					memory_for_assembled_code[(*out_used_memory_size)-1] = CPU_CMD_OUT_VALUE_FROM_STACK;
					OUT ("#  it looks like cpu_cmd_out_value_from_stack\n");
					switch_key = SEARCH_ASM_COMMAND;
					break;
				}

				if (temp == 1)
				{
					OUT ("#  find double parameter for prev command param_buffer %d\n", (int)param_buffer);
					if (need_link_addr == 1)
					{
						OUT ("# need link!\n");
						param_buffer = memory_for_goto_labels[(int)param_buffer];

					}
					need_link_addr = 0;
					memory_for_assembled_code[(*out_used_memory_size)++] = param_buffer;
					switch_key = SEARCH_ASM_COMMAND;
					break;
				}

				fprintf (OUT_DEVICE, "(%d) Invalid double parameter (readed %s) %lg for %s\n", *out_used_memory_size, (temp==1) ? "OK" : "BAD",  param_buffer, buffer);
				wrong_code = 1;
				break;
			}

			case SEARCH_REGISTER_NAME:
			{
				int temp = fscanf (input_file, "%s", buffer);

				if (temp == 1)
				{
					#define ON_CMP( R_NAME, INTERNAL_R_NAME, NEW_SW_KEY )                           \
					if (strcmp( R_NAME, buffer) == 0)                                               \
					{                                                                               \
						OUT ("# find register %s\n", buffer);										\
						memory_for_assembled_code[(*out_used_memory_size)++] = INTERNAL_R_NAME;     \
						switch_key = NEW_SW_KEY;                                                    \
						break;                                                                      \
					}

					if (COMMAND_IS (CPU_CMD_PUSH_REGISTER_TO_STACK) || COMMAND_IS (CPU_CMD_PUSH_REGISTER_FROM_STACK))
					{
						ON_CMP ("ax", AX, SEARCH_ASM_COMMAND)
						else ON_CMP ("bx", BX, SEARCH_ASM_COMMAND)
							else ON_CMP ("cx", CX, SEARCH_ASM_COMMAND)
								else ON_CMP ("dx", DX, SEARCH_ASM_COMMAND)
									else
									{
										fprintf (OUT_DEVICE, "(%d) Invalid register name %s (readed %s)\n",
												 *out_used_memory_size, buffer, (temp==1) ? "OK" : "BAD");
										wrong_code = 1;
										break;
									};
					}

					if (COMMAND_IS (CPU_CMD_PUSH_REGISTER))
					{
						ON_CMP ("ax", AX, SEARCH_DOUBLE_PARAM)
						else ON_CMP ("bx", BX, SEARCH_DOUBLE_PARAM)
							else ON_CMP ("cx", CX, SEARCH_DOUBLE_PARAM)
								else ON_CMP ("dx", CX, SEARCH_DOUBLE_PARAM)
									else
									{
										fprintf (OUT_DEVICE, "(%d) Invalid register name %s (readed %s)\n",
												 *out_used_memory_size, buffer, (temp==1) ? "OK" : "BAD");
										wrong_code = 1;
										break;
									};
					}
				} else
				{
					fprintf (OUT_DEVICE, "(%d) No register name for %s\n",
							 *out_used_memory_size, buffer);
					break;
				};
				#undef ON_CMP
			}

			default: BUG_END ("# invalid assembling end-mashine state\n");
        }
		#undef COMMAND_IS
		if (switch_key == SEARCH_ASM_COMMAND) fscan_result = fscanf (input_file, "%s", buffer);
    }
	#undef BUG_END

    free (buffer);
    OUT ("\n");
    return wrong_code;
}

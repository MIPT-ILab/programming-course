#include "cpu.h"
#include "command_codes.h"


#define CHECK_COMMAND(str, name) (strcmp(str, #name) == 0)? CMD_##name : 

#define CONVERT_REG_(word, reg) (strcmp(word, #reg) == 0)? STR_##reg:

#define CASE_COMMAND(cmd)																		\
		case (cmd):																				\
			CHECK_CUR_CODE_;																	\
			codes[cur_code++] = cmd;															\
		break;
#define INJURED_IF(cond, error_message)															\
	if (cond)																					\
	{																							\
		healthy = false;																		\
		fprintf(strerr, error_message);															\
		break;																					\
	}	
#define CHECK_CUR_CODE_																			\
if (cur_code == MAXCODES - 1)																	\
{																								\
	fprintf(strerr, "Maximum size of commands array reached. Assemblation terminated");			\
	free(codes);																				\
	return NULL;																				\
}


/**
		assemble					function builds the array of commands and their arguments reading and analysing the input file stream

		param[out]		strin		input file stream
		param[out]		strerr		error file stream
		param[out]		pts			the array of pointers

		return						pointer of commands double array if successfull, otherwise NULL
**/

double* assemble(FILE* strin, FILE* strerr, pointer* pts)
{
	VERIFY(strin  != NULL);
	VERIFY(strerr != NULL);

	double* codes = (double*) calloc(MAXCODES, sizeof(codes[0]));
	int cur_code = 0;


	const char MAXLINE = 50;
	char word[MAXLINE] = {};
	int c = 0;
	int cond = 0;
	int reg = 0;
	int is_value = 0;
	double push_value = 0;
	char push_word[MAXLINE] = {};
	char pop_word[MAXLINE] = {};
	char out_word[MAXLINE] = {};
	char mov_word1 [MAXLINE] = {};
	char mov_word2 [MAXLINE] = {};
	char in_word [MAXLINE] = {};
	double mov_value = 0;
	int mov_arg1 = 0;
	int mov_arg2 = 0;
	char jump_mark[MAXLINE] = {};
	int i = 0;

	bool healthy = true;
	bool is_mark = false;

	while (healthy)
	{
		cond = fscanf_s(strin, "%s", word, _countof(word));
		
		INJURED_IF((cond <= 0), "\nUnexpected end of input\n");
		
		if (strcmp(word, "func") == 0)
		{
			CHECK_CUR_CODE_;
			codes[cur_code++] = CMD_FUNC;
			cond = fscanf_s(strin,"%s", word, _countof(word));
			INJURED_IF((cond <= 0), "\nUnexpected end of input\n");
			if (word[0] != ':') 
			{
				fprintf(strerr, "\nWrong function naming\n");
				free(codes);
				return NULL;
			}
		}
		if (word[0] == ':')
		{
			
			bool found_name = false;
			if (strlen(word) > NAME_LEN) 
			{
				fprintf(strerr, "\nToo big mark [%s]", &(word[1]));
				free(codes);
				return NULL;
			}
			for (i = 0; i < NUM_OF_POINTERS; ++i)
				if (strcmp(pts[i].name, &(word[1])) == 0)
				{
					if ((pts[i].mark != POISON_MARK) && (pts[i].mark != cur_code))
					{
						fprintf(strerr, "\nMark [%s] has been used more than once", &(word[1]));
						free(codes);
						return NULL;
					}
					pts[i].mark = cur_code;
					found_name = true;
					break;
				}
			
			if (found_name == false)
			{
				i = 0;
				while ((pts[i].name[0] != 0)&&(i < NUM_OF_POINTERS)) i++;
				
				if (pts[i].name[0] != 0) 
				{
					fprintf(strerr, "\nMaximum quantity of marks reached\n");
					free(codes);
					return NULL;
				}

				strcpy(pts[i].name, &(word[1]));
				pts[i].mark = cur_code;
			}
			continue;
		}
		
		_strupr(word);
		c = CHECK_COMMAND(word, PUSH)
			CHECK_COMMAND(word, POP)
			CHECK_COMMAND(word, ADD)
			CHECK_COMMAND(word, SUB)
			CHECK_COMMAND(word, MUL)
			CHECK_COMMAND(word, DIV)
			CHECK_COMMAND(word, SIN)
			CHECK_COMMAND(word, COS)
			CHECK_COMMAND(word, TAN)
			CHECK_COMMAND(word, SQRT)
			CHECK_COMMAND(word, POW)
			CHECK_COMMAND(word, END)
			CHECK_COMMAND(word, DUMP)
			CHECK_COMMAND(word, ENTER)
			CHECK_COMMAND(word, TAB)
			CHECK_COMMAND(word, SPACE)
			CHECK_COMMAND(word, OUT)
			CHECK_COMMAND(word, MOV)
			CHECK_COMMAND(word, SWAP)
			CHECK_COMMAND(word, DUB)
			CHECK_COMMAND(word, JMP)
			CHECK_COMMAND(word, JBE)
			CHECK_COMMAND(word, JB)
			CHECK_COMMAND(word, JAE)
			CHECK_COMMAND(word, JA)
			CHECK_COMMAND(word, JE)
			CHECK_COMMAND(word, JNE)
			CHECK_COMMAND(word, FUNC)
			CHECK_COMMAND(word, CALL)
			CHECK_COMMAND(word, RET)
			CHECK_COMMAND(word, IN)
			CMD_NONE;


		if (c == CMD_NONE) 
		{
			fprintf(strerr,"\nBad instruction token [%s]", word);
			return NULL;
		}
		
		CHECK_CUR_CODE_;
		codes[cur_code++] = c;

		switch (c)
		{
		case CMD_PUSH:
			cond = fscanf_s(strin, "%s", push_word, _countof(push_word));
			INJURED_IF(cond == 0, "\nUnexpected end after PUSH\n");

			push_value = 0;
			is_value = sscanf(push_word, "%lg", &push_value);
			if (is_value)
			{
				CHECK_CUR_CODE_;
				codes[cur_code++] = STR_value;
				CHECK_CUR_CODE_;
				codes[cur_code++] = push_value;
			}
			else
			{
				_strlwr(push_word);
				reg =		CONVERT_REG_(push_word, ax)
							CONVERT_REG_(push_word, bx)
							CONVERT_REG_(push_word, cx)
							CONVERT_REG_(push_word, dx)
							STR_NON;
				INJURED_IF((reg == STR_NON), "\nBad argument after push\n");

				CHECK_CUR_CODE_;
				codes[cur_code++] = reg;
				CHECK_CUR_CODE_;
				codes[cur_code++] = 0;
			}
			break;
		case CMD_IN:

			cond = fscanf_s(strin, "%s", in_word, _countof(in_word));
			INJURED_IF(cond == 0, "\nUnexpected end after IN\n");

			_strlwr(pop_word);
			reg =			CONVERT_REG_(in_word, ax)
							CONVERT_REG_(in_word, bx)
							CONVERT_REG_(in_word, cx)
							CONVERT_REG_(in_word, dx)
							CONVERT_REG_(in_word, st)
							STR_NON;
			INJURED_IF((reg == STR_NON), "\nBad argument after IN\n");
			CHECK_CUR_CODE_;
			codes[cur_code++] = reg;
			break;

		case CMD_POP:
			
			cond = fscanf_s(strin, "%s", pop_word, _countof(pop_word));
			INJURED_IF(cond == 0, "\nUnexpected end after POP\n");

			_strlwr(pop_word);
			reg =			CONVERT_REG_(pop_word, ax)
							CONVERT_REG_(pop_word, bx)
							CONVERT_REG_(pop_word, cx)
							CONVERT_REG_(pop_word, dx)
							CONVERT_REG_(pop_word, out)
							STR_NON;
			INJURED_IF((reg == STR_NON), "\nBad argument after POP\n");
			CHECK_CUR_CODE_;
			codes[cur_code++] = reg;
			break;

		case CMD_OUT:
			
			cond = fscanf_s(strin, "%s", out_word, _countof(out_word));
			INJURED_IF(cond == 0, "\nUnexpected end after OUT\n");

			_strlwr(out_word);
			reg =			CONVERT_REG_(out_word, ax)
							CONVERT_REG_(out_word, bx)
							CONVERT_REG_(out_word, cx)
							CONVERT_REG_(out_word, dx)
							CONVERT_REG_(out_word, st)
							CONVERT_REG_(out_word, ch)
							STR_NON;
			INJURED_IF((reg == STR_NON), "\nBad first OUT argument\n"); 
			if (reg == STR_ch) 
			{
				int out_char = -1;
				cond = fscanf_s(strin, "%d", &out_char);
				INJURED_IF(cond == 0, "\nBad argument after OUT CH\n");
				CHECK_CUR_CODE_;
				codes[cur_code++] = reg;
				CHECK_CUR_CODE_;
				codes[cur_code++] = out_char;
			}
			else 
			{
				CHECK_CUR_CODE_;
				codes[cur_code++] = reg;
				CHECK_CUR_CODE_;
				codes[cur_code++] = -1;
			}
			break;

		case CMD_MOV:
			

			cond = fscanf_s(strin, "%s", mov_word1, _countof(mov_word1));
			INJURED_IF((cond == 0), "\nUnexpected end after MOV, can't find first argument\n");

			
			cond = fscanf_s(strin, "%s", mov_word2, _countof(mov_word2));
			
			INJURED_IF((cond == 0), "\nUnexpected end after MOV, can't find second argument\n");

			mov_arg1 =		CONVERT_REG_(mov_word1, ax)
							CONVERT_REG_(mov_word1, bx)
							CONVERT_REG_(mov_word1, cx)
							CONVERT_REG_(mov_word1, dx)
							STR_NON;
			INJURED_IF((mov_arg1 == STR_NON), "\nOUT: bad first argument\n");
			
			mov_value = -1;

			cond = sscanf(mov_word2, "%lg", &mov_value);
			if (cond != 0)	
				mov_arg2 = STR_value;
			else
				mov_arg2 =	CONVERT_REG_(mov_word2, ax)
							CONVERT_REG_(mov_word2, bx)
							CONVERT_REG_(mov_word2, cx)
							CONVERT_REG_(mov_word2, dx)
							STR_NON;
			
			INJURED_IF((mov_arg2 == STR_NON), "\nOUT: bad second argument\n");
			
			CHECK_CUR_CODE_;
			codes[cur_code++] = mov_arg1;
			CHECK_CUR_CODE_;
			codes[cur_code++] = mov_arg2;
			CHECK_CUR_CODE_;
			codes[cur_code++] = mov_value;
			
			break;
		
		case CMD_JMP:
		case CMD_JBE:
		case CMD_JB:
		case CMD_JAE:
		case CMD_JA:
		case CMD_JE:
		case CMD_JNE:
		case CMD_CALL:

			cond = fscanf_s(strin, "%s", jump_mark, _countof(jump_mark));																		
			
			INJURED_IF((cond <= 0), "\nUnexpected end of input\n");														
			INJURED_IF((jump_mark[0] != ':'), "\nWrong format of mark\n");
			
			is_mark = false;
			i = 0;
			while ((strcmp(pts[i].name, &(jump_mark[1])) != 0) && (i < NUM_OF_POINTERS)) i++;
			if (i != NUM_OF_POINTERS)
			{
				if (c == CMD_FUNC) cur_code--;
				CHECK_CUR_CODE_;
				codes[cur_code++] = pts[i].mark;
				break;
			}
			i = 0;
			while ((pts[i].name[0] != 0) && (i < NUM_OF_POINTERS)) i++;
			INJURED_IF((i == NUM_OF_POINTERS), "\nMaximum quantity of pointers reached\n");
			
			strcpy(pts[i].name, &(jump_mark[1]));
			if (c == CMD_FUNC) cur_code--;
			CHECK_CUR_CODE_;
			codes[cur_code++] = pts[i].mark;
			break;

		case CMD_END:
			CHECK_CUR_CODE_;
			codes[cur_code++] = CMD_END;
			return codes;
			break;
		default:
			//fprintf(strerr, "WRONG TOKEN [%s]\n", word);
			break;
		}
	}
	free(codes);
	return NULL;
}

#undef CONVERT_REG_
#undef CHECK_CUR_CODE_


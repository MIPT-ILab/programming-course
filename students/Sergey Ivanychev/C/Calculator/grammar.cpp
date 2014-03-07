#include "calc.h"

extern FILE* strerr;


/**
		get_g						starts interpretating input expression and checks, whether it was successful or not

		@param[out]		string		input expression
		@param[out]		res			where result is to be saved

		@return						GRAM_BAD	- if parcing completed unsuccessfully
									GRAM_OK
**/

/**
		@par			all functions are described with grammar!
**/

int get_g(const char* string, TYPE* res);

int get_e(char** pos, TYPE* out);

int get_t(char** pos, TYPE* out);

int get_p(char** pos, TYPE* out);

int get_n(char** pos, TYPE* out);

int get_f(char** pos, TYPE* out);

/**
		get_f_check_args					counts and verifys function's arguments

		@param[out]			check_args		copy of current pointer of analysing string
		@param[out]			count_args		where to save quantity of arguments

		@return								GRAM_INVAL_ARGS - if arguments are incorrect or injured
											GRAM_OK
**/
int get_f_check_args(char* check_args, int* count_args);

/**
		get_f_get_name						scans for name of function

		@param[out]			pos				string pointer
		@param[out]			name			where the name will be saved
		
		@return								GRAM_INVAL_FUNC_NAME	- too long function name
											GRAM_NO_BRACKET			- no bracket after function or invalid name
											GRAM_OK
**/
	
int get_f_get_name(char** pos, char* name);

/**
		get_f_get_args						scans brackets for arguments

		@param[out]			pos				string pointer
		@param				argc			quaintity of awaited arguments
		@param[out]			argv			contain arguments

		@return								GRAM_INVAL_ARGS			- argument hasn't been scanned properly. It's broken
											GRAM_ARGS_SCAN_ERROR	- there's no closing 
											GRAM_OK
**/

int get_f_get_args(char** pos, int argc, double* argv);


#define CALL(func) if ((ret = (func)) != GRAM_OK) return ret;



int get_g(const char* string, TYPE* out)
{
	VERIFY(string == NULL, GRAM_OK, "# ERROR: Argumented string pointer is NULL\n");
	
	char** pos = (char**) calloc(1, sizeof(char*));
	VERIFY(pos == NULL, GRAM_OK, "# ERROR: Calloc failed to establish memory for pos\n");
	
	(*pos) = (char*)string;
	
	TYPE res = 0;
	
	int ret = get_e(pos, &res);

	//VERIFY(**pos != '\0', GRAM_BAD, "# ERROR: incorrect end of expression\n" _ ((int)*pos - (int)string) / sizeof(char*));
	if (**pos != '\0') fprintf(strerr, "# ERROR: incorrect end of expression\n");

	if ((GRAM_OK < ret && ret < GRAM_BAD) || **pos != '\0') 
	{
		fprintf(strerr, "[%d] %s", ret, gram_msgs[ret - GRAM_OK]);
		fprintf(strerr, "%s\n", string);
		
		for (int i = 0; i < ((int)*pos - (int)string) / sizeof(char); ++i) putc(' ', strerr);
		
		putc('^' , strerr);
		putc('\n', strerr);
		
		return GRAM_BAD;
	}
	
	

	*out = res;
	return GRAM_OK;
}

int get_e(char** pos, TYPE* out)
{
	int ret = 0;
	TYPE res = 0;
	TYPE temp_res = 0;
	
	CALL(get_t(pos, &res));
	while (**pos == '+' || **pos == '-')
	{
		char last_op = **pos;
		(*pos)++;
		CALL(get_t(pos, &temp_res));
		
		switch(last_op)
		{
		case '+': res += temp_res; break;
		case '-': res -= temp_res; break;
		default: GRAM_UNEXP_SHT;
		}
	}
	*out = res;
	return GRAM_OK;
}

int get_t(char** pos, TYPE* out)
{
	int ret = 0;
	TYPE res = 0;
	TYPE temp_res = 0;
	
	CALL(get_p(pos, &res));
	while (**pos == '*' || **pos == '/')
	{
		char last_op = **pos;
		(*pos)++;
		CALL(get_p(pos, &temp_res));
		
		switch(last_op)
		{
		case '*':													res *= temp_res; break;
		case '/':	if (!(fabs((double)(temp_res)) > DBL_EPSILON)) return GRAM_DIV_BY_ZERO;
					res /= temp_res; 
					break;
		default:  GRAM_UNEXP_SHT;
		}
	}
	
	*out = res;
	return GRAM_OK;
}

int get_p(char** pos, TYPE* out)
{
	int ret = 0;
	TYPE res = 0;
	int sign = PLUS;
	
	while (**pos == '-' || **pos == '+')
	{
		switch (**pos)
		{
		case '+': sign *= PLUS;  break;
		case '-': sign *= MINUS; break;
		default: return GRAM_UNEXP_SHT;
		}
		(*pos)++;
	}

	if (isalpha(**pos)) {CALL(get_f(pos, &res))}
	else
	{
		if (**pos == '(')
		{
			(*pos)++;
			CALL(get_e(pos, &res));
			if (**pos != ')') return GRAM_CLOSE_BRAC_ERROR; 
			(*pos)++;
		
			*out = res;
			return GRAM_OK;
		}
		CALL(get_n(pos, &res));
	}
		*out = res * (TYPE) sign;
	return GRAM_OK;
}



int get_n(char** pos, TYPE* out)
{
	if (!('0' <= **pos && **pos <= '9')) return GRAM_N_ERROR;
	
	TYPE res = 0;

	while ('0' <= **pos && **pos <= '9') 
	{
		res = 10 * res + (**pos - '0');
		(*pos)++;
	}

	if (**pos != '.')
	{
		*out = res;
		return GRAM_OK;
	}
	else (*pos)++;
	
	int i = 0;
	while ('0' <= **pos && **pos <= '9') 
	{
		res += (double)(**pos - '0') * powf((double)10, -(double)(++i));
		(*pos)++;
	}
	*out = res;
	
	return GRAM_OK;
}


int get_f(char** pos, TYPE* out)
{
	char name[FUNC_MAXLEN] = {};
	int ret = 0;
	
	CALL(get_f_get_name(pos, name));

	int argc = 0;
	
	CALL(get_f_check_args(*pos, &argc));
	
	double argv[MAX_ARGS] = {};

	ret = get_f_get_args(pos, argc, argv);
	if (ret != GRAM_OK)
	{
		fprintf(strerr, "Invalid argument of function [%s], symbol [%c]\n", name, **pos);
		return GRAM_INVAL_ARGS;
	}

	int i = 0;
	for (i = 0; i < FUNC_NUM; ++i) 	if (strcmp(name, (math_funcs[i]).name) == 0)	break;

	if (i == FUNC_NUM) return GRAM_NO_SUCH_FUNC;
	
	if (argc != math_funcs[i].argc) return GRAM_INV_NUM_OF_ARGS;

	double res = 0;
	CALL(math_funcs[i].func(argv, &res));

	*out = (TYPE) res;

	return GRAM_OK;

}

int get_f_get_args(char** pos, int argc, double* argv)
{
	for (int i = 0; i < argc; ++i)
	{
		(*pos)++;
		TYPE res = 0;
		int ret = get_e(pos, &res);
		
		if (ret != GRAM_OK)						//checking errors
		{
			if (ret != GRAM_INVAL_ARGS) 	fprintf(strerr, "[%d] %s\n", ret, gram_msgs[ret - GRAM_OK]);
			return GRAM_INVAL_ARGS;
		}

		argv[i] = (double)res;
	}

	if (**pos != ')') return GRAM_ARGS_SCAN_ERROR;
	(*pos)++;
	return GRAM_OK;
}

int get_f_get_name(char** pos, char* name)
{
	int i = 0;
	while (isalpha(**pos) && i < FUNC_MAXLEN - 1)
	{
		name[i++] = **pos;
		(*pos)++;
	}
	if (isalpha(**pos))			return GRAM_INVAL_FUNC_NAME;
	if (isalpha(**pos != '('))	return GRAM_NO_BRACKET;
	name[i] = '\0';
	return GRAM_OK;
}

int get_f_check_args(char* check_args, int* count_args)
{
	check_args++; 
	if (*check_args == ')') 
	{
		*count_args = 0;
		return GRAM_OK;
	}
	*count_args = 1;
	int count_brackets = 0;
	while	(! (*check_args == '\0' || (*check_args == ')' && count_brackets == 0)))		//(*check_args != ')' && *check_args != '\0')
	{
		switch (*(check_args++))
		{
		case '(': count_brackets++; break;
		case ')': count_brackets--; break;
		case ',': if (count_brackets == 0) (*count_args)++; break;
		default: break;
		}

		//if (*check_args == ',') (*count_args)++;
	}
	if (*check_args == '\0') return GRAM_INVAL_ARGS;
	return GRAM_OK;
}
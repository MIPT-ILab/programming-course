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

#define CALL(func) if ((ret = (func)) != GRAM_OK) return ret;



int get_g(const char* string, TYPE* out)
{
	char** pos = (char**) calloc(1, sizeof(char*));
	(*pos) = (char*)string;
	
	TYPE res = 0;
	
	int ret = get_e(pos, &res);

	if (GRAM_OK < ret && ret < GRAM_BAD) 
	{
		fprintf(strerr, "%s", gram_msgs[ret - GRAM_OK]);
		return GRAM_BAD;
	}
	
	
	VERIFY(**pos != '\0', GRAM_BAD, "# G4 EXPRESSION ERROR: %d'th symbol is a kind of error!\n" _ ((int)*pos - (int)string) / sizeof(char*));
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
	*out = res * (TYPE) sign;
	return GRAM_OK;
}



int get_n(char** pos, TYPE* out)
{
	if (!('0' <= **pos && **pos <= '9')) return GRAM_N_ERROR;
	int ret = 0;
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
		res += (**pos - '0') * powf((double)10, -(++i));
		(*pos)++;
	}
	*out = res;
	
	return GRAM_OK;
}
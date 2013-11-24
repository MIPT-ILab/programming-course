#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#include <iostream>


const int MAXLEN	= 200;
const int PLUS		=   1;
const int MINUS		=  -1;

enum grammar_conditions
{
	GRAM_OK					= 1000,
	GRAM_N_ERROR			= 1001,
	GRAM_UNEXP_SHT			= 1002,
	GRAM_DIV_BY_ZERO		= 1003,
	GRAM_CLOSE_BRAC_ERROR	= 1004,
	GRAM_FUNC_INVAL_ARG1	= 1005,
	GRAM_FUNC_INVAL_ARG2	= 1006,
	GRAM_FUNC_INVAL_ARG3	= 1007,
	GRAM_ARGV_NULL			= 1008,
	GRAM_RES_NULL			= 1009,
	GRAM_INVAL_FUNC_NAME	= 1010,
	GRAM_INVAL_ARGS			= 1011,
	GRAM_ARGS_SCAN_ERROR	= 1012,
	GRAM_NO_SUCH_FUNC		= 1013,
	GRAM_INV_NUM_OF_ARGS	= 1014,
	GRAM_NO_BRACKET			= 1015,
	GRAM_BAD				= 1016,
	
};

const char* const gram_msgs[] = 
{
	"\n",
	"# ERROR: Number is not recognized!\n",
	"# ERROR: Unusal thing in switch\n",
	"# ERROR: Division by zero\n",
	"# ERROR: no closing bracket\n",
	"# ERROR: first argument is invalid\n",
	"# ERROR: second argument is invalid\n",
	"# ERROR: third argument is invalid\n",
	"# ERROR: argv pointer is null\n",
	"# ERROR: result pointer is null\n",
	"# ERROR: invalid function name\n",
	"# ERROR: scanning args error\n",
	"# ERROR: no such function\n",
	"# ERROR: Invalid number of arguments for this function\n",
	"# ERROR: No bracket after function\n"
	"# GRAM_BAD\n",
};

#define VERIFY(cond, err_code, msg)								\
if (cond)														\
{																\
	fprintf(strerr, "file %s, line %d\n", __FILE__, __LINE__);	\
	fprintf(strerr, msg);										\
																\
	return err_code;											\
}

#define PRECOND(cond, err_code, msg)							\
if (cond)														\
{																\
	fprintf(strerr, msg);										\
																\
	return err_code;											\
}

#define POSTCOND(cond, err_code, msg)			\
if (cond)										\
{												\
	fprintf(strerr, msg);						\
												\
	return err_code;							\
}

#define DEBUG

#ifdef DEBUG
	#define ASSERT(cond)																										\
	if (!(cond))																												\
			{																													\
				printf("Program %s died in battle on line %d with the mistake of (%s)", __FILE__, __LINE__, #cond);				\
				abort();																										\
			}
#else 
	#define ASSERT(cond) (cond)
#endif

typedef double TYPE;

#define _ ,


int get_g(const char* string, TYPE* res);

int get_e(char** pos, TYPE* out);

int get_t(char** pos, TYPE* out);

int get_p(char** pos, TYPE* out);

int get_n(char** pos, TYPE* out);

//-----------------------------------------------------------------------------------------------

int c_tan(const double* argv, double* res);

int c_ctan(const double* argv, double* res);

int c_sin(const double* argv, double* res);

int c_cos(const double* argv, double* res);

int c_ln(const double* argv, double* res);

int c_log(const double* argv, double* res);

int c_sqrt(const double* argv, double* res);

int c_asin(const double* argv, double* res);

int c_acos(const double* argv, double* res);

int c_atan(const double* argv, double* res);

int c_exp(const double* argv, double* res);

int c_pow(const double* argv, double* res);

int c_fac(const double* argv, double* res);


const char FUNC_MAXLEN = 10;

typedef int (*math_func)(const double* argv, double* res);

typedef struct func_def_s
{
	//int (*func)(const double* argv, double* res);
	math_func func;
	char name[FUNC_MAXLEN];
	char argc;
} func_def;


const func_def math_funcs[] =
{
	/*
{c_tan	,"tg"		, 1},
{c_ctan	,"ctg"		, 1},
{c_sin	,"sin"		, 1},
{c_cos	,"cos"		, 1},
{c_ln	,"ln"		, 1},
{c_log	,"log"		, 2},
{c_sqrt	,"sqrt"		, 1},
{c_asin	,"arcsin"	, 1},
{c_acos	,"arccos"	, 1},
{c_atan	,"arctg"	, 1},
{c_exp	,"exp"		, 1},
{c_pow	,"pow"		, 2},
{c_fac	,"fac"		, 1},
*/

#define _S(func, name, argc) {func, name, argc},	
#define _NUM(num)
//#include "functions.h"
_S(c_tan	,"tg"		, 1)
_S(c_ctan	,"ctg"		, 1)
_S(c_sin	,"sin"		, 1)
_S(c_cos	,"cos"		, 1)
_S(c_ln		,"ln"		, 1)
_S(c_log	,"log"		, 2)
_S(c_sqrt	,"sqrt"		, 1)
_S(c_asin	,"arcsin"	, 1)
_S(c_acos	,"arccos"	, 1)
_S(c_atan	,"arctg"	, 1)
_S(c_exp	,"exp"		, 1)
_S(c_pow	,"pow"		, 2)
_S(c_fac	,"fac"		, 1)
#undef _S
#undef _NUM

};

const int MAX_ARGS = 4;
const int FUNC_NUM =
#define _S(func, name, argc)
#define _NUM(num) num;
#include "functions.h"
#undef _S
#undef _NUM




/*
const math_func* arr =
{
#define _S(func, name, argc) func
#include "functions.h"
#undef _S
};

const char* func_names =
{
#define _S(func, name, argc) name
#include "functions.h"
#undef _S
}

*/
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
	GRAM_BAD				= 1005,
};

const char* const gram_msgs[] = 
{
	"",
	"# ERROR: Number is not recognized!\n",
	"# ERROR: Unusal thing in switch\n",
	"# ERROR: Division by zero\n",
	"# ERROR: no closing bracket\n",
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

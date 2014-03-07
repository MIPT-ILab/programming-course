
/**
			@file						main.cpp
			@author						Sergey Ivanychev, group 376, DCAM MIPT
			@mainpage

			@version					V 1.1

			@par						This is calculator that uses the idea of recursive descent parser.
										It supports any expressions with brackets, real (positive and negative) numbers, spaces
			
			@par						Changelog V1.1
										- Added functions support. All functions are described in functions.h and in the first print.
										  In functions.c you may find basic information and links between syntax and used C function.

			@par						Grammar
										
										G ::= E \0
										E ::= T {[+-] T}*
										T ::= P {[*\] P}*
										P ::= [+-]* {N | (E) | F}
										F ::= [a-zA-Z]+ (E+)
										N ::= [0-9]+ {.[0-9]* | nul} 

**/

#include "calc.h"

#define FILE_CLOSE(str)						\
	if (str##_opened)						\
	{										\
		str##_opened = false;				\
		fclose(str);						\
		str = NULL;							\
	}

#define FILED_VERIFY(cond, ret_val, msg)	\
	if (cond)								\
	{										\
		assert(strerr);						\
		fprintf(strerr, msg);				\
											\
		FILE_CLOSE(strerr)					\
		FILE_CLOSE(strin);					\
		FILE_CLOSE(strout);					\
		return ret_val;						\
	}										

FILE* strerr = NULL;								//!< error stream

/**
			main					rules io and prints result

			@param		argc
			@param[out]	argv

			@return					1, if there was mistake, otherwise 0
**/

int main(int argc, char* argv[])
{
	//_wsetlocale (LC_ALL, L"Russian_Russia.ACP");
	//SetConsoleCP (1251);
	//SetConsoleOutputCP (1251);
	
	strerr = stdout;			//fopen("log.txt", "w");
	assert(strerr != NULL);

	bool strerr_opened	= true;
	bool strin_opened	= false;
	bool strout_opened	= false;
	FILE* strin  = NULL;
	FILE* strout = NULL;

#define _S(func, name, argc)			\
			name						\
			"\n"
#define _NUM(num)

	printf(	"# Program %s\n\n# Compiled %s\n# %s\n\n# Developedby Ivanychev Sergey\n# V 1.0"
			"# Hi, this is calculator which solve one-line expressions\n"
			"# I'm able to deal with real numbers with leading signs, spaces and brackets\n"
			"\n#Example -(-3 + 6) + 5 * (65 / 11)\n"
			"# You'll see: 32.5455\n"
			"# Don't forget to use '.' and NOT ','\n"
			"\n# Supported functions:"

			#include "functions.h"

			"\n# Enjoy\n\n", __FILE__, __DATE__, __TIME__);
#undef _S
#undef _NUM

	strin = stdin; //fopen("input.txt", "r");
	FILED_VERIFY(strin == NULL, 1, "# MAIN ERROR: input stream hasn't been opened for input\n");

	strout = stdout;  //fopen("output.txt", "w");
	FILED_VERIFY(strout == NULL, 1, "# MAIN ERROR: output stream hasn't been opened for input\n");
	
	char input[MAXLEN] = {};
	int c = 0;
	int i = 0;

	while ((c = getc(strin)) != '\0' && c != EOF && c != '\n') if (!(isspace(c))) input[i++] = (char)c;
	input[i] = '\0';

	TYPE res = 0;

	int ret = get_g(input, &res);
	if (ret != GRAM_OK) fprintf(strout, "Expression is not valid\n");
	else fprintf(strout, "%lg\n", res);

	FILE_CLOSE(strin);
	FILE_CLOSE(strout);
	FILE_CLOSE(strerr);

	return 0;
}
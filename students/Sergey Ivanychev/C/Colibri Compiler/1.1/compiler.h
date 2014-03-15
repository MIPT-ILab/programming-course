//			compiler.h, version 0.1

#ifndef CRT_SECURE_NO_WARNINGS
#define CRT_SECURE_NO_WARNINGS
#endif



#ifndef _TOKEN_GET_UNIT_
#define _TOKEN_GET_UNIT_ 

/*
				WARNING
	You are to remember that global "strlog" and "strerr" file stream must be defined
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>
#include <crtdbg.h>
#include <float.h>

#ifndef _CRTDBG_CHECK_ALWAYS_DF
#define _CRTDBG_CHECK_ALWAYS_DF
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TOKEN CONSTANTS AND DEFINITION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

enum token_types
{
	TKN_OP			= 2001,
	TKN_COMP		= 2002,
	TKN_ID			= 2003,
	TKN_NUM			= 2004,
	TKN_SEP			= 2005,
	TKN_ASSGN		= 2006,
	TKN_STR			= 2007,
	TKN_END			= 2008,
	TKN_KEY			= 2009,
};

enum assign_type
{
	ASSGN			= 20060,
	ASSGN_ADD		= 20061,
	ASSGN_SUB		= 20062,
	ASSGN_MUL		= 20063,
	ASSGN_DIV		= 20064,
};

enum operator_type
{
	OP_SUM			= '+',
	OP_SUB			= '-',
	OP_MUL			= '*',
	OP_DIV			= '/',
};

enum compare_type
{
	CMP_B			= 20020,
	CMP_A			= 20021,
	CMP_BE			= 20022,
	CMP_AE			= 20023,
	CMP_E			= 20024,
	CMP_NE			= 20025,
};

enum key_word_type				// if you change that thing, do not forget to change token_word_is_key() function
								// there's something to increase performance
{
	WORD_if			= 20090,
	WORD_else		= 20091,
	WORD_while		= 20092,
	WORD_do 		= 20093,
	WORD_until		= 20094,
	WORD_print		= 20095,
	WORD_print_val	= 20096,
};

enum token_condition
{
	TOKEN_OK		= 2101,
	TOKEN_BAD		= 2102,
};

typedef struct token_s
{
	int type;
	void* value;

} token;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								COMPILER CONSTANTS AND DEFINITION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

enum compiler_errors
{
	COMP_OK				,
	COMP_NULL_ARG		,
	COMP_NULL_CHILD		,
	COMP_BAD_TREE		,
	COMP_BAD_TYPE		,
	COMP_BAD_VALUE		,
	COMP_UNEXP_END		,
	COMP_OUT_OF_VARS	,
	COMP_TOO_LONG_VAR	,
	COMP_UNDEF_VAR		,
	COMP_BAD			,
};

const int MAX_VAR_NAME = 20;

const int MAXVARS  = 50;

const int SYS_LABEL_LEN	= 30;

typedef struct var_s
{
	char name[MAX_VAR_NAME];
} var;

const char* const cmd[] =
{
	"push "	,
	"pop "	,
	"add "	,
	"sub "	,
	"mul "	,
	"div "	,
	"sin "	,
	"cos "	,
	"tan "	,
	"sqrt "	,
	"pow "	,
	"end "	,
	"dump "	,
	"out "	,
	"mov "	,
	"swap "	,
	"dub "	,
	"jmp "	,
	"jbe "	,
	"jb "	,
	"jae "	,
	"ja "	,
	"je "	,
	"jne "	,
	"func "	,
	"call "	,
	"ret "	,
	"asin "	,
	"fac "	,
	"ln "	,
	"def "	,
	"in "
};

enum cmd_numerate
{
	PUSH,
	POP	,
	ADD	,
	SUB	,
	MUL	,
	DIV	,
	SIN	,
	COS	,
	TAN	,
	SQRT,
	POW	,
	END	,
	DUMP,
	OUT	,
	MOV	,
	SWAP,
	DUB	,
	JMP	,
	JBE	,
	JB	,
	JAE	,
	JA	,
	JE	,
	JNE	,
	FUNC,
	CALL,
	RET	,
	ASIN,
	FAC	,
	LN  ,
	DEF ,
	IN	,

};




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TREE CONSTANTS AND DEFINITION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


enum tree_errors
{
	TREE_OK					= 5000,
	TREE_ARG_TREE_NULL		= 5001,
	TREE_CALLOC_FAILED		= 5002,
	TREE_CHECK_BAD			= 5003,
	TREE_CHECK_OK			= 5004,
	TREE_CHECK_BAD_TYPE		= 5005,
	TREE_CHECK_BAD_LINK		= 5006,
	TREE_CHECK_OVERFLOW		= 5007,
	TREE_CHECK_STR_BROKEN	= 5008,
	TREE_CHECK_NO_HEAD		= 5009,
	TREE_CHECK_NO_ROOT		= 5010,
	TREE_INJURED			= 5011,
	TREE_ADD_INJURED		= 5012,
	TREE_ALREADY_THERE		= 5013,
	TREE_UNEXPECTED_TYPE	= 5014,
	TREE_ARG_STR_NULL		= 5015,
	TREE_PRINT_ELEM_FAILED	= 5016,
	TREE_INVALID_INPUT		= 5017,
	TREE_CTR_FAILED			= 5018,
	TREE_COPY_FAILED		= 5019,
	TREE_OPT_INVAL_ARG1		= 5020,
	TREE_OPT_INVAL_ARG2		= 5021,
	TREE_BAD				= 5020,
};

enum tree_conditions
{
	TREE_DESTR_ALL			= 5400,
	TREE_DESTR_HEAD			= 5401,
};


enum tree_types
{
	TR_V					= 5301,					//contain string
	TR_F					= 5302,					//contain string
	TR_STR					= 5303,					//contain string
	TR_N					= 5304,					//contain double value

	TR_PGM					= 5305,
	TR_B					= 5306,
	TR_OP					= 5307,
	TR_ASSN					= 5308,					//int
	TR_IF					= 5309,
	TR_WHILE				= 5310,
	TR_DO					= 5311,
	TR_PRINT				= 5312,
	TR_PRVAL				= 5313,				
	TR_E					= 5314,					//
	TR_T					= 5315,					// We don't need this
	TR_P					= 5316,					//
	TR_CMP					= 5317,					//int
	TR_SIGN					= 5318,					//int
	TR_NONE					= 5319,

};

const char* const tree_types_strings[] = 
{
	"Variable",
	"Function",
	"String",
	"Number",
	"Program",
	"Block",
	"Operator",
	"Assignment",
	"If",
	"While",
	"Do",
	"Print",
	"Print_val",
	"Expression",
	"Term",
	"Primary expr",
	"Comparisment",
	"Sign",
	"Empty"
};


typedef struct tree_s
{
	struct tree_s* left;
	struct tree_s* right;
	struct tree_s* papa;

	struct tree_head_s* head;
	int type;
	void* value;
} tree;

typedef struct tree_head_s
{
	struct tree_s* root;
	int size;
} tree_head;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								SYNTAX PARSER CONSTANTS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<





//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								GENERAL CONSTANTS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


const char* const nil		= "nil";
const int POISON	= -228;
const int MAXLINE = 100;
const int MAXTREE = 10000;
const int MAXTOKEN = 10000;

enum side
{
	LEFT  					= 100,
	RIGHT					= 101,
	NONE					= 102,
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								GENERAL ERROR CODES
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

enum compiler_main_errors
{
	CPLR_OK				=	3000,
	CPLR_TOKENIZE_FAULT	=	3001,
	CPLR_BAD			=	3002,

};


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								DEBUG MACROSES
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#define __LOG_TEMPLATE(place, cond, err_code, msg)					\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(strerr, "ERROR# ");										\
	fprintf(strerr, msg);											\
	fprintf(strerr, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(strlog, #place"_ERROR# ");								\
	fprintf(strlog, msg);											\
	fprintf(strlog, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
	return err_code;												\
}


#define VERIFY1(cond, err_code, msg, arg1)							\
if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(strerr, "VERIFY# ");									\
	fprintf(strerr, msg, arg1);										\
	fprintf(strerr, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
	fprintf(strlog, "VERIFY_ERROR# ");								\
	fprintf(strlog, msg, arg1);										\
	fprintf(strlog, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
																	\
	return err_code;												\
}
#define VERIFY2(cond, err_code, msg, arg1, arg2)					\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(strerr, "VERIFY# ");									\
	fprintf(strerr, msg, arg1, arg2);								\
	fprintf(strerr, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
	fprintf(strlog, "VERIFY_ERROR# ");								\
	fprintf(strlog, msg, arg1, arg2);								\
	fprintf(strlog, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
																	\
	return err_code;												\
}

#define VERIFY3(cond, err_code, msg, arg1, arg2, arg3)				\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(strerr, "VERIFY# ");									\
	fprintf(strerr, msg, arg1, arg2, arg3);							\
	fprintf(strerr, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
	fprintf(strlog, "VERIFY_ERROR# ");								\
	fprintf(strlog, msg, arg1, arg2, arg3);							\
	fprintf(strlog, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
																	\
	return err_code;												\
}


#define   VERIFY(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)
#define  PRECOND(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)
#define POSTCOND(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)


#define ERR(msg)													\
	fprintf(strerr, "ERROR# ");										\
	fprintf(strerr, msg);											\
	fprintf(strerr, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\
	fprintf(strlog, "PRECOND_ERROR# ");								\
	fprintf(strlog, msg);											\
	fprintf(strlog, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);		\

#define _ )


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TOKEN LIBRARY FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define D_OUT(thing) fprintf(strlog, "DEBUG# "); fprintf(strlog, thing); fputc('\n', strlog);
#define D_OUT1(thing, arg1) fprintf(strlog, "DEBUG# "); fprintf(strlog, thing, arg1); fputc('\n', strlog);
#define D_OUT2(thing, arg1, arg2) fprintf(strlog, "DEBUG# "); fprintf(strlog, thing, arg1 ,arg2); fputc('\n', strlog);
#define D_OUT3(thing, arg1, arg2, arg3) fprintf(strlog, "DEBUG# "); fprintf(strlog, thing, arg1, arg2, arg3); fputc('\n', strlog);
#define DBG_FREE
#else
#define D_OUT(thing)
#define D_OUT1(thing, arg1)
#define D_OUT2(thing, arg1, arg2) 
#define D_OUT3(thing, arg1, arg2, arg3) 
#define DBG_FREE if(0)


#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TOKEN LIBRARY FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int tokenize_stream(FILE* strin, token** token_stream, int* token_count);

int get_token(token* save_loc, FILE* strin);

int get_token_num(token* save_loc, FILE* strin);

int get_token_got_equal(token* save_loc, FILE* strin);

int print_token(token* my_token, FILE* strout);

int token_construct(token** my_token);

int token_destruct(token* my_token);

int token_word_is_key(char* string);

int token_word_is_valid(char* string);

int token_write(token* my_token, int type, const void* source);

int get_token_got_cmp(token* save_loc, FILE* strin, int c);




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TREE LIBRARY FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int tree_burn(tree* my_tree, int type, ...);

int tree_read_in_order(FILE* strin, tree* my_tree);

int head_ctr(tree_head** my_tree);

int tree_ctr(tree** my_tree, tree_head* my_head);

int tree_print_elem_value(FILE* strout, tree* my_tree, char* extra_space);

void tree_dump_in_order(FILE* strout, tree* my_tree, char* space);

int tree_dump(FILE* strout, tree_head* my_head);

//int tree_print_in_order(FILE* strout, tree* my_tree);

int tree_check(tree* my_tree, int* size);

int tree_add_left(tree* my_tree, tree* adding);

int tree_add_right(tree* my_tree, tree* adding);

//int tree_get_token(FILE* strin, tree* my_tree, int* type);

int head_destr(tree_head* my_head, int cond, ...);

int tree_destr(tree* my_tree);

int tree_delete(tree* my_tree, int side);

int tree_optimize(tree* my_tree, bool* is_optimised);

int tree_init(tree** dest_save_tree_token, tree_head* head_ptr, tree* tree_to_stick_to, char* func_name, int tree_type, int add_side);

void tree_save_string(tree* my_tree, char* word);

void tree_save_double(tree* my_tree, double value);

void tree_save_int(tree* my_tree, int value);

int tree_copy(tree* my_tree, tree_head** copied_tree);

void tree_save_head(tree* my_tree, tree_head* head);

int node_insert(tree* new_papa, tree** save_to, int side_papa, int side_child);

int tree_get_side(tree* my_tree, int* side);

//int tree_read_in_order(FILE* strin, tree* my_tree);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								PARSER FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int get_pgm(token* code, tree_head** syntax_tree);

int get_b(token** code, tree* my_tree);

int get_op(token** code, tree* my_tree);

int get_if(token** code, tree* my_tree);

int get_assnop(token** code, tree* my_tree);

int get_while(token** code, tree* my_tree);

int get_do(token** code, tree* my_tree);

int get_print(token** code, tree* my_tree);

int get_print_val(token** code, tree* my_tree);

int get_v(token** code, tree* my_tree, int side);

int get_f(token** code, tree* my_tree);

int get_e(token** code, tree* my_tree, int side);

int get_t(token** code, tree* my_tree, int side);

int get_p(token** code, tree* my_tree, int side);

int get_n(token** code, tree* my_tree);

int get_cmp(token** code, tree* my_tree);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								BUILDER FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int build_pgm(tree* my_tree, FILE* strout);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								DERIVATIVE FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int build_derivative(tree* my_tree, tree_head** derivative, char* var);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								TEX EXPORT FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int tex_build(FILE* tex_output, FILE* tex_template, tree* func, tree* opt_func, tree* der, tree* opt_der, char* var);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								PARSER CONSTANTS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


const char* const sntx_errors[] = 
{
	"Argumented code pointer is NULL",
	"Argumented tree pointer is NULL",
	"Tree construction failed",
	"Tree burning failed",
	"Tree is injured",
	"Unexpected end of code",
	"Failed to add tree node",
};

enum sntx_error_msgs
{
	TOK_NULL				,
	TR_NULL					,
	CTR_FAIL				,
	BURN_FAIL				,
	INJURED					,
	UNX_END					,
	ADD_FAIL				,
};

enum parser_errors
{
	SNTX_OK					= 4000,
	SNTX_ARG_NULL			= 4001,
	SNTX_BAD_HEAD			= 4002,
	SNTX_INVALID_TREE		= 4003,
	SNTX_BAD				= 4004,
	SNTX_CTR_FAILED			= 4005,
	SNTX_BURN_FAILED		= 4006,
	SNTX_UNEXP_END			= 4007,
	SNTX_ADD_FAILED			= 4008,
	SNTX_BAD_OP_TOKEN		= 4009,
	SNTX_BAD_OP_END			= 4010,
	SNTX_MISSED_END			= 4011,
	SNTX_DIV_BY_ZERO		= 4012,
	SNTX_INIT_FAIL			= 4013,
	SNTX_NO_END				= 4014,
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								MATH FUNCTIONS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


typedef int (*math_func)(const double* argv, double* res);

const int FUNC_MAXLEN = 10;
typedef struct func_def_s
{
	math_func func;
	char name[FUNC_MAXLEN];
	char argc;
} func_def;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								OPTIMIZING MATH FUNCTIONS DEFINITION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef FUNC_OPTIMIZE_DEFINED
#define FUNC_OPTIMIZE_DEFINED

#define _S(func, name, argc) int c##func(const double* argv, double* res);
#define _NUM(num)
#include "functions.h"
#undef _S

#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

const func_def math_funcs[] =									//Why red???
{

#define _S(func, name, argc) {c##func, name, argc},	
#define _NUM(num)
#include "functions.h"
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





#endif
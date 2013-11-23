#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

enum tree_errors
{
	TREE_OK					= 1400,
	TREE_ARG_TREE_NULL		= 1401,
	TREE_CALLOC_FAILED		= 1402,
	TREE_CHECK_BAD			,
	TREE_CHECK_OK			,
	TREE_INJURED			,
	TREE_ADD_INJURED		,
	TREE_ALREADY_THERE		,
	TREE_UNEXPECTED_TYPE	,
	TREE_ARG_STR_NULL		,
	TREE_PRINT_ELEM_FAILED	,
	TREE_INVALID_INPUT		,
	TREE_CTR_FAILED			,
	TREE_BAD				,
};

enum tree_conditions
{
	TREE_DESTR_ALL			= 2400,
	TREE_DESTR_HEAD			= 2401,
};


const char* const nil		= "nil";
const int POISON	= -228;

enum tree_value_types
{
	ADD		= '+',
	SUB		= '-',
	MUL		= '*',
	DIV		= '/',
	NUM		= '8',
	OP_BRAC = '(',
	CL_BRAC = ')',

};

#define VERIFY(cond, err_code, msg)				\
if (cond)										\
{												\
	fprintf(strerr, msg);						\
												\
	return err_code;							\
}

#define PRECOND(cond, err_code, msg)			\
if (cond)										\
{												\
	fprintf(strerr, msg);						\
												\
	return err_code;							\
}

#define POSTCOND(cond, err_code, msg)			\
if (cond)										\
{												\
	fprintf(strerr, msg);						\
												\
	return err_code;							\
}


#define _ ,

typedef struct tree_s
{
	struct tree_s* left;
	struct tree_s* right;
	struct tree_s* papa;
	char type;
	double value;
} tree;

typedef struct tree_head_s
{
	struct tree_s* root;
	int size;
} tree_head;

int tree_read_in_order(FILE* strin, tree* my_tree);

int head_ctr(tree_head** my_tree);

int tree_ctr(tree** my_tree);

int tree_print_elem_value(FILE* strout, tree* my_tree);

void tree_dump_in_order(FILE* strout, tree* my_tree);

int tree_print_in_order(FILE* strout, tree* my_tree);

int tree_check(tree* my_tree, int* size);

int tree_add_left(tree* my_tree, tree* adding);

int tree_add_right(tree* my_tree, tree* adding);

int tree_get_token(FILE* strin, tree* my_tree, int* type);

int head_destr(tree_head* my_head, int cond, ...);

int tree_destr(tree* my_tree);

int tree_read_in_order(FILE* strin, tree* my_tree);
/**
		@file				main.cpp
		@author				Sergey Ivanychev, 376 group, DCAM MIPT
		@mainpage

		@par				This is an example of using binary trees. The program reads full-bracket expression,
							interpretates it as a tree and prints it back, making a dump print. There're tree, 
							tree_head (aka head) and some functions, that were requested, are implemented.

		@verison			1.00
**/

#include "tree.h"


FILE* strerr = NULL;

/**
		main				Function rules io, creates tree and calls functions of tree

		@return
**/

#define FILED_VERIFY(cond, ret_val, msg)	\
	if (cond)								\
	{										\
		assert(strerr);						\
		fprintf(strerr, msg);				\
											\
		if (strerr_opened)					\
		{									\
			fclose(strerr);					\
			strerr = NULL;					\
		}									\
		if (strin_opened)					\
		{									\
			fclose(strin);					\
			strin = NULL;					\
		}									\
		if (strout_opened)					\
		{									\
			fclose(strout);					\
			strout = NULL;					\
		}									\
		return ret_val;						\
	}										


int main(int argc, char* argv[])
{
	strerr = fopen("log.txt", "w");
	assert(strerr);
	
	bool strerr_opened	= true;
	bool strin_opened	= false;
	bool strout_opened	= false;

	FILE* strin  = NULL;
	FILE* strout = NULL;					//for FILED_VERIFY possibility, see the macros

	strin = fopen("input.txt", "r");
	FILED_VERIFY(strin == NULL, 1, "# MAIN ERROR: strin hasn't been opened for input\n");

		

	strout = fopen("output.txt", "w");
	FILED_VERIFY(strout == NULL, 1, "# MAIN ERROR: strout hasn't been opened for output\n");

	tree_head* my_tree = NULL;

	int ret = head_ctr(&my_tree);
	FILED_VERIFY(ret == TREE_BAD, 0, "# MAIN ERROR: Tree hasn't been constructed\nTreminating...\n");

	ret = tree_read_in_order(strin, my_tree -> root);
	FILED_VERIFY(ret != TREE_OK, 0, "# MAIN ERROR: Tree hasn't been read properly\n");

	ret = tree_print_in_order(strout, my_tree -> root);
	FILED_VERIFY(ret != TREE_OK, 0, "# MAIN ERROR: Tree hasn't been printed properly\n");

	fputc('\n',strout);
	tree_dump_in_order(strout, my_tree -> root);
	

	ret = head_destr(my_tree, TREE_DESTR_ALL);
	FILED_VERIFY(ret != TREE_OK, 0, "# MAIN ERROR: Tree hasn't been destructed properly\n");

	fclose(strin);
	fclose(strout);
	strin = NULL;
	strout = NULL;

	return 0;
}
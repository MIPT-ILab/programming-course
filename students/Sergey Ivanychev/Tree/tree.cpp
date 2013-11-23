#include "tree.h"

extern FILE* strerr;


/**
		is_there_num							that function checks. whether there's a number in front. That function has been 
												created because of bug with '+' and fscanf.
		@param[out]			strin				input file stream

		@return									1 - if yes, 0 - if no

**/

int is_there_num(FILE* strin);

/**
		head_ctr								constructor of head structure of tree. Contain information of current tree and pointer
												to root element
		@param[out]			my_tree				pointer to the pointer of head_element

		@return									TREE_ARG_TREE_NULL - argumented tree pointer is NULL
												TREE_CALLOC_FAILED - calloc failed to establish memory
												TREE_CTR_FAILED	- tree construction failed
												TREE_OK
**/

int head_ctr(tree_head** my_tree);

/**
		tree_ctr								constructs tree element

		@param[out]			my_tree				pointer to pointer of tree

		@return									TREE_ARG_TREE_NULL - argumented tree pointer is NULL
												TREE_CALLOC_FAILED - calloc failed to establish memory
												TREE_OK

**/

int tree_ctr(tree** my_tree);

/**
		tree_print_elem_value					prints the value in output file print

		@param[out]			strout				output file stream
		@param[out]			my_tree				tree element

		@return									TREE_UNEXPECTED_TYPE - unknown type contained in tree element
												TREE_ARG_TREE_NULL - argumented tree pointer is NULL
												TREE_OK
**/

int tree_print_elem_value(FILE* strout, tree* my_tree);

/**
		tree_dump_in_order						creates dump print in argumented file stream

		@param[out]			strout				output file stream
		@param[out]			my_tree				tree

		@return									void
**/

void tree_dump_in_order(FILE* strout, tree* my_tree);

/**
		tree_print_in_order						prints the tree in output stream, interpretating it as bracket construction

		@param[out]			strout				output stream
		@param[out]			my_tree				printing tree

		@return									TREE_ARG_STR_NULL -	argumented stream is NULL
												TREE_PRINT_ELEM_FAILED - printing of some element failed
												TREE_OK
**/

int tree_print_in_order(FILE* strout, tree* my_tree);

/**
		tree_add_left							adds left tree element to current tree element

		@param[out]			my_tree				current tree element
		@param[out]			adding				adding tree (element)

		@return									TREE_OK
												TREE_INJURED - current tree is not OK
												TREE_ADD_INJURED - adding tree is not OK
												TREE_ALREADY_THERE - there's left element already
**/

int tree_add_left(tree* my_tree, tree* adding);

/**
		tree_add_right							adds right tree element to current tree element

		@param[out]			my_tree				current tree element
		@param[out]			adding				adding tree (element)

		@return									TREE_OK
												TREE_INJURED - current tree is not OK
												TREE_ADD_INJURED - adding tree is not OK
												TREE_ALREADY_THERE - there's right element already
**/

int tree_add_right(tree* my_tree, tree* adding);

/**
		tree_check								checks whether tree is valid or not

		@param[out]			my_tree				current tree
		@param[out]			size				pointer to the integer variable that will contain the size of tree

		@return[out]							TREE_CHECK_BAD
												TREE_CHECK_OK
**/

int tree_check(tree* my_tree, int* size);

/**
		tree_get_token							gets forward token from the stream and saves it to current element
												of tree, saving its type to *type

		@param[out]			strin				input file stream
		@param[out]			my_tree				current tree element
		@param[out]			type				pointer to the variable that will contain type of scanned token

		@return									TREE_BAD - token hasn't been recognized
												TREE_OK
**/

int tree_get_token(FILE* strin, tree* my_tree, int* type);

/**
		tree_read_in_order						scans argumented file stream for tree and interpretates it as a tree

		@param[out]			strin				input file stream
		@param[out]			my_tree				tree-to-save

		@return									TREE_INVALID_INPUT - invalid input
												TREE_ARG_TREE_NULL - argumented tree pointer is NULL
												TREE_ARG_STR_NULL -	argumented stream is NULL
												TREE_OK
**/

int tree_read_in_order(FILE* strin, tree* my_tree);

/**
		tree_destr								destroys tree

		@param[out]			my_tree				destroying tree

		@return									TREE_OK
												TREE_BAD
**/

int tree_destr(tree* my_tree);

/**
		head_destr								the action depend on argument. It can destroy only head saving root pointer
												or destroy the whole tree

		@param[out]			my_head				argumented head of tree
		@param				cond				key

		@return									TREE_OK
												TREE_BAD
**/

int head_destr(tree_head* my_head, int cond, ...);


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int is_there_num(FILE* strin)
{
	int c = 0;
	while (isspace(c = getc(strin)));
	if (isdigit(c))
	{
		ungetc(c, strin);
		return 1;
	}
	int cc = getc(strin);
	if (((c == '-') || (c == '+'))&&(isdigit(cc)))
	{
		ungetc(cc, strin);
		ungetc(c, strin);
		return 1;
	}
	ungetc(cc, strin);
	ungetc(c, strin);
	return 0;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int head_ctr(tree_head** my_tree)
{
	PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL, "# HEAD CTR ERROR: argumented head pointer is NULL\n");

	(*my_tree) = (tree_head*) calloc(1, sizeof(tree_head));
	VERIFY((*my_tree) == NULL, TREE_CALLOC_FAILED, "# HEAD CTR ERROR: Calloc failed to establish memory for head\n");
	(*my_tree) -> size = 1;
	
	int ret = tree_ctr(&((*my_tree) -> root));
	
	VERIFY(ret != TREE_OK, TREE_CTR_FAILED, "# HEAD CTR ERROR: TREE_CTR() failed to construct tree, error [%d]\n" _ ret);
	
	return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_ctr(tree** my_tree)
{
	PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL, "# TREE CTR ERROR: argumented tree pointer is NULL\n");
	*my_tree = (tree*) calloc(1, sizeof(tree));
	VERIFY(my_tree == NULL, TREE_CALLOC_FAILED, "# TREE CTR ERROR: Calloc failed to establish memory\n");
	(*my_tree) -> papa  = NULL;
	(*my_tree) -> left  = NULL;
	(*my_tree) -> right = NULL;
	(*my_tree) -> value = (double) POISON;
	(*my_tree) -> type = 0;

	return TREE_OK;

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_print_elem_value(FILE* strout, tree* my_tree)
{
	VERIFY(my_tree == NULL, TREE_ARG_TREE_NULL, "# PRINT TREE ELEMENT ERROR: Argumented tree pointer is NULL\n");
	switch (my_tree -> type)
	{
	case '8':
		fprintf(strout, "%lg ", my_tree -> value);
		break;
	case '+':
	case '-':
	case '*':
	case '/':
		fprintf(strout, "%c ", my_tree -> type);
		break;
	default:
		return TREE_UNEXPECTED_TYPE;
	}
	return TREE_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void tree_dump_in_order(FILE* strout, tree* my_tree)
{
	if (strout == NULL) strout = strerr;
	assert(strout != NULL);
	fprintf(strout, "( ");
	
	if (my_tree -> left == NULL) fprintf(strout, "%s ", nil);
	else tree_dump_in_order(strout, my_tree -> left);

	fputc('[', strout);
	fputc('"', strout);
	if (tree_print_elem_value(strout, my_tree) != TREE_OK)	fprintf(strout, "TYPE={%c}, VALUE={%lg}", my_tree -> type, my_tree -> value);
	fputc('"', strout);
	fputc(' ', strout);
	
	fprintf(strout, "|%08x", my_tree);

	fputc(']', strout);
	fputc(' ', strout);

	if (my_tree -> right == NULL) fprintf(strout, "%s ", nil);
	else tree_dump_in_order(strout, my_tree -> right);

	fprintf(strout, ") ");
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_print_in_order(FILE* strout, tree* my_tree)
{
	if (my_tree -> left  != NULL) VERIFY(my_tree -> left  -> papa != my_tree, TREE_ARG_STR_NULL  , "# TREE PRINT ERROR: [%08x] tree element is broken (left link)\n" _ my_tree);
	if (my_tree -> right != NULL) VERIFY(my_tree -> right -> papa != my_tree, TREE_ARG_STR_NULL  , "# TREE PRINT ERROR: [%08x] tree element is broken (right link)\n" _ my_tree);
	
	fprintf(strout, "( ");
	if (my_tree -> left == NULL) fprintf(strout, /*"%s "*/" ");
	else tree_print_in_order(strout, my_tree -> left);
	
	int ret = 0;
	if ((ret = tree_print_elem_value(strout, my_tree)) != TREE_OK) return TREE_PRINT_ELEM_FAILED;

	if (my_tree -> right == NULL) fprintf(strout, /*"%s "*/" ");
	else tree_print_in_order(strout, my_tree -> right);
	fprintf(strout, ") ");

	return TREE_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define RETURN_BAD_ {*size = 0; return TREE_CHECK_BAD;}

int tree_check(tree* my_tree, int* size) /*and function pointer, that checks value of tree, general*/
{
	if ((my_tree -> right != NULL)&&(my_tree -> right -> papa != my_tree)) RETURN_BAD_
	if ((my_tree -> left  != NULL)&&(my_tree -> left  -> papa != my_tree)) RETURN_BAD_

	int ret = 0;
	if (my_tree -> right != NULL) ret = tree_check(my_tree -> right, size);
	if (ret == TREE_CHECK_BAD) RETURN_BAD_
	if (my_tree -> left  != NULL) ret = tree_check(my_tree -> left , size);
	if (ret == TREE_CHECK_BAD) RETURN_BAD_
	
	if ((my_tree -> left != NULL)&&(my_tree -> left == my_tree -> right)) RETURN_BAD_
	if ((my_tree -> left != NULL)&&(my_tree -> left == my_tree -> papa )) RETURN_BAD_
	if ((my_tree -> papa != NULL)&&(my_tree -> papa == my_tree -> right)) RETURN_BAD_

	(*size)++;
	return ret;
}

#undef RETURN_BAD_


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_add_left(tree* my_tree, tree* adding)
{
	int tr_counter = 0;
	VERIFY(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED, "# ADD LEFT ERROR: [%08x] element, tree is broken\n");
	tr_counter = 0;
	VERIFY(tree_check(adding,  &tr_counter) == TREE_CHECK_BAD, TREE_ADD_INJURED,"# ADD LEFT ERROR: [%08] adding element, tree is broken\n");

	if (my_tree -> left != NULL) return TREE_ALREADY_THERE;
	my_tree -> left = adding;
	
	if (adding -> papa != NULL)
	{
		if (adding -> papa -> left  == adding) adding -> papa -> left  = NULL;
		if (adding -> papa -> right == adding) adding -> papa -> right = NULL;
	}
	adding -> papa = my_tree;
	return TREE_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_add_right(tree* my_tree, tree* adding)
{
	int tr_counter = 0;
	VERIFY(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED, "# ADD RIGHT ERROR: [%08x] element, tree is broken\n");
	tr_counter = 0;
	VERIFY(tree_check(adding,  &tr_counter) == TREE_CHECK_BAD, TREE_ADD_INJURED,"# ADD RIGHT ERROR: [%08] adding element, tree is broken\n");

	if (my_tree -> right != NULL) return TREE_ALREADY_THERE;
	my_tree -> right = adding;
	
	if (adding -> papa != NULL)
	{
		if (adding -> papa -> left  == adding) adding -> papa -> left  = NULL;
		if (adding -> papa -> right == adding) adding -> papa -> right = NULL;
	}
	adding -> papa = my_tree;
	return TREE_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int tree_get_token(FILE* strin, tree* my_tree, int* type)
{
	assert(strin   != NULL);
	assert(my_tree != NULL);

	if (is_there_num(strin) > 0)
	{
		double value = 0;
		fscanf(strin, " %lg", &value);
		my_tree -> type = NUM;
		my_tree -> value = value;
		*type = NUM;
		return TREE_OK;
	}
	else
	{
		int c = 0;
		fscanf(strin, " %c", &c);
		switch (c)
		{
		case ADD: 
		case SUB: 
		case MUL: 
		case DIV: 
			my_tree -> type = c;
			my_tree -> value = (double)POISON;
			*type = c;
			return TREE_OK;
		case OP_BRAC:
		case CL_BRAC:
			*type = c;
			ungetc(c, strin);
			return TREE_OK;
		default:
			fprintf(strerr, "TREE GET TOKE ERROR: wrong token [%c]\n" _ c);
			return TREE_BAD;
		}
	}
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#define BRAKETS_(which)																								\
	add_tree = NULL;																								\
	ret = tree_ctr(&add_tree);																						\
	VERIFY(ret != TREE_OK, TREE_CTR_FAILED, "# TREE WRITE IN ORD ERROR: Failed to construct tree element\n");		\
	assert(add_tree != NULL);																						\
	tree_add_##which(my_tree, add_tree);																			\
	ret = tree_read_in_order(strin, my_tree -> which);																\
	if (ret != TREE_OK) return ret;																							


int tree_read_in_order(FILE* strin, tree* my_tree)
{
	VERIFY(strin == NULL, TREE_ARG_STR_NULL, "# TREE READ ERROR: Argumented stream pointer is NULL\n");
	VERIFY(my_tree == NULL, TREE_ARG_TREE_NULL, "# TREE READ ERROR: Argumented tree pointer is NULL\n");
	int c = 0;
	
	fscanf(strin, " %c", &c);
	VERIFY(c != '(', TREE_INVALID_INPUT, "# TREE READ IN ORD ERROR: Invalid input!\n");
	

	int got_type = 0;
	int ret = tree_get_token(strin, my_tree, &got_type);
	VERIFY(ret != TREE_OK, TREE_INVALID_INPUT, "# TREE READ IN ORD ERROR: error happened while tree_get_token()\n");

	if (got_type == NUM)
	{
		my_tree -> left  = NULL;
		my_tree -> right = NULL;
		fscanf(strin, " %c", &c);
		VERIFY(c != ')', TREE_INVALID_INPUT, "# TREE READ IN ORD ERROR: Invalid input! Got [%c] after double\n" _ c);
		return TREE_OK;
	}
	VERIFY(got_type != OP_BRAC, TREE_INVALID_INPUT, "# TREE READ IN ORD ERROR: Invalid input! Got [%c] type after '('\n");

	tree* add_tree = NULL;
	BRAKETS_(left);

	ret = tree_get_token(strin, my_tree, &got_type);
	VERIFY(!( (got_type == ADD) || (got_type == SUB) || (got_type == MUL) || (got_type == DIV) ), TREE_INVALID_INPUT, "# TREE WRITE IN ORD ERROR: Invalid input! Got [%c] type after ')'\n");

	BRAKETS_(right);
	
	fscanf(strin, " %c", &c);
	VERIFY(c != ')', TREE_INVALID_INPUT, "# TREE WRITE IN ORD ERROR: Invalid input!\n");
	
	return TREE_OK;
}

#undef BRACKETS_


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_destr(tree* my_tree)
{
	assert(my_tree);
	int ret = 0;
	int temp_ret = TREE_OK;
	if ((my_tree -> left  != NULL)&&(my_tree -> left  -> papa != my_tree)) temp_ret = TREE_BAD;
	if ((my_tree -> right != NULL)&&(my_tree -> right -> papa != my_tree)) temp_ret = TREE_BAD;
	
	if (my_tree -> left  != NULL) temp_ret = tree_destr(my_tree -> left);
	if (temp_ret != TREE_OK) ret = temp_ret;
	if (my_tree -> right != NULL) temp_ret = tree_destr(my_tree -> right);
	if (temp_ret != TREE_OK) ret = temp_ret;

	my_tree -> left  = NULL;
	my_tree -> right = NULL;
	my_tree -> papa  = NULL;
	my_tree -> value = POISON;
	my_tree -> type  = 0;

	return temp_ret;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int head_destr(tree_head* my_head, int cond, ...)
{
	tree** ret_tree = NULL;
	if (cond == TREE_DESTR_HEAD)
	{
		va_list args;
		va_start(args, cond);
		ret_tree = va_arg(args, tree**);
	}
	tree* tree_head = my_head -> root;
	my_head -> root = NULL;
	my_head -> size = POISON;
	free(my_head);
	if (cond == TREE_DESTR_HEAD) 
	{
		*ret_tree = tree_head;
		return TREE_OK;
	}
	else
	{
		int ret = tree_destr(tree_head);
		return ret;
	}
}

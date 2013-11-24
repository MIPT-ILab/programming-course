#include "hash.h"
#include "errors.h"

extern FILE* strerr;

/**
			list_elem_construst					constructs list element

			@param[out]			my_elem			pointer of pointer of list element. That used to automaticly generate pointer and save it
			@param[out]			value			argumented string

			@return								ELEM_CONSTR_PTR_NULL			-	argumented pointer is NULL
												ELEM_CONSTR_CALLOC_FAILED		-	calloc failed to establish memory
												ELEM_CONSTR_VAL_OUT_OF_RANGE	-	value size is out of range
												ELEM_OK
**/
int list_elem_ctor(list_elem** my_elem, const char* value);

/**
			list_elem_destruct					destructs list element
			
			@param[out]			my_elem			argumented list element

			@return								ELEM_DEST_PTR_NULL				-	argumented element pointer is NULL
												ELEM_CONSTR_VAL_NULL			-	argumented value pointer is NULL
												ELEM_OK							-	OK
**/

int list_elem_destruct(list_elem* my_elem);

/**
			list_elem_delete					deletes list element, remembering it's element of LIST.
												It carefully saves links between list elements in list

			@param[out]			my_elem			argumented list element

			@return								ELEM_DEL_PTR_NULL				-	argumented element pointer is NULL
												ELEM_DEL_NEXT_BROKEN			-	next element injured
												ELEM_DEL_PREV_BROKEN			-	previous element injured
												ELEM_DEL_DESTR_FAILED			-	element destruction failed
												ELEM_OK							-	OK
**/


int list_elem_delete(list_elem* my_elem);

/**
			list_elem_check						veryfies argumented list element

			@param[out]			my_elem			argumented list element

			@return								ELEM_CHECK_PTR_NULL				-	argumented element pointer is NULL	
												ELEM_CHECK_OK					-	verification succeded

**/

int list_elem_check(list_elem* my_elem);

/**
			list_elem_interrupt_handler			prototype of function, which verifies inputted error codes 
												and prints error messages to log file

			@param[out]			my_elem			argumented list element
			@param				cond			argumented error code
				
			@return								LIST_ELEM_INTRPT_BAD			-	there were errors
												LIST_ELEM_INTRPT_OK				-	there weren't errors
**/

int list_elem_interrupt_handler(list_elem* my_elem, int cond);

/**
			list_elem_dump						creates dump print in standart error stream

			@param[out]			my_list			argumented list element

			@return								ELEM_OK							-	OK

**/


int list_elem_dump(list_elem* my_list);


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1



int list_elem_ctor(list_elem** my_elem, const char* value)
{
	OUT_DEB("# Starting construction of list elem...\n");
	if (my_elem == NULL) 
	{
			OUT_DEB("# ERROR: Argumented pointer is null\n");
			OUT_DEB("# \nTerminating...\n");
			return ELEM_CONSTR_PTR_NULL;
	}
	(*my_elem) = (list_elem*) calloc(1, sizeof(list_elem));
	if (*my_elem == NULL)
	{
		OUT_DEB("# ERROR: Calloc failed: returned pointer is null\n");
		OUT_DEB("# Terminating...\n\n");
		return ELEM_CONSTR_CALLOC_FAILED;
	}
	if (value == NULL)
	{
		OUT_DEB("# ERROR: Argumented value pointer is NULL");
		OUT_DEB("Terminating...\n\n");
		return ELEM_CONSTR_VAL_NULL;
	}
	if (strlen(value) > MAX_VALUE)
	{
		OUT_DEB("# ERROR: Argumented value size is bigger than maximal\n");
		OUT_DEB("# Terminating...\n\n");
		return ELEM_CONSTR_VAL_OUT_OF_RANGE;
	}
	(*my_elem) -> prev = NULL;
	(*my_elem) -> next = NULL;
	(*my_elem) -> occur = 1;
	strcpy((*my_elem) -> value, value);
	(*my_elem) -> occur = 0;
	OUT_DEB("# DONE\n\n");
	return ELEM_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_elem_destruct(list_elem* my_elem)
{
	OUT_DEB("# Starting list elem destructing...\n");
	if (my_elem == NULL)
	{
		OUT_DEB("# ERROR: Argumented pointer is null\n");
		OUT_DEB("# Terminating...\n\n");
		return ELEM_DEST_PTR_NULL;
	}
	my_elem -> prev = NULL;
	my_elem -> next = NULL;
	for (int i = 0; i < MAX_VALUE; ++i)	my_elem -> value[i] = 0;
	my_elem -> occur = POISON;
	free(my_elem);
	
	OUT_DEB("# DONE\n\n");
	return ELEM_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_elem_delete(list_elem* my_elem)
{
	OUT_DEB("# Deleting list elem...\n");
	int ret = 0;
	if (my_elem == NULL) 
	{
		OUT_DEB("# ERROR: Argumented pointer is null\nTerminating...\n");
		return ELEM_DEL_PTR_NULL;
	}
	OUT_DEB("# Searching for previous and next elements\n");
	
	if (my_elem -> next != NULL)
	{
		OUT_DEB("# Found next element. Checking...\n");
		if ((ret = list_elem_check(my_elem -> next)) != ELEM_CHECK_OK)
		{
			OUT_DEB("# CHECK FAILED\n");
			list_elem_interrupt_handler(my_elem, ret);
			return ELEM_DEL_NEXT_BROKEN;
		}
		OUT_DEB("# OK. Saving there PREVIOUS pointer...\n");
		my_elem -> next -> prev = my_elem -> prev;
	}
	else OUT_DEB("# Haven't found NEXT element\n");

	if (my_elem -> prev != NULL)
	{
		OUT_DEB("# Found previous element. Checking...\n");
		if ((ret = list_elem_check(my_elem -> prev)) != ELEM_CHECK_OK)
		{
			OUT_DEB("# CHECK FAILED\n");
			list_elem_interrupt_handler(my_elem, ret);
			return ELEM_DEL_PREV_BROKEN;
		}
		OUT_DEB("# OK. Saving there NEXT pointer...\n");
		my_elem -> prev -> next = my_elem -> next;
	}
	else OUT_DEB("# Haven't found PREVIOUS element\n");
	
	OUT_DEB("# Calling destruction of elem\n");
	ret = list_elem_destruct(my_elem);
	if (ret != ELEM_OK)
	{
		OUT_DEB("# ERROR: Destruction failed\n");
		list_elem_interrupt_handler(my_elem, ret);
		OUT_DEB("# Terminating...\n");
		return ELEM_DEL_DESTR_FAILED;
	}

	OUT_DEB("# OK\n");
	OUT_DEB("# DONE\n\n");

	return ELEM_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_elem_check(list_elem* my_elem)
{
	if (my_elem == NULL) return ELEM_CHECK_PTR_NULL;
	return ELEM_CHECK_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_elem_interrupt_handler(list_elem* my_elem, int cond)
{
	if ((cond < ELEM_OK)||(cond > ELEM_DEL_DESTR_FAILED))
	{
		fprintf(strerr, "UNKNOWN LIST ELEM ERROR\n");
		list_elem_dump(my_elem);
		return LIST_ELEM_INTRPT_BAD;
	}
	if ((cond == ELEM_OK)||(cond == ELEM_CHECK_OK)) return LIST_ELEM_INTRPT_OK;
	fprintf(stderr, list_elem_err_msgs[cond - ELEM_OK]);
	list_elem_dump(my_elem);
	return LIST_ELEM_INTRPT_BAD;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_elem_dump(list_elem* my_list)
{
	fprintf(stderr, "I'm list elemenent %s [%08x]\n, NEXT = [%08x], PREV = [%08x], occur = %d\n",
		(list_elem_check(my_list) == ELEM_CHECK_OK)? "OK" : "BAD", 
		(void*)my_list, 
		(void*)(my_list -> next), 
		(void*)(my_list -> prev), my_list -> occur);

	fprintf(stderr, "Value = [%s]\n", my_list -> value);
	return ELEM_OK;
}

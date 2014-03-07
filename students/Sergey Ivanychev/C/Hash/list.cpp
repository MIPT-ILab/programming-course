#include "hash.h"
#include "errors.h"

#define CHECK_LIST(my_list) if (list_interrupt_handler(my_list, list_check(my_list)) != LIST_INTRPT_OK) return LIST_BAD;

extern FILE* strerr;

/**
			list_interrupt_handler					checks inputted error code and prints error code to standart error stream

			@param[out]			my_list				argumented list pointer
			@param				cond				argumented error code

			@return									LIST_INTRPT_BAD				-	there were errors
													LIST_INTRPT_OK				-	there weren't errors
**/


int list_interrupt_handler(list* my_list, int cond);

/**
			list_ctor							constructs list

			@param[out]			my_list				argumented list
			
			@return									LIST_CONSTR_PTR_NULL		-	argumented pointer is NULL
													LIST_CONSTR_CALLOC_FAILED	-	calloc function failed to establish memory
													LIST_OK						-	OK
													
**/

int list_ctor(list** my_list);

/**
			list_check								verifies conditiuon of list

			@param[out]			my_list				argumented list

			@return									LIST_CHECK_PTR_NULL			-	invalid argumented pointer
													LIST_CHECK_LEN_BROKEN		-	invalid length of list
													LIST_CHECK_HEAD_NULL		-	head pointer is NULL while length != 0
													LIST_CHECK_TAIL_NULL		-	tail pointer is NULL while length != 0
													LIST_CHECK_REAL_SIZE_LOWER	-	size of list is lower than expected
													LIST_CHECK_REAL_SIZE_HIGHER	-	size of list is higher than expected
													LIST_CHECK_BROKEN_STRUCTURE	-	the structure of list is invalid
													LIST_CHECK_OK				-	verificated successfully

**/
int list_check(list* my_list);

/**
			list_destruct							function destructs list

			@param				my_list				argumented list

			@return									LIST_DESTR_INVALID_LIST		-	list check hasn't been successful
													LIST_DESTR_ELEM_DESTR_FAILED-	destruction of list element failed
													LIST_OK						-	OK
**/

int list_destruct(list* my_list);

/**
			list_add								adds new element with the value of VALUE to the enf of list

			@param[out]			my_list				argumented list
			@param[out]			value				saving value

			@return									LIST_ADD_PTR_NULL			-	argumented list pointer is NULL
													LIST_ADD_VALUE_PTR_NULL		-	argumented value pointer is NULL
													LIST_BAD					-	there were errors
													LIST_OK						-	OK

													
**/
int list_add(list* my_list, char* value);

/**
			list_dump								function makes dump print of list

			@param[out]			my_list				argumented list
			
			@return									LIST_OK						-	OK
**/


int list_dump(list* my_list);

/**
			list_delete								deletes the element of current list with different verifications

			@param[out]			my_list				argumented element
			@param[out]			my_elem				current list element

			@return									LIST_BAD					-	there were errors
													LIST_OK						-	OK
**/

int list_delete(list* my_list, list_elem* my_elem);

/**
			list_occur_change						changes OCCUR value by argumented number

			@param[out]			my_elem				argumented list element
			@param				delta				change

			@return									LIST_BAD					-	there were errors
													LIST_OK						-	OK
**/


int list_occur_change(list_elem* my_elem, int delta);

/**
			list_search_word						searches list element with equal string

			@param[out]			my_list				argumented list
			@param[out]			word				a searched-for word
			@param[out]			my_elem				pointer of where found pointer would pe saved

			@return									LIST_BAD					-	there were errors (list injured)
													LIST_SEARCH_NO_SUCH			-	haven't found such element
													LIST_SEARCH_FOUND			-	found and saved
**/


int list_search_word(list* my_list, char* word, list_elem** my_elem);

/**
			list_delete_word						deletes the element of list with such value of string

			@param[out]			my_list				argumented list
			@param[out]			word				argumented string

			@return									LIST_BAD					-	there were errors (list injured)
													LIST_DELWORD_NO_SUCH				
**/

int list_delete_word(list* my_list, char* word);

/**
			list_search_index						searches and saves the value of pointer with such index of list

			@param[out]			my_list				argumented list pointer
			@param[out]			found_elem			a save-to pointer

			@return									LIST_BAD					-	there were errors (list injured)
													LIST_SEARCH_NO_SUCH			-	haven't found element
													LIST_OK						-	have found, complete
**/

int list_search_index(list* my_list, list_elem** found_elem);


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_search_index(list* my_list, list_elem** found_elem, int index)
{
	OUT_DEB("### LIST SEARCH INDEX STARTED ###\n");
	CHECK_LIST(my_list);

	if (found_elem == NULL)
	{
		OUT_DEB("# LIST SEARCH INDEX ERROR: Argumented pointer of element is NULL");
		list_elem_interrupt_handler((*found_elem), LIST_ELEM_PTR_NULL);
		return LIST_BAD;
	}

	if ((0 < index) || (index >= my_list->len))
	{
		OUT_DEB("# LIST SEARCH EXCEPTION: Index is OUT_DEB of range of list indexes\n");
		(*found_elem) = NULL;
		return LIST_SEARCH_NO_SUCH;
	}
	*found_elem = my_list-> head;
	for (int i = 0; i < my_list->len; ++i) *found_elem = (*found_elem) -> next;
	
	OUT_DEB("# Found %d'th element of list [%08x]\n");
	OUT_DEB("### LIST SEARCH INDEX FINISHED\n");
	return LIST_OK;


}


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1





int list_interrupt_handler(list* my_list, int cond)
{
	if ((cond < LIST_OK)||(cond > LIST_CONSTR_CALLOC_FAILED))
	{
		fprintf(strerr, "LIST INTERRUPT HANDLER: UNKNOWN ERROR [%d]\n", cond);
		if (my_list != NULL) list_dump(my_list);
		return LIST_INTRPT_BAD;
	}
	if ((cond != LIST_OK)&&(cond != LIST_CHECK_OK))
	{
		fprintf(stderr, "%s\n", list_error_msgs[cond - LIST_OK]);
		if (my_list != NULL) list_dump(my_list);
		return LIST_INTRPT_BAD;
	}
	return LIST_INTRPT_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int list_ctor(list** my_list)
{
	OUT_DEB("### LIST CONSTRUCT BEGIN ###\n");
	OUT_DEB("# Constructing list...\n");
	PRECOND(my_list == NULL, LIST_CONSTR_PTR_NULL, "# LIST CONSTRUCT ERROR: Argumented pointer is NULL\n### LIST CONSTRUCT END ###\n");
	*my_list = (list*) calloc(1, sizeof(list));
	VERIFY(*my_list == NULL, LIST_CONSTR_CALLOC_FAILED, "# LIST CONSTRUCT ERROR: Calloc failed (returned NULL)\n### LIST CONSTRUCT END ###\n");

	(*my_list) -> head = NULL;
	(*my_list) -> tail = NULL;
	(*my_list) -> len = 0;
	list_dump(*my_list);
	OUT_DEB("# DONE\n");
	CHECK_LIST((*my_list));
	OUT_DEB("### LIST CONSTRUCT END ###\n");
	return LIST_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_check(list* my_list)
{
	if (my_list == NULL) return LIST_CHECK_PTR_NULL;
	if (my_list -> len < 0) return LIST_CHECK_LEN_BROKEN;
	if ((my_list -> head == NULL)&&(my_list -> len != 0)) return LIST_CHECK_HEAD_NULL;
	if ((my_list -> tail == NULL)&&(my_list -> len != 0)) return LIST_CHECK_TAIL_NULL;
	if ((my_list -> len == 0)&&(my_list -> head == NULL)&&(my_list -> tail == NULL)) return LIST_CHECK_OK;

	list_elem* temp = my_list -> head;
	
	for (int i = 0; i < my_list -> len - 1; ++i)
	{
		if (temp -> next == NULL) return LIST_CHECK_REAL_SIZE_LOWER;
		temp = temp -> next;
	}
	if (temp -> next != NULL) return LIST_CHECK_REAL_SIZE_HIGHER;
	if (temp != my_list -> tail) return LIST_CHECK_BROKEN_STRUCTURE;
	return LIST_CHECK_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_destruct(list* my_list)
{
	OUT_DEB("### LIST DESTRUCT BEGIN ###\n");
	OUT_DEB("Destructing list [%08x]...", my_list);

	int ret = list_check(my_list);
	if (ret != LIST_CHECK_OK)
	{
		OUT_DEB("# LIST DESTRUCT ERROR: List is broken");
		OUT_DEB("# Freeing list memory. Some segments hasn't set free\n");

		list_interrupt_handler(my_list, ret);
		free(my_list);

		OUT_DEB("### LIST DESTRUCT END ###\n");
		return LIST_DESTR_INVALID_LIST;
	}

	list_elem* current_elem = my_list -> head;
	list_elem* next_elem = NULL;

	OUT_DEB("There are %d elements in list", my_list -> len);

	for (int i = 0; i < my_list -> len; ++i)
	{
		next_elem = current_elem -> next;
		ret = list_elem_destruct(current_elem);

		OUT_DEB("# In %d'th element now", i);
		OUT_DEB("### LIST DESTRUCT END ###\n");

		VERIFY(ret != ELEM_OK, LIST_DESTR_ELEM_DESTR_FAILED, "DESTRUCT ERROR: Element hasn't been destructed (ERROR %d)\n### LIST DESTRUCT END ###\n" _ ret);

		OUT_DEB("# Destructed");
		current_elem = next_elem;

	}

	my_list -> head = NULL;
	my_list -> tail = NULL;
	my_list -> len = POISON;

	OUT_DEB("# DONE\n");
	OUT_DEB("### LIST DESTRUCT END ###\n");

	return LIST_OK;
}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_add(list* my_list, char* value)
{
	OUT_DEB("### LIST ADD BEGIN ###\n");
	OUT_DEB("# Adding new element to [%08x] list, value = [%s]...\n", my_list, value);

	int ret = list_check(my_list);

	OUT_DEB("# value = [%s], len = %d\n", value, my_list -> len);
	PRECOND(my_list == NULL, LIST_ADD_PTR_NULL, "# LIST ADD: Argumented pointer is NULL\n### LIST ADD END ###\n");
	PRECOND(value == NULL, LIST_ADD_VALUE_PTR_NULL, "# LIST ADD: Argumented pointer of value is NULL\n### LIST ADD END ###\n"); 
	
	list_elem* find_such = NULL;
	ret = list_search_word(my_list, value, &find_such);
	
	VERIFY(ret == LIST_BAD, LIST_BAD, "# CPU ADD WORD: SOMETHING BAD HAPPENED WHILE SEARCHING\nTerminating...\n### LIST ADD END ###\n");
	
	if (ret == LIST_SEARCH_FOUND)
	{
		ret = list_occur_change(find_such, 1);
		if ( ret != LIST_OK)
		{
			OUT_DEB("# Something bad happened while changing occur\n");
			list_interrupt_handler(my_list, ret);
			OUT_DEB("### LIST ADD END ###\n");

			return LIST_BAD;
		}
		OUT_DEB("# Such element found, occur increased by one\n");
		OUT_DEB("# DONE\n");
		CHECK_LIST(my_list);
		OUT_DEB("### LIST ADD END ###\n");

		return LIST_OK;
	}

	list_elem* added = NULL;
	ret = list_elem_ctor(&(added), value);
	if (ret != ELEM_OK)
		{
			OUT_DEB("# Construction failed");
			OUT_DEB("# Terminating...");
			OUT_DEB("### LIST ADD END ###\n");

			return LIST_ADD_CONSTR_FAILED;
		}
	OUT_DEB("Saving [%s] to the created element\n", value);
	if (my_list -> len == 0)
	{
		my_list -> head = added;
		my_list -> tail = my_list -> head;
		(my_list -> len)++;

		OUT_DEB("# DONE\n");
		CHECK_LIST(my_list);
		OUT_DEB("### LIST ADD END ###\n");

		return LIST_OK;
	}
	
	added -> prev = my_list -> tail;
	added -> next = NULL;

	my_list -> tail -> next = added;
	my_list -> tail = added;
	my_list -> len += 1;

	OUT_DEB("# DONE\n");
	CHECK_LIST(my_list);
	OUT_DEB("### LIST ADD END ###\n");

	return LIST_OK;
}


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int list_occur_change(list_elem* my_elem, int delta)
{
	OUT_DEB("### LIST OCCUR CHANGE BEGIN ###\n");
	if (my_elem == NULL)
	{
		OUT_DEB("LIST OCCUR CHANGE ERROR: Argumented element pointer is null");
		list_elem_interrupt_handler(my_elem, LIST_ELEM_PTR_NULL);
		return LIST_BAD;
	}
	OUT_DEB("Changing OCCUR of element [%08x] list by %d\n", my_elem, delta); 

	my_elem -> occur += delta;

	OUT_DEB("Ocur changed successfully: now it's %d\n", my_elem -> occur);
	OUT_DEB("### LIST OCCUR CHANGE END ###\n");

	return LIST_OK;	
}


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1


int list_dump(list* my_list)
{
	OUT_DEB("### LIST DUMP BEGIN ###\n");
	//fprintf(stderr, "I'm list [%08x], len = %d, %s\n", my_list, my_list -> len, (list_check(my_list) == LIST_CHECK_OK)? "OK": "BAD");
	int dump_quant = my_list -> len;
	
	if (list_interrupt_handler(my_list, list_check(my_list)) != LIST_CHECK_OK) dump_quant = DUMPED_ELEMENTS_IF_ERROR;
	
	list_elem* cur = my_list -> head;
	int cur_num = 0;
	while ((cur != NULL)&&(cur_num < dump_quant))
	{
		list_elem_dump(cur);
		cur = cur -> next;
		cur_num++;
	}

	CHECK_LIST(my_list);
	OUT_DEB("# DONE\n");
	OUT_DEB("### LIST DUMP END ###\n");

	return LIST_OK;

}

//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int list_delete_word(list* my_list, char* word)
{
	OUT_DEB("### LIST DELETE WORD BEGIN ###\n");
	OUT_DEB("# Deleting  element of list [%08x] with the value of [%s], len = %d\n", my_list, word, my_list -> len);
	
	int ret = list_check(my_list);
	if (ret != LIST_CHECK_OK)
	{
		OUT_DEB("# LIST DELETE WORD ERROR: list is not OK in the beginning [error: %d]", ret);
		ret = list_interrupt_handler(my_list, ret);
		return LIST_BAD;
	}

	if (my_list -> len == 0) 
	{
		OUT_DEB("List is empty, nothing to delete\nNo elements deleted\n");
		OUT_DEB("### LIST DELETE WORD END ###\n");
		
		return LIST_DELWORD_NO_SUCH;
	}

	list_elem* my_elem = NULL;
	ret = list_search_word(my_list, word, &my_elem);
	
	if (ret == LIST_BAD)
	{
		OUT_DEB("CPU DELETE WORD: SOMETHING BAD HAPPENED WHILE SEARCHIN\nTerminating...\n");
		OUT_DEB("### LIST DELETE WORD END ###\n");
		
		return LIST_BAD;
	}

	if (ret == LIST_SEARCH_NO_SUCH)
	{
		OUT_DEB("No element in list with the value of [%s]\n", word);
		OUT_DEB("### LIST DELETE WORD END ###\n");
		CHECK_LIST(my_list);
		
		return LIST_DELWORD_NO_SUCH;
	}

	ret = list_delete(my_list, my_elem);
	
	if (ret != LIST_OK)
	{
		OUT_DEB("Removing failed, error[%d]\n", ret);
		OUT_DEB("### LIST DELETE WORD END ###\n");
		
		list_interrupt_handler(my_list, ret);
		return LIST_BAD;
	}

	OUT_DEB("Successfully removed [%08x] element", my_elem);
	
	CHECK_LIST(my_list);
	
	OUT_DEB("DONE\n");
	OUT_DEB("### LIST DELETE WORD END ###\n");
	
	return LIST_OK;
	
}


//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1

int list_search_word(list* my_list, char* word, list_elem** my_elem)
{
	OUT_DEB("### LIST SEARCH BEGIN ###\n");
	OUT_DEB("# Searching for element of list [%08x] with the value of [%s], len = %d\n", my_list, word, my_list -> len);
	
	int ret = list_check(my_list);
	
	if (my_elem == NULL)
	{
		OUT_DEB("LIST SEARCH ERROR: Argumented pointer of element is NULL");
		list_elem_interrupt_handler((*my_elem), LIST_ELEM_PTR_NULL);
		return LIST_BAD;
	}
	
	if (ret != LIST_CHECK_OK)
	{
		OUT_DEB("# LIST SEARCH WORD ERROR: list is not OK in the beginning [error: %d]", ret);
		OUT_DEB("### LIST SEARCH END ###\n");
		
		ret = list_interrupt_handler(my_list, ret);
		return LIST_BAD;
	}

	if (my_list -> len == 0) 
	{
		OUT_DEB("# List is empty, nothing to search\nNo elements deleted\n");
		
		CHECK_LIST(my_list);
		
		OUT_DEB("### LIST SEARCH END ###\n");
		
		return LIST_SEARCH_NO_SUCH;
	}
	list_elem* temp = my_list -> head;

	for (int i = 0; i < my_list -> len; ++i)
		if (strcmp(/*_strlwr(*/word, temp -> value) != 0) temp = temp -> next;
		else
		{
			*my_elem = temp;
			CHECK_LIST(my_list);
			
			OUT_DEB("# Found element, number = %d\n", i);
			OUT_DEB("### LIST SEARCH END ###\n");

			return LIST_SEARCH_FOUND;
		}
		OUT_DEB("# No such values found\n");
		OUT_DEB("### LIST SEARCH END ###\n");

		CHECK_LIST(my_list);
		return LIST_SEARCH_NO_SUCH;
}
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1
//+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1




#define DESTROY_ELEM_																					\
	ret = list_elem_destruct(temp);																	\
		if (ret != ELEM_OK)																			\
		{																							\
			OUT_DEB("# LIST DELETE ERROR: Element destruction error [error = %d]", ret);	\
			list_elem_interrupt_handler(temp, ret);													\
			return LIST_BAD;																		\
		}

int list_delete(list* my_list, list_elem* my_elem)
{
	OUT_DEB("### LIST DELETE BEGIN ###\n");
	OUT_DEB("# Deleting [%08x] element of list [%08x], len = %d\n", my_elem, my_list, my_list -> len);
	
	int ret = list_check(my_list);
	if (ret != LIST_CHECK_OK)
	{
		OUT_DEB("# LIST DELETE ERROR: list is not OK in the beginning [error: %d]", ret);
		
		ret = list_interrupt_handler(my_list, ret);
		
		OUT_DEB("### LIST DELETE END ###\n");
		
		return LIST_BAD;
	}

	if (my_elem == NULL)
	{
		OUT_DEB("LIST DELETE ERROR: Argumented pointer of element is NULL\n");
		OUT_DEB("Terminating...");
		
		return LIST_BAD;
	}
	
	if (my_list -> len == 1)
	{
		list_elem* temp = my_list -> head;
		my_list -> head = NULL;
		my_list -> tail = NULL;
		my_list -> len -= 1;

		DESTROY_ELEM_;
		CHECK_LIST(my_list);

		OUT_DEB("# DONE\n");
		OUT_DEB("### LIST DELETE END ###\n");

		return LIST_OK;

	}
	if (my_list -> head == my_elem)
	{
		list_elem* temp = my_list -> head;
		my_list -> head = my_list -> head -> next;
		my_list -> head -> prev = NULL;

		DESTROY_ELEM_;

		my_list -> len -= 1;
		CHECK_LIST(my_list);

		OUT_DEB("# DONE\n");
		OUT_DEB("### LIST DELETE END ###\n");

		return LIST_OK;
	}

	if (my_list-> tail == my_elem)
	{
		list_elem* temp = my_list -> tail;
		my_list -> tail = my_list -> tail -> prev;
		my_list -> tail -> next = NULL;

		DESTROY_ELEM_;

		my_list -> len -= 1;
		CHECK_LIST(my_list);

		OUT_DEB("# DONE\n");
		OUT_DEB("### LIST DELETE END ###\n");

		return LIST_OK;
	}
	list_elem* temp = my_list -> head;

	my_elem -> prev->next = my_elem -> next;
	my_elem -> next->prev = my_elem -> prev;
	my_list -> len -= 1;

	DESTROY_ELEM_;

	CHECK_LIST(my_list);

	OUT_DEB("# DONE\n");
	OUT_DEB("### LIST DELETE END ###\n");

	return LIST_OK;
}

#undef DESTROY_ELEM_
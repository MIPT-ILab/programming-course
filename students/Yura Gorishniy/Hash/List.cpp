#include "Hash.h"
extern FILE* the_log;

list* List_NEW ()
{
	list* new_list = (list*) calloc (1, sizeof(list));
	assert (new_list);

	new_list -> length = 0;
	new_list -> first_elem = NULL;
	new_list -> first_elem = NULL;

return new_list;
}

void List_Delete (list* my_list)
{
	List_Clear (my_list);

	my_list -> length = POiSON;
	free (my_list);
}

int List_OK (list* my_list)
{
	if (!my_list) return ERR_LIST_NULL;
	if (my_list -> length == 0 && (my_list -> first_elem != NULL || my_list -> last_elem != NULL)) return ERR_LIST_FIRST_LAST_POINTERS;
	if (my_list -> length != 0 && (my_list -> first_elem == NULL || my_list -> last_elem == NULL)) return ERR_LIST_FIRST_LAST_POINTERS;

	if (my_list -> length)
	{
		if (my_list -> first_elem -> prev || my_list -> last_elem -> next) return ERR_LIST_WRONG_FIRST_LAST;

		int nElems = 1;
		elem* cur_elem = my_list -> first_elem;

		while (nElems <= my_list -> length)
		{
			if (Elem_OK (cur_elem) != HAPPY) return ERR_LIST_BAD_ELEM;
			if (cur_elem -> next)
			{
				++nElems;
				cur_elem = cur_elem -> next;
			}
			else break;
		}
		if (cur_elem -> next) return ERR_LIST_LEN;
		if (nElems != my_list -> length) return ERR_LIST_LEN;
	}

return HAPPY;
}

int List_Dump (list* my_list)
{
	fprintf (the_log, "\n****************************  DUMP OF LIST  ********************\n");
	
	if (int err_index = List_OK (my_list) == HAPPY) fprintf (the_log, "Your list [%.8x] is OK\n", my_list);
	else
	{
		fprintf (the_log, "Your list [%.8x] is NOT ok!!!\n", my_list);
		PRINT_ERROR (err_index);
		fprintf (the_log, "Number of elements = %d\n"
						  "The first element [%.8x]\n"
						  "The last  element [%.8x]\n\n", 
						  my_list -> length, my_list -> first_elem, my_list -> last_elem);
		int nElems = 1;
		elem* cur_elem = my_list -> first_elem;
		while (nElems <= my_list -> length)
		{
			if (Elem_OK (cur_elem) != HAPPY)
			{
				fprintf (the_log, "BAD ELEM [%d] ", nElems);
				Elem_Dump (cur_elem);
				return SAD;
			}
			cur_elem = cur_elem -> next;
			nElems++;
		}
	}
	fprintf (the_log, "Number of elements = %d\n"
					  "The first element [%.8x]\n"
					  "The last  element [%.8x]\n\n", 
					  my_list -> length, my_list -> first_elem, my_list -> last_elem);
	int nElems = 1;
	elem* cur_elem = my_list -> first_elem;
	while (nElems <= my_list -> length)
	{
		if (cur_elem)
		{
			fprintf (the_log, "%d. ", nElems++);
			Elem_Dump (cur_elem);
			cur_elem = cur_elem -> next;
		}
		else
		{
			fprintf (the_log, "Length of List [%.8x] is too big\n", my_list);
			break;
		}
	}

return HAPPY;
}

int List_Clear (list* my_list)
{
	ASSERT_LIST_OK (my_list);

	elem* cur_elem = my_list -> last_elem; 
	while (1)
	{
		if (cur_elem) cur_elem = Elem_Delete (my_list, cur_elem);
		else break;
	}

	ASSERT_LIST_OK (my_list);

return HAPPY;
}

int List_Elem_Add (list* my_list, const char* my_key, int my_info)
{
	ASSERT_LIST_OK (my_list);

	elem* new_elem = Elem_NEW ();
	strcpy (new_elem -> key, my_key);
	new_elem -> info = my_info;

	if (my_list -> last_elem)
	{
		my_list -> last_elem -> next = new_elem;
		new_elem -> prev = my_list -> last_elem;
		my_list -> last_elem = new_elem;
	}
	else
	{
		my_list -> first_elem = new_elem;
		my_list -> last_elem  = new_elem;
	}
	my_list -> length += 1;

	ASSERT_LIST_OK (my_list);
return HAPPY;
}

int List_Elem_Find_Key (list* my_list, const char* my_key, elem** my_elem)
{
	ASSERT_LIST_OK (my_list);
	
	*my_elem = NULL;
	if (!my_list -> first_elem) return 0;
	elem* cur_elem = my_list -> first_elem;
	int nElems = 1;
	while (nElems <= my_list -> length)
	{
		if (!cur_elem) return NULL;
		if (strcmp (cur_elem -> key, my_key) == 0)
		{
			*my_elem = cur_elem;
			break;
		}
		else
		{
			cur_elem = cur_elem -> next;
			++nElems;
		}
	}

	ASSERT_LIST_OK (my_list);
return HAPPY;
}

int List_Elem_Find_Num (list* my_list, int my_num, elem** my_elem)
{
	ASSERT_LIST_OK (my_list);

	*my_elem = NULL;
	if (!my_list -> first_elem) return NULL;
	elem* cur_elem = my_list -> first_elem;
	int nElems = 1;
	while (nElems <= my_list -> length)
	{
		if (!cur_elem) return NULL;
		if (nElems == my_num)
		{
			*my_elem = cur_elem;
			break;
		}
		else
		{
			cur_elem = cur_elem -> next;
			++nElems;
		}
	}

	ASSERT_LIST_OK (my_list);
return HAPPY;	
}

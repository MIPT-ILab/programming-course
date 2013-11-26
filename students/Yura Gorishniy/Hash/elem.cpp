#include "Hash.h"
extern FILE* the_log;

elem* Elem_NEW ()
{
	elem* new_elem = (elem*) calloc (1, sizeof(elem));
	assert (new_elem);
	new_elem -> key = (char*) calloc (KEY_SIZE, sizeof(char));
	assert (new_elem -> key);
	new_elem -> info = 0;
	new_elem -> prev = NULL;
	new_elem -> next = NULL;
return new_elem;
}

elem* Elem_Delete (list* my_list, elem* my_elem)
{
	elem* ret = my_elem -> prev;
	if (my_elem -> prev)
	{
		if (my_elem -> next)
		{
			my_elem -> prev -> next = my_elem -> next;
			my_elem -> next -> prev = my_elem -> prev;
		}
		else
		{
			my_elem -> prev -> next = NULL;
			my_list -> last_elem = my_elem -> prev;
		}
	}
	else if (my_elem -> next)
		{
			my_elem -> next -> prev = NULL;
			my_list -> first_elem = my_elem -> next;
		}
		else 
		{
			my_list -> first_elem = NULL;
			my_list -> last_elem  = NULL;
		}

	for (int i = 0; i < strlen(my_elem -> key); ++i) my_elem -> key[i] = STR_POiSON;
	my_elem -> info = POiSON;
	free (my_elem);
	my_list -> length -= 1;

return ret;
}

int Elem_OK (elem* my_elem)
{
	if (!my_elem) return ERR_ELEM_NULL;
	if (my_elem -> prev) if (my_elem != my_elem -> prev -> next) return ERR_ELEM_PREV;
	if (my_elem -> next) if (my_elem != my_elem -> next -> prev) return ERR_ELEM_NEXT;
return HAPPY;
}

int Elem_Dump (elem* my_elem)
{
	if (int err_index = Elem_OK (my_elem) == HAPPY) fprintf (the_log, "Elem [%.8x] is OK     ", my_elem);
	else
	{
		fprintf (the_log, "Elem [%.8x] is NOT ok!  ", my_elem);
		PRINT_ERROR (err_index);
		return SAD;
	}
	fprintf (the_log, "key = %s     info = %d     prev[%.8x]      next[%.8x]\n\n", 
					  my_elem -> key, my_elem -> info, my_elem -> prev, my_elem -> next);
return HAPPY;
}
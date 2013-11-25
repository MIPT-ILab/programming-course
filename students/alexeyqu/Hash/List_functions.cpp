#include "Hash.h"

int List_Construct (list_t* list)
{
    OUT (stdout, "Construction of new list [%08x]..\n", (int) list);

    if (list == NULL)
    {
        OUT (stdout, "Pointer to list [%08x] is NULL.\n", (int) list);
        return LIST_NULL;
    }

    HTEC (Elem_Construct (&list->head, ""));
    list->length = 0;

    OUT (stdout, "Construction of list [%08x] was finished.\n\n", (int) list);

    LIST_CHECK_ (list);

    return LIST_OK;
}

int List_Destruct (list_t* list)
{
    OUT (stdout, "Destructing list [%08x]..\n", (int) list);

    LIST_CHECK_ (list);

    elem_t* cur_elem = list->head;
    elem_t* next_elem = NULL;

    register unsigned int cur_index = 0;
    for (cur_index = 0; cur_index < list->length; cur_index++)
    {
        next_elem = cur_elem->next;

        HTEC (Elem_Destruct (cur_elem));

        cur_elem = next_elem;
    }

    list->length = Poison;

    OUT (stdout, "Destruction of list [%08x] was finished.\n\n", (int) list);

    return LIST_OK;
}

int List_Is_OK (list_t* list)
{
    if (list == NULL) return LIST_NULL;
    if (list->length < 0) return LIST_WR_NDX_RANGE;

    elem_t* cur_elem = list->head;

    unsigned int i = 0;
    for (i = 0; i < list->length; i++)
    {
        if (cur_elem->next == NULL ||
            cur_elem->next->prev != cur_elem) return LIST_INV;

        cur_elem = cur_elem->next;
    }

    return LIST_OK;
}

void List_Dump (list_t* list, FILE* log)
{
    OUT (stdout, "\tDump of list [%08x] started.\n", (int) list);

    fprintf (log, "\tList [%08x] - %s\n", (int) list, (List_Is_OK (list) == LIST_OK)? "ok" : "ERROR");
    fprintf (log, "\tlength -\t%d\n", list->length);

    elem_t* cur_elem = list->head;

    register unsigned int cur_index = 0;
    for (cur_index = 0; cur_index <= list->length; cur_index++)
    {
        fprintf (log, "\tElement #%d\n", cur_index);
        Elem_Dump (cur_elem, log);

        cur_elem = cur_elem->next;
    }

    OUT (stdout, "\tDump of list [%08x] was finished.\n", (int) list);
}

int List_Add_Elem (list_t* list, elem_t* elem, unsigned int index)
{
    OUT (stdout, "Adding element [%08x] to list [%08x] started.\n", (int) elem, (int) list);
    OUT (stdout, "Index = %d\n", index);

    LIST_CHECK_ (list);

    ELEM_CHECK_ (elem);

    INDEX_CHECK_ (index);

    elem_t* cur_elem = list->head;

    register unsigned int cur_index = 0;
    for (cur_index = 0; cur_index < index; cur_index++)
    {
        cur_elem = cur_elem->next;
    }

    elem->next = cur_elem->next;
    elem->prev = cur_elem;
    cur_elem->next = elem;
    if (elem->next != NULL) elem->next->prev = elem;

    list->length++;

    OUT (stdout, "Adding element finished.\n");

    LIST_CHECK_ (list);

    ELEM_CHECK_ (elem);

    INDEX_CHECK_ (index);

    return LIST_OK;
}

int List_Delete_Elem (list_t* list, unsigned int index)
{
    OUT (stdout, "Deleting element #%d to list [%08x] started.\n", index, (int) list);

    LIST_CHECK_ (list);

    INDEX_CHECK_ (index);

    elem_t* cur_elem = list->head;

    register unsigned int cur_index = 0;
    for (cur_index = 0; cur_index < index; cur_index++)
    {
        cur_elem = cur_elem->next;
    }

    cur_elem->prev->next = cur_elem->next;
    cur_elem->next->prev = cur_elem->prev;

    list->length--;

    OUT (stdout, "Deleting element finished.\n");

    LIST_CHECK_ (list);

    INDEX_CHECK_ (index);

    return LIST_OK;
}

int List_Find_Key (list_t* list, const char* key, int* index)
{
    OUT (stdout, "Finding the key '%s' inside the list [%08x]..\n", key, (int) list);

    *index = -1;

    LIST_CHECK_ (list);

    KEY_CHECK_ (key);

    elem_t* cur_elem = list->head;

    register unsigned int cur_index = 0;
    for (cur_index = 0; cur_index < list->length; cur_index++)
    {
        if (strcmp (cur_elem->key, key) == 0)
        {
            *index = cur_index;

            OUT (stdout, "Key found, index = %d", *index);

            return LIST_OK;
        }

        cur_elem = cur_elem->next;
    }

    OUT (stdout, "Key wasn't found\n");

    LIST_CHECK_ (list);

    KEY_CHECK_ (key);

    return -1;
}

/*int List_Print (list_t* list, FILE* output)
{
    OUT (stdout, "Printing the list [%08x] into file %d..\n", (int) list, (int) output);

    if (hashtable == NULL)
    {
        OUT (stdout, "Pointer to list [%08x] is NULL.\n", (int) list);
        return HT_NULL;
    }

    if (output == NULL)
    {
        OUT (stdout, "Pointer to file is NULL.\n");
        return HT_BAD_FILE;
    }

    register unsigned int cur_index = 0;

    while (cur_index < list->length)
    {
        fprintf (output, "%s %d\n", etc)
    }

    OUT (stdout, "List [%08x] is printed into %d file.\n", (int) list, (int) output);

    return HT_OK;
}
*/

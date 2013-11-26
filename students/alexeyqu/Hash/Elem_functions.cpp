/** ***************************************************************************
 * @file    Elem_functions.cpp
 *
 * @ingroup elem
******************************************************************************/

#include "Hash.h"

int Elem_Construct (elem_t** elem, const char* key)
{
    OUT (stdout, "\tConstructing new element [%08x]..\n", (int) elem);

    KEY_CHECK_ (key);

    *elem = (elem_t*) calloc (1, sizeof (elem_t));

    ELEM_CHECK_ (*elem);

    strcpy ((*elem)->key, key);

    (*elem)->amount = 0;
    (*elem)->prev = NULL;
    (*elem)->next = NULL;

    OUT (stdout, "\tConstruction of element [%08x] was finished.\n", (int) elem);

    ELEM_CHECK_ (*elem);

    return ELEM_OK;
}

int Elem_Destruct (elem_t* elem)
{
    OUT (stdout, "\tDestructing element [%08x]..\n", (int) elem);

    ELEM_CHECK_ (elem);

    elem->prev = NULL;
    elem->next = NULL;
    elem->amount = Poison;

    register unsigned int i = 0;
    for (i = 0; i < Max_Len; i++)
    {
        elem->key[i] = 0;
    }

    free (elem);

    OUT (stdout, "\tDestruction of element [%08x] was finished.\n", (int) elem);

    return ELEM_OK;
}

int Elem_Is_OK (elem_t* elem)
{
    if (elem == NULL) return ELEM_NULL;

    if (elem->key == NULL) return ELEM_NULL_KEY;

    return ELEM_OK;
}

void Elem_Dump (elem_t* elem, FILE* log)
{
    OUT (stdout, "\t\tDump of elem [%08x] started.\n", (int) elem);

    fprintf (log, "\t\tDump of elem [%08x]\n", (int) elem);
    fprintf (log, "\t\tkey -\t\t'%s'\n", elem->key);
    fprintf (log, "\t\tamount -\t%d\n", elem->amount);
    fprintf (log, "\t\tnext -\t[%08x]\n", (int) elem->next);
    fprintf (log, "\t\tprev -\t[%08x]\n", (int) elem->prev);
    fprintf (log, "\t\tDump of elem was finished.\n");

    OUT (stdout, "\t\tDump of elem [%08x] was finished.\n", (int) elem);
}

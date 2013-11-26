/** ***************************************************************************
 * @file    Hashtable_functions.cpp
 *
 * @ingroup hash
******************************************************************************/

#include "Hash.h"

int Hashtable_Construct (hashtable_t* hashtable, unsigned int max_hashvalue)
{
    OUT (stdout, "Constructing hashtable [%08x]..\n", (int) hashtable);

    if (hashtable == NULL)
    {
        OUT (stdout, "Pointer to hashtable [%08x] is NULL.\n", (int) hashtable);
        return HT_NULL;
    }

    if (max_hashvalue >= MAX_HASHVALUE)
    {
        OUT (stdout, "Max_hashvalue is too big.\n");
        return HT_WR_HV_RANGE;
    }

    hashtable->buckets = (list_t*) calloc (max_hashvalue, sizeof (list_t));

    register unsigned int cur_bucket = 0;
    for (cur_bucket = 0; cur_bucket < max_hashvalue; cur_bucket++)
    {
        HTEC (List_Construct (&hashtable->buckets[cur_bucket]));
    }

    hashtable->max_hashvalue = max_hashvalue;

    OUT (stdout, "Construction of hashtable [%08x] was finished\n", (int) hashtable);

    HASHTABLE_CHECK_ (hashtable);

    return HT_OK;
}

int Hashtable_Destruct (hashtable_t* hashtable)
{
    OUT (stdout, "Destructing hashtable [%08x]..\n", (int) hashtable);

    HASHTABLE_CHECK_ (hashtable);

    register unsigned int cur_bucket = 0;
    for (cur_bucket = 0; cur_bucket < hashtable->max_hashvalue; cur_bucket++)
    {
        HTEC (List_Destruct (&hashtable->buckets[cur_bucket]));
    }

    free (hashtable->buckets);
    hashtable->max_hashvalue = 0;

    OUT (stdout, "Destruction of hashtable [%08x] was finished", (int) hashtable);

    return HT_OK;
}

int Hashtable_Is_OK (hashtable_t* hashtable)
{
    if (hashtable->max_hashvalue >= MAX_HASHVALUE)
    {
        OUT (stdout, "Max_hashvalue is too big.\n");
        return HT_WR_HV_RANGE;
    }
    register unsigned int i = 0;
    for (i = 0; i < hashtable->max_hashvalue; i++)
    {
        LIST_CHECK_ (&hashtable->buckets[i])
    }

    return HT_OK;
}

void Hashtable_Dump (hashtable_t* hashtable, FILE* log)
{
    OUT (stdout, "Dump of hashtable [%08x] started.\n", (int) hashtable);

    fprintf (log, "Hashtable [%08x] - %s\n", (int) hashtable, (Hashtable_Is_OK (hashtable) != HT_OK)? "ok" : "ERROR");
    fprintf (log, "max_hashvalue -\t%d\n", hashtable->max_hashvalue);

    register unsigned int cur_hashvalue = 0;
    for (cur_hashvalue = 0; cur_hashvalue < hashtable->max_hashvalue; cur_hashvalue++)
    {
        fprintf (log, "Hashvalue #%d\n", cur_hashvalue);
        List_Dump (&hashtable->buckets[cur_hashvalue], log);
    }

    OUT (stdout, "Dump of hashtable [%08x] was finished. See log file for dump info.\n\n", (int) hashtable);
}

int Hashtable_Add_Key (hashtable_t* hashtable, const char* key,
                       int (*hash) (const char* key, int* hash))
{
    OUT (stdout, "Adding key '%s' to hashtable [%08x] started.\n", key, (int) hashtable);

    HASHTABLE_CHECK_ (hashtable);

    KEY_CHECK_ (key);

    int hashvalue = 0;
    int index = -1;

    HTEC (hash (key, &hashvalue));

    hashvalue %= (hashtable->max_hashvalue);

    HTEC (List_Find_Key (&hashtable->buckets[hashvalue], key, &index));

    if (index == -1)
    {
        OUT (stdout, "Adding new element to hashtable..\n");

        elem_t* new_elem;

        HTEC (Elem_Construct (&new_elem, key));

        HTEC (List_Add_Elem (&hashtable->buckets[hashvalue],
              new_elem, 0));
    }

    OUT (stdout, "Adding element finished.\n");

    HASHTABLE_CHECK_ (hashtable);

    return HT_OK;
}

int Hashtable_Fill (hashtable_t* hashtable, FILE* input,
                    int (*hash) (const char* key, int* hash))
{
    OUT (stdout, "Filling the hashtable [%08x] by words from file %d..\n", (int) hashtable, (int) input);

    HASHTABLE_CHECK_ (hashtable);

    if (hash == NULL)
    {
        OUT (stdout, "Pointer to hash function is NULL.\n");
        return HT_ERR;
    }

    if (input == NULL)
    {
        OUT (stdout, "Pointer to file is NULL.\n");
        return HT_BAD_FILE;
    }

    fseek (input, 0, 0);

    char* word = (char*) calloc (Max_Len, sizeof (char));
    int res_input = 0;

    while (1)
    {
        res_input = fscanf (input, "%s", word);

        if (res_input == EOF)
        {
            break;
        }

        if (res_input == 0)
        {
            return HT_WR_INPUT;
        }

        HTEC (Hashtable_Add_Key (hashtable, word, hash));
    }

    OUT (stdout, "Hashtable is ready.\n");

    return HT_OK;
}

int Hashtable_Print (hashtable_t* hashtable, FILE* output)
{
    OUT (stdout, "Printing the hashtable [%08x] into file %d..\n", (int) hashtable, (int) output);

    if (hashtable == NULL)
    {
        OUT (stdout, "Pointer to hashtable [%08x] is NULL.\n", (int) hashtable);
        return HT_NULL;
    }

    if (output == NULL)
    {
        OUT (stdout, "Pointer to file is NULL.\n");
        return HT_BAD_FILE;
    }

    fseek (output, 0, 0);

    register unsigned int cur_hashvalue = 0;

    while (cur_hashvalue < hashtable->max_hashvalue)
    {
        fprintf (output, "%d\t%d\n", cur_hashvalue, hashtable->buckets[cur_hashvalue].length);

        cur_hashvalue++;
    }

    OUT (stdout, "Hashtable is printed into %d file.\n", (int) output);

    return HT_OK;
}

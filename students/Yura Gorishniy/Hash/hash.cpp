#include "Hash.h"
extern FILE* the_log;

hash* Hash_NEW ()
{
	hash* new_hash = (hash*) calloc (1, sizeof(hash));
	assert (new_hash);
	for (int i = 0; i < HASH_SIZE; ++i) new_hash -> table[i] = List_NEW();
	new_hash -> size = HASH_SIZE;
	new_hash -> func = NULL;
	return new_hash;
}

void Hash_Delete (hash* my_hash)
{
	ASSERT_HASH_OK (my_hash);

	for (int i = 0; i < my_hash -> size; ++i) List_Delete (my_hash -> table[i]);
	my_hash -> func = NULL;
	my_hash -> size = POiSON;
	free (my_hash);
}

int Hash_OK (hash* my_hash)
{
	if (!my_hash -> func) return 0;
	for (int i = 0; i < my_hash -> size; ++i) if (List_OK (my_hash -> table[i]) != HAPPY) return ERR_HASH_BAD_LIST;
return HAPPY;
}

int Hash_Dump (hash* my_hash)
{
	fprintf (the_log, "\n\n********************* DUMP OF HASH ****************************************\n"
					 "The file: %s\n"
					 "The compilation time: %s, %s\n\n", __FILE__, __DATE__, __TIME__);

	if (int ok_index = Hash_OK (my_hash) == HAPPY) fprintf (the_log, "Your Hash [%.8x] is OK\n", my_hash);
	else
		{
			fprintf (the_log, "Your Hash [%.8x] is NOT ok!!!\n", my_hash);
			fprintf (the_log, "The size of hash = %d\n", my_hash -> size);
			fprintf (the_log, "Pointer of hash function [%.8x]\n\n", my_hash -> func);
			PRINT_ERROR (ok_index);
			for (int i = 0; i < my_hash -> size; ++i)
			{
				if (List_OK (my_hash -> table[i]) != HAPPY)
				{
					List_Dump (my_hash -> table[i]);
					return SAD;
				}
			}
		}
	fprintf (the_log, "The size of hash = %d\n", my_hash -> size);
	fprintf (the_log, "Pointer of hash function [%.8x]\n\n", my_hash -> func);
	for (int i = 0; i < my_hash -> size; ++i)
	{
		fprintf (the_log, "List [%d]", i);
		List_Dump (my_hash -> table[i]);
	}
return HAPPY;
}

int Hash_Find_Key (hash* my_hash, const char* my_key, elem** my_elem)
{
	ASSERT_HASH_OK (my_hash);

	*my_elem = NULL;
	List_Elem_Find_Key (my_hash -> table[(*(my_hash -> func)) (my_key) & my_hash -> size], my_key, my_elem);

	ASSERT_HASH_OK (my_hash);
return HAPPY;
}

unsigned int hf0 (const char* my_key)
{
    assert (my_key);
    return 0;
}

unsigned int hf1 (const char* my_key)
{
    assert (my_key);
    return (unsigned int)my_key[0];
}


unsigned int hf2 (const char* my_key)
{
    assert (my_key);
    int i = 0;
    unsigned int sum = 0;
    while ((my_key[i] != 0) && (i < HASH_SIZE)) sum += my_key[i++];
    return sum;
}


unsigned int hf3 (const char* my_key)
{
    assert (my_key);
    unsigned int sum = 0;
    int i = 0;
    while ((my_key[i] != 0) && (i < HASH_SIZE)) sum += my_key[i++];
    if (i != 0) sum /= i;
    return sum;
}

unsigned int hf4 (const char* my_key)
{
	assert (my_key);
    unsigned int ret = 0;
    int i = 0;
    while ((my_key[i] != 0) && (i < HASH_SIZE)) ret = ((ret << sizeof(ret)* 8 - 1) | (ret >> 1)) ^ ((long long) my_key[i++]);
    return ret;
}
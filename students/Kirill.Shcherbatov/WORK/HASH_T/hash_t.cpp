#include "defines.h"
#include "hash_t.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

hash_table_t *hash_constructor (const unsigned hash_table_size)
{
	OUT ("# called hash_constructor\n");
	assert (hash_table_size>0);
	hash_table_t *ret_hash_table = (hash_table_t *)calloc (1, sizeof(hash_table_t));
	assert (ret_hash_table!=NULL);
	ret_hash_table->table_size = hash_table_size;
	ret_hash_table->table = (hash_table_record_t**)calloc (hash_table_size, sizeof(struct hash_table_record_t*));
	assert (ret_hash_table->table != NULL);
	return ret_hash_table;
}

struct hash_table_record_t  *hash_find (const hash_table_t *hash_table, const char *request_name,
	unsigned(*hash_function)(const char *string, const unsigned hash_table_size))
{
	OUT ("# called hash_find with %s, table [%p]\n", request_name, hash_table);

	assert (request_name != NULL);
	assert (hash_table != NULL);
	assert (hash_table->table != NULL);

	struct hash_table_record_t *searh_pointer = NULL;

	for (searh_pointer = hash_table->table[hash_function (request_name, hash_table->table_size)];
		searh_pointer != NULL; searh_pointer = searh_pointer->next)
	{
		if (strcmp (request_name, searh_pointer->name) == 0)
		{
			OUT ("#  find [%p]\n", searh_pointer);
			return searh_pointer;
		}
	}
	OUT ("#  no this record\n");
	return NULL;
}

struct hash_table_record_t *hash_add (const hash_table_t *hash_table,  const char *name, const double data,
	unsigned(*hash_function)(const char *string, const unsigned hash_table_size))
{
	OUT("# called hash_add with '%s', %lg, table [%p]\n", name, data, hash_table);

	assert (name != NULL);
	assert (hash_table != NULL);
	assert (hash_table->table != NULL);

	struct hash_table_record_t *temp_pointer = NULL;
	unsigned hash_value = 0;

	if ((temp_pointer = hash_find (hash_table, name, hash_function)) == NULL)
	{
		temp_pointer = (struct hash_table_record_t *)calloc(1, sizeof (struct hash_table_record_t));
		assert (temp_pointer != NULL);

		temp_pointer->name = _strdup (name);
		assert (temp_pointer->name != NULL);


		hash_value = hash_function (name, hash_table->table_size);
		temp_pointer->next = hash_table->table[hash_value];
		hash_table->table[hash_value] = temp_pointer;
	}
	temp_pointer->value++;
	return temp_pointer;
}

void hash_destructor (hash_table_t *hash_table)
{
	OUT ("# called hash_destructor [%p]\n", hash_table);
	assert (hash_table != NULL);

	for (register unsigned i = 0; i < hash_table->table_size; i++)
	{
		OUT("#  start free AREA %d <<o>>\n", i);
		struct hash_table_record_t *temp_pointer = hash_table->table[i];
		if (temp_pointer != NULL)
		{
			do {
				struct hash_table_record_t *old_pointer = temp_pointer->next;

				OUT("#    -now free [%p]\t'%s'\t%lg\t>[%p]\n", temp_pointer, temp_pointer->name, temp_pointer->value, temp_pointer->next);

				free (temp_pointer->name);
				temp_pointer->name = NULL;
				temp_pointer->value = -666;
				temp_pointer->next = NULL;
				free (temp_pointer);
				temp_pointer = old_pointer;

			} while (temp_pointer != NULL);
			hash_table->table[i] = NULL;
		} else
			OUT("#  already EMPTY!\n");
	}
	free (hash_table->table);
	hash_table->table = NULL;

	free (hash_table);
	hash_table = NULL;
}

char hash_is_ok (const hash_table_t *hash_table)
{
	return (hash_table != NULL) && (hash_table->table != NULL) && (hash_table->table_size > 0);
}

void hash_dump (const hash_table_t *hash_table)
{
	assert (hash_table != NULL);
	printf ("#> HASH DUMP.\n");
	printf ("#> hash [%p] is %s\n", hash_table, (hash_is_ok(hash_table) != 0) ? "OK." : "BAD!");
	for (register unsigned i = 0; i <  hash_table->table_size; i++)
	{
		printf ("#>  AREA %d <<o>>\n", i);
		struct hash_table_record_t *temp_pointer = (struct hash_table_record_t*)hash_table->table[i];
		if (temp_pointer != NULL)
		{
			do {
				printf ("#>    [%p]\t'%s'\t%lg\t>[%p]\n",
					temp_pointer, temp_pointer->name,
					temp_pointer->value, temp_pointer->next);
				temp_pointer = (temp_pointer->next);
			} while (temp_pointer != NULL);
		}
		else printf ("#>   EMPTY!\n");
	}
	printf ("#> END HASH DUMP.\n");
}

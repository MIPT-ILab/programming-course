#include <stdio.h>
#include <assert.h>
#include <Windows.h>
#include "defines.h"
#include "hash_t.cpp"

unsigned hash_kernigan  (const char *string, const unsigned hash_table_size);
unsigned hash_0         (const char *string, const unsigned hash_table_size);
unsigned hash_1         (const char *string, const unsigned hash_table_size);
unsigned hash_2         (const char *string, const unsigned hash_table_size);
unsigned hash_3         (const char *string, const unsigned hash_table_size);
void     out_collision  (const hash_table_t *hash_table, FILE* target_device);

int main(int, char *argv[])
{
	OUT("# %s \n"
		"# (%s)\n"
		"# %s %s:\n\n",
		argv[0], __FILE__, __DATE__, __TIME__);

	printf("Hash function test.\n");
	printf("Using:\t'HASH' program_file_to_process\n\n");

	printf("Choose the hash function [0; 3]:\t");
	int mode = 0;
	scanf ("%d", &mode);

	char *file_name = NULL;
	if (argv[1] != NULL) file_name = _strdup(argv[1]);
	else
	{
		printf("No input filename argument, enter the name of the file to hashing\n");
		file_name = (char*)calloc(255, sizeof(char));
		assert(file_name != NULL);
		scanf("%s", file_name);
	}

	FILE* f = fopen(file_name, "r");
	assert(f != NULL);
	if (file_name != NULL) free(file_name);

	hash_table_t *my_hash = hash_constructor (128);

	char buffer_string[255] = "";

	while (fscanf(f, "%s", buffer_string) != EOF)
	{
		switch (mode)
		{
			case 0:
			{
				hash_add(my_hash, buffer_string, 0, hash_0);
				break;
			}
			case 1:
			{
				hash_add(my_hash, buffer_string, 0, hash_1);
				break;
			}
			case 2:
			{
				hash_add(my_hash, buffer_string, 0, hash_2);
				break;
			}
			case 3:
			{
				hash_add(my_hash, buffer_string, 0, hash_kernigan);
				break;
			}
		default:
			break;
		}
	}
	fclose (f);
	f = NULL;

	f = fopen ("report.txt", "w");
	assert(f != NULL);

	out_collision(my_hash, f);
	hash_destructor(my_hash);
	my_hash = NULL;


	fclose (f);
	f = NULL;

	system ("pause");
	return 0;
}


unsigned hash_kernigan (const char *string, const unsigned hash_table_size)
{
	OUT("# called hash_f with %s and %u\n", string, hash_table_size);

	assert (string != NULL);
	assert (hash_table_size > 0);

	unsigned hash_value = 0;
	for (hash_value = 0; *string != '\0'; string++)
		hash_value = *string + 31 * hash_value;
	return hash_value % hash_table_size;
}

unsigned hash_0 (const char *string, const unsigned hash_table_size)
{
	OUT("# called hash_0 with %s and %u\n", string, hash_table_size);

	assert(string != NULL);
	assert(hash_table_size > 0);

	OUT ("# called hash_0\n");
	return 0;
}

unsigned hash_1 (const char *string, const unsigned hash_table_size)
{
	OUT("# called hash_1 with %s and %u\n", string, hash_table_size);

	assert(string != NULL);
	assert(hash_table_size > 0);

	return (unsigned)string[0];
}

unsigned hash_2 (const char *string, const unsigned hash_table_size)
{
	OUT("# called hash_2 with %s and %u\n", string, hash_table_size);

	assert(string != NULL);
	assert(hash_table_size > 0);

	unsigned sum = 0;
	for (; *string != '\0'; string++)
		sum += *string;
	return sum % hash_table_size;
}

void out_collision (const hash_table_t *hash_table, FILE* target_device)
{
	assert(hash_table != NULL);

	for (register unsigned i = 0; i < hash_table->table_size; i++)
	{
		struct hash_table_record_t *temp_pointer = (struct hash_table_record_t*)hash_table->table[i];
		int counter = 0;
		if (temp_pointer != NULL)
		{
			do {
				counter++;
				temp_pointer = (temp_pointer->next);
			} while (temp_pointer != NULL);
		};
		fprintf (target_device, "%d\n", counter);
	}
}

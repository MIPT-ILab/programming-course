#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
    #define OUT printf
#else
    #define OUT if (0) printf
#endif

struct table_record
{
    struct table_record *next;
    char *name;
    unsigned kol;
};

unsigned h_kernigan (const char *s, const unsigned table_size)
{
    OUT ("# called kernigan [%p] = '%s', normalize=[%d]\n", s, s, table_size);
    assert (s != NULL);
    assert (table_size > 0);
    OUT ("# assertion ok.\n");

    unsigned hash_value = 0;

    for (hash_value = 0; *s != '\0'; s++)
        hash_value = *s + 31*hash_value;

    return hash_value % table_size;
}

unsigned h0 (const char *s, const unsigned table_size)
{
	OUT ("# called h0 [%p] = '%s', normalize=[%d]\n", s, s, table_size);
    assert (s != NULL);
    assert (table_size > 0);
    OUT ("# assertion ok.\n");

    return 0;
}

unsigned h2 (const char *s, const unsigned table_size)
{
	OUT ("# called h2 [%p] = '%s', normalize=[%d]\n", s, s, table_size);
    assert (s != NULL);
    assert (table_size > 0);
    OUT ("# assertion ok.\n");

    unsigned sum = 0;
    for (; *s!='\0'; s++)
        sum+=*s;
    return sum % table_size;
}

struct table_record *find_in_table (const char *request_name, const struct table_record **hash_table, const unsigned table_size,
                                    unsigned (*hash_function)(const char *s, const unsigned table_size))
{
    OUT ("# called find_in_table with [%p] = '%s', t=[%p] f=[%p]\n",
         request_name, request_name, hash_table, hash_function);
    assert (request_name != NULL);
    assert (hash_table != NULL);
    assert (hash_function != NULL);
    assert (table_size > 0);
    OUT ("#  assertion ok.\n");

    struct table_record *searh_pointer = NULL;

    for (searh_pointer = (struct table_record *)hash_table[hash_function (request_name, table_size)];
          searh_pointer != NULL; searh_pointer = searh_pointer->next)
    {
        OUT ("#  compare '%s' and |'%s'|\n", request_name, searh_pointer->name);
        if (strcmp(request_name, searh_pointer->name) == 0)
        {
            OUT ("#   find [%p]\n", searh_pointer);
            return searh_pointer;
        }
    }
    OUT ("#  no this record\n");
    return NULL;
}

struct table_record *add_data_in_table (const char *name, struct table_record **hash_table, const unsigned table_size,
                                        unsigned (*hash_function)(const char *s, const unsigned table_size))
{
    OUT ("# called add_data_in_table with [%p] = '%s', t=[%p] f=[%p]\n", name, name, hash_table, hash_function);
    assert (name != NULL);
    assert (hash_table != NULL);
    assert (hash_function != NULL);
    assert (table_size > 0);
    OUT ("#  assertion ok.\n");

    struct table_record *temp_pointer = NULL;
    unsigned hash_value = 0;

    if ((temp_pointer = find_in_table(name, (const struct table_record **)hash_table, table_size, hash_function)) == NULL)
    {
        OUT ("#   no same data in table, add new\n");
        temp_pointer = (struct table_record *)calloc(1, sizeof (struct table_record));
        assert (temp_pointer != NULL);
        temp_pointer -> name = strdup(name);
        assert (temp_pointer -> name != NULL);
        temp_pointer->kol = 1;
        hash_value = hash_function(name, table_size);
        temp_pointer->next = hash_table[hash_value];
        hash_table[hash_value] = temp_pointer;
        OUT ("# added in root\n");

    } else
    {
        temp_pointer->kol++;
        OUT ("#   finded! inc kol, new [%d]\n", temp_pointer->kol);
    }
    return temp_pointer;
}

void free_table (struct table_record **hash_table, const unsigned table_size)
{
    OUT ("# called add_data_in_table t=[%p] table_size=[%d]\n", hash_table, table_size);
    assert (hash_table != NULL);
    assert (table_size > 0);
    OUT ("#  assertion ok.\n");

    for (register unsigned i = 0; i < table_size; i++)
    {
        OUT ("#  start free AREA %d <<o>>\n", i);
        struct table_record *temp_pointer = (struct table_record *)hash_table[i];
        if (temp_pointer != NULL)
        {
            do {
                    struct table_record *buffer_pointer = temp_pointer->next;
                    OUT ("#    -now free [%p]\t'%s'\t%d\t>[%p]\n",
                         temp_pointer,temp_pointer->name, temp_pointer->kol, temp_pointer->next);
                    free (temp_pointer->name);
                    temp_pointer->name = NULL;
                    OUT ("#     name freed\n");
                    temp_pointer->kol = -666;
                    temp_pointer->next = NULL;
                    OUT ("#     rewrite_data:\n"
                         "#       }now it's [%p]\t'%s'\t%d\t>[%p]\n",
                          temp_pointer,temp_pointer->name, temp_pointer->kol, temp_pointer->next);
                    free (temp_pointer);
                    OUT ("#     cure record freed\n");
                    temp_pointer = buffer_pointer;
            } while (temp_pointer != NULL);
            hash_table[i] = NULL;
        } else OUT ("#   already EMPTY!\n");
    }
}

void dump_table (const struct table_record **hash_table, const unsigned table_size)
{
    assert (hash_table != NULL);
    assert (table_size > 0);
    printf ("#> HASH DUMP.\n");
    for (register unsigned i = 0; i < table_size; i++)
    {
        printf ("#>  AREA %d <<o>>\n", i);
        struct table_record *temp_pointer = (struct table_record*)hash_table[i];
        if (temp_pointer != NULL)
        {
            do {
                printf ("#>    [%p]\t'%s'\t%d\t>[%p]\n",
                         temp_pointer,temp_pointer->name, temp_pointer->kol, temp_pointer->next);
                temp_pointer = (temp_pointer->next);
            } while (temp_pointer != NULL);
        } else printf ("#>   EMPTY!\n");
    }
    printf ("#> END HASH DUMP.\n");
}

void out_kollision (struct table_record const **hash_table, const unsigned table_size)
{
    assert (hash_table != NULL);
    assert (table_size > 0);
    for (register unsigned i = 0; i < table_size; i++)
    {
        struct table_record *temp_pointer = (struct table_record*)hash_table[i];
        int counter = 0;
        printf ("%d ", i);
        if (temp_pointer != NULL)
        {
            do {
                counter++;
                temp_pointer = (temp_pointer->next);
            } while (temp_pointer != NULL);
        };
        printf ("%d\n", counter);
    }
}

int main(int argc, char *argv[])
{
    OUT ( "# %s \n"
		  "# (%s)\n"
		  "# %s %s:\n\n",
		   argv[0], __FILE__, __DATE__, __TIME__ );

	printf ("Hash functon test.\n");
    printf ("Using:\t'HASH' program_file_to_process\n\n");
    assert (argv[1] != NULL);
    #define HASH_TABLE_MAX_SIZE 101
    struct table_record **my_hash_table = (struct table_record **)calloc(HASH_TABLE_MAX_SIZE, sizeof(struct table_record *));

    char buffer_string[255] = "";

    FILE* f = fopen (argv[1], "r");
    while (fscanf(f, "%s", buffer_string) != EOF)
        add_data_in_table(buffer_string, my_hash_table, HASH_TABLE_MAX_SIZE, h_kernigan);
    fclose(f);
    out_kollision ((const struct table_record **)my_hash_table, HASH_TABLE_MAX_SIZE);
    free_table (my_hash_table, HASH_TABLE_MAX_SIZE);
    free (my_hash_table);
    return 0;
}

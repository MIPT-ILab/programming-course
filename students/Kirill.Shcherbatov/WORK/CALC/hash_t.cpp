#include "libs.h"
#include "hash_t.h"

unsigned hash_f (const char *s, const unsigned table_size)
{
    OUT ("# called hash_f [%p] = '%s', normalize=[%d]\n", s, s, table_size);
    assert (s != NULL);
    assert (table_size > 0);

    unsigned hash_value = 0;

    for (hash_value = 0; *s != '\0'; s++)
        hash_value = *s + 31*hash_value;

    OUT ("# hash value %u\n", hash_value % table_size);

    return hash_value % table_size;
}

struct hash_table_t *find_in_table (const char *request_name,
                                    const struct hash_table_t **hash_table,
                                    const unsigned table_size)
{
    OUT ("# called find_in_table with [%p] = '%s', t=[%p]\n",
         request_name, request_name, hash_table);

    assert (request_name != NULL);
    assert (hash_table != NULL);
    assert (table_size > 0);

    struct hash_table_t *searh_pointer = NULL;

    for (searh_pointer = (struct hash_table_t *)hash_table[hash_f (request_name, table_size)];
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

struct hash_table_t *add_data_in_table (const char *name,
                                        const double data,
                                        struct hash_table_t **hash_table,
                                        const unsigned table_size)
{
    OUT ("# called add_data_in_table with [%p] = '%s', t=[%p]\n",
         name, name, hash_table);

    assert (name != NULL);
    assert (hash_table != NULL);
    assert (table_size > 0);

    struct hash_table_t *temp_pointer = NULL;
    unsigned hash_value = 0;

    if ((temp_pointer = find_in_table(name,
                                      (const struct hash_table_t **)hash_table, table_size))
          == NULL)
    {
        OUT ("#   no same name in table, add new\n");

        temp_pointer = (struct hash_table_t *)calloc(1, sizeof (struct hash_table_t));
        assert (temp_pointer != NULL);

        temp_pointer -> name = strdup(name);
        assert (temp_pointer -> name != NULL);

        temp_pointer->value = data;

        hash_value = hash_f(name, table_size);
        temp_pointer->next = hash_table[hash_value];
        hash_table[hash_value] = temp_pointer;
    } else
    {
        OUT ("#   rewrite data '%lg' -> '%lg'\n", temp_pointer->value, data);
        temp_pointer->value = data;
    }
    return temp_pointer;
}

void free_table (struct hash_table_t **hash_table,
                 const unsigned table_size)
{
    OUT ("# called add_data_in_table t=[%p] table_size=[%d]\n", hash_table, table_size);
    assert (hash_table != NULL);
    assert (table_size > 0);

    for (register unsigned i = 0; i < table_size; i++)
    {
        OUT ("#  start free AREA %d <<o>>\n", i);
        struct hash_table_t *temp_pointer = (struct hash_table_t *)hash_table[i];
        if (temp_pointer != NULL)
        {
            do {
                    struct hash_table_t *buffer_pointer = temp_pointer->next;
                    OUT ("#    -now free [%p]\t'%s'\t%lg\t>[%p]\n",
                         temp_pointer,temp_pointer->name, temp_pointer->value, temp_pointer->next);

                    free (temp_pointer->name);
                    temp_pointer->name = NULL;
                    OUT ("#     name freed\n");

                    temp_pointer->value = -666;
                    temp_pointer->next = NULL;
                    OUT ("#     rewrite_data:\n"
                         "#       }now it's [%p]\t'%s'\t%lg\t>[%p]\n",
                          temp_pointer,temp_pointer->name, temp_pointer->value, temp_pointer->next);

                    free (temp_pointer);
                    OUT ("#     cure record freed\n");

                    temp_pointer = buffer_pointer;
            } while (temp_pointer != NULL);

            hash_table[i] = NULL;
        } else
            OUT ("#   already EMPTY!\n");
    }
}

void dump_table (const struct hash_table_t **hash_table,
                 const unsigned table_size)
{
    assert (hash_table != NULL);
    assert (table_size > 0);

    printf ("#> HASH DUMP.\n");
    for (register unsigned i = 0; i < table_size; i++)
    {
        printf ("#>  AREA %d <<o>>\n", i);
        struct hash_table_t *temp_pointer = (struct hash_table_t*)hash_table[i];
        if (temp_pointer != NULL)
        {
            do {
                printf ("#>    [%p]\t'%s'\t%lg\t>[%p]\n",
                        temp_pointer,temp_pointer->name,
                        temp_pointer->value, temp_pointer->next);
                temp_pointer = (temp_pointer->next);
            } while (temp_pointer != NULL);
        } else printf ("#>   EMPTY!\n");
    }
    printf ("#> END HASH DUMP.\n");
}

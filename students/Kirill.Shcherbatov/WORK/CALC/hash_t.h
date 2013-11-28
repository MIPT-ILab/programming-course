#ifndef HASH_T_H
#define HASH_T_H

struct hash_table_t
{
    struct hash_table_t *next;
    char *name;
    double value;
};

struct hash_table_t *find_in_table (const char *request_name,
                                    const struct hash_table_t **hash_table,
                                    const unsigned table_size);

struct hash_table_t *add_data_in_table (const char *name,
                                        const double data,
                                        struct hash_table_t **hash_table,
                                        const unsigned table_size);

void free_table (struct hash_table_t **hash_table,
                 const unsigned table_size);

void dump_table (const struct hash_table_t **hash_table,
                 const unsigned table_size);


#endif // HASH_T_H

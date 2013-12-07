struct hash_table_record_t
{
	struct hash_table_record_t *next;
	char	*name;
	double	value;
};

typedef struct
{
	struct hash_table_record_t** table;
	unsigned table_size;
} hash_table_t;

hash_table_t *hash_constructor (const unsigned hash_table_size);

struct hash_table_record_t  *hash_find(const hash_table_t *hash_table, const char *request_name,
	unsigned(*hash_function)(const char *string, const unsigned hash_table_size));

struct hash_table_record_t *hash_add(const hash_table_t *hash_table, const char *name, const double data,
	unsigned(*hash_function)(const char *string, const unsigned hash_table_size));

void hash_destructor(hash_table_t *hash_table);

char hash_is_ok(const hash_table_t *hash_table);

void hash_dump(const hash_table_t *hash_table);

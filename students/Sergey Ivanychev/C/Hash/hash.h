
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include <assert.h>



const int POISON = -228;
const int DUMPED_ELEMENTS_IF_ERROR = 10;
const int MAX_VALUE = 100;
const int BITSPERBYTE = 8;


typedef char list_elem_type;

typedef struct list_elem_s
{
	struct list_elem_s* prev;
	struct list_elem_s* next;
	char value[MAX_VALUE];
	int occur;
} list_elem;

typedef struct list_s
{
	list_elem* head;
	list_elem* tail;
	int len;

} list;

const int HASH_SIZE = 101;

typedef struct hash_s
{
	list* table[HASH_SIZE];

	unsigned long long(*hash_func)(const char* word);
	int size;
} hash;



//---------------------------------------------------------------

int list_elem_ctor(list_elem** my_elem, const char* value);

int list_elem_destruct(list_elem* my_elem);

int list_elem_delete(list_elem* my_elem);

int list_elem_check(list_elem* my_elem);

int list_elem_interrupt_handler(list_elem* my_elem, int cond);

int list_elem_dump(list_elem* my_list);

//-----------------------------------------------------------

int list_interrupt_handler(list* my_list, int cond);

int list_ctor(list** my_list);

int list_check(list* my_list);

int list_destruct(list* my_list);

int list_add(list* my_list, char* value);

int list_dump(list* my_list);

int list_delete(list* my_list, list_elem* my_elem);

int list_occur_change(list_elem* my_elem, int delta);

int list_search_word(list* my_list, char* word, list_elem** my_elem);

int list_delete_word(list* my_list, char* word);

int list_search_index(list* my_list, list_elem** found_elem, int index);


//-----------------------------------------------------------
int hash_check(hash* my_hash);

int hash_destruct(hash** my_hash);

int hash_ctor(hash** my_hash);

int hash_dump(hash* my_hash);

unsigned long long hash_func_zero(const char* word);

unsigned long long hash_func_first_ascii(const char* word);

unsigned long long hash_func_sum_ascii(const char* word);

unsigned long long hash_func_average_ascii(const char* word);

unsigned long long hash_func_bits_move(const char* word);

int hash_set_function(hash* my_hash, unsigned long long (*hash_func)(const char* word));

int generate_stats(hash* my_hash, const char* name_file, FILE* strin, unsigned long long(*h_func)(const char*));
		/*
		current_elem -> prev = NULL;
		current_elem -> next = NULL;
		current_elem -> value = NULL;
		current_elem -> occur = POISON;
		*/

//#define DEBUG

#ifdef DEBUG
	#define OUT_DEB printf
#else
	#define OUT_DEB if (0)
#endif

#define PRECOND(cond, err_ret, string)			\
	if ((cond))									\
	{											\
		OUT_DEB(string);						\
		return err_ret;							\
	}

#define POSTCOND(cond, err_ret, string)			\
	if ((cond))									\
	{											\
		OUT_DEB(string);						\
		return err_ret;							\
	}

#define VERIFY(cond, err_ret, string)			\
	if ((cond))									\
	{											\
		OUT_DEB(string);						\
		return err_ret;							\
	}

#define _ ,


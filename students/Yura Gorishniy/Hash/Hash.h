#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "DEFINES.h"
#include "CONSTS.h"

//====================================================================
//STRUCTURES
//====================================================================

typedef struct elem_s
{
    char* key;
	int   info;
    struct elem_s* next;
    struct elem_s* prev;
} elem;

typedef struct list_s
{
	int length;
	elem* first_elem;
	elem* last_elem;
} list;

typedef struct hash_s
{
	list* table[HASH_SIZE];
	unsigned int (*func) (const char* my_key);
	int size;
} hash;

//====================================================================
//ELEM FUNCTIONS
//====================================================================

elem* Elem_NEW ();
elem* Elem_Delete (list* my_list, elem* my_elem);
int Elem_OK (elem* my_elem);
int Elem_Dump (elem* my_elem);

//====================================================================
//HASH FUNCTIONS
//====================================================================

hash* Hash_NEW ();
void Hash_Delete (hash* my_hash);
int Hash_OK (hash* my_hash);
int Hash_Dump (hash* my_hash);
int Hash_Find_Key (hash* my_hash, const char* my_key, elem** my_elem);
unsigned int hf0 (const char* my_key);
unsigned int hf1 (const char* my_key);
unsigned int hf2 (const char* my_key);
unsigned int hf3 (const char* my_key);
unsigned int hf4 (const char* my_key);

//====================================================================
//LIST FUNCTIONS
//====================================================================

list* List_NEW ();
void List_Delete (list* my_list);
int List_OK (list* my_list);
int List_Dump (list* my_list);
int List_Clear (list* my_list);
int List_Elem_Add (list* my_list, const char* my_key, int my_info);
int List_Elem_Find_Key (list* my_list, const char my_key[], elem** my_elem);
int List_Elem_Find_Num (list* my_list, int my_num, elem** my_elem);
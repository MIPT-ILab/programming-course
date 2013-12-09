#ifndef LIST_FUNCTION_H_INCLUDED
#define LIST_FUNCTION_H_INCLUDED


#define ELEM_STR_SIZE 30

typedef struct elem_list_t elem_list_t;

struct elem_list_t
{
    char str[ELEM_STR_SIZE];
    struct elem_list_t* next;
    struct elem_list_t* previous;
};

struct head_list
{
    int size_list;
    elem_list_t* last;
    elem_list_t* first;
};

typedef struct head_list head_list;

typedef struct head_list head_list;

int list_add_before ( head_list* list, elem_list_t* elem, char* val );
int list_add_after ( head_list* list, elem_list_t* elem, char* val );

int list_ok ( head_list* list );

int list_del ( head_list* list, elem_list_t* elem );

int list_dump ( head_list* list );

int list_clear ( head_list* list );

head_list* list_construct ( );

int list_destruct ( head_list* list );

elem_list_t* list_find ( head_list* list, char* val );

#endif // LIST_FUNCTION_H_INCLUDED

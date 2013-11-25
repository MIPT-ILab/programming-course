/** ***************************************************************************
 * @file    Hash.h
******************************************************************************/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

#define DEBUG 0

#define LIST_CHECK_( list )\
    if (Hashtable_Error_Catch (List_Is_OK (list), "", (int) list) == HT_ERR) exit (1);

#define ELEM_CHECK_( elem )\
    if (Hashtable_Error_Catch (Elem_Is_OK (elem), "", (int) elem) == HT_ERR) exit (1);

#define KEY_CHECK_( key )\
    if (key == NULL)\
    {\
        OUT (stdout, "\tKey is inallocated.\n"); \
        return ELEM_NULL_KEY;\
    }\
    if (strlen (key) >= Max_Len)\
    {\
        OUT (stdout, "\tToo big size of key.\n"); \
        return ELEM_WR_KEY_RANGE;\
    }

#define INDEX_CHECK_( index )\
    if (index > list->length)\
    {\
        OUT (stdout, "Invalid index in list [%08x].\n", (int) list); \
        return LIST_WR_NDX_RANGE;\
    }

#define HASHTABLE_CHECK_( hashtable )\
    if (Hashtable_Error_Catch (Hashtable_Is_OK (hashtable), "", (int) hashtable) == HT_ERR) exit (1);

#ifndef DEBUG
    #error Define DEBUG as 0 or 1!
#endif

#if (DEBUG == 1)
    #define OUT fprintf
    #define ASSERT( cond )\
        if (!cond)\
        {\
            printf ("Assertion <%s> failed!\n", #cond);\
            printf ("Info: file %s, line %d", __FILE__, __LINE__);\
            exit (1);\
        }
#else
    #define OUT if (0)
    #define ASSERT( cond )
#endif

#define HTEC( func ) if (Hashtable_Error_Catch (func, "") == HT_ERR) ASSERT (!"Here it was:");

const unsigned int Max_Len = 50;
const unsigned int Poison = 0xDEAD;
const unsigned int MAX_HASHVALUE = 1000;

typedef struct elem
{
    char key[Max_Len];
    int amount;

    elem* next;
    elem* prev;
} elem_t;

typedef struct list
{
    unsigned int length;
    elem_t* head;
} list_t;

typedef struct hashtable
{
    list_t* buckets;
    unsigned int max_hashvalue;
} hashtable_t;

enum ERR_ELEM
{
    ELEM_OK = 1000,
    ELEM_NULL = 1001,
    ELEM_NULL_KEY = 1002,
    ELEM_WR_KEY_RANGE = 1003,
    ELEM_NOMEM = 1004
};

enum ERR_LIST
{
    LIST_OK = 2000,
    LIST_NULL = 2001,
    LIST_WR_NDX_RANGE = 2002,
    LIST_INV = 2003
};

enum ERR_HASHTABLE
{
    HT_ERR = -1,
    HT_OK = 3000,
    HT_NULL = 3001,
    HT_WR_HV_RANGE = 3002,
    HT_BAD_FILE = 3003,
    HT_WR_INPUT = 3004,
    HT_INV = 3005
};

int Elem_Construct (elem_t** elem, const char* key);
int Elem_Destruct (elem_t* elem);
int Elem_Is_OK (elem_t* elem);
void Elem_Dump (elem_t* elem, FILE* log);

int List_Construct (list_t* list);
int List_Destruct (list_t* list);
int List_Is_OK (list_t* list);
void List_Dump (list_t* list, FILE* log);
int List_Add_Elem (list_t* list, elem_t* elem, unsigned int index);
int List_Delete_Elem (list_t* list, unsigned int index);

int List_Find_Key (list_t* list, const char* key, int* index);

int List_Print (list_t* list, FILE* output);

int Hashtable_Construct (hashtable_t* hashtable, unsigned int max_hashvalue);
int Hashtable_Destruct (hashtable_t* hashtable);
int Hashtable_Is_OK (hashtable_t* hashtable);
void Hashtable_Dump (hashtable_t* hashtable, FILE* log);
int Hashtable_Add_Key (hashtable_t* hashtable, const char* key, int (*hash) (const char* key, int* hash));

int Hashtable_Fill (hashtable_t* hashtable, FILE* input, int (*hash) (const char* key, int* hash));
int Hashtable_Print (hashtable_t* hashtable, FILE* output);

int Hashtable_Error_Catch (int error, const char* msg, ...);

int hash_1 (const char* key, int* hash);
int hash_2 (const char* key, int* hash);
int hash_3 (const char* key, int* hash);
int hash_4 (const char* key, int* hash);
int hash_5 (const char* key, int* hash);
int hash_6 (const char* key, int* hash);

int Delete_All_Except_Letters_And_Spaces_From_Input_File_Or_Simple_Delete_All_Punctuation (FILE* input, FILE* output);
int ROL (int arg, int shift);

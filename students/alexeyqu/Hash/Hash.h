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

#ifndef DEBUG
    #error Define DEBUG as 0 or 1!
#endif

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

    #define HTEC( func ) if (Hashtable_Error_Catch (func, "") == HT_ERR) ASSERT (!"Here it was:");

    #define LIST_CHECK_( list ) HTEC (List_Is_OK (list));

    #define ELEM_CHECK_( elem ) HTEC (Elem_Is_OK (elem));

    #define HASHTABLE_CHECK_( hashtable ) HTEC (Hashtable_Is_OK (hashtable));

#if (DEBUG == 1)
//    #define KEY_CHECK_( key )\
//        if (key == NULL)\
//        {\
//            OUT (stdout, "\tKey is inallocated.\n"); \
//            return ELEM_NULL_KEY;\
//        }\
//        if (strlen (key) >= Max_Len)\
//        {\
//            OUT (stdout, "\tToo big size of key.\n"); \
//            return ELEM_WR_KEY_RANGE;\
//        }
//
//    #define INDEX_CHECK_( index )\
//        if (index > list->length)\
//        {\
//            OUT (stdout, "Invalid index in list [%08x].\n", (int) list); \
//            return LIST_WR_NDX_RANGE;\
//        }
//
//    #define HTEC( func ) if (Hashtable_Error_Catch (func, "") == HT_ERR) ASSERT (!"Here it was:");
//
//    #define LIST_CHECK_( list ) HTEC (List_Is_OK (list));
//
//    #define ELEM_CHECK_( elem ) HTEC (Elem_Is_OK (elem));
//
//    #define HASHTABLE_CHECK_( hashtable ) HTEC (Hashtable_Is_OK (hashtable));

    #define OUT fprintf
    #define ASSERT( cond )\
        if (!cond)\
        {\
            printf ("Assertion <%s> failed!\n", #cond);\
            printf ("Info: file %s, line %d", __FILE__, __LINE__);\
            exit (1);\
        }
#else
//    #define KEY_CHECK_( key )
//    #define INDEX_CHECK_( index )
//    #define HTEC( func )
//    #define LIST_CHECK_( list )
//    #define ELEM_CHECK_( elem )
//    #define HASHTABLE_CHECK_( hashtable )
    #define OUT if (0)
    #define ASSERT( cond )
#endif

const unsigned int Max_Len = 50; //!< Maximum length of key
const unsigned int Poison = 0xDEAD; //!< Poison value
const unsigned int MAX_HASHVALUE = 10000; //!< Maximum hash value

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

/** ***************************************************************************
 * List_Add_Elem
 *
 * @brief   Adds new element into list's specified index
 *
 * @ingroup list
 *
 * @param[out]  list    pointer to list
 * @param       elem    pointer to element
 * @param       index   index to plug new element
 *
 * @retval  ERR_LIST
******************************************************************************/
int List_Add_Elem (list_t* list, elem_t* elem, unsigned int index);

/** ***************************************************************************
 * List_Delete_Elem
 *
 * @brief   Deletes element from list's specified index
 *
 * @ingroup list
 *
 * @param[out]   list    pointer to list
 * @param        index   index to delete element
 *
 * @retval  ERR_LIST
******************************************************************************/
int List_Delete_Elem (list_t* list, unsigned int index);

/** ***************************************************************************
 * List_Find_Key
 *
 * @brief   Searches through the list for an element with key needed
 *
 * @ingroup list
 *
 * @param[out]  list    pointer to list
 * @param       key     key to find
 * @param[out]  index   index with needed key; -1 if not found
 *
 * @retval  ERR_LIST
******************************************************************************/
int List_Find_Key (list_t* list, const char* key, int* index);

/** ***************************************************************************
 * List_Print
 *
 * @brief   Prints hashtable into file
 *
 * @ingroup list
 *
 * @param   hashtable   pointer to hashtable
 * @param   output      output file descriptor
 *
 * @retval  ERR_LIST
******************************************************************************/
int List_Print (list_t* list, FILE* output);

int Hashtable_Construct (hashtable_t* hashtable, unsigned int max_hashvalue);
int Hashtable_Destruct (hashtable_t* hashtable);
int Hashtable_Is_OK (hashtable_t* hashtable);
void Hashtable_Dump (hashtable_t* hashtable, FILE* log);

/** ***************************************************************************
 * Hashtable_Add_Key
 *
 * @brief   Add new element to one of hashtable's lists using hash function
 *
 * @ingroup hash
 *
 * @param[out]  hashtable   pointer to hashtable
 * @param       key         key to add
 * @param       hash        pointer to hash function
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int Hashtable_Add_Key (hashtable_t* hashtable, const char* key, int (*hash) (const char* key, int* hash));

/** ***************************************************************************
 * Hashtable_Fill
 *
 * @brief   Fills hashtable using words from input file
 *
 * @ingroup hash
 *
 * @param[out]  hashtable   pointer to hashtable
 * @param       input       file descriptor
 * @param       hash        pointer to hash function
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int Hashtable_Fill (hashtable_t* hashtable, FILE* input, int (*hash) (const char* key, int* hash));

/** ***************************************************************************
 * Hashtable_Print
 *
 * @brief   Unstaged yet
******************************************************************************/
int Hashtable_Print (hashtable_t* hashtable, FILE* output);

/** ***************************************************************************
 * hash_1
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) = 0 (always 0!)
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_1 (const char* key, int* hash);

/** ***************************************************************************
 * hash_2
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) = first ASCII symbol code
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_2 (const char* key, int* hash);

/** ***************************************************************************
 * hash_3
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) = sum of ASCII symbol codes
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_3 (const char* key, int* hash);

/** ***************************************************************************
 * hash_4
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) = average of ASCII symbol codes
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_4 (const char* key, int* hash);

/** ***************************************************************************
 * hash_5
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) - algorithm with usage of bitshifts etc. Well, look inside source code :)
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_5 (const char* key, int* hash);

/** ***************************************************************************
 * hash_6
 *
 * @brief   hashes key
 *
 * @ingroup hash
 *
 * @par     f (key) a combination of hash_4 and hash_5 functions
 *
 * @param       key     key to hash
 * @param[out]  hash    hash value
 *
 * @retval      ERR_HASHTABLE
******************************************************************************/
int hash_6 (const char* key, int* hash);

/** ***************************************************************************
 * Hashtable_Error_Catch
 *
 * @brief   Error catcher, what?
 *
 * @ingroup misc
 *
 * @param   error   error code
 * @param   msg     message to print
 *
 * @retval  HT_OK | HT_ERR
******************************************************************************/
int Hashtable_Error_Catch (int error, const char* msg, ...);


/** ***************************************************************************
 * Adapt_Input
 *
 * @brief   tramsforms input file into good format style (no punctuation etc.)
 *
 * @ingroup misc
 *
 * @param   input   input file
 * @param   output  output file
 *
 * @retval  HT_OK | HT_ERR
******************************************************************************/
int Adapt_Input (FILE* input, FILE* output);

/** ***************************************************************************
 * ROL
 *
 * @brief   bit left shift
 *
 * @ingroup misc
 *
 * @param   arg     number to ROL
 * @param   shift   number of bits
 *
 * @retval  shifted arg
******************************************************************************/
int ROL (int arg, int shift);

#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define NOT_A_SUBSTRING -1
#define SUBSTRING( i ) i
#define MAXLEN 10000

#ifdef DEBUG
    #define DBG printf ("# "),

    #define ASSERT( cond )                                                    \
        if (!cond)                                                            \
        {                                                                     \
            printf ("\nOops! Something went wrong on %d line of %s file.\n"   \
                    "Exactly, the assertion <%s> is false.\n"                 \
                    "Whatever it is, it is too dangerous to let it live.\n"   \
                    , __LINE__, __FILE__, #cond);                             \
                                                                              \
            abort();                                                          \
        }
#else
    #define DBG if (0)
    #define ASSERT( cond )
#endif

/** ********************************************************************************
 * get_str - gets string from input stream
 *
 * @param      str      pointer to string
 * @param      MaxLen   Maximum allowed length
 *
 * @return     length of string
************************************************************************************/
int get_str (char* str, int MaxLen);


/** ********************************************************************************
 * str_cmp - compares 2 strings
 *
 * @param      str_1    pointer to first string
 * @param      str_2    pointer to second string
 * @param      MaxLen   Maximum allowed length
 *
 * @return     -1   str_1 < str_2
 *             0    str_1 = str_2
 *             1    str_1 > str_2
************************************************************************************/
int str_cmp (char* str_1, char* str_2, int MaxLen);


/** ********************************************************************************
 * sub_str - looks for a substring
 *
 * @param      haystack pointer to haystack string
 * @param      needdle  pointer to needle string
 * @param      MaxLen   Maximum allowed length
 *
 * @return     index of first substring entry
************************************************************************************/
int sub_str (char* haystack, char* needle, int MaxLen);


/** ********************************************************************************
 * str_len - returns lengths of string
 *
 * @param      str      pointer to string
 *
 * @return     length of string
************************************************************************************/
int str_len (char* str);

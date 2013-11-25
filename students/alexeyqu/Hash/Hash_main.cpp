/** ***************************************************************************
 * @file    Hash_main.cpp
 * @mainpage
 * @date    2013-11-21 19:34
 * @author  Alexey Kulikov <alexeyqu@gmail.com>, group 376, DCAM MIPT
 * @version 1.00
 *
 * Hashtable.
 *
 * @defgroup    elem
 * @defgroup    list
 * @defgroup    hash
 * @defgroup    misc
 *
 * @par     V1.00
 *          - Realised structures elem_t, list_t, hashtable_t ( see file @link Hash.h @endlink )
 *          - Added basic functions for working with these structures
 *          - Realised 6 different hash functions ( see file @link Hash_functions.cpp @endlink )
 *          - Added system of error catches
 *          - Added primitive print into .xls file to estimate effectiveness of hash functions
******************************************************************************/

#include "Hash.h"

int main()
{
    printf ("Hello!\n");
    printf ("I'm a program that constructs a hashtable and "
            "fills it with words from text.\n");
    printf ("There are 6 different hash functions (see documentation).\n");
    printf ("After the hashtable is filled up it is printed into suitable .xls file.\n");
    printf ("It prints also timing of each function.\n");
    printf ("So you can compare them by different parametres \n"
            "(e.g. time elapsed, usefulness etc.)\n\n");
    printf ("Author: AQ\n");
    printf ("Compiled from %s file\n"
            "on %s %s\n\n", __FILE__, __DATE__, __TIME__);

    FILE* log = fopen ("log.txt", "w");
    FILE* text = fopen ("text.txt", "r");
    FILE* input = fopen ("input.txt", "w+");
    FILE* output;

    fprintf (log, "Hashtable.\n");
    fprintf (log, "Author: AQ\n");
    fprintf (log, "Compiled from %s file\n"
            "on %s %s\n\n", __FILE__, __DATE__, __TIME__);

    hashtable_t hashtable = {};

    printf ("Please enter size of hashtable:\n->");

    unsigned int max_hashvalue = 0;
    int res_input = scanf ("%d", &max_hashvalue);

    ASSERT (res_input);

    HTEC (Delete_All_Except_Letters_And_Spaces_From_Input_File_Or_Simple_Delete_All_Punctuation (text, input));

    clock_t t_start = 0, t_finish = 0;

    #define TRY_HASH_( num )\
    {\
        printf ("Processing #%d hash function..\n", num);\
        output = fopen ("output-"#num".xls", "w");\
            HTEC (Hashtable_Construct (&hashtable, max_hashvalue));\
        t_start = clock();\
            HTEC (Hashtable_Fill (&hashtable, input, hash_##num));\
        t_finish = clock();\
        printf ("Time elapsed: %lg\n\n", (double) ((double) (t_finish) - (double) t_start)/CLOCKS_PER_SEC);\
            HTEC (Hashtable_Print (&hashtable, output));\
            HTEC (Hashtable_Destruct (&hashtable));\
        fclose (output);\
    }

    TRY_HASH_ (1);
    TRY_HASH_ (2);
    TRY_HASH_ (3);
    TRY_HASH_ (4);
    TRY_HASH_ (5);
    TRY_HASH_ (6);

    #undef TRY_HASH_

    fclose (log);
    fclose (input);
    fclose (text);

    return 0;
}

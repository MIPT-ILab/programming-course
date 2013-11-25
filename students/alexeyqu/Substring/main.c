/** ***************************************************************************
 * @file    main.c
 * @mainpage
 * @date    2013-10-06
 * @author  Alexey Kulikov <alexeyqu@gmail.com>, group 376, DCAM MIPT
 * @version 1.00
 *
 * Substring search
 *
 * @par     The task.
 *          The program gets 2 strings and demonstrates some functions
 *          that are identical to standart string.h functions
 *
 * @note    Realised functions:
 *          - get_str() gets a string from the input
 *          - str_cmp() compares 2 strings
 *          - sub_str() searches a substring
 *          - str_len() returns length of the string
 *          Return values are documented and usually are equal to standart ones from string.h
 *
 * @todo    - add some user-friendly interface
 *          - add some more string functions
 *          - add AI :)
******************************************************************************/

#include "Substring.h"

int main()
{
    printf ("Hello! This is a simple program without a high destination "
            "that can read 2 strings and demonstrates functions "
            "for operations with strings.\n");
    printf ("Please enter maximum length of string"
            "(it should be less than %d.\n-> ", MAXLEN);

    char *str_1 = NULL, *str_2 = NULL;
    int MaxLen = 0;
    int res_input = 0;

    res_input = scanf ("%d", &MaxLen);
    ASSERT (res_input); ASSERT ((MaxLen > 0)); ASSERT ((MaxLen < MAXLEN));
    getchar();

    str_1 = calloc (MaxLen, sizeof(char));
    str_2 = calloc (MaxLen, sizeof(char));

    ASSERT (str_1); ASSERT (str_2);

    printf ("Please enter 2 strings: \n");

    get_str (str_1, MaxLen);
    get_str (str_2, MaxLen);

    int mode = -1;

    printf ("-------------------------------------------------------------\n");    \
    printf ("Now you can command what to do: \n");                                 \
    printf ("1 - print lengths of strings\n");                                     \
    printf ("2 - print result of comparision of 2 strings\n");                     \
    printf ("3 - print first index where second string is a part of the first\n"); \
    printf ("0 - exit program\n");

    while (mode != 0)
    {
        printf ("What's your choice?\n");

        scanf ("%d", &mode);

        ASSERT ((mode >= 0)); ASSERT ((mode <= 3));

        if (mode == 1) printf ("Lengts of strings: %d %d\n", str_len (str_1), str_len (str_2));

        if (mode == 2) printf ("Result of comparision: %d\n", str_cmp (str_1, str_2, MaxLen));

        if (mode == 3) printf ("Substring search result: %d\n", sub_str (str_1, str_2, MaxLen));
    }

    printf ("Good bye!\n");

    return 0;
}

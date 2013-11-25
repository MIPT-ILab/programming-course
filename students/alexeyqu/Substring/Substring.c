#include "Substring.h"

int get_str (char* str, int MaxLen)
{
    ASSERT (str);

    DBG printf ("Enter string: ");

    int len = 0;
    char c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            break;
        }

        if (len >= MaxLen - 1)
        {
            printf ("You've reached maximum length of string. \n");
            printf ("Sorry, but the rest of the input will be considered" \
                        " as next values that you'll enter.\n");
            printf ("It is NOT guaranteed that the program will work correctly\n");

            break;
        }

        str[len++] = c;
    }

    str[len] = '\0';

    return len;
}

int str_cmp (char* str_1, char* str_2, int MaxLen)
{
    ASSERT (str_1); ASSERT (str_2);
    ASSERT ((str_1 != str_2));

    int i = 0;

    for (i = 0; ; i++)
    {
        ASSERT ((i < MaxLen));

        if (str_1[i] == '\0' && str_2[i] == '\0') return 0;
        if (str_1[i] != '\0' && str_2[i] == '\0') return 1;
        if (str_1[i] == '\0' && str_2[i] != '\0') return -1;

        if (str_1[i] == str_2[i]) continue;

        if (str_1[i] < str_2[i]) return -1;
        else return 1;
    }

    return 0;
}

int sub_str (char* haystack, char* needle, int MaxLen)
{
    ASSERT (haystack); ASSERT (needle); ASSERT ((haystack != needle));

    int i = 0, j = 0;
    int found = 0;

    for (i = 0; i <= str_len (haystack) - str_len (needle); i++)
    {
        ASSERT ((i < MaxLen));

        if (haystack[i] == needle[0])
        {
            found = 1;

            for (j = i; j - i < str_len (needle) - 1; j++)
            {
                ASSERT ((j < MaxLen));

                if (haystack[j] != needle[j - i]) {found = 0; break;}
            }

            if (found) return SUBSTRING (i);
        }
    }

    return NOT_A_SUBSTRING;
}

int str_len (char* str)
{
    ASSERT (str);

    int len = 0;

    while (str[len++] != '\0');

    return len;
}


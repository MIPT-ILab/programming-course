/** ***************************************************************************
 * @file    Misc.cpp
 *
 * @ingroup misc
******************************************************************************/

#include "Hash.h"

int Hashtable_Error_Catch (int error, const char* msg, ...)
{
    printf ("%s", msg);

    switch (error)
    {
        case ELEM_NULL:
            printf ("ELEM_NULL. The element wasn't initialised correctly!\n");
            getchar();
            return HT_ERR;

        case ELEM_NULL_KEY:
            printf ("ELEM_NULL_KEY. Key of element is NULL.. strange..\n");
            getchar();
            return HT_ERR;

        case ELEM_NOMEM:
            printf ("ELEM_NOMEM. Failed to allocate memory for an element!\n");
            getchar();
            return HT_ERR;

        case ELEM_WR_KEY_RANGE:
            printf ("ELEM_WR_KEY_RANGE. Wrong key size.\n");
            getchar();
            return HT_ERR;

        case LIST_NULL:
            printf ("LIST_NULL. The list wasn't initialised correctly!\n");
            getchar();
            return HT_ERR;

        case LIST_INV:
            printf ("LIST_INV. Your list is somehow invalid! Call the support.\n");
            getchar();
            return HT_ERR;

        case LIST_WR_NDX_RANGE:
            printf ("LIST_WR_NDX_RANGE. Wrong list index.\n");
            getchar();
            return HT_ERR;

        case HT_NULL:
            printf ("HT_NULL. The hashtable wasn't initialised correctly!\n");
            getchar();
            return HT_ERR;

        case HT_BAD_FILE:
            printf ("HT_BAD_FILE. The file for hashtable is invalid!\n");
            getchar();
            return HT_ERR;

        case HT_INV:
            printf ("HT_INV. Your hashtable is full of errors! Better to call the support.\n");
            getchar();
            return HT_ERR;

        case HT_WR_HV_RANGE:
            printf ("HT_WR_HV_RANGE. Wrong hashvalue range.\n");
            getchar();
            return HT_ERR;

        case HT_WR_INPUT:
            printf ("HT_WR_INPUT. Something is bad inside the input file..\n");
            getchar();
            return HT_ERR;
    }

    return HT_OK;
}

int Adapt_Input (FILE* input, FILE* output)
{
    if (input == NULL)
    {
        OUT (stdout, "Pointer to file is NULL.\n");
        return HT_BAD_FILE;
    }

    if (output == NULL)
    {
        OUT (stdout, "Pointer to file is NULL.\n");
        return HT_BAD_FILE;
    }

    fseek (input, 0, 0);
    fseek (output, 0, 0);

    char c = 0;
    int res_input = 0;

    while (1)
    {
        res_input = fscanf (input, "%c", &c);

        if (res_input == EOF)
        {
            break;
        }

        if (isalpha (c)) c = toupper (c);

        if (isalpha (c) || isdigit (c) || isspace (c)) fprintf (output, "%c", c);
    }

    return HT_OK;
}

int ROL (int arg, int shift)
{
    return (arg << shift) | (arg >> (sizeof(arg)*sizeof (int) - shift));;
}

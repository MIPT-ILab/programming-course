#include "Hash.h"

int Delete_All_Except_Letters_And_Spaces_From_Input_File_Or_Simple_Delete_All_Punctuation (FILE* input, FILE* output)
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

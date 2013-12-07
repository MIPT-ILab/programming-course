#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

enum TOKEN_TYPES
{
    NUMBER_TOKEN = 1,
    REG_TOKEN = 2,
    OP_TOKEN = 3
};

struct token_t
{
    //short int token_type;
    char *data;
};

typedef struct
{
    token_t **token;
    int array_size;
} token_array_t;

token_t *token_constructor ()
{
    token_t* ret_token = (token_t *)calloc (1, sizeof (token_t));
//    ret_token->token_type = 0;
    ret_token->data = NULL;
    return ret_token;
}

void token_destructor (token_t *token_to_destruct)
{
    assert (token_to_destruct != NULL);

    if (token_to_destruct->data != NULL)
        free (token_to_destruct->data);
    token_to_destruct->data = NULL;

//    token_to_destruct->token_type = -666;

    free (token_to_destruct);
    token_to_destruct = NULL;
}

void token_array_destructor (token_array_t *token_array_to_destruct)
{
    assert (token_array_to_destruct != NULL);

    for (register unsigned i=0; i<token_array_to_destruct->array_size; i++)
        token_destructor (token_array_to_destruct->token[i]);

    free (token_array_to_destruct->token);
    token_array_to_destruct->token = NULL;

    token_array_to_destruct->array_size = -666;

    free (token_array_to_destruct);
    token_array_to_destruct = NULL;
}

token_array_t *token_array_constructor (const char expression[])
{
    int expression_size = 0;
    for (; expression[expression_size] != '#'; expression_size++);

    token_array_t* ret_token_array = (token_array_t *)calloc (expression_size-1, sizeof (token_array_t));

    register int i = 0;

    char *buffer = calloc(expression_size-1, sizeof(char)),
          search_state = 0;

    unsigned buffer_size = 0;

    while (i++ < expression_size)
    {
         switch (search_state)
         {
            case 0:
            {
                if (!('0' < expression[i] && expression[i] < '9'))
                {

                }

                buffer[buffer_size++] =
            }
            case 1:
            {
            }
         }
    }

}


int main()
{
    char *a = "hello world#";
    char *b = strdup(a);
    printf ("%s %s",a,b);
    return 0;
}

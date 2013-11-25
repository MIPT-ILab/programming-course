/** ***************************************************************************
 * @file    Stack_functions.cpp
******************************************************************************/

#include "CPU.h"

int Stack_Construct (Stack_t* stack)
{
    assert (stack);

    stack->max_size = Start_Max_Size;
    stack->cur_size = 0;
    stack->my_stack_data = (double* ) calloc (stack->max_size, sizeof (double));

    assert (stack->my_stack_data != NULL);

    STACK_CHECK (stack);

    return STACK_OK;
}

int Stack_Destruct (Stack_t* stack)
{
    STACK_CHECK (stack);

    register unsigned int i = 0;

    for (i = 0; i < stack->max_size; i++)
    {
        stack->my_stack_data[i] = Poison;
    }

    free (stack->my_stack_data);
    stack->my_stack_data = NULL;
    stack->cur_size = Poison;
    stack->max_size = Poison;

    return STACK_OK;
}

int Stack_Is_Empty (const Stack_t* stack)
{
    STACK_CHECK (stack);

    return (stack->cur_size == 0);
}

int Stack_Is_Full (const Stack_t* stack)
{
    STACK_CHECK (stack);

    return (stack->cur_size == stack->max_size);
}

int Stack_Is_OK (const Stack_t* stack)
{
    if (stack == NULL) return STACK_ERR_NULL;
    if (stack->my_stack_data == NULL) return STACK_ERR_INIT;

    return (stack->cur_size >= 0 &&
            stack->cur_size <= stack->max_size)? STACK_OK : STACK_ERR_WR_SZ;
}

int Need_More_Memory (Stack_t* stack)
{
    STACK_CHECK (stack);

    register unsigned int i = 0;

    stack->max_size *= 2;
    double* more_data = (double* ) realloc (stack->my_stack_data,
                                 stack->max_size * sizeof (double));

    for (i = stack->cur_size + 1; i < stack->max_size; i++)
    {
        more_data[i] = 0;
    }

    assert (more_data);

    stack->my_stack_data = more_data;

    STACK_CHECK (stack);

    return 0;
}

int Stack_Push (Stack_t* stack, const double value)
{
    STACK_CHECK (stack);

    if (Stack_Is_Full (stack))
    {
        Need_More_Memory (stack);
    }

    stack->my_stack_data[stack->cur_size++] = value;

    STACK_CHECK (stack);

    return 0;
}

double Stack_Pop (Stack_t* stack)
{
    double value;

    STACK_CHECK (stack);

    if (Stack_Is_Empty (stack))
    {
        assert (!"You tried to pop from an empty stack. Life is cruel, bro. Bye.");
    }

    value = stack->my_stack_data[--stack->cur_size];

    STACK_CHECK (stack);

    return value;
}

void Stack_Dump (const Stack_t* stack)
{
    printf ("Stack_Dump.\n");
    printf ("Stack [%08x] %s \n", (int) stack, (Stack_Is_OK (stack))? "ok" : "ERROR!");

    printf ("\t -maxsize = %d\n", stack->max_size);
    printf ("\t -size = %d\n", stack->cur_size);
    printf ("\t -empty = %d\n", Stack_Is_Empty (stack));
    printf ("\t -full = %d\n", Stack_Is_Full (stack));

    if (stack->my_stack_data == NULL) return;

    register unsigned int i = 0;

    for (i = 0; i < stack->max_size; i++)
    {
        printf ("\t -data[%d] = %lg %c\n", i, stack->my_stack_data[i], (i < stack->cur_size)? '*' : ' ');
    }

    printf ("Stack_Dump finished.\n");
}

int Stack_Error_Catch (int err_code, const char* msg, ...)
{
    printf ("%s", msg);

    switch (err_code)
    {
        case STACK_ERR_INIT:
            printf ("An error occured! You stack hasn't been initialized correctly.\n");
            return STACK_ERR;

        case STACK_ERR_NULL:
            printf ("An error occured! Pointer to your stack is NULL.\n");
            return STACK_ERR;

        case STACK_ERR_WR_SZ:
            va_list args;
            va_start (args, msg);
            printf ("An error occured! You're addressing to a wrong element of stack.\n");
            printf ("MAXSIZE = %d, \tSIZE = %d\n", va_arg (args, int), va_arg (args, int));
            return STACK_ERR;
    }

    return STACK_OK;
}

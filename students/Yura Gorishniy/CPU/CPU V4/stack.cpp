#include "cpu.h"

stack* Stack_Construct (int stack_size)
{
    stack* new_stack = (stack*) calloc (1, sizeof(stack));
    new_stack -> data = (double*)  calloc (stack_size, sizeof(double));
    new_stack -> size_now = 0;
    new_stack -> max_size = stack_size;

return new_stack;
}




void Stack_Destruct (stack* my_stack)
{
    if (!my_stack) OUT printf ("\n" "You haven't created a stack!\n\n");
    else
    {
        my_stack -> size_now = -1;

        int i = 0;

        for (i = 0; i < my_stack -> max_size; ++i)
        {
            ASSERT (0 <= i && i < my_stack -> max_size);
            my_stack -> data[i] = POiSON; 
        }

        free (my_stack -> data);
        free (my_stack);
    }
}




int Stack_OK (const stack* the_stack)
{
    return  (  the_stack != NULL
            && the_stack -> size_now >= 0
            && the_stack -> size_now <= the_stack -> max_size - 1
            && the_stack -> data != NULL) ?
    1 : 0;
}




void Stack_Dump (stack* the_stack, FILE* my_log)
{
    if (!the_stack)
    {
        OUT fprintf (my_log, "\n" "You haven't created a stack!\n");
    }

    else
    {
        if (Stack_OK (the_stack))         fprintf (my_log, "\n" "Your stack [%.8x] is ok\n\n",     the_stack);
        else                              fprintf (my_log, "\n" "Your stack [%.8x] is NOT ok\n\n", the_stack);

        fprintf (my_log, "max_size = %d\n" "size_now = %d\n\n", the_stack -> max_size, the_stack -> size_now);

        int i = 0;
        for (i = 0; i < the_stack -> max_size; ++i)
        {
            fprintf (my_log, "data[%d] = %lg", i, the_stack -> data[i]);
            fprintf (my_log, i < the_stack -> size_now ? " *\n" : "\n");
        }

        fprintf (my_log, "\n\n");
    }
}




int Stack_Full (stack* the_stack)
{
    ASSERT_STACK_OK (the_stack);
    return (the_stack -> size_now == the_stack -> max_size) ? 1 : 0;
}




int Stack_Empty (stack* the_stack)
{
    ASSERT_STACK_OK (the_stack);
    return (the_stack -> size_now == 0) ? 1 : 0;
}




int Stack_Push (stack* the_stack, double item)
{
    if (Stack_OK  (the_stack))
    {
        if (   0 <= the_stack -> size_now
                    && the_stack -> size_now <= the_stack -> max_size - 1)
        {
            the_stack -> data[the_stack -> size_now] = item;
            the_stack -> size_now += 1;

            ASSERT_STACK_OK (the_stack);

            return HAPPY;
        }

        else return ERR_STACK_PUSH;
    }

    else return ERR_STACK_FAIL;
}




int Stack_Pop (stack* the_stack, double* pop)
{
    ASSERT_STACK_OK (the_stack);

    if (the_stack -> size_now > 0)
    {
        ASSERT (   0 <= the_stack -> size_now - 1
                && the_stack -> size_now <= the_stack -> max_size);

        *pop = the_stack -> data[the_stack -> size_now - 1];


        ASSERT (   0 <= the_stack -> size_now - 1
                && the_stack -> size_now <= the_stack -> max_size);

        the_stack -> data[the_stack -> size_now - 1] = 0;


        the_stack -> size_now -= 1;

        ASSERT_STACK_OK (the_stack);

        return HAPPY;
    }

     else
    {
        return ERR_STACK_POP;
    }
}

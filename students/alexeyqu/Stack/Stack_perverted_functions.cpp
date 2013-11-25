/** ***************************************************************************
 * @file    Stack_perverted_functions.cpp
******************************************************************************/

#include "Stack.h"

int Stack_Perverted_Push (Stack_t* stack, const double value)
{
    STACK_CHECK (stack);

    if (Stack_Is_Full (stack))
    {
        Need_More_Memory (stack);
    }

    if (stack->cur_size == 0)
    {
        Stack_Push (stack, value);

        STACK_CHECK (stack);

        return 0;
    }

    Stack_t stack_2 = {}, stack_3 = {};

    Stack_Construct (&stack_2);
    Stack_Construct (&stack_3);

    Stack_Space_Cpy (stack, &stack_2);
    Stack_Space_Cpy (stack, &stack_3);

    assert (Stack_Is_OK (&stack_2));
    assert (Stack_Is_OK (&stack_3));

    Tower_Move (stack, &stack_2, &stack_3, stack->cur_size);

    Stack_Push (stack, value);

    Tower_Move (&stack_2, stack, &stack_3, stack_2.cur_size);

    STACK_CHECK (stack);

    Stack_Destruct (&stack_2);
    Stack_Destruct (&stack_3);

    return 0;
}

int Stack_Perverted_Pop (Stack_t* stack, double* value)
{
    STACK_CHECK (stack);

    if (Stack_Is_Empty (stack)) return 1;

    if (stack->cur_size == 1)
    {
        *value = stack->my_stack_data[--stack->cur_size];

        STACK_CHECK (stack);

        return 0;
    }

    Stack_t stack_2 = {}, stack_3 = {};

    Stack_Construct (&stack_2);
    Stack_Construct (&stack_3);

    Stack_Space_Cpy (stack, &stack_2);
    Stack_Space_Cpy (stack, &stack_3);

    assert (Stack_Is_OK (&stack_2));
    assert (Stack_Is_OK (&stack_3));

    Tower_Move (stack, &stack_2, &stack_3, stack->cur_size - 1);

    Stack_Pop (stack, value);

    Tower_Move (&stack_2, stack, &stack_3, stack_2.cur_size);

    STACK_CHECK (stack);

    Stack_Destruct (&stack_2);
    Stack_Destruct (&stack_3);

    return 0;
}

void Stack_Space_Cpy (const Stack_t* from, Stack_t* to)
{
    STACK_CHECK (from);
    STACK_CHECK (to);

    to->isenable = from->isenable;
    to->max_size = from->max_size;
    to->my_stack_data = (double* ) realloc (to->my_stack_data, to->max_size * sizeof (double));

    STACK_CHECK (from);
    STACK_CHECK (to);
}

void Tower_Move (Stack_t* from_stack, Stack_t* to_stack, Stack_t* temp_stack,
                const int num_left)
{
    STACK_CHECK (from_stack);
    STACK_CHECK (to_stack);
    STACK_CHECK (temp_stack);

    if (num_left == 1)
    {
        to_stack->my_stack_data[to_stack->cur_size++] = from_stack->my_stack_data[--from_stack->cur_size];
        return;
    }

    Tower_Move (from_stack, temp_stack, to_stack, num_left - 1);

    to_stack->my_stack_data[to_stack->cur_size++] = from_stack->my_stack_data[--from_stack->cur_size];

    Tower_Move (temp_stack, to_stack, from_stack, num_left - 1);

    STACK_CHECK (from_stack);
    STACK_CHECK (to_stack);
    STACK_CHECK (temp_stack);
}


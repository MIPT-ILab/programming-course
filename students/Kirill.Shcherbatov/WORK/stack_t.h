//{==================================================================================================
//! @file "stack_t.h"
//! @date 2013-11-09
//! @mainpage Stack prototype
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#include <stdlib.h>
//----------------------------------------------------------------------------------------------------
#include "debug_defines.h"
//****************************************************************************************************

struct stack_t
{
    double             *data;
    int                 max_size,
                        cure_size;
};

struct stack_t* stack_constructor (const int target_size_to_create)
{
   	OUT ("# called stack constructor.\n");
    RETURN_ASSERT (target_size_to_create > 0, 0);

   	struct stack_t* target_stack = NULL;
   	target_stack = (stack_t*) calloc (1, sizeof (stack_t));
   	RETURN_ASSERT (target_stack != NULL, 0);

    target_stack -> data = NULL;
    target_stack -> data = (double*) calloc (target_size_to_create, sizeof (double));
    RETURN_ASSERT (target_stack -> data != NULL, 0);

    target_stack -> max_size = target_size_to_create;
    target_stack -> cure_size = 0;

    return target_stack;
}

short int stack_destructor (struct stack_t *target_stack)
{
    OUT ("#  called stack [ %p ] destructor\n", target_stack -> data);
    RETURN_ASSERT (target_stack != NULL, -1);

    const short int POISON = -666;

    for (register int  i = 0; i < (target_stack -> max_size); i++)
        target_stack -> data [i] = POISON;

    target_stack -> cure_size = POISON;
    target_stack -> max_size  = POISON;

    free (target_stack -> data);
    target_stack -> data = NULL;

	free (target_stack);
	target_stack = NULL;

    return 0;
}

short int stack_is_ok (const struct stack_t *target_stack)
{
    OUT ("#  called stack is ok\n");
    RETURN_ASSERT (target_stack != NULL, -1);

    return ((target_stack != NULL)
            &&
            (target_stack -> data != NULL)
            &&
            (target_stack -> cure_size >= 0)
            &&
            (target_stack -> cure_size <= target_stack -> max_size)
           );
}

short int stack_dump (const struct stack_t *target_stack, FILE *out_stream)
{
	OUT ("#  called stack_dump\n");
	RETURN_ASSERT (target_stack != NULL, -1);
	RETURN_ASSERT (out_stream != NULL, -1);

    fprintf (out_stream, "#> BEGIN STACK DUMP REPORT\n");
    fprintf (out_stream, "#> Stack [ %p ] data [ %p ] is %s\n", (target_stack),
                (target_stack -> data), stack_is_ok (target_stack) ? "OK." : "BAD!");

    fprintf (out_stream, "#> Max size is %d\n", target_stack -> max_size);
    fprintf (out_stream, "#> Cure size is %d\n", target_stack -> cure_size);
    fprintf (out_stream, "#> Stack memory map:\n");

    register int i = 0;
    for (; i < target_stack -> cure_size; i++)
        fprintf (out_stream, "#> stack -> data [%d] = %lg (*)\n", i, target_stack -> data[i]);

    for (; i < target_stack -> max_size; i++)
        fprintf (out_stream, "#> stack -> data [%d] = %lg\n", i, target_stack -> data[i]);

    fprintf (out_stream, "#> END STACK DUMP REPORT\n");
    return 0;
}

short int memory_dump (const struct stack_t *target_memory, FILE *out_stream)
{
	OUT ("#  called memory_dump\n");
	RETURN_ASSERT (target_memory != NULL, -1);
    RETURN_ASSERT (out_stream != NULL, -1);

    fprintf (out_stream, "#> BEGIN MEMORY DUMP REPORT\n");
    fprintf (out_stream, "#> Memory [ %p ] data [ %p ] is %s\n", (target_memory), (target_memory -> data), stack_is_ok (target_memory) ? "OK." : "BAD!");
    fprintf (out_stream, "#> Max size is %d\n", target_memory -> max_size);
    fprintf (out_stream, "#> Cure size is %d\n", target_memory -> cure_size);
    fprintf (out_stream, "#> Memory map:\n");

    for (register int i = 0; i < target_memory -> cure_size; i++)
        fprintf (out_stream, "%lg ", target_memory -> data[i]);

    fprintf (out_stream, "\n"
                         "#> END MEMORY DUMP REPORT\n");

    return 0;
}

short int stack_is_empty (const struct stack_t *target_stack)
{
	OUT ("#  called stack_is_empty\n");
	RETURN_ASSERT (target_stack != NULL, -1);

    return ( target_stack -> cure_size  ==  0);
}

short int stack_is_full (const struct stack_t *target_stack)
{
	OUT ("#  called stack_is_full\n");
	RETURN_ASSERT (target_stack != NULL, -1);

    return ( target_stack -> cure_size  ==  target_stack -> max_size);
}

short int stack_push (struct stack_t *target_stack, const double value)
{
	OUT ("#  called stack_push with stack [ %p ] and value [ %lg ]\n", target_stack -> data, value);

	RETURN_ASSERT (target_stack != NULL, -1);
    RETURN_ASSERT (stack_is_ok (target_stack) == 1, -1);
    RETURN_ASSERT (stack_is_full (target_stack) == 0, -1);

    target_stack -> data[(target_stack -> cure_size)++] = value;
    RETURN_ASSERT (stack_is_ok (target_stack) == 1, -1);

    return 0;
}

short int stack_pop (struct stack_t *target_stack, double *target_place)
{
	OUT ("#  called stack_pop with stack [ %p ]\n", target_stack -> data);
    RETURN_ASSERT (target_stack != NULL, -1);
    RETURN_ASSERT (target_place != NULL, -1);
    RETURN_ASSERT (stack_is_ok (target_stack) == 1, -1);
    RETURN_ASSERT (stack_is_empty (target_stack) == 0, -1);

    *target_place  =  target_stack -> data[--(target_stack -> cure_size)];
    RETURN_ASSERT (stack_is_ok (target_stack) == 1, -1);

    return 0;
}

#undef OUT
#undef RETURN_ASSERT

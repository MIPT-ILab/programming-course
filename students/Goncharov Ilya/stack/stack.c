//{=================================================================================
//! @file    stack.c
//! @date    2013-11-02 11:50
//! @author  Ilya Goncharov <ilgonmic@gmail.ru>
//!
//! Polish calculator
//!
//! @par     Conditions
//!          User enter command into calculator
//!          Command:
//!          HELP or help - call help
//!          push x - push x into stack
//!          add - add two numbers on stack
//!          mul - multiply two numbers
//!          q - quit
//}=================================================================================

#include <stdio.h>
#include <string.h>

#define SIZE 10
#define WRONG Something goes wrong\n
#define DEFHELP For help enter HELP\n

typedef double elem_t;

struct Stack_t
{
    int count;
    elem_t data[SIZE];
};

int stack_constract   (struct Stack_t* st);
int stack_ok          (struct Stack_t* st);
void stack_dump       (struct Stack_t* st);
int stack_push        (struct Stack_t* st, elem_t val);
elem_t stack_pop      (struct Stack_t* st);

int main()
{
    struct   Stack_t st;
    char     command[10];
    int      i;
    elem_t   x, a, b;

    stack_constract(&st);

    printf("# Hello, it is polish calculator, for help entered HELP, for quit enter q\n");

    while (1)
    {
        scanf("%s", command);

        if ( (strcmp(command, "HELP") == 0) || (strcmp(command, "help") == 0) )
        {
            printf("# Stack of this calculator have only 10 slots for number\n");
            printf("# For put to stack enter 'push ...'\n");
            printf("# For add two numbers enter 'add'\n");
            printf("# For multiply two numbers enter 'mul'\n");
            printf("# For exit enter 'q'\n");
        }

        else if ( strcmp(command, "push") == 0 )
        {
            scanf("%lg", &x);
            stack_push(&st, x);
        }

        else if ( strcmp(command, "add") == 0 )
        {
            if ( st.count > 1 )
            {
                a = stack_pop(&st);
                b = stack_pop(&st);
                stack_push(&st, a+b);
            }
            else
                printf("# Sorry, but too low number in stack\n# For help enter HELP\n");
        }

        else if (strcmp(command, "mul") == 0)
        {
            if (st.count > 1)
            {
                a = stack_pop(&st);
                b = stack_pop(&st);
                stack_push(&st, a*b);
            }
            else
                printf("# Sorry, but too low number in stack\n# For help enter HELP\n");
        }

        else if (strcmp(command, "q") == 0 )
            break;

        else
            printf("# Sorry, it's non-existent command\n# For help enter HELP\n");


        if(st.count > 0)
        {
            printf("Stack:\n");
            for (i = 0; i < st.count; i++)
                printf("%lg ", st.data[i]);
            printf("\n");
        }

    }

    return 0;
}

int stack_constract(struct Stack_t* st)
{
    st->count = 0;
    return 1;

}

int stack_ok (struct Stack_t* st)
{
    return ((0 <= st->count) && (st->count <= SIZE));
}

void stack_dump (struct Stack_t* st)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%lg", st->data[i]);
        if (i < st->count)
            printf("*");
        printf("\n");
    }
}

int stack_push (struct Stack_t* st, elem_t val)
{
    if (st->count >= SIZE)
    {
        printf("# Sorry, but stack is overflown\n# For help enter HELP\n");
        return 0;
    }
    else
    {
        st->data[(st->count)++] = val;
        if (stack_ok)
            return 1;
        else
            printf("# Something goes wrong\n# For help enter HELP\n");
    }
}

elem_t stack_pop (struct Stack_t* st)
{
    elem_t s;
    if (stack_ok)
    {
        s = st->data[--(st->count)];
        st->data[(st->count)] = 0;
        if (stack_ok)
        {
            return s;
        }
        else
            printf("# Something goes wrong\n# For help enter HELP\n");
    }
    else
        printf ("# Something goes wrong\n# For help enter HELP\n");
}

//{=================================================================================
//! @file    CPU.c
//! @date    2013-11-02 1:15
//! @author  Ilya Goncharov <ilgonmic@gmail.ru>
//!
//! CPU
//!
//! @par     Conditions
//!          We open program from file
//!          Program print table of square of number
//!          Program is result of assembler's job
//}=================================================================================

#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef int elem_t;

enum {end, push, mul, add, push_ax};

struct Stack_t
{
    int count;
    elem_t data[SIZE];
};

struct CPU
{
    struct Stack_t st; //stack
    elem_t ax; //register
};

int stack_constract   (struct Stack_t* st);
int stack_ok          (struct Stack_t* st);
void stack_dump       (struct Stack_t* st);
int stack_push        (struct Stack_t* st, elem_t val);
elem_t stack_pop      (struct Stack_t* st);

int CPU_run (char prog[], struct CPU* my_cpu);
int CPU_mov_ax(elem_t x, struct CPU* my_cpu);

int main()
{
    struct   Stack_t st;
    struct   CPU my_cpu;
    elem_t x = -10;

    stack_constract(&st);
    my_cpu.st = st;
    my_cpu.ax = 0;

    for (x = -10; x <= 10; x++)
    {
        printf("%3d ", x);
        CPU_mov_ax(x, &my_cpu);
        CPU_run ("prog.txt", &my_cpu);
        printf("\n");
    }

    return 0;
}

//{=================================================================================
//! CPU_run - run program on CPU.
//!
//! @param  prog[]   way to file
//! @param  my_cpu   addres to structure of our CPU
//!
//! @return         0, if all is OK
//!
//! @note           Print square of number in register
//}=================================================================================

int CPU_run (char prog[], struct CPU* my_cpu)
{
    int     command;
    int      i;
    elem_t   x, a, b;
    FILE* reading = fopen(prog, "r");
    do
    {
        fscanf(reading, "%d", &command);
        switch (command)
        {
        case push:
            if (fscanf(reading, "%d", &x) == 1)
                stack_push(&(*my_cpu).st, x);
            break;
        case add:
            if ( (my_cpu->st).count > 1 )
            {
                a = stack_pop(&(*my_cpu).st);
                b = stack_pop(&(*my_cpu).st);
                stack_push(&(*my_cpu).st, a+b);
            }
            else
                printf("Something went wrong\n");
            break;
        case mul:
            if ((my_cpu->st).count > 1)
            {
                a = stack_pop(&(*my_cpu).st);
                b = stack_pop(&(*my_cpu).st);
                stack_push(&(*my_cpu).st, a*b);
            }
            else
                printf("Something went wrong\n");
            break;
        case push_ax:
            stack_push(&(*my_cpu).st, my_cpu->ax);
            break;

        }

    }
    while(command != 0);
    printf("%d ", stack_pop(&(*my_cpu).st));
    return 0;
}


//{=================================================================================
//! CPU_mov_ax - move element in register
//!
//! @param  x   element
//! @param  my_cpu   addres to structure of our CPU
//!
//! @return         0, if all is OK
//}=================================================================================
int CPU_mov_ax(elem_t x, struct CPU* my_cpu)
{
    my_cpu -> ax = x;
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
        printf("# Sorry, but stack is overflown\n");
        return 0;
    }
    else
    {
        st->data[(st->count)++] = val;
        if (stack_ok)
            return 1;
        else
            printf("# Something goes wrong\n");
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
            printf("# Something goes wrong\n");
    }
    else
        printf ("# Something goes wrong\n");
}

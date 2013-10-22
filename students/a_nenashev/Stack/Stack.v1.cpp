/** ****************************************************************
 @file stack_[ver].cpp
 @author ALex Nenashev <a.nenash95@gmail.com>
 @date 12-10-2013 20:39

 @param Stack functions realisation
 @param Included files: stack.h, stack_fun.cpp

 @return 0 if ok, -1, 1 if smth wrong

********************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

/** *********************************************************************
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Defines~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* CHECK_STACK print&break if ptr->user_stack == 0
*
* MAXLINE = 50
*
* typedef struct Stack_t
* @par      maxsize     max size of stack
* @par      data        data array, all elements are outside.
* @par      dsize       current stack size
*
* const char *COMMANDS[6] - Constant massive of commands, lying in particular order.
*
*************************************************************************/

typedef struct{
    int maxsize;            //!<  Max size of data
    int dsize;              //!<  Number of element
    double data[1];         //!<  the data, every element is outside the structure!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
} Stack_t;

#define MAXLINE 50

#define POISON -0x548

#define DEADMEM 0xDEAD

const char *COMMANDS[6] = {"Create", "Pop", "Push", "Dump", "Kill", "Quit"};

// ////////////////////////////////////////////////////////////////////////
/** ***********************************************************************
* @name stack_ok
*
* @par [in]     Stack
* @par [out]    Big bull test, ptr != 0 and dsize & maxsize in right values
***************************************************************************/

int stack_ok(Stack_t *user_stack);

/** ***********************************************************************
* @name Stack_construct
*
* @par [in]     number of elements in new stack
* @par [out]    New ready empty stack
***************************************************************************/

Stack_t *stack_construct(int num);

/** ***********************************************************************
* @name stack_dump
*
* @par [in]     Stack
* @par [out]    Prints everything about stack, it's elements and so on
***************************************************************************/

int stack_dump(Stack_t *st);

/** ***********************************************************************
* @name stack_push
*
* @par [in]     Num for pushing and stack with(without) free place
* @par [out]    Pushes num into it's place(creates x3 more place if needed)
***************************************************************************/

int stack_push(int push, Stack_t *box_stack);

/** ***********************************************************************
* @name Stack_pop
* Popping stack's top. Pops only if dsize > 0
* @par [in]     Stack
* @par [out]    Zero
***************************************************************************/

int stack_pop(Stack_t *user_stack);

/** ***********************************************************************
* @name enlarge_stack
* Gives more memory for out-stack's massive of DATA(Works with Stack_push)
* @par [in]     massive
* @par [out]    Creates x3 more place
***************************************************************************/

int enlarge_stack(Stack_t *st);

/** ***********************************************************************
* @name setmem
*
* @par [in]     Stack and number, that will be setted into all massive cells
* @par [out]    Stack with setted memory
***************************************************************************/

void setmem(Stack_t *st, double num);

/** ***********************************************************************
* @name do_stack
* Control program
* @par [in]     Number of command
* @par [out]    Comm
***************************************************************************/

int do_stack(int comm);

// ////////////////////////////////////////////////////////////////////////

int Check_stack(Stack_t *st)
{
    if (st->dsize > st->maxsize)printf("\n################\nCheck stack - dsize BAD!!!\n################\n");
    if (st->dsize < 0) printf("\n################\nDsize < 0!!!!!!!!!!!\n################\n\n");
    return 0;
}


int stack_ok(Stack_t *user_stack)
{
    return (user_stack && 0 <= user_stack -> dsize && user_stack -> dsize <= user_stack -> maxsize);
}

// ////////////////////////////////////////////////////////////////////////

/**
* StackSys()
* Co-control program
**/

int StackSys();

// ////////////////////////////////////////////////////////////////////////

int main()
{
        printf(     "It's a program by Alex Nenashev\n"
                                "Compiled in %s, %s, in file %s\n"
                                "Stack imitation program\n\n\n////////////////////////////////////////\n\n>>>",\
                                 __TIME__, __DATE__, __FILE__);

        StackSys();
        printf("\nBye!\n\n");
        return 0;
}


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


void setmem(Stack_t *st, double num)
{
    int j = 0;
    for( ; j < st -> maxsize; j++)
    {
        st -> data[j] = num;
    }
}

Stack_t *stack_construct(int num)
{
    Stack_t *user_stack;
    //CHECK_STACK(user_stack);


    user_stack = (Stack_t *)calloc(num+1, sizeof(double));


    assert(user_stack);
    setmem(user_stack, POISON);
    user_stack->maxsize = num;
    user_stack->dsize = 0;
    return user_stack;
}

int stack_destruct(Stack_t *st)
{
    stack_ok(st);
    setmem(st, DEADMEM);
    free(st->data);
    st->dsize = 0;
    st->maxsize = -1;

}

int stack_dump(Stack_t *st)
{
    Check_stack(st);
    printf("\n//////////////////////Stack-dump//////////////////////\t//%s", (stack_ok(st))? ("ok") : ("STACK IS BAD!!!!!!!!"));
    int i = 0;
    printf("\nData Size - %d\nMax Size - %d\n", st -> dsize, st -> maxsize);
    for ( ; i < st -> maxsize; i++)
    {
        printf("data[%d] - %lf", i, st->data[i]);
        if (i < st -> dsize) printf(" (*)");
        printf("\n");
    }
    return i;
}

int stack_push(double push, Stack_t *st)
{
    assert(st);
    if (!stack_ok(st)) printf("Stack ISN't OK!!!!\n\n");
    //CHECK_STACK(st);
    st->data[st->dsize] = push;
    st->dsize += 1;
    return 0;
}

int stack_pop(Stack_t *user_stack)
{
    if (!stack_ok(user_stack)) printf("Stack ISN'T OK!!!!\n\n");
    assert(user_stack);
    //CHECK_STACK(user_stack);
    if (user_stack->dsize == 0)
    {
        printf("You can't pop the top, stack is empty!\n\n");
    }
    else
    {
    user_stack->dsize -= 1;
    user_stack->data[user_stack->dsize] = POISON;
    printf("# Popped.\n\n");
    }
    return 0;
}

int enlarge_stack(Stack_t *st)
{
    printf("Enlarge!!!\n\n");
    int i = 0;
    Stack_t *dump = st;
    st->maxsize = st->maxsize * 3;
    st = (Stack_t *)calloc(st->maxsize + 1,sizeof(double));
    setmem(st, POISON);
    for ( ; i < st -> dsize; i++)
    {
        (st->data)[i] = dump->data[i];
    }

    st -> dsize = dump->dsize;
    return 0;
}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


int StackSys()
{
    int comm = -1;
    printf("Welcome!\n"
        "Here are some commands to work with stack: \n\"Create\" - Create new stack\n\"Pop\" - delete element\n\"Push\" - Push new element on top\n"
        "\"Dump\" - Print all\n\"Kill\" - Destruct all\n\"Exit\" - End looking through monitor\n\n>>>");
    while(comm != 5)
    {
        comm = do_stack(comm);
    }
    return 0;
}

int do_stack(int comm)
{
    comm = -1;
    char s[MAXLINE];
    printf(">>> ");                    //!< char command massive
    scanf("%50s", s);
    assert(s);
    int i = 0;
    printf("%s =", s);
    for( ; i < 6; i++)
    {
        if (!strcmp(s, COMMANDS[i])) comm = i;
    }
    printf(" %d\n\n", comm);

    if (comm < 0 || comm > 5 ) comm = -1;


    Stack_t *user_stack;

    switch (comm)
    {
        case 0://!< Create
        {
            int num = 0;

            printf("# Enter num of elements: ");
            scanf("%d",&num);

            if (num < 1)
            {
                printf("Num must be more than zero!\n\nTry again\n\n");
                break;
            }

            user_stack = stack_construct(num);
            //CHECK_STACK(user_stack);

            printf("# Stack created!\n\n");
            break;
        }
        case 1://!< Pop
        {
            //CHECK_STACK(user_stack);
            printf("# Popping...\n\n");
            stack_pop(user_stack);
            break;
        }

        case 2://!<  Push
        {
            double push = -66.6;
            printf("Enter element: ");
            scanf("%lf", &push);

            if (push == POISON)
            {
                printf("Why do you use POISON?!\n");
                //assert(!"Push failed!!!");
            }
            if (user_stack->dsize == user_stack->maxsize)
            {
                enlarge_stack(user_stack);
            }

            stack_push(push, user_stack);

            printf("# %lf pushed in stack\n\n", push);
            break;
        }

        case 3://!< Dump
        {
            stack_dump(user_stack);
            printf("\n");
            break;
        }

        case 4://!< Destruct
        {
            stack_destruct(user_stack);
            printf("# Nothing to enter in stack\n\nThere is no stack at all.\n\n");
            break;
        }

        case 5://!< Exit
        {
            printf("# Exit.\n\n");
            return 5;
            break;
        }
        default:
            printf("# Let's retry! Incorrect command.\n\n");

    }
    return comm;
}


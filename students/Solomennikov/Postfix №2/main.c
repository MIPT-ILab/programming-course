//{=================================================================================
//! @file    Stack.cpp
//! @date    2013-10-25 23:10
//! @author  Solomennikov Semen, 999solom.s.v.999@gmail.com
//!
//! Calculating expression in Reverse Polish Notation
//!
//! @par     Condition of the task:
//!          We enter expression in Reverse Polish Notation. Program should print
//!          solution of it.
//!
//! @warning Math!
//}=================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Making the stack.
typedef struct stack
{
    double *data;
    int last;
    int data_size;

} stack_t;


//Check the stack.
int stack_ok(const stack_t *stack)
{
    return (stack && stack -> last >= 0 && stack -> last <= stack -> data_size);
}

//Print nessesary fakts about the program and the stack.
stack_t* dump_stack(const stack_t *stack)
{
    int i=0;

    printf("Options of the stack and the programm:\n");
    printf("%s\n%s\n%s\n",__TIME__,__DATE__,__FILE__);
    printf("last = %i\n",stack -> last);
    printf("data_size = %i\n",stack -> data_size);

    for (i = 0 ; i < stack -> data_size ; i++)
    {
        printf("data[%i] = %lg\n", i,stack -> data[i]);
    }
    return 0;
}

//Constructor of the stack, which allocate memory for it.
stack_t* cons_stack(int initial_size)
{
    stack_t *stack = (stack_t*) malloc(sizeof(stack_t));

    stack -> data_size = initial_size;

    if (stack -> data_size <= 0)
    stack -> data_size = 10;

    stack -> last = 0;

    stack -> data = (double*) malloc(sizeof(double)*stack -> data_size);

    return stack;
}

//Destructor of the stack, which free memory.
void dest_stack(stack_t *stack)
{
    free(stack -> data);
    free(stack);
}

//push element into stack. May allocate memory for it.
void push(stack_t *stack, double a)
{
    assert(stack_ok(stack));

    if ( stack -> last == stack -> data_size)
    {
        stack -> data_size = (2 * stack -> data_size);
        stack -> data = (double*)realloc(stack -> data, stack -> data_size);
    }
    stack -> data[stack -> last++] = a;

    assert(stack_ok(stack));
}

//Pop.Returns a* if stack is not empty.Esle returns -1.
double pop(stack_t *stack)
{
    if (stack -> last > 0)
    {
        double l = stack -> data[--stack -> last];
        return l;
    }
    else
    {
        printf("ERROR!!! EMPTY STACK!!!!"); return -1;
    }
}


unsigned int fact(unsigned int p);
int power(int a, unsigned int n);
int resh(int w, int q);


int main()
{
    int c = 0;
    stack_t *s;
    s = cons_stack(10);

    while((c = getchar()) != '@')
    {
        double x = 0;
        switch(c)
        {
            case ' '  :                                            break;
            case '\n' :                                            break;
            case '+'  : push(s, pop(s) + pop(s) );                 break;
            case '-'  : push(s,-(pop(s) - pop(s)) );               break;
            case '*'  : push(s, pop(s) * pop(s) );                 break;
            case '/'  : push(s, (1/pop(s)) * pop(s) );             break;
            case '!'  : push(s, fact(pop(s)) );                    break;
            case '^'  : push(s, power(pop(s),pop(s)) );            break;
            case '%'  : push(s, resh( (int)pop(s), (int)pop(s)) ); break;
            default:
                {
                    ungetc( c, stdin );
                    if (scanf("%lg",&x) != 1)
                    {
                       printf("Can`t  read numder\n");
                       return 1;
                    }
                    else
                    {
                        push(s,x);
                    }
                    break;
                }
        }
    }
    printf("Answer is:%lg\n\n",pop(s));
    dump_stack(s);
    dest_stack(s);

    return 0;
}

int power(int a, unsigned int n)
{
    int k = 0, l = 1;

    for (k = 0 ; k < n ; k++)
    {
        l = a*l;
    }

    return l;
}

unsigned int fact(unsigned int p)
{
    int k = 0, c = 1;

    for(k = 1 ; k <= p ; k++)
    {
        c = c*k;
    }
    if (p == 0)
    {
        return 1;
    }

    return c;
}

int resh(int w, int q)
{
    return (w % q);
}

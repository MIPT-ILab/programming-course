//{=============================================================================
//!  @file  main.c
//!  @date  17.11.13
//!  @author Igor Yadrov <igor.yafrov@frtk>
//!  makes polish calculator by using stack
//!  @par arithmetic expression in polish
//}=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define size_stack 100
/*creating structure for stack */
// FIXME Move this to separate file. struct and function declaration to .h,
// function defenitions to .c, then include .h here
struct stack {
    int Data;
    struct stack *next;
};
struct stack* push (int x, struct stack *ps); // adds a number into stack
struct stack* pop (int* number_pop, struct stack *ps); /* takes a number from stack*/
void dump (struct stack *ps); /* prints all elements of stack*/
// FIXME You should to implement 'stack_ok' function, that checks stack's correctness.
// FIXME You should add stack, that uses an array to store data.
int main() {
    struct stack List; // Initialization
    struct stack *ps=NULL; // creates a создание переменной, указывающей на вершину стека
    List.Data=0;
    List.next=NULL;
    ps=&List;
    int number_1=0;
    int number_2=0;
    int number_push=0;
    int temp;
    int size=0;
    int exit=0;
    char expression[100]; /*creates string for arithmetic expression*/

    // FIXME Print some instructions for user. It is not obvious, how to use your program.
    // FIXME I think, that ',' is more natural than '_'
    scanf("%s", expression);//separate numbers with '_'
    int i=0;
    int old_temp=0;
    while (1) {
        temp=expression[i]-'0';
        if (0 <=temp && temp<= 9) {
            number_push=number_push*10+temp;// makes a number from scanned numbers
        } // checks if a number is scanned
        else {
            if (i>0)
            old_temp=expression[i-1]-'0';/* checks if the previous symbol
            was a number*/
            if (expression[i]!='=' && old_temp>=0 && old_temp<=9 && i>0) {
            /* if the previous symbol
            was a number and current symbol - not, than add a number to stack
            */
            assert(size<size_stack);
            ps=push(number_push, ps);
            size++;
            number_push=0;
            }
            // making arithmetic operations and checking if cycle breaks
            switch (expression[i]) {
            case '+':
            // FIXME Move this to separate function like 'add()'
                assert(size>1);
                ps=pop(&number_1, ps);
                ps=pop(&number_2, ps);
                ps=push(number_1+number_2, ps);
                size--;
                break;
            case '*':
            // FIXME Move this to separate function like 'mul()'
                assert(size>1);
                ps=pop(&number_1, ps);
                ps=pop(&number_2, ps);
                ps=push(number_1*number_2, ps);
                size--;
                break;
            case '-':
            // FIXME Move this to separate function like 'sub()'
                assert(size>1);
                ps=pop(&number_1, ps);
                ps=pop(&number_2, ps);
                ps=push(number_1-number_2, ps);
                size--;
                break;
            case '\0':
                exit=1;
                break;
            }
            if (exit==1)
                break;
        }
        i++;
    }
    /*finally, only one element is in stack, that is a result of
     * arithmetic expression */
    printf ("%d\n", ps->Data);
    return 0;
}
struct stack* push (int x, struct stack *ps) {
    // FIXME What if ps == NULL?
    struct stack *p=(struct stack*)calloc(1, sizeof (struct stack));
    p->Data=x;
    p->next=ps;
    return p;
}
struct stack* pop (int *number_pop, struct stack *ps) {
    assert(ps!=NULL);
    // FIXME and what if number_pop == NULL?
    struct stack* temp=ps->next;
    *number_pop=ps->Data;
    free(ps);
    return temp;
}
void dump (struct stack *ps) {
    // FIXME What if ps = NULL?
    struct stack* p=ps;
    while (p->next!=NULL) {
        printf ("%d\n", p->Data);
        p=p->next;
    }
}
//fuck Diskran shit nigga

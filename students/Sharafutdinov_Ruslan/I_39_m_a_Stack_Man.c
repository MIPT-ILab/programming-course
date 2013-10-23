
//{=================================================================================
//! @file    I'm_a_Stack_Man.c
//! @date    2013-20-10 10:46
//! @author  Sharafutdinov Ruslan <shar.rus72@gmail.com>
//!
//! Implements the function stack
//!
//}=================================================================================
#include <stdio.h>
#define MAXSIZE 5

typedef struct
{
    double data[MAXSIZE];
    int count ;
} Stack_t;

void stack_construct ( Stack_t* st);

void stack_destruct ( Stack_t* st);

int stack_OK ( Stack_t* st);

void stack_push ( Stack_t* st, double number);

double stack_pop ( Stack_t* st );

void stack_dump ( Stack_t* st);

void main ()
{
    int choice = 0;
	int option = 1;
	double number = 0;
	double pop = 0;

	Stack_t st;
	stack_construct (&st);

	printf ( "STACK OPERATIONS\n");
	while (option)
	{
		printf ( "------------------------------------------\n");
		printf ( "  	1	-->	PUSH	       \n");
		printf ( "  	2	-->	POP	           \n");
		printf ( "  	3	-->	DISPLAY		   \n");
		printf ( "  	4	-->	EXIT	       \n");
		printf ( "------------------------------------------\n");

		printf ( "Enter your choice\n");
		scanf	( "%d", &choice);

		if ( choice == 1)
        {
            if ( stack_OK(&st))
            {
                printf ( "Enter the element to be pushed\n");
                scanf ( "%lf", &number);
                stack_push ( &st, number);
            }
            else
            {
                printf ( "ERROR!!!\n");
                printf ( "(count <= 0) or ( STACK IS FULL)\n");
                stack_dump ( &st);
            }
        }
        if ( choice == 2)
        {
            if ( stack_OK(&st) && st.count || st.count == MAXSIZE)
            {
                pop = stack_pop ( &st);
                printf ( "poped element is = %lf\n" , pop);
            }
            else
            {
                printf ( "ERROR!!!\n");
                printf ( "(count <= 0) or (count >= MAXSIZE)\n");
                stack_dump ( &st);
            }
        }
        if ( choice == 3)
        {
            stack_dump ( &st);
        }
        if ( choice == 4)
        {
            stack_destruct( &st);
            option = 0;
            return 0;
        }

	}
    return 0;
}

//! stack_construct - clears all the elements of an array and a variable const
//!
//! @param   Stack_t* st   the stack pointer
//!

void stack_construct ( Stack_t* st)
{
    int i = 0;
    for ( i = 0; i < MAXSIZE; ++i)
        st -> data[i] = 0;
    st -> count = 0;
}

//! stack_destruct - infects the stack
//!
//! @param   Stack_t* st   the stack pointer
//!

void stack_destruct ( Stack_t* st)
{
    int i = 0;
    for ( i = 0; i < MAXSIZE; ++i)
        st -> data[i] = 666;
    st -> count = -1;
    return;
}

//! stack_OK - checks the state of the stack
//!
//! @param   Stack_t* st   the stack pointer
//! return 0 if stack isn't OK
//! return 1 if stack is OK

int stack_OK ( Stack_t* st)
{
    return ( 0 <= st -> count && st -> count < MAXSIZE );
}

//! stack_push - puts an element into the stack
//!
//! @param   Stack_t* st   the stack pointer
//! @param   number - number for push
//!

void stack_push ( Stack_t* st, double number)
{
    if ( stack_OK(&st))
    {
        st -> data[st -> count] = number;
        st -> count ++;
    }
    else
    {
        printf ("ERROR!!!\n");
        printf ("(count < 0) or (count >= MAXSIZE)\n");
    }
    return;
}

//! stack_pop - gets the last push's element
//!
//! @param   Stack_t* st   the stack pointer
//! return   last push's element
//!

double stack_pop ( Stack_t* st )
{
    double number = 0;
    if ( !(stack_OK(&st) == 0) && !(st -> count == 0) )
    {
        number = st -> data[st -> count - 1];
        st -> count --;
        return number;
    }
    else
    {
        printf ( "ERROR!!!\n");
        printf ( "(count <= 0) or (count >= MAXSIZE)\n");
    }
}

//! stack_dump - displays information about the stack
//!
//! @param   Stack_t* st   the stack pointer
//!
//!

void stack_dump ( Stack_t* st)
{
    int i = 0;
    printf ( "STACK// ");
    if ( stack_OK(&st))
        printf ("ok\n");
    else
        {
            printf ( "ERROR!!!\n");
            printf ( "(count < 0 or count >= MAXSIZE)\n");
        }
    printf ( "MAXSIZE = %d\n", MAXSIZE);
    printf ( "COUNT = %d\n", st -> count);
    for ( i = 0; i < MAXSIZE; ++i)
    {
        if ( i < st -> count)
            printf ("data [%d] = %lf  *\n", i, st -> data[i]);
        else
            printf ("data [%d] = %lf\n", i, st -> data[i]);
    }

}

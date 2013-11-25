//{=================================================================================
//! @file    02-poland-2.1.c
//! @date    2013-11-25 18:50
//! @version 2.1
//! @author  Pronin Alexander <texhobeer95@gmail.com>
//!
//! RPN calculator
//!
//! ChangeLog:
//! v. 0.0 :  start working with project
//! v. 1.0 :  first normal version of this program, added error handling
//! v. 2.0 :  program works with double numbers and has stack limited by RAM          
//! v. 2.1 :  fixed problem with reallocated memory, fixed error with emty
//!           expression
//!
//}=================================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define eps 0.000000001

typedef double elem_t;

int error_line_func = -1, error_line_op = -1, STK_SIZE;

struct stack {
	int count;
	elem_t* data;
};

//{=================================================================================
//! ERROR_CHECK - check errors at the moment and report an error if
//!               necessary
//!
//! @param      OK    error code
//!
//! note: this function uses global variables:
//! @param      error_line_op     number of line where was found secondary error
//! @param      error_line_func   number of line where was found main error
//}=================================================================================

int ERROR_CHECK (int OK) {
	switch (OK)
	{
	case 2:
		if (error_line_op == -1) {
			printf ("There was an operation in the not constructed stack. Line %d.\n", error_line_func);
		}
		else {
			printf ("There was an operation in the not constructed stack (line %d) in function on line %d.\n", error_line_func, error_line_op);
		}
		break;
	case 3:
		if (error_line_op == -1) {
			printf ("There was a pop in the empty stack. Line %d.\n", error_line_func);
		}
		else {
			printf ("There was a pop in the empty stack (line %d) in function on line %d.\n", error_line_func, error_line_op);
		}
		break;
	case 4:
		printf ("There was a division by zero. Line %d.\n", error_line_func);
		break;
	case 5:
		printf ("The stack's address is NULL. Line %d.\n", error_line_func);
		break;
	case 6:
		printf ("There was a pop to element with address NULL. Line %d.\n", error_line_func);
		break;
	case 0:
		return 0;
	case -1:
		printf ("You entered empty expression. Good by, my dear friend.\n");
		break;
	default:
		printf ("Unknown error. Write an e-mail to me: texhobeer95@gmail.com\n");
		printf ("Also write, what did you do with my program to get this error.\n");
		break;
	}
	if (OK) {
		printf ("Program will be stopped.\n");
	}
	return OK;
}

//{=================================================================================
//! stack_construct - construct stack 
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      STK_SIZE        stack size at the moment
//! @param      error_line_func number of line where was found error
//}=================================================================================

void stack_construct (struct stack* st) {
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	st -> count = 0;
	st -> data = (elem_t*) malloc (4 * sizeof (elem_t));
	STK_SIZE = 4;
}

//{=================================================================================
//! stack_realloc - change stack's size
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      STK_SIZE        stack size at the moment
//! @param      error_line_func number of line where was found error
//}=================================================================================

void stack_realloc (struct stack* st) {
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	if (st -> count == -1) {
		ERROR_CHECK (2);
		error_line_func = __LINE__;
		exit (2);
	}
	if (st -> count < STK_SIZE/4) {
		st -> data = (elem_t*) realloc (st -> data, sizeof (elem_t) * STK_SIZE/2);
		STK_SIZE /= 2;
	}
	if (st -> count > STK_SIZE/2) {
		st -> data = (elem_t*) realloc (st -> data, sizeof (elem_t) * STK_SIZE*2);
		STK_SIZE *= 2;
	}
}

//{=================================================================================
//! stack_destroy - free stack's memory
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      STK_SIZE        stack size at the moment
//! @param      error_line_func number of line where was found error
//}=================================================================================

void stack_destroy (struct stack* st) {
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	if (st -> count != -1) {
		free (st -> data);
	}
	STK_SIZE = 4;
}

//{=================================================================================
//! stack_dump - print all stack's elements
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      error_line_func number of line where was found error
//}=================================================================================

void stack_dump (struct stack* st) {
	int i = 0;
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	if (st -> count > 0) {
		printf ("This stack has %d elements at the moment:\n", st -> count);
		for (i = 0; i < st -> count; i++) {
			printf ("%d ", st -> data[i]);
		}
		printf ("\n");
	}
	else if (st -> count == 0) {
		printf ("There is no elements here\n");
	}
	else {
		printf ("This stack hasn't been constructed yet\n");
	}
}

//{=================================================================================
//! stack_push - add element to stack
//!
//! @param      st    stack address
//! @param      num   new element
//!
//! note: this function uses global variables:
//! @param      error_line_func number of line where was found error
//}=================================================================================

int stack_push (struct stack* st, elem_t num) {
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	if (st -> count != -1) {
		st -> data[st -> count] = num;
		st -> count += 1;
		stack_realloc (st);
		return 0;
	}
	else {
		error_line_func = __LINE__;
		return 2;
	}
}

//{=================================================================================
//! stack_pop -  return last stack's element and delete him from stack
//!
//! @param      st       stack address
//! @param      result   last element
//!
//! note: this function uses global variables:
//! @param      error_line_func number of line where was found error
//}=================================================================================

int stack_pop (struct stack* st, elem_t* result) {
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	if (result == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (6);
		exit (6);
	}
	if (st -> count == -1) {
		error_line_func = __LINE__;
		return 2;
	}
	else if (st -> count == 0) {
		error_line_func = __LINE__;
		return 3;
	}
	else {
		st -> count -= 1;
		*result = st -> data[st -> count];
		stack_realloc (st);
		return 0;
	}
}

//{=================================================================================
//! stack_sum - pop two elements and push their sum
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      error_line_op     number of line where was found error
//! @param      error_line_func   number of line where was found error,
//!                               if the error was in another function
//}=================================================================================

int stack_sum (struct stack* st) {
	elem_t a, b;
	int check;
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_push (st, a + b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	return 0;
}

//{=================================================================================
//! stack_mul - pop two elements and push their multiple
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      error_line_op     number of line where was found error
//! @param      error_line_func   number of line where was found error,
//!                               if the error was in another function
//}=================================================================================

int stack_mul (struct stack* st) {
	elem_t a, b;
	int check;
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_push (st, a * b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	return 0;
}

//{=================================================================================
//! stack_diff - pop two elements and push their difference
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      error_line_op     number of line where was found error
//! @param      error_line_func   number of line where was found error,
//!                               if the error was in another function
//}=================================================================================

int stack_diff (struct stack* st) {
	elem_t a, b;
	int check;
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	check = stack_push (st, a - b);
	if (check) {
		error_line_op =__LINE__;
		return check;
	}
	return 0;
}

//{=================================================================================
//! stack_div - pop two elements and push their quotient
//! note: last element is divider, last but one is dividend
//!
//! @param      st    stack address
//!
//! note: this function uses global variables:
//! @param      error_line_op     number of line where was found error
//! @param      error_line_func   number of line where was found error,
//!                               if the error was in another function
//}=================================================================================

int stack_div (struct stack* st) {
	elem_t a, b;
	int check;
	if (st == NULL) {
		error_line_func = __LINE__;
		ERROR_CHECK (5);
		exit (5);
	}
	check = stack_pop (st, &b);
	if (check) {
		error_line_op = __LINE__;
		return check;
	}
	if (((b + eps) >= 0) && ((b - eps) <= 0)) {
		error_line_func = __LINE__;
		return 4;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op = __LINE__;
		return check;
	}
	check = stack_push (st, a / b);
	if (check) {
		error_line_op = __LINE__;
		return check;
	}
	return 0;
}

int main()
{
	struct stack st;
	int stop = 0, OK = -1, check, check2;
	elem_t num = 0, ans = 0;
	char ch[2];
	st.count = -1;
	stack_construct (&st);
	printf ("RPN solver v. 2.1 by Alexander Pronin\n");
	printf ("Enter an expression in RPN. Program works with double numbers.\n");
	printf ("Attention! In the end of expression must be the EOF symbol!\n");
	printf ("You must enter space between every operation sign.\n");
	printf ("If you won't do it, the program will crash.\n");
	while (!stop) {
		check = scanf (" %[*/+-]", ch);
		if (check == 0) {
			check = 5;
		}
		else if (check == -1) {
			check = 6;
		}
		else if (ch[0] == '+') {
			check = 1;
		}
		else if (ch[0] == '-') {
			check = 2;
		}
		else if (ch[0] == '*') {
			check = 3;
		}
		else if (ch[0] == '/') {
			check = 4;
		}
		else if (ch[0] == '\n') {
			check = 6;
		}
		else {
			check = 5;
		}
		switch (check)
		{
		case 1:
			OK = stack_sum (&st);
			break;
		case 2:
			OK = stack_diff (&st);
			break;
		case 3:
			OK = stack_mul (&st);
			break;
		case 4:
			OK = stack_div (&st);
			break;
		case 5:
			check2 = scanf ("%lf", &num);
			if (check2 != 1) {
				stop = 1;
			}
			else if (check2 == 1) {
				OK = stack_push(&st, num);
			}
			break;
		case 6:
			stop = 1;
			break;
		}
		if (ERROR_CHECK (OK)) {
			stack_destroy (&st);
			return OK;
			}
	}
	OK = stack_pop (&st, &ans);
	if (ERROR_CHECK (OK)) {
		return OK;
	}
	printf ("\nResult: %.2lf\n", ans);
	stack_destroy (&st);
	return 0;
}
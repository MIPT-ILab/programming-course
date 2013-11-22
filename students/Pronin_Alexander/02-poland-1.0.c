#include <stdio.h>
#include <stdlib.h>

#define STK_SZ 10000

#define INF 1000000

typedef int elem_t;

int error_line_func = -1, error_line_op = -1;

struct stack {
	int count;
	elem_t data[STK_SZ];
};

void stack_construct (struct stack* st) {
	st -> count = 0;
	st -> data[st -> count] = INF;
}

void stack_dump (struct stack* st) {
	int i = 0;
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

int stack_push (struct stack* st, elem_t num) {
	if (st -> count < STK_SZ) {
		st -> data[st -> count] = num;
		st -> count += 1;
		return 0;
	}
	else if (st -> count == -1) {
		error_line_func = __LINE__ - 1;
		return 2;
	}
	else {
		error_line_func = __LINE__ - 1;
		return 1;
	}
}

int stack_pop (struct stack* st, elem_t* result) {
	if (st -> count == -1) {
		error_line_func = __LINE__ - 1;
		return 2;
	}
	else if (st -> count == 0) {
		error_line_func = __LINE__ - 1;
		return 3;
	}
	else {
		st -> count -= 1;
		*result = st -> data[st -> count];
		return 0;
	}
}

int stack_sum (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__ - 5;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__ - 10;
		return check;
	}
	check = stack_push (st, a + b);
	if (check) {
		error_line_op =__LINE__ - 15;
		return check;
	}
	return 0;
}

int stack_mul (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__ - 5;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__ - 10;
		return check;
	}
	check = stack_push (st, a * b);
	if (check) {
		error_line_op =__LINE__ - 15;
		return check;
	}
	return 0;
}

int stack_diff (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		error_line_op =__LINE__ - 5;
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op =__LINE__ - 10;
		return check;
	}
	check = stack_push (st, a - b);
	if (check) {
		error_line_op =__LINE__ - 15;
		return check;
	}
	return 0;
}

int stack_div (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		error_line_op = __LINE__ - 5;
		return check;
	}
	if (b == 0) {
		error_line_func = __LINE__ - 1;
		return 4;
	}
	check = stack_pop (st, &a);
	if (check) {
		error_line_op = __LINE__ - 14;
		return check;
	}
	check = stack_push (st, a / b);
	if (check) {
		error_line_op = __LINE__ - 19;
		return check;
	}
	return 0;
}

int ERROR_CHECK (int OK) {
	switch (OK)
	{
	case 1:
		if (error_line_op == -1) {
			printf ("There was a push to the full stack. Line %d.\nProgram will be stopped.\n", error_line_func);
		}
		else {
			printf ("There was a push to the full stack (line %d) in function on line %d.\nProgram will be stopped.\n", error_line_func, error_line_op);
		}
		return 1;
	case 2:
		if (error_line_op == -1) {
			printf ("There was a push or pop in the not constructed stack. Line %d.\nProgram will be stopped.\n", error_line_func);
		}
		else {
			printf ("There was a push or pop in the not constructed stack (line %d) in function on line %d.\nProgram will be stopped.\n", error_line_func, error_line_op);
		}
		return 2;
	case 3:
		if (error_line_op == -1) {
			printf ("There was a pop in the empty stack. Line %d.\nProgram will be stopped.\n", error_line_func);
		}
		else {
			printf ("There was a pop in the empty stack (line %d) in function on line %d.\nProgram will be stopped.\n", error_line_func, error_line_op);
		}
		return 3;
	case 4:
		printf ("There was a division by zero. Line %d.\nProgram will be stopped.\n", error_line_op);
		return 4;
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
	printf ("RPN solver v. 1.0 by Alexander Pronin\n");
	printf ("Enter an expression in RPN.\n");
	printf ("Attention! In the end of expression must be the EOF symbol!\n");
	while (!stop) {
		check = scanf(" %[*/+-]", ch);
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
			check2 = scanf ("%d", &num);
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
		default:
			OK = 1;
			break;
			if (ERROR_CHECK (OK)) {
				return OK;
			}
		}
	}
	OK = stack_pop (&st, &ans);
	if (ERROR_CHECK (OK)) {
		return OK;
	}
	printf ("\nResult: %d\n", ans);
	return 0;
}
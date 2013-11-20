#include <stdio.h>
#include <stdlib.h>

#define STK_SZ 10000

#define INF 1000000

typedef int elem_t;

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
		return 2;
	}
	else {
		return 1;
	}
}

int stack_pop (struct stack* st, elem_t* result) {
	if (st -> count == -1) {
		return 2;
	}
	else if (st -> count == 0) {
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
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		return check;
	}
	check = stack_push (st, a + b);
	if (check) {
		return check;
	}
	return 0;
}

int stack_mul (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		return check;
	}
	check = stack_push (st, a * b);
	if (check) {
		return check;
	}
	return 0;
}

int stack_diff (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		return check;
	}
	check = stack_pop (st, &a);
	if (check) {
		return check;
	}
	check = stack_push (st, a - b);
	if (check) {
		return check;
	}
	return 0;
}

int stack_div (struct stack* st) {
	elem_t a, b;
	int check;
	check = stack_pop (st, &b);
	if (check) {
		return check;
	}
	if (b == 0) {
		return 4;
	}
	check = stack_pop (st, &a);
	if (check) {
		return check;
	}
	check = stack_push (st, a / b);
	if (check) {
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
	stack_dump (&st);
	while (!stop) {
		check = scanf(" %[\n*/+-]", ch);
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
			stack_dump (&st);
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
//			if (ERROR_CHECK (OK)) {
//				return OK;
//			}
		}
	}
	OK = stack_pop (&st, &ans);
	printf ("%d\n", ans);
	stack_dump (&st);
	return 0;
}
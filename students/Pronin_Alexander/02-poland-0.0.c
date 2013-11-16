#include <stdio.h>
#define STK_SZ 10000

typedef double elem_t;

struct stack {
	int count;
	elem_t data[STK_SZ];
};

int main()
{
	struct stack st;
	int stop = 0, OK = -1;
	double num, first, second, ans;
	char ch;
//	stack_construct (&st);
	while (!stop) {
		if (scanf ("%lf", &num) == 1) {
//			stack_push (&st, num);
			OK = 0;
		}
		else if (scanf ("%c", &ch) == 1) {
			switch (ch)
			{
			case '+':
//				OK = stack_sum (&st);
				break;
			case '-':
//				OK = stack_diff (&st);
				break;
			case '*':
//				OK = stack_mul (&st);
				break;
			case '/':
//				OK = stack_div (&st);
				break;
			case ' ':
				break;
			case '\n':
				stop = 1;
				break;
			default:
				OK = 1;
				break;
			}
//			if (ERROR_CHECK (OK)) {
//				return OK;
//			}
		}
		else {
			stop = 1;
		}
	}
//	ans = stack_pop (&st);
	printf ("lf\n", ans);
	return 0;
}
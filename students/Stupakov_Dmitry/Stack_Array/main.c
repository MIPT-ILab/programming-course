#include <stdio.h>
#include "StackStup.h"
#include <assert.h>
int main()
{
	struct Stack_Arr stack;
	Push(&stack, 5);
	Dump(&stack);
	system("pause");
	return 0;
}

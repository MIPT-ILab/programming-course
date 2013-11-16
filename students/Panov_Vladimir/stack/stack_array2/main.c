/*
 * main.c
 *
 *  Created on: 03 нояб. 2013 г.
 *      Author: ALTAIR
 */
#include "stack.h"

int main() {
	int num = 4;
	Stack* stack = Stack_Initialize(num, 0);
	int i = 0;
	for(i = 0; i < num; i++ )
		Stack_Push(stack, i);
	Stack_Dump(stack);
	for(i = 0; i < num+1; i++)
		Stack_Pop(stack);
	stack = Stack_Destroy(stack);
	return 0;
}


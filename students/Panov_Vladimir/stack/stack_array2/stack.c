/*
 * stack.c
 *
 *  Created on: 11 нояб. 2013 г.
 *      Author: ALTAIR
 */

#include "stack.h"

#define ASSERT(cond) \
if (!(cond)) {\
    printf("All gone bad: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__);\
	abort();\
    }

#define ASSERT_STACK_OK(stack) \
if(stack == NULL || stack->counter > stack->size || (stack->counter < 0)) {\
	printf("Stack is BAD!!! file: %s, line: %d\n", __FILE__, __LINE__);\
	Stack_Destroy(&stack);\
	abort();\
}

struct Stack {
	int counter;
	int size;
	int elements[1];
};

Stack* Stack_Initialize(int size, int FirstValue) {
	ASSERT(size > 0);
	Stack* NewStack = (Stack*) calloc(size + 2, sizeof(int));
	NewStack->size = size;
	NewStack->counter = 0;
	NewStack->elements[0] = FirstValue;
	ASSERT_STACK_OK(NewStack);
	return NewStack;
}

Stack* Stack_Destroy(Stack* stack) {
	ASSERT(stack != NULL);
	int i;
	Stack* destroyStack = stack;
	for( i = 0; i < destroyStack->size; i++) {
		destroyStack->elements[i] = 0xBAD;
	}
	destroyStack->counter = 0xBAD;
	destroyStack->size = 0xBAD;
	free(destroyStack);
	return NULL;
}

int Stack_Push(Stack* stack, const int NewValue) {
	ASSERT_STACK_OK(stack);
	stack->counter++;
	ASSERT_STACK_OK(stack);
	stack->elements[stack->counter] = NewValue;
	return 0;
}

int Stack_Pop(Stack* stack) {
	ASSERT_STACK_OK(stack);
	int Value = stack->elements[stack->counter];
	stack->elements[stack->counter] = 0xBAD;
	stack->counter--;
	ASSERT_STACK_OK(stack);
	return Value;
}

int Stack_Size(const Stack* stack) {
	ASSERT_STACK_OK(stack);
	return stack->counter;
}

int Stack_Dump(const Stack* stack) {
	ASSERT_STACK_OK(stack);
	printf("Stack ok size: %d counter: %d \n", stack->size, stack->counter);
	int i;
	for( i = 0; i < stack->counter; i++){
		printf("%d : %d \n", i, stack->elements[i]);
	}
	return 0;
}

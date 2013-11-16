/*
 * stack_list.c
 *
 *  Created on: 03 нояб. 2013 г.
 *      Author: ALTAIR
 */
#include "stack.h"

#define ASSERT(cond) \
if (!(cond)) {\
    printf("All gone bad: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__);\
    abort();\
    }

#define ASSERT_STACK_OK(Stack) \
if(Stack == NULL) {\
	printf("Stack is bad!!! file: %s, lineL %d\n", __FILE__, __LINE__);\
	Stack_Destroy(Stack);\
	abort();\
}

struct stack {
	Stack_Type Value;
	stack* prev;
};

stack* Stack_Initialize() {
	return NULL;
}

int Stack_Destroy(stack* Stack) {
	while(Stack != NULL) {
		stack* buf = Stack->prev;
		Stack->Value = 0xBAD;
		free(Stack);
		Stack = buf;
	}
	return 0;
}

stack* Stack_Push(stack **currentNode, const Stack_Type NewValue) {
	stack * NewNode = (stack*) malloc(sizeof(stack));
	(NewNode)->Value = NewValue;
	(NewNode)->prev = *currentNode;
	*currentNode = NewNode;
	ASSERT_STACK_OK(*currentNode);
	return *currentNode;
}

int Stack_Pop(stack **currentNode, Stack_Type* Value) {
	ASSERT(Value != NULL);
	if((*currentNode) == NULL) {
		return 0;
	}
	ASSERT_STACK_OK(*currentNode);
	Stack_Type NewValue = (*currentNode)->Value;
	*currentNode = (*currentNode)->prev;
	*Value = NewValue;
	return 1;
}

int Stack_Invert(stack **currentNode) {
	stack* nextNode = NULL;
	stack* prevNode = NULL;
	while(*currentNode != NULL) {
		prevNode = (*currentNode)->prev;
		(*currentNode)->prev = nextNode;
		nextNode = *currentNode;
		*currentNode = prevNode;
	}
	(*currentNode) = nextNode;
	return 0;
}

int Stack_Size(const stack * Stack){
	ASSERT_STACK_OK(Stack);
	stack* currentNode = Stack;
	int Size = 0;
	while(currentNode->prev != NULL){
		Size++;
		currentNode = currentNode->prev;
	}
	return Size;
}

int Stack_Dump(const stack* Stack) {
	int size = Stack_Size(Stack);
	printf("DUMP Stack ok Size: %d \n", size);
	int i;
	stack* currentNode = Stack;
	for(i = 0; i < size; i++){
		ASSERT(currentNode != NULL);
		printf("%d : %lg \n", size - i, currentNode->Value);
		currentNode = currentNode->prev;
	}
	printf("DUMP complite\n");
	ASSERT_STACK_OK(Stack);
	return 0;
}

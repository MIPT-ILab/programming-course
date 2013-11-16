/*
 * stack.h
 *
 *  Created on: 03 нояб. 2013 г.
 *      Author: ALTAIR
 */

#ifndef STACK_H_
#define STACK_H_
#include <stdio.h>
#include <stdlib.h>

struct stack;

typedef struct stack stack;
typedef double Stack_Type;

stack* Stack_Initialize();

int Stack_Destroy(stack* Stack);

stack* Stack_Push(stack **currentNode, const Stack_Type NewValue);

int Stack_Pop(stack **currentNode, Stack_Type* Value);

int Stack_Invert(stack **currentNode);

int Stack_Size(const stack *Stack);

int Stack_Dump(const stack* Stack);

int Stack_Ok();

#endif /* STACK_H_ */

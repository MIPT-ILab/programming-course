/*
 * stack.h
 *
 *  Created on: 11 нояб. 2013 г.
 *      Author: ALTAIR
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <stdio.h>

struct Stack;

typedef struct Stack Stack;
// FIXME Why some variables starts with capital letters (FirstValue)
// and other not (size)? Should be one style.
Stack* Stack_Initialize(int size, int FirstValue);

Stack* Stack_Destroy(Stack* Stack);

int Stack_Push(Stack* stack, const int NewValue);

int Stack_Pop(Stack* stack);

int Stack_Size(const Stack *Stack);

int Stack_Dump(const Stack* Stack);

int Stack_Ok();

#endif /* STACK_H_ */

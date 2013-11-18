/*
 * main.c
 *
 *  Created on: 03 нояб. 2013 г.
 *      Author: ALTAIR
 */
#include "stack.h"
#include <stdio.h>

int pushAB(stack **Stack, Stack_Type* a, Stack_Type* b) {
	Stack_Pop(Stack, a);
	Stack_Pop(Stack, b);
	return 1;
}

int Plus(stack** Stack) {
	Stack_Type a, b;
	pushAB(Stack, &a, &b);
	Stack_Push(Stack, a+b);
	return 0;
}

int Minus(stack** Stack) {
	Stack_Type a, b;
	pushAB(Stack, &a, &b);
	Stack_Push(Stack, a-b);
	return 0;
}

int Multi(stack** Stack) {
	Stack_Type a, b;
	pushAB(Stack, &a, &b);
	Stack_Push(Stack, a*b);
	return 0;
}

int Division(stack** Stack) {
	Stack_Type a, b;
	pushAB(Stack, &a, &b);
	Stack_Push(Stack, a/b);
	return 0;
}

int main() {
	Stack_Type num;
	char s[100];
	stack* Number = Stack_Initialize();
	stack* ActionList = Stack_Initialize();
	Stack_Type Action = 0;
	do{
		scanf("%s",s);
		int isNumber = sscanf(s ,"%lg", &num);
		if(isNumber) {
			Stack_Push(&Number, num);
		}
		else {
			Action = 0;
			switch(s[0]){
				case 'p': Action = 1;
					break;
				case 'm': Action = 2;
					break;
				case 'u': Action = 3;
					break;
				case 'd': Action = 4;
					break;
			};
			if(Action )
				Stack_Push(&ActionList, Action);
		}
	}while(s[0] != 'e');
	Stack_Invert(&ActionList);
	Stack_Invert(&Number);
	while(Stack_Pop(&ActionList, &Action)){
			switch((int)Action){
				case 1: Plus(&Number);
					break;
				case 2: Minus(&Number);
					break;
				case 3: Multi(&Number);
					break;
				case 4: Division(&Number);
					break;
			};
	}
	Stack_Pop(&Number, &num);
	printf("#Answer : \n%lg", num);
	Stack_Destroy(Number);
	Stack_Destroy(ActionList);
	return 0;
}


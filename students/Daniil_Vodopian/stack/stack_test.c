#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "stackLib.h"

int main (int argc, char *arg[])
{
	Stack_t st = Stack();
	/*
	Stack_t st = {};
	Stack_constarct(st);//*/
	
	//Stack_distruct(&st);
	//Stack_constract(&st);
	push(&st, 5);
	push(&st, 239);
	
	printf("%d %d\n", pop(&st), pop(&st));
	
	Stack_distruct(&st);
	return 0;
}


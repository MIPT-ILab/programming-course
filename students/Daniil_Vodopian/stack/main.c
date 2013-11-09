#include <stdio.h>
#include <string.h>
#include <assert.h>

<<<<<<< HEAD
#include <stackLib.h>
=======
//the line used to not exist

#include "stackLib.h"
//#include <stackLib.h>
>>>>>>> dfa4d63c20786d023b852f6f953f5e6778e15c87

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
   
   //it is a new comment
}


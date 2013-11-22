#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXVAL 100
int sp = 0;
int val[MAXVAL];

main()
{
	int myorder;
	char * ord;
	int x;
	FILE *f_in;
	f_in = fopen("in.txt", "r");
	do
	{	
		ord=malloc(64);
		fscanf(f_in, "%s", ord);
		if ((strcmp(ord,"push")) == 0) 
			myorder=1;
		if ((strcmp(ord,"add")) == 0) 
			myorder=2;
		if ((strcmp(ord,"mul")) == 0) 
			myorder=3;
		if ((strcmp(ord,"out")) == 0) 
			myorder=4;
		if ((strcmp(ord,"pop")) == 0) 
			myorder=5;
		free(ord);
		switch (myorder)
		{
			case 1: 
				fscanf(f_in, "%i", &x); 
				push(x);
				break;
			case 2: 
				push(pop()+pop());
				break;
			case 3: 
				push(pop()*pop());
				break;
			case 4: 
				printf("%i\n", pop());
				break;
			case 5: 
				pop();
				break;
		}
			
	}
	while (myorder!=4);
	fclose(f_in);
}

void push(int fk)
{
	if (sp < MAXVAL)
		val[sp++] = fk;
	else 
		printf("error: stack full\n");
}

int pop(void)
{
	if (sp > 0)
		return val[--sp];
	else 
	{ 
		printf("error: stack empty\n");
		return 0.0;
	}
}

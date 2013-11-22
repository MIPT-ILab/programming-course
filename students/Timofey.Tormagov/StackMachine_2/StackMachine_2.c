#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXVAL 100
int sp = 0;
int val[MAXVAL];

main()
{
	int myorder;
	int x;
	FILE *f_in;
	f_in = fopen("in.txt", "r");
	do
	{
		fscanf(f_in, "%i", &myorder);
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
				printf("%i", pop());
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

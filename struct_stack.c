#define _GNU_SOURCE
#define STK_SZ 30

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

typedef int elem_t;

struct Stack_t
{
	int 	count;
	elem_t  data[STK_SZ];
};

int stack_ok(const struct Stack_t *st)
{
	assert (st != NULL);
	return (0 <= st->count && st->count < STK_SZ);
}

void stack_construct(struct Stack_t *st)
{
	assert(st != NULL);
	st->count  = 0;
	//st->data[] = {}; //не сработало.
	return;
}

int stack_push(struct Stack_t *st, elem_t digit)
{
	assert(st != NULL);
	
	if(!stack_ok(st))
		return 1;    
	
	st->data[st->count] = digit;
	st->count++;
	
	return 0;
}

elem_t stack_pop(struct Stack_t *st)
{
	assert(st != NULL);
	st->count--;
	if (stack_ok(st))
		return st->data[st->count];
	
	printf("Произошла ошибка переполнения стека");
	assert(0 <= st->count && st->count < STK_SZ);
	return 1;
}

void stack_destruct(struct Stack_t *st)
{
	for(int i = 0; i < STK_SZ; i++)
		st->data[i] = 0xBAD;
	st->count = 0xBAD;
	return;
}

int main()
{
	struct Stack_t  st 		= {};
	elem_t          d 		= 0;
	char 			*s      = NULL;
	char 			*digit  = NULL;
	size_t 			len     = 0;
	int 			i 		= 0;
	int 			z		= 0;
	int 			num     = 0;
	
	stack_construct(&st);
	
	len = getline(&s, &len, stdin);
	
	while (i < len)
	{
		if isdigit(s[i])
		{
			digit = (char*) calloc(255, sizeof(char));
			z 	  = 0;
			
			while ((i < len) && (isdigit(s[i])))
			{
				digit[z] = s[i];
				i++;
				z++;
			}
			
			num = atoi(digit);
			
			assert		(stack_ok(&st));
			stack_push  (&st,num);
			free		(digit);
			z = 0;
			i--;
		}
		else
			if(!isspace(s[i]))
			{	char 	operation = s[i];
			  	elem_t	num2 	  = stack_pop(&st);
			  	elem_t	num1      = stack_pop(&st);
			  	elem_t	result    = 0;
			  	switch(operation)
			  	{
			  		case '+': result = num1 + num2;break;
			  		case '-': result = num1 - num2;break;
			  		case '*': result = num1 * num2;break;
			  		case '/': result = num1 / num2;break;
			  		default : printf("Введен неверный символ");
			  	}
			  	stack_push(&st, result);
			  
			}
		i++;
	}
	
	
	printf("%d\n", stack_pop(&st));
	
	free(s);	
	stack_destruct(&st);
	
	return 0;
}

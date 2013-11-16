#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int elem_t;

struct Stack_t
{
	elem_t*  data;
	int     count;
	int     length; 
};

void stack_construct(struct Stack_t *st)
{
	st->count  = 0;
	st->length = 1;
	
	st->data = (elem_t*) calloc(st->length, sizeof(elem_t));
	assert(st->data != NULL);	
}

void stack_dump(struct Stack_t *st)
{
	if(st != NULL)
	{
		printf("\nstack dump:");
		printf("\ncount  = %d", st->count );
		printf("\nlength = %d", st->length);
		for(int i = 0; i < st->count; i++)
		{
			if ((st->data != NULL) && (0 <= st->count) && (st->count <= st->length))
				printf("\ndata[%d] = %d", i, st->data[i]);
		}
		printf("\n");
		
	}
	else 
		assert(!"st == NULL");
	
}

int stack_ok(struct Stack_t *st)
{
	return (st && 0 <= st->count && st->count <= st->length);
}

elem_t stack_push(struct Stack_t *st, elem_t digit)
{
	if (stack_ok(st))
		{
			if (st->count == st->length)
			{
				st->length = 2 * st->length;
				st->data = (elem_t*) realloc(st->data, st->length * sizeof(elem_t));
				assert(st->data != NULL);
			}
			st->data[st->count] = digit;
			st->count++;
			
			return digit;
		}
	stack_dump(st);
	assert(!"stack not ok in push");
	
	return 0;
	
}

elem_t stack_pop(struct Stack_t *st)
{
	if(stack_ok(st))
	{ 
		st->count--;
		if(stack_ok(st))
			return st->data[st->count];
	}
	stack_dump(st);
	assert(!"stack not ok in pop");
	return 0;
}

void stack_destruct(struct Stack_t *st)
{
	st->count  = 0xBAD;
	st->length = 0xBAD;
	free(st->data);
}




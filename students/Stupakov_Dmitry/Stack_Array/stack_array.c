void Assert_OK (struct Stack_Arr *st)
{
    assert(st->head != NULL);
	assert(st->elem != NULL);
	assert((0 <= *st->head) && (*st->head <= MAX_SIZE));
}

int stack_push (struct Stack_Arr *st, int val)
{
    Assert_OK(st);

    if (*(st->head) == MAX_SIZE)
		printf("#Stack is full\n");
	else
	{
		st->elem[*(st->head)] = val;
		st->head++;

		Assert_OK(st);

		return 0;
	}
}

int stack_pop (struct Stack_Arr *st)
{
	int val = 0;
    Assert_OK(st);

    if (st->head == 0)
		printf("#No elements in stack");
	else
	{
		val = st->elem[*st->head];
		st->head--;

		Assert_OK(st);

		return val;
	}
}

void Dump (struct Stack_Arr *st)
{
	int i = 0;
    Assert_OK(st);

	printf("#Stack size: %i\n"
			"#Stack content:\n", st->head);
    for(i = 0; i < st->head; i++)
		printf ("%\n", st->elem[i]);
    
	Assert_OK(st);
}

int Size (struct Stack_Arr *st)
{
	Assert_OK(st);

	return *st->head;
}
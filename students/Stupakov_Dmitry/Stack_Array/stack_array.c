struct Stack_Arr
{
	int *head;
	double elem[100];
}

int Assert_OK(struct Stack_Arr *st)
{
	int err = 0, i = 0;
	if (0<= st->head < 100)
		err = 1;
	if (st->elem == 0)
		err = 2;
	if (st->head == 0)
		err = 3;
	return *err;
}

int Push(struct Stack_Arr *st, double val)
{
	int proof = Assert_OK(st);
	if (proof == 0)
	{
		st->elem[*st->head];
		proof = Assert_OK(st);
		return proof;
	}
	else
		return proof;
}

int Pop(struct Stack_Arr *st)
{
	int proof = Assert_OK(st);
	if (proof == 0)
	{
		st->head--;
	proof = Assert_OK(st);
	return proof;
	}
	else
		return proof;
}

int Dump(struct Stack_Arr *st)
{
	int i = 0;
	int proof = Assert_OK(st);
		if (proof == 0)
		{
			printf("#Stack content:\n");
			for (i = 0; i < *st->head; i++)
				printf("%lg ", st->elem[i]);
			printf("/n#StackSize:/n%i", st->head);
			proof = Assert_OK(st);
		}
		else
		return proof;

}

int Size(struct Stack_Arr *st)
{
	int proof = Assert_OK(st);
	if (proof  == 0)
		return *st->head;
	else
		return proof;
}

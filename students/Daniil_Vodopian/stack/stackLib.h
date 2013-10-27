#ifndef _STACK_LIB_H_
#define _STACK_LIB_H_

typedef int elmStack_t;
#define MaxSizeStackT 100
typedef struct Stack_t{
		const int maxSize;
		int count;
		elmStack_t arr[MaxSizeStackT];
} Stack_t;

//------------------------
void Stack_constract(Stack_t *st);
Stack_t Stack();
void Stack_distruct(Stack_t *st);
int Stack_OK(const Stack_t *st);
void Stack_Dump(const Stack_t *st);//elmStack_t = int

/*
#define Stack_assert_d(st, mess) if(!Stack_OK(st)){ 	\
	 Stack_Dump(st); 									\
	 assert(!mess);										\
}														//*/

void Stack_assert(const Stack_t *st, char *message);

void push(Stack_t *st, elmStack_t x);
elmStack_t pop(Stack_t *st);

#endif

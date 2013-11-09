#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <stackLib.h>

#define repeat(x)	for(int cnt_rpt = 0; cnt_rpt < x; cnt_rpt++)
#define repeatI(x)	for(int I = 0; I < x; I++)
#define print(expr) printf(#expr " = %d\n", expr);

//----------------------------------------------------------------------

void Stack_constract(Stack_t *st){
	*( (int*) &(st -> maxSize) ) = MaxSizeStackT;
	if(st -> count < 0) assert(!"dead stack");
	st -> count = 0;
}

Stack_t Stack(){
	Stack_t ans;
	Stack_constract(&ans);
	return ans;
}

void Stack_distruct(Stack_t *st){
	st -> count = -1;
}

int Stack_OK(const Stack_t *st){
	return (st && (0 <= st -> count) && (st -> count <= st -> maxSize) && (st -> arr));
}

void Stack_Dump(const Stack_t *st){ //elmStack_t = int
	printf("Stack_t // %s\n", (Stack_OK(st))? "ok" : "ERROR STRUKT");
	printf("in #%p\n", (st -> arr));
	printf("count = %d < %d\n", st -> count, MaxSizeStackT);
	printf("arr:\n");
	repeatI(st -> count)
		printf("  %d : %d in #%p\n", I, st -> arr[I], (st -> arr + I));
}
/*
#define Stack_assert_d(st, mess) if(!Stack_OK(st)){ 	\
	 Stack_Dump(st); 									\
	 assert(!mess);										\
}														//*/

void Stack_assert(const Stack_t *st, char *message){
	if(!Stack_OK(st)){
		Stack_Dump(st); 
		assert(!message);
	}
}
//---------------------------

void push(Stack_t *st, elmStack_t x){
	Stack_assert(st, "push");
	if(st->count  <  st->maxSize  -  1){
		st->arr[st->count]  =  x;
		st->count  ++;
	}else assert(!"stack overflow");
}

elmStack_t pop(Stack_t *st){
	Stack_assert(st, "push");
	if (st->count > 0){
		st->count --;
		return st->arr[st->count];
	}else assert(!"empty stack");
}

/** ********************************************************************
 @file		stackLib.h
 @date		2013-11-09 15:55
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.02

 A short library for work with a Stack_t
***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stackLib.h>

#define repeat(x)	for(int cnt_rpt = 0; cnt_rpt < x; cnt_rpt++)
#define repeatI(x)	for(int I = 0; I < x; I++)
#define print(expr) printf(#expr " = %d\n", expr);

//----------------------------------------------------------------------
/** ********************************************************************
 Constracts an empty sctack
 @param			this_	link to the memory for a stack
***********************************************************************/
void Stack_constract(Stack_t *this_){
	ASSERT(this_)
	*( (int*) &(this_ -> maxSize) ) = MaxSizeStackT;
	assert(this_ -> count >= 0, "second use of the stack");
	this_ -> count = 0;
	STACK_ASSERT
}
/** ********************************************************************
 Allocates memory and constracts a sctack
 @return		link to the memory with a new stack
***********************************************************************/
Stack_t* Stack(){
	Stack_t* this_;
	this_  = (Stack_t*) calloc(sizeof(Stack_t), 1);
	Stack_constract(this_);
	STACK_ASSERT
	return this_;
}
/** ********************************************************************
 Distracts a sctack
 @param			this_	link to the memory for a stack
***********************************************************************/
void Stack_distruct(Stack_t *this_){
	STACK_ASSERT
	this_ -> count = -1;
}
/** ********************************************************************
 Checks stack condition
 @param[in]		this_	link for a stack
 @return 		if everything is good
***********************************************************************/
int Stack_OK(const Stack_t *this_){
	return (this_ && (0 <= this_ -> count) && (this_ -> count <= this_ -> maxSize) && (this_ -> arr));
}
/** ********************************************************************
 Prints the content of a stack
 @param[in]		this_	link for a stack
***********************************************************************/
void Stack_Dump(const Stack_t *this_){ //elmStack_t = int
	printf("!# Stack_t // %s\n", (Stack_OK(this_))? "ok" : "BROKEN STACK");
	if(!this_) return;
	printf("!# in #%p\n", (this_ -> arr));
	printf("!# count = %d < %d == %d\n", this_ -> count, this_ -> maxSize, MaxSizeStackT);
	printf("!# arr:\n");
	if(this_ -> arr) repeatI(this_ -> count)
		printf("!#   %d : %d in #%p\n", I, this_ -> arr[I], (this_ -> arr + I));
}
//---------------------------
/** ********************************************************************
 Pushes an element to the stack
 @param			this_	link for a stack
 @param[in]		elm		an element
 @note 			stack overflow exeption is possible
***********************************************************************/
void Stack_push(Stack_t *this_, elmStack_t elm){
	STACK_ASSERT
	assert(this_->count  <  this_->maxSize - 1, "stack overflow")
	this_->arr[this_->count]  =  elm;
	this_->count  ++;
}
/** ********************************************************************
 Pops an element from the stack
 @param			this_	link for a stack
 @return		poped element
 @note 			empty stack exeption is possible
***********************************************************************/
elmStack_t Stack_pop(Stack_t *this_){
	STACK_ASSERT
	assert(this_->count > 0, "empty stack");
	this_->count --;
	return this_->arr[this_->count];
}

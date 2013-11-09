/** ********************************************************************
 @file		stackLib.h
 @date		2013-11-09 15:55
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.02

 A short library for work with a Stack_t
***********************************************************************/

#ifndef STACK_LIB_H //STACK_LIB_H
#define STACK_LIB_H

#ifdef __cplusplus
extern "C" {
#endif 				//C++ compatibility
//----------------------------------------------------------------------
#define printErr(mess)\
	printf("!#ERROR: %s :: file: %s; line: %d\n", mess, __FILE__, __LINE__) //print error massage
	
#ifndef UNDEBUG 	//UNDEBUG
#define assert(cond, mess) 					\
	if (!(cond)) {							\
		printErr(#mess ":: (" #cond ")");	\
		abort();							\
	}
	
#define ASSERT(cond)\
	assert(cond, "-?-")

#define stack_Assert(st) 			\
	if(!Stack_OK(st)){ 				\
	Stack_Dump(st); 				\
	printErr("broken stack" #st);	\
	abort();						\
}

#define STACK_ASSERT\
	stack_Assert(this_)

#else 				//UNDEBUG

#define assert(cond, mess)
#define ASSERT(cond)
#define stack_Assert(st)
#define STACK_ASSERT

#endif 				//UNDEBUG
//----------------------------------------------------------------------

/** ********************************************************************
 @typedef	elmStack_t
 @brief		stack element type
 
 Type for elements of a Stack_t
***********************************************************************/
typedef int elmStack_t;
/** ********************************************************************
 @struct	Stack_t
 @brief		Object, containing one stack
 
 Encapsulates stack
***********************************************************************/
#define MaxSizeStackT 100	///<Max number of elements in a Stack_t
typedef struct Stack_t{
		const int maxSize;	///<Max number of elements in the stack
		int count;			///<Current number of elements in the stack
		elmStack_t arr[MaxSizeStackT]; ///<Elements of the stack
} Stack_t;

//------------------------
void Stack_constract(Stack_t *st);
Stack_t* Stack();
void Stack_distruct(Stack_t *st);
int Stack_OK(const Stack_t *st);
void Stack_Dump(const Stack_t *st);//elmStack_t = int

void push(Stack_t *st, elmStack_t x);
elmStack_t pop(Stack_t *st);
//----------------------------------------------------------------------
#ifdef __cplusplus
}
#endif 				//C++ compatibility (end)

#endif 				//STACK_LIB_H

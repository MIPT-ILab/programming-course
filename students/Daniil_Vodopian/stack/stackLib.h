/** ********************************************************************
 @file		stackLib.h
 @date		2013-11-09 15:55
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.02

 A short library for work with a Stack_t
***********************************************************************/
#ifndef _STACK_LIB_H_ //_STACK_LIB_H_
#define _STACK_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 				//C++ compatibility
//----------------------------------------------------------------------
#include <errOutput.h>
	
#ifndef UNDEBUG 	//UNDEBUG

#define Stack_Assert(this_) 				\
	struct_Assert(Stack, this_)

#define STACK_ASSERT						\
	Stack_Assert(this_)

#else 				//UNDEBUG

#define Stack_Assert(this_)
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
void 	Stack_constract(Stack_t *this_);
Stack_t* Stack();
void 	Stack_distruct(Stack_t *this_);
int 	Stack_OK(const Stack_t *this_);
void 	Stack_Dump(const Stack_t *this_);//elmStack_t = int

void 	Stack_push(Stack_t *this_, elmStack_t elm);
elmStack_t Stack_pop(Stack_t *this_);
//----------------------------------------------------------------------
#ifdef __cplusplus
}
#endif 				//C++ compatibility (end)

#endif 				//_STACK_LIB_H_

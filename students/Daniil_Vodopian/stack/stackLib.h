/** ********************************************************************
 @file		stackLib.h
 @date		2013-10-27 23:03
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.01

 A short library for work with a Stack_t
***********************************************************************/

#ifndef STACK_LIB_H //STACK_LIB_H
#define STACK_LIB_H

#ifdef __cplusplus
extern "C" {
#endif //C++ compatibility
//----------------------------------------------------------------------
#ifndef UNDEBUG
#define ASSERT(cond) \
	if (!(cond)) {\
		printf("ERROR: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__);\
		abort();\
	}
#else
#define ASSERT(cond)
#endif //DEBUG

#define Stack_assert_d(st, mess) 		\
	if(!Stack_OK(st)){ 					\
	Stack_Dump(st); 					\
	assert(!mess);						\
}										//*/
//----------------------------------------------------------------------

/** ********************************************************************
 @typedef	elmStack_t
 @brief		stack elemen type
 
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
Stack_t Stack();
void Stack_distruct(Stack_t *st);
int Stack_OK(const Stack_t *st);
void Stack_Dump(const Stack_t *st);//elmStack_t = int



//void Stack_assert(const Stack_t *st, char *message);
//----------------------------------------------------------------------
void push(Stack_t *st, elmStack_t x);
elmStack_t pop(Stack_t *st);
//----------------------------------------------------------------------
#ifdef __cplusplus
}
#endif //C++ compatibility (end)

#endif //STACK_LIB_H

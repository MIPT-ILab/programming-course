/** ********************************************************************
 @file		operLib.h
 @date		2013-11-09 22:17
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.01

 Oper_t, OperArr_t and utils for "assembler emulator"
***********************************************************************/
#ifndef _OPER_LIB_H_ //_OPER_LIB_H_
#define _OPER_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 				//C++ compatibility
//----------------------------------------------------------------------
#include <errOutput.h>
	
#ifndef UNDEBUG 	//UNDEBUG

#define Oper_Assert(this_) 				\
	struct_Assert(Oper, this_)

#define OPER_ASSERT						\
	Oper_Assert(this_)

#else 				//UNDEBUG

#define Oper_Assert(this_)
#define OPER_ASSERT

#endif 				//UNDEBUG
//----------------------------------------------------------------------
#define maxNameLen 8
typedef void (*OperFunc_t) (int id); 
typedef struct Oper_t{
	char name[maxNameLen + 1];
	int input;
	int output;
	OperFunc_t func;
	//void (*fun) (Oper_t this_); ???
} Oper_t;

void 	Oper_constract(Oper_t *this_);
Oper_t* Oper(char* name, int input, int output, OperFunc_t func);
void 	Oper_distruct(Oper_t *this_);
int 	Oper_OK(const Oper_t *this_);
void 	Oper_Dump(const Oper_t *this_);
//---------------------------------------------------
#define maxOper 20
typedef struct OperArr_t{
	Oper_t operArr[maxOper];
	int operCount;
} OperArr_t;

void 	OperArr_constract(OperArr_t *this_);
OperArr_t* OperArr();
void 	OperArr_distruct(OperArr_t *this_);
int 	OperArr_OK(const OperArr_t *this_);
void 	OperArr_Dump(const OperArr_t *this_);

void 	OperArr_add(OperArr_t *this_, Oper_t oper);
int 	OperArr_find(OperArr_t *this_, char* name);

//----------------------------------------------------------------------
#ifdef __cplusplus
}
#endif 				//C++ compatibility (end)

#endif 				//_OPER_LIB_H_

/** ********************************************************************
 @file		operLib.c
 @date		2013-11-09 22:37
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.01

 Oper_t and utils for "assembler emulator"
***********************************************************************/
#include <stdlib.h>
#include <operLib.h>
//----------------------------------------------------------------------
/** ********************************************************************
 Constracts a blank operator
 @param			this_	link to the memory for an operator
***********************************************************************/
void 	Oper_constract(Oper_t *this_){
	ASSERT(this_)
	assert(this_->input >= 0 && this_->output >= 0, "second use of the operator");
	this_->name 	= "";
	this_->input 	= 0;
	this_->output 	= 0;
	this_->func 	= NULL;
	STACK_ASSERT
}

Oper_t* Oper(char* name, int input, int output, OperFunc_t func);
void 	Oper_distruct(Oper_t *this_);
int 	Oper_OK(const Oper_t *this_);
void 	Oper_Dump(const Oper_t *this_);

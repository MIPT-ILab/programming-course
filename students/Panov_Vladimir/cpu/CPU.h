#pragma once

#include "Stack.h"
#include "List.h"
#include <iostream>
#include <string>

class CPU
{
public:
	CPU(int size);
	~CPU();
	bool run(const char* file);
	// FIXME A lot of spaces. Check style
	// FIXME I think, that it can be be 'const'
	bool assemble	(const char *source_file, char *asm_file	 );
	// FIXME I think, that it can be be 'const'
	bool disassemble(const char *asm_file	  ,	char *source_file);
	// FIXME I think, that it can be be 'const'
	bool run_assembled(const char* asm_file);
private:
	Stack *memory_;
	mytype reg_ax_ = 0;
	// FIXME I think, that it can be be 'const'
	bool get_jump(List *list, const char *file);
	// FIXME I think, that it can be be 'const'
	bool get_asm_jump(List *list, const char *file);
	bool push_ax();
	bool pop_ax();
	// FIXME Why Value but not 'value'? Check this and .cpp file.
	bool push(int Value);
	bool add();
	bool mul();
	bool out();
	bool jb();
};


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
	bool assemble	(const char *source_file, char *asm_file	 );
	bool disassemble(const char *asm_file	  ,	char *source_file);
	bool run_assembled(const char* asm_file);
private:
	Stack *memory_;
	mytype reg_ax_ = 0;
	bool get_jump(List *list, const char *file);
	bool get_asm_jump(List *list, const char *file);
	bool push_ax();
	bool pop_ax();
	bool push(int Value);
	bool add();
	bool mul();
	bool out();
	bool jb();
};


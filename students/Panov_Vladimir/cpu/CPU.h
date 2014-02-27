#pragma once

#include "Stack.h"
#include <iostream>
#include <string>

class CPU
{
public:
	Stack *memory_;
	CPU(int size);
	~CPU();
	bool run(char* file);
	bool assemble	(char *source_file, char *asm_file	 );
	bool disassemble(char *asm_file	  ,	char *source_file);
	bool run_assembled(char* asm_file);
private:
	bool push(int Value);
	bool add();
	bool mul();
	bool out();
};


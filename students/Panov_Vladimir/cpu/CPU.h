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
  //FIXME source_file* should be const. assemble method may be const itself,
  // while it does not modifies object state
	bool assemble	(char *source_file, char *asm_file	 );

  //FIXME asm_file* should be const. assemble method may be const itself,
  // while it does not modifies object state
	bool disassemble(char *asm_file	  ,	char *source_file);
	bool run_assembled(char* asm_file);
private:
	bool push(int Value);
	bool add();
	bool mul();
	bool out();
};


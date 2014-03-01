// FIXME Fix encoding
// CPU.cpp: определяет точку входа для консольного приложения.
//
// FIXME You use copy o Stack.h and Stack.cpp
// Try to build your project that it will depend from Stack in a other folder
// 'stack'. And remove these copies of file
#include <stdio.h>
#include "CPU.h"
#include <string.h>

int main() {
	CPU cpu1(10);
	char file[20] = "input.txt";
	char asm_file[20] = "asm.txt";
	cpu1.assemble(file, asm_file);
	cpu1.disassemble(asm_file, "out.txt");
	cpu1.run(file);
	cpu1.run_assembled(asm_file);
	getchar();
	return 0;
}

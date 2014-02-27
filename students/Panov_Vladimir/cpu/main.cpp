// CPU.cpp: определяет точку входа для консольного приложения.
//

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
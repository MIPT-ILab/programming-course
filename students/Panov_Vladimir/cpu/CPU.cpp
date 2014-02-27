#include "CPU.h"

#define CPU_PUSH 1
#define CPU_ADD  2
#define CPU_MUL  3
#define CPU_OUT  4

CPU::CPU(int size) {
	memory_ = new Stack(size);
}


CPU::~CPU()
{
	delete memory_;
}

bool CPU::push(int Value) {
	memory_->Push(Value);
	return true;
}

bool CPU::add() {
	mytype a = 0;
	mytype b = 0;
	if (!memory_->Pop(&a)) {
		return false;
	}
	if (!memory_->Pop(&b)) {
		memory_->Push(a);
		return false;
	}
	memory_->Push(a + b);
	return true;
}

bool CPU::mul() {
	mytype a = 0;
	mytype b = 0;
	if (!memory_->Pop(&a)) {
		return false;
	}
	if (!memory_->Pop(&b)) {
		memory_->Push(a);
		return false;
	}
	memory_->Push(a * b);
	return true;
}

bool CPU::out() {
	mytype a = 0;
	mytype b = 0;
	if (!memory_->Pop(&a)) {
		return false;
	}
	printf("OUT: %lf\n", a);
	return true;
}

bool CPU::run(char* file) {
	FILE *f_in = fopen(file, "r");
	if (!f_in) {
		printf("%s, FILE NOT FOUND!!!\n", file);
		return false;
	}
	printf("file find\n");
	char cmd_str[100];
	while (fgets(cmd_str, sizeof(cmd_str), f_in)) {
		char cmd[5];
		bool is_done = false;
		sscanf(cmd_str, "%s", cmd);
		if (!is_done && !strcmp(cmd, "push")) {
			int num;
			sscanf((cmd_str+strlen(cmd)), "%d", &num);
			is_done = push(num);
		}
		if (!is_done && !strcmp(cmd, "add")) {
			is_done = add();
		}
		if (!is_done && !strcmp(cmd, "mul")) {
			is_done = mul();
		}
		if (!strcmp(cmd, "out")) {
			is_done = out();
		}
		if (!is_done) {
			printf("#ERROR in file: %s", file);
			return false;
		}
	}
	fclose(f_in);
	memory_->Dump();
	return true;
}

bool CPU::assemble(char *source_file, char *asm_file) {
	ASSERT(source_file);
	ASSERT(asm_file);
	FILE *src_file = fopen(source_file, "r");
	if (!src_file) {
		printf("#%s file not found!\n", source_file);
		return false;
	}
	FILE *asm_File = fopen(asm_file, "w");
	if (!asm_File) {
		printf("#%s file not create!\n", asm_file);
		fclose(src_file);
		return false;
	}
	char cmd_str[100];
	while (fgets(cmd_str, sizeof(cmd_str), src_file)) {
		char cmd[5];
		bool is_done = false;
		sscanf(cmd_str, "%s", cmd);
		if (!is_done && !strcmp(cmd, "push")) {
			int num;
			sscanf((cmd_str + strlen(cmd)), "%d", &num);
			fprintf(asm_File, "%d %d\n", CPU_PUSH, num);
			is_done = true;
		}
		if (!is_done && !strcmp(cmd, "add")) {
			fprintf(asm_File, "%d\n", CPU_ADD);
			is_done = true;
		}
		if (!is_done && !strcmp(cmd, "mul")) {
			fprintf(asm_File, "%d\n", CPU_MUL);
			is_done = true;
		}
		if (!is_done && !strcmp(cmd, "out")) {
			fprintf(asm_File, "%d\n", CPU_OUT);
			is_done = true;
		}
		if (!is_done) {
			printf("#ERROR, file: %s is not all recognize", source_file);
		}
	}
	fclose(src_file);
	fclose(asm_File);
	return true;
}

bool CPU::disassemble(char *asm_file, char *source_file) {
	ASSERT(asm_file);
	ASSERT(source_file);
	FILE *asm_File = fopen(asm_file, "r");
	if (!asm_File) {
		printf("#%s file not create!\n", asm_file);
		return false;
	}
	FILE *src_file = fopen(source_file, "w");
	if (!src_file) {
		printf("#%s file not found!\n", source_file);
		fclose(asm_File);
		return false;
	}
	char cmd_str[100];
	while (fgets(cmd_str, sizeof(cmd_str), asm_File)) {
		int cmd;
		sscanf(cmd_str, "%d", &cmd);
		switch (cmd)
		{
		case CPU_PUSH:
			int num;
			sscanf(cmd_str, "%d %d", &cmd, &num);
			fprintf(src_file, "push %d\n", num);
			break;
		case CPU_ADD:
			fprintf(src_file, "add\n");
			break;
		case CPU_MUL:
			fprintf(src_file, "mul\n");
			break;
		case CPU_OUT:
			fprintf(src_file, "out\n");
			break;
		default:
			printf("#FILE: %s is not all recognize", asm_file);
			return false;
			break;
		}
	}
	fclose(src_file);
	fclose(asm_File);
	return true;
}

bool CPU::run_assembled(char *asm_file) {
	FILE *f_in = fopen(asm_file, "r");
	if (!f_in) {
		printf("%s, FILE NOT FOUND!!!\n", asm_file);
		return false;
	}
	printf("file find\n");
	char cmd_str[100];
	while (fgets(cmd_str, sizeof(cmd_str), f_in)) {
		int cmd = -1;
		sscanf(cmd_str, "%d", &cmd);
		switch (cmd) {
		case CPU_PUSH: 
			int num;
			sscanf(cmd_str, "%d %d", &cmd, &num);
			push(num);
			break;
		case CPU_ADD:
			add();
			break;
		case CPU_MUL:
			mul();
			break;
		case CPU_OUT:
			out();
			break;
		default:
			printf("#Command is not recognize\n");
			return false;
			break;
		}
	}
	fclose(f_in);
	memory_->Dump();
	return true;
}
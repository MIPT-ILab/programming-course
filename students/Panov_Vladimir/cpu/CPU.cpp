#include "CPU.h"

#define CPU_PUSH	 1
#define CPU_ADD		 2
#define CPU_MUL		 3
#define CPU_OUT		 4
#define CPU_PUSH_AX	 5
#define CPU_POP_AX	 6
#define CPU_JUMP	 7

CPU::CPU(int size) {
	memory_ = new Stack(size);
}


CPU::~CPU()
{
	delete memory_;
}

bool CPU::pop_ax() {
	ASSERT(memory_);
	return memory_->Pop(&reg_ax_);
}

bool CPU::push_ax() {
	ASSERT(memory_);
	return memory_->Push(reg_ax_);
}

bool CPU::push(int Value) {
	ASSERT(memory_);
	memory_->Push(Value);
	return true;
}

bool CPU::add() {
	ASSERT(memory_);
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
	ASSERT(memory_);
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
	ASSERT(memory_);
	mytype a = 0;
	mytype b = 0;
	if (!memory_->Pop(&a)) {
		return false;
	}
	printf("OUT: %lf\n", a);
	return true;
}

bool CPU::jb() {
	ASSERT(memory_);
	mytype a = 0;
	mytype b = 0;
	if (!memory_->Pop(&a)) {
		return false;
	}
	if (!memory_->Pop(&b)) {
		memory_->Push(a);
		return false;
	}
	if (a <= b)
		return false;
	return true;
}

bool CPU::get_jump(List *list, const char *file) {
	ASSERT(list);
	ASSERT(file);
	FILE *f_in = fopen(file, "r");
	if (!f_in) {
		printf("%s, FILE NOT FOUND!!!\n", file);
		return false;
	}
	printf("file find\n");
	int num_jump = 0;
	char cmd_str[100];
	for (int i = 0; fgets(cmd_str, sizeof(cmd_str), f_in); i++) {
		if (cmd_str[0] == ':') {
			num_jump++;
			char jump[10];
			sscanf(cmd_str, "%s", jump);
			list->add(jump, i, num_jump);
		}
	}
	fclose(f_in);
	return true;
}

bool CPU::get_asm_jump(List *list, const char *file){
	ASSERT(list);
	ASSERT(file);
	FILE *File = fopen(file, "r");
	if (!File) {
		return false;
	}
	char cmd_str[1024];
	int cmd;
	int num_jump = 0;
	while (fgets(cmd_str, 1024, File)) {
		sscanf(cmd_str, "%d", &cmd);
		if (cmd == CPU_JUMP) {
			int pos;
			sscanf(cmd_str, "%d %d", &cmd, &pos);
			char key[100];
			sprintf(key, ":%d", pos);
			list->add(key, pos, num_jump);
			num_jump++;
		}
	}
	list->dump();
	return true;
}

bool CPU::run(const char* file) {
	ASSERT(file);
	ASSERT(memory_);
	List list;
	if (!get_jump(&list, file)) {
		printf("ERROR in file %s", file);
		return false;
	}
	FILE *f_in = fopen(file, "r");
	if (!f_in) {
		printf("%s, FILE NOT FOUND!!!\n", file);
		return false;
	}
	printf("file find\n");
	char cmd_str[100];
	list.dump();
	while (fgets(cmd_str, sizeof(cmd_str), f_in)) {
		char cmd[10];
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
		if (!is_done && !strcmp(cmd, "push_ax")) {
			is_done = push_ax();
		}
		if (!is_done && !strcmp(cmd, "pop_ax")) {
			is_done = pop_ax();
		}
		if (!is_done && !strcmp(cmd, "jb")) {
			if (jb()) {
				char jump[10];
				sscanf(cmd_str + strlen(cmd), "%s", jump);
				int pos = list.search(jump);
				if (pos != -1) {
					int result = fseek(f_in, 0L, SEEK_SET);
					if (result) {
						printf("ERROR in file %s\n", file);
						return false;
					}
					for (int i = 0; i <= pos && fgets(cmd_str, sizeof(cmd_str), f_in); i++);
				}
				else {
					printf("ERROR jump not found in file: %s cmd: %s\n", file, cmd);
					return false;
				}
			}
			is_done = true;
		}
		if (!is_done && cmd[0] == ':') {
			is_done = true;
		}
		if (!is_done) {
			printf("#ERROR in file: %s cmd: %s", file, cmd);
			return false;
		}
	}
	fclose(f_in);
	memory_->Dump();
	return true;
}

bool CPU::assemble(const char *source_file, char *asm_file) {
	ASSERT(source_file);
	ASSERT(asm_file);
	List list;
	if (!get_jump(&list, source_file)) {
		printf("ERROR in file %s", source_file);
		return false;
	}
	list.dump();
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
		char cmd[10];
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
		if (!is_done && !strcmp(cmd, "push_ax")) {
			fprintf(asm_File, "%d\n", CPU_PUSH_AX);
			is_done = true;
		}
		if (!is_done && !strcmp(cmd, "pop_ax")) {
			fprintf(asm_File, "%d\n", CPU_POP_AX);
			is_done = true;
		}
		if (!is_done && cmd[0] == ':') {
			is_done = true;
		}
		if (!is_done && !strcmp(cmd, "jb")) {
			char jump[10];
			sscanf(cmd_str + strlen(cmd), "%s", jump);
			int num_jump = 0;
			int pos = list.search(jump, &num_jump);
			printf("key: %s, pos: %d, num:%d\n", jump, pos, num_jump);
			if (pos < 0) {
				printf("ERROR in file: %s cmd: %s", source_file, cmd_str);
				return false;
			}
			fprintf(asm_File, "%d %d\n", CPU_JUMP, pos - num_jump + 1);
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

bool CPU::disassemble(const char *asm_file, char *source_file) {
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
	List list;
	if (!get_asm_jump(&list, asm_file)) {
		fclose(asm_File);
		fclose(src_file);
		printf("ERROR!!! in file: %s", asm_file);
		return false;
	}
	char cmd_str[100];
	int num_jump = 0;
	for (int pos = 0; fgets(cmd_str, sizeof(cmd_str), asm_File); pos++) {
		char *key = list.search(pos - num_jump);
		if (key) {
			fprintf(src_file, "%s\n", key);
			pos++;
			num_jump++;
		}
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
		case CPU_POP_AX:
			fprintf(src_file, "pop_ax\n");
			break;
		case CPU_PUSH_AX:
			fprintf(src_file, "push_ax\n");
			break;
		case CPU_JUMP:
			int jump_pos;
			sscanf(cmd_str, "%d %d", &cmd, &jump_pos);
			fprintf(src_file, "jb %s\n", list.search(jump_pos));
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

bool CPU::run_assembled(const char *asm_file) {
	ASSERT(asm_file);
	ASSERT(memory_);
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
		case CPU_POP_AX:
			pop_ax();
			break;
		case CPU_PUSH_AX:
			push_ax();
			break;
		case CPU_JUMP:
			if (jb()) {
				int pos;
				sscanf(cmd_str, "%d %d", &cmd, &pos);
				if (pos < 0) {
					printf("ERROR in file: %s cmd: %s", asm_file, cmd_str);
					return false;
				}
				int result = fseek(f_in, 0L, SEEK_SET);
				if (result) {
					printf("ERROR in file %s\n", asm_file);
					return false;
				}
				for (int i = 0; i < pos && fgets(cmd_str, sizeof(cmd_str), f_in); i++);
			}
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
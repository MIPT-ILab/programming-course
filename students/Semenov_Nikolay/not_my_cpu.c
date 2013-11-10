/**
 * File: .....
 */

#define DEBUG_MODE

#define PUSH_N 1 << 1
#define PUSH_R 1 << 2
#define POP    1 << 3
#define ADD    1 << 4
#define MUL    1 << 5
#define JMP    1 << 6
#define JBE    1 << 7
// ....

#define NUM_OF_REGISTERS 4
#define AX 0
#define BX 1
#define CX 2
#define DX 3

/**
 * File: processor.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
    Stack
*/
#define STACK_LIMIT 100

static float stack_start[STACK_LIMIT];
static float *stack_top = stack_start;

void stack_push(float elem) {
	assert(stack_top < stack_start + STACK_LIMIT);
	*stack_top++ = elem;
}

float stack_pop() {
	assert(stack_start < stack_top);
	return *--stack_top;
}

/*
    Processor's data
*/
int current;
void *data;
size_t data_len;

float registers[NUM_OF_REGISTERS];

/*
    Handlers
*/

void handle_push(bool is_reg) {
    if(is_reg) {
        int reg = ((int *) data)[current++];
        stack_push(registers[reg]);
    } else {
        float number = ((float *) data)[current++];
        stack_push(number);
	}
}

void handle_pop(){
	int reg = ((int *) data)[current++];
	registers[reg] = stack_pop();
}

void handle_add() {
    stack_push(stack_pop() + stack_pop());
}

void handle_mul() {
    stack_push(stack_pop() * stack_pop());
}

void handle_jmp() {
    current = ((int *) data)[current];
}

void handle_jbe() {
    float a = stack_pop();
    float b = stack_pop();
    stack_push(b);
    stack_push(a);
    
    a > b ? handle_jmp() : ++current; 
}


/*#ifdef DEBUG_MODE
#define DEBUG
*/

/*
    Launch
*/
void read_to_data(const char *path) {
    char *src;
    FILE *fp = fopen(path, "r");
    assert(fp);
    
    // Seek to end
    int stat = fseek(fp, 0L, SEEK_END);
    assert(stat);
    
    // Get size of file
    size_t size = ftell(fp);
    assert(size != -1);
    
    // Seek to start
    int status = fseek(fp, 0L, SEEK_SET);
    assert(status);
    
    // Allocate the buffer
    data = calloc(size, sizeof(char));
    size_t new_size = fread(src, sizeof(char), size, fp);
    assert(new_size);
    
    data_len = size / sizeof(int);
    fclose(fp);
}

void run(const char *path) {
    read_to_data(path);
    
    while(current < data_len) {
        ++current;
        switch(((int *) data)[current-1]) {
            case PUSH_N: handle_push(false); break;
            case PUSH_R: handle_push(true); break;
            case POP: handle_pop(); break;
            case ADD: handle_add(); break;
            case MUL: handle_mul(); break;
            case JMP: handle_jmp(); break;
            case JBE: handle_jbe(); break;
            default:
                assert(0 & 0xBAD);
        }
    }
}

void complete() {
    free(data);
}

int main(int argc, const char *argv[]) {
    assert(sizeof(int) == sizeof(float));
    
    for(int i = 1; i < argc; ++i) {
        run(argv[i]);
        complete();
    }
    
    return 0;
}


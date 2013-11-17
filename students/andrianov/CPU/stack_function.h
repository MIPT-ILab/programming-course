#ifndef STACK_FUNCTION_H_INCLUDED
#define STACK_FUNCTION_H_INCLUDED



#define ST_SIZE 10

struct Stack_t
{
    int count;
    float data[ST_SIZE];
};

typedef struct Stack_t Stack_t;


int stack_construct ( Stack_t* st );

int stack_destruct ( Stack_t* st );

int stack_OK ( const Stack_t* st );

int stack_push ( Stack_t* st, float val );

float stack_pop ( Stack_t* st );

int stack_full ( Stack_t* st );

int stack_empty ( Stack_t* st );

int stack_dump ( Stack_t* st );


#endif // STACK_FUNCTION_H_INCLUDED

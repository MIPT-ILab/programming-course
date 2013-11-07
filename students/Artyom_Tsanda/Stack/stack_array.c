#include <stdio.h>

#define STACKSIZE 200

typedef struct stack{
            unsigned int size;
            int elements[STACKSIZE];
            unsigned int is_initialized;
            } STACK;

//----------------------------------------------initialize(STACK *link)---------------------------------------
//                                       nullifies the stack___can be used only once
void initialize(STACK *link)
{
    if(link->is_initialized==NULL){
        printf("Error: you can not initialize stack one more time\n");
        abort();
    }else{
        int i=0;

        link->size=0;
        for(i;i<STACKSIZE;i++)
            link->elements[i]=NULL;
        link->is_initialized=NULL;
    }
}

//----------------------------------------------is_ok(STACK *link)--------------------------------------------
//                               check if the stack was initialaized_____if not abort prodram
void is_ok(STACK *link)
{
    if(link->is_initialized!=NULL){
        printf("Error: any operation is impossible without initializing, please use initialize(STACK *link) function to do it\n");
        abort();
    }
}

//-------------------------------------------push(STACK *link, int new_value)---------------------------------
void push(STACK *link, int new_value)
{
    is_ok(link);

    if(link->size==STACKSIZE){
        printf("Error: stack overflow\n");
        abort();
    }else{
        link->elements[link->size++]=new_value;
    }
}

//----------------------------------------------size(STACK *link)---------------------------------------------
//                                    returns number of elements in the stack
int size(STACK *link)
{
    is_ok(link);

    printf("%ud\n",link->size);
}

//----------------------------------------------dump(STACK *link)---------------------------------------------
//                                        display all elements of the stack
void dump(STACK *link)
{
    is_ok(link);

    if(link->size==0){
        printf("Stack is empty\n");
        return ;
    }

    unsigned int i=link->size;

    for(i;i>0;)
        printf("%d\n",link->elements[--i]);
}

//----------------------------------------------delete(STACK *link)-------------------------------------------
//                                        delete the last element of the stack
void delete(STACK *link)
{
    is_ok(link);

    if(link->size==0){
        printf("Error: stack underflow\n");
        abort();
    }else{
        link->elements[--link->size]=NULL;
    }
}

//----------------------------------------------pop(STACK *link)----------------------------------------------
//                                       returns the content of the last element
int pop(STACK *link)
{
    is_ok(link);

    if(link->size==0){
        printf("Error: stack underflow\n");
        abort();
    }else{
        return link->elements[link->size-1];
    }
}






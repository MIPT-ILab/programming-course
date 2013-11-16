#include <stdio.h>
#include <malloc.h>
// FIXME I think, that you need also 'previous' pointer
typedef struct element
{
    int value;
    struct element *previous;
} ELEMENT;
// FIXME may be you can add 'size' of stack?
typedef struct stack
{
    ELEMENT *head;
    unsigned int is_initialized;
} STACK;

//----------------------------------------------initialize(STACK *link)---------------------------------------
//                                       nullifies the stack___can be used only once
void initialize(STACK *link)
{
    // FIXME may be assert this?
    if(link->is_initialized==NULL){
        printf("Error: you can not initialize stack one more time\n");
        abort();
    }else{
        link->head=NULL;
        link->is_initialized=NULL;
    }
}

//----------------------------------------------is_ok(STACK *link)--------------------------------------------
//                               check if the stack was initialaized_____if not abort prodram
void is_ok(STACK *link)
{
    // FIXME may be assert this?
    if(link->is_initialized!=NULL){
        printf("Error: any operation is impossible without initializing, please use initialize(STACK *link) function to do it\n");
        abort();
    }
}

//-------------------------------------------push(STACK *link, int new_value)---------------------------------
void push(STACK *link, int new_value)
{
    is_ok(link);

    ELEMENT *new_element=(ELEMENT*) malloc(sizeof(ELEMENT));
    // FIXME may be assert this?
    if(new_element == NULL){
        printf("Error: no space available\n");
        abort();
    }else{
        new_element->value=new_value;
        new_element->previous=link->head;

        link->head=new_element;
    }
}

//----------------------------------------------size(STACK *link)---------------------------------------------
//                                    returns number of elements in the stack
int size(STACK *link)
{
    is_ok(link);

    ELEMENT *a=link->head;
    int i=0;

    while(a!=NULL){
        a=a->previous;
        i++;
    }

    return i;
}

//----------------------------------------------dump(STACK *link)---------------------------------------------
//                                        display all elements of the stack
void dump(STACK *link)
{
    is_ok(link);

    ELEMENT *a=link->head;

    if(a==NULL){
        printf("Stack is empty\n");
        return ;
    }
    while(a!=NULL){
        printf("%d\n",a->value);
        a=a->previous;
    }
}

//----------------------------------------------delete(STACK *link)-------------------------------------------
//                                        delete the last element of the stack
void delete(STACK *link)
{
    is_ok(link);
    // FIXME may be assert this?
    if(link->head==NULL){
        printf("Error: stack is already empty, delete operation is impossible\n");
    }

    ELEMENT *a=(link->head);
    (link->head)=(link->head)->previous;
    free(a);
}

//----------------------------------------------pop(STACK *link)----------------------------------------------
//                                       returns the content of the last element
//FIXME Pop MUST destroy stack's head.
int pop(STACK *link)
{
    is_ok(link);
    // FIXME may be assert this?
    if(link->head==NULL){
        printf("Error: stack is empty, pop operation is impossible\n");
    }


}




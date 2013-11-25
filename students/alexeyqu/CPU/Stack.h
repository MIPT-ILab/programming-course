/** ***************************************************************************
 * @file    Stack.h
******************************************************************************/

#ifndef STACKLIB
    #define STACKLIB

#define STACK_CHECK( stack )\
    if (Stack_Error_Catch (Stack_Is_OK (stack), "") == STACK_ERR)\
    {\
        exit (1);\
    }

typedef struct Stack
{
    double* my_stack_data; //!< Pointer to data set
    unsigned int cur_size, max_size; //!< current size and maximum size of stack
    int isenable; //!< Flag that indicates if the stack is enabled
} Stack_t;

enum STACK_ERR
{
    STACK_OK = 0,
    STACK_ERR = -1,
    STACK_ERR_INIT = 1,
    STACK_ERR_WR_SZ = 2,
    STACK_ERR_NULL = 3,
};

const int Start_Max_Size = 2;

/** ***************************************************************************
 * Stack_Test   lets the user to test program
 *
 * @return  0\-1 if there weren't\were any\some sintakes while testing
******************************************************************************/
int Stack_Test();

/** ***************************************************************************
 * Stack_Construct  constructs the stack
 *
 * @param[out]  stack pointer to stack
 *
 * @return      0\1 depending on mistakes
******************************************************************************/
int Stack_Construct (Stack_t* stack);

/** ***************************************************************************
 * Stack_Destruct  destructs the stack
 *
 * @param[out]   stack pointer to stack
 *
 * @return      0\1 depending on mistakes
******************************************************************************/
int Stack_Destruct (Stack_t* stack);

/** ***************************************************************************
 * Stack_Is_Empty   checks is the stack is empty
 *
 * @param   stack stack
 *
 * @return  0\1 depending on emptyness of stack
******************************************************************************/
int Stack_Is_Empty (const Stack_t* stack);

/** ***************************************************************************
 * Stack_Is_Full   checks is the stack is full
 *
 * @param   stack stack
 *
 * @return  0\1 depending on fullness of stack
******************************************************************************/
int Stack_Is_Full (const Stack_t* stack);

/** ***************************************************************************
 * Stack_Is_OK   checks is the stack is OK
 *
 * @param   stack stack
 *
 * @return  0\1 depending on OKness of stack
******************************************************************************/
int Stack_Is_OK (const Stack_t* stack);

/** ***************************************************************************
 * Need_More_Memory   allocates more free space in case if stack is full
 *
 * @param   stack pointer to stack
 *
 * @return  0\1 - if the allocation was successful
******************************************************************************/
int Need_More_Memory (Stack_t* stack);

/** ***************************************************************************
 * Stack_Push   push the value into the stack
 *
 * @param[out]  stack pointer to stack
 * @param       value   value to push
 *
 * @return  0\1 depending on presence of mistakes
******************************************************************************/
int Stack_Push (Stack_t* stack, const double value);

/** ***************************************************************************
 * Stack_Pop    pops out value from the stack
 *
 * @param[out]  stack pointer to stack
 *
 * @return      popped value
******************************************************************************/
double Stack_Pop (Stack_t* stack);

/** ***************************************************************************
 * Stack_Dump   prints dump info for stack
 *
 * @param[out]  stack pointer to stack
******************************************************************************/
void Stack_Dump (const Stack_t* stack);

/** ***************************************************************************
 * Stack_Error_Catch    reacts on errors that occured
 *
 * @param   err_code    error code
 * @param   msg         message to print
 * @param   additional data
******************************************************************************/
int Stack_Error_Catch (int err_code, const char* msg, ...);

#endif

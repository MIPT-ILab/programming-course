//{========================================================================================================
//! @file    stack_array.c
//! @date    2013-11-17 22:35
//! @author  Alexey Neganov <neganovalexey@gmail.com>
//!
//! Computing stack machine, which have been realised by array
//}========================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "stack-array.h"
const int STKSIZE = 1000;
int main()
   {
   printf(MAIN_INVITATION);
   Stack_Interface(Stack_Construct(STKSIZE));
   return 0;
   }
const int FORBIDDEN = -2;
struct Stack_t
   {
   int count;
   int size;
   elem_t *data;
   };
//{========================================================================================================
//! Stack_OK - returns validity of the stack
//!
//! @param         st           Pointer to stack
//!
//! @return        1, if stack is valid, or 0, if not.
//}========================================================================================================
int Stack_OK(const struct Stack_t *st)
   {
   return (st && st->data && st->size > 0 && 0 <= st->count && st->count < st->size);
   }
//{========================================================================================================
//! Stack_Dump - to print information about stack
//!
//! @param         st           Pointer to stack
//!
//! @message       Validity of stack and its parts;\
stack size, count (position of the top), all elements of the stack - if possible.
//!
//! @return        OK
//}========================================================================================================
int Stack_Dump(const struct Stack_t *st)
   {
   if(!Stack_OK(st))
      printf("ERROR!\n");
   else printf("all is ok\n");
   if (!st)
      printf("Bad pointer to stack\n");
   else
      {
      printf("Stack size = %d\n", st->size);
      printf("count = %d\n", st->count);
      if(!st->data)
         printf("Bad pointer to stack data\n");
      else if(0 <= st->count && st->count < st->size)
         {
         int i=0;
         for(i=0; i<st->count; i++)
            printf("data[%d] = %lg\n", i, st->data[i]);
         }
      }
   return OK;
   }
//{========================================================================================================
//! Stack_Assert - smart assertion in order to debugging
//!
//! @param         st           Pointer to stack
//!
//! @return        OK
//}========================================================================================================
int Stack_Assert(const struct Stack_t *st)
   {
   if(!Stack_OK(st))
      {
      Stack_Dump(st);
      assert(!"error with stack");
      }
    return OK;
   }
//{========================================================================================================
//! Stack_Construct - to create new empty stack
//!
//! @param         size    Size of data of stack
//!
//! @return        Pointer to stack
//}========================================================================================================
struct Stack_t * Stack_Construct(int size)
   {
   struct Stack_t *res = (struct Stack_t*)calloc(1, sizeof(*res));
   res->count = 0;
   res->size = size;
   res->data = (elem_t*)calloc(size, sizeof(elem_t));
   Stack_Assert(res);
   return res;
   }
//{========================================================================================================
//! Stack_Destruct - to destruct stack and free allocated memory
//!
//! @param         st           Pointer to stack
//!
//! @return        OK
//}========================================================================================================
int Stack_Destruct(struct Stack_t *st)
   {
   Stack_Assert(st);
   int i=0;
   for(i=0; i<st->size; i++)
      st->data[i]=0;
   st->count = FORBIDDEN;
   st->size = FORBIDDEN;
   free(st->data);
   free(st);
   return OK;
   }
//{========================================================================================================
//! Stack_Push - to push value into stack and increase its count
//!
//! @param         st           Pointer to stack
//!
//! @return        OK
//}========================================================================================================
int Stack_Push(struct Stack_t *st, const elem_t value)
    {
    Stack_Assert(st);
    if(st->count+1 < st->size)
       {
       st->data[st->count] = value;
       st->count++;
       }
    else
       {
       st->size += STKSIZE;
       st->data = (elem_t*)realloc(st->data, (st->size)*sizeof(elem_t));
       Stack_Push(st, value);
       }
    Stack_Assert(st);
    return OK;
    }
//{========================================================================================================
//! Stack_Pop - to get value from the stack and decrease its count
//!
//! @param         st           Pointer to stack
//!
//! @return        value from top of the stack
//}========================================================================================================
elem_t Stack_Pop(struct Stack_t *st)
   {
    Stack_Assert(st);
    assert(st->count>0);
    st->count--;
    elem_t result = st->data[st->count];
    st->data[st->count] = 0;
    Stack_Assert(st);
    return result;
   }
//{========================================================================================================
//! action - to turn name of the command to code of this action
//!
//! @param         command        Command in text
//!
//! @return        Code of the action
//}========================================================================================================
int action(char *command)
   {
   assert(command);
   if(!strcmp(command, "push")) return PUSH;
   else if(!strcmp(command, "pop")) return POP;
   else if(!strcmp(command, "add")) return ADD;
   else if(!strcmp(command, "sub")) return SUB;
   else if(!strcmp(command, "mul")) return MUL;
   else if(!strcmp(command, "div")) return DIV;
   else if(!strcmp(command, "dump")) return DUMP;
   else if(!strcmp(command, "exit")) return EXIT;
   else return UNKNOWN;
   }
//{========================================================================================================
//! Stack_Arithmetic - to do arithmetic operations on the top elements of the stack
//!
//! @param         st           Pointer to stack
//! @param         action       Code of the operation
//!
//! @return        OK
//}========================================================================================================
int Stack_Arithmetic(struct Stack_t *st, const int action)
   {
   Stack_Assert(st);
   if(st->count < 2) return NOT_ENOUGH;
   else
      {
      elem_t ax=Stack_Pop(st);
      elem_t bx=Stack_Pop(st);
      switch(action)
         {
         case ADD: Stack_Push(st, ax+bx); break;
         case SUB: Stack_Push(st, -ax+bx); break;
         case MUL: Stack_Push(st, ax*bx); break;
         case DIV:
            {if(IS_ZERO(ax))
               {
               Stack_Push(st,bx);
               Stack_Push(st,ax);
               Stack_Assert(st);
               return ZERO_DIV;
               }
            else Stack_Push(st, bx/ax); break;}
         default: assert(!"Changing of strange commands"); break;
         }
      }
   Stack_Assert(st);
   return OK;
   }
//{========================================================================================================
//! double_warriorscanf - function, that provides correct input of floating-point values
//!
//! @param[out]      value   Value to reading from stdin
//!
//! @return     OK or ERROR
//}========================================================================================================
int double_warriorscanf(double *value)
   {
   if (!value) return ERROR;
   int valid = scanf("%lg", value);
   if(!valid || valid == EOF)
      return ERROR;
   return OK;
   }
//{========================================================================================================
//! Stack_Interface - user interface of the program
//!
//! @param         st           Pointer to stack
//!
//! @return          OK
//}========================================================================================================
int Stack_Interface(struct Stack_t *st)
   {
   Stack_Assert(st);
   printf("#New stack was successfully constructed.\n\n");
   char command[4];
   elem_t ax=0;
   int cond=1;
   while(cond)
      {
      scanf("%4s", command);
      elem_t ax=0;
      switch(action(command))
         {
         case UNKNOWN: printf("#Unknown command\n"); break;
         case PUSH:
            if (double_warriorscanf(&ax)==OK)
               Stack_Push(st, ax);
            else
               printf("\n#ERROR!\n#It was incorrect input there. Be more careful and try again.\n");
            break;
         case POP:
            if(st->count>0) printf("%lg\n", Stack_Pop(st));
            else printf("#Empty stack\n\n");
            break;
         case DUMP: Stack_Dump(st); break;
         case EXIT:
            if(Stack_Destruct(st) == OK)
               printf("#Stack was successfully destructed.\n");
            cond=0;
            break;
         default:
            {
            switch (Stack_Arithmetic(st, action(command)))
               {
               case NOT_ENOUGH: printf("#Not enough elements in stack\n\n"); break;
               case ZERO_DIV: printf("#ERROR: an attempt to divide by zero. Stack is unchanged\n\n"); break;
               }
            }
            break;
         }
      }
   return OK;
   }

//{========================================================================================================
//! @file    stack_lists.c
//! @date    2013-11-17 23:49
//! @author  Alexey Neganov <neganovalexey@gmail.com>
//!
//! Computing stack machine, which have been realised by list
//}========================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "stack-lists.h"
int main()
   {
   printf(MAIN_INVITATION);
   Stack_Interface();
   return 0;
   }
struct Stack_t
   {
   elem_t value;
   struct Stack_t *prev;
   struct Stack_t *next;
   };
//{========================================================================================================
//! Stack_Dump - to print information about stack
//!
//! @param         st           Pointer to top of the stack
//!
//! @message       Stack size, all elements of the stack - if possible.
//!
//! @return        OK
//}========================================================================================================
// FIXME You can move 'else {...}' prt to Stack_Ok, I think.
int Stack_Dump(const struct Stack_t *st)
   {
   if (!st)
      printf("#Empty stack\n");
   else
      {
      int i=1;
      if(st->prev)
         do{
            i++;
            st = st->prev;}
         while(st->prev);
      printf("#Stack size = %d\n", i);
      int j=0;
      for(j=0; j<i; j++)
         {
         printf("#elem[%d] = %lg\n", j, st->value);
         st=st->next;
         }
      }
   return OK;
   }
//{========================================================================================================
//! Stack_Destruct - to destruct stack and free allocated memory
//!
//! @param         st           Pointer to pointer to top of the stack
//!
//! @return        OK
//}========================================================================================================
int Stack_Destruct(struct Stack_t **st)
   {
   // FIXME You can move this to separate function or assert this.
    if(!st)
       {
       printf("Bad pointer to stack!\n");
       return ERROR;
       }
    if(!(*st)) return OK;
    int last=1;
    while((*st)->prev)
      {
      if(!last) free((*st)->next);
      last=0;
      (*st)->next=NULL;
      (*st)->value=0;
      *st=(*st)->prev;
      }
    (*st)->value=0;
    if(!last) free((*st)->next);
    (*st)->next=NULL;
    free(*st);
    *st=NULL;
    return OK;
   }
//{========================================================================================================
//! Stack_Push - to push value into stack and increase its count
//!
//! @param         st           Pointer to pointer to top of the stack
//!
//! @return        OK
//}========================================================================================================
int Stack_Push(struct Stack_t **st, const elem_t value)
    {
    assert(st);
    // FIXME I would like to call it "newElement" or something like that.
    struct Stack_t *addition = (struct Stack_t*)calloc(1, sizeof(struct Stack_t));
    assert(addition);
    addition->value = value;
    addition->next = NULL;
    addition->prev = *st;
    if(*st)
       {
       (*st)->next = addition;
       *st=(*st)->next;
       }
    else *st = addition;
    assert(*st);
    return OK;
    }
//{========================================================================================================
//! Stack_Pop - to get value from the stack and decrease its count
//!
//! @param         st           Pointer to pointer to top of the stack
//!
//! @return        value from top of the stack
//}========================================================================================================
elem_t Stack_Pop(struct Stack_t **st)
   {
    assert(st && *st);
    elem_t result = (*st)->value;
    (*st)->value=0;
    if((*st)->prev)
       {
       (*st)=(*st)->prev;
       free((*st)->next);
       (*st)->next=NULL;
       }
    else
       {
       free(*st);
       *st=NULL;
       }
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
//! @param         st           Pointer to pointer to top of the stack
//! @param         action       Code of the operation
//!
//! @return        OK
//}========================================================================================================
int Stack_Arithmetic(struct Stack_t **st, const int action)
   {
   assert(st);
   if(!(*st) || !(*st)->prev) return NOT_ENOUGH;
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
         // FIXME Something wrong with code style here. :)
            {if(IS_ZERO(ax))
               {
               Stack_Push(st,bx);
               Stack_Push(st,ax);
               return ZERO_DIV;
               }
            else Stack_Push(st, bx/ax); break;}
         default: assert(!"Changing of strange commands"); break;
         }
      }
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
//! @return          OK
//}========================================================================================================
int Stack_Interface()
   {
   struct Stack_t *st = NULL;
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
               {Stack_Push(&st, ax); assert(st); }
            else
               printf("\n#ERROR!\n#It was incorrect input there. Be more careful and try again.\n");
            break;
         case POP:
            if(st) printf("%lg\n", Stack_Pop(&st));
            else printf("#Empty stack\n\n");
            break;
         case DUMP: Stack_Dump(st); break;
         case EXIT:
            if(Stack_Destruct(&st) == OK)
               printf("#Stack was successfully destructed.\n");
            cond=0;
            break;
         default:
            {
            switch (Stack_Arithmetic(&st, action(command)))
               {
               case NOT_ENOUGH: printf("#Not enough elements in stack\n\n"); break;
               case ZERO_DIV: printf("#ERROR: an attempt to divide by zero. Stack is unchanged\n\n"); break;
               }
            }
            break;
         }
      }
   }


#ifndef Struck_Stup_h_
#define Struck_Stup_h_

#define MAX_SIZE 100

struct Stack_Arr
{
	int *head;
	int elem[MAX_SIZE];              
};

/** ********************************************************************************
 Push        add elem to stack
 
 @param      *st     stack
 @param      val     item to add
 
 @return     0,      if OK
             "Stack is full" if stack i full
			 assert, if it has bugs  
************************************************************************************/
int Push (struct Stack_Arr *st, int val);

/** ********************************************************************************
 pop  -      Extract the last element from the stack
 
 @param      *st     stack
 
 @return     head stack element
************************************************************************************/
int Pop (struct Stack_Arr *st);

/** ********************************************************************************
 Assert_OK   check the correctness of the stack
 
 @param      *st     stack
 
 @return     nothing 
************************************************************************************/
void Assert_OK (struct Stack_Arr *st);

/** ********************************************************************************
 Dump        show stack content
 
 @param      *st     stack
 
 @return     nothing   
************************************************************************************/
void Dump (struct Stack_Arr *st);

/** ********************************************************************************
 Size        return size of the stack
 
 @param      *st     stack name
 
 @return     size of the stack
************************************************************************************/
int Size (struct Stack_Arr *st);




#endif //Struck_Stup_h_
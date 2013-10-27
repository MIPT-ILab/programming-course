#ifndef Struck_Stup_h_
#define Struck_Stup_h_

//const int MAX_SIZE = 100;     max number of stack elements

struct Stack_Arr
{
	int *head;
	double elem[100];          //MAX_SIZE only in C++     
}

/** ********************************************************************************
 Push        add elem to stack
 
 @param      *st     stack
 @param      val     item to add
 
 @return     0,      if OK
************************************************************************************/
int Push (struct Stack_Arr *st, double val);

/** ********************************************************************************
 pop  -      Extract the last element from the stack
 
 @param      *st     stack
 
 @return     0,      if OK
************************************************************************************/
int Pop (struct Stack_Arr *st);

/** ********************************************************************************
 Assert_OK   check the correctness of the stack
 
 @param      *st     stack
 
 @return     errors 
************************************************************************************/
int Assert_OK (struct Stack_Arr *st);

/** ********************************************************************************
 Dump        show stack content
 
 @param      *st     stack
 
 @return     stack content    
************************************************************************************/
int Dump (struct Stack_Arr *st);

/** ********************************************************************************
 Size        return size of the stack
 
 @param      *st     stack name
 
 @return     size of the stack
************************************************************************************/
int Size (struct Stack_Arr *st);

#endif //Struck_Stup_h_
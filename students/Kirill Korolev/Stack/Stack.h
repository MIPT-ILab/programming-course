/** *********************************************************************

 A list of functions for working with stack.

 @file Stack.h; Stack.cpp
 @date November 8, 2013
 @author Kirill Korolev <kirill.korolef@gmail.com>
 @version 1.0 (Noverber 8, 2013)

 @note Ver. 1.0 (Novermber 8, 2013)
	- main stack functions
	- mathematic stack functions
	- 2 auxiliary functions of "string.h" library

 @onte Var. 1.01 (November 15, 2013)
   - added "free" function for stack memory

 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# pragma once

typedef double Arr_type; /**< The type of the array in the Stack struct. */

typedef struct Stack  /**< The struct for stack. */
{
	Arr_type * Arr;   /**< The array of data of the stack. */
	long Num;         /**< The number of the current stack. */
	long Size;        /**< The size of the current stack. */
	long Last;        /**< The number of the last element in the stack. */
} Stack_t;


/** ****************************************************************************

 Stack_Construct - the function which allocates memory for all parts of a new
				   stack.

 @param  Size - the size of a new stack.

 @return 0 - if there are a mistake of creation (Size == 0).
         address of the stack - if a new stack has been created successfully.

*******************************************************************************/

Stack_t * Stack_Construct (long Size);

/** ****************************************************************************

 Stack_Reconstruct - the function which reallocates the stack with bigger
				     memory for the array of data.

 @param[out]  St - the address of the current stack.

 @return 1 - if the stack has been recreated successfully.

 @note  - The function increase the size of the stack with 10 free elements.
	    - The function will be terminated by Stack_OK if there are mistakes.

 ******************************************************************************/

int Stack_Reconstruct (Stack_t * St);

/** ****************************************************************************

 Stack_Distruct - the function which destroys all data in the stack and free
				  all the allocated memory.

 @param[out]  St - the address of the current stack.

 @return 1

 @note - the function is activated by Stack_Dump function.

 ******************************************************************************/

int Stack_Distruct (Stack_t * St);

/** ****************************************************************************

 Stack_Push - the function which adds a new element to the top of the stack.

 @param[out]  St  - the address of the current stack.
 @param       val - the value of the new element.

 @return 1

 @note - The function will be terminated by Stack_OK if there are mistakes.

 ******************************************************************************/

int Stack_Push (Stack_t * St, Arr_type val);

/** ****************************************************************************

 Stack_Pull - the function which returns the top element of the stack with
			  removing it from the stack.

 @param[out]  St - the address of the current stack.

 @return                     0 - if the stack is empty.
         value of the last el. - if pull has been made succsessfully.

*******************************************************************************/

Arr_type Stack_Pop (Stack_t * St);

/** ****************************************************************************

 Stack_OK - the function which check the stack.

 @param[out]  St - the address of the current stack.

 @return -1 - if any elements of the stack is not appropriate for a work.
          1 - if stack is without any mistakes.

*******************************************************************************/

int Stack_OK (Stack_t * St);

/** ****************************************************************************

 Stack_Dump - the emergency function which print down all the information
              about the stack and data inside.

 @param[out]  St - the address of the current stack.

 @note - The functions will be activated after the -1 return code of the 
         Stack_OK program.
	   - The function will activate the Stack_Distruct function which will
	     destroy the current stack.

*******************************************************************************/

void Stack_Dump (Stack_t * St);

/** ****************************************************************************

 Stack_Top - the function which returns the top element of the stack wihtout
             changing the stack.

 @param[out]  St - the address of the current stack.

 @return the value - if functions has been finished successfully.
                 0 - if the stack is empty.

*******************************************************************************/

Arr_type Stack_Top (Stack_t * St);

/** ****************************************************************************

 Stack_Sum - the function which sum up the two top elements of the stack and
             put the result to on their place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Sum (Stack_t * St);

/** ****************************************************************************

 Stack_Sub - the function which subtract the two top elements of the stack and
             put the result to on their place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Sub (Stack_t * St);

/** ****************************************************************************

 Stack_Mul - the function which multiply the two top elements of the stack and
             put the result to on their place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Mul (Stack_t * St);

/** ****************************************************************************

 Stack_Div - the function which divide the two top elements of the stack and
             put the result to on their place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Div (Stack_t * St);

/** ****************************************************************************

 Stack_Exp - the function which take the exponent of the top element of 
			 the stack and put the result to on its place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Exp (Stack_t * St);

/** ****************************************************************************

 Stack_Pow - the function which involute the top two elements of 
			 the stack and put the result to on its place in the stack.

 @param[out]  St - the address of the current stack.

 @return  -1 - if there are not enough elements in the stack.
           1 - is the function has been finished successfully.

*******************************************************************************/

int Stack_Pow (Stack_t * St);

/** ****************************************************************************

 Func_Strlen - the auxiliary function which calculate the length of the string.

 @param[out]  str - the address of the current string (char *).

 @return the value

*******************************************************************************/

int Func_Strlen (const char * str);

/** ****************************************************************************

 Func_Strcmp - the auxiliary function which compare two strings.

 @param[out]  str1 - the address of the first string (char *).
 @param[out]  str1 - the address of the second string (char *).

 @return  1 - if the 1st sring is bigger than the 2nd.
          0 - if the strings are equal.
		 -1 - if the 1st string is smaller than the 2nd.

*******************************************************************************/

int Func_Strcmp (const char * str1, const char * str2);
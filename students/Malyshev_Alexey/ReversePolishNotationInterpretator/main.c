//{==========================================================================================================
//! @file		ReversePolishNotationInterpreter.c
//! @date		2013-10-22 23:58
//! @author 	Malyshev Alexey <samymnyi2008@gmail.com>
//! @version 	1.00
//!
//! Allows to calculate the value of expression written in the
//! reverse polish notation
//!
//! @par		Program reads one string, which consists of
//!				mathematical expression, written in the
//!				reverse polish notation.
//!				Returns the calculated value of this expression.
//!
//! @warning 	In this version only integer numbers and only arithmetic functions should be used!
//! @warning	Also, this program doesn't check the correctness of your data!
//}==========================================================================================================



#include <stdio.h> 	//allows to use printf(), scanf(), gets()
#include <string.h> //allows to work with special string's functions
#include <assert.h> //allows to use assert()
#include <stdlib.h> //allows to use abort()



#define ASSERT_OK(st) 						\
{   										\
	if (!Stack_OK(&st))						\
	{										\
		Stack_DUMP(&st);					\
		abort();							\
	}										\
}



//-----------------------------------------------------------------------------------------------------------
const int St_SIZE=10; //!<Determines the size of integer stacks
//-----------------------------------------------------------------------------------------------------------



//{==================================+++STACK_STRUCTURE_DESCRIPTION+++=======================================
struct Stack_t
{
	int Top; 		  // Variable which stores number of the next free element in the stack
	double Data[St_SIZE]; // An array which stores the elements of the stack
};



//{==========================================================================================================
//! Stack_Construct - creates normal or fix given stack from the Stack_t variable
//!
//!	@param[out]	st - an address of Stack_t type variable which would become a working stack
//!
//! @return 	Void
//}==========================================================================================================

void Stack_Construct(Stack_t* st)
{
	(*st).Top = 0; 	//  If st.Top is equal to zero it means, that  given stack is empty and ready to be used
	return;
}



//{==========================================================================================================
//! Stack_Destruct - spoils any Stack_t variable
//!
//!	@param[out]	st - an address of Stack_t type variable which would become a spoiled stack
//!
//! @return 	Void
//!
//! @warning 	Of course, you can reconstruct a spoiled stack, but in a way not to get in troubles, please, \
//!          	try to avoid such a deeds
//}=========================================================================================================

void Stack_Destruct(Stack_t* st)
{
   (*st).Top = 0; 	// If st.Top is less than zero it means, that our stack is spoiled and we can't use it
   return;
}



//{==========================================================================================================
//! Stack_OK - defines whether the stack is normal or spoiled
//!
//!	@param		st - an address of  (const Stack_t) type variable which would be checked
//!
//! @return 	Zero if the stack is spoiled, one if the stack is OK
//!
//! @warning 	Doesn't checks the stack data correctness!
//}==========================================================================================================

int Stack_OK(const Stack_t* st)
{
	return (st && (0 <= (*st).Top) && ((*st).Top < St_SIZE));
	// Checks whether (&st) is not NULL and Top is not less than zero (otherwise stack is spoiled),\
	   and Top is less than St_SIZE (otherwise, the number of next free stack element is greater  \
	   than size of the stack.
}



//{==========================================================================================================
//! Stack_DUMP - allow user to define whether the stack is normal or spoiled and to see its content
//!
//!	@param		st - an address of  (const Stack_t) type variable which would be checked
//!
//! @return 	Void
//}==========================================================================================================

void Stack_DUMP(const Stack_t* st)
{
	printf ("\n#FROM HERE THE DUMP BEGINS!\n");
	if (!Stack_OK(st))
	{
		printf("\n#Your stack is spoiled! Try to do something!\n");
	}
	else
	{
		printf("\n#Your stack is normal, but something is wrong.\n");
	}
	printf("\n#Top = %d\n", (*st).Top);
	for (int i = 0; i < St_SIZE; i++)
	{
		if (i < (*st).Top)
		{
			printf("#Stack %d element's value = %lg*\n", i+1, (*st).Data[i]);
		}
		else
		{
			printf("#Stack %d element's value = %lg\n", i+1, (*st).Data[i]);
		}
	}
	printf("\n#Your stack address is: %d \n", st);
	printf("\nHope, it has helped you!\n");
	return;
}



//{==========================================================================================================
//! Stack_PUSH - pushes an double element to the top of the stack
//!
//! @param		st - an address of  (iStack_t) type variable which would be changed
//! @param		val - an integer variable whose value would be pushed to the stack
//!
//! @return 	Void
//}==========================================================================================================

void Stack_PUSH(Stack_t* st, double val)
{
	ASSERT_OK(*st);
	(*st).Data[(*st).Top++] = val;
	//Stack_DUMP(st);
	ASSERT_OK(*st);
	return;
}



//{==========================================================================================================
//! Stack_POP - returns the element from the top of the stack
//!
//! @param		st - an address of  (Stack_t) type variable which would be used
//!
//! @return 	Value of the element from the stack's top
//}==========================================================================================================

double Stack_POP(Stack_t* st)
{
	ASSERT_OK(*st);
	if ((*st).Top==0)
	{
		printf("\nYou can't pop anything from this stack! Error line: %c\n", __LINE__);
		//Stack_DUMP(st);
		abort();
	}
	else
	{
		return (*st).Data[--((*st).Top)];
	}
}
//}=======================+++THE_END_OF_STACK_STRUCTURE_DESCRIPTION+++======================================


//{=====================================+++AN_INTERPETER_PART+++=============================================
//{==========================================================================================================
//! Interpreter - allows calculate the value of expression written in the reverse polish notation
//!
//! @param		cExp - That string, which include expression, which should be calculated
//!
//! @return 	Calculated value of the expression
//}==========================================================================================================

double Interpreter(char cExp[])
{
	Stack_t Add = {};				// We will use this stack to store here values of numbers from the expression
	Stack_Construct(&Add);
	int dtm = 0; 				// This variable shows whether we are still parsing a number or not
	double val = 0;				// This variable stores a number got during the parsing
	double temp1 = 0;           // Due to the structure of reverse polish notation we need only two variables
	double temp2 = 0;           // to be used as a temporary

	// From here the parsing of the string begins

	for (int i = 0; i < strlen(cExp); i++)
	{
		if (('0' <= cExp[i]) && (cExp[i] <= '9'))  // Check whether the current symbol is a digit
		{
			if (!dtm )                             // That case, when it's the beginning of a new number
			{
				dtm = 1;
				val = 0;
				val += (cExp[i] - '0');
			}
			else                                   // That case, when it's the end of a number
			{
				dtm = 1;
				val *= 10;
				val += cExp[i] - '0';
			}
		}
		else
		{
			if (dtm)                               // That case, when we have just finished parsing of a number
			{
				Stack_PUSH(&Add, val);
			}
			dtm = 0;
			switch (cExp[i])					   // Determines if we have to do come action and if yes - does it
			{                                      // as it can be done with using of a stack
				case '+':
					{
						temp1 = Stack_POP(&Add);
						temp2 = Stack_POP(&Add);
						Stack_PUSH(&Add, temp1 + temp2);
						break;
					}
				case '-':
					{
						temp1 = Stack_POP(&Add);
						temp2 = Stack_POP(&Add);
						Stack_PUSH(&Add, temp2 - temp1);
						break;
					}
				case '*':
					{
						temp1 = Stack_POP(&Add);
						temp2 = Stack_POP(&Add);
						Stack_PUSH(&Add, temp1 * temp2);
						break;
					}
				case '/':
					{
						temp1 = Stack_POP(&Add);
						temp2 = Stack_POP(&Add);
						Stack_PUSH(&Add, temp2 / temp1);
						break;
					} ;
			}

		}
	}
	return (Stack_POP(&Add));
}
//}===============================+++THE_END_OF_THE_INTERPRETER_PART+++======================================



int main()
{
	printf("#Good day, sir! This program is created to help you in calculating expressions\n");
	printf("#which are given in the reverse polish notation.\n");
	printf("\n#You have opened this program on %s %s\n\n", __TIME__, __DATE__);
	printf("#Please, enter that expression you'd like to be calculated as a NULL-terminated string.\n\n");
	char cExp[1000]; // Here the given expression is stored
	gets(cExp);      // Here we got the expression
	printf("\n#Thank you.\n");
    printf("#So, your result is: %lg", Interpreter(cExp));
    printf("\n#Good luck!\n");
	return 0;
}

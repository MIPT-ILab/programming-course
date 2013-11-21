#include <stdio.h> 	//allows to use printf(), scanf(), gets()
#include <string.h> //allows to work with special string's functions
#include <assert.h> //allows to use assert()
#include <stdlib.h> //allows to use abort()

#define st_type double



#define ASSERT_OK(st) 						\
{   										\
	if (!Stack_OK(&st))						\
	{										\
		Stack_DUMP(&st);					\
		abort();							\
	}										\
}



//-----------------------------------------------------------------------------------------------------------
const int St_SIZE=1000; //!<Determines the size of integer stacks
//-----------------------------------------------------------------------------------------------------------


//{==================================+++STACK_STRUCTURE_DESCRIPTION+++=======================================
struct Stack_t
{
	int Top; 		  // Variable which stores number of the next free element in the stack
	st_type Data[St_SIZE]; // An array which stores the elements of the stack
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
	int i = 0;
	(*st).Top = 0; 	//  If st.Top is equal to zero it means, that  given stack is empty and ready to be used
	for (i = 0; i < St_SIZE; i++)
	{
		st->Data[i]=0;
	}
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

void Stack_PUSH(Stack_t* st, st_type val)
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

st_type Stack_POP(Stack_t* st)
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

/*int main()
{
	return 0;
} */

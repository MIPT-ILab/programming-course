/** *********************************************************************

 A program which solves the mathematic terms.

 @file Calculator.cpp
 @date November 4, 2013
 @author Kirill Korolev <kirill.korolef@gmail.com>
 @version 1.0 (Noverber 4, 2013)

 @note Ver. 1.0 (Novermber 4, 2013)
	- a conditional compilation added
	- multiple stacks support
	- main stack functions
	- printing functions added
	- mathematic stack functions added
	- enum command numeration added
	- added a calculation function with "+, -, /, *"
	- added exponent and degree to the calculator
	
 @note Ver. 2.0 (December 6, 2013)
	- release vertion
    - added checking of division by zero

 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Stack.cpp"

enum COMMAND
{
	EN_Error,
	EN_Construct,
	EN_Distruct,
	EN_Choose,
	EN_Leave,
	EN_Push,
	EN_Pop,
	EN_Print,
	EN_Printall,
	EN_Size,
	EN_Exit,
	EN_Top,
	EN_Sum,
	EN_Sub,
	EN_Mul,
	EN_Div,
	EN_Exp,
	EN_Help,
	EN_Calc
};

enum SYMBOL
{
	SY_Err,
	SY_Plus,
	SY_Min,
	SY_Mul,
	SY_Div,
	SY_Br1,
	SY_Br2,
	SY_Num,
	SY_Exp,
	SY_Deg
};

const char * ver = "2.0";       /**< the vertion of the program. */
const int MAXIN = 1000;         /**< the maximum size of the input. */
const int MAXSTACK = 1000;      /**< the maximum number of the stacks. */ 

/** **************************************************************************************

 Command - the function which make needed opperations according to the command.

 @param[out] term      - the input string
 @param[out] Num_Stack - the number of constructed stacks.
 @param[out] val       - the value for opperating b some functions.
 @param[out] Arr_Stack - the array of the addresses of the stacks.
 @param[out] buff      - the buffer for the return value of the Pop function.
 @param[out] work_st   - the number of the working stack.
 @param[out] exit      - the exit code for the program.

 @return  1 - if the correct command was intered and correctly executed.
         -1 - if the was a mistake while opperating.

*****************************************************************************************/

int Command (char * term, int * Num_Stack, double * val, Stack_t * * Arr_Stack, Arr_type * buff, int * work_st, int * exit);

/** **************************************************************************************

 Print_all - the function which print down all constructed stacks.

 @param[out] Arr_Stack - the array of the addresses of the stacks.
 @param      Num_Stack - the number of constructed stacks.

 @return  1 - if the stacks were printed successfully.
 
 @note If the function can not be executed, it will be terminated in the Command func.

*****************************************************************************************/

int Print_all (Stack_t * * Arr_Stack, int Num_Stack);

/** **************************************************************************************

 Print - the function which print down the current stack.

 @param[out] Arr_Stack - the array of the addresses of the stacks.
 @param      Num       - the number of the current stack.

 @return 1 - if the stack was printed successfully.
 
 @note If the function can not be executed, it will be terminated in the Command func.

 ****************************************************************************************/

int Print (Stack_t * * Arr_Stack, int Num);

/** **************************************************************************************

 Command_Val - the function which returns the enum code of the command.

 @param[out] cmd - the command string.

 @return the value      - if the command is correct.
         the error code - if the command is incorrect.
 
 @note The enum code is needed for using switch with the commands in the Command func.

*****************************************************************************************/

enum COMMAND Command_Val (char * cmd);

/** **************************************************************************************

 Scan_Value - the function which scans the input string for the opperating value.

 @param[out] val - the result value
 @param[out] input - the input string
 @param[out] i - the number of the el. in the iput for starting scanning.

 @return  1 - if the value has been scaned successfully.
         -1 - if the there aren't appropriate value in the input.

@note The function seaching for the value only after the command in the input string.
      If if has found the value, in doesn't matter what is in the string after it.

*****************************************************************************************/

int Scan_Value (double * val, const char * input, int * i);

/** **************************************************************************************

 Brackets - the function which check the if the brackets in the math. term is correct.

 @param[out] str - the current string for checking.

 @return  1 - if the brackets are correct.
         -1 - if it is not.

 @note The function can be activated only by Poland_Recording function (for checking 
       the term).

*****************************************************************************************/

int Brackets (const char * str);

/** **************************************************************************************

 Prioriry - the function which returns the priority of the math. opperation.

 @param sym - the symbol of the current opperation.

 @return the value of the priority - if the symbol is correct.
                                -1 - if it is not.

*****************************************************************************************/

int Priority (char sym);

/** **************************************************************************************

 Poland_Recording - the function which calculate the mathematic term by poland recording
                    method.

 @param[out] str - the string with the current term.
 @param[out] i   - the number of the el. where the term begins.

 @return the result - if the term is correct
                 -1 - if it is not correct.

 @note This function uses Scan func. for reading the values of the numbers in the term.
       It makes a full check of correctness of the term. 

*****************************************************************************************/

Arr_type Poland_Recording (const char * str, int * i);

/** **************************************************************************************

 Calculate - the function which calculate 1 opperation from the poland recording for 
             the Poland_Recording function.

 @param[out] elem - the stack with the numbers in the term.
 @parar[out] sym  - the stack with the math. opperations.

 @return the return code of math. stack function.

*****************************************************************************************/

int Calculate (Stack_t * elem, Stack_t * sym);

int main()
{
	printf("\n[_____***_____***_____***_____]\n\n"
		   "The program for calculating the mathematic terms.\n"
		   "File: Stack.cpp\n"
		   "Author: Kirill Korolev <kirill.korolef@gmail.com>\n"
		   "Date of creation: November 4, 2013\n"
		   "Version: %s\n\n"
		   "Start working with 'help'...\n\n", ver);

	long Size = 0;
	int exit = 0;
	Stack_t * Arr_Stack[MAXSTACK] = {};
	int Num_Stack = 0;
	double val = 0;
	int check = 0;
	int work_st = 0;
	Arr_type buff = 0;
	char term[MAXIN] = {};
	int i = 0;

	while (exit != 1)
	{
		for (i = 0; i < MAXIN; i++)
			term[i] = '\0';

		val = 0;

		printf("\n>");
		if (work_st != 0)
			printf("%d:", work_st);
		
		i = 0;
		char sym = '\0';
		scanf("%c", &sym);
		while ( sym != '\n')
		{
			ASSERT( ( (i >= 0) && (i < MAXIN) ), "i is out of the size of the term.");
			term[i] = sym;
			scanf("%c", &sym);
			i++;
			if (i >= MAXIN)
			{
				printf("Too long input.");
				while (sym != '\n')
					scanf("%c", &sym);
				break;
			}
		}
		if (i < MAXIN)
			Command (term, &Num_Stack, &val, Arr_Stack, &buff, &work_st, &exit);
	}

	return 0;
}

enum COMMAND Command_Val (char * cmd)
{
	if      ( Func_Strcmp (cmd, "construct") == 0 ) return EN_Construct;
	else if ( Func_Strcmp (cmd, "distruct")  == 0 ) return EN_Distruct;
	else if ( Func_Strcmp (cmd, "choose")    == 0 ) return EN_Choose;
	else if ( Func_Strcmp (cmd, "leave")     == 0 ) return EN_Leave;
	else if ( Func_Strcmp (cmd, "push")      == 0 ) return EN_Push;
	else if ( Func_Strcmp (cmd, "pop")       == 0 ) return EN_Pop;
	else if ( Func_Strcmp (cmd, "print")     == 0 ) return EN_Print;
	else if ( Func_Strcmp (cmd, "printall")  == 0 ) return EN_Printall;
	else if ( Func_Strcmp (cmd, "size")      == 0 ) return EN_Size;
	else if ( Func_Strcmp (cmd, "exit")      == 0 ) return EN_Exit;
	else if ( Func_Strcmp (cmd, "top")       == 0 ) return EN_Top;
	else if ( Func_Strcmp (cmd, "sum")       == 0 ) return EN_Sum;
	else if ( Func_Strcmp (cmd, "sub")       == 0 ) return EN_Sub;
	else if ( Func_Strcmp (cmd, "mul")       == 0 ) return EN_Mul;
	else if ( Func_Strcmp (cmd, "div")       == 0 ) return EN_Div;
	else if ( Func_Strcmp (cmd, "exp")       == 0 ) return EN_Exp;
	else if ( Func_Strcmp (cmd, "help")      == 0 ) return EN_Help;
	else if ( Func_Strcmp (cmd, "calc")      == 0 ) return EN_Calc;
	else                                            return EN_Error;
}

int Command (char * term, int * Num_Stack, double * val, Stack_t * * Arr_Stack, Arr_type * buff, int * work_st, int * exit)
{
	ASSERT(term != NULL, "term is a NULL address.");
	ASSERT(Num_Stack != NULL, "Num_Stack is a NULL address.");
	ASSERT(Arr_Stack != NULL, "Arr_Stack is a NULL address.");
	ASSERT(buff != NULL, "address is a NULL address.");
	ASSERT(work_st != NULL, "work_st is a NULL address.");

	char cmd[MAXIN] = {};
	int term_num = 0;

	while ( (term[term_num] != ' ') && (term_num != Func_Strlen(term) ) )
	{
		ASSERT( ( (term_num >= 0) && (term_num <= MAXIN - 1) ), "term_num is out of the size of the term.");
		cmd[term_num] = term[term_num];
		term_num++;
	}

	enum COMMAND cmd_val = Command_Val (cmd);

	if (cmd_val == EN_Error)
	{
		printf("\nAn inappropriate command.\n");
		return -1;
	}

	switch (cmd_val)
	{
		case (EN_Leave):
		{
			* work_st = 0;
			return 1;
		}

		case (EN_Pop):
		{
			if ( (* work_st < 1) ||(* work_st > * Num_Stack) )
				printf("\nChoose a stack first.\n");
			else
			{
				ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "work_st is out of the size of the Arr_Stack.");
				if (Arr_Stack[* work_st -1] -> Last <= -1)
				{
					printf("\nThe stack is empty.\n");
					return -1;
				}
				* buff = Stack_Pop (Arr_Stack[* work_st - 1]);
			}
			return 1;
		}

		case (EN_Printall):
		{
			if (* Num_Stack < 1)
				printf("\nThere are not any stacks.\n");
			else
				Print_all (Arr_Stack, * Num_Stack);
			return 1;
		}

		case (EN_Exit):
		{
			* exit = 1;
			return 1;
		}

		case (EN_Top):
		{
			if ( (* work_st < 1) ||(* work_st > * Num_Stack) )
				printf("\nChoose a stack first.\n");
			else
			{
				ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "work_st is out of the size of the Arr_Stack.");
				if (Arr_Stack[* work_st -1] -> Last <= -1)
				{
					printf("\nThe stack is empty.\n");
					return -1;
				}
				* buff = Stack_Pop (Arr_Stack[* work_st - 1]);
			}
			return 1;
		}

		case (EN_Help):
		{
			printf("\nThe list of the operations:\n"
			       "[1]  construct [the size of the stack]   - create a new stack.\n"
			       "[2]  distrcuct [the number of the stack] - destroy a stack.\n"
			       "[3]  choose    [the number of the stack] - choose a stack for working.\n"
			       "[4]  leave                               - finish a work with a current stack.\n"
			       "[5]  push      [the value]               - add a new element to a current stack.\n"
			       "[6]  pop                                 - move the last element of a current stack to the buffer.\n"
			       "[7]  print     [the number of the stack] - print down the stack.\n"
			       "[8]  printall                            - print down all the stacks.\n"
			       "[9]  size      [the number of the stack] - print down the number of the elements in the stack.\n"
			       "[10] exit                                - finish the program.\n"
			       "[11] top       [the number of the stack] - print the top element of the stack.\n"
			       "Mathematic operations:\n"
			       "[12] sum       [the number of the stack] - sum up the top two elements.\n"
			       "[13] sub       [the number of the stack] - subtract the top two elements.\n"
			       "[14] mul       [the number of the stack] - multiply the top two elements.\n"
			       "[15] div       [the number of the stack] - divide the top two elelments.\n"
			       "[16] exp       [the number of the stack] - calculate the exponent of the top element.\n"
				   "[17] calc      [the math. term]          - calculate the current term.\n\n");
			return 1;
		}

		case (EN_Calc):
		{
			Arr_type ans = Poland_Recording(term, &term_num);
			if (ans != -1 )
			{
				printf("\n%lf\n", ans);
				return 1;
			}
			else 
			{
				printf("\nAn inappropriate string for calculating.\n");
				return -1;
			}
		}

		case (EN_Sum):
		{
			ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
			{
				printf("\nChoose a stack first.\n");
				return -1;
			}
			else
			{
				int check = Stack_Sum (Arr_Stack[(* work_st) - 1]);
				if (check == -1)
				{
					printf("\nThere are not enough elements in the stack.\n");
					return -1;
				}
				return 1;
			}
		}

		case (EN_Sub):
		{
			ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
			{
				printf("\nChoose a stack first.\n");
				return -1;
			}
			else
			{
				int check = Stack_Sub (Arr_Stack[(* work_st) - 1]);
				if (check == -1)
				{
					printf("\nThere are not enough elements in the stack.\n");
					return -1;
				}
				return 1;
			}
		}

		case (EN_Mul):
		{
			ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
			{
				printf("\nChoose a stack first.\n");
				return -1;
			}
			else
			{
				int check = Stack_Mul (Arr_Stack[(* work_st) - 1]);
				if (check == -1)
				{
					printf("\nThere are not enough elements in the stack.\n");
					return -1;
				}
				return 1;
			}
		}

		case (EN_Div):
		{
			ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
			{
				printf("\nChoose a stack first.\n");
				return -1;
			}
			else
			{
				int check = Stack_Div (Arr_Stack[(* work_st) - 1]);
				if (check == -1)
				{
					printf("\nThere are not enough elements in the stack.\n");
					return -1;
				}
				return 1;
			}
		}

		case (EN_Exp):
		{
			ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
			{
				printf("\nChoose a stack first.\n");
				return -1;
			}
			else
			{
				int check = Stack_Exp (Arr_Stack[(* work_st) - 1]);
				if (check == -1)
				{
					printf("\nThere are not enough elements in the stack.\n");
					return -1;
				}
				return 1;
			}
		}
	}

	int check = Scan_Value (val, term, &term_num);
	if (check == -1)
	{
		printf("\nAn inappropriate value.\n");
		return -1;
	}

	switch (cmd_val)
	{
		case (EN_Construct):
			{
			Stack_t * St = Stack_Construct ((int) * val);
			if (St == 0)
				printf("\nAn inappropriate stack size.\n");
			else
			{
				Arr_Stack[(* Num_Stack)] = St;
				(* Num_Stack) ++;
				St -> Num = * Num_Stack;
				printf("\nA stack Num.%d has been created.\n", St -> Num);
			}
			return 1;
		}

		case (EN_Distruct):
		{
			if (Arr_Stack[(int) * val - 1] != 0)
			{
				Stack_t * St = Arr_Stack[(int) * val - 1];
				Stack_Distruct (St);
				(* Num_Stack) --;
				Arr_Stack[(int) * val - 1] = 0;
				printf("\nThe stack Num.%d has been destroyed.\n", (int) * val);
				return 1;
			}
			else
			{
				printf("\nThere are not any stack with number %d.\n", (int) * val);
				return -1;
			}
		}

		case (EN_Choose):
		{
			if ( ((int) * val > * Num_Stack) || ((int) * val < 1) )
			{
				printf("\nThere is not a stack with number %d\n", (int) * val);
				return -1;
			}
			else
			{
				* work_st = (int) * val;
				printf("\nThe stack Num.%d has been chosen.\n", (int) * val);
				return 1;
			}
		}		

		case (EN_Push):
		{
			if ( (* work_st < 1) || (* work_st > * Num_Stack) )
				printf("\nChoose a stack first.\n");
			else
			{
				ASSERT( ( (* work_st >= 0) && (* work_st <= MAXSTACK) ), "work_st - 1 is out of the size of the Arr_Stack.");
				Stack_Push (Arr_Stack[* work_st - 1], (Arr_type) * val);
			}
			return 1;
		}

		case (EN_Print):
		{
			if ( ((int) * val < 1) || ((int) * val > * Num_Stack) )
				printf("\nThere is not a stack with number %d\n", (int) * val);
			else
				Print (Arr_Stack, (int) * val);
			return 1;
		}

		case (EN_Size):
		{
			ASSERT( ( ((int) * val >= 1) && ((int) * val <= MAXSTACK) ), "(int) * val - 1 is out of the size of the Arr_Stack.");	
			printf("\n%d\n", Arr_Stack[(int) (* val) - 1] -> Last + 1);
			return 1;
		}
	}

	return 1;
}

int Print_all (Stack_t * * Arr_Stack, int Num_Stack)
{
	ASSERT(Arr_Stack != NULL, "Arr_stack is a NULL address.");
	printf("\n");
	for (int i = 0; i < MAXSTACK; i++)
	{
		ASSERT( ( (i >= 0) && (i <= MAXSTACK - 1) ), "i is out of the size of the Arr_Stack.");
		
		if (Arr_Stack[i] != 0)
		{
			printf("A stack Num.%d:\n", i + 1);
			for (int j = 0; j <= Arr_Stack[i]->Last; j++)
			{
				ASSERT( ( (j >= 0) && (j <= Arr_Stack[i]->Size - 1) ), "j is out of the size of the Arr_Stack[j]->Arr.");
				ASSERT(Arr_Stack[i]->Arr != NULL, "Arr_Stack[i]->Arr is a NULL address.");
				if (j == Arr_Stack[i]->Last)
					printf("[%d]: %lg\n", j, (double) Arr_Stack[i]->Arr[j]);
				else
					printf("[%d]: %lg; ", j, (double) Arr_Stack[i]->Arr[j]);
			}
		}
	}
	return 1;
}

int Print (Stack_t * * Arr_Stack, int Num)
{
	ASSERT(Arr_Stack != NULL, "Arr_Stack is a NULL address.");
	ASSERT( ( (Num >= 1) && (Num <= MAXSTACK) ), "Num is out of the size of the Arr_Stack.");
	printf("\n");
	for (int i = 0; i <= Arr_Stack[Num - 1]->Last; i++)
	{
		if (i == Arr_Stack[Num - 1]->Last)
			printf("[%d]: %lg\n", i, (double) Arr_Stack[Num - 1]->Arr[i]);
		else
			printf("[%d]: %lg; ", i, (double) Arr_Stack[Num - 1]->Arr[i]);
	}
	return 1;
}

int Scan_Value (double * val, const char * input, int * i)
{
	ASSERT(val != NULL, "val is a NULL address.");
	ASSERT(input != NULL, "input is a NULL address.");

	int in_size = Func_Strlen(input);		
	
	ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
	while (input[* i] == ' ')
		(* i)++;
			
	if (* i == in_size)
		return -1;

	int sign = 1;
	ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
	if (input[* i] == '-')
	{
		sign = -1;
		(* i)++;
	}

	if (* i == in_size)
		return -1;

	ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
	while ( (input[* i] <= '9') && (input[* i] >= '0') && (input[* i] != '.') )
	{	
		ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
		* val = 10 * (* val) + (double) input[* i] - '0';
		(* i)++;
	}
	* val = (* val) * sign;

	ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
	if (input[* i] != '.') 
		return 1;
	
	int point_val = (* i);
	(* i)++;
	int point = 1;
	ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
	while ( (input[* i] <= '9') && (input[* i] >= '0') )
	{
		ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the input.");
		* val = 10 * (* val) + (double) input[* i] - '0';
		(* i)++;
		point = point*10;
		if ((*i) - point_val > 10)
			return -1;
	}
	* val = (* val) / point;

	return 1;
}

int Brackets (const char * str)
{
	ASSERT(str != NULL,"str is a NULL address.");
	
	int str_len = Func_Strlen (str);
	int br_num = 0;
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] == '(') br_num++;
		if (str[i] == ')') br_num--;
		if (br_num < 0)
			return -1;
	}
	if (br_num == 0)
		return 1;
	else
		return -1;
}

int Priority (char sym)
{
	if (sym == '+') return  1;
	if (sym == '-') return  1;
	if (sym == '*') return  2;
	if (sym == '/') return  2;
	if (sym == '(') return  0;
	if (sym == 'e') return  3;
	if (sym == '^') return  3;
	else            return -1;
}

SYMBOL Symbol_Val (char sym)
{
	if      (sym == '+')                     return SY_Plus;
	else if (sym == '-')                     return SY_Min;
	else if (sym == '/')                     return SY_Div;
	else if (sym == '*')                     return SY_Mul;
	else if (sym == '(')                     return SY_Br1;
	else if (sym == ')')                     return SY_Br2;
	else if ( (sym >= '0') && (sym <= '9') ) return SY_Num;
	else if (sym == '^')                     return SY_Deg;
	else if (sym == 'e')                     return SY_Exp;
	else                                     return SY_Err;
}

int Calculate (Stack_t * elem, Stack_t * sym)
{
	int check = 0;

	if      ( (char) sym -> Arr[sym -> Last] == '*' )
		check = Stack_Mul (elem);
	else if ( (char) sym -> Arr[sym -> Last] == '/' )
		check = Stack_Div (elem);
	else if ( (char) sym -> Arr[sym -> Last] == '+' )
		check = Stack_Sum (elem);
	else if ( (char) sym -> Arr[sym -> Last] == '-' )
		check = Stack_Sub (elem);
	else if ( (char) sym -> Arr[sym -> Last] == 'e' )
		check = Stack_Exp (elem);
	else if ( (char) sym -> Arr[sym -> Last] == '^' )
		check = Stack_Pow (elem);
	Stack_Pop (sym);
	return check;
}

Arr_type Poland_Recording (const char * str, int * i)
{
	int check = 0;
	ASSERT(str != NULL,"str is a NULL address.");

	int str_len = Func_Strlen (str);

	Stack_t * elem = Stack_Construct (MAXIN);
	Stack_t * sym = Stack_Construct (MAXIN);

	double val = 0;
	int bracket = 0;
	int order = 0;
	while (* i < str_len)
	{
		ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the str.");
		while (str[* i] == ' ') 
		{
			ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the str.");
			(* i)++;
		}
		
		ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the str.");
		SYMBOL sym_val = Symbol_Val (str[* i]);

		val = 0;
		if (sym_val == SY_Num)
		{
			check = Scan_Value (& val, str, i);
			(* i)--;
		}

		if (sym_val == SY_Min)
		{
			if (((bracket != 0) || (elem -> Last == -1)) && (order == 0))
			{
				Stack_Push (elem, 0);
				order = 1;
			}
			else if ((bracket == 0) && (order == 0))
				return -1;
		}
		bracket = 0;

		if (sym_val == SY_Exp)
		{
			ASSERT( ( (* i >= 1) && (* i <= MAXIN) ), "* i is out of the size of the str.");
			ASSERT( ( (* i >= 2) && (* i <= MAXIN + 1) ), "* i is out of the size of the str.");
			if ((str[* i + 1] == 'x') && (str[* i + 2] == 'p'))
				* i =(* i) + 2;
			else sym_val = SY_Err;
		}

		if ( (sym_val == SY_Err) || (Brackets (str) != 1) )
			return -1;

		switch (sym_val)
		{
			case (SY_Num):
				if (order != 0)
					return -1;
				else
				{
					order = 1;
					if (sym->Arr[sym->Last] == '/' && val == 0)
						return -1;
					Stack_Push (elem, (Arr_type) val);
				}
				break;

			case (SY_Br1):
				ASSERT( ( (* i >= 0) && (* i <= MAXIN - 1) ), "* i is out of the size of the str.");
				Stack_Push (sym, (Arr_type) str[* i]);
				bracket = 1;
				break;
			
			case (SY_Plus): case(SY_Min): case(SY_Div): case(SY_Mul): case(SY_Deg):
				if (order != 1)
					return -1;
				else
				{
					order = 0;
					if (sym -> Last > -1)
						while ( Priority (str[* i]) < Priority ((char) sym -> Arr[sym -> Last]) )
							Calculate (elem, sym);
					Stack_Push (sym, (Arr_type) str[* i]);
				}
				break;

			case (SY_Exp):
				if (order != 0)
					return -1;
				else
				{
					if (sym -> Last > -1)
						while ( Priority ('e') < Priority ((char) sym -> Arr[sym -> Last]) )
							Calculate (elem, sym);
					Stack_Push (sym, (Arr_type) 'e');
				}
				break;

			case (SY_Br2):
				while ( (char) sym -> Arr[sym -> Last] != '(' )
					Calculate (elem, sym);
				Stack_Pop (sym);
				break;
		}
		(* i)++;
	}

	while ( sym -> Last != -1)
	{
		check = Calculate (elem, sym);
		if (check == -1) return -1;
	}

	if ( elem -> Last == 0 )
		return Stack_Pop (elem);
	else return -1;
}
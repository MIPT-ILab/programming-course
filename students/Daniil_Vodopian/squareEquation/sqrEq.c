/** ********************************************************************
 @file		sqrEq.c
 @date		2013-10-23 14:45
 @author	Daniil Vodopian <dgvodopyan@gmail.com>
 @version	1.01

 Solving a square equation with minding all cases.

 @par		Task:
			input: 3 coefficients of a square equation
			ouput: number of its roots (-1 in infinity) 
					* and the roots themselves (if exist)
			
 @return 	0: no errors occurred
			1: an unknown exception happened
			2: incorrect input
			
 @note		The precision of output is the second digit after the decimal point
			
 @warning 	Do NOT kill the program!
			It will close by itself after an incorrect input.
			If you want to stop using the program, enter empty line when asked.
***********************************************************************/
//----------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <float.h>
//#include <stdlib.h>
//----------------------------------------------------------------------
#define DEBUG//DEBAG-key
//----------------------------------------------------------------------
#ifdef DEBUG
#define ASSERT(cond) \
	if (!(cond)) {\
		printf("ERROR: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__);\
		abort();\
	}
#else
#define ASSERT(cond)
#endif //DEBUG
//----------------------------------------------------------------------
#define printErr(str)\
	printf("#ERROR: %s", str) //print error massage
//----------------------------------------------------------------------	
#define printInvit \
	printf(">> ")		//print an invitation for input
//----------------------------------------------------------------------
/** ********************************************************************
 solveSquare -  solve a square equation specified by its coefficients
				* in the form a*(x^2) + b*x + c = 0
 
 @param      a	Equation a-coefficient
 @param      b	Equation b-coefficient
 @param      c	Equation c-coefficient
 @param[out] x1	1st root of equation, if exist (if not, value will be unchanged)
 @param[out] x2	2nd root of equation, if exist (if not, value will be unchanged)
 
 @return		Number of roots or zero if none, -1 if infinite number of roots
 
 @note			Calculation precision is considered to be FLT_EPSILON.
***********************************************************************/
int solveSquare (float a, float b, float c, float* x1, float* x2);

/** ********************************************************************
 printEquation - print a square equation specified by its coefficients
					* in the form a*(x^2) + b*x + c = 0

 @param		a	Equation a-coefficient
 @param		b	Equation b-coefficient
 @param		c	Equation c-coefficient

 @note		it prints the only line without '\n' symbols
***********************************************************************/
void printEquation (float a, float b, float c);
//----------------------------------------------------------------------
//MAIN FUNCTION
int main(){
	printf(	"#I will solve your square equation\n");
	printf(	"#Enter three float value, separeted by a space " 
			"- A, B and C coeficients " 
			"in a square euation A*(X^2) + B*X + C = 0\n");
	printInvit;
			
	float A = 0, B = 0, C = 0; 	//coeficients
	switch (scanf("%f %f %f", &A, &B, &C)){	//read input and catch errors
		case EOF: 
			printErr("no float values entered"); return 2; break;
		case 0: case 1: case 2:		//0, 1 or 2 values in the input
			printErr("too few values entered"); return 2; break;
		case 3:						//we have 3 coef. and everything is OK
			break;					//to solve the equation after the switch
		default: 					//more than 3 values in the input
			printErr("too many values entered"); return 2; break;
	}
	
	printf(	"#I will solve this equation:\n" "# ");//print the equation
	printEquation(A, B, C);
	printf("\n");
	
	float X1 = 0, X2 = 0;							//roots
	int rootNum = solveSquare(A, B, C, &X1, &X2); 	//number of roots
	printf("#Number of different roots this equation has:\n" "%d\n", rootNum);
	switch (rootNum){
		case -1: printf("#Every real number is a root\n");								break;
		case  0: printf("#There is NO roots at all\n");									break;
		case  1: printf("#There is only ONE root:\n" " %.2f", X1);						break;
		case  2: printf("#There are TWO defferent roots:\n" " %.2f;  %.2f;", X1, X2); 	break;
		default: printErr("an unknown eror in solving the equation\n"); return 1; 		break;
	}
	
	printf(	"#Thank you for using me to solve your square equation\n");
	return 0;	//everything was OK
}

//----------------------------------------------------------------------
int solveSquare (float a, float b, float c, float* x1, float* x2){
	//a*(x^2) + b*x + c = 0		//general form of the equation
	float d = b*b - 4*a*c;		//discriminant of this equation (if it is a SQUARE one)
	
	if 		(!a && !b && !c)	return -1;	//0 = 0
	else if (!a && !b &&  c)	return  0;	//0 = c
	else if (!a){ 							//it is a LINEAR equation
		*x1 = -c / b;						//b*x = -c
		return  1;
	}
	else if (d < 0)				return  0;	//NO  roots
	else if (d == 0){						//ONE root
		*x1 = -b / (2*a);			
		return  1;
	}
	else{									//TWO roots
		float sqrtD = sqrt(d);
		*x1 = (-b - sqrtD) / (2*a);
		*x2 = (-b + sqrtD) / (2*a);
		return 2;
	}
	
	return -1;
}
//----------------------------------------------------------------------
#define signStr(x) 	(	\
	(x == 0) ? " "  :	\
	(x < 0)  ? "- " :	\
	(x > 0)  ? "+ " : "") //return string with the sign of x

void printEquation (float a, float b, float c){
	if(a || b || c){							//a coef. is NOT zero
		if(a){										//print a-coef
			printf("%s", (a < 0)? "- ": "");					//print sign if required
			if(fabs(a) == 1) 	printf("(X^2)");				//a-coef is NOT required
			else 				printf("%.2f*(X^2)", fabs(a));	//print a-coef without sign
		}
		
		if(b){										//print b-coef
			printf(" %s", ((!a && b < 0) || a)? signStr(b): "");	//print sign if required
			if(fabs(b) == 1)	printf("X");						//b-coef is NOT required
			else 				printf("%.2f*X", fabs(b));			//print b-coef without sign
		}
		
		if(c){										//print c-coef
			printf(" %s", ((!a && !b && c < 0) || (a || b))? signStr(c): "");	//print sign if required
			printf("%.2f", fabs(c)); 											//print c-coef without sign
		}
	}else 		printf("0");					//all coef. are zero
	printf(" = 0");
}//*/

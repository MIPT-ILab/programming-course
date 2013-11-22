// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS 1

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

// G4 ::= E
// E ::= T { [+-] T } *
// T ::= P { [*/] P } *
// P ::= ( E ) | N
// N ::= [0-9] +

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

typedef enum Exc Exc;

enum Exc {
	EXC_OK    = 0,
	EXC_NUM   = 1,
	EXC_DIV_0 = 2,
	EXC_BKT   = 3,
};

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

const char *S = NULL;

Exc flag = EXC_OK;

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetG4 (const char *str);

int GetN ();

int GetE ();

int GetT ();

int GetP ();

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int main ()
{
	char str[200] = {};
	scanf_s ("%s", str, 200); // warning: never! enter ^C symbol. just don't do it.
	GetG4 (str);
	return 0;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetG4 (const char *str)
{
	S = str;
	int val = GetE ();
	if (!(*S == '\0') || flag != EXC_OK) {
		printf ("Expression: __%s__ is not valid: ", str);
		switch (flag) {
			case EXC_OK    : printf ("%c symbol got.", *S);      break;
			case EXC_NUM   : printf ("%c symbol got.", *S);      break;
			case EXC_DIV_0 : printf ("division by 0.");          break;
			case EXC_BKT   : printf ("wrong bracket sequence."); break;
			default : printf ("undefined exception got.");
		}
		printf ("\n");
		return 0;
	}
	printf ("Expression: __%s__ is ok. Result is equal to __%d__.\n", str, val);
	return val;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetN ()
{
	int val = 0;
	if (!('0' <= *S && *S <= '9')) {
		flag = EXC_NUM;
		return -1;
	}
	while ('0' <= *S && *S <= '9') {
		val = val * 10 + *S - '0';
		S++;
	}
	return val;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetE ()
{
	int val = GetT ();
	if (flag != EXC_OK) 
		return -1;
	while (*S == '+' || *S == '-') {
		char op = *S;
		S++;

		int val2 = GetT ();
		if (flag != EXC_OK) 
			return -1;

		if (0);
		else if (op == '+') 
			val += val2;
		else if (op == '-')
			val -= val2;
	}
	return val;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetT ()
{
	int val = GetP ();
	if (flag != EXC_OK) 
		return -1;
	while (*S == '*' || *S == '/') {
		char op = *S;
		S++;

		int val2 = GetP ();
		if (flag != EXC_OK) 
			return -1;

		if (0);
		else if (op == '*') 
			val *= val2;
		else if (op == '/')
			if (val2 != 0)
				val /= val2;
			else {
				flag = EXC_DIV_0;
				return -1;
			}
	}
	return val;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

int GetP ()
{
	if (*S == '(') {
		S++;
		int val = GetE ();

		if (*S != ')') {
			flag = EXC_BKT;
			return -1;
		}

		S++;
		return val;
	}
	else 
		return GetN ();
}
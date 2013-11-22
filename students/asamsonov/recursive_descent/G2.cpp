#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS 1

/*/
	
G2 ::= N
E ::= 
N ::= [0-9] +

/*/

const char *S = NULL;

int GetG0 (const char *str);

int GetN ();

int main ()
{
	char str[200] = {};\
	scanf_s ("%s", str, 200);
	GetG0 (str);
	return 0;
}

int GetG0 (const char *str)
{
	S = str;
	int val = GetN ();
	if (!(*S == '\0')) {
		printf ("Expression: __%s__ is not valid: %c symbol got.\n", str, *S);
		return 0;
	}
	printf ("Expression: __%s__ is ok. Result is equal to __%d__.\n", str, val);
	return val;
}

int GetN ()
{
	int val = 0;
	if (!('0' <= *S && *S <= '9'))
		val = -1;
	while ('0' <= *S && *S <= '9') {
		val = val * 10 + *S - '0';
		S++;
	}
	return val;
}
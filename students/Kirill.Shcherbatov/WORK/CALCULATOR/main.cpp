#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define DEBUG

#ifdef DEBUG
    #define OUT        printf
#else
    #define OUT if (0) printf
#endif

char *expression = NULL,
     *expression_start_point = NULL;

char left_indent = 0;

void   MemoryFree ();
void   BugEnd ();
double GetN ();
double GetP ();
double GetE ();
double GetT ();
double GetG4 ();

int main(int, char *argv[])
{
	OUT("# %s \n"
		"# (%s)\n"
		"# %s %s:\n\n",
		argv[0], __FILE__, __DATE__, __TIME__);

    printf ("Tree builder test.\n");
	printf ("Using:\t'CALCULATOR' \"EXPRESSION\"\n\n");

    if (argv[1] != NULL) expression = strdup(argv[1]);
	else
	{
		printf("No input data argument, enter the expression\n");
		expression = (char*)calloc(255, sizeof(char));
		assert(expression != NULL);
		scanf("%s", expression);
	}

    expression_start_point = expression;
    double result = GetG4 ();
    printf ("Result is %lg\n", result);
    MemoryFree ();
	expression = NULL;
    return 0;
}

#define MK_INDENT for (register unsigned i = 0; i<left_indent; i++) putchar (' ');

void MemoryFree ()
{
    MK_INDENT;
    OUT ("# called MemoryFree\n");

    assert (expression_start_point != NULL);
    free (expression_start_point);
    expression_start_point = NULL;
    expression = NULL;

    MK_INDENT;
    OUT ("# memory freed\n");
}

void BugEnd ()
{
    MK_INDENT;
    OUT ("# called BugEnd; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    printf ("!:\t%s\n!:\t", expression);
    for (register unsigned i = 0; i<expression-expression_start_point; i++)
        putchar (' ');
    printf ("^ a wrong char/operation/var %c\n", *expression);
    MemoryFree ();

    left_indent--;
    MK_INDENT;
    OUT ("# end BugEnd();\n");

    exit (1);
}

double GetG4 ()
{
    MK_INDENT;
    OUT ("# called GetT; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = 0.0;
    val = GetE ();
    if (*expression != 0)
    {
        printf ("!:\texpected end of line\n", *expression);
        BugEnd ();
    }

    left_indent--;
    MK_INDENT;
    OUT ("# end GetG0(); will return %lg\n", val);

    return val;
}

double GetT ()
{
    MK_INDENT;
    OUT ("# called GetT; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = GetP ();
    while (*expression == '*' || *expression == '/')
    {
        char op = *expression++;
        double val2 = GetP ();

        if (op == '/' && val2 == 0)
        {
            printf ("!:\tDevision by zero!\n");
            expression-=1;
            BugEnd ();
        }

        if (op == '*') val *= val2;
        if (op == '/') val /= val2;
    }

    left_indent--;
    MK_INDENT;
    OUT ("# end GetT; will return %lg\n", val);

    return val;
}

double GetE ()
{
    MK_INDENT;
    OUT ("# called GetE; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = GetT ();
    while (*expression == '+' || *expression == '-')
    {
        char op = *expression++;
        double val2 = GetT ();
        if (op == '+') val += val2;
        if (op == '-') val -= val2;
    }

    left_indent--;
    MK_INDENT;
    OUT ("# end GetE; will return %lg\n", val);

    return val;
}

double GetP ()
{
    MK_INDENT;
    OUT ("# called GetP; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = 0;
    if (*expression == '(')
    {
        expression++;
        val = GetE();
        if (*expression++ != ')')
        {
            printf ("!:\tMissing closing brace ')'\n");
            BugEnd ();
        }
    } else val = GetN ();

    left_indent--;
    MK_INDENT;
    OUT ("# end GetP; will return %lg\n", val);

    return val;
}

double GetN ()
{
    MK_INDENT;
    OUT ("# called GetN; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = 0;

    if ('0' <= *expression && *expression <= '9')
    {
        while ('0' <= *expression && *expression <= '9')
        {
            val = val*10 + *expression - '0';
            expression++;
        }
        // reading digits after the decimal point
        if (*expression == '.')
          {
            expression++;
            if ('0' <= *expression && *expression <= '9')
              {
                char dig_n = 0;
                double val2 = 0;
                while ('0' <= *expression && *expression <= '9')
                {
                    val2 = val2*10 + *expression - '0';
                    expression++;
                    dig_n++;
                }
                val += val2 / pow(10, dig_n);
              }
            else
              {
                printf ("!:\tNo digits after the decimal point\n");
                BugEnd ();
              }
          }
         // end reading digits after the decimal point
    } else BugEnd();

    left_indent--;
    MK_INDENT;
    OUT ("# end GetN; will return %lg\n", val);

    return val;
}

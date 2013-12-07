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

double ax = 0, bx = 0, cx = 0, dx = 0;

char left_indent = 0;

void   MemoryFree ();
void   BugEnd ();
double GetN ();
double GetP ();
double GetE ();
double GetT ();
double GetId ();
double AssnOp ();
double Compound ();
double Op ();
double GetG4 ();
double Pgm ();

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
    printf (">>>\tResult is %lg\n", result);
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
    OUT ("# called GetG4; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    double val = 0.0;
    val = Pgm ();
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

double Compound ()
{
    MK_INDENT;
    OUT ("# called Compound; expression[%p] is %s\n", expression, expression);
    left_indent++;

    double val = 0;
    if (*expression == '{')
    {
        expression++;
        while (*expression != '}') val = Op ();
        expression++;
    }

    left_indent--;
    MK_INDENT;
    OUT ("# end Compound();\n");
    return val;
}

double Pgm ()
{
    MK_INDENT;
    OUT ("# called Pgm; expression[%p] is %s\n", expression, expression);
    left_indent++;

    double val = 0;
    while (*expression != 0) val = Op();

    left_indent--;
    MK_INDENT;
    OUT ("# end Pgm();\n");
    return val;
}

double Op ()
{
    MK_INDENT;
    OUT ("# called Op; expression[%p] is %s\n", expression, expression);
    left_indent++;

   char *old_point = expression;
   double val = 0;

   val = AssnOp ();
   if (expression == old_point)
   {
        val = Compound ();
        if (expression == old_point)
        {
            printf ("!:\tBad syntax\n");
            BugEnd ();
        }
    }
    if (*expression != ';' && *expression != 0)
    {
        printf ("!:\tBad syntax\n");
        BugEnd ();
    }
    expression++;

    left_indent--;
    MK_INDENT;
    OUT ("# end Op(); will return %lg\n", val);
    return val;
}

double AssnOp ()
{
    MK_INDENT;
    OUT ("# called AssnOp; expression[%p] is %s\n", expression, expression);
    left_indent++;

    switch (*expression)
    {
        case 'a':
            if (*(expression+1)=='=')
            {
                expression+=2;
                ax = GetE();
                left_indent--;
                return ax;
            }
        case 'b':
            if (*(expression+1)=='=')
            {
                expression+=2;
                bx = GetE();
                left_indent--;
                return bx;
            }
        case 'c':
            if (*(expression+1)=='=')
            {
                expression+=2;
                cx = GetE();
                left_indent--;
                return cx;
            }
        case 'd':
            if (*(expression+1)=='=')
            {
                expression+=2;
                dx = GetE();
                left_indent--;
                return dx;
            }
        default:
            left_indent--;
            return 0;
    }
}

double GetId ()
{
    MK_INDENT;
    OUT ("# called GetId; expression[%p] is %s\n", expression, expression);
    //expression++;
    switch (*(expression))
    {
        case 'a':
            expression++;
            return ax;
        case 'b':
            expression++;
            return bx;
        case 'c':
            expression++;
            return cx;
        case 'd':
            expression++;
            return dx;
        case 'P':
            expression++;
            return M_PI;
        case 'E':
            expression++;
            return M_E;
        case 'S':
            expression++;
            if (*expression == '(')
            {
                expression++;
                left_indent++;
                double val = sin (GetP ());
                if (*expression != ')')
                    {
                        printf ("!:\tNo closing brace\n");
                        BugEnd ();
                    }
                expression++;
                left_indent--;
                return val;
            }
        case 'C':
            expression++;
            if (*expression == '(')
            {
                expression++;
                left_indent++;
                double val = cos (GetP ());
                if (*expression != ')')
                    {
                        printf ("!:\tNo closing brace\n");
                        BugEnd ();
                    }
                expression++;
                left_indent--;
                return val;
            }
        default:
            MK_INDENT;
            OUT ("# end GetId; It isn't Id.\n");
            return 0;
    }
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
    char *old_point = expression;
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
    } else
        {
            val = GetId();
            if (old_point == expression) val = GetN ();
        }

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

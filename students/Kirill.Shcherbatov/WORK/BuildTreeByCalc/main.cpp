
//***************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "tree_t.h"
#include "defines.h"
//***************************************************************************************************


//***************************************************************************************************
char                    *expression                   = NULL,
                        *expression_start_point       = NULL;
//---------------------------------------------------------------------------------------------------
double                  ax                            = 0,
                        bx                            = 0,
                        cx                            = 0,
                        dx                            = 0;
//---------------------------------------------------------------------------------------------------
const char              diff_var                      = 'a';
char                    optimization_carried_out_flag = 0;
//---------------------------------------------------------------------------------------------------
unsigned                left_indent                   = 0; // левый оступ
//***************************************************************************************************


//***************************************************************************************************
void                    MemoryFree ();
void                    BugEnd ();
//---------------------------------------------------------------------------------------------------
struct tree_elem_t      *GetN ();
struct tree_elem_t      *GetE ();
struct tree_elem_t      *GetT ();
struct tree_elem_t      *GetP ();
struct tree_elem_t      *GetG0 ();
//---------------------------------------------------------------------------------------------------
struct tree_elem_t      *GetId ();
struct tree_elem_t      *AssnOp ();
struct tree_elem_t      *Compound ();
struct tree_elem_t      *Op ();
struct tree_elem_t      *Pgm ();
//---------------------------------------------------------------------------------------------------
struct tree_elem_t      *DiffTree (struct tree_elem_t *diff_point);
//---------------------------------------------------------------------------------------------------
void                    OptimizationCalculateSum (struct tree_elem_t *optimize_point);
void                    OptimizationCalculateMul (struct tree_elem_t *optimize_point);
void                    DoOptimization           (struct tree_elem_t *optimize_point);
//***************************************************************************************************


//***************************************************************************************************
int main (int, char *argv[])
{
    OUT("# %s \n"
        "# (%s)\n"
        "# %s %s:\n\n",
        argv[0], __FILE__, __DATE__, __TIME__);

    printf ("Tree builder test.\n"
            "Using:\t'CALCULATOR' \"EXPRESSION\"\n\n"
            "Hi! This program is intended for creation and optimization of the expression trees.\n"
            "With its help, you can also calculate the values ​​of the derivatives by the 'a' argument.\n\n"
            "Grammar:\n"
            " Programm ::= Op+\n"
            " Op       ::= A';' | Compound\n"
            " A        ::= Id'='E\n"
            "  Id      ::= 'a'|'b'|'c'|'d' //or one of:\n"
            "   'S''('E')' // calculates sin(E)\n"
            "   'C''('E')' // calculates cos(E)\n"
            "   'P'        // const Pi = 3.14..\n"
            "   'E'        // const E  = 2,718..\n"
            "   'D''('E')' // find(build) expression d(E)/d(a); use only 'a'' varible in E !!!\n"
            "  E       ::= T{[+-]T}*\n"
            "  T       ::= P{[*/]P}*\n"
            "  P       ::= '('E')' | N\n"
            "  N       ::= [0-9]+{'.'[[0-9]+]+}*\n"
            " Compound = '{'Op+'}'\n\n"
            );
    if (argv[1] != NULL) expression = strdup(argv[1]);
    else
    {
        printf("No input data argument, enter the expression\n");
        expression = (char*)calloc(255, sizeof(char));
        assert(expression != NULL);
        scanf("%s", expression);
    }

    expression_start_point = expression;

    printf ("Start building the ExpressionTree...\n");
    struct tree_elem_t *result = GetG0 (); //Here
    printf (" Ok. The ExpressionTree was successfully builded.\n\n"
            "Now starts an optimization process...\n");

    DoOptimization (result);
    printf (" Ok. The ExpressionTree is ready to use.\n\n"
            "It will be written in file 'result'..\n");

    FILE *fout = fopen ("result", "w");
    tree_print (result, stdout, IN_ORDER);//HERE
    printf ("\n");
    printf (" Ok. ExpressionTreeBuilder have finished all tasks.\n\n");
    fclose (fout);
    tree_destructor (result);
    result = NULL;
    MemoryFree ();
    expression = NULL;
    return 0;
}
//***************************************************************************************************

//***************************************************************************************************
void MemoryFree ()
{

    OUT ("# called MemoryFree\n");

    assert (expression_start_point != NULL);
    free (expression_start_point);
    expression_start_point = NULL;
    expression = NULL;


    OUT ("# memory freed\n");
}
//***************************************************************************************************

//***************************************************************************************************
void BugEnd ()
{

    OUT ("# called BugEnd; expression[%p] is %s\n", expression, expression);
    left_indent++;

    assert (expression != NULL);

    printf ("!:\t%s\n!:\t", expression);
    for (register unsigned i = 0; i<expression-expression_start_point; i++)
        putchar (' ');
    printf ("^ a wrong char/operation/var %c\n", *expression);
    MemoryFree ();

    left_indent--;

    OUT ("# end BugEnd();\n");

    exit (1);
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetG0 ()
{

    OUT ("# called GetG4; expression[%p] is %s\n", expression, expression);
    left_indent++;

    struct tree_elem_t *val = GetE ();

    if (*expression != 0)
    {
        printf ("!:\texpected end of line\n");
        BugEnd ();
    }

    left_indent--;

    OUT ("# end GetG0(); will return %p\n", val);

    return val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetN ()
{

    OUT ("# called GetN; expression[%p] is %s\n", expression, expression);
    left_indent++;
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

    struct tree_elem_t *ret_value = node_constructor (val, INFO_TYPE_NUMBER);

    left_indent--;

    OUT ("# end GetN; will return [%p] => %lg\n", ret_value, val);

    return ret_value;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetE ()
{

    OUT ("# called GetE; expression[%p] is %s\n", expression, expression);
    left_indent++;

    struct tree_elem_t *prev_val = GetT ();

    while (*expression == '+' || *expression == '-')
    {
        struct tree_elem_t *op_node = node_constructor ((double)*expression++, INFO_TYPE_ACTION);
        op_node->link[1] = GetT ();
        op_node->link[0] = prev_val;
        prev_val = op_node;
    }

    left_indent--;

    OUT ("# end GetE; will return [%p]\n", prev_val);

    return prev_val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetT ()
{

    OUT ("# called GetT; expression[%p] is %s\n", expression, expression);
    left_indent++;

    struct tree_elem_t *prev_val = GetP ();

    while (*expression == '*' || *expression == '/')
    {
        char mem_op = *expression;

        struct tree_elem_t *op_node = node_constructor ((double)*expression++, INFO_TYPE_ACTION);
        op_node->link[1] = GetP ();
        if (mem_op == '/' && op_node->link[1]->data.info == 0)
        {
            printf ("!:\tDevision by zero!\n");
            expression-=1;
            BugEnd ();
        }

        op_node->link[0] = prev_val;
        prev_val = op_node;
    }

    left_indent--;

    OUT ("# end GetT; will return [%p]\n", prev_val);

    return prev_val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetP ()
{

    OUT ("# called GetP; expression[%p] is %s\n", expression, expression);
    left_indent++;

    char *old_point = expression;
    struct tree_elem_t *ret_val = NULL;
    if (*expression == '(')
    {
        expression++;
        ret_val = GetE();
        if (*expression++ != ')')
        {
            printf ("!:\tMissing closing brace ')'\n");
            BugEnd ();
        }
    } else
        {
            ret_val = GetId();
            if (old_point == expression) ret_val = GetN ();
        }

    left_indent--;

    OUT ("# end GetP; will return [%p]\n", ret_val);

    return ret_val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *GetId ()
{

    OUT ("# called GetId; expression[%p] is %s\n", expression, expression);

    switch (*expression)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
            return node_constructor ((double)*expression++, INFO_TYPE_ACTION);
        case 'P':
            expression++;
            return node_constructor (M_PI, INFO_TYPE_NUMBER);
        case 'E':
            expression++;
            return node_constructor (M_E, INFO_TYPE_NUMBER);
        case 'S':
        case 'C':
            expression++;
            if (*expression == '(')
            {
                //expression++;
                struct tree_elem_t *ret_val = node_constructor ((double)*(expression-1), INFO_TYPE_ACTION);
                ret_val->link[0]=GetP ();
                return ret_val;
            } else
            {
                printf ("!:\tMissing brace '(' for function\n");
                BugEnd ();
            }
        case 'D':
            expression++;
            if (*expression == '(')
            {
                //expression++;
                struct tree_elem_t *ret_val = DiffTree (GetP ());
                return ret_val;
            } else
            {
                printf ("!:\tMissing brace '(' for Diff operation\n");
                BugEnd ();
            }
        default:

            OUT ("# end GetId; It isn't Id.\n");
            return 0;
    }
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *AssnOp ()
{

    OUT ("# called AssnOp; expression[%p] is %s\n", expression, expression);
    left_indent++;

    switch (*expression)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
            if (*(expression+1) == '=')
            {
                struct tree_elem_t *ret_value = node_constructor ((double)'=', INFO_TYPE_ACTION);
                ret_value->link[0] = node_constructor ((double)(*expression), INFO_TYPE_ACTION);
                expression+=2;
                ret_value->link[1] = GetE ();
                left_indent--;
                return ret_value;
            }
            break;
        default:
            left_indent--;
            return NULL;
    }
    return NULL;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *Compound ()
{

    OUT ("# called Compound; expression[%p] is %s\n", expression, expression);
    left_indent++;

    struct tree_elem_t *ret_val = NULL,
                        *val = NULL;

    if (*expression == '{')
    {
        expression++;
        while (*expression != '}')
        {
            val = Op ();
            if (ret_val != NULL && ret_val->link[1] == NULL) ret_val->link[1] = val;
            if (ret_val==NULL) ret_val = val;
            val = val->link[1];
        }
        expression++;
    }


    val = node_constructor ((double)'{', INFO_TYPE_ACTION);
    val -> link[0] = ret_val;

    left_indent--;

    OUT ("# end Compound();\n");

    return val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *Op ()
{

   OUT ("# called Op; expression[%p] is %s\n", expression, expression);
   left_indent++;

   char *old_point = expression;
   struct tree_elem_t *ret_val = AssnOp ();

   if (expression == old_point)
   {
       ret_val = Compound ();
        if (expression == old_point)
        {
            printf ("!:\tBad syntax\n");
            BugEnd ();
        }
    } else
        if (*expression != ';')
        {
            printf ("!:\tNo ';' after the expression\n");
            BugEnd ();
        }
    expression++;

    struct tree_elem_t *new_ret_val = node_constructor ((double)';', INFO_TYPE_ACTION);
    new_ret_val->link[0] = ret_val;

    left_indent--;

    OUT ("# end Op(); will return [%p]\n", new_ret_val);

    return new_ret_val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *Pgm ()
{

    OUT ("# called Pgm; expression[%p] is %s\n", expression, expression);
    left_indent++;

    struct tree_elem_t *ret_val = Op (),
                       *val = NULL;

    while (*expression != 0)
    {
        val = Op ();
        if (ret_val->link[1] == NULL) ret_val->link[1] = val;
        val = val->link[1];
    }

    left_indent--;

    OUT ("# end Pgm();\n");
    return ret_val;
}
//***************************************************************************************************

//***************************************************************************************************
struct tree_elem_t *DiffTree (struct tree_elem_t *diff_point)
{

    OUT ("# called DiffTree([%p])\n", diff_point);
    assert (diff_point != NULL);
    // Грамматика языка гарантирует, что узлы с числом и переменной diff_var не имеют левых и правых веток
    if (diff_point->data.info_type == INFO_TYPE_NUMBER)
    {
        diff_point->data.info = 0;
        return diff_point;
    }
    if (diff_point->data.info_type == INFO_TYPE_ACTION && (char)diff_point->data.info == diff_var)
    {
        diff_point->data.info = 1;
        diff_point->data.info_type = INFO_TYPE_NUMBER;
        return diff_point;
    }
    // ----------------------------------------------------------------------------------------------------

    if (diff_point->data.info_type == INFO_TYPE_ACTION && ((char)diff_point->data.info == '+' || (char)diff_point->data.info == '-'))
    {
        left_indent++;

        diff_point->link[0] = DiffTree (diff_point->link[0]);
        diff_point->link[1] = DiffTree (diff_point->link[1]);

        left_indent--;
        return diff_point;
    }
    if (diff_point->data.info_type == INFO_TYPE_ACTION && (char)diff_point->data.info == '*')
    {
        left_indent++;

        struct tree_elem_t *ret_value = node_constructor ((double)'+', INFO_TYPE_ACTION);

        ret_value->link[0] = tree_clone (diff_point);
        ret_value->link[0]->link[0] = DiffTree (ret_value->link[0]->link[0]);

        ret_value->link[1] = diff_point;
        ret_value->link[1]->link[1] = DiffTree (ret_value->link[1]->link[1]);

        left_indent--;
        return ret_value;
    }

    if (diff_point->data.info_type == INFO_TYPE_ACTION && (char)diff_point->data.info == '/')
    {
        left_indent++;

        struct tree_elem_t *ret_value = node_constructor ((double)'/', INFO_TYPE_ACTION);

        //numerator
        struct tree_elem_t *numerator = node_constructor ((double)'-', INFO_TYPE_ACTION);

        numerator->link[0] = node_constructor ((double)'*', INFO_TYPE_ACTION);     // (a/b)'=(A'*B-b'*a)/(b*b);
        numerator->link[0]->link[0] = DiffTree (tree_clone (diff_point->link[0])); // (a/b)'=(A'*b-b'*a)/(b*b);
        numerator->link[0]->link[1] = tree_clone (diff_point->link[1]);            // (a/b)'=(a'*B-b'*a)/(b*b);

        numerator->link[1] = node_constructor ((double)'*', INFO_TYPE_ACTION);     // (a/b)'=(a'*b-B'*A)/(b*b);
        numerator->link[1]->link[0] = DiffTree (tree_clone (diff_point->link[1])); // (a/b)'=(a'*b-B'*a)/(b*b);
        numerator->link[1]->link[1] = tree_clone (diff_point->link[0]);            // (a/b)'=(a'*b-b'*A)/(b*b);

        ret_value->link[0] = numerator;

        //denominator
        struct tree_elem_t *denominator = node_constructor ((double)'*', INFO_TYPE_ACTION);
        denominator->link[0] = tree_clone (diff_point->link[1]);                   // (a/b)'=(a'*B-b'*a)/(B*b);
        denominator->link[1] = tree_clone (diff_point->link[1]);                   // (a/b)'=(a'*B-b'*a)/(b*B);

        ret_value->link[1] = denominator;

        tree_destructor (diff_point);
        diff_point = NULL;

        left_indent--;
        return ret_value;
    }

    if (diff_point->data.info_type == INFO_TYPE_ACTION && ((char)diff_point->data.info == 'S' || (char)diff_point->data.info == 'C'))
    {
        left_indent++;

        struct tree_elem_t *ret_value = node_constructor ((double)'*', INFO_TYPE_ACTION);

        if ((char)diff_point->data.info == 'S')
        {
            ret_value->link[0] = tree_clone (diff_point);
            ret_value->link[0]->data.info = (double)'C';
        } else
        {
            ret_value->link[0] = node_constructor ((double)'*', INFO_TYPE_ACTION); //C'=-1*S
            ret_value->link[0]->link[0] = node_constructor (-1, INFO_TYPE_NUMBER);
            ret_value->link[0]->link[1] = tree_clone (diff_point);
            ret_value->link[0]->link[1]->data.info = (double)'S';
        }

        ret_value->link[1] = DiffTree (tree_clone (diff_point->link[0]));

        tree_destructor (diff_point);
        diff_point = NULL;

        left_indent--;
        return ret_value;
    }


    printf ("!:\tI'm sorry, but this structure is not supporting in this version of grammar:\n");

    tree_print (diff_point, stdout, IN_ORDER);
    printf ("\n");
    MemoryFree ();
    exit(1);
}
//***************************************************************************************************

//***************************************************************************************************
void OptimizationCalculateSum (struct tree_elem_t *optimize_point)
{

    OUT ("# called OptimizationCalculateSum([%p])\n", optimize_point);
    assert (optimize_point != NULL);

    if (optimize_point->data.info_type == INFO_TYPE_ACTION &&
            ((char)optimize_point->data.info == '+' || (char)optimize_point->data.info == '-') &&
            optimize_point->link[0]->data.info_type == INFO_TYPE_NUMBER
            && optimize_point->link[1]->data.info_type == INFO_TYPE_NUMBER)
    {
        double value = 0;

        if ((char)optimize_point->data.info == '+')
            value = optimize_point->link[0]->data.info + optimize_point->link[1]->data.info;
            else value = optimize_point->link[0]->data.info - optimize_point->link[1]->data.info;

        tree_destructor (optimize_point->link[0]);
        optimize_point->link[0] = NULL;
        tree_destructor (optimize_point->link[1]);
        optimize_point->link[1] = NULL;

        optimize_point->data.info_type = INFO_TYPE_NUMBER;
        optimize_point->data.info = value;
        \
        optimization_carried_out_flag = 1;

        OUT ("# optimization OptimizationCalculateSum() made\n");
    } else
        if (optimize_point->data.info_type == INFO_TYPE_ACTION &&
                ((char)optimize_point->data.info == '+' || (char)optimize_point->data.info == '-') &&
                (optimize_point->link[1]->data.info_type == INFO_TYPE_NUMBER && optimize_point->link[1]->data.info == 0))
        {
            // smt + 0
            OUT ("FINDED + 0 at right\n");
            optimize_point->data.info = optimize_point->link[0]->data.info;
            optimize_point->data.info_type = optimize_point->link[0]->data.info_type;

            struct tree_elem_t *old_left_to_destroy = optimize_point->link[0],
                               *old_right_to_destroy = optimize_point->link[1];

            if (old_left_to_destroy->link[1] != NULL)
                optimize_point->link[1] = tree_clone (old_left_to_destroy->link[1]);
                else optimize_point->link[1] = NULL;

            if (old_left_to_destroy->link[0] != NULL)
                optimize_point->link[0] = tree_clone (old_left_to_destroy->link[0]);
                else optimize_point->link[0] = NULL;

            tree_destructor (old_left_to_destroy);
            old_left_to_destroy = NULL;
            tree_destructor (old_right_to_destroy);
            old_right_to_destroy = NULL;
        } else
            if (optimize_point->data.info_type == INFO_TYPE_ACTION &&
                    ((char)optimize_point->data.info == '+' || (char)optimize_point->data.info == '-') &&
                    (optimize_point->link[0]->data.info_type == INFO_TYPE_NUMBER && optimize_point->link[0]->data.info == 0))
            {
                // smt*1 and smt/1
                optimize_point->data.info = optimize_point->link[1]->data.info;
                optimize_point->data.info_type = optimize_point->link[1]->data.info_type;

                struct tree_elem_t *old_left_to_destroy = optimize_point->link[0],
                                   *old_right_to_destroy = optimize_point->link[1];

                if (old_right_to_destroy->link[1] != NULL)
                    optimize_point->link[1] = tree_clone (old_right_to_destroy->link[1]);
                    else optimize_point->link[1] = NULL;

                if (old_right_to_destroy->link[0] != NULL)
                    optimize_point->link[0] = tree_clone (old_right_to_destroy->link[0]);
                    else optimize_point->link[0] = NULL;

                tree_destructor (old_left_to_destroy);
                old_left_to_destroy = NULL;
                tree_destructor (old_right_to_destroy);
                old_right_to_destroy = NULL;
            } else
                {
                    left_indent++;
                    if (optimize_point->link[0] != NULL) OptimizationCalculateSum (optimize_point->link[0]);
                    if (optimize_point->link[1] != NULL) OptimizationCalculateSum (optimize_point->link[1]);
                    left_indent--;
                }


    OUT ("# leave OptimizationCalculateSum\n");
}
//***************************************************************************************************

//***************************************************************************************************
void OptimizationCalculateMul (struct tree_elem_t *optimize_point)
{

    OUT ("# called OptimizationCalculateMul([%p])\n", optimize_point);
    assert (optimize_point != NULL);
    if (optimize_point->data.info_type == INFO_TYPE_ACTION &&
            ((char)optimize_point->data.info == '*' || (char)optimize_point->data.info == '/') &&
            (optimize_point->link[0]->data.info_type == INFO_TYPE_NUMBER
            || optimize_point->link[1]->data.info_type == INFO_TYPE_NUMBER))
    {
        if ((optimize_point->link[0]->data.info == 0) || (optimize_point->link[1]->data.info == 0))
        {
            // Грамматика языка гарантирует отсутсвие деления на 0
            tree_destructor (optimize_point->link[0]);
            optimize_point->link[0] = NULL;
            tree_destructor (optimize_point->link[1]);
            optimize_point->link[1] = NULL;

            optimize_point->data.info_type = INFO_TYPE_NUMBER;
            optimize_point->data.info = 0;

            optimization_carried_out_flag = 1;

            OUT ("# optimization OptimizationCalculateSum() made\n");
        } else
            if ((optimize_point->link[0]->data.info_type == INFO_TYPE_NUMBER)
                    && (optimize_point->link[1]->data.info_type == INFO_TYPE_NUMBER))
            {
                double value = 0;

                if ((char)optimize_point->data.info == '*')
                    value = optimize_point->link[0]->data.info * optimize_point->link[1]->data.info;
                    else value = optimize_point->link[0]->data.info / optimize_point->link[1]->data.info;

                tree_destructor (optimize_point->link[0]);
                optimize_point->link[0] = NULL;
                tree_destructor (optimize_point->link[1]);
                optimize_point->link[1] = NULL;

                optimize_point->data.info_type = INFO_TYPE_NUMBER;
                optimize_point->data.info = value;

                optimization_carried_out_flag = 1;

                OUT ("# optimization OptimizationCalculateSum() made\n");
            } else
                if (optimize_point->link[1]->data.info_type == INFO_TYPE_NUMBER && optimize_point->link[1]->data.info == 1)
                {
                    // smt*1 and smt/1
                    optimize_point->data.info = optimize_point->link[0]->data.info;
                    optimize_point->data.info_type = optimize_point->link[0]->data.info_type;

                    struct tree_elem_t *old_left_to_destroy = optimize_point->link[0],
                                       *old_right_to_destroy = optimize_point->link[1];

                    if (old_left_to_destroy->link[1] != NULL)
                        optimize_point->link[1] = tree_clone (old_left_to_destroy->link[1]);
                        else optimize_point->link[1] = NULL;

                    if (old_left_to_destroy->link[0] != NULL)
                        optimize_point->link[0] = tree_clone (old_left_to_destroy->link[0]);
                        else optimize_point->link[0] = NULL;

                    tree_destructor (old_left_to_destroy);
                    old_left_to_destroy = NULL;
                    tree_destructor (old_right_to_destroy);
                    old_right_to_destroy = NULL;
                } else
                    if (optimize_point->link[0]->data.info_type == INFO_TYPE_NUMBER
                            && optimize_point->link[0]->data.info == 1 && (char)optimize_point->data.info == '*')
                    {
                        // 1*smt
                        optimize_point->data.info = optimize_point->link[1]->data.info;
                        optimize_point->data.info_type = optimize_point->link[1]->data.info_type;

                        struct tree_elem_t *old_left_to_destroy = optimize_point->link[0],
                                           *old_right_to_destroy = optimize_point->link[1];

                        if (old_right_to_destroy->link[1] != NULL)
                            optimize_point->link[1] = tree_clone (old_right_to_destroy->link[1]);
                            else optimize_point->link[1] = NULL;

                        if (old_right_to_destroy->link[0] != NULL)
                            optimize_point->link[0] = tree_clone (old_right_to_destroy->link[0]);
                            else  optimize_point->link[0] = NULL;

                        tree_destructor (old_left_to_destroy);
                        old_left_to_destroy = NULL;
                        tree_destructor (old_right_to_destroy);
                        old_right_to_destroy = NULL;
                    }
    } else
    {
        left_indent++;
        if (optimize_point->link[0] != NULL) OptimizationCalculateMul (optimize_point->link[0]);
        if (optimize_point->link[1] != NULL) OptimizationCalculateMul (optimize_point->link[1]);
        left_indent--;
    }

    OUT ("# leave OptimizationCalculateMul [%p]\n", optimize_point);
}
//***************************************************************************************************

//***************************************************************************************************
void DoOptimization (struct tree_elem_t *optimize_point)
{

    OUT ("# called DoOptimization([%p])\n", optimize_point);
    assert (optimize_point != NULL);
    left_indent++;

    optimization_carried_out_flag = 1;
    left_indent++;
    while (optimization_carried_out_flag == 1)
    {
        OUT ("# next iteration of the optimization\n");
        optimization_carried_out_flag = 0;
        OptimizationCalculateMul (optimize_point);
        OptimizationCalculateSum (optimize_point);
    }
    left_indent--;
    left_indent--;

    OUT ("# leave DoOptimization()\n");
}
//***************************************************************************************************

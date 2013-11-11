//---------------------- Block of program constants ------------------------------------------------------------------------------

const int STK_SZ = 200;
const int MAX_INPUT_SIZE = 200;


//---------------------- Block of program structurs ------------------------------------------------------------------------------

struct stack_t
{
    int count;
    int data[STK_SZ];
};


//---------------------- Block of program functions ------------------------------------------------------------------------------

//{=================================================================================
//! stack_construct - Constructor of the stack.
//!
//! @param      stack      Stack
//!
//! @return     Nothing.
//}=================================================================================

void stack_construct (stack_t* stack);

//{=================================================================================
//! stack_destruct - Destractor of the stack.
//!
//! @param      stack      Stack
//!
//! @return     Nothing.
//}=================================================================================

void stack_dectruct (stack_t* stack);

//{=================================================================================
//! stack_ok - Проверка of the stack.
//!
//! @param      stack      Stack
//!
//! @return     'true' if stack is OK or 'false' if stack has bugs.
//}=================================================================================

bool stack_ok (stack_t* stack);

//{=================================================================================
//! stack_dump - print all information about stack.
//!
//! @param      stack      Stack
//!
//! @return     Nothing.
//}=================================================================================

void stack_dump (stack_t* stack);

//{=================================================================================
//! stack_push - Push value from stack.
//!
//! @param      stack      Stack
//! @param      val        pushed value
//!
//! @return     '0' if value has been pushed and '1' if stack is full
//}=================================================================================

int stack_push (stack_t* stack, int val);

//{=====================================================================================
//! stack_pop - Get value from stack and delete it.
//!
//! @param      stack      Stack
//!
//! @return     value if value gets succesful and '2147483647' if stack has no elements
//}=====================================================================================

int stack_pop (stack_t* stack);

//{==========================================================================================================
//! stack_add - Get 2 values from stack and push it's sum.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if stack has only one element.
//}==========================================================================================================

int stack_add (stack_t* stack);

//{==========================================================================================================
//! stack_sub - Get 2 values from stack and push it's sub.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if stack has only one element.
//}==========================================================================================================

int stack_sub (stack_t* stack);

//{==========================================================================================================
//! stack_mul - Get 2 values from stack and push it's multiplicate.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if stack has only one element.
//}==========================================================================================================

int stack_mul (stack_t* stack);

//{============================================================================================================================================
//! stack_div - Get 2 values from stack and push it's sum.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if stack has only one element, '3' if trere was division by zero.
//}============================================================================================================================================

int stack_div (stack_t* stack);

//{==========================================================================================================
//! stack_sin - Get value from stack and push it's sin.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements.
//}==========================================================================================================

int stack_sin (stack_t* stack);

//{==========================================================================================================
//! stack_cos - Get value from stack and push it's cos.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements.
//}==========================================================================================================

int stack_cos (stack_t* stack);

//{==========================================================================================================
//! stack_sqrt - Get value from stack and push it's square root.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if value is sub zero.
//}==========================================================================================================

int stack_sqrt (stack_t* stack);

//{==========================================================================================================
//! stack_pow - Get 2 values from stack and push 1 встепени 2-го.
//!
//! @param      stack      Stack
//!
//! @return     '0' if sum has been pushed, '1' if stack has no elements, '2' if stack has only one element
//}==========================================================================================================

int stack_pow (stack_t* stack);

//{==========================================================================================================
//! stack_pow - Print help with function names and descriptions.
//!
//! @return     Nothing.
//}==========================================================================================================

void stack_help ();


//----------------------- Function: stack_construct ------------------------------------------------------------------------------

void stack_construct (stack_t* stack)
{
    assert (stack);

    stack -> count = 0;
    for (int i = 0; i < STK_SZ; i++)
        stack -> data[i] = 0;

    assert (stack_ok(stack));
}


void stack_dectruct (stack_t* stack)
{
    assert (stack);

    stack -> count = -1;
}


bool stack_ok (stack_t* stack)
{
    return (stack) && (0 <= stack -> count) && (stack -> count <= STK_SZ);
}


//----------------------- Function: stack_dump -----------------------------------------------------------------------------------

void stack_dump (stack_t* stack)
{
    assert (stack);

    printf ("Stack // ");
    if (stack_ok (stack))
    {
        printf ("ok\n"
                         "{\n"
                         "    count = %d \n"
                         "    STK_SZ = %d\n", stack -> count, STK_SZ);
        int i = 0;
        for (i = 0; i < stack -> count; i++)
        {
            printf ("    data[%d] = %d*\n", i, stack -> data[i]);
        }
        for (i = stack -> count; i < STK_SZ; i++)
        {
            printf ("    data[%d] = %d\n", i, stack -> data[i]);
        }
        printf ("}\n");
    }
    else
    {
        printf ("STACK HAS BEEN CRACHED. CLOSE THE PROGRAM AND FIND BUGS\n");
        assert (stack -> count >= 0);
        assert (stack -> count <= STK_SZ);
    }

    assert (stack_ok(stack));
}

//----------------------- Function: stack_push ----------------------------------------------------------------------------------

int stack_push (stack_t* stack, int val)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count == STK_SZ)
        return 1;

    stack -> data[stack -> count] = val;
    stack -> count += 1;

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_pop -----------------------------------------------------------------------------------

int stack_pop (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count == 0)
        return false;

    stack -> count -= 1;
    int buffer = stack -> data[stack -> count];

    assert (stack_ok(stack));

    return buffer;
}


//----------------------- Function: stack_add -----------------------------------------------------------------------------------

int stack_add (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 2)
        return stack -> count + 1;

    int sum1 = stack_pop (stack);
    int sum2 = stack_pop (stack);
    stack_push (stack, sum1 + sum2);

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_sub -----------------------------------------------------------------------------------

int stack_sub (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 2)
        return stack -> count + 1;

    int sub1 = stack_pop (stack);
    int sub2 = stack_pop (stack);
    stack_push (stack, sub1 - sub2);

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_mul -----------------------------------------------------------------------------------

int stack_mul (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 2)
        return stack -> count + 1;

    int mul1 = stack_pop (stack);
    int mul2 = stack_pop (stack);
    stack_push (stack, mul1 * mul2);

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_div -----------------------------------------------------------------------------------

int stack_div (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 2)
        return stack -> count + 1;

    int div1 = stack_pop (stack);
    int div2 = stack_pop (stack);

    if (!div1)
        return 3;

    stack_push (stack, div2 / div1);

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_sin -----------------------------------------------------------------------------------

int stack_sin (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 1)
        return stack -> count + 1;

    int val = stack_pop (stack);
    stack_push (stack, (int) sin(val));

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_cos -----------------------------------------------------------------------------------

int stack_cos (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 1)
        return stack -> count + 1;

    int val = stack_pop (stack);
    stack_push (stack, (int) cos(val));

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_sqrt ----------------------------------------------------------------------------------

int stack_sqrt (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 1)
        return stack -> count + 1;

    int val = stack_pop (stack);

    if (val < 0)
        return 2;

    stack_push (stack, (int) sqrt(val));

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_pow -----------------------------------------------------------------------------------

int stack_pow (stack_t* stack)
{
    assert (stack);
    assert (stack_ok(stack));

    if (stack -> count < 2)
        return stack -> count + 1;

    int pow = stack_pop (stack);
    int val = stack_pop (stack);

    int result = 1;
    for (int i = 0; i < pow; i++)
        result *= val;

    stack_push (stack, result);

    assert (stack_ok(stack));

    return 0;
}


//----------------------- Function: stack_help -----------------------------------------------------------------------------------

void stack_help ()
{
    printf ("You may input:\n"
            "'push 'value'' //to input value into stack                                                                     \n"
            "'top'          //to see last value from stack                                                                  \n"
            "'pop'          //to see last value from stack and delete it                                                    \n"
            "'dump'         //to see all information about stack                                                            \n"
            "'add'          //to sum two last values from stack, delete it and push result into stack                       \n"
            "'sub'          //to sub two last values from stack, delete it and push result into stack                       \n"
            "'mul'          //to multiplicate two last values from stack, delete it and push result into stack              \n"
            "'div'          //to divine two last values from stack, delete it and push result into stack                    \n"
            "'sin'          //to calculate sinus for last value from stack, delete it and push result into stack            \n"
            "'cos'          //to calculate cosinus for last value from stack, delete it and push result into stack          \n"
            "'sqrt'         //to calculate square root for last value from stack, delete it and push result into stack      \n"
            "'pow'          //to pow last value from stack into prelast value, delete it and push result into stack         \n"
            "'end'          //to exit from program                                                                          \n");
}

//----------------------- End of file ---------------------------------------------------------------------------------------------

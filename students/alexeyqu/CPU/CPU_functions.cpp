/** ***************************************************************************
 * @file      CPU_functions.cpp
******************************************************************************/

#include "CPU.h"

int CPU_Construct (CPU_t* cpu)
{
    assert (cpu);

    Stack_Construct (&cpu->stack);
    Stack_Construct (&cpu->call_stack);

    cpu->ax = 0;
    cpu->bx = 0;
    cpu->cx = 0;
    cpu->dx = 0;
    cpu->tx = 0;

    cpu->code_len = 0;

    register unsigned int i = 0;
    for (i = 0; i < MAXIMUM_CODE_LENGTH; i++)
    {
        cpu->code[i] = CMD_END;
    }

    CPU_CHECK (cpu);

    return CPU_OK;
}

int CPU_Destruct (CPU_t* cpu)
{
    CPU_CHECK (cpu);

    Stack_Destruct (&cpu->stack);
    Stack_Destruct (&cpu->call_stack);

    cpu->ax = Poison;
    cpu->bx = Poison;
    cpu->cx = Poison;
    cpu->dx = Poison;
    cpu->tx = Poison;

    cpu->code_len = Poison;

    register unsigned int i = 0;
    for (i = 0; i < MAXIMUM_CODE_LENGTH; i++)
    {
        cpu->code[i] = Poison;
    }

    return CPU_OK;
}

int CPU_Is_OK (const CPU_t* cpu)
{
    if (Stack_Is_OK (&cpu->stack) != STACK_OK) return CPU_ERR_WR_STACK;
    if (Stack_Is_OK (&cpu->call_stack) != STACK_OK) return CPU_ERR_WR_STACK;

    return (cpu->code_len >= 0 &&
            cpu->code_len < MAXIMUM_CODE_LENGTH)? CPU_OK : CPU_ERR_WR_IP;
}

void CPU_Dump (const CPU_t* cpu)
{
    printf ("CPU_Dump.\n");

    printf ("CPU [%08x] %s\n", (int) cpu, (CPU_Is_OK (cpu))? "ok" : "ERROR!");

    printf ("-ax = %lg\n", cpu->ax);
    printf ("-bx = %lg\n", cpu->bx);
    printf ("-cx = %lg\n", cpu->cx);
    printf ("-dx = %lg\n", cpu->dx);
    printf ("-tx = %lg\n", cpu->tx);

    printf ("Calling stack dump:\n");
    Stack_Dump (&cpu->stack);

//    printf ("Calling call_stack dump:\n");
//    Stack_Dump (&cpu->call_stack);
//
//    printf ("Code:\n");
//    printf ("-code_len = %d\n", cpu->code_len);
//
//    register unsigned int i = 0;
//    for (i = 0; i < cpu->code_len; i++)
//    {
//        printf ("\t-code[%d] = %lg\n", i, cpu->code[i]);
//    }

    printf ("CPU_Dump finished.\n");
}

int CPU_Load_Data (CPU_t* cpu, FILE* in_file)
{
    CPU_CHECK (cpu);
    assert (in_file);

    fseek (in_file, 0, 0);

    if (Verify_Signature (in_file) == CPU_ERR_SIGN_WRONG)
    {
        printf ("Wrong signature! Aborting..\n");
        return CPU_ERR_SIGN_WRONG;
    }

    double cmd = 0.0;
    int res_input = 0;
    int end = 0;

    while (1)
    {
        res_input = fscanf (in_file, "%lg", &cmd);
        assert (res_input);

        if (res_input == EOF)
        {
            if (end == 0)
            {
                printf ("Reached end of instructions file.\n"
                        "That's an ERROR!\n");

                return CPU_ERR_LOAD_ERROR;
            }

            return CPU_LOAD_OK;
        }

        if (cmd == CMD_END)
        {
            end = 1;
            cpu->code[cpu->code_len++] = CMD_END;
        }

        cpu->code[cpu->code_len++] = cmd;
    }

    CPU_CHECK (cpu);

    return CPU_LOAD_OK;
}

int Verify_Signature (FILE* file)
{
    assert (file);

    fseek (file, 0, 0);

    char sign[3] = {};
    double ver = 0.0;

    fscanf (file, "%s %lg\n", sign, &ver);

    if (strcmp (sign, SIGNATURE) == 0 && ver == VERSION) return CPU_SIGN_OK;
    else return CPU_ERR_SIGN_WRONG;
}

int CPU_Run (CPU_t* cpu)
{
    CPU_CHECK (cpu);

    #define CHK_ERR_(Code)\
    if (Stack_Error_Catch (Code, "") == STACK_ERR)\
    {\
        return CPU_ERR;\
    }

    #define CHK_CMD_(name, Code)\
    if (cpu->code[cur_pos] == CMD_##name)\
    {\
        Code;\
    }

    unsigned int cur_pos = 0;
    int res_input = 0;

    while (cpu->code[cur_pos] != CMD_BEGIN) cur_pos++;

    while (cur_pos < cpu->code_len)
    {
        CHK_CMD_ (PUSH, CHK_ERR_ (Stack_Push (&cpu->stack, cpu->code[++cur_pos])););
        CHK_CMD_ (POP,  CHK_ERR_ (Stack_Pop (&cpu->stack)););
        CHK_CMD_ (IN,   res_input = scanf ("%lg", &cpu->tx);\
                        assert (res_input);\
                        CHK_ERR_ (Stack_Push (&cpu->stack, cpu->tx)););
        CHK_CMD_ (OUT,  printf ("%lg", Stack_Pop (&cpu->stack)););
        CHK_CMD_ (DUP,  cpu->tx = Stack_Pop (&cpu->stack);\
                        Stack_Push (&cpu->stack, cpu->tx);\
                        Stack_Push (&cpu->stack, cpu->tx););

        CHK_CMD_ (PUSH_AX, CHK_ERR_ (Stack_Push (&cpu->stack, cpu->ax)););
        CHK_CMD_ (POP_AX,  cpu->ax = Stack_Pop (&cpu->stack););
        CHK_CMD_ (PUSH_BX, CHK_ERR_ (Stack_Push (&cpu->stack, cpu->bx)););
        CHK_CMD_ (POP_BX,  cpu->bx = Stack_Pop (&cpu->stack););
        CHK_CMD_ (PUSH_CX, CHK_ERR_ (Stack_Push (&cpu->stack, cpu->cx)););
        CHK_CMD_ (POP_CX,  cpu->cx = Stack_Pop (&cpu->stack););
        CHK_CMD_ (PUSH_DX, CHK_ERR_ (Stack_Push (&cpu->stack, cpu->dx)););
        CHK_CMD_ (POP_DX,  cpu->dx = Stack_Pop (&cpu->stack););

        CHK_CMD_ (ADD,  CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) + Stack_Pop (&cpu->stack))););
        CHK_CMD_ (SUB,  CHK_ERR_ (Stack_Push (&cpu->stack, (- Stack_Pop (&cpu->stack)) + Stack_Pop (&cpu->stack))););
        CHK_CMD_ (MUL,  CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) * Stack_Pop (&cpu->stack))););
        CHK_CMD_ (DIV,  CHK_ERR_ (Stack_Push (&cpu->stack, (double) 1/Stack_Pop (&cpu->stack) * Stack_Pop (&cpu->stack))););

        CHK_CMD_ (POW,  CHK_ERR_ (Stack_Push (&cpu->stack, pow (Stack_Pop (&cpu->stack), Stack_Pop (&cpu->stack)))));
        CHK_CMD_ (SIN,  CHK_ERR_ (Stack_Push (&cpu->stack, sin (Stack_Pop (&cpu->stack)))););
        CHK_CMD_ (COS,  CHK_ERR_ (Stack_Push (&cpu->stack, cos (Stack_Pop (&cpu->stack)))););
        CHK_CMD_ (SQRT, CHK_ERR_ (Stack_Push (&cpu->stack, sqrt (Stack_Pop (&cpu->stack)))););

        CHK_CMD_ (AND,  CHK_ERR_ (Stack_Push (&cpu->stack, (Stack_Pop (&cpu->stack) and Stack_Pop (&cpu->stack)))););
        CHK_CMD_ (OR,   CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) or Stack_Pop (&cpu->stack))););
        CHK_CMD_ (NOT,  CHK_ERR_ (Stack_Push (&cpu->stack, not (Stack_Pop (&cpu->stack)))));

        CHK_CMD_ (EQU,  CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) == Stack_Pop (&cpu->stack))););
        CHK_CMD_ (LT,   CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) < Stack_Pop (&cpu->stack))););
        CHK_CMD_ (GT,   CHK_ERR_ (Stack_Push (&cpu->stack, Stack_Pop (&cpu->stack) > Stack_Pop (&cpu->stack))););

        CHK_CMD_ (JMP,  cur_pos = cpu->code[cur_pos + 1];\
                        continue;);
        CHK_CMD_ (JE,   if (Stack_Pop (&cpu->stack) == Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);
        CHK_CMD_ (JNE,  if (Stack_Pop (&cpu->stack) != Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);
        CHK_CMD_ (JA,   if (Stack_Pop (&cpu->stack) < Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);
        CHK_CMD_ (JAE,  if (Stack_Pop (&cpu->stack) <= Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);
        CHK_CMD_ (JB,   if (Stack_Pop (&cpu->stack) > Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);
        CHK_CMD_ (JBE,  if (Stack_Pop (&cpu->stack) >= Stack_Pop (&cpu->stack))\
                        {cur_pos = cpu->code[cur_pos + 1];\
                        continue;}\
                        else cur_pos++;);

        CHK_CMD_ (CALL, CHK_ERR_ (Stack_Push (&cpu->call_stack, cur_pos + 1));\
                        cur_pos = cpu->code[cur_pos + 1] + 1;\
                        continue;)

        CHK_CMD_ (RET,  cur_pos = Stack_Pop (&cpu->call_stack);)

        CHK_CMD_ (SPC,  printf (" "););
        CHK_CMD_ (TAB,  printf ("\t"););
        CHK_CMD_ (EOL,  printf ("\n"););

        CHK_CMD_ (DUMP, CPU_Dump (cpu););
        CHK_CMD_ (MSG,  while (cpu->code[++cur_pos] != (int) '\n')\
                        {\
                            printf ("%c", (char) cpu->code[cur_pos]);\
                        })

        CHK_CMD_ (END, break;)

        cur_pos++;
    }

    CPU_CHECK (cpu);

    #undef CHK_CMD_
    #undef CHK_ERR_

    return CPU_OK;
}

int CPU_Error_Catch (int err_code, const char* msg, ...)
{
    fprintf (stdin, "%s", msg);

    switch (err_code)
    {
        case CPU_ERR_LOAD_ERROR:
            fprintf (stdin, "Error while loading commands.\n");
            return CPU_ERR;

        case CPU_ERR_NULL:
            fprintf (stdin, "Pointer to CPU is NULL.\n");
            return CPU_ERR;

        case CPU_ERR_SIGN_WRONG:
            fprintf (stdin, "Error signature.\n");
            return CPU_ERR;

        case CPU_ERR_WR_IP:
            va_list args;
            va_start (args, msg);
            fprintf (stdin, "Incorrect ip.\n");
            fprintf (stdin, "[ip = %d, MAX_IP = %d]\n", va_arg (args, int), va_arg (args, int));
            return CPU_ERR;

        case CPU_ERR_WR_STACK:
            fprintf (stdin, "Invalid stack.\n");
            return CPU_ERR;
    }

    return CPU_OK;
}

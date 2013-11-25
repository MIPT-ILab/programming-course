#include "CPU.h"

int Assembler (FILE* in_structions, FILE* out_code, FILE* log)
{
    assert (in_structions); assert (out_code); assert (log);

    fseek (in_structions, 0, 0);
    fseek (out_code, 0, 0);

    DBG_OUT fprintf (log, "Assembler started\n");

    if (Verify_Signature (in_structions) == CPU_SIGN_OK)
    {
        fprintf (out_code, "%s %lg\n\n", SIGNATURE, VERSION);
    }
    else
    {
        printf ("Wrong signature in file in_structions! Aborting..\n");
        return CPU_ERR_SIGN_WRONG;
    }

    #define CHK_CMD_(name)\
    if (strcmp (cmd, #name) == 0)\
    {\
        command_index++;\
        fprintf (out_code, "%d\n", CMD_##name);\
    }

    #define CHK_JMP_(name)\
    if (strcmp (cmd, #name) == 0)\
    {\
        if (fscanf (in_structions, " :%d", &label) == 0)\
        {\
            printf ("Invalid argument of %s. %d\n", #name, command_index);\
            return ASM_ERR_WRONG_ARG;\
        }\
        command_index += 2;\
        fprintf (out_code, "%d %d\n", CMD_##name, labels[label]);\
        continue;\
    }

    char cmd[MAXIMUM_CMD_LENGTH] = {};
    char c = 0;
    double arg = 0.0;
    static unsigned int labels[NUM_OF_LABELS] = {};
    unsigned int label = 0;
    static ProcPointer_t procpointers[NUM_OF_PROC] = {};
    static ProcPointer_t procpointer = {};
    static unsigned int cur_num_of_proc = 0;
    unsigned int command_index = 0;
    int res_input = 0;
    int cpu_reg = 0;
    int begin = 0, end = 0;

    while (1)
    {
        res_input = fscanf (in_structions, "%s", cmd);
        assert (res_input);

        if (res_input == EOF)
        {
            if (end == 0)
            {
                printf ("Reached end of instructions file.\n"
                        "That's an ERROR!\n");

                return ASM_ERR_EOF;
            }

            return ASM_OK;
        }

        if (strcmp (cmd, "BEGIN") == 0)
        {
            begin = 1;
            command_index++;
            fprintf (out_code, "%d\n", CMD_BEGIN);
        }

        if (strcmp (cmd, "END") == 0)
        {
            if (begin == 0)
            {
                printf ("Syntax of your program is incorrect.\n");
                return ASM_ERR_SYNTAX;
            }

            end = 1;
            command_index++;
            fprintf (out_code, "%d\n", CMD_END);
        }

        if (strcmp (cmd, "PUSH") == 0)
        {
            if (fscanf (in_structions, "%lg", &arg) == 0)
            {
                register unsigned int i = 0;
                for (i = 0; i < MAXIMUM_CMD_LENGTH; i++) cmd[i] = 0;

                if (fscanf (in_structions, "%s", cmd) == 0)
                {
                    printf ("Invalid argument of PUSH.\n");

                    return ASM_ERR_WRONG_ARG;
                }
                else
                {
                    cpu_reg = Reg_Ident (cmd);

                    if (cpu_reg == ASM_REG_WRONG) return printf ("Invalid argument of PUSH.\n"), ASM_ERR_WRONG_ARG;

                    cpu_reg += CMD_BASE + 10;

                    command_index++;
                    fprintf (out_code, "%d\n", cpu_reg);
                }
            }
            else
            {
                command_index += 2;
                fprintf (out_code, "%d %lg\n", CMD_PUSH, arg);
            }
        }

        if (strcmp (cmd, "POP") == 0)
        {
            register unsigned int i = 0;
            for (i = 0; i < MAXIMUM_CMD_LENGTH; i++) cmd[i] = 0;

            if (fscanf (in_structions, "%s", cmd) == 0)
            {
                command_index++;
                fprintf (out_code, "%d\n", CMD_POP);
            }
            else
            {
                cpu_reg = Reg_Ident (cmd);

                if (cpu_reg == ASM_REG_WRONG) return printf ("Invalid argument of POP.\n"), ASM_ERR_WRONG_ARG;

                cpu_reg += CMD_BASE + 20;

                command_index++;
                fprintf (out_code, "%d\n", cpu_reg);
            }
        }

        if (strcmp (cmd, ":") == 0)
        {
            if (fscanf (in_structions, "%d", &label) == 0 ||
                label > NUM_OF_LABELS ||
                label <= 0)
            {
                printf ("Incorrect label mentioned.\n");
                return ASM_ERR_RANGE;
            }

            if (labels[label] != 0 &&
                labels[label] != command_index)
            {
                printf ("Redefinition of label %d.\n", label);
                return ASM_ERR_REDEF;
            }

            labels[label] = command_index;
        }

        if (strcmp (cmd, "PROC") == 0)
        {
            if (fscanf (in_structions, " : %s", procpointer.identifier) == 0 ||
                strlen (procpointer.identifier) > PROC_IDENTIFIER_MAX_LEN ||
                strlen (procpointer.identifier) <= 0)
            {
                printf ("Incorrect procpointer mentioned.\n");
                return ASM_ERR_RANGE;
            }

            register unsigned int i = 0;
            for (i = 0; i < cur_num_of_proc; i++)
            {
                if (procpointers[i].ip != 0 &&
                    procpointers[i].ip != command_index)
                {
                    printf ("Redefinition of procpointer '%s'.\n", procpointer.identifier);
                    return ASM_ERR_REDEF;
                }
            }

            procpointer.ip = command_index;

            procpointers[cur_num_of_proc] = procpointer;
            cur_num_of_proc++;
        }

        CHK_JMP_ (JMP);
        CHK_JMP_ (JE);
        CHK_JMP_ (JNE);
        CHK_JMP_ (JA);
        CHK_JMP_ (JAE);
        CHK_JMP_ (JB);
        CHK_JMP_ (JBE);

        if (strcmp (cmd, "CALL") == 0)
        {
            if (fscanf (in_structions, " :%s", procpointer.identifier) == 0)
            {
                printf ("Invalid argument of CALL.\n");
                return ASM_ERR_WRONG_ARG;
            }

            register unsigned int i = 0;
            for (i = 0; i < cur_num_of_proc; i++)
            {
                if (strcmp (procpointers[i].identifier, procpointer.identifier) == 0)
                {
                    fprintf (out_code, "%d %d\n", CMD_CALL, procpointer.ip);
                    break;
                }
            }

            command_index += 2;
            continue;
        }

        CHK_CMD_ (RET);

        CHK_CMD_ (IN);
        CHK_CMD_ (OUT);
        CHK_CMD_ (DUP);

        CHK_CMD_ (ADD);
        CHK_CMD_ (SUB);
        CHK_CMD_ (MUL);
        CHK_CMD_ (DIV);
        CHK_CMD_ (POW);
        CHK_CMD_ (SIN);
        CHK_CMD_ (COS);
        CHK_CMD_ (SQRT);

        CHK_CMD_ (AND);
        CHK_CMD_ (OR);
        CHK_CMD_ (NOT);

        CHK_CMD_ (EQU);
        CHK_CMD_ (LT);
        CHK_CMD_ (GT);

        CHK_CMD_ (SPC);
        CHK_CMD_ (TAB);
        CHK_CMD_ (EOL);

        CHK_CMD_ (DUMP);

        if (strcmp (cmd, "MSG") == 0)
        {
            command_index++;
            fprintf (out_code, "%d", CMD_MSG);

            while (1)
            {
                fscanf (in_structions, "%c", &c);

                if (c == '"') break;

                if (c == '\n')
                {
                    printf ("Invalid message!");
                    return ASM_ERR_SYNTAX;
                }
            }

            while (1)
            {
                res_input = fscanf (in_structions, "%c", &c);
                assert (res_input);

                if (c == '"')
                {
                    command_index++;
                    fprintf (out_code, " %d", (int) '\n');
                    break;
                }

                if (c == '\n')
                {
                    printf ("Invalid message!");
                    return ASM_ERR_SYNTAX;
                }

                command_index++;
                fprintf (out_code, " %d", (int) c);
            }

            fprintf (out_code, "\n");
        }

        if (strcmp (cmd, "//") == 0)
        {
            while (1)
            {
                res_input = fscanf (in_structions, "%c", &c);
                assert (res_input);

                if (c == '\n') break;
            }
        }

        CHK_CMD_ (ERROR);
    }

    #undef CHK_CMD_

    return ASM_OK;
}

/*int Disasm (FILE* in_code, FILE* out_structions) //Labels AND functions NOT staged yet.
{
    assert (in_code); assert (out_structions);

    fseek (in_code, 0, 0);
    fseek (out_structions, 0, 0);

    if (Verify_Signature (in_code) == ASM_SIGN_OK)
    {
        fprintf (out_structions, "AQ %lg\n\n", VERSION);
    }
    else
    {
        printf ("Wrong signature! Aborting..\n");
        return ASM_ERROR;
    }

    #define CHK_CMD_(name)\
    if (cmd == CMD_##name)\
    {\
        fprintf (out_structions, "%s\n", #name);\
    }

    #define CHK_CMD_REG_(name, reg)\
    if (cmd == CMD_##name##_##reg)\
    {\
        fprintf (out_structions, "%s %s\n", #name, #reg);\
    }

    int cmd = 0;
    double arg = 0.0;
    int res_input = 0;

    while (1)
    {
        res_input = fscanf (in_code, "%d", &cmd);
        assert (res_input);

        if (res_input == EOF)
        {
            printf ("Reached end of instructions file.\n"
                    "That's an ERROR!\n");

            return ASM_ERROR;
        }

        if (cmd == 0)
        {
            fprintf (out_structions, "END\n");

            return ASM_END;
        }

        if (cmd == CMD_PUSH)
        {
            if (fscanf (in_code, "%lg", &arg) == 0)
            {
                printf ("Invalid argument of PUSH.\n");

                return ASM_ERROR;
            }
            else
            {
                fprintf (out_structions, "PUSH %lg\n", arg);
            }
        }

        CHK_CMD_ (POP);
        CHK_CMD_ (IN);
        CHK_CMD_ (OUT);
        CHK_CMD_ (DUP);

        CHK_CMD_REG_ (PUSH, AX);
        CHK_CMD_REG_ (POP, AX);
        CHK_CMD_REG_ (PUSH, BX);
        CHK_CMD_REG_ (POP, BX);
        CHK_CMD_REG_ (PUSH, CX);
        CHK_CMD_REG_ (POP, CX);
        CHK_CMD_REG_ (PUSH, DX);
        CHK_CMD_REG_ (POP, DX);

        CHK_CMD_ (ADD);
        CHK_CMD_ (SUB);
        CHK_CMD_ (MUL);
        CHK_CMD_ (DIV);
        CHK_CMD_ (POW);
        CHK_CMD_ (SIN);
        CHK_CMD_ (COS);
        CHK_CMD_ (SQRT);

        CHK_CMD_ (DUMP);
    }

    #undef CHK_CMD_REG_
    #undef CHK_CMD_
}
*/
int Reg_Ident (char reg[])
{
    if (reg[2] != '\0' || reg[1] != 'X')
    {
        printf ("Invalid argument of command.\n");

        return ASM_REG_WRONG;
    }

    char rgstr = reg[0] - 'A' + 1;

    return rgstr;
}

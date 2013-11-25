/** ***************************************************************************
 * @file    asm.cpp
 * @mainpage
 * @author  Alexey Kulikov <alexeyqu@gmail.com>, 376 group, DCAM MIPT
 * @date    2013-11-7 23:42
 * @version 1.0
 *
 * Asm.
 * Assembler and disassembler functions on a determined command field for CPU.
 *
 * @par     V1.0
 *          - Realised functions Assembler and Disasm
 *          - Realised checking of signatures in files
 *
 * @todo    Add log prints
******************************************************************************/

#include "asm.h"

int main()
{
    FILE* Log = fopen ("log.txt", "w");
    FILE* To_asm = fopen ("input.txt", "r");
    FILE* Code = fopen ("code.txt", "w+");

    Assembler (To_asm, Code, Log);

    fclose (To_asm);

    FILE* From_disasm = fopen ("output.txt", "w");

    Disasm (Code, From_disasm, Log);

    fclose (From_disasm);
    fclose (Code);
    fclose (Log);

    return 0;
}

int Assembler (FILE* in_structions, FILE* out_code, FILE* log)
{
    assert (in_structions); assert (out_code);

    fseek (in_structions, 0, 0);
    fseek (out_code, 0, 0);

    if (Verify_Signature (in_structions) == SIGN_OK)
    {
        fprintf (out_code, "AQ %lg\n\n", ASM_VERSION);
    }
    else
    {
        LOG ("Wrong signature! Aborting..\n");
        return ASM_ERROR;
    }

    #define CHK_CMD_(name)\
    if (strcmp (cmd, #name) == 0)\
    {\
        fprintf (out_code, "%d\n", CMD_##name);\
    }

    char cmd[MAXIMUM_CMD_LENGTH] = {};
    double arg = 0.0;
    int res_input = 0;

    while (1)
    {
        res_input = fscanf (in_structions, "%s", cmd);
        assert (res_input);

        if (res_input == EOF)
        {
            LOG ("Reached end of instructions file.\n"
                 "That's an ERROR!\n");

            return ASM_ERROR;
        }

        if (strcmp (cmd, "END") == 0)
        {
            fprintf (out_code, "%d\n", CMD_END);

            return ASM_END;
        }

        if (strcmp (cmd, "PUSH") == 0)
        {
            if (fscanf (in_structions, "%lg", &arg) == 0)
            {
                register unsigned int i = 0;
                for (i = 0; i < MAXIMUM_CMD_LENGTH; i++) cmd[i] = 0;

                if (fscanf (in_structions, "%s", cmd) == 0)
                {
                    LOG ("Invalid argument of PUSH.\n");

                    return ASM_ERROR;
                }
                else
                {
                    if (cmd[2] != '\0' || cmd[1] != 'X')
                    {
                        LOG ("Invalid argument of PUSH.\n");

                        return ASM_ERROR;
                    }

                    switch (cmd[0])
                    {
                        case 'A':
                            fprintf (out_code, "%d\n", CMD_PUSH_AX);
                            break;

                        case 'B':
                            fprintf (out_code, "%d\n", CMD_PUSH_BX);
                            break;

                        case 'C':
                            fprintf (out_code, "%d\n", CMD_PUSH_CX);
                            break;

                        case 'D':
                            fprintf (out_code, "%d\n", CMD_PUSH_DX);
                            break;

                        default:
                            printf ("Invalid argument of PUSH.\n");
                            return ASM_ERROR;
                    }
                }
            }
            else
            {
                fprintf (out_code, "%d %lg\n", CMD_PUSH, arg);
            }
        }

        if (strcmp (cmd, "POP") == 0)
        {
            register unsigned int i = 0;
            for (i = 0; i < MAXIMUM_CMD_LENGTH; i++) cmd[i] = 0;

            if (fscanf (in_structions, "%s", cmd) == 0)
            {
                fprintf (out_code, "%d\n", CMD_POP);
            }
            else
            {
                if (cmd[2] != '\0' || cmd[1] != 'X')
                {
                    LOG ("Invalid argument of POP.\n");

                    return ASM_ERROR;
                }

                switch (cmd[0])
                {
                    case 'A':
                        fprintf (out_code, "%d\n", CMD_POP_AX);
                        break;

                    case 'B':
                        fprintf (out_code, "%d\n", CMD_POP_BX);
                        break;

                    case 'C':
                        fprintf (out_code, "%d\n", CMD_POP_CX);
                        break;

                    case 'D':
                        fprintf (out_code, "%d\n", CMD_POP_DX);
                        break;

                    default:
                        printf ("Invalid argument of POP.\n");
                        return ASM_ERROR;
                }
            }
        }

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

        CHK_CMD_ (DUMP);
        CHK_CMD_ (ERROR);
    }

    #undef CHK_CMD_

    return ASM_OK;
}

int Disasm (FILE* in_code, FILE* out_structions, FILE* log)
{
    assert (in_code); assert (out_structions);

    fseek (in_code, 0, 0);
    fseek (out_structions, 0, 0);

    if (Verify_Signature (in_code) == SIGN_OK)
    {
        fprintf (out_structions, "AQ %lg\n\n", ASM_VERSION);
    }
    else
    {
        LOG ("Wrong signature! Aborting..\n");
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
            LOG ("Reached end of instructions file.\n"
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
                LOG ("Invalid argument of PUSH.\n");

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

int Verify_Signature (FILE* asm_file)
{
    assert (asm_file);

    fseek (asm_file, 0, 0);

    char sign[3] = {};
    double ver = 0.0;

    fscanf (asm_file, "%s %lg\n", sign, &ver);

    if (strcmp (sign, SIGNATURE) == 0 && ver == ASM_VERSION) return SIGN_OK;
    else return SIGN_WRONG;
}

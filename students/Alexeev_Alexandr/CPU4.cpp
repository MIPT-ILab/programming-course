//{=====================================================================================
//! @file   CPU4.cpp
//! @date   2013-11-4 12:43
//! @author Alexeev Alexandr
//!
//! CPU emulator. You give program in accembler language and program compiling and run it.
//! You can see list of assembler instructions in file 'help.txt'.
//!
//! @warning The last instruction must be 'end'.
//}=====================================================================================

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "stack.h"
#define print_the_description printf ("# CPU emulator\n"                                                                  \
                                      "# Copyrights (C) 2013 Alekseev Aleksandr\n"                                        \
                                      "# Last compiling 2013-10-20 12:28\n"                                               \
                                      "# If you want to see list of CPU's assembler instructions, please open help.txt\n")


//---------------------- Block of program constants ------------------------------------------------------------------------------

const int MAX_PROG_SIZE = 400;
const int MAX_FILENAME_SIZE = 30;


//---------------------- Block of program structurs ------------------------------------------------------------------------------

struct CPU
{
    int ax, bx, cx, dx;
    stack_t stack;
    stack_t func_stack;
    int prog_mem[MAX_PROG_SIZE];
    int label_array[MAX_PROG_SIZE];
};


//---------------------- Block of program functions ------------------------------------------------------------------------------

//{=================================================================================
//! cpu_construct - Constructor of the cpu.
//!
//! @param      cpu     cpu
//!
//! @return     Nothing.
//}=================================================================================

void cpu_construct (CPU* cpu);

//{=================================================================================
//! cpu_destruct - Destractor of the cpu.
//!
//! @param      cpu      cpu
//!
//! @return     Nothing.
//}=================================================================================

void cpu_destruct (CPU* cpu);

//{=================================================================================
//! cpu_ok - Check the correctness of the stack
//!
//! @param      cpu   cpu
//!
//! @return     'true' if cpu is OK or 'false' if cpu has bugs.
//}=================================================================================

bool cpu_ok (CPU* cpu);

//{=================================================================================
//! cpu_dump - print all information about cpu.
//!
//! @param      cpu     cpu
//!
//! @return     Nothing.
//}=================================================================================

void cpu_dump (CPU* cpu);

//{=================================================================================
//! cpu_assembler - translate program from file into cpu code;
//!
//! @param      file_name - name of file with program
//! @param      cpu       - cpu
//!
//! @return     '0' if assebler has been crashed and size of used program memory if assembler has been worked succesfull.
//}=================================================================================

int cpu_assmbler (char* file_name, CPU* cpu);

//{=================================================================================
//! cpu_run - launch program from program memory.
//!
//! @param      prog_mem_size - number of elements in program memory
//! @param      cpu           - cpu
//! @param[out] result        - result of the program
//!
//! @return     '0' if program finished succesful and position in program memory if program crashed in this position.
//}=================================================================================

int cpu_run (CPU* cpu, int prog_mem_size);

//{=================================================================================
//! cpu_dbz_interrupt - processing interrupt of divining by zero
//!
//! @param      position - position in program memory where this error happens
//!
//! @return     Nothing.
//}=================================================================================

void cpu_dbz_interrupt (int position);

//{=================================================================================
//! cpu_full_stack_interrupt - processing interrupt of pushing in full stack
//!
//! @param      position - position in program memory where this error happens
//!
//! @return     Nothing.
//}=================================================================================

void cpu_full_stack_interrupt (int position);

//{=================================================================================
//! cpu_empty_stack_interrupt - processing interrupt of getting value from empty stack
//!
//! @param      position - position in program memory where this error happens
//!
//! @return     Nothing.
//}=================================================================================

void cpu_empty_stack_interrupt (int position);


//----------------------- Function: main -----------------------------------------------------------------------------------------

int main ()
{
    print_the_description;

    char file_name[MAX_FILENAME_SIZE] = {};
    printf ("Input name of program file: ");
    int name_size;
    for (name_size = 0; file_name[name_size - 1] != '\n'; name_size++)
        scanf ("%c", &file_name[name_size]);
    file_name[name_size - 1] = '\0';

    CPU cpu;

    cpu_construct (&cpu);

    int prog_mem_size = cpu_assmbler (file_name, &cpu);
        prog_mem_size = cpu_assmbler (file_name, &cpu);

    if (!prog_mem_size)
        printf ("Assembler has been crashed. Your code has bugs.\n");

    cpu_run (&cpu, prog_mem_size);

    cpu_destruct(&cpu);

    return 0;
}


//----------------------- Function: cpu_construct ------------------------------------------------------------------------------

void cpu_construct (CPU* cpu)
{
    assert (cpu);

    cpu -> ax = 0;
    cpu -> bx = 0;
    cpu -> cx = 0;
    cpu -> dx = 0;

    stack_construct (&cpu -> stack);
    stack_construct (&cpu -> func_stack);

    for (int i = 0; i < MAX_PROG_SIZE; i++)
        cpu -> prog_mem[i] = 0;
    for (int i = 0; i < MAX_PROG_SIZE; i++)
        cpu -> label_array[i] = -1;

    assert (stack_ok(&cpu -> stack));
}


//----------------------- Function: cpu_destruct ------------------------------------------------------------------------------

void cpu_destruct (CPU* cpu)
{
    assert (cpu);

    cpu -> ax = -2147483647;
    stack_dectruct(&cpu -> stack);
    stack_dectruct(&cpu -> func_stack);
}


//----------------------- Function: cpu_ok ------------------------------------------------------------------------------------

bool cpu_ok (CPU* cpu)
{
    return (cpu) && stack_ok (&cpu -> stack) && stack_ok (&cpu -> func_stack);
}


//----------------------- Function: cpu_dump ---------------------------------------------------------------------------------

void cpu_dump (CPU* cpu)
{
    assert (cpu);

    if (cpu_ok (cpu))
    {
        printf ("CPU // ok\n");
        printf ("ax = %d\n", cpu -> ax);
        printf ("Program memory - ");
        for (int i = 0; i < MAX_PROG_SIZE; i++)
            printf ("%d ", cpu -> prog_mem[i]);
        printf ("\n");
        printf ("Label array - ");
        for (int i = 0; i < MAX_PROG_SIZE; i++)
            printf ("%d ", cpu -> label_array[i]);
        printf ("\n");
        stack_dump (&cpu -> stack);
        stack_dump (&cpu -> func_stack);
    }
    else
    {
        printf ("CPU // CPU HAS BEEN CRACHED. CLOSE THE PROGRAM AND FIND BUGS\n");
        stack_dump (&cpu -> stack);
    }
}


//----------------------- Function: cpu_assembler --------------------------------------------------------------------------------

int cpu_assmbler (char* file_name, CPU* cpu)
{
    assert (cpu);
    assert (cpu_ok(cpu));

    FILE *input = fopen (file_name, "r");

    char input_data[MAX_INPUT_SIZE] = {};
    int prog_mem_pos = 0; //current position in program memory
    bool input_flag = true;
    while (input_flag)
    {
        input_flag = false;

        for (int i = 0; (input_data[i - 1] != '\n') && (i < MAX_INPUT_SIZE); i++)
            fscanf (input, "%c", &input_data[i]);

        if ((input_data[0] == 'e') && (input_data[1] == 'n') && (input_data[2] == 'd'))
        {
            input_flag = false;
            cpu -> prog_mem[prog_mem_pos] = 0;
            prog_mem_pos++;
            continue;
        }

        //push
        if ((input_data[0] == 'p') && (input_data[1] == 'u') && (input_data[2] == 's') && (input_data[3] == 'h'))
        {
            if ((input_data[5] == 'a') && (input_data[6] == 'x'))
            {
                input_flag = true;
                cpu -> prog_mem[prog_mem_pos] = 1;
                prog_mem_pos++;
            }
            else
            {
                //push bx
                if ((input_data[5] == 'b') && (input_data[6] == 'x'))
                {
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 17;
                    prog_mem_pos++;
                }
                else
                {
                    //push cx
                    if ((input_data[5] == 'c') && (input_data[6] == 'x'))
                    {
                        input_flag = true;
                        cpu -> prog_mem[prog_mem_pos] = 18;
                        prog_mem_pos++;
                    }
                    else
                    {
                        //push dx
                        if ((input_data[5] == 'd') && (input_data[6] == 'x'))
                        {
                            input_flag = true;
                            cpu -> prog_mem[prog_mem_pos] = 19;
                            prog_mem_pos++;
                        }
                        else
                        {
                            //push 'value'
                            if (((input_data[5] - '0' >= 0) && (input_data[5] - '0' <= 9)) || (input_data[5] == '-'))
                            {
                                input_flag = true;
                                int value = 0;
                                int i = 0;
                                int sign = 1, sign_flag = 5;
                                if (input_data[5] == '-')
                                {
                                    sign = -1;
                                    sign_flag = 6;
                                }
                                for (i = sign_flag; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                                {
                                    value *= 10;
                                    value += input_data[i] - '0';
                                }
                                cpu -> prog_mem[prog_mem_pos] = 2;
                                cpu -> prog_mem[prog_mem_pos + 1] = value * sign;
                                prog_mem_pos++;
                                prog_mem_pos++;

                            }
                            else
                            {
                                input_flag = false;
                            }
                        }
                    }
                }
            }
        }

        //add
        if ((input_data[0] == 'a') && (input_data[1] == 'd') && (input_data[2] == 'd'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 4;
            prog_mem_pos++;
        }

        //sub
        if ((input_data[0] == 's') && (input_data[1] == 'u') && (input_data[2] == 'b'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 5;
            prog_mem_pos++;
        }

        //mul
        if ((input_data[0] == 'm') && (input_data[1] == 'u') && (input_data[2] == 'l'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 6;
            prog_mem_pos++;
        }

        //cos
        if ((input_data[0] == 'c') && (input_data[1] == 'o') && (input_data[2] == 's'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 10;
            prog_mem_pos++;
        }

        //div
        if ((input_data[0] == 'd') && (input_data[1] == 'i') && (input_data[2] == 'v'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 7;
            prog_mem_pos++;
        }

        //dump
        if ((input_data[0] == 'd') && (input_data[1] == 'u') && (input_data[2] == 'm') && (input_data[3] == 'p'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 12;
            prog_mem_pos++;
        }

        //sin
        if ((input_data[0] == 's') && (input_data[1] == 'i') && (input_data[2] == 'n'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 9;
            prog_mem_pos++;
        }

        //pow
        if ((input_data[0] == 'p') && (input_data[1] == 'o') && (input_data[2] == 'w'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 8;
            prog_mem_pos++;
        }

        //pop
        if ((input_data[0] == 'p') && (input_data[1] == 'o') && (input_data[2] == 'p'))
        {
            if ((input_data[4] <= 'a') && (input_data[4] >= 'd'))
            {
                input_flag = true;
                cpu -> prog_mem[prog_mem_pos] = 3;
                prog_mem_pos++;
            }
            else
            {
                //pop ax
                if ((input_data[4] == 'a') && (input_data[5] == 'x'))
                //if (input_data[3] == 'a')
                {
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 13;
                    prog_mem_pos++;
                }
                else
                {
                    //pop bx
                    if ((input_data[4] == 'b') && (input_data[5] == 'x'))
                    {
                        input_flag = true;
                        cpu -> prog_mem[prog_mem_pos] = 14;
                        prog_mem_pos++;
                    }
                    else
                    {
                        //pop cx
                        if ((input_data[4] == 'c') && (input_data[5] == 'x'))
                        {
                            input_flag = true;
                            cpu -> prog_mem[prog_mem_pos] = 15;
                            prog_mem_pos++;
                        }
                        else
                        {
                            //pop dx
                            if ((input_data[4] == 'd') && (input_data[5] == 'x'))
                            {
                                input_flag = true;
                                cpu -> prog_mem[prog_mem_pos] = 16;
                                prog_mem_pos++;
                            }
                            else
                                input_flag = false;
                        }
                    }
                }
            }
        }

        //sqrt
        if ((input_data[0] == 's') && (input_data[1] == 'q') && (input_data[2] == 'r') && (input_data[3] == 't'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 11;
            prog_mem_pos++;
        }

        //jmp
        if ((input_data[0] == 'j') && (input_data[1] == 'm') && (input_data[2] == 'p'))
        {
            if (input_data[4] == ':')
            {
                int label_value = 0;
                if ((input_data[5] - '0' >= 0) && (input_data[5] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 5; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 21;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }

        //jbe
        if ((input_data[0] == 'j') && (input_data[1] == 'b') && (input_data[2] == 'e'))
        {
            if (input_data[4] == ':')
            {
                int label_value = 0;
                if ((input_data[5] - '0' >= 0) && (input_data[5] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 5; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 20;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }


        //jba
        if ((input_data[0] == 'j') && (input_data[1] == 'b') && (input_data[2] == 'a'))
        {
            if (input_data[4] == ':')
            {
                int label_value = 0;
                if ((input_data[5] - '0' >= 0) && (input_data[5] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 5; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 26;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }


        //ja
        if ((input_data[0] == 'j') && (input_data[1] == 'a') && (input_data[2] == ' '))
        {
            if (input_data[3] == ':')
            {
                int label_value = 0;
                if ((input_data[4] - '0' >= 0) && (input_data[4] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 4; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 27;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }

        //jnb
        if ((input_data[0] == 'j') && (input_data[1] == 'n') && (input_data[2] == 'b'))
        {
            if (input_data[4] == ':')
            {
                int label_value = 0;
                if ((input_data[5] - '0' >= 0) && (input_data[5] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 5; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 30;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }

        //je
        if ((input_data[0] == 'j') && (input_data[1] == 'e') && (input_data[2] == ' '))
        {
            if (input_data[3] == ':')
            {
                int label_value = 0;
                if ((input_data[4] - '0' >= 0) && (input_data[4] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 4; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 28;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }


        //jb
        if ((input_data[0] == 'j') && (input_data[1] == 'b') && (input_data[2] == ' '))
        {
            if (input_data[3] == ':')
            {
                int label_value = 0;
                if ((input_data[4] - '0' >= 0) && (input_data[4] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 4; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 29;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }

        //:
        if (input_data[0] == ':')
        {
            int label_value = 0;
            if ((input_data[1] - '0' >= 0) && (input_data[1] - '0' <= 9))
            {
                int i = 0;
                for (i = 1; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                }
                input_flag = true;

                assert (label_value >= 0);
                assert (label_value <= MAX_PROG_SIZE);
                cpu -> label_array[label_value] = prog_mem_pos;
            }
            else
                input_flag = false;
        }

        //halt
        if ((input_data[0] == 'h') && (input_data[1] == 'a') && (input_data[2] == 'l') && (input_data[3] == 't'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 22;
            prog_mem_pos++;
        }

        //out
        if ((input_data[0] == 'o') && (input_data[1] == 'u') && (input_data[2] == 't'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 23;
            prog_mem_pos++;
        }

        //WTF??
        if (input_data[0] == '\n')
        {
            input_flag = true;
            prog_mem_pos++;
            return prog_mem_pos;
        }

        //call
        if ((input_data[0] == 'c') && (input_data[1] == 'a') && (input_data[2] == 'l') && (input_data[3] == 'l'))
        {
            if (input_data[5] == ':')
            {
                int label_value = 0;
                if ((input_data[6] - '0' >= 0) && (input_data[6] - '0' <= 9))
                {
                    int i = 0;
                    for (i = 6; (input_data[i] != '\n') && ((input_data[i] - '0' >= 0) && (input_data[i] - '0' <= 9)); i++)
                    {
                        label_value *= 10;
                        label_value += input_data[i] - '0';
                    }
                    input_flag = true;
                    cpu -> prog_mem[prog_mem_pos] = 24;

                    assert (label_value >= 0);
                    assert (label_value <= MAX_PROG_SIZE);
                    cpu -> prog_mem[prog_mem_pos + 1] = cpu -> label_array[label_value];

                    prog_mem_pos++;
                    prog_mem_pos++;
                }
                else
                    input_flag = false;
            }
            else
                input_flag = false;
        }

        //ret
        if ((input_data[0] == 'r') && (input_data[1] == 'e') && (input_data[2] == 't'))
        {
            input_flag = true;
            cpu -> prog_mem[prog_mem_pos] = 25;
            prog_mem_pos++;
        }

        if ((!input_flag) && (input_data[0] != 'e'))
            return 0;
    }

    return prog_mem_pos;

    assert (cpu_ok(cpu));
}


//----------------------- Function: cpu_run ---------------------------------------------------------------------------------------

int cpu_run (CPU* cpu, int prog_mem_size)
{
    for (int curr_pos = 0; curr_pos < prog_mem_size; curr_pos++)
    {
            int value = 0;
            int value1 = 0, value2 = 0; //values for jbe or jmp
            int operation_res = 0;
            switch (cpu -> prog_mem[curr_pos])
            {
                case 0 :
                    return 0;
                    break;
                case 1 :
                    value = cpu -> ax;

                    operation_res = stack_push (&cpu -> stack, value);

                    if (operation_res)
                    {
                        cpu_full_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack is full! You can not push values! In program memory position %d\n", i);
                    }
                    break;
                case 2 :
                    curr_pos++;
                    value = cpu -> prog_mem[curr_pos];

                    operation_res = stack_push (&cpu -> stack, value);

                    if (operation_res)
                    {
                        cpu_full_stack_interrupt (curr_pos - 1);
                        return curr_pos - 1;
                        //printf ("Error! Stack is full! You can not push values! In program memory position %d\n", i - 1);
                    }
                    break;
                case 3 :
                    operation_res = stack_pop(&cpu -> stack);

                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    break;
                case 4 :
                    operation_res = stack_add(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Stack have only one element! In program memory position %d\n", i);
                        }
                    break;
                case 5 :
                    operation_res = stack_sub(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Stack have only one element! In program memory position %d\n", i);
                        }
                    break;
                case 6 :
                    operation_res = stack_mul(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Stack have only one element! In program memory position %d\n", i);
                        }
                    break;
                case 7 :
                    operation_res = stack_div(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Stack have only one element! In program memory position %d\n", i);
                        }
                        else
                            if (operation_res == 3)
                            {
                                cpu_empty_stack_interrupt (curr_pos);
                                return curr_pos;
                                //printf ("Error! Division by zero! In program memory position %d\n", i);
                            }

                    break;
                case 8 :
                    operation_res = stack_pow(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Stack have only one element! In program memory position %d\n", i);
                        }

                    break;
                case 9 :
                    operation_res = stack_sin(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }

                    break;
                case 10 :
                    operation_res = stack_cos(&cpu -> stack);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    break;
                case 11 :
                    operation_res = stack_sqrt(&cpu -> stack);
                    //printf ("d = %d\n", cpu -> dx);

                    if (operation_res == 1)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                        if (operation_res == 2)
                        {
                            cpu_empty_stack_interrupt (curr_pos);
                            return curr_pos;
                            //printf ("Error! Value is sub zero! In program memory position %d\n", i);
                        }
                    break;
                case 12 :
                    cpu_dump(cpu);
                    break;
                case 13 :
                    operation_res = stack_pop(&cpu -> stack);

                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                    }
                    else
                    {
                        cpu -> ax = operation_res;
                    }
                    break;
                case 14 :
                    operation_res = stack_pop(&cpu -> stack);

                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                    }
                    else
                    {
                        cpu -> bx = operation_res;
                    }
                    break;
                case 15 :
                    operation_res = stack_pop(&cpu -> stack);

                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                    }
                    else
                    {
                        cpu -> cx = operation_res;
                    }
                    break;
                case 16 :
                    operation_res = stack_pop(&cpu -> stack);

                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                    }
                    else
                    {
                        cpu -> dx = operation_res;
                    }
                    break;
                case 17 :
                    value = cpu -> bx;

                    operation_res = stack_push (&cpu -> stack, value);

                    if (operation_res)
                    {
                        cpu_full_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack is full! You can not push values! In program memory position %d\n", i);
                    }
                    break;
                case 18 :
                    value = cpu -> cx;

                    operation_res = stack_push (&cpu -> stack, value);

                    if (operation_res)
                    {
                        cpu_full_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack is full! You can not push values! In program memory position %d\n", i);
                    }
                    break;
                case 19 :
                    value = cpu -> dx;

                    operation_res = stack_push (&cpu -> stack, value);

                    if (operation_res)
                    {
                        cpu_full_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack is full! You can not push values! In program memory position %d\n", i);
                    }
                    break;
                case 20 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 >= value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                case 21 :
                    curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    break;
                case 22 :
                    curr_pos = prog_mem_size;
                    break;
                case 23 :
                    operation_res = stack_pop (&cpu -> stack);
                    if (operation_res == 2147483647)
                    {
                        cpu_empty_stack_interrupt (curr_pos);
                        return curr_pos;
                        //printf ("Error! Stack have not elements! In program memory position %d\n", i);
                    }
                    else
                    {
                        printf ("%d\n", operation_res);
                    }
                    break;
                case 24 :
                    stack_push (&cpu -> func_stack, curr_pos + 1);
                    curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    break;
                case 25 :
                    curr_pos = stack_pop (&cpu -> func_stack);
                    break;
                case 26 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 <= value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                case 27 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 < value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                case 28 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 > value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                case 29 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 == value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                case 30 :
                    value1 = stack_pop (&cpu -> stack);
                    value2 = stack_pop (&cpu -> stack);
                    if (value1 != value2)
                        curr_pos = cpu -> prog_mem[curr_pos + 1] - 1;
                    else
                        curr_pos++;
                    break;
                default :
                    return curr_pos;
                    //printf ("Error in the program memory! In program memory position %d\n", i);
                    break;
            }

    }
    return 0;
}


//----------------------- Function: cpu_dbz_interrupt -----------------------------------------------------------------------------

void cpu_dbz_interrupt (int position)
{
    printf ("There is division by zero. Position in program memory - %d", position);
}


//----------------------- Function: full_stack_interrupt --------------------------------------------------------------------------

void cpu_full_stack_interrupt (int position)
{
    printf ("There is stack overflow. Position in program memory - %d", position);
}


//----------------------- Function: full_stack_interrupt --------------------------------------------------------------------------

void cpu_empty_stack_interrupt (int position)
{
    printf ("There is push from empty stack. Position in program memory - %d", position);
}

//----------------------- End of file ---------------------------------------------------------------------------------------------

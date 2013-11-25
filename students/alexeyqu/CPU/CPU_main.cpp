/** ***************************************************************************
 * @file    CPU_main.cpp
 * @mainpage
 * @date    2013-11-8
 * @author  Alexey Kulikov <alexeyqu@gmail.com>, group 376, DCAM MIPT
 * @version 1.14
 *
 * CPU emulator.
 *
 * @par     Commands summary (V1.14):
 *          : {value}       - sets label {value}\n
 *          PROC : {name}   - sets pointer to function {name}\n
 *          PUSH {value\reg}- pushes value\reg to stack\n
 *          POP (reg)       - pops value out of stack (or to reg)\n
 *          IN              - gets value from the input stream and pushes it into stack\n
 *          OUT             - prints popped value on screen\n
 *          DUP             - duplicates top value of stack\n\n
 *
 *          ADD             - pushes sum of 2 popped elements\n
 *          SUB             - pushes difference of 2 popped elements\n
 *          MUL             - pushes product of 2 popped elements\n
 *          DIV             - pushes quotient of 2 popped elements\n
 *          POW             - pushes power function of 2 popped elements\n
 *          SIN             - pushes sin of last element instead of it\n
 *          COS             - pushes cos of last element instead of it\n
 *          SQRT            - pushes sqrt of last element instead of it\n\n
 *
 *          AND             - logical and\n
 *          OR              - logical or\n
 *          NOT             - logical not\n\n
 *
 *          EQU             - ==\n
 *          LT              - <\n
 *          GT              - >\n\n
 *
 *          JMP :{value}    - jumps on {value} label\n
 *          JE :{value}     - jumps on {value} label if pop = pop\n
 *          JNE :{value}    - jumps on {value} label if pop != pop\n
 *          JA :{value}     - jumps on {value} label if pop > pop\n
 *          JAE :{value}    - jumps on {value} label if pop >= pop\n
 *          JB :{value}     - jumps on {value} label if pop < pop\n
 *          JBE :{value}    - jumps on {value} label if pop <= pop\n\n
 *
 *          CALL :{name}    - calls {name} function\n
 *          RET             - returns from current function\n\n
 *
 *          SPC             - prints ' '\n
 *          TAB             - prints '\t'\n
 *          EOL             - prints '\n'\n\n
 *
 *          DUMP            - prints full dump info on CPU\n
 *          MSG "text"      - printf text\n\n
 *
 *          // {text}       - comment\n\n
 *
 *          END             - ends the program\n
 *
 * @par     V1.00
 *          - Realised CPU emulator with 4 registres and dynamically growing stack
 *          - Added basic 23 commands
 *
 * @par     V1.01
 *          - PUSH commands combined into one +args on asm stage
 *          - added asm and disasm
 *
 * @par     V1.1
 *          - added labels (based in asm)
 *          - added some outprint-format options (e.g. SPC, TAB)
 *
 * @par     V1.11
 *          - added functions and call stack
 *
 * @par     V1.12
 *          - primitive logic added
 *
 * @par     V1.13
 *          - string identifiers added (e.g. PROC :count_apples_newton_mode)
 *          - added MSG and comments to asm syntax
 *
 * @par     V1.14
 *          - started integration with error_catcher
 *
 * @todo
 *          - add some more simple commands (e.g. INC, DEC etc)
 *          - use hash to manipulate Proc identifiers
 *          - add RAM to cpu
 *          - try the dark side of the force .. a bit (c)
 *          - set up log prints and error watches
 *          - update disasm
 *          - improve logical operations
******************************************************************************/

#include "CPU.h"

int main()
{
    FILE* in_structions = fopen ("instructions.txt", "r");
    FILE* code          = fopen ("code.txt", "w+");
    FILE* log           = fopen ("log.txt", "w");

    assert (in_structions); assert (code); assert (log);

    fseek (in_structions, 0, 0);
    fseek (code, 0, 0);
    fseek (log, 0, 0);

    DBG_OUT fprintf (log, "CPU log file.\n");
    DBG_OUT fprintf (log, "%s %lg\n\n", SIGNATURE, VERSION);

    CPU_Error_Catch (Assembler (in_structions, code, log), "");
    CPU_Error_Catch (Assembler (in_structions, code, log), "");

    CPU_t cpu = {};

    CPU_Construct (&cpu);

    CPU_Error_Catch (CPU_Load_Data (&cpu, code), "");

    CPU_Error_Catch (CPU_Run (&cpu), "");

    CPU_Destruct (&cpu);

    fclose (in_structions);
    fclose (code);
    fclose (log);

    return 0;
}

/** ***************************************************************************
 * @file    Asm.h
******************************************************************************/

const unsigned int NUM_OF_LABELS = 10;
const unsigned int NUM_OF_PROC = 10;
const unsigned int PROC_IDENTIFIER_MAX_LEN = 50;

typedef struct ProcPointer
{
    char identifier[PROC_IDENTIFIER_MAX_LEN];
    unsigned int ip;
} ProcPointer_t;

/** ***************************************************************************
 * RET_ASM
 *
 * @brief list of return codes
******************************************************************************/
enum RET_ASM //FIXME expand
{
    ASM_ERR = -1,
    ASM_OK = 0,
    ASM_ERR_WRONG_ARG = 2,
    ASM_ERR_EOF = 3,
    ASM_ERR_SYNTAX = 4,
    ASM_ERR_RANGE = 5,
    ASM_ERR_REDEF = 6,
    ASM_REG_WRONG = 7
};

/** ***************************************************************************
 * Assembler
 *
 * @brief it assemblies instructions into a machine code
 *
 * @arg in_structions   input file descriptor
 * @arg out_code        output file descriptor
 *
 * @see Verify_Signature @see Disassembler
 *
 * @retval RET_ASM
******************************************************************************/
int Assembler (FILE* in_structions, FILE* out_code, FILE* log);

/** ***************************************************************************
 * Disasm
 *
 * @brief it disassemblies code into readable instructions
 *
 * @arg in_structions   input file descriptor
 * @arg out_code        output file descriptor
 *
 * @see Verify_Signature @see Assembler
 *
 * @retval RET_ASM
******************************************************************************/
int Disasm (FILE* in_code, FILE* out_structions);

int Reg_Ident (char reg[]);

int Add_Proc(); //FIXIT

/** ***************************************************************************
 * @file    asm.h
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "commands.h"

#define DEBUG 1

#ifdef DEBUG
    #define LOG(msg) fprintf (log, "%s", #msg);
    #define OUT printf ("# "),
#else
    #define LOG(msg)
    #define OUT if (0)
#endif

static const char   SIGNATURE [3]    = "AQ";
static const double ASM_VERSION     = 1.0;
const unsigned int MAXIMUM_CMD_LENGTH = 15;

/** ***************************************************************************
 * RET_ASM
 *
 * @brief list of return codes
******************************************************************************/
enum RET_ASM
{
    ASM_ERROR = -1,
    ASM_END = 0,
    ASM_OK = 1,
    SIGN_OK = 10,
    SIGN_WRONG = 11
};

/** ***************************************************************************
 * Verify_Signature
 *
 * @brief it verifies if the signature of file is correct
 *
 * @arg asm_file    file to check signature descriptor
 *
 * @retval SIGN_OK or SIGN_WRONG
******************************************************************************/
int Verify_Signature (FILE* asm_file);


/** ***************************************************************************
 * Assembler
 *
 * @brief it assemblies instructions into a machine code
 *
 * @arg in_structions   input file descriptor
 * @arg out_code        output file descriptor
 * @arg log             log file descriptor
 *
 * @see Verify_Signature @see Diassembler
 *
 * @retval RET_ASM
******************************************************************************/
int Assembler (FILE* in_structions, FILE* out_code, FILE* log);

/** ***************************************************************************
 * Assembler
 *
 * @brief it disassemblies code into readable instructions
 *
 * @arg in_structions   input file descriptor
 * @arg out_code        output file descriptor
 * @arg log             log file descriptor
 *
 * @see Verify_Signature @see Assembler
 *
 * @retval RET_ASM
******************************************************************************/
int Disasm (FILE* in_code, FILE* out_structions, FILE* log);

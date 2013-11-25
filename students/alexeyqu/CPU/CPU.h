/** ***************************************************************************
 * @file      CPU.h
******************************************************************************/

#ifndef CPULIB
    #define CPULIB

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "Stack.h"
#include "Asm.h"
#include "Commands.h"

#define _EJC
#define DEBUG 1

#ifndef DEBUG
    #error DEBUG should be defined as 0 or 1.
#endif

#ifdef _EJC
    #define OUT
#else
    #define OUT if (0)
#endif

#if (DEBUG == 1)
    #define DBG_OUT
    #define ASSERT( cond )\
        if (!cond)\
        {\
            fprintf (log, "Assertion [%s] failed in %s file %s line\n"\
                          "Aborting..\n",\
                     cond, __FILE__, __LINE__);\
            abort();\
        }
#else
    #define DBG_OUT if (0)
    #define ASSERT( cond )
#endif

#define CPU_CHECK( cpu )\
    if (CPU_Error_Catch (CPU_Is_OK (cpu), "") == CPU_ERR)\
    {\
        exit (1);\
    }

const int Poison = (int) 0xDEAD;
const unsigned int MAXIMUM_CODE_LENGTH = 1000;
const unsigned int MAXIMUM_CMD_LENGTH = 15;
const char   SIGNATURE [3]    = "AQ";
const double VERSION = 1.13;

typedef struct CPU
{
    Stack_t stack;
    Stack_t call_stack;
    double ax, bx, cx, dx, tx;
    double code[MAXIMUM_CODE_LENGTH];
    unsigned int code_len;
} CPU_t;

enum CPU_ERR
{
    CPU_ERR = -1,
    CPU_OK = 0,
    CPU_SIGN_OK = 0,
    CPU_ERR_SIGN_WRONG = 1,
    CPU_ERR_WR_STACK = 2,
    CPU_ERR_NULL = 3,
    CPU_ERR_WR_IP = 4,
    CPU_ERR_LOAD_ERROR = 5,
    CPU_LOAD_OK = 6,
};

int CPU_Construct (CPU_t* cpu);

int CPU_Destruct (CPU_t* cpu);

int CPU_Is_OK (const CPU_t* cpu);

/** ***************************************************************************
 * CPU_DUMP
 *
 * @brief       it prints dump info for CPU
 *
 * @param[out]  cpu pointer to CPU
 *
 * @see Stack_Dump
******************************************************************************/
void CPU_Dump (const CPU_t* cpu);

/** ***************************************************************************
 * CPU_Load_Data
 *
 * @brief   it stores commands from file inside array in CPU
 *
 * @arg     cpu     pointer to CPU
 * @arg     in_file file descriptor
 *
 * @see Assembler @see Verify_Signature
 *
 * @retval  0/1 !FIXME!
******************************************************************************/
int CPU_Load_Data (CPU_t* cpu, FILE* in_file);

/** ***************************************************************************
 * CPU_Run
 *
 * @brief   Main part of CPU - it processes commands
 *
 * @arg     cpu     pointer to CPU
 *
 * @retval  0/1 !FIXME!
******************************************************************************/
int CPU_Run (CPU_t* cpu);

/** ***************************************************************************
 * Verify_Signature
 *
 * @brief   it verifies if the signature of file is correct
 *
 * @arg     file    file to check signature descriptor
 *
 * @retval  SIGN_OK or SIGN_WRONG
******************************************************************************/
int Verify_Signature (FILE* file);

/** ***************************************************************************
 * CPU_Error_Catch    reacts on errors that occured
 *
 * @param   err_code    error code
 * @param   msg         message to print
 * @param   additional data
******************************************************************************/
int CPU_Error_Catch (int err_code, const char* msg, ...);

#endif

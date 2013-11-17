//!{====================================================================================
//! @file asm2.c
//! @date    2013-11-15 13:33
//! @author Andrianov Georgiy <egor.andrianov81@gmail.com>
//!
//! Interpritation of string commands fron file, to number of commands to other file
//!
//! @par File with string commands
//!      Programm put number of commands to other file
//!}====================================================================================


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_comands.h"
#include <string.h>

#define CODE_SIZE 150
#define POINTERS_SIZE 50

#define CHECK_CMD_(name) \
        if ( stricmp ( cmd, #name ) == 0 ){\
            code[position] = CMD_##name; position++;}\
            else

#define CHECK_CMD_PAR_(name)\
    if ( stricmp ( cmd, #name ) == 0 )\
    {\
        code[position] = CMD_##name; \
        position++;\
        char c = 0;\
        int j = 0;\
        while ( ( c = getc ( fcmd ) ) != ' ' && c != '\n')\
        {   \
            if ( c != ':' )\
            {\
            cmd[j] = c;\
            j++;\
            }\
        }\
        cmd[j] = '\0';\
        code[position] = strtof ( cmd, NULL); \
        position++;\
    }     \
    else

int getcmdfile ( char* cmd, FILE* fcmd );
int interpretingcmds ( FILE* fcmd, FILE* fcode );
int rewrittingcmd ( char* cmd, FILE* fcmd, float* code, int* pointers, int position );

int main()
{
    FILE * fcmd = fopen ( "comands.txt", "r" );
    FILE * fcode = fopen ( "code.txt", "wb" );
    interpretingcmds ( fcmd, fcode );
    fclose ( fcmd  );
    fclose ( fcode );
    return 0;
}

//!{============================================================================
//! interpretingcmds - Function calls functions getcmdfile and rewrittingcmd until
//!                    it finds command "end" and then change number of pointer in commands
//!                    on number of string with command
//!
//! @param      fcmd    File with string commands
//! @param      fcode   File with number of commands
//!
//! @return         0
//!}============================================================================

int interpretingcmds ( FILE* fcmd, FILE* fcode )
{
    assert ( fcmd  );
    assert ( fcode );
    char cmd[40] = {};
    float code[CODE_SIZE] = {};
    int pointers[POINTERS_SIZE] = {};
    int position = 0;
    while ( stricmp ( cmd, "end") != 0 )
    {
        getcmdfile ( cmd, fcmd );
        position = rewrittingcmd ( cmd, fcmd, code, pointers, position );
    }
    int i = 0;
    int p = 0;
    while ( i < position )
    {
        if ( code[i] == CMD_PUSH )
        {
            i = i + 2;
        }
        else if ( (code[i] >= CMD_JMP && code[i] <= CMD_JBE) || code[i] == CMD_CALL )
            {
                i++;
                code[i] = (float) pointers[(int) code[i]];
            }
            else
            {
                i++;
            }
    }
    fwrite ( code, sizeof ( float ), (position), fcode);
    return 0;
}

//!{============================================================================
//! getcmdfile - function get one command or one number from file
//!
//! @param      fcmd   file with commands
//! @param[out] cmd    array of char, where read command will lay
//!
//! @return         0
//!}============================================================================

int getcmdfile ( char* cmd, FILE* fcmd )
{
    assert ( cmd );
    assert ( fcmd );
    int i = 0;
    char c;
    while ( ( c = getc ( fcmd ) ) != ' ' && c != '\n' && c != EOF)
    {
        cmd[i] = c;
        i++;
    }
    cmd[i] = '\0';
    return 0;
}

//!{============================================================================
//! rewrittingcmd - function takes string command and writes its number and parameter
//!                 if it exist to code array
//!
//! @param      cmd        String command
//! @param      fcmd       File with string commands
//! @param      fcode      File with number of commands
//! @param      pointers   Array where pointers on command lay
//! @param      position   Position where the last read command stand
//!
//! @return                Position of the last read command
//!}============================================================================

int rewrittingcmd ( char* cmd, FILE* fcmd, float* code, int* pointers, int position )
{
    assert ( cmd );
    assert ( fcmd );
    CHECK_CMD_( POP )
    CHECK_CMD_( ADD )
    CHECK_CMD_( SUB )
    CHECK_CMD_( DIV )
    CHECK_CMD_( MUL )
    CHECK_CMD_( SIN )
    CHECK_CMD_( COS )
    CHECK_CMD_( TAN )
    CHECK_CMD_( END )
    CHECK_CMD_( SQRT )
    CHECK_CMD_( PUSH_AX )
    CHECK_CMD_( POP_AX )
    CHECK_CMD_( PUSH_BX )
    CHECK_CMD_( POP_BX )
    CHECK_CMD_( PUSH_CX )
    CHECK_CMD_( POP_CX )
    CHECK_CMD_( OUT )
    CHECK_CMD_( IN )
    CHECK_CMD_( RET )
    CHECK_CMD_PAR_( JMP )
    CHECK_CMD_PAR_( JE )
    CHECK_CMD_PAR_( JNE )
    CHECK_CMD_PAR_( JB )
    CHECK_CMD_PAR_( JBE )
    CHECK_CMD_PAR_( JA )
    CHECK_CMD_PAR_( JAE )
    CHECK_CMD_PAR_( PUSH )
    CHECK_CMD_PAR_( CALL )
    if ( cmd[0] = ':' )
    {
        int i = 0;
        cmd = cmd + 1;
        pointers[ atoi ( cmd ) ] = position ;
    }
    return position;
}

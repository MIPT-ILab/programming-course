/** ***************************************************************************
 * @file    Commands.h
******************************************************************************/
//Надо бы: Doxylevelup, error tracking, log prints, ifndefы, filename scan
enum CMD
{
    CMD_PUSH    = 1101,
    CMD_POP     = 1102,
    CMD_IN      = 1103,
    CMD_OUT     = 1104,
    CMD_DUP     = 1105,

    CMD_BASE    = 1200,
    CMD_PUSH_AX = 1210,
    CMD_POP_AX  = 1220,
    CMD_PUSH_BX = 1211,
    CMD_POP_BX  = 1221,
    CMD_PUSH_CX = 1212,
    CMD_POP_CX  = 1222,
    CMD_PUSH_DX = 1213,
    CMD_POP_DX  = 1223,

    CMD_MOV     = 1251, //FIXIT

    CMD_ADD     = 1301,
    CMD_SUB     = 1302,
    CMD_MUL     = 1303,
    CMD_DIV     = 1304,
    CMD_POW     = 1311,
    CMD_SIN     = 1312,
    CMD_COS     = 1313,
    CMD_SQRT    = 1314,

    CMD_AND     = 1401,
    CMD_OR      = 1402,
    CMD_NOT     = 1403,
    CMD_EQU     = 1411,
    CMD_LT      = 1412,
    CMD_GT      = 1413,

    CMD_JMP     = 1501,
    CMD_JE      = 1502,
    CMD_JNE     = 1503,
    CMD_JA      = 1504,
    CMD_JAE     = 1505,
    CMD_JB      = 1506,
    CMD_JBE     = 1507,

    CMD_CALL    = 1601,
    CMD_PROC    = 1602,
    CMD_RET     = 1603,

    CMD_SPC     = 1801,
    CMD_TAB     = 1802,
    CMD_EOL     = 1803,

    CMD_DUMP    = 1901,
    CMD_MSG     = 1902,
    CMD_ERROR   = 1999,

    CMD_BEGIN   = 1000,
    CMD_END     = 9999
};

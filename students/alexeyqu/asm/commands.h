/** ***************************************************************************
 * @file    commands.h
******************************************************************************/

enum CMD
{
    CMD_PUSH    = 1101,
    CMD_POP     = 1102,
    CMD_IN      = 1103,
    CMD_OUT     = 1104,
    CMD_DUP     = 1105,

    CMD_PUSH_AX = 1201,
    CMD_POP_AX  = 1202,
    CMD_PUSH_BX = 1211,
    CMD_POP_BX  = 1212,
    CMD_PUSH_CX = 1221,
    CMD_POP_CX  = 1222,
    CMD_PUSH_DX = 1231,
    CMD_POP_DX  = 1232,

    CMD_ADD     = 1301,
    CMD_SUB     = 1302,
    CMD_MUL     = 1303,
    CMD_DIV     = 1304,
    CMD_POW     = 1311,
    CMD_SIN     = 1312,
    CMD_COS     = 1313,
    CMD_SQRT    = 1314,

    CMD_DUMP    = 1901,
    CMD_ERROR   = 1999,

    CMD_END     = 0
};

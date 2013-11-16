//{==================================================================================================
//! @file "cpu_consts.h"
//! @date 2013-11-09
//! @mainpage CPU internal command names/consts table
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#define SHCHERBATOV_KIRILL_PROGRAM_SIGNATURE -666
#define CPU_MEMORY_SIZE 512
#define CPU_STACK_SIZE 64
#define CPU_CALL_STACK_SIZE 32
//----------------------------------------------------------------------------------------------------
#define OUT_DEVICE stdout
#define IN_DEVICE stdin
//****************************************************************************************************

enum CPU_REGISTERS_NAMES
{
	AX = 0,
	BX = 1,
	CX = 2,
	DX = 3
};

enum CPU_INSTRUCTIONS_NAMES
{
	CPU_CMD_HALT = 1000,  //end
	CPU_CMD_PUSH_STACK = 1001, // push 12
	CPU_CMD_PUSH_REGISTER = 1002, // mov ax 12
	CPU_CMD_PUSH_REGISTER_FROM_STACK = 1003, //pop ax
	CPU_CMD_PUSH_REGISTER_TO_STACK = 1004, //push ax
	CPU_CMD_OUT_VALUE_FROM_STACK = 1005, //out
	CPU_CMD_OUT_TEXT = 1006, //out 0
	CPU_CMD_DUB = 1007, //dub
	CPU_CMD_SUM = 1008,
	CPU_CMD_SUB = 1009,
	CPU_CMD_MUL = 1010,
	CPU_CMD_DIV = 1011,
	CPU_CMD_SIN = 1012,
	CPU_CMD_COS = 1013,
	CPU_CMD_TAN = 1014,
	CPU_CMD_ASIN = 1015,
	CPU_CMD_ACOS = 1016,
	CPU_CMD_ATAN = 1017,
	CPU_CMD_LOG = 1018,
	CPU_CMD_JMP = 1019,//jmp 1
	CPU_CMD_JE = 1020, //je 1
	CPU_CMD_JNE = 1021,
	CPU_CMD_JA = 1022,
	CPU_CMD_JAE = 1023,
	CPU_CMD_JB = 1024,
	CPU_CMD_JBE = 1025,
	CPU_CMD_SQRT = 1026,
	CPU_CMD_IN = 1027,
	CPU_CMD_CALL = 1028, //call
	CPU_CMD_RET = 1029 //ret
};


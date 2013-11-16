const double ZERO =  0.0000001;
const int POiSON  =  228;
const int HAPPY   =  777;
const int SAD     = -777;
const int COMMANDS_SIZE = 200;
const int LABELS_SIZE = 20;
const int MAX_LINE = 10;

enum COMMAND
{
    CMD_END     =  999,
    CMD_PUSH    =  1001,
	CMD_PUSH_RX =  1002,
    CMD_DUP     =  1003,
    CMD_POP     =  1004,
	CMD_MOV		=  1005,
	CMD_MOV_RX  =  1006,

    CMD_ADD     =  1101,
    CMD_SUB     =  1102,
    CMD_MUL     =  1103,
    CMD_DIV     =  1104,
    CMD_SQR     =  1201,
    CMD_SQRT    =  1202,
    CMD_POW     =  1203,
    CMD_SIN     =  1301,
    CMD_COS     =  1302,
    CMD_TAN     =  1303,
    CMD_CTAN    =  1304,

	CMD_DUMP	=  1901,
	CMD_IN		=  1911,
	CMD_IN_RX	=  1912,
    CMD_OUT		=  1913,
	CMD_OUT_RX  =  1914,

	CMD_JMP		=  2000,
	CMD_JB		=  2001,
	CMD_JBE		=  2002,
	CMD_JE		=  2003,
	CMD_JAE		=  2004,
	CMD_JA		=  2005,
	CMD_JUE		=  2006,
	CMD_CALL	=  2100,
	CMD_FUNC	=  2101,
	CMD_RET		=  2102,
};

enum REGISTER
{
    AX = 801,
    BX = 802,
    CX = 803,
    DX = 804,
};



enum ERROR
{
    ERR_ADD = -1004,
    ERR_SUB = -1005,
    ERR_MUL = -1006,
    ERR_DIV = -1007,
    ERR_DIV_ZERO = -1008,
    ERR_SQR = -1009,
    ERR_SQRT_NEG = -1010,
    ERR_SIN = -1011,
    ERR_COS = -1012,
    ERR_TAN = -1013,
    ERR_TAN_INF = -1014,
    ERR_CTAN = -1015,
    ERR_CTAN_INF = -1016,
    ERR_SQRT = -1017,
    ERR_POW = -1018,
    ERR_CPU_PUSH = -1019,
    ERR_STACK_POP = -1020,
    ERR_STACK_FAIL = -1021,
    ERR_CPU_FAIL = -1022,
    ERR_STACK_PUSH = -1023,
    ERR_DUP = -1024,
    ERR_POW_ZEROES = -1025,
	ERR_CPU_POP = -1026,
};
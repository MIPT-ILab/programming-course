#define _CRT_SECURE_NO_WARNINGS

#define DEBUG

#ifdef DEBUG

    #define ASSERT(cond)																				 \
    if (!(cond))																						 \
    {																									 \
        /*fprintf (the_log, "The state is wrong: %s, file: %s, line: %d\n", #cond, __FILE__, __LINE__); */ \
        abort();																						 \
    }																									 \

    #define ASSERT_CPU_OK( test_cpu )   if (! Cpu_OK (test_cpu)) return ERR_CPU_FAIL;

    #define ASSERT_STACK_OK( test_stack )   if (! Stack_OK (test_stack)) return ERR_STACK_FAIL;

#else

    #define ASSERT(cond)
    #define ASSERT_CPU_OK
    #define ASSERT_STACK_OK

#endif //DEBUG


//#define _EJC

#ifdef  _EJC
    #define OUT if (0)
    #define PRINT_INFO

#else
    #define OUT
#endif // _EJC

#define CHECK_INPUT_REG( str, REG )						\
    else if (strcmp (strupr (str), #REG) == 0)			\
			input = REG									\

#define DEF_INPUT_REG( str )               \
    if (0) printf ("Magic");		   	   \
    CHECK_INPUT_REG (str, AX);             \
    CHECK_INPUT_REG (str, BX);             \
    CHECK_INPUT_REG (str, CX);             \
    CHECK_INPUT_REG (str, DX);             \


/*#define CASE_REG_MOV( REG )
	case REG:*/


#define CHOOSE_REG_MOV

#define CASE_REG_OUT(REG, reg)								\
	case REG:												\
		fprintf (output, "%lg", my_cpu -> reg);		     	\
		break;												\
	
#define CHOOSE_REG_OUT						\
	CASE_REG_OUT(AX, ax);					\
	CASE_REG_OUT(BX, bx);					\
	CASE_REG_OUT(CX, cx);					\
	CASE_REG_OUT(DX, dx);					\

#define CASE_ERR( err )                                         \
    case ERR_##err:                                             \
        printf ("\n" "There is an error: ERR_%s\n", #err);      \
        abort ();                                               \
        break;                                                  \

#define CHOOSE_ERR           \
    CASE_ERR (ADD);          \
    CASE_ERR (SUB);          \
    CASE_ERR (MUL);          \
    CASE_ERR (DIV);          \
    CASE_ERR (SQR);          \
    CASE_ERR (SQRT);         \
    CASE_ERR (POW);          \
    CASE_ERR (SIN);          \
    CASE_ERR (COS);          \
    CASE_ERR (TAN);          \
    CASE_ERR (CTAN);         \
    CASE_ERR (DUP);          \
                             \
    CASE_ERR (DIV_ZERO);     \
    CASE_ERR (SQRT_NEG);     \
    CASE_ERR (TAN_INF);      \
    CASE_ERR (CTAN_INF);     \
    CASE_ERR (CPU_PUSH);     \
    CASE_ERR (STACK_POP);    \
    CASE_ERR (STACK_FAIL);   \
    CASE_ERR (STACK_PUSH);   \
    CASE_ERR (CPU_FAIL);     \
	CASE_ERR (CPU_POP);		 \


#define CHECK_CMD( str_command, cmd )						\
    else if (strcmp (strupr (str_command), #cmd) == 0)      \
        command = CMD_##cmd									\

#define DEF_CMD( cmd )					\
    if (0) printf ("Magic");		    \
	CHECK_CMD (cmd, END);				\
    CHECK_CMD (cmd, PUSH);				\
    CHECK_CMD (cmd, DUP);				\
    CHECK_CMD (cmd, POP);				\
	CHECK_CMD (cmd, MOV);				\
    CHECK_CMD (cmd, ADD);				\
    CHECK_CMD (cmd, SUB);				\
    CHECK_CMD (cmd, MUL);				\
    CHECK_CMD (cmd, DIV);				\
    CHECK_CMD (cmd, SQR);				\
    CHECK_CMD (cmd, SQRT);				\
    CHECK_CMD (cmd, POW);				\
    CHECK_CMD (cmd, SIN);				\
    CHECK_CMD (cmd, COS);				\
    CHECK_CMD (cmd, TAN);				\
    CHECK_CMD (cmd, CTAN);				\
	CHECK_CMD (cmd, DUMP);				\
	CHECK_CMD (cmd, IN);				\
	CHECK_CMD (cmd, OUT);				\
	CHECK_CMD (cmd, JMP);				\
	CHECK_CMD (cmd, JB);				\
	CHECK_CMD (cmd, JBE);				\
	CHECK_CMD (cmd, JE);				\
	CHECK_CMD (cmd, JAE);				\
	CHECK_CMD (cmd, JA);				\
	CHECK_CMD (cmd, JUE);				\
	CHECK_CMD (cmd, CALL);				\
	CHECK_CMD (cmd, FUNC);				\
	CHECK_CMD (cmd, RET);				\


#define CASE_CMD_ASM( CMD )						\
	case CMD_##CMD:								\
		add_code (codes, &cur_code, command);	\
		break;									\

#define CHOOSE_CMD_ASM							\
	CASE_CMD_ASM (ADD)							\
	CASE_CMD_ASM (SUB)							\
	CASE_CMD_ASM (MUL)							\
	CASE_CMD_ASM (DIV)							\
	CASE_CMD_ASM (SQR)							\
	CASE_CMD_ASM (SQRT)							\
	CASE_CMD_ASM (POW)							\
	CASE_CMD_ASM (SIN)							\
	CASE_CMD_ASM (COS)							\
	CASE_CMD_ASM (TAN)							\
	CASE_CMD_ASM (CTAN)							\
	CASE_CMD_ASM (DUMP)							\
	CASE_CMD_ASM (RET)							\
	CASE_CMD_ASM (DUP)							\

#define CASE_REG_ASM( REG )									\
	case REG:												\
		add_code (codes, &cur_code, REG);					\
		break												\

#define CHOOSE_REG_ASM			\
	CASE_REG_ASM (AX);			\
	CASE_REG_ASM (BX);			\
	CASE_REG_ASM (CX);			\
	CASE_REG_ASM (DX);			\

#define CASE_REG_MOV( REG, a, b )			\
	case REG:								\
		a = b;								\
		break								\

#define CASE_LABEL( LABEL )									\
	case CMD_##LABEL:										\
		add_code (codes, &cur_code, command);				\
		fscanf (my_program, "%s", str_label);				\
		sscanf (&(str_label[1]),"%d", &label);				\
		add_code (codes, &cur_code, labels[label]);			\
		break
		
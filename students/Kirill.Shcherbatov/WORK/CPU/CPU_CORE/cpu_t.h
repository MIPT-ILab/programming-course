//{==================================================================================================
//! @file "cpu_t.h"
//! @date 2013-11-09
//! @mainpage Virtual CPU main
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#include <math.h>
#include <stdlib.h>
//----------------------------------------------------------------------------------------------------
#include "../../stack_t.h"
#include "../../debug_defines.h"
//----------------------------------------------------------------------------------------------------
#include "../cpu_consts.h"
//****************************************************************************************************

struct cpu_t
{
    double ax, bx, cx, dx;
    struct stack_t *cpu_stack,
				   *cpu_call_stack;
    struct stack_t *cpu_memory;
};

struct cpu_t* cpu_constructor (void)
{
    OUT ("# called cpu_constructor\n");

    struct cpu_t *target_cpu = NULL;
    target_cpu = (cpu_t*) calloc (1, sizeof(cpu_t));
    RETURN_ASSERT (target_cpu != NULL, 0);

    target_cpu -> cpu_memory = NULL;
    target_cpu -> cpu_memory = stack_constructor (CPU_MEMORY_SIZE);
    RETURN_ASSERT (target_cpu -> cpu_memory != NULL, 0);

    target_cpu -> cpu_stack = NULL;
    target_cpu -> cpu_stack = stack_constructor (CPU_STACK_SIZE);
    RETURN_ASSERT (target_cpu -> cpu_stack != NULL, 0);

    target_cpu -> cpu_call_stack = NULL;
    target_cpu -> cpu_call_stack = stack_constructor (CPU_CALL_STACK_SIZE);
    RETURN_ASSERT (target_cpu -> cpu_call_stack != NULL, 0);

    target_cpu -> ax = 0.0;
    target_cpu -> bx = 0.0;
    target_cpu -> cx = 0.0;
    target_cpu -> dx = 0.0;

    return target_cpu;
}

short int cpu_destructor (struct cpu_t *target_cpu)
{
	OUT ("# called cpu_destructor\n");
    RETURN_ASSERT (target_cpu != NULL, -1);

    const short int POISON = -666;

    RETURN_ASSERT (stack_destructor (target_cpu -> cpu_memory) == 0, -1);
    RETURN_ASSERT (stack_destructor (target_cpu -> cpu_stack) == 0, -1);
	RETURN_ASSERT (stack_destructor (target_cpu -> cpu_call_stack) == 0, -1);

    target_cpu -> ax = POISON;
    target_cpu -> bx = POISON;
    target_cpu -> bx = POISON;
	target_cpu -> dx = POISON;

    free (target_cpu);
    target_cpu = NULL;

    return 0;
}


short int cpu_is_ok (const struct cpu_t *target_cpu)
{
	OUT ("# called cpu_is_ok\n");
	RETURN_ASSERT (target_cpu != NULL, -1);

    return (stack_is_ok (target_cpu -> cpu_memory)
            &&
            stack_is_ok (target_cpu -> cpu_stack)
            &&
            stack_is_ok (target_cpu -> cpu_call_stack)
            );
}

short int cpu_dump (const struct cpu_t *target_cpu)
{
	OUT ("# called cpu_dump\n");
	RETURN_ASSERT (target_cpu != NULL, -1);

    fprintf (OUT_DEVICE, "#> BEGIN CPU DUMP REPORT\n");
    fprintf (OUT_DEVICE, "#> Have register ax = %lg\n", target_cpu -> ax);
    fprintf (OUT_DEVICE, "#> Have register bx = %lg\n", target_cpu -> bx);
    fprintf (OUT_DEVICE, "#> Have register cx = %lg\n", target_cpu -> cx);
	fprintf (OUT_DEVICE, "#> Have register dx = %lg\n", target_cpu -> cx);

    fprintf (OUT_DEVICE, "#> Have stack\n");
    RETURN_ASSERT (stack_dump (target_cpu -> cpu_stack, OUT_DEVICE) == 0, -1);

	fprintf (OUT_DEVICE, "#> Have call stack\n");
    RETURN_ASSERT (stack_dump (target_cpu -> cpu_call_stack, OUT_DEVICE) == 0, -1);

    fprintf (OUT_DEVICE, "#> Have memory\n");
    RETURN_ASSERT (memory_dump (target_cpu -> cpu_memory, OUT_DEVICE) == 0, -1);

    fprintf (OUT_DEVICE, "#> END CPU DUMP REPORT\n");

    return 0;
}

short int cpu_load_program (struct cpu_t *target_cpu, FILE *source)
{
	OUT ("# called cpu_load_program\n");
	RETURN_ASSERT (target_cpu != NULL, -1);
	RETURN_ASSERT (cpu_is_ok (target_cpu) == 1, -1);
	RETURN_ASSERT (source != NULL, -1);

    double buffer = 0;

	RETURN_ASSERT (fscanf (source, "%lg", &buffer) == 1, -1); // signature
    RETURN_ASSERT (buffer == SHCHERBATOV_KIRILL_PROGRAM_SIGNATURE, -1);

	RETURN_ASSERT (fscanf (source, "%lg", &buffer) == 1, -1); // program size
    RETURN_ASSERT (buffer <= target_cpu -> cpu_memory -> max_size, -1);

    target_cpu -> cpu_memory -> cure_size = 0;

	for (register int i = 0; i < buffer; i++)
        RETURN_ASSERT (fscanf (source, "%lg", & target_cpu -> cpu_memory -> data[i]) == 1, -1);

    target_cpu -> cpu_memory -> cure_size = buffer;

    return 0;
}

short int cpu_in (struct cpu_t const *target_cpu, FILE *source)
{
	OUT ("# call cpu_in\n");
	RETURN_ASSERT (target_cpu != NULL, -1);
	RETURN_ASSERT (source != NULL, -1);

	double buffer = 0.0;
	RETURN_ASSERT (fscanf (source, "%lg", &buffer) == 1, -1);

	if (buffer == SHCHERBATOV_KIRILL_PROGRAM_SIGNATURE)
	{
        RETURN_ASSERT (cpu_dump (target_cpu) == 0, -1);
        return -1;
    }

	RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, buffer) == 0, -1);

	return 0;
}


short int cpu_push_value_in_stack (struct cpu_t const *target_cpu, const double *value)
{
	OUT ("# call cpu_push_value_in_stack\n");
	RETURN_ASSERT (target_cpu != NULL, -1);
	RETURN_ASSERT (value != NULL, -1);

    RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, *value) == 0, -1);

    return 0;
}

short int cpu_out_value_from_stack (struct cpu_t const *target_cpu, FILE *target_source)
{
	OUT ("# call cpu_out_value_from_stack\n");
    RETURN_ASSERT (target_cpu != NULL, -1);
    RETURN_ASSERT (target_source != NULL, -1);

    double buffer = 0.0;
    RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer) == 0, -1);
	fprintf (target_source, "%lg", buffer);

    return 0;
}


short int cpu_out_text (FILE *target_source, const char text_number)
{
	OUT ("# call cpu_out_text with param %d\n", text_number);
    RETURN_ASSERT ( target_source != NULL, -1);
    RETURN_ASSERT (text_number >= 0, -1);
    RETURN_ASSERT (text_number <= 2, -1);

    #define OUT_TEXT( number, text )                            \
    case number:                                                \
    {                                                           \
        fprintf (target_source, "%s", text);					\
        break;                                                  \
    }

    switch (text_number)
    {
        OUT_TEXT (0, "\n");
        OUT_TEXT (1, " ");
        OUT_TEXT (2, "\t");
    }
    #undef OUT_TEXT

    return 0;
}

short int cpu_push_register (struct cpu_t *target_cpu, const double register_number, const double *value)
{
	OUT ("# call cpu_push_register with register %d and param %lg\n", (char)register_number, *value);
    RETURN_ASSERT (target_cpu != NULL, -1);
    RETURN_ASSERT (value != NULL, -1);
    RETURN_ASSERT (register_number >= 0, -1);
    RETURN_ASSERT (register_number <= 3, -1);

    switch ((char)register_number)
    {
		#define PUSH_IN_REGISTER( register_name )												    			\
					{																							\
						target_cpu -> register_name = *value;                                                   \
						return 0;																				\
					}

		case 0:
			PUSH_IN_REGISTER ( ax );
		case 1:
			PUSH_IN_REGISTER ( bx );
		case 2:
		    PUSH_IN_REGISTER ( cx );
		case 3:
		    PUSH_IN_REGISTER ( dx );

		#undef PUSH_REGISTER

		default: return 1;
    }
}

short int cpu_push_register_to_stack (struct cpu_t const *target_cpu, const double register_number)
{
	OUT ("# call cpu_push_register_to_stack with register %d\n", (char)register_number);
    RETURN_ASSERT (target_cpu != NULL, -1);
    RETURN_ASSERT (register_number >= 0, -1);
    RETURN_ASSERT (register_number <= 3, -1);

    switch ((char)register_number)
    {

    #define PUSH_REGISTER( register_name )																	    \
                {																							    \
                    RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, target_cpu -> register_name) == 0, -1); \
                    return 0;																				    \
                }

    case 0:
        PUSH_REGISTER ( ax );
    case 1:
        PUSH_REGISTER ( bx );
    case 2:
        PUSH_REGISTER ( cx );
    case 3:
		PUSH_REGISTER ( dx );

    #undef PUSH_REGISTER

    default:  return -1;
    }
}

short int cpu_push_register_from_stack (struct cpu_t *target_cpu, const double register_number)
{
	OUT ("# call cpu_push_register_from_stack with register %d\n", (char)register_number);
    RETURN_ASSERT (target_cpu != NULL, -1);
    RETURN_ASSERT (register_number >= 0, -1);
    RETURN_ASSERT (register_number <= 3, -1);

    double buffer = 0.0;
    RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer) == 0, -1);

    switch ((char)register_number)
    {
    #define POP_REGISTER( register_name )																	\
                {																							\
                    target_cpu -> register_name = buffer;													\
                    return 0;																				\
                }

    case 0:
        POP_REGISTER ( ax );
    case 1:
        POP_REGISTER ( bx );
    case 2:
        POP_REGISTER ( cx );
    case 3:
        POP_REGISTER ( dx );

    #undef POP_REGISTER

    default: return -1;
    }
}

short int cpu_dub_stack_last_value (struct cpu_t const *target_cpu)
{
	OUT ("# call cpu_dub_stack_last_value\n");
    RETURN_ASSERT (target_cpu != NULL, -1);

    double buffer = 0.0;
    RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer) == 0, -1);
    RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, buffer) == 0, -1);
    RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, buffer) == 0, -1);

    return 0;
}

#define CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK( function_name, algebra_action );					\
	short int cpu_##function_name (struct cpu_t const *target_cpu)									    \
	{																									\
		OUT ("# call cpu_%s\n", #function_name);                                                        \
		RETURN_ASSERT (target_cpu != NULL, -1);    						    							\
		double 	buffer1 = 0.0,																			\
				buffer2 = 0.0;																			\
		RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer1) == 0, -1);						    \
		RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer2) == 0, -1);							\
		RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, buffer1 algebra_action buffer2) == 0, -1);	\
		                                                                                                \
		return 0;																						\
	}

CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK ( sum, + );
CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK ( sub, - );
CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK ( mul, * );
CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK ( div, / );

#undef CPU_MATH_ALGEBRA_FUNCTION_FROM_STACK_TO_STACK


#define CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK( function_name )								\
	short int cpu_##function_name (struct cpu_t  *target_cpu)											\
	{																									\
		OUT ("# call cpu_%s\n", #function_name);	                                                    \
		RETURN_ASSERT (target_cpu != NULL, -1);        													\
		double buffer = 0.0;																			\
		RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer) == 0, -1);							\
		RETURN_ASSERT (stack_push (target_cpu -> cpu_stack, function_name (buffer)) == 0, -1);			\
		return 0;																						\
	}

CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( sin 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( cos 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( tan 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( asin 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( acos 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( atan 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( log 	);
CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK ( sqrt 	);

#undef CPU_MATH_ONE_PARAM_FUNCTION_FROM_STACK_TO_STACK

short int cpu_run (struct cpu_t *target_cpu)
{
	OUT ("# call cpu_run\n");
	RETURN_ASSERT (target_cpu != NULL, -1);

    int ip = 0;
    while (ip  <  target_cpu -> cpu_memory -> cure_size)
    {
		OUT ("\n#"
			 "# NEW ITERATION: ADDR %d, INSTRUCTION %d\n", ip, (int)target_cpu -> cpu_memory -> data [ip]);
        switch ((int) target_cpu -> cpu_memory -> data [ip])
        {
			case CPU_CMD_HALT: return 0;
            case CPU_CMD_PUSH_REGISTER:
			{
				ip+=2;
				RETURN_ASSERT (cpu_push_register (target_cpu, target_cpu -> cpu_memory -> data[ip-1], &target_cpu -> cpu_memory -> data[ip]) == 0, -1);
				ip++;
				break;
			}

			#define CPU_JMP_INSTRUCTION 																    \
				OUT ("# call JMP %d new addr instruction %d\n",				    	    					\
					 (int)target_cpu -> cpu_memory -> data[ip+1],										    \
					 (int)target_cpu -> cpu_memory -> data[(int)target_cpu -> cpu_memory -> data[ip+1]]);	\
				ip = (int)target_cpu -> cpu_memory -> data[ip+1];										    \
				break;

			case CPU_CMD_JMP: { CPU_JMP_INSTRUCTION; }

            case CPU_CMD_CALL:
		    {
		        RETURN_ASSERT (stack_push (target_cpu -> cpu_call_stack, ip+2) == 0, -1);
		        CPU_JMP_INSTRUCTION;
		    }

		    case CPU_CMD_RET:
		    {
		        double buffer = 0.0;
		        RETURN_ASSERT (stack_pop (target_cpu -> cpu_call_stack, &buffer) == 0, -1);
		        ip = (int)buffer;
		        break;
		    }

			#define AUTO_IF_JMP_CASE(cmd_name, sign)													\
				case cmd_name:																			\
				{																						\
					OUT ("# call CMP %s\n", #sign);						    							\
					double buffer1 = 0.0,																\
							buffer2 = 0.0;																\
					RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer1) == 0, -1);				\
					RETURN_ASSERT (stack_pop (target_cpu -> cpu_stack, &buffer2) == 0, -1);				\
					if (buffer1 sign buffer2)															\
						{ 																				\
							CPU_JMP_INSTRUCTION;														\
						} else ip+=2;																	\
					break;                                                                      		\
				}

			AUTO_IF_JMP_CASE (CPU_CMD_JE, ==);
			AUTO_IF_JMP_CASE (CPU_CMD_JNE, !=);
			AUTO_IF_JMP_CASE (CPU_CMD_JA, >);
			AUTO_IF_JMP_CASE (CPU_CMD_JAE, >=);
			AUTO_IF_JMP_CASE (CPU_CMD_JB, <);
			AUTO_IF_JMP_CASE (CPU_CMD_JBE, <=);

			#undef AUTO_IF_JMP_CASE

			#undef CPU_JMP_INSTRUCTION

			#define AUTO_CPU_CASE(cmd_name, action)												\
				case cmd_name :																	\
				{																				\
					RETURN_ASSERT (action == 0, -1);											\
					ip++;																		\
					break;																		\
				}

			AUTO_CPU_CASE (CPU_CMD_OUT_VALUE_FROM_STACK,
								cpu_out_value_from_stack (target_cpu, OUT_DEVICE));

			AUTO_CPU_CASE (CPU_CMD_OUT_TEXT,
								cpu_out_text (OUT_DEVICE,
									target_cpu -> cpu_memory -> data[++ip]));


			AUTO_CPU_CASE (CPU_CMD_PUSH_STACK,
								cpu_push_value_in_stack (target_cpu,
									&target_cpu -> cpu_memory -> data[++ip]));

			AUTO_CPU_CASE (CPU_CMD_PUSH_REGISTER_FROM_STACK,
								cpu_push_register_from_stack (target_cpu,
									target_cpu -> cpu_memory -> data[++ip]));

			AUTO_CPU_CASE (CPU_CMD_PUSH_REGISTER_TO_STACK,
								cpu_push_register_to_stack (target_cpu,
									target_cpu -> cpu_memory -> data[++ip]));

			AUTO_CPU_CASE (CPU_CMD_DUB,
								cpu_dub_stack_last_value (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_SUM,
								cpu_sum (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_SUB,
								cpu_sub (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_MUL,
								cpu_mul (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_DIV,
								cpu_div (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_SIN,
								cpu_sin (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_COS,
								cpu_cos (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_TAN,
								cpu_tan (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_ASIN,
								cpu_asin (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_ACOS,
								cpu_acos (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_ATAN,
								cpu_atan (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_LOG,
								cpu_log (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_SQRT,
								cpu_sqrt (target_cpu));

			AUTO_CPU_CASE (CPU_CMD_IN,
								cpu_in (target_cpu, IN_DEVICE));

			#undef AUTO_CPU_CASE

            default: RETURN_ASSERT ("Undeclarated command.\n" == 0, -1);
        }

        RETURN_ASSERT (ip >= 0, -1);
        RETURN_ASSERT (ip  <  target_cpu -> cpu_memory -> cure_size, -1);
    }
    return 0;
}

#undef OUT
#undef RETURN_ASSERT

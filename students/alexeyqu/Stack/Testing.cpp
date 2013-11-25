/** ***************************************************************************
 * @file    Testing.cpp
******************************************************************************/

#include "Stack.h"

int Stack_Test()
{
    #define INTERVAL printf ("________________________________________________\n");

    #define LEGEND \
        printf ("Now please choose what to do "\
                "with empty pre-determined non-allocated stack:\n");\
        printf ("Legend:\n");\
        printf ("1 - Construct stack\n");\
        printf ("2 - Push value into stack\n");\
        printf ("3 - Pop value out of the stack\n");\
        printf ("4 - Destruct stack\n");\
        printf ("5 - Print dump info\n");\
        printf ("6 - Reprint the legend\n");\
        printf ("0 - Exit the program\n");

    #define WHATTODO printf ("Enter your choice here: ")

    #define ASSERT( cond )\
    if (!cond)\
    {\
        printf ("Oops! Something's gone wrong within the assertion <%s>\n"\
                "Life <%s>\nLine <%d>\n"\
                "The program will be shut down soon.\n", #cond, __FILE__, __LINE__);\
        printf ("Stack before destruction:\n");\
        Stack_Dump (&stack);\
        Stack_Destruct (&stack);\
        printf ("Stack after destruction:\n");\
        Stack_Dump (&stack);\
        printf ("Shutting down the program.\n"\
                "Please send this error report to google and NASA.\n");\
        return -1;\
    }

    Stack_t stack = {};
    int mode = 0;
    int sloptimization = 0;
    double value_to_push = 0, value_popped = 0;
    int res_input = 0;
    clock_t t_start = 0, t_finish = 0;

    printf ("Do you want to use the optimized version of stack? (1/0): ");
    res_input = scanf ("%d", &sloptimization);

    assert (res_input); assert (sloptimization == 1 || sloptimization == 0);

    INTERVAL;
    LEGEND;

    while (1)
    {
        WHATTODO;
        res_input = scanf ("%d", &mode);

        assert (res_input); assert (mode >= 0); assert (mode <= 6);

        switch (mode)
        {
            case CMD_CONSTRUCT:
                t_start = clock();

                if (Stack_Error_Catch (Stack_Construct (&stack),
                "Constructing the stack..\n") == ERR) return ERR;

                t_finish = clock();
                printf ("Stack is successfully constructed!\n");
                printf ("Time elapsed: %lg\n", (double) ((double) t_finish - (double) t_start)/CLOCKS_PER_SEC);
                break;

            case CMD_PUSH:
                printf ("Enter integer value to push: ");
                res_input = scanf ("%lg", &value_to_push);
                assert (res_input); assert (value_to_push < INT_MAX);

                t_start = clock();

                if (sloptimization)
                {
                    if (Stack_Error_Catch (Stack_Perverted_Push (&stack, value_to_push),
                    "Pushing your value somehow smartly..\n") == ERR) return ERR;
                }
                else
                {
                    if (Stack_Error_Catch (Stack_Push (&stack, value_to_push),
                    "Pushing your value..\n") == ERR) return ERR;
                }

                t_finish = clock();
                printf ("Value pushed!\n");
                printf ("Time elapsed: %lg\n", (double) ((double) t_finish - (double) t_start)/CLOCKS_PER_SEC);
                break;

            case CMD_POP:
                t_start = clock();

                if (sloptimization)
                {
                    if (Stack_Error_Catch (Stack_Perverted_Pop (&stack, &value_popped),
                    "Getting value using innovational algorithms..\n") == ERR) return ERR;
                }
                else
                {
                    if (Stack_Error_Catch (Stack_Pop (&stack, &value_popped),
                    "Getting value..\n") == ERR) return ERR;
                }

                t_finish = clock();
                printf ("Value popped out of the stack: %lg\n", value_popped);
                printf ("Time elapsed: %lg\n", (double) ((double) t_finish - (double) t_start)/CLOCKS_PER_SEC);
                break;

            case CMD_DESTRUCT:
                t_start = clock();

                if (Stack_Error_Catch (Stack_Destruct (&stack),
                "Destroying stack..\n") == ERR) return ERR;

                t_finish = clock();
                printf ("Stack destroyed!\n");
                printf ("Time elapsed: %lg\n", (double) ((double) t_finish - (double) t_start)/CLOCKS_PER_SEC);
                break;

            case CMD_DUMP:
                printf ("Dump info:\n");
                t_start = clock();

                Stack_Dump (&stack);

                t_finish = clock();
                printf ("-----\n");
                printf ("Time elapsed: %lg\n", (double) ((double) t_finish - (double) t_start)/CLOCKS_PER_SEC);
                break;

            case CMD_LEGEND:
                INTERVAL;
                LEGEND;
                break;

            case CMD_END:
                printf ("Good bye!\n");
                if (Stack_Is_OK (&stack))
                {
                    printf ("You've forgot to destruct the stack.\n");
                    printf ("Then I'll do it for you.\n");
                    Stack_Error_Catch (Stack_Destruct (&stack),
                    "Destroying while exiting..\n");
                    printf ("Stack destroyed!\nGood bye!\n");
                }
                return OK;

            default:
                printf ("How you forced the unknown command to reach this point through asserts?!\n");
                break;
        }

        INTERVAL;
    }

    #undef WHATTODO
    #undef LEGEND
    #undef INTERVAL

    return OK;
}


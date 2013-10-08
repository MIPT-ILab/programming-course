#include <stdio.h>
#include <stdlib.h>

#define ASSERT( cond, s)                                                                            \
do                                                                                                  \
{                                                                                                   \
    if (!(cond))                                                                                    \
    {                                                                                               \
        printf("Condition %s is wrong.[%s] \nFile[%s]\nLine[%d]\n", #cond,s, __FILE__, __LINE__);   \
        abort();                                                                                    \
    }                                                                                               \
}                                                                                                   \
while(0)

#ifdef DEBUG
    #define LOG_PRINTF( message ) printf("File[%s] Function[%s] Line[%d] [%s]\n",__FILE__,__FUNCTION__,__LINE__, message)
#else
    #define LOG_PRINTF( message ) do {} while(0)
#endif

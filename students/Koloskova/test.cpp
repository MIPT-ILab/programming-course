#include <stdio.h>

#define DEBUG

#include "define.h"
#define SIZE 2
int main()
{
    LOG_PRINTF("hello");
    int a = 0, b = 1;
    ASSERT(a == b, "message");
    return 0;
}

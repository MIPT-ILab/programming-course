#include <stdio.h>

#define DEBUG

#ifdef DEBUG
    #define OUT printf
#else
    #define OUT if (0) printf
#endif

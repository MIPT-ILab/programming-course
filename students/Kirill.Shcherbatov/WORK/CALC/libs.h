#ifndef LIBS_H
#define LIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
    #define OUT         printf
#else
    #define OUT if (0)  printf
#endif

#endif // LIBS_H

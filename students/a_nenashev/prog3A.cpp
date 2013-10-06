/*************************************************************************************
* @file    NOK.cpp
* @date    2013-10-06 19:00
* @author  Alex Nenashev <a.nenash95@gmail.com>
*
* Program find the biggest divisor of 3 numerals
*
* @version v1.1
*
* What's new in this version:
* - Headers
* - Doxygen texts
* - Wild struct of program, spaghetti code-like
*
* @par     Program gets 3 numerals and finds out it's biggest divisior
*
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>

//-------------------------------------------------
//#define _EJC
//-------------------------------------------------

#define DEF_O 0.001

#define OUT printf
#ifndef _EJC
    #define OUT if(0) printf
#endif

int min(int a, int b)
{
    return (a < b)? a : b;
}

int BigDiv(int one, int two, int three)
{
    int locksize = min(one, min(two, three));
    int i = 0;
    for ( i = locksize; i > 0; i--)
    {
        if (one % i == 0 && two %i == 0 && three % i == 0)
        {
            return i;
        }
    }
    return 0;
}

int main()
{
    OUT("File NOK.cpp\n"\
        "Date %s, time %s\n"\
        "Author: Alex Nenashev\n", __DATE__, __TIME__);
    OUT("# Enter 3 numerals: ");
    int one = 0, two = 0, three = 0;
    scanf("%d%d%d", &one, &two, &three);
    OUT("# Here they are: \none: %d\ntwo: %d\nthree: %d\n\n\n", one, two, three);
    int k = BigDiv(one, two, three);
    if (k == 1)
    {
        OUT("# Nums are relatively prime\n\n");
    }
    else
    {
        OUT("This is The Big Divisor: %d\n\n", k);
    }
    return 0;
}

/*************************************************************************************
* @file    NOK.cpp
* @date    2013-10-06 19:00
* @author  Alex Nenashev <a.nenash95@gmail.com>
*
* Program find the biggest divisor of 3 numerals
*
* @version v1.2
*
* What's new in this version:
* - More Doxygen texts
* - Arguing with reviewer in names of parameters
* - Better code for everyone
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

/** ****************************************
* Min - find minimum of two args. 
*
* @param a        first comparative
* @param b        second comparative
* @return     minimum(a, b)
*
********************************************/

int min(int a, int b)
{
    return (a < b)? a : b;
}

/** *******************************************************************
* BigDiv - function that find the biggest divisor of 3 arguments
*
* @param first_num     first parameter
* @param second_num    second parameter
* @param third_num     third parameter
* @param locksize      the biggest divisor of three numerals (for coprime cases)
*
* @return              Biggest divisor of 3 numerals
*
* @note                Arguments are unordered, so I gave them silly names for better understanding
***********************************************************************/

int BigDiv(int first_num, int second_num, int third_num)
{
    int locksize = min(first_num, min(second_num, third_num));
    int i = 0;
    for ( i = locksize; i > 0; i--)
    {
        if (first_num % i == 0 && second_num %i == 0 && third_num % i == 0)
        {
            return i;
        }
    }
    return 0;
}

/** ************************************************************************
* Main - enters user information, checks up date & time of compilation, names author and makes other functions work in proper way.
*
* @param one       first numeral
* @param two       second numeral
* @param three     thrid numeral
*
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
    
    (k == 1)? OUT ( "# Nums are relatively prime\n\n" ) :\
    OUT ("This is The Big Divisor: %d\n\n", k);
    
    return 0;
}

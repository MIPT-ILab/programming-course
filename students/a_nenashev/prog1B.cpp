/*************************************************************************************
* @file    prog1B.cpp
* @date    2013-10-10 1:09
* @author  Alex Nenashev <a.nenash95@gmail.com>
*
* Finding squares
*
* @version v1.1
*
* What's new in this version:
* - Doxygen texts
* - More good code
*
* @par     Program gets number and finds out, if it is a square(prints YES if so, NO if not)
*
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


//-----------------------------------------------------------------------------------------
#define _EJC
//-----------------------------------------------------------------------------------------
#ifdef _EJC
    #define OUT printf
#else
    #define OUT if(0) printf
#endif

/** ********************************************************
* @par num       main part of function, if it's a square, return 0, 1 if not
* @par i         counter
*
*
*
* @note Warning, if i = 1, so, every number will be a square.
* Lolz
*
***********************************************************/
int SquareFind(int num)
{
    assert(num);
    int i = 0;
    for(i = 2; i <= num - 1; i++)
    {
        if (num % i*i == 0)
        {
            return 1;
        }
        if (i == num - 1)
        {
            return 0;
        }
    }
}

int main()
{
    unsigned int num = 0;
    OUT("# Enter number, and I'll check if it includes of some sqares:\n");
    scanf("%d", &num);
    int k = 0;
    k = SquareFind(num);
    OUT ("# The result is: ");
    (k == 1)? printf("YES\n") : printf("NO\n");
    return 0;
}

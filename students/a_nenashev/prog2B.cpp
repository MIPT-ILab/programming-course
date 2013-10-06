/** ****************************************************************
* @mainpage
* @file    prog2B.cpp
* @date    2013-10-06, 22:30
* @author  Alex Nenashev <a.nenash95@gmail.com>
*
* Normalization of square roots.
*
* @par     For this program it's not easy to write down doxy-comment that will be less than
* program..:D
*
*
****************************************************************** **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _EJC
#ifdef _EJC
    #define OUT printf
#else
    #define OUT if(0) printf
#endif
/** Function norm
* @param nroot      under-root value after normalization
* @param nconst     out-root value
*
* @return
******************************************* **/

int norm(int *rootv, int *nroot, int *nconst)
{

    *nroot = *rootv;
    *nconst = 1;
    int i = 0;
    double max = sqrt(*rootv);
    for ( i = 2, i < max, i++)
    {
        if (*rootv % i*i == 0)
        {
            *nconst *= i;
            *rootv /= i*i;
        }
    }
    if ( *nroot == *rootv) return 0;
    else
    {
        *nroot = *rootv;
        return 1;
    }
}

int main()
{
    int rootv = 0, k = 0;
    int *norm_root = 0, *norm_const = 0;
    OUT("# Enter root value to normalize: \n");
    scanf("%d",&rootv);
    k = norm(rootv, norm_root, norm_const);
    switch(k)
    {
        case 1:
            OUT("Const\t%lf\nroot value\t%lf", *norm_const, *norm_root);
            return 0;
        case 0:
            return 1;
    }
}

/** ****************************************************************
* @mainpage
* @file      prog2B.cpp
* @date      2013-10-06, 22:30
* @author    Alex Nenashev <a.nenash95@gmail.com>
* @version   1.1
*
* What's new?
* - More doxygen code
* - New named parameters
*
* Normalization of square roots.
*
* @par     For this program it's not easy to write doxy-comment that will be less than
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

/** *******************************************
* Function norm
* @param nroot      under-root value after normalization
* @param nconst     out-root value
* @param rootv      primary value of root
*
* @return           0 if all is OK, 1 if something goes wrong
******************************************** **/

int norm(int *rootv, int *nroot, int *nconst)
{
    assert(rootv);
    assert(nroot);
    assert(nconst);
    
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
    
    assert( *nroot == *rootv );
    return 0;
}

/** **************************************************************
* Main - enters parameters, uses Switch-construction for printing fails and wins.
*
* @param rootv         root value for normalization
* @param k             returned value of function norm()
* @param norm_root     normalized root value
* @param norm_const    normalized const value
*
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
            OUT("Const\t");
            printf("%lf", *norm_const);
            OUT("Root value\t",);
            printf("%lf", *norm_root);
            return 0;
        case 0:
            return 1;
    }
}

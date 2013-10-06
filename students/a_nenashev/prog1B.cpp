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
    OUT("# Enter number, and I'll check if it consist of some sqares:\n");
    scanf("%d", &num);
    int k = 0;
    k = SquareFind(num);
    OUT ("# The result is: ");
    if (k == 1)
    {
        printf("YES\n");
        return 0;
    }
    if (k == 0)
    {
        printf("NO\n");
        return 0;
    }
    return 0;
}

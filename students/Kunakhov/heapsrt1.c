
/**======================================================
    program to sort the array
    @file heapsrt.c
    @date 9.10.13
    @author Kunakhov Ivan <Ivan.Kunakhov@frtk.ru>
======================================================**/


double const  eps = 0.00000000001;
int const SIZE = 1000;


#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>



#define ASSERT( cond , txt )           \
    if ( !( cond ) )                      \
        {                                 \
        printf ("Error: %s \n  file: %s, line: %d \n", #txt, __FILE__, __LINE__);    \
        abort(); \
        }



/**===============================================================
    exchange - swaps  two elements of the array
    @param i - number of the first element of the array to replace
    @param j -  number of the second element to replace
    @param[out] a - array with replaced elements
==================================================================**/

int  exchange(int i,int j,double *a)
{
    double b;

    ASSERT(a!= NULL, "adress of the a[0] is zero!");
    ASSERT(( (0 <= i) && (i <= SIZE) ), "i does not match the array indexes");
    ASSERT(( (0 <= j) && (j <= SIZE) ), "j does not match the array indexes");


    b = a[i];
    a[i] = a[j];
    a[j] = b;
}





/**=============================================================
    heap - recursive function that sorts triple (all array, we
    present a tree, split into triple, headed of each triples
    and is the ancestor of every parent to 2 offspring. Function
    sorts tree starting with the last triple, and moves up the
    tree each time recursively checking the lower elements

    @param i - number of the element of the array
    @param M -  number of the highest element int the triple

    @param[out] a - the the array of numbers which need to be sorted

================================================================**/
int heap (int i, int M, double * a)
{
    int j = i ;
    int l = i*2,  r = i*2 + 1;  /** l-left offspring r-right offspring of the triple**/


    ASSERT(a!= NULL, "adress of the a[0] is zero!");
    ASSERT(( (1 <= l) && (l <= SIZE) ),"l does not match the array indexes" );
    ASSERT(( (1 <= r) && (r <= SIZE) ), "r does not match the array indexes");
    ASSERT(( (1 <= i) && (i <= SIZE) ), "i does not match the array indexes");
    ASSERT(( (1 <= M) && (M <= SIZE) ), "M does not match the array indexes");




    if ((l <= M) && (a[l]-a[j] >eps))
    {
        j = l;
    }
    if ((r <= M) && (a[r]-a[j] > eps))
    {
        j = r;
    }
    if (i != j)
    {
        exchange(i, j, a);
        heap(j, M, a);
    }
}







int main ()
{
 double a[SIZE]; //= {};
 int  i = 0, M = 0, n = 0, k=0, q=0;

    printf("how many arrays wold you sort ?\n");
    scanf("%d", &k);


for (q = 1;q <= k; q++ )
{
    n = 0;
    M = 0;


    printf("insert length of your array\n");
    scanf("%d",&n);
    printf("insert elements of the array\n");



    for (i = 1; i <= n; i++)
    {
        scanf("%lf", &a[i]);
    }

    for (i = 1; i <= n; i++)
    {
        M = n;
        for (i = n/2; i >= 1; i--)
        {
            heap(i,M,a);
        }
        while (M > 1)
        {
            exchange(1,M,a);
            M--;
            heap(1,M,a);
        }
        for (i = 1; i <= n; i++)
            printf("%lg ", a[i]);
    }
printf("\n");
}
return 0;
}

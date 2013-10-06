#include <stdio.h>
#include <math.h>

int check ( int i);
int normalization_of_the_root_coefficient_a (int n);
int normalization_of_the_root_coefficient_b (int n);

int main()
{
    printf ("PROGRAM: NORMALIZATION OF THE ROOT\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER N\n");

    int n = 0, a = 0 , b = 0;
    scanf ("%d", &n);
    a = normalization_of_the_root_coefficient_a(n);
    b = normalization_of_the_root_coefficient_b(n);

    printf ("COEFFICIENT A = %d\n", a);
    printf ("COEFFICIENT B = %d\n", b);
    return 0;

}

int check ( int i)
{
    int p = 1;
    for ( p = 2; p <= sqrt (i); ++p)
        if (i % p == 0)
            return 1;
    return 0;
}

int normalization_of_the_root_coefficient_b (int n)
{
    int i = 0, b = 1;

    for ( i = 1; i <= sqrt(n); ++i)
    {

        if ( (n % (i * i)) == 0  && check(i) == 0)
            b = b * i;
    }

    return b;
}

int normalization_of_the_root_coefficient_a (int n)
{
    int a = 0;
    a = n / (normalization_of_the_root_coefficient_b(n) * normalization_of_the_root_coefficient_b(n));
    return a;
}


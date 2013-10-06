# include <stdio.h>
# include <math.h>

int SquareDivider ( int number);

int main ()
{
    int number = 0;

    printf ("PROGRAM: FINDING THE SQUARE DIVIDER\n");
    printf ("AUTHOR: SHARAFUTDINOV RUSLAN, v 1.0 \n");
    printf ("ENTER THE NUMBER\n");
    scanf ("%ld", &number);

    if (SquareDivider(number))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;

}
int SquareDivider ( int number)
{
    int i = 0;
    double sqrt_number = sqrt(number);
    for ( i = 2; i <= sqrt_number; ++i  )
    {
        if ( number % (i*i) == 0) return 1;
    }
    return 0;
}

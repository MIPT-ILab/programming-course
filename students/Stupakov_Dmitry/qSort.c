#include <stdio.h>
#include <stdlib.h>
//Finding the minimum
int Minimum(int *p, int *q)
{
	return *p - *q;
}
int main()
{
	int i = 0, n = 0, a[30000] = {0*30000};
	printf("#Author Dmitry Stupakov\n"
		   "#Version 1.0\n"
		   "#30.09.2013\n"
		   "#Enter the number of array elements:\n");
	scanf_s("%i", &n);
	printf("#Elements:\n");
    for(i=0; i<n; i++)
	    scanf_s("%i", &a[i]);
    qsort(a, n, sizeof(int), Minimum);
	printf("#Sorted array:\n");
    for(i=0;i<n;i++)
	    printf("%i ", a[i]);
	printf("\n");
	system("pause");
	return 0;
}
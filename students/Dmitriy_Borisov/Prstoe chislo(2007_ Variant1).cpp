#include <stdio.h>
#include <math.h>

int main()
{
 int n;
 scanf("%d", &n);
 for (int j = 1; j <= n; j++) 
 { 
   unsigned int chislo;
   scanf("%d", &chislo);
   int i=2, del=0;
   while (i <= sqrt(1.0*chislo))
   {
     if (chislo % i == 0) {del = 1;break;};
     i++;
   };
 if (del == 0 && chislo != 1)
 printf("%u ",chislo);
 };
 printf("\n");
}
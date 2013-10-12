#include <stdio.h>
#include <math.h>

int main()
{
  int chislo;
  scanf ("%d", &chislo);
  
  int i=4, del=0;
   while (i <= chislo)
   {
     if (chislo % i == 0) 
	  {
		 int koren=sqrt(1.0*i); 
		  if (koren*koren == i) 
			  {del = 1;break;};
	  }	 
	 i++;
   };
   if (del == 1) printf("YES\n"); else printf("NO\n");
}

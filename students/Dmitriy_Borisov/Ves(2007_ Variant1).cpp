#include <stdio.h>
#include <math.h>

int main()
{
  int n, ch;
  scanf ("%d", &n);
  
  while (n != 1)
  {  
	int k=0;
	 
	 if (n % 4 == 0) 
	  {
	   n/=4; k++;
	  }
	 else 
	   {
		 if ((n-1) % 4 == 0) 
	      {
			n=(n-1)/4; k++;
		  }
	     else 
		   {
			 if ((n+1) % 4 == 0) 
	          {
				n=(n+1)/4; k++;
			  }
			 else break;
		   }
       }
   };

  if (n==1) printf("YES\n"); else printf("NO\n");
   
}
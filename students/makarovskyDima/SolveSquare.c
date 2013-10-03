#include <math.h>
#include <stdio.h>

   int main()
   {
       double a=0,b=0,c=0,x1=0,x2=0,d=0;
       printf("enter the coefficients\n");
       scanf("%lg %lg %lg",&a,&b,&c);
        d=b*b-4*a*c;
        
       if (a==0)
            printf("equation does not square"); 
      
       else
       {
       if (d<0) 
       printf("no solutions");
       else
       
       if (d>0)
       {
       x1=(-b+sqrt(d))/(2*a);
       x2=(-b-sqrt(d))/(2*a);
       printf("x1=%lg x2=%lg\n",x1,x2);
       }  
       
         else
         printf("x=%lg",(-b)/(2*a));
       }
       system("pause");
       return 0;       
       }
       

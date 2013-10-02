#include <stdio.h>
int main()
{
    double a[1000],t;
    int i,j,c;
    printf("enter the number of array elements\n");
    scanf("%d",&c);
    printf("enter the array elements\n");
    
         for(i=0;i<c;i++)
         scanf("%lg",&a[i]);
    
       
         for(j=0;j<c;j++)
      {  
         
      for(i=0;i<(c-1);i++)
      {
       if (a[i]>a[i+1])
          {
           t=a[i+1];
           a[i+1]=a[i];
           a[i]=t;
             }            
             }
             }
             
        for(i=0;i<c;i++)
         printf("%lg ",a[i]);

       system("pause");
       return 0;
       }               

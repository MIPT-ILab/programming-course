#include <stdio.h>
int main()
{
    int a[1000],j,c,i,t;
    printf("enter the number of array elements\n");
    scanf("%d\n",&c);
    printf("enter the array elements\n");
    
         for(i=0;i<c;i++)
         scanf("%d",&a[i]);
    
       
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
         printf("%d ",a[i]);

       system("pause");
       return 0;
       }               

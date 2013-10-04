#include<stdio.h>
#define N 10
int main ()
{
    int a[N],n,t,j,i;
    scanf("%i",&n);
    for(i=0;i<n;i++)
    {
                    scanf("%i",&a[i]);
    }
    for(i=0;i<(n-1);i++)
    {
                        for(j=i+1;j<n;j++)
                        {
                                          if(a[i]>a[j])
                                          {
                                                    t=a[i];
                                                    a[i]=a[j];
                                                    a[j]=t;
                                         }
                        }                           
    }
    for(i=0;i<n;i++)
    {
                    printf("%i ",a[i]);  
}
system("pause");
return 0;
}                                                         

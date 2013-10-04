//{=================================================================================
//! file    Sort.c
//! date    2013-10-04 
//! author  Roma Blinov <roman.blinov@frtk.ru>
//! version 1.0
//! Сортировка массива.
//}=================================================================================

#include <stdio.h>
#define N 1000

int main()
{      printf("file     sort.c\n"
              "date     2013-10-04\n"
              "autor    Roma Blinov <roman.blinov@frtk.ru>\n"
              "version  1.0\n");
               

       int i=0, j=0, n=0;
       double a[N]={0} , m=0;
       printf("Input number of elements:\n");
       scanf("%d", &n);
       printf("Elements:\n");
       for (i = 0; i < n; ++i) 
           scanf("%lf", &a[i]);            //reading
       
       
       for (i = 0; i < n; ++i)
           for (j = i + 1; j < n; ++j)
               if (a[i]>a[j]) 
                  {
                  m=a[i]; a[i]=a[j]; a[j]=m;   // sort
                  }
       
       printf("Sorted array:\n");           
                  
       for (i = 0; i < n; ++i) 
           printf("%lf " , a[i]);              //output
          
         
       system("pause");
       return 0;
       }    

//{=================================================================================
//! file    Sort.c
//! date    2013-10-04 
//! author  Roma Blinov <roman.blinov@frtk.ru>
//! version 2.0
//! Sorting an array.
//}=================================================================================

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
int main()
{      
       printf("# file       sort.c\n"
              "# date       2013-10-18\n"
              "# autor      Roma Blinov <roman.blinov@frtk.ru>\n"
              "# version    2.0\n");
               

       int i=0, j=0, Data_Size = 0, Check = 0;      
       double *Data , Swap;
       
       
       printf("# Input number of elements:\n");
       Check = scanf("%d", &Data_Size);
       assert(Check == 1);
       printf("# Elements:\n");
       Data = (double*)calloc(Data_Size, sizeof(double));
       
       for (i = 0; i < Data_Size; ++i)
           { 
              Check = scanf("%lf", &Data[i]);
              assert(Check == 1);            
           }
       
       for (i = 0; i < Data_Size; ++i)
           for (j = i + 1; j < Data_Size; ++j)
               if (Data[i] > Data[j]) 
                  {  
                     assert(i >= 0);
                     assert(j >= 0);
                     assert(i < Data_Size);
                     assert(j < Data_Size);
                     Swap = Data[i]; 
                     Data[i] = Data[j]; 
                     Data[j] = Swap; 
                  }
       
       printf("# Sorted array:\n");           
                  
       for (i = 0; i < Data_Size; ++i) 
           printf("%lg " , Data[i]);  
       free(Data);                
          
         
       system("pause");
       return 0;
       }    

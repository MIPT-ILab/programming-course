//{========================================================================================================
//! @file    2-sort.cpp
//! @date    2013-11-02 15:21
//! @author  Alexey Neganov <neganovalexey@gmail.com>
//!
//! Sorting array of floating-point numbers (double C type) by mergesort algorithm
//!
//! @par     Input: number of the elements and elements of array as such
//!          Output: array after sorting
//}========================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define EPSILON 10e-6
#define IS_BELOW(x1, x2) x1-x2<EPSILON
#define IS_ABOVE(x1, x2) x1-x2>EPSILON
typedef double datatype;
const int OK = 1;
const int ERROR = 0;
//{========================================================================================================
//! data_copy - copy some number of elements of the array, starting from a certain position, to the buffer.
//!
//! @param         data         Array - source of copied data
//! @param[out]    buffer       Buffer
//! @param         copy_number  Number of elements to copy
//! @param         position     Position in source array to start from
//!
//! @return        OK
//}========================================================================================================
int data_copy(const datatype *data, datatype *buffer, const int copy_number, const int position)
   {
   assert(data && buffer);
   for(int i=0; i<copy_number; i++)
      {
      assert(0 <= i && i < copy_number);
      buffer[i] = data[position+i];
      }
   return OK;
   }
//{========================================================================================================
//! cmp_double - compare two floating-point numbers (double C type)
//!
//! @param      a     First number
//! @param      b     Second number
//!
//! @return     1, if a > b; -1, if a < b; 0, if a = b.
//!
//! @note       Calculation precision is considered to be EPSILON.
//}========================================================================================================
int cmp_double(const double a, const double b)
    {
    if( IS_ABOVE(a,b) )
       return 1;
    else if ( IS_BELOW(a,b) )
       return -1;
    else return 0;
    }
//{========================================================================================================
//! data_ord_merge - merge two arrays in the order of elements, which is set in special compare function
//!
//! @param[out]    receiver     Array - receiver of data
//! @param         source1      Array - first source of data
//! @param         source2      Array - second source of data
//! @param         number       Size of receiver
//! @param         number1      Size of first source
//! @param         number2      Size of second source
//! @param         cmp          Compare function, which can take on values -1, 0 or 1.
//!
//! @return        OK
//}========================================================================================================
int data_ord_merge(datatype *receiver, const datatype *source1, const datatype *source2,\
const int number, const int number1, const int number2, int (*cmp)(const datatype, const datatype))
    {
    assert(receiver && source1 && source2);
    assert(number >= number1 + number2);
    assert(cmp);
    int i=0, i1=0, i2=0;
    for(i=0; i<number; i++)
       {
       if(i1<number1 && i2<number2)
          {
          if( cmp(source1[i1], source2[i2]) <= 0 )
             {
             receiver[i] = source1[i1];
             i1++;
             }
          else
             {
             receiver[i] = source2[i2];
             i2++;
             }
           }
        else if(i1 >= number1 && i2 < number2)
           {
           receiver[i] = source2[i2];
           i2++;
           }
        else if(i1 < number1 && i2 >= number2)
           {
           receiver[i] = source1[i1];
           i1++;
           }
       }
    return OK;
    }
//{========================================================================================================
//! mergesort - sorting array of floating-point numbers (double C type) by mergesort algorithm
//!
//! @param[out]    data         Array to sort
//! @param         number       Size of array
//! @param         cmp          Compare function, which can take on values -1, 0 or 1.
//!
//! @return        OK
//}========================================================================================================
int mergesort(datatype *data, const int number, int (*cmp)(const datatype, const datatype))
   {
    assert(data);
    assert(cmp);
    if( number > 1 )
       {
       const int num1 = number/2;
       datatype *data1 = (datatype*)calloc(num1, sizeof(*data1));
       assert(data1);
       data_copy(data, data1, num1, 0);
       mergesort(data1, num1, cmp);

       const int num2 = (number%2 == 0)? num1: num1+1;
       datatype *data2 = (datatype*)calloc(num2, sizeof(*data2));
       assert(data2);
       data_copy(data, data2, num2, num1);
       mergesort(data2, num2, cmp);

       data_ord_merge(data, data1, data2, number, num1, num2, cmp);

       free(data1);
       free(data2);
       }
    return OK;
   }
//{========================================================================================================
//! double_warriorscanf - function, that provides correct input of floating-point values
//!
//! @param[out]      value   Value to reading from stdin
//!
//! @return     OK or ERROR
//}========================================================================================================
int double_warriorscanf(double *value)
   {
   if (!value) return ERROR;
   int valid = scanf("%lg", value);
   if(!valid || valid == EOF)
      return ERROR;
   return OK;
   }
//{========================================================================================================
//! int_warriorscanf - function, that provides correct input of integer values
//!
//! @param[out]      value   Value to reading from stdin
//!
//! @return     OK or ERROR
//}========================================================================================================
int int_warriorscanf(int *value)
   {
   if (!value) return ERROR;
   int valid = scanf("%d", value);
   if(!valid || valid == EOF)
      return ERROR;
   return OK;
   }
//{========================================================================================================
//! polite_action - function, that give message to user, if he do incorrect input
//!
//! @return     OK or ERROR
//}========================================================================================================
int polite_action()
   {
   printf("#ERROR!\n#It was incorrect input there. Be more careful and try again.\n");
   return OK;
   }



int main()
   {
   int number=0;
   printf("#Enter the number of elements\n");
   if (int_warriorscanf(&number)!=OK)
      {
      polite_action();
      return 0;
      }
   datatype *data = (datatype*)calloc(number, sizeof(datatype));
   assert(data);
   printf("#Enter your data\n");
   for(int i=0; i<number; i++)
      {
      assert(0 <= i && i < number);
      if (double_warriorscanf(data+i)!=OK)
         {
         polite_action();
         return 0;
         }
      }
   mergesort(data, number, cmp_double);
   for(int i=0; i<number; i++)
       printf("%lg ", data[i]);
   printf("\n");
   free(data);
   return 0;
   }
